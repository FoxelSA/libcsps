/*
 * libcsps - Crossed-signal positioning system library
 *
 * Copyright (c) 2013-2014 FOXEL SA - http://foxel.ch
 * Please read <http://foxel.ch/license> for more information.
 *
 *
 * Author(s):
 *
 *      Nils Hamel <n.hamel@foxel.ch>
 *
 *
 * This file is part of the FOXEL project <http://foxel.ch>.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * Additional Terms:
 *
 *      You are required to preserve legal notices and author attributions in
 *      that material or in the Appropriate Legal Notices displayed by works
 *      containing it.
 *
 *      You are required to attribute the work as explained in the "Usage and
 *      Attribution" section of <http://foxel.ch/license>.
 */


/*
    Source - Includes
 */

    # include "csps-timestamp.h"

/*
    Source - FPGA timestamp reader
 */

    lp_Time_t lp_timestamp( 

        const lp_Void_t * const lpRec

    ) {

        /* Return filtered timestamp value - 32HSb for unix time and 20LSb for microseconds */
        return( lp_Time_s( 0xFFFFFFFF000FFFFF ) & ( * ( ( uint64_t * ) lpRec ) ) );

    }


/*
    Source - Timestamp composer
 */

    lp_Time_t lp_timestamp_compose( 

        lp_Time_t lpSec, 
        lp_Time_t lpUsec

    ) {

        /* Return composed timestamp */
        return( ( lpSec << lp_Size_s( 32 ) ) | lpUsec );

    }

/*
    Source - Timestamp decomposer
 */

    lp_Time_t lp_timestamp_sec( 

        lp_Time_t lpT 

    ) {

        /* Return time stamp seconds */
        return( lpT >> lp_Size_s( 32 ) );

    }

    lp_Time_t lp_timestamp_usec( 

        lp_Time_t lpT 

    ) {

        /* Return time stamp microseconds */
        return( lpT & lp_Time_s( 0x00000000000FFFFF ) );

    }

/*
    Source - Timestamp search
 */

    lp_Size_t lp_timestamp_index( 

        lp_Time_t   lpT, 
        lp_Time_t * lpBuffer, 
        lp_Size_t   lpSize

    ) {

        /* Check timestamp range */
        if ( ( lp_timestamp_ge( lpBuffer[0], lpT ) == LP_TRUE ) || ( lp_timestamp_ge( lpT, lpBuffer[lpSize - 1] ) == LP_TRUE ) ) {

            /* Check boundaries equality */
            if ( lp_timestamp_eq( lpBuffer[0], lpT ) == LP_TRUE ) {

                /* Return exact index */
                return( lp_Size_s( 0 ) );

            } else {

                /* Check boundaries equality */
                if ( lp_timestamp_eq( lpBuffer[lpSize - 1], lpT ) == LP_TRUE ) {

                    /* Return exact index */
                    return( lpSize - lp_Size_s( 1 ) );

                } else {

                    /* Return range fault */
                    return( LP_TIMESTAMP_FAULT );

                }

            }

        } else {

            /* Dichotomous search variables */
            lp_Size_t lpDichD = lp_Size_s( 0 );
            lp_Size_t lpDichM = lp_Size_s( 0 );
            lp_Size_t lpDichU = lpSize - lp_Size_s( 1 );

            while ( ( lpDichU - lpDichD ) > lp_Size_s( 1 ) ) {

                /* Compute range middle */
                lpDichM = ( lpDichD + lpDichU ) >> lp_Size_s( 1 );

                /* Check sub-range position */
                if ( lp_timestamp_ge( lpT, lpBuffer[lpDichM] ) == LP_TRUE ) {

                    /* Update downer boundary */
                    lpDichD = lpDichM;

                } else {

                    /* Update upper boundary */
                    lpDichU = lpDichM;

                }

            }

            /* Verify search results */
            if ( lp_timestamp_eq( lpT, lpBuffer[lpDichU] ) == LP_TRUE ) {

                /* Returns exact index */
                return( lpDichU );

            } else {

                /* Return the index of nearest lower or exact timestamp */
                return( lpDichD );

            }

        }

    }

/*
    Source - Timestamp comparison
 */

    lp_Enum_t lp_timestamp_eq( 

        lp_Time_t lpTa, 
        lp_Time_t lpTb

    ) {

        /* Verify timestamp equality */
        if ( lpTa == lpTb ) {

            /* Return boolean result */
            return( LP_TRUE );

        } else {

            /* Return boolean result */
            return( LP_FALSE );

        }

    }

    lp_Enum_t lp_timestamp_ge( 

        lp_Time_t lpTa, 
        lp_Time_t lpTb

    ) {

        /* Timestamp decomposition */
        lp_Time_t cspsSeca  = lp_timestamp_sec ( lpTa );
        lp_Time_t cspsUseca = lp_timestamp_usec( lpTa );
        lp_Time_t cspsSecb  = lp_timestamp_sec ( lpTb );
        lp_Time_t cspsUsecb = lp_timestamp_usec( lpTb );

        /* Verify unix time */
        if ( cspsSeca > cspsSecb ) {

            /* Return boolean result */
            return( LP_TRUE );

        } else {

            /* Verify unix time */
            if ( cspsSeca == cspsSecb ) {

                /* Verify microseconds time */
                if ( cspsUseca >= cspsUsecb ) {

                    /* Return boolean result */
                    return( LP_TRUE );

                } else  {

                    /* Return boolean result */
                    return( LP_FALSE );

                }

            } else {

                /* Return boolean result */
                return( LP_FALSE );

            }

        }

    }

/*
    Source - Timestamp arithmetic
 */

    lp_Time_t lp_timestamp_add( 

        const lp_Time_t lpTa, 
        const lp_Time_t lpTb

    ) {

        /* Compute addition by parts */
        lp_Time_t lpSec  = lp_timestamp_sec ( lpTa ) + lp_timestamp_sec ( lpTb );
        lp_Time_t lpUsec = lp_timestamp_usec( lpTa ) + lp_timestamp_usec( lpTb );

        /* Return addition of timestamps */
        return( lp_timestamp_compose( lpSec + ( lpUsec > lp_Time_s( 1000000 ) ? lp_Time_s( 1 ) : lp_Time_s( 0 ) ), lpUsec % lp_Time_s( 1000000 ) ) );

    }

    lp_Time_t lp_timestamp_diff( 

        lp_Time_t lpTa, 
        lp_Time_t lpTb

    ) {

        /* Verify timestamp equality */
        if ( lp_timestamp_eq( lpTa, lpTb ) == LP_TRUE ) {

            /* Return difference */
            return( 0 );

        } else {

            /* Microseconds difference variable */
            lp_Size_t lpUsec = 0;

            /* Verify highest timestamp */
            if ( lp_timestamp_ge( lpTb, lpTa ) == LP_TRUE ) { uint64_t cspsSwap = lpTa; lpTa = lpTb; lpTb = cspsSwap; }

            /* Compute microseconde difference */
            lpUsec = lp_timestamp_usec( lpTa ) - lp_timestamp_usec( lpTb );

            /* Verify microseconde sign */
            if ( lpUsec < 0 ) {

                /* Return difference */
                return( ( ( lp_timestamp_sec( lpTa ) - lp_timestamp_sec( lpTb ) - 1 ) << lp_Size_s( 32 ) ) | ( lpUsec + lp_Size_s( 1000000 ) ) );

            } else {

                /* Return difference */
                return( ( ( lp_timestamp_sec( lpTa ) - lp_timestamp_sec( lpTb ) ) << lp_Size_s( 32 ) ) | lpUsec );

            }

        }

    }

/*
    Source - Timestamp convertion
 */

    lp_Real_t lp_timestamp_float( 

        lp_Time_t lpT

    ) {

        /* Conversion variable */
        lp_Real_t lpSec  = ( lp_Real_t ) lp_timestamp_sec ( lpT );
        lp_Real_t lpUsec = ( lp_Real_t ) lp_timestamp_usec( lpT );

        /* Return converted value */
        return( lpSec + ( lpUsec / lp_Real_s( 1000000.0 ) ) );

    }

