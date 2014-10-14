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
 * This program is lp_stream_delete software: you can redistribute it and/or modify
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

    # include "csps-imu-mod-AACEX.h"

/*
    Source - IMU absolute acceleration extraction
 */

    lp_Void_t lp_imu_mod_AACEX( 

        lp_Char_t const * const lpPath, 
        lp_IMU_t  const         lpIMU, 
        lp_Char_t const * const lpIMUmodACC, 
        lp_Char_t const * const lpIMUmodFRM

    ) {

        /* Parsing variables */
        lp_Size_t lpParse = 0;

        /* Stream size variables */
        lp_Size_t lpSize = 0;

        /* Stream memory variables */
        lp_Real_t * lpIMUacx = LP_NULL;
        lp_Real_t * lpIMUacy = LP_NULL;
        lp_Real_t * lpIMUacz = LP_NULL;
        lp_Time_t * lpIMUasn = LP_NULL;
        lp_Real_t * lpIMUfxx = LP_NULL;
        lp_Real_t * lpIMUfxy = LP_NULL;
        lp_Real_t * lpIMUfxz = LP_NULL;
        lp_Real_t * lpIMUfyx = LP_NULL;
        lp_Real_t * lpIMUfyy = LP_NULL;
        lp_Real_t * lpIMUfyz = LP_NULL;
        lp_Real_t * lpIMUfzx = LP_NULL;
        lp_Real_t * lpIMUfzy = LP_NULL;
        lp_Real_t * lpIMUfzz = LP_NULL;
        lp_Time_t * lpIMUfsn = LP_NULL;
        lp_Real_t * lpIMUaax = LP_NULL;
        lp_Real_t * lpIMUaay = LP_NULL;
        lp_Real_t * lpIMUaaz = LP_NULL;

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodACC );

        /* Read streams */
        lpIMUacx = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodACC, LP_STREAM_CPN_ACX, sizeof( lp_Real_t ) * lpSize );
        lpIMUacy = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodACC, LP_STREAM_CPN_ACY, sizeof( lp_Real_t ) * lpSize );
        lpIMUacz = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodACC, LP_STREAM_CPN_ACZ, sizeof( lp_Real_t ) * lpSize );
        lpIMUasn = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodACC, LP_STREAM_CPN_SYN, sizeof( lp_Time_t ) * lpSize );
        lpIMUfxx = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodFRM, LP_STREAM_CPN_FXX, sizeof( lp_Real_t ) * lpSize );
        lpIMUfxy = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodFRM, LP_STREAM_CPN_FXY, sizeof( lp_Real_t ) * lpSize );
        lpIMUfxz = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodFRM, LP_STREAM_CPN_FXZ, sizeof( lp_Real_t ) * lpSize );
        lpIMUfyx = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodFRM, LP_STREAM_CPN_FYX, sizeof( lp_Real_t ) * lpSize );
        lpIMUfyy = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodFRM, LP_STREAM_CPN_FYY, sizeof( lp_Real_t ) * lpSize );
        lpIMUfyz = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodFRM, LP_STREAM_CPN_FYZ, sizeof( lp_Real_t ) * lpSize );
        lpIMUfzx = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodFRM, LP_STREAM_CPN_FZX, sizeof( lp_Real_t ) * lpSize );
        lpIMUfzy = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodFRM, LP_STREAM_CPN_FZY, sizeof( lp_Real_t ) * lpSize );
        lpIMUfzz = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodFRM, LP_STREAM_CPN_FZZ, sizeof( lp_Real_t ) * lpSize );
        lpIMUfsn = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodFRM, LP_STREAM_CPN_SYN, sizeof( lp_Time_t ) * lpSize );

        /* Create streams */
        lpIMUaax = ( lp_Real_t * ) lp_stream_create( sizeof( lp_Real_t ) * lpSize );
        lpIMUaay = ( lp_Real_t * ) lp_stream_create( sizeof( lp_Real_t ) * lpSize );
        lpIMUaaz = ( lp_Real_t * ) lp_stream_create( sizeof( lp_Real_t ) * lpSize );
        lpIMUfsn = ( lp_Time_t * ) lp_stream_create( sizeof( lp_Time_t ) * lpSize );

        /* Gravity-less acceleration extraction */
        for ( lpParse = lp_Size_s( 0 ) ; lpParse < lpSize ; lpParse ++ ) {

            /* Gravity-less acceleration x-component */
            lpIMUaax[lpParse] = lpIMUacx[lpParse] * lpIMUfxx[lpParse] +
                                lpIMUacy[lpParse] * lpIMUfyx[lpParse] +
                                lpIMUacz[lpParse] * lpIMUfzx[lpParse];

            /* Gravity-less acceleration y-component */
            lpIMUaay[lpParse] = lpIMUacx[lpParse] * lpIMUfxy[lpParse] +
                                lpIMUacy[lpParse] * lpIMUfyy[lpParse] +
                                lpIMUacz[lpParse] * lpIMUfzy[lpParse];

            /* Gravity-less acceleration z-component */
            lpIMUaaz[lpParse] = lpIMUacx[lpParse] * lpIMUfxz[lpParse] +
                                lpIMUacy[lpParse] * lpIMUfyz[lpParse] +
                                lpIMUacz[lpParse] * lpIMUfzz[lpParse];

        }

        /* Write streams */
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_AACEX_MOD, LP_STREAM_CPN_ACX, lpIMUaax, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_AACEX_MOD, LP_STREAM_CPN_ACY, lpIMUaay, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_AACEX_MOD, LP_STREAM_CPN_ACZ, lpIMUaaz, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_AACEX_MOD, LP_STREAM_CPN_SYN, lpIMUasn, sizeof( lp_Time_t ) * lpSize );

        /* Unallocate streams */
        lpIMUacx = lp_stream_delete( lpIMUacx );
        lpIMUacy = lp_stream_delete( lpIMUacy );
        lpIMUacz = lp_stream_delete( lpIMUacz );
        lpIMUasn = lp_stream_delete( lpIMUasn );
        lpIMUfxx = lp_stream_delete( lpIMUfxx );
        lpIMUfxy = lp_stream_delete( lpIMUfxy );
        lpIMUfxz = lp_stream_delete( lpIMUfxz );
        lpIMUfyx = lp_stream_delete( lpIMUfyx );
        lpIMUfyy = lp_stream_delete( lpIMUfyy );
        lpIMUfyz = lp_stream_delete( lpIMUfyz );
        lpIMUfzx = lp_stream_delete( lpIMUfzx );
        lpIMUfzy = lp_stream_delete( lpIMUfzy );
        lpIMUfzz = lp_stream_delete( lpIMUfzz );
        lpIMUfsn = lp_stream_delete( lpIMUfsn );
        lpIMUaax = lp_stream_delete( lpIMUaax );
        lpIMUaay = lp_stream_delete( lpIMUaay );
        lpIMUaaz = lp_stream_delete( lpIMUaaz );

    }

