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

    # include "csps-imu-mod-BAIFA.h"

/*
    Source - Body attached inertial frame alignment module
*/

    lp_Void_t lp_imu_mod_BAIFA(

        const lp_Char_t * const lpPath, 
        lp_IMU                  lpIMU,
        lp_GPS                  lpGPS,
        const lp_Char_t * const lpIMUmodGEO  

    ) {

        /* Parsing variables */
        lp_Size_t lpParse = lp_Size_s( 0 );

        /* Stream size variables */
        lp_Size_t lpSize = lp_Size_s( 0 );

        /* Distance variable */
        lp_Real_t lpDist = lp_Real_s( 0.0 );

        /* Differential variables */
        lp_Real_t lpDphi = lp_Real_s( 0.0 );
        lp_Real_t lpDlam = lp_Real_s( 0.0 );
        lp_Real_t lpDnrm = lp_Real_s( 0.0 );

        /* Time variables */
        lp_Time_t lpTime1 = lp_Time_s( 0 );
        lp_Time_t lpTime2 = lp_Time_s( 0 );

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

        /* Search minimum displacement */
        while ( ( lpDist < lp_Real_s( 10.0 ) ) && ( lpParse < ( lpSize - lp_Size_s( 1 ) ) ) ) {

            /* Compute distance */
            lpDist = lp_Real_s( 2.0 ) * lp_Real_s( 63781370.0 ) * asin( sqrt(

                sin( lp_Real_s( 0.5 ) * ( LP_PI / lp_Real_s( 180.0 ) ) * ( lpGPSlat[lpParse] - lpGPSlat[0] ) ) *
                sin( lp_Real_s( 0.5 ) * ( LP_PI / lp_Real_s( 180.0 ) ) * ( lpGPSlat[lpParse] - lpGPSlat[0] ) ) +
                cos( ( LP_PI / lp_Real_s( 180.0 ) ) * lpGPSlat[0] ) *
                cos( ( LP_PI / lp_Real_s( 180.0 ) ) * lpGPSlat[lpParse] ) *
                sin( lp_Real_s( 0.5 ) * ( LP_PI / lp_Real_s( 180.0 ) ) * ( lpGPSlon[lpParse] - lpGPSlon[0] ) ) *
                sin( lp_Real_s( 0.5 ) * ( LP_PI / lp_Real_s( 180.0 ) ) * ( lpGPSlon[lpParse] - lpGPSlon[0] ) )

            ) ); 

            /* Update search index */
            lpParse ++;

        }

        /* Compute differential quantities */
        lpDphi = lpGPSlat[lpParse] - lpGPSlat[0];
        lpDlam = lpGPSlon[lpParse] - lpGPSlon[0];
        lpDnrm = sqrt( lpDphi * lpDphi + lpDlam * lpDlam );

        /* Import initialization time */
        lpTime1 = lpGPSsyn[0];
        lpTime2 = lpGPSsyn[lpParse];

        /* Unallocate streams */
        lpGPSlat = lp_stream_delete( lpGPSlat );
        lpGPSlon = lp_stream_delete( lpGPSlon );
        lpGPSalt = lp_stream_delete( lpGPSalt );
        lpGPSsyn = lp_stream_delete( lpGPSsyn );

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

        /* Compute initial frame x-vector */
        lpIMUixx[0] = + lpDlam / lpDnrm;
        lpIMUixy[0] = + lpDphi / lpDnrm;
        lpIMUixz[0] = + lp_Real_s( 0.0 );

        /* Compute initial frame y-vector */
        lpIMUiyx[0] = - lpDphi / lpDnrm;
        lpIMUiyy[0] = + lpDlam / lpDnrm;
        lpIMUiyz[0] = + lp_Real_s( 0.0 );

        /* Compute initial frame z-vector */
        lpIMUizx[0] = + lp_Real_s( 0.0 );
        lpIMUizy[0] = + lp_Real_s( 0.0 );
        lpIMUizz[0] = + lp_Real_s( 1.0 );

        /* Rotation */
        lp_Real_t a = lpIMUixx[0] * cos( 90.0 * ( LP_PI / 180.0 ) ) - lpIMUixy[0] * sin( 90.0 * ( LP_PI / 180.0 ) );
        lp_Real_t b = lpIMUixx[0] * sin( 90.0 * ( LP_PI / 180.0 ) ) + lpIMUixy[0] * cos( 90.0 * ( LP_PI / 180.0 ) );

        lpIMUixx[0] = a;
        lpIMUixy[0] = b;        

        a = lpIMUiyx[0] * cos( 90.0 * ( LP_PI / 180.0 ) ) - lpIMUiyy[0] * sin( 90.0 * ( LP_PI / 180.0 ) );
        b = lpIMUiyx[0] * sin( 90.0 * ( LP_PI / 180.0 ) ) + lpIMUiyy[0] * cos( 90.0 * ( LP_PI / 180.0 ) );

        lpIMUiyx[0] = a;
        lpIMUiyy[0] = b;

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

        /* Assign initial condition timestamps */
        lpIMUisn[0] = lpTime1;
        lpIMUisn[1] = lpTime2;

        /* Write streams */
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_BAIFA_MOD, LP_STREAM_CPN_IXX, lpIMUixx, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_BAIFA_MOD, LP_STREAM_CPN_IXY, lpIMUixy, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_BAIFA_MOD, LP_STREAM_CPN_IXZ, lpIMUixz, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_BAIFA_MOD, LP_STREAM_CPN_IYX, lpIMUiyx, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_BAIFA_MOD, LP_STREAM_CPN_IYY, lpIMUiyy, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_BAIFA_MOD, LP_STREAM_CPN_IYZ, lpIMUiyz, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_BAIFA_MOD, LP_STREAM_CPN_IZX, lpIMUizx, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_BAIFA_MOD, LP_STREAM_CPN_IZY, lpIMUizy, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_BAIFA_MOD, LP_STREAM_CPN_IZZ, lpIMUizz, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_BAIFA_MOD, LP_STREAM_CPN_SYN, lpIMUisn, sizeof( lp_Time_t ) * lp_Size_s( 2 ) );

        /* Unallocate streams */
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

