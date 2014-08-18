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

    # include "csps-imu-mod-IFETI.h"

/*
    Source - IMU frame explicit time-integration module
 */

    lp_IMU lp_imu_mod_IFETI( const lp_Char_t * const lpPath, lp_IMU lpDevice, const lp_Char_t * const lpPSgr ) {

        /* Integration variables */
        lp_Real_t lpDelta = lp_Real_s( 0.0 );
        lp_Size_t lpParse = lp_Size_s( 0 );

        /* Files size */
        lp_Size_t lpSize = lp_Size_s( 0 );

        /* Data buffers */
        lp_Real_t * lpDEVgrx = NULL;
        lp_Real_t * lpDEVgry = NULL;
        lp_Real_t * lpDEVgrz = NULL;
        lp_Real_t * lpDEVfxx = NULL;
        lp_Real_t * lpDEVfxy = NULL;
        lp_Real_t * lpDEVfxz = NULL;
        lp_Real_t * lpDEVfyx = NULL;
        lp_Real_t * lpDEVfyy = NULL;
        lp_Real_t * lpDEVfyz = NULL;
        lp_Real_t * lpDEVfzx = NULL;
        lp_Real_t * lpDEVfzy = NULL;
        lp_Real_t * lpDEVfzz = NULL;
        lp_Time_t * lpDEVsyn = NULL;

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, lpPSgr, "syn" ) / sizeof( uint64_t );

        /* Read streams data */
        lpDEVgrx = lp_stream_read( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, lpPSgr, "grx", sizeof( lp_Real_t ) * lpSize );
        lpDEVgry = lp_stream_read( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, lpPSgr, "gry", sizeof( lp_Real_t ) * lpSize );
        lpDEVgrz = lp_stream_read( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, lpPSgr, "grz", sizeof( lp_Real_t ) * lpSize );
        lpDEVsyn = lp_stream_read( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, lpPSgr, "syn", sizeof( lp_Time_t ) * lpSize );

        /* Allocate stream memory */
        lpDEVfxx = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpSize );
        lpDEVfxy = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpSize );
        lpDEVfxz = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpSize );
        lpDEVfyx = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpSize );
        lpDEVfyy = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpSize );
        lpDEVfyz = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpSize );
        lpDEVfzx = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpSize );
        lpDEVfzy = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpSize );
        lpDEVfzz = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpSize );

        /* Setting initial conditions */
        for ( lpParse = lp_Size_s( 0 ) ; lpParse < LP_IMU_FRAME_BOUND ; lpParse ++ ) {

            /* Assign initial condition on IMU frame */
            lpDEVfxx[lpParse] = lpDevice.dvfxx;
            lpDEVfxy[lpParse] = lpDevice.dvfxy;
            lpDEVfxz[lpParse] = lpDevice.dvfxz;
            lpDEVfyx[lpParse] = lpDevice.dvfyx;
            lpDEVfyy[lpParse] = lpDevice.dvfyy;
            lpDEVfyz[lpParse] = lpDevice.dvfyz;
            lpDEVfzx[lpParse] = lpDevice.dvfzx;
            lpDEVfzy[lpParse] = lpDevice.dvfzy;
            lpDEVfzz[lpParse] = lpDevice.dvfzz;

        }

        /* Compute time step value */
        lpDelta = lp_Real_s( 1.0 ) / ( ( lp_Real_t ) lpDevice.dvdfreq );

        /* Frame integration procedure */
        for ( lpParse = LP_IMU_FRAME_BOUND ; lpParse < lpSize ; lpParse ++ ) {

            /* Integration - Advance frame x-vector x-component */
            lpDEVfxx[lpParse] = ( lp_Real_s( 20.0 ) / lp_Real_s( 49.0 ) ) * (
                                  + ( lpDelta                                 ) * lpDEVfxz[lpParse-1] * lpDEVgry[lpParse-1]
                                  - ( lpDelta                                 ) * lpDEVfxy[lpParse-1] * lpDEVgrz[lpParse-1]
                                  + ( lp_Real_s(  6.0 )                       ) * lpDEVfxx[lpParse-1]
                                  - ( lp_Real_s( 15.0 ) / lp_Real_s(  2.0 ) ) * lpDEVfxx[lpParse-2]
                                  + ( lp_Real_s( 20.0 ) / lp_Real_s(  3.0 ) ) * lpDEVfxx[lpParse-3]
                                  - ( lp_Real_s( 15.0 ) / lp_Real_s(  4.0 ) ) * lpDEVfxx[lpParse-4]
                                  + ( lp_Real_s(  6.0 ) / lp_Real_s(  5.0 ) ) * lpDEVfxx[lpParse-5]
                                  - ( lp_Real_s(  1.0 ) / lp_Real_s(  6.0 ) ) * lpDEVfxx[lpParse-6]
                                  );

            /* Integration - Advance frame x-vector y-component */
            lpDEVfxy[lpParse] = ( lp_Real_s( 20.0 ) / lp_Real_s( 49.0 ) ) * (
                                  + ( lpDelta                                 ) * lpDEVfxx[lpParse-1] * lpDEVgrz[lpParse-1]
                                  - ( lpDelta                                 ) * lpDEVfxz[lpParse-1] * lpDEVgrx[lpParse-1]
                                  + ( lp_Real_s(  6.0 )                       ) * lpDEVfxy[lpParse-1]
                                  - ( lp_Real_s( 15.0 ) / lp_Real_s(  2.0 ) ) * lpDEVfxy[lpParse-2]
                                  + ( lp_Real_s( 20.0 ) / lp_Real_s(  3.0 ) ) * lpDEVfxy[lpParse-3]
                                  - ( lp_Real_s( 15.0 ) / lp_Real_s(  4.0 ) ) * lpDEVfxy[lpParse-4]
                                  + ( lp_Real_s(  6.0 ) / lp_Real_s(  5.0 ) ) * lpDEVfxy[lpParse-5]
                                  - ( lp_Real_s(  1.0 ) / lp_Real_s(  6.0 ) ) * lpDEVfxy[lpParse-6]
                                  );

            /* Integration - Advance frame x-vector z-component */
            lpDEVfxz[lpParse] = ( lp_Real_s( 20.0 ) / lp_Real_s( 49.0 ) ) * (
                                  + ( lpDelta                                 ) * lpDEVfxy[lpParse-1] * lpDEVgrx[lpParse-1]
                                  - ( lpDelta                                 ) * lpDEVfxx[lpParse-1] * lpDEVgry[lpParse-1]
                                  + ( lp_Real_s(  6.0 )                       ) * lpDEVfxz[lpParse-1]
                                  - ( lp_Real_s( 15.0 ) / lp_Real_s(  2.0 ) ) * lpDEVfxz[lpParse-2]
                                  + ( lp_Real_s( 20.0 ) / lp_Real_s(  3.0 ) ) * lpDEVfxz[lpParse-3]
                                  - ( lp_Real_s( 15.0 ) / lp_Real_s(  4.0 ) ) * lpDEVfxz[lpParse-4]
                                  + ( lp_Real_s(  6.0 ) / lp_Real_s(  5.0 ) ) * lpDEVfxz[lpParse-5]
                                  - ( lp_Real_s(  1.0 ) / lp_Real_s(  6.0 ) ) * lpDEVfxz[lpParse-6]
                                  );

            /* Integration - Advance frame y-vector x-component */
            lpDEVfyx[lpParse] = ( lp_Real_s( 20.0 ) / lp_Real_s( 49.0 ) ) * (
                                  + ( lpDelta                                 ) * lpDEVfyz[lpParse-1] * lpDEVgry[lpParse-1]
                                  - ( lpDelta                                 ) * lpDEVfyy[lpParse-1] * lpDEVgrz[lpParse-1]
                                  + ( lp_Real_s(  6.0 )                       ) * lpDEVfyx[lpParse-1]
                                  - ( lp_Real_s( 15.0 ) / lp_Real_s(  2.0 ) ) * lpDEVfyx[lpParse-2]
                                  + ( lp_Real_s( 20.0 ) / lp_Real_s(  3.0 ) ) * lpDEVfyx[lpParse-3]
                                  - ( lp_Real_s( 15.0 ) / lp_Real_s(  4.0 ) ) * lpDEVfyx[lpParse-4]
                                  + ( lp_Real_s(  6.0 ) / lp_Real_s(  5.0 ) ) * lpDEVfyx[lpParse-5]
                                  - ( lp_Real_s(  1.0 ) / lp_Real_s(  6.0 ) ) * lpDEVfyx[lpParse-6]
                                  );

            /* Integration - Advance frame y-vector y-component */
            lpDEVfyy[lpParse] = ( lp_Real_s( 20.0 ) / lp_Real_s( 49.0 ) ) * (
                                  + ( lpDelta                                 ) * lpDEVfyx[lpParse-1] * lpDEVgrz[lpParse-1]
                                  - ( lpDelta                                 ) * lpDEVfyz[lpParse-1] * lpDEVgrx[lpParse-1]
                                  + ( lp_Real_s(  6.0 )                       ) * lpDEVfyy[lpParse-1]
                                  - ( lp_Real_s( 15.0 ) / lp_Real_s(  2.0 ) ) * lpDEVfyy[lpParse-2]
                                  + ( lp_Real_s( 20.0 ) / lp_Real_s(  3.0 ) ) * lpDEVfyy[lpParse-3]
                                  - ( lp_Real_s( 15.0 ) / lp_Real_s(  4.0 ) ) * lpDEVfyy[lpParse-4]
                                  + ( lp_Real_s(  6.0 ) / lp_Real_s(  5.0 ) ) * lpDEVfyy[lpParse-5]
                                  - ( lp_Real_s(  1.0 ) / lp_Real_s(  6.0 ) ) * lpDEVfyy[lpParse-6]
                                  );

            /* Integration - Advance frame y-vector z-component */
            lpDEVfyz[lpParse] = ( lp_Real_s( 20.0 ) / lp_Real_s( 49.0 ) ) * (
                                  + ( lpDelta                                 ) * lpDEVfyy[lpParse-1] * lpDEVgrx[lpParse-1]
                                  - ( lpDelta                                 ) * lpDEVfyx[lpParse-1] * lpDEVgry[lpParse-1]
                                  + ( lp_Real_s(  6.0 )                       ) * lpDEVfyz[lpParse-1]
                                  - ( lp_Real_s( 15.0 ) / lp_Real_s(  2.0 ) ) * lpDEVfyz[lpParse-2]
                                  + ( lp_Real_s( 20.0 ) / lp_Real_s(  3.0 ) ) * lpDEVfyz[lpParse-3]
                                  - ( lp_Real_s( 15.0 ) / lp_Real_s(  4.0 ) ) * lpDEVfyz[lpParse-4]
                                  + ( lp_Real_s(  6.0 ) / lp_Real_s(  5.0 ) ) * lpDEVfyz[lpParse-5]
                                  - ( lp_Real_s(  1.0 ) / lp_Real_s(  6.0 ) ) * lpDEVfyz[lpParse-6]
                                  );

            /* Integration - Advance frame z-vector x-component */
            lpDEVfzx[lpParse] = ( lp_Real_s( 20.0 ) / lp_Real_s( 49.0 ) ) * (
                                  + ( lpDelta                                 ) * lpDEVfzz[lpParse-1] * lpDEVgry[lpParse-1]
                                  - ( lpDelta                                 ) * lpDEVfzy[lpParse-1] * lpDEVgrz[lpParse-1]
                                  + ( lp_Real_s(  6.0 )                       ) * lpDEVfzx[lpParse-1]
                                  - ( lp_Real_s( 15.0 ) / lp_Real_s(  2.0 ) ) * lpDEVfzx[lpParse-2]
                                  + ( lp_Real_s( 20.0 ) / lp_Real_s(  3.0 ) ) * lpDEVfzx[lpParse-3]
                                  - ( lp_Real_s( 15.0 ) / lp_Real_s(  4.0 ) ) * lpDEVfzx[lpParse-4]
                                  + ( lp_Real_s(  6.0 ) / lp_Real_s(  5.0 ) ) * lpDEVfzx[lpParse-5]
                                  - ( lp_Real_s(  1.0 ) / lp_Real_s(  6.0 ) ) * lpDEVfzx[lpParse-6]
                                  );

            /* Integration - Advance frame z-vector y-component */
            lpDEVfzy[lpParse] = ( lp_Real_s( 20.0 ) / lp_Real_s( 49.0 ) ) * (
                                  + ( lpDelta                                 ) * lpDEVfzx[lpParse-1] * lpDEVgrz[lpParse-1]
                                  - ( lpDelta                                 ) * lpDEVfzz[lpParse-1] * lpDEVgrx[lpParse-1]
                                  + ( lp_Real_s(  6.0 )                       ) * lpDEVfzy[lpParse-1]
                                  - ( lp_Real_s( 15.0 ) / lp_Real_s(  2.0 ) ) * lpDEVfzy[lpParse-2]
                                  + ( lp_Real_s( 20.0 ) / lp_Real_s(  3.0 ) ) * lpDEVfzy[lpParse-3]
                                  - ( lp_Real_s( 15.0 ) / lp_Real_s(  4.0 ) ) * lpDEVfzy[lpParse-4]
                                  + ( lp_Real_s(  6.0 ) / lp_Real_s(  5.0 ) ) * lpDEVfzy[lpParse-5]
                                  - ( lp_Real_s(  1.0 ) / lp_Real_s(  6.0 ) ) * lpDEVfzy[lpParse-6]
                                  );

            /* Integration - Advance frame z-vector z-component */
            lpDEVfzz[lpParse] = ( lp_Real_s( 20.0 ) / lp_Real_s( 49.0 ) ) * (
                                  + ( lpDelta                                 ) * lpDEVfzy[lpParse-1] * lpDEVgrx[lpParse-1]
                                  - ( lpDelta                                 ) * lpDEVfzx[lpParse-1] * lpDEVgry[lpParse-1]
                                  + ( lp_Real_s(  6.0 )                       ) * lpDEVfzz[lpParse-1]
                                  - ( lp_Real_s( 15.0 ) / lp_Real_s(  2.0 ) ) * lpDEVfzz[lpParse-2]
                                  + ( lp_Real_s( 20.0 ) / lp_Real_s(  3.0 ) ) * lpDEVfzz[lpParse-3]
                                  - ( lp_Real_s( 15.0 ) / lp_Real_s(  4.0 ) ) * lpDEVfzz[lpParse-4]
                                  + ( lp_Real_s(  6.0 ) / lp_Real_s(  5.0 ) ) * lpDEVfzz[lpParse-5]
                                  - ( lp_Real_s(  1.0 ) / lp_Real_s(  6.0 ) ) * lpDEVfzz[lpParse-6]
                                  );

        }

        /* Write stream data */
        lp_stream_write( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, LP_IMU_MODULE_IFETI__MOD, "fxx", lpDEVfxx, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, LP_IMU_MODULE_IFETI__MOD, "fxy", lpDEVfxy, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, LP_IMU_MODULE_IFETI__MOD, "fxz", lpDEVfxz, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, LP_IMU_MODULE_IFETI__MOD, "fyx", lpDEVfyx, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, LP_IMU_MODULE_IFETI__MOD, "fyy", lpDEVfyy, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, LP_IMU_MODULE_IFETI__MOD, "fyz", lpDEVfyz, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, LP_IMU_MODULE_IFETI__MOD, "fzx", lpDEVfzx, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, LP_IMU_MODULE_IFETI__MOD, "fzy", lpDEVfzy, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, LP_IMU_MODULE_IFETI__MOD, "fzz", lpDEVfzz, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, LP_IMU_MODULE_IFETI__MOD, "syn", lpDEVsyn, sizeof( lp_Time_t ) * lpSize );

        /* Unallocate buffer memory */
        free( lpDEVgrx );
        free( lpDEVgry );
        free( lpDEVgrz );
        free( lpDEVfxx );
        free( lpDEVfxy );
        free( lpDEVfxz );
        free( lpDEVfyx );
        free( lpDEVfyy );
        free( lpDEVfyz );
        free( lpDEVfzx );
        free( lpDEVfzy );
        free( lpDEVfzz );
        free( lpDEVsyn );

        /* Return device descriptor */
        return( lpDevice );

    }


