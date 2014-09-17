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

    # include "csps-imu-mod-IOBMA.h"

/*
    Source - Initial orientation body momentum alignment module
*/

    lp_Void_t lp_imu_mod_IOBMA(

        const lp_Char_t * const lpPath, 
        lp_IMU                  lpIMU,
        lp_GPS                  lpGPS,
        const lp_Char_t * const lpIMUmodGEO  

    ) {

        /* Stream size variables */
        lp_Size_t lpSize = lp_Size_s( 0 );

        /* Parsing variables */
        lp_Size_t lpParse = lp_Size_s( 0 );

        /* Amplitude detection variables */
        lp_Size_t lpIndex = lp_Size_s( 0 );
        lp_Real_t lpLocal = lp_Real_s( 0.0 );
        lp_Real_t lpLarge = lp_Real_s( 0.0 );
        lp_Real_t lpDelta = lp_Real_s( 0.0 );

        /* Differentials variables */
        lp_Real_t lpDifflon = lp_Real_s( 0.0 );
        lp_Real_t lpDifflat = lp_Real_s( 0.0 );
        lp_Real_t lpDiffnrm = lp_Real_s( 0.0 );

        /* Stream memory variables */
        lp_Real_t * lpGPSlat = LP_NULL;
        lp_Real_t * lpGPSlon = LP_NULL;
        lp_Real_t * lpGPSalt = LP_NULL;
        lp_Time_t * lpGPSsyn = LP_NULL;
        lp_Real_t * lpIMUixx = LP_NULL;
        lp_Real_t * lpIMUixy = LP_NULL;
        lp_Real_t * lpIMUixz = LP_NULL;
        lp_Real_t * lpIMUiyx = LP_NULL;
        lp_Real_t * lpIMUiyy = LP_NULL;
        lp_Real_t * lpIMUiyz = LP_NULL;
        lp_Real_t * lpIMUizx = LP_NULL;
        lp_Real_t * lpIMUizy = LP_NULL;
        lp_Real_t * lpIMUizz = LP_NULL;
        lp_Time_t * lpIMUisn = LP_NULL;

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, lpGPS.dvType, lpGPS.dvTag, lpIMUmodGEO );

        /* Read streams */
        lpGPSlat = lp_stream_read( lpPath, lpGPS.dvType, lpGPS.dvTag, lpIMUmodGEO, LP_STREAM_CPN_LAT, sizeof( lp_Real_t ) * lpSize );
        lpGPSlon = lp_stream_read( lpPath, lpGPS.dvType, lpGPS.dvTag, lpIMUmodGEO, LP_STREAM_CPN_LON, sizeof( lp_Real_t ) * lpSize );
        lpGPSalt = lp_stream_read( lpPath, lpGPS.dvType, lpGPS.dvTag, lpIMUmodGEO, LP_STREAM_CPN_ALT, sizeof( lp_Real_t ) * lpSize );
        lpGPSsyn = lp_stream_read( lpPath, lpGPS.dvType, lpGPS.dvTag, lpIMUmodGEO, LP_STREAM_CPN_SYN, sizeof( lp_Time_t ) * lpSize );

        /* Create streams */
        lpIMUixx = lp_stream_create( sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUixy = lp_stream_create( sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUixz = lp_stream_create( sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUiyx = lp_stream_create( sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUiyy = lp_stream_create( sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUiyz = lp_stream_create( sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUizx = lp_stream_create( sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUizy = lp_stream_create( sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUizz = lp_stream_create( sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUisn = lp_stream_create( sizeof( lp_Time_t ) * lp_Size_s( 2 ) );

        /* Search maximum displacement amplitude */
        for ( lpParse = lp_Size_s( 1 ); lpParse < lpSize - lp_Size_s( 1 ); lpParse ++ ) {

            /* Compute local delta-time */
            lpDelta = lp_timestamp_float( lp_timestamp_diff( lpGPSsyn[lpParse + 1], lpGPSsyn[lpParse - 1] ) );

            /* Compute local amplitude - Longitude */
            lpLocal = lp_fabs( lpGPSlon[lpParse + 1] - lpGPSlon[lpParse - 1] ) / lpDelta;

            /* Largest amplitude detection */
            if ( lpLocal > lpLarge ) {

                /* Memorize index */
                lpIndex = lpParse;
    
                /* Update largest amplitude buffer */
                lpLarge = lpLocal;

            }

            /* Compute local amplitude - Latitude */
            lpLocal = lp_fabs( lpGPSlat[lpParse + 1] - lpGPSlat[lpParse - 1] ) / lpDelta;

            /* Largest amplitude detection */
            if ( lpLocal > lpLarge ) {

                /* Memorize index */
                lpIndex = lpParse;
    
                /* Update largest amplitude buffer */
                lpLarge = lpLocal;

            }

        }

        /* Compute differential quantities */
        lpDifflon = lpGPSlon[lpIndex+1] - lpGPSlon[lpIndex-1];
        lpDifflat = lpGPSlat[lpIndex+1] - lpGPSlat[lpIndex-1];

        /* Compute differential quantities norm */
        lpDiffnrm = sqrt( lpDifflon * lpDifflon + lpDifflat * lpDifflat );

        /* Compute initial frame x-vector */
        lpIMUixx[0] = + lpDifflon / lpDiffnrm;
        lpIMUixy[0] = + lpDifflat / lpDiffnrm;
        lpIMUixz[0] = + lp_Real_s( 0.0 );

        /* Compute initial frame y-vector */
        lpIMUiyx[0] = - lpDifflat / lpDiffnrm;
        lpIMUiyy[0] = + lpDifflon / lpDiffnrm;
        lpIMUiyz[0] = + lp_Real_s( 0.0 );

        /* Compute initial frame z-vector */
        lpIMUizx[0] = + lp_Real_s( 0.0 );
        lpIMUizy[0] = + lp_Real_s( 0.0 );
        lpIMUizz[0] = + lp_Real_s( 1.0 );

        /* Assign second component */
        lpIMUixx[1] = lpIMUixx[0];
        lpIMUixy[1] = lpIMUixy[0];
        lpIMUixz[1] = lpIMUixz[0];
        lpIMUiyx[1] = lpIMUiyx[0];
        lpIMUiyy[1] = lpIMUiyy[0];
        lpIMUiyz[1] = lpIMUiyz[0];
        lpIMUizx[1] = lpIMUizx[0];
        lpIMUizy[1] = lpIMUizy[0];
        lpIMUizz[1] = lpIMUizz[0];

        /* Initial conditions timestamps */
        lpIMUisn[0] = lpGPSsyn[lpIndex];
        lpIMUisn[1] = lpGPSsyn[lpIndex];

        /* Write streams */
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IOBMA_MOD, LP_STREAM_CPN_IXX, lpIMUixx, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IOBMA_MOD, LP_STREAM_CPN_IXY, lpIMUixy, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IOBMA_MOD, LP_STREAM_CPN_IXZ, lpIMUixz, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IOBMA_MOD, LP_STREAM_CPN_IYX, lpIMUiyx, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IOBMA_MOD, LP_STREAM_CPN_IYY, lpIMUiyy, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IOBMA_MOD, LP_STREAM_CPN_IYZ, lpIMUiyz, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IOBMA_MOD, LP_STREAM_CPN_IZX, lpIMUizx, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IOBMA_MOD, LP_STREAM_CPN_IZY, lpIMUizy, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IOBMA_MOD, LP_STREAM_CPN_IZZ, lpIMUizz, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IOBMA_MOD, LP_STREAM_CPN_SYN, lpIMUisn, sizeof( lp_Time_t ) * lp_Size_s( 2 ) );

        /* Unallocate streams */
        lpGPSlat = lp_stream_delete( lpGPSlat );
        lpGPSlon = lp_stream_delete( lpGPSlon );
        lpGPSalt = lp_stream_delete( lpGPSalt );
        lpGPSsyn = lp_stream_delete( lpGPSsyn );
        lpIMUixx = lp_stream_delete( lpIMUixx );
        lpIMUixy = lp_stream_delete( lpIMUixy );
        lpIMUixz = lp_stream_delete( lpIMUixz );
        lpIMUiyx = lp_stream_delete( lpIMUiyx );
        lpIMUiyy = lp_stream_delete( lpIMUiyy );
        lpIMUiyz = lp_stream_delete( lpIMUiyz );
        lpIMUizx = lp_stream_delete( lpIMUizx );
        lpIMUizy = lp_stream_delete( lpIMUizy );
        lpIMUizz = lp_stream_delete( lpIMUizz );
        lpIMUisn = lp_stream_delete( lpIMUisn );

    }

