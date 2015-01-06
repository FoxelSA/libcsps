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

    # include "csps-query.h"

/*
    Source - CSPS query - Synchronization
 */

    lp_Query_Timestamp_t lp_query_timestamp_by_timestamp(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpDevice,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule,        
        lp_Time_t const         lpTimestamp

    ) {

        /* Timestamp index variables */
        lp_Size_t lpParse = lp_Size_s( 0 );

        /* Stream size variables */
        lp_Size_t lpSize = lp_Size_s( 0 );

        /* Stream memory variables */
        lp_Time_t * lpSYNmas = LP_NULL;
        lp_Time_t * lpSYNsyn = LP_NULL;

        /* Returned structure */
        lp_Query_Timestamp_t lpReturn;

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, lpDevice, lpTag, lpModule );        

        /* Read streams */
        lpSYNmas = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, LP_STREAM_CPN_TAG, sizeof( lp_Time_t ) * lpSize );
        lpSYNsyn = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, LP_STREAM_CPN_SYN, sizeof( lp_Time_t ) * lpSize );

        /* Search timestamp in camera records array */
        if ( ( lpParse = lp_timestamp_index( lpTimestamp, lpSYNmas, lpSize ) ) != LP_TIMESTAMP_FAULT ) {

            /* Return corresponding master clock timestamp */
            lpReturn.qrTimestamp = lpSYNsyn[lpParse];

            /* Update query status */
            lpReturn.qrStatus = LP_TRUE;            

        } else {

            /* Update query status */
            lpReturn.qrStatus = LP_FALSE;

        }

        /* Unallocate streams */
        lpSYNmas = lp_stream_delete( lpSYNmas );
        lpSYNsyn = lp_stream_delete( lpSYNsyn );

        /* Return timestamp structure */
        return( lpReturn );

    }

/*
    Source - CSPS query - Position
 */

    lp_Query_Position_t lp_query_position_by_timestamp(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpDevice,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule,
        lp_Time_t const         lpTimestamp

    ) {

        /* Timestamp index variables */
        lp_Size_t lpParse = lp_Size_s( 0 );

        /* Files size variables */
        lp_Size_t lpSize = lp_Size_s( 0 );

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

        /* Stream memory variables */
        lp_Real_t * lpGENlat = LP_NULL;
        lp_Real_t * lpGENlon = LP_NULL;
        lp_Real_t * lpGENalt = LP_NULL;
        lp_Time_t * lpGENsyn = LP_NULL;

        /* Returned structure */
        lp_Query_Position_t lpPosition;

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, lpDevice, lpTag, lpModule );

        /* Read streams */
        lpGENlat = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "lat", sizeof( lp_Real_t ) * lpSize );
        lpGENlon = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "lon", sizeof( lp_Real_t ) * lpSize );
        lpGENalt = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "alt", sizeof( lp_Real_t ) * lpSize );
        lpGENsyn = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "syn", sizeof( lp_Time_t ) * lpSize );

        /* Obtains index of nearest lower or equal timestamp stored in synchronization array */
        if ( ( lpParse = lp_timestamp_index( lpTimestamp, lpGENsyn, lpSize ) ) != LP_TIMESTAMP_FAULT ) {

            /* Compute quantity interpolation sampling nodes */
            lpSample0 = LP_RNG( lpParse - 1, 0, lpSize - lp_Size_s( 1 ) );
            lpSample1 = LP_RNG( lpParse    , 0, lpSize - lp_Size_s( 1 ) );
            lpSample2 = LP_RNG( lpParse + 1, 0, lpSize - lp_Size_s( 1 ) );
            lpSample3 = LP_RNG( lpParse + 2, 0, lpSize - lp_Size_s( 1 ) );

            /* Compute time interpolation variable */
            lpDT1TI = lp_timestamp_float( lp_timestamp_diff( lpTimestamp, lpGENsyn[lpSample1] ) );

            /* Compute time interpolation sample */
            lpDT1T2 = lp_timestamp_float( lp_timestamp_diff( lpGENsyn[lpSample2], lpGENsyn[lpSample1] ) );
            lpDT0T2 = lp_timestamp_float( lp_timestamp_diff( lpGENsyn[lpSample2], lpGENsyn[lpSample0] ) );
            lpDT1T3 = lp_timestamp_float( lp_timestamp_diff( lpGENsyn[lpSample3], lpGENsyn[lpSample1] ) );

            /* Compute interpolation values - Latitude */
            lpPosition.qrLatitude = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpGENlat[lpSample1], lpGENlat[lpSample2],

                /* Standard derivatives */
                ( lpGENlat[lpSample2] - lpGENlat[lpSample0] ) / lpDT0T2,
                ( lpGENlat[lpSample3] - lpGENlat[lpSample1] ) / lpDT1T3

            );

            /* Compute interpolation values - Longitude */
            lpPosition.qrLongitude = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpGENlon[lpSample1], lpGENlon[lpSample2],

                /* Standard derivatives */
                ( lpGENlon[lpSample2] - lpGENlon[lpSample0] ) / lpDT0T2,
                ( lpGENlon[lpSample3] - lpGENlon[lpSample1] ) / lpDT1T3

            );

            /* Compute interpolation values - Altitude */
            lpPosition.qrAltitude = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpGENalt[lpSample1], lpGENalt[lpSample2],

                /* Standard derivatives */
                ( lpGENalt[lpSample2] - lpGENalt[lpSample0] ) / lpDT0T2,
                ( lpGENalt[lpSample3] - lpGENalt[lpSample1] ) / lpDT1T3

            );

            /* Update query status */
            lpPosition.qrStatus = LP_TRUE;

        } else {

            /* Update query status */
            lpPosition.qrStatus = LP_FALSE;

        }

        /* Unallocate streams */
        lpGENlat = lp_stream_delete( lpGENlat );
        lpGENlon = lp_stream_delete( lpGENlon );
        lpGENalt = lp_stream_delete( lpGENalt );
        lpGENsyn = lp_stream_delete( lpGENsyn );

        /* Return position structure */
        return( lpPosition );

    }

/*
    Source - CSPS query - Orientation
 */

    lp_Query_Orientation_t lp_query_orientation_by_timestamp(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpDevice,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule,
        lp_Time_t const         lpTimestamp

    ) {

        /* Timestamp index variables */
        lp_Size_t lpParse = lp_Size_s( 0 );

        /* Files size variables */
        lp_Size_t lpSize = lp_Size_s( 0 );

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

        /* Data buffers */
        lp_Real_t * lpGENfxx = LP_NULL;
        lp_Real_t * lpGENfxy = LP_NULL;
        lp_Real_t * lpGENfxz = LP_NULL;
        lp_Real_t * lpGENfyx = LP_NULL;
        lp_Real_t * lpGENfyy = LP_NULL;
        lp_Real_t * lpGENfyz = LP_NULL;
        lp_Real_t * lpGENfzx = LP_NULL;
        lp_Real_t * lpGENfzy = LP_NULL;
        lp_Real_t * lpGENfzz = LP_NULL;
        lp_Time_t * lpGENsyn = LP_NULL;

        /* Returned structure */
        lp_Query_Orientation_t lpOrientation;

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, lpDevice, lpTag, lpModule );

        /* Read streams */
        lpGENfxx = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "fxx", sizeof( lp_Real_t ) * lpSize );
        lpGENfxy = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "fxy", sizeof( lp_Real_t ) * lpSize );
        lpGENfxz = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "fxz", sizeof( lp_Real_t ) * lpSize );
        lpGENfyx = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "fyx", sizeof( lp_Real_t ) * lpSize );
        lpGENfyy = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "fyy", sizeof( lp_Real_t ) * lpSize );
        lpGENfyz = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "fyz", sizeof( lp_Real_t ) * lpSize );
        lpGENfzx = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "fzx", sizeof( lp_Real_t ) * lpSize );
        lpGENfzy = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "fzy", sizeof( lp_Real_t ) * lpSize );
        lpGENfzz = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "fzz", sizeof( lp_Real_t ) * lpSize );
        lpGENsyn = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "syn", sizeof( lp_Time_t ) * lpSize );

        /* Obtains index of nearest lower or equal timestamp stored in synchronization array */
        if ( ( lpParse = lp_timestamp_index( lpTimestamp, lpGENsyn, lpSize ) ) != LP_TIMESTAMP_FAULT ) {

            /* Compute quantity interpolation sampling nodes */
            lpSample0 = LP_RNG( lpParse - 1, 0, lpSize - lp_Size_s( 1 ) );
            lpSample1 = LP_RNG( lpParse    , 0, lpSize - lp_Size_s( 1 ) );
            lpSample2 = LP_RNG( lpParse + 1, 0, lpSize - lp_Size_s( 1 ) );
            lpSample3 = LP_RNG( lpParse + 2, 0, lpSize - lp_Size_s( 1 ) );

            /* Compute time interpolation variable */
            lpDT1TI = lp_timestamp_float( lp_timestamp_diff( lpTimestamp, lpGENsyn[lpSample1] ) );

            /* Compute time interpolation sample */
            lpDT1T2 = lp_timestamp_float( lp_timestamp_diff( lpGENsyn[lpSample2], lpGENsyn[lpSample1] ) );
            lpDT0T2 = lp_timestamp_float( lp_timestamp_diff( lpGENsyn[lpSample2], lpGENsyn[lpSample0] ) );
            lpDT1T3 = lp_timestamp_float( lp_timestamp_diff( lpGENsyn[lpSample3], lpGENsyn[lpSample1] ) );

            /* Compute interpolation values - Frame x-component x-vector */
            lpOrientation.qrfxx = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpGENfxx[lpSample1], lpGENfxx[lpSample2],

                /* Standard derivatives */
                ( lpGENfxx[lpSample2] - lpGENfxx[lpSample0] ) / lpDT0T2,
                ( lpGENfxx[lpSample3] - lpGENfxx[lpSample1] ) / lpDT1T3

            );

            /* Compute interpolation values - Frame y-component x-vector */
            lpOrientation.qrfxy = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpGENfxy[lpSample1], lpGENfxy[lpSample2],

                /* Standard derivatives */
                ( lpGENfxy[lpSample2] - lpGENfxy[lpSample0] ) / lpDT0T2,
                ( lpGENfxy[lpSample3] - lpGENfxy[lpSample1] ) / lpDT1T3

            );

            /* Compute interpolation values - Frame z-component x-vector */
            lpOrientation.qrfxz = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpGENfxz[lpSample1], lpGENfxz[lpSample2],

                /* Standard derivatives */
                ( lpGENfxz[lpSample2] - lpGENfxz[lpSample0] ) / lpDT0T2,
                ( lpGENfxz[lpSample3] - lpGENfxz[lpSample1] ) / lpDT1T3

            );

            /* Compute interpolation values - Frame x-component y-vector */
            lpOrientation.qrfyx = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpGENfyx[lpSample1], lpGENfyx[lpSample2],

                /* Standard derivatives */
                ( lpGENfyx[lpSample2] - lpGENfyx[lpSample0] ) / lpDT0T2,
                ( lpGENfyx[lpSample3] - lpGENfyx[lpSample1] ) / lpDT1T3

            );

            /* Compute interpolation values - Frame y-component y-vector */
            lpOrientation.qrfyy = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpGENfyy[lpSample1], lpGENfyy[lpSample2],

                /* Standard derivatives */
                ( lpGENfyy[lpSample2] - lpGENfyy[lpSample0] ) / lpDT0T2,
                ( lpGENfyy[lpSample3] - lpGENfyy[lpSample1] ) / lpDT1T3

            );

            /* Compute interpolation values - Frame z-component y-vector */
            lpOrientation.qrfyz = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpGENfyz[lpSample1], lpGENfyz[lpSample2],

                /* Standard derivatives */
                ( lpGENfyz[lpSample2] - lpGENfyz[lpSample0] ) / lpDT0T2,
                ( lpGENfyz[lpSample3] - lpGENfyz[lpSample1] ) / lpDT1T3

            );

            /* Compute interpolation values - Frame x-component z-vector */
            lpOrientation.qrfzx = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpGENfzx[lpSample1], lpGENfzx[lpSample2],

                /* Standard derivatives */
                ( lpGENfzx[lpSample2] - lpGENfzx[lpSample0] ) / lpDT0T2,
                ( lpGENfzx[lpSample3] - lpGENfzx[lpSample1] ) / lpDT1T3

            );

            /* Compute interpolation values - Frame y-component z-vector */
            lpOrientation.qrfzy = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpGENfzy[lpSample1], lpGENfzy[lpSample2],

                /* Standard derivatives */
                ( lpGENfzy[lpSample2] - lpGENfzy[lpSample0] ) / lpDT0T2,
                ( lpGENfzy[lpSample3] - lpGENfzy[lpSample1] ) / lpDT1T3

            );

            /* Compute interpolation values - Frame z-component z-vector */
            lpOrientation.qrfzz = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpGENfzz[lpSample1], lpGENfzz[lpSample2],

                /* Standard derivatives */
                ( lpGENfzz[lpSample2] - lpGENfzz[lpSample0] ) / lpDT0T2,
                ( lpGENfzz[lpSample3] - lpGENfzz[lpSample1] ) / lpDT1T3

            );

            /* Update query status */
            lpOrientation.qrStatus = LP_TRUE;

        } else {

            /* Update query status */
            lpOrientation.qrStatus = LP_FALSE;

        }

        /* Unallocate streams */
        lpGENfxx = lp_stream_delete( lpGENfxx );
        lpGENfxy = lp_stream_delete( lpGENfxy );
        lpGENfxz = lp_stream_delete( lpGENfxz );
        lpGENfyx = lp_stream_delete( lpGENfyx );
        lpGENfyy = lp_stream_delete( lpGENfyy );
        lpGENfyz = lp_stream_delete( lpGENfyz );
        lpGENfzx = lp_stream_delete( lpGENfzx );
        lpGENfzy = lp_stream_delete( lpGENfzy );
        lpGENfzz = lp_stream_delete( lpGENfzz );
        lpGENsyn = lp_stream_delete( lpGENsyn );

        /* Return position structure */
        return( lpOrientation );

    }

