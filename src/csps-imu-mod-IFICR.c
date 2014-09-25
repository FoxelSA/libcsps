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

    # include "csps-imu-mod-IFICR.h"

/*
    Source - Inertial frame initial conditions rotation
*/

    lp_Void_t lp_imu_mod_IFICR(

        const lp_Char_t * const lpPath, 
        lp_IMU                  lpIMU,
        const lp_Char_t * const lpIMUmod

    ) {

        /* Stream memory variables */
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

        /* Read streams */
        lpIMUixx = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod, LP_STREAM_CPN_IXX, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUixy = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod, LP_STREAM_CPN_IXY, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUixz = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod, LP_STREAM_CPN_IXZ, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUiyx = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod, LP_STREAM_CPN_IYX, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUiyy = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod, LP_STREAM_CPN_IYY, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUiyz = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod, LP_STREAM_CPN_IYZ, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUizx = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod, LP_STREAM_CPN_IZX, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUizy = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod, LP_STREAM_CPN_IZY, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUizz = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod, LP_STREAM_CPN_IZZ, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUisn = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod, LP_STREAM_CPN_SYN, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );

        /* Compute rotation around z-axis */
        lp_rotation_zR3( lpIMU.dvICRz, lpIMUixx, lpIMUixy, lpIMUixz );
        lp_rotation_zR3( lpIMU.dvICRz, lpIMUiyx, lpIMUiyy, lpIMUiyz );
        lp_rotation_zR3( lpIMU.dvICRz, lpIMUizx, lpIMUizy, lpIMUizz );

        /* Compute rotation around y-axis */
        lp_rotation_yR3( lpIMU.dvICRy, lpIMUixx, lpIMUixy, lpIMUixz );
        lp_rotation_yR3( lpIMU.dvICRy, lpIMUiyx, lpIMUiyy, lpIMUiyz );
        lp_rotation_yR3( lpIMU.dvICRy, lpIMUizx, lpIMUizy, lpIMUizz );

        /* Compute rotation around x-axis */
        lp_rotation_xR3( lpIMU.dvICRx, lpIMUixx, lpIMUixy, lpIMUixz );
        lp_rotation_xR3( lpIMU.dvICRx, lpIMUiyx, lpIMUiyy, lpIMUiyz );
        lp_rotation_xR3( lpIMU.dvICRx, lpIMUizx, lpIMUizy, lpIMUizz );

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
        
        /* Write streams */
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IFICR_MOD, LP_STREAM_CPN_IXX, lpIMUixx, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IFICR_MOD, LP_STREAM_CPN_IXY, lpIMUixy, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IFICR_MOD, LP_STREAM_CPN_IXZ, lpIMUixz, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IFICR_MOD, LP_STREAM_CPN_IYX, lpIMUiyx, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IFICR_MOD, LP_STREAM_CPN_IYY, lpIMUiyy, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IFICR_MOD, LP_STREAM_CPN_IYZ, lpIMUiyz, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IFICR_MOD, LP_STREAM_CPN_IZX, lpIMUizx, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IFICR_MOD, LP_STREAM_CPN_IZY, lpIMUizy, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IFICR_MOD, LP_STREAM_CPN_IZZ, lpIMUizz, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IFICR_MOD, LP_STREAM_CPN_SYN, lpIMUisn, sizeof( lp_Time_t ) * lp_Size_s( 2 ) );

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

