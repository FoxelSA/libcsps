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

    lp_Geopos_t lp_query_position_read(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule

    ) {

        /* Stream size variables */
        lp_Size_t lpSize = lp_stream_size( lpPath, lpTag, lpModule );

        /* Returned structure variables */
        lp_Geopos_t lpGeopos = {

            /* Setting query status */
            LP_FALSE,

            /* Initialize data fields */
            lp_Real_s( 0.0 ),
            lp_Real_s( 0.0 ),
            lp_Real_s( 0.0 ),

            /* Setting stream size */
            lpSize,

            /* Streams data importation */
            lp_stream_read( lpPath, lpTag, lpModule, LP_STREAM_CPN_LAT, sizeof( lp_Real_t ) * lpSize ),
            lp_stream_read( lpPath, lpTag, lpModule, LP_STREAM_CPN_LON, sizeof( lp_Real_t ) * lpSize ),
            lp_stream_read( lpPath, lpTag, lpModule, LP_STREAM_CPN_ALT, sizeof( lp_Real_t ) * lpSize ),
            lp_stream_read( lpPath, lpTag, lpModule, LP_STREAM_CPN_SYN, sizeof( lp_Time_t ) * lpSize )

        };

        /* Return structure */
        return( lpGeopos );

    }

    lp_Void_t lp_query_position_delete( 

        lp_Geopos_t * const lpGeopos 

    ) {

        /* Reset query status */
        lpGeopos->qrStatus = LP_FALSE;

        /* Reset data field */
        lpGeopos->qrLatitude  = lp_Real_s( 0.0 );
        lpGeopos->qrLongitude = lp_Real_s( 0.0 );
        lpGeopos->qrAltitude  = lp_Real_s( 0.0 );

        /* Reset stream size */
        lpGeopos->qrSize = lp_Size_s( 0 );

        /* Unallocate streams */
        lpGeopos->qrStrmLat = lp_stream_delete( lpGeopos->qrStrmLat );
        lpGeopos->qrStrmLon = lp_stream_delete( lpGeopos->qrStrmLon );
        lpGeopos->qrStrmAlt = lp_stream_delete( lpGeopos->qrStrmAlt );
        lpGeopos->qrStrmSyn = lp_stream_delete( lpGeopos->qrStrmSyn );

    }

/*
    Source - CSPS query - Position - Method
 */

    lp_Enum_t lp_query_position_status(

        lp_Geopos_t const * const lpGeopos

    ) {

        /* Return query structure status */
        return( lpGeopos->qrStatus );

    }

    lp_Size_t lp_query_position_size( 

        lp_Geopos_t const * const lpGeopos

    ) {

        /* Return imported streams size */
        return( lpGeopos->qrSize );

    }

/*
    Source - CSPS query - Position - Query
 */

    lp_Void_t lp_query_position(

        lp_Geopos_t       * const lpGeopos,
        lp_Time_t   const         lpTimestamp

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
        lp_Real_t lpDT1T2 = lp_Real_s( 0.0 );
        lp_Real_t lpDT0T2 = lp_Real_s( 0.0 );
        lp_Real_t lpDT1T3 = lp_Real_s( 0.0 );

        /* Obtains index of nearest lower or equal timestamp stored in synchronization array */
        if ( ( lpParse = lp_timestamp_index( lpTimestamp, lpGeopos->qrStrmSyn, lpGeopos->qrSize ) ) != LP_TIMESTAMP_FAULT ) {

            /* Cubic interpolation derivative range necessities */
            if ( ( lpParse >= lp_Size_s( 1 ) ) && ( lpParse < ( lpGeopos->qrSize - lp_Size_s( 2 ) ) ) ) {

                /* Compute quantity interpolation sampling nodes */
                lpSample0 = lpParse - 1;
                lpSample1 = lpParse;
                lpSample2 = lpParse + 1;
                lpSample3 = lpParse + 2;

                /* Compute time interpolation variable */
                lpDT1TI = lp_timestamp_float( lp_timestamp_diff( lpTimestamp, lpGeopos->qrStrmSyn[lpSample1] ) );

                /* Compute time interpolation sample */
                lpDT1T2 = lp_timestamp_float( lp_timestamp_diff( lpGeopos->qrStrmSyn[lpSample2], lpGeopos->qrStrmSyn[lpSample1] ) );
                lpDT0T2 = lp_timestamp_float( lp_timestamp_diff( lpGeopos->qrStrmSyn[lpSample2], lpGeopos->qrStrmSyn[lpSample0] ) );
                lpDT1T3 = lp_timestamp_float( lp_timestamp_diff( lpGeopos->qrStrmSyn[lpSample3], lpGeopos->qrStrmSyn[lpSample1] ) );

                /* Compute interpolation values - Latitude */
                lpGeopos->qrLatitude = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpGeopos->qrStrmLat[lpSample1], lpGeopos->qrStrmLat[lpSample2],

                    /* Standard derivatives */
                    ( lpGeopos->qrStrmLat[lpSample2] - lpGeopos->qrStrmLat[lpSample0] ) / lpDT0T2,
                    ( lpGeopos->qrStrmLat[lpSample3] - lpGeopos->qrStrmLat[lpSample1] ) / lpDT1T3

                );

                /* Compute interpolation values - Longitude */
                lpGeopos->qrLongitude = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpGeopos->qrStrmLon[lpSample1], lpGeopos->qrStrmLon[lpSample2],

                    /* Standard derivatives */
                    ( lpGeopos->qrStrmLon[lpSample2] - lpGeopos->qrStrmLon[lpSample0] ) / lpDT0T2,
                    ( lpGeopos->qrStrmLon[lpSample3] - lpGeopos->qrStrmLon[lpSample1] ) / lpDT1T3

                );

                /* Compute interpolation values - Altitude */
                lpGeopos->qrAltitude = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpGeopos->qrStrmAlt[lpSample1], lpGeopos->qrStrmAlt[lpSample2],

                    /* Standard derivatives */
                    ( lpGeopos->qrStrmAlt[lpSample2] - lpGeopos->qrStrmAlt[lpSample0] ) / lpDT0T2,
                    ( lpGeopos->qrStrmAlt[lpSample3] - lpGeopos->qrStrmAlt[lpSample1] ) / lpDT1T3

                );

                /* Update query status */
                lpGeopos->qrStatus = LP_TRUE;

            } else {

                /* Update query status */
                lpGeopos->qrStatus = LP_FALSE;

            }

        } else {

            /* Update query status */
            lpGeopos->qrStatus = LP_FALSE;

        }

    }

