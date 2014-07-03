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

    csps_Time_t csps_timestamp( const csps_Void_t * const cspsRec ) {

        /* Return filtered timestamp value - 32HSb for unix time and 20LSb for microseconds */
        return( csps_Time_s( 0xFFFFFFFF000FFFFF ) & ( * ( ( uint64_t * ) cspsRec ) ) );

    }


/*
    Source - FPGA timestamp composer
 */

    csps_Time_t csps_timestamp_compose( csps_Time_t cspsSec, csps_Time_t cspsUsec ) {

        /* Return composed timestamp */
        return( ( cspsSec << csps_Size_s( 32 ) ) | cspsUsec );

    }

/*
    Source - FPGA timestamp decomposer
 */

    csps_Time_t csps_timestamp_sec( csps_Time_t cspsT ) {

        /* Return time stamp seconds */
        return( cspsT >> csps_Size_s( 32 ) );

    }

    csps_Time_t csps_timestamp_usec( csps_Time_t cspsT ) {

        /* Return time stamp microseconds */
        return( cspsT & csps_Time_s( 0x00000000000FFFFF ) );

    }

/*
    Source - FPGA timestamp comparators
 */

    csps_Enum_t csps_timestamp_eq( csps_Time_t cspsTa, csps_Time_t cspsTb ) {

        /* Verify timestamp equality */
        if ( cspsTa == cspsTb ) {

            /* Return boolean result */
            return( CSPS_TRUE );

        } else {

            /* Return boolean result */
            return( CSPS_FALSE );

        }

    }

    csps_Enum_t csps_timestamp_ge( csps_Time_t cspsTa, csps_Time_t cspsTb ) {

        /* Timestamp decomposition */
        csps_Time_t cspsSeca  = csps_timestamp_sec ( cspsTa );
        csps_Time_t cspsUseca = csps_timestamp_usec( cspsTa );
        csps_Time_t cspsSecb  = csps_timestamp_sec ( cspsTb );
        csps_Time_t cspsUsecb = csps_timestamp_usec( cspsTb );

        /* Verify unix time */
        if ( cspsSeca > cspsSecb ) {

            /* Return boolean result */
            return( CSPS_TRUE );

        } else {

            /* Verify unix time */
            if ( cspsSeca == cspsSecb ) {

                /* Verify microseconds time */
                if ( cspsUseca >= cspsUsecb ) {

                    /* Return boolean result */
                    return( CSPS_TRUE );

                } else  {

                    /* Return boolean result */
                    return( CSPS_FALSE );

                }

            } else {

                /* Return boolean result */
                return( CSPS_FALSE );

            }

        }

    }

/*
    Source - FPGA timestamp arithmetic
 */

    csps_Time_t csps_timestamp_add( const csps_Time_t cspsTa, const csps_Time_t cspsTb ) {

        /* Compute addition by parts */
        csps_Time_t cspsSec  = csps_timestamp_sec ( cspsTa ) + csps_timestamp_sec ( cspsTb );
        csps_Time_t cspsUsec = csps_timestamp_usec( cspsTa ) + csps_timestamp_usec( cspsTb );

        /* Return addition of timestamps */
        return( csps_timestamp_compose( cspsSec + ( cspsUsec > csps_Time_s( 1000000 ) ? csps_Time_s( 1 ) : csps_Time_s( 0 ) ), cspsUsec % csps_Time_s( 1000000 ) ) );

    }

    csps_Time_t csps_timestamp_diff( csps_Time_t cspsTa, csps_Time_t cspsTb ) {

        /* Difference variable */
        csps_Diff_t cspsUsec = 0;

        /* Verify timestamp equality */
        if ( csps_timestamp_eq( cspsTa, cspsTb ) == CSPS_TRUE ) {

            /* Return difference */
            return( 0 );

        } else {

            /* Verify highest timestamp */
            if ( csps_timestamp_ge( cspsTb, cspsTa ) == CSPS_TRUE ) { uint64_t cspsSwap = cspsTa; cspsTa = cspsTb; cspsTb = cspsSwap; }

            /* Compute microseconde difference */
            cspsUsec = csps_timestamp_usec( cspsTa ) - csps_timestamp_usec( cspsTb );

            /* Verify microseconde sign */
            if ( cspsUsec < 0 ) {

                /* Return difference */
                return( ( ( csps_timestamp_sec( cspsTa ) - csps_timestamp_sec( cspsTb ) - 1 ) << csps_Size_s( 32 ) ) | ( cspsUsec + csps_Diff_s( 1000000 ) ) );

            } else {

                /* Return difference */
                return( ( ( csps_timestamp_sec( cspsTa ) - csps_timestamp_sec( cspsTb ) ) << csps_Size_s( 32 ) ) | cspsUsec );

            }

        }

    }

/*
    Source - FPGA timestamp converter
 */

    csps_Real_t csps_timestamp_float( csps_Time_t cspsT ) {

        /* Conversion variable */
        csps_Real_t cspsSec  = ( csps_Real_t ) csps_timestamp_sec ( cspsT );
        csps_Real_t cspsUsec = ( csps_Real_t ) csps_timestamp_usec( cspsT );

        /* Return converted value */
        return( cspsSec + ( cspsUsec / csps_Real_s( 1000000.0 ) ) );

    }

/*
    Source - UTC to localtime converter
 */

    csps_Time_t csps_timestamp_local( const csps_Char_t * const cspsZone, csps_Time_t cspsUTC ) {

        /* Select zone */
        if ( strcmp( cspsZone, CSPS_TIMESTAMP_ZONE_WET ) == 0 ) {

            /* Return local timestamp */
            return( cspsUTC );

        } else if ( strcmp( cspsZone, CSPS_TIMESTAMP_ZONE_WEST ) == 0 ) {

            /* Return local timestamp */
            return( csps_timestamp_compose( csps_timestamp_sec( cspsUTC ) + csps_Time_s( 3600 * 1 ), csps_timestamp_usec( cspsUTC ) ) );

        } else if ( strcmp( cspsZone, CSPS_TIMESTAMP_ZONE_CET ) == 0 ) {

            /* Return local timestamp */
            return( csps_timestamp_compose( csps_timestamp_sec( cspsUTC ) + csps_Time_s( 3600 * 1 ), csps_timestamp_usec( cspsUTC ) ) );

        } else if ( strcmp( cspsZone, CSPS_TIMESTAMP_ZONE_CEST ) == 0 ) {

            /* Return local timestamp */
            return( csps_timestamp_compose( csps_timestamp_sec( cspsUTC ) + csps_Time_s( 3600 * 2 ), csps_timestamp_usec( cspsUTC ) ) );

        } else if ( strcmp( cspsZone, CSPS_TIMESTAMP_ZONE_EET ) == 0 ) {

            /* Return local timestamp */
            return( csps_timestamp_compose( csps_timestamp_sec( cspsUTC ) + csps_Time_s( 3600 * 2 ), csps_timestamp_usec( cspsUTC ) ) );

        } else if ( strcmp( cspsZone, CSPS_TIMESTAMP_ZONE_EEST ) == 0 ) {

            /* Return local timestamp */
            return( csps_timestamp_compose( csps_timestamp_sec( cspsUTC ) + csps_Time_s( 3600 * 3 ), csps_timestamp_usec( cspsUTC ) ) );


        } else {

            /* Return original timestamp */
            return( cspsUTC );

        }

    }

