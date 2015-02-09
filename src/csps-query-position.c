/*
 * libcsps - Crossed-signal positioning system library
 *
 * Copyright (c) 2013-2015 FOXEL SA - http://foxel.ch
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

    # include "csps-query-position.h"

/*
    Source - CSPS query - Position - Handle
 */

    lp_Position_t lp_query_position_create(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule

    ) {

        /* Returned structure variables */
        lp_Position_t lpPosition;

        /* Initialize structure status */
        lpPosition.qrState  = LP_FALSE;
        lpPosition.qrStatus = LP_FALSE;    

        /* Initialize query fields */
        lpPosition.qrLatitude  = LP_FALSE;
        lpPosition.qrLongitude = LP_FALSE;
        lpPosition.qrAltitude  = LP_FALSE;

        /* Initialize query complements */
        lpPosition.qrWeak = lp_Enum_s( 0 );

        /* Retrieve stream size */
        lpPosition.qrSize = lp_stream_size( lpPath, lpTag, lpModule );

        /* Streams component importation */
        lpPosition.qrStrmLat = lp_stream_read( lpPath, lpTag, lpModule, LP_STREAM_CPN_LAT, sizeof( lp_Real_t ) * lpPosition.qrSize );
        lpPosition.qrStrmLon = lp_stream_read( lpPath, lpTag, lpModule, LP_STREAM_CPN_LON, sizeof( lp_Real_t ) * lpPosition.qrSize );
        lpPosition.qrStrmAlt = lp_stream_read( lpPath, lpTag, lpModule, LP_STREAM_CPN_ALT, sizeof( lp_Real_t ) * lpPosition.qrSize );
        lpPosition.qrStrmSyn = lp_stream_read( lpPath, lpTag, lpModule, LP_STREAM_CPN_SYN, sizeof( lp_Time_t ) * lpPosition.qrSize );

        /* Verify structure state */
        if ( ( lpPosition.qrStrmLat == NULL ) || ( lpPosition.qrStrmLon == NULL ) || ( lpPosition.qrStrmAlt == NULL ) || ( lpPosition.qrStrmSyn == NULL ) ) {

            /* Delete structure */
            lp_query_position_delete( & lpPosition );

        } else {

            /* Update structure state */
            lpPosition.qrState = LP_TRUE;

        }

        /* Return structure */
        return( lpPosition );

    }

    lp_Void_t lp_query_position_delete( 

        lp_Position_t * const lpPosition 

    ) {

        /* Reset structure status */
        lpPosition->qrState  = LP_FALSE;
        lpPosition->qrStatus = LP_FALSE;

        /* Reset stream size */
        lpPosition->qrSize = lp_Size_s( 0 );

        /* Unallocate stream components */
        lpPosition->qrStrmLat = lp_stream_delete( lpPosition->qrStrmLat );
        lpPosition->qrStrmLon = lp_stream_delete( lpPosition->qrStrmLon );
        lpPosition->qrStrmAlt = lp_stream_delete( lpPosition->qrStrmAlt );
        lpPosition->qrStrmSyn = lp_stream_delete( lpPosition->qrStrmSyn );

    }

/*
    Source - CSPS query - Position - Method
 */

    lp_Enum_t lp_query_position_state(

        lp_Position_t const * const lpPosition

    ) {

        /* Return query structure status */
        return( lpPosition->qrState );

    }

    lp_Enum_t lp_query_position_status(

        lp_Position_t const * const lpPosition

    ) {

        /* Return query structure status */
        return( lpPosition->qrStatus );

    }

    lp_Size_t lp_query_position_size( 

        lp_Position_t const * const lpPosition

    ) {

        /* Return imported streams size */
        return( lpPosition->qrSize );

    }

/*
    Source - CSPS query - Position - Query
 */

    lp_Void_t lp_query_position(

        lp_Position_t       * const lpPosition,
        lp_Time_t   const         lpTime

    ) {

        /* Timestamp index variables */
        lp_Size_t lpParse = lp_Size_s( 0 );

        /* Interpolation sampling nodes variables */
        lp_Size_t lpSample0 = lp_Size_s( 0 );
        lp_Size_t lpSample1 = lp_Size_s( 0 );
        lp_Size_t lpSample2 = lp_Size_s( 0 );
        lp_Size_t lpSample3 = lp_Size_s( 0 );

        /* Interpolation time variables */
        lp_Real_t lpDT1TI = lp_Real_s( 0.0 );
        lp_Real_t lpDTIT2 = lp_Real_s( 0.0 );
        lp_Real_t lpDT1T2 = lp_Real_s( 0.0 );
        lp_Real_t lpDT0T2 = lp_Real_s( 0.0 );
        lp_Real_t lpDT1T3 = lp_Real_s( 0.0 );

        /* Check query structure state */
        if ( lpPosition->qrState == LP_TRUE ) {

            /* Obtains index of nearest lower or equal timestamp stored in synchronization array */
            if ( ( lpParse = lp_timestamp_index( lpTime, lpPosition->qrStrmSyn, lpPosition->qrSize ) ) != LP_TIMESTAMP_FAULT ) {

                /* Cubic interpolation derivative range necessities */
                if ( ( lpParse >= lp_Size_s( 1 ) ) && ( lpParse < ( lpPosition->qrSize - lp_Size_s( 2 ) ) ) ) {

                    /* Compute quantity interpolation sampling nodes */
                    lpSample0 = lpParse - 1;
                    lpSample1 = lpParse;
                    lpSample2 = lpParse + 1;
                    lpSample3 = lpParse + 2;

                    /* Compute time interpolation variable */
                    lpDT1TI = lp_timestamp_float( lp_timestamp_diff( lpTime, lpPosition->qrStrmSyn[lpSample1] ) );
                    lpDTIT2 = lp_timestamp_float( lp_timestamp_diff( lpTime, lpPosition->qrStrmSyn[lpSample2] ) );

                    /* Compute time interpolation sample */
                    lpDT1T2 = lp_timestamp_float( lp_timestamp_diff( lpPosition->qrStrmSyn[lpSample2], lpPosition->qrStrmSyn[lpSample1] ) );
                    lpDT0T2 = lp_timestamp_float( lp_timestamp_diff( lpPosition->qrStrmSyn[lpSample2], lpPosition->qrStrmSyn[lpSample0] ) );
                    lpDT1T3 = lp_timestamp_float( lp_timestamp_diff( lpPosition->qrStrmSyn[lpSample3], lpPosition->qrStrmSyn[lpSample1] ) );

                    /* Compute interpolation values - Latitude */
                    lpPosition->qrLatitude = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpPosition->qrStrmLat[lpSample1], lpPosition->qrStrmLat[lpSample2],

                        /* Standard derivatives */
                        ( lpPosition->qrStrmLat[lpSample2] - lpPosition->qrStrmLat[lpSample0] ) / lpDT0T2,
                        ( lpPosition->qrStrmLat[lpSample3] - lpPosition->qrStrmLat[lpSample1] ) / lpDT1T3

                    );

                    /* Compute interpolation values - Longitude */
                    lpPosition->qrLongitude = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpPosition->qrStrmLon[lpSample1], lpPosition->qrStrmLon[lpSample2],

                        /* Standard derivatives */
                        ( lpPosition->qrStrmLon[lpSample2] - lpPosition->qrStrmLon[lpSample0] ) / lpDT0T2,
                        ( lpPosition->qrStrmLon[lpSample3] - lpPosition->qrStrmLon[lpSample1] ) / lpDT1T3

                    );

                    /* Compute interpolation values - Altitude */
                    lpPosition->qrAltitude = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpPosition->qrStrmAlt[lpSample1], lpPosition->qrStrmAlt[lpSample2],

                        /* Standard derivatives */
                        ( lpPosition->qrStrmAlt[lpSample2] - lpPosition->qrStrmAlt[lpSample0] ) / lpDT0T2,
                        ( lpPosition->qrStrmAlt[lpSample3] - lpPosition->qrStrmAlt[lpSample1] ) / lpDT1T3

                    );

                    /* Weak reliability detection */
                    if ( ( lpDT1TI > lp_Real_s( 2.0 ) ) || ( lpDTIT2 > lp_Real_s( 2.0 ) ) ) {

                        /* Update reliability flag */
                        lpPosition->qrWeak = LP_TRUE;

                    } else {

                        /* Update reliability flag */
                        lpPosition->qrWeak = LP_FALSE;

                    }

                    /* Update query status */
                    lpPosition->qrStatus = LP_TRUE;

                } else {

                    /* Update query status */
                    lpPosition->qrStatus = LP_FALSE;

                }

            } else {

                /* Update query status */
                lpPosition->qrStatus = LP_FALSE;

            }

        } else {

            /* Update query status */
            lpPosition->qrStatus = LP_FALSE;

        }

    }

