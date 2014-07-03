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

    # include "csps-imu-modfi.h"

/*
    Source - IMU frame integration module
 */

    csps_IMU csps_imu_modfi(

        const csps_Char_t * const cspsPath,
        csps_IMU cspsDevice,
        const csps_Char_t * const cspsName,
        const csps_Char_t * const cspsPSgr

    ) {

        /* Integration variables */
        csps_Real_t cspsDelta = csps_Real_s( 0.0 );
        csps_Size_t cspsParse = csps_Size_s( 0 );

        /* Files size */
        csps_Size_t cspsSize = csps_Size_s( 0 );

        /* Data buffers */
        csps_Real_t * cspsDEVgrx = NULL;
        csps_Real_t * cspsDEVgry = NULL;
        csps_Real_t * cspsDEVgrz = NULL;
        csps_Real_t * cspsDEVfxx = NULL;
        csps_Real_t * cspsDEVfxy = NULL;
        csps_Real_t * cspsDEVfxz = NULL;
        csps_Real_t * cspsDEVfyx = NULL;
        csps_Real_t * cspsDEVfyy = NULL;
        csps_Real_t * cspsDEVfyz = NULL;
        csps_Real_t * cspsDEVfzx = NULL;
        csps_Real_t * cspsDEVfzy = NULL;
        csps_Real_t * cspsDEVfzz = NULL;
        csps_Time_t * cspsDEVsyn = NULL;

        /* Obtain stream size */
        cspsSize = csps_stream_size( cspsPath, CSPS_IMU_MODFI_DEV, cspsName, cspsPSgr, "syn" ) / sizeof( uint64_t );

        /* Read streams data */
        cspsDEVgrx = csps_stream_read( cspsPath, CSPS_IMU_MODFI_DEV, cspsName, cspsPSgr, "grx", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVgry = csps_stream_read( cspsPath, CSPS_IMU_MODFI_DEV, cspsName, cspsPSgr, "gry", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVgrz = csps_stream_read( cspsPath, CSPS_IMU_MODFI_DEV, cspsName, cspsPSgr, "grz", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVsyn = csps_stream_read( cspsPath, CSPS_IMU_MODFI_DEV, cspsName, cspsPSgr, "syn", sizeof( csps_Time_t ) * cspsSize );

        /* Allocate stream memory */
        cspsDEVfxx = ( csps_Real_t * ) malloc( sizeof( csps_Real_t ) * cspsSize );
        cspsDEVfxy = ( csps_Real_t * ) malloc( sizeof( csps_Real_t ) * cspsSize );
        cspsDEVfxz = ( csps_Real_t * ) malloc( sizeof( csps_Real_t ) * cspsSize );
        cspsDEVfyx = ( csps_Real_t * ) malloc( sizeof( csps_Real_t ) * cspsSize );
        cspsDEVfyy = ( csps_Real_t * ) malloc( sizeof( csps_Real_t ) * cspsSize );
        cspsDEVfyz = ( csps_Real_t * ) malloc( sizeof( csps_Real_t ) * cspsSize );
        cspsDEVfzx = ( csps_Real_t * ) malloc( sizeof( csps_Real_t ) * cspsSize );
        cspsDEVfzy = ( csps_Real_t * ) malloc( sizeof( csps_Real_t ) * cspsSize );
        cspsDEVfzz = ( csps_Real_t * ) malloc( sizeof( csps_Real_t ) * cspsSize );

        /* Setting initial conditions */
        for ( cspsParse = csps_Size_s( 0 ) ; cspsParse < CSPS_IMU_FRAME_BOUND ; cspsParse ++ ) {

            /* Assign initial condition on IMU frame */
            cspsDEVfxx[cspsParse] = cspsDevice.dvfxx;
            cspsDEVfxy[cspsParse] = cspsDevice.dvfxy;
            cspsDEVfxz[cspsParse] = cspsDevice.dvfxz;
            cspsDEVfyx[cspsParse] = cspsDevice.dvfyx;
            cspsDEVfyy[cspsParse] = cspsDevice.dvfyy;
            cspsDEVfyz[cspsParse] = cspsDevice.dvfyz;
            cspsDEVfzx[cspsParse] = cspsDevice.dvfzx;
            cspsDEVfzy[cspsParse] = cspsDevice.dvfzy;
            cspsDEVfzz[cspsParse] = cspsDevice.dvfzz;

        }

        /* Compute time step value */
        cspsDelta = csps_Real_s( 1.0 ) / ( ( csps_Real_t ) cspsDevice.dvdfreq );

        /* Frame integration procedure */
        for ( cspsParse = CSPS_IMU_FRAME_BOUND ; cspsParse < cspsSize ; cspsParse ++ ) {

            /* Integration - Advance frame x-vector x-component */
            cspsDEVfxx[cspsParse] = ( csps_Real_s( 20.0 ) / csps_Real_s( 49.0 ) ) * (
                                  + ( cspsDelta                                 ) * cspsDEVfxz[cspsParse-1] * cspsDEVgry[cspsParse-1]
                                  - ( cspsDelta                                 ) * cspsDEVfxy[cspsParse-1] * cspsDEVgrz[cspsParse-1]
                                  + ( csps_Real_s(  6.0 )                       ) * cspsDEVfxx[cspsParse-1]
                                  - ( csps_Real_s( 15.0 ) / csps_Real_s(  2.0 ) ) * cspsDEVfxx[cspsParse-2]
                                  + ( csps_Real_s( 20.0 ) / csps_Real_s(  3.0 ) ) * cspsDEVfxx[cspsParse-3]
                                  - ( csps_Real_s( 15.0 ) / csps_Real_s(  4.0 ) ) * cspsDEVfxx[cspsParse-4]
                                  + ( csps_Real_s(  6.0 ) / csps_Real_s(  5.0 ) ) * cspsDEVfxx[cspsParse-5]
                                  - ( csps_Real_s(  1.0 ) / csps_Real_s(  6.0 ) ) * cspsDEVfxx[cspsParse-6]
                                  );

            /* Integration - Advance frame x-vector y-component */
            cspsDEVfxy[cspsParse] = ( csps_Real_s( 20.0 ) / csps_Real_s( 49.0 ) ) * (
                                  + ( cspsDelta                                 ) * cspsDEVfxx[cspsParse-1] * cspsDEVgrz[cspsParse-1]
                                  - ( cspsDelta                                 ) * cspsDEVfxz[cspsParse-1] * cspsDEVgrx[cspsParse-1]
                                  + ( csps_Real_s(  6.0 )                       ) * cspsDEVfxy[cspsParse-1]
                                  - ( csps_Real_s( 15.0 ) / csps_Real_s(  2.0 ) ) * cspsDEVfxy[cspsParse-2]
                                  + ( csps_Real_s( 20.0 ) / csps_Real_s(  3.0 ) ) * cspsDEVfxy[cspsParse-3]
                                  - ( csps_Real_s( 15.0 ) / csps_Real_s(  4.0 ) ) * cspsDEVfxy[cspsParse-4]
                                  + ( csps_Real_s(  6.0 ) / csps_Real_s(  5.0 ) ) * cspsDEVfxy[cspsParse-5]
                                  - ( csps_Real_s(  1.0 ) / csps_Real_s(  6.0 ) ) * cspsDEVfxy[cspsParse-6]
                                  );

            /* Integration - Advance frame x-vector z-component */
            cspsDEVfxz[cspsParse] = ( csps_Real_s( 20.0 ) / csps_Real_s( 49.0 ) ) * (
                                  + ( cspsDelta                                 ) * cspsDEVfxy[cspsParse-1] * cspsDEVgrx[cspsParse-1]
                                  - ( cspsDelta                                 ) * cspsDEVfxx[cspsParse-1] * cspsDEVgry[cspsParse-1]
                                  + ( csps_Real_s(  6.0 )                       ) * cspsDEVfxz[cspsParse-1]
                                  - ( csps_Real_s( 15.0 ) / csps_Real_s(  2.0 ) ) * cspsDEVfxz[cspsParse-2]
                                  + ( csps_Real_s( 20.0 ) / csps_Real_s(  3.0 ) ) * cspsDEVfxz[cspsParse-3]
                                  - ( csps_Real_s( 15.0 ) / csps_Real_s(  4.0 ) ) * cspsDEVfxz[cspsParse-4]
                                  + ( csps_Real_s(  6.0 ) / csps_Real_s(  5.0 ) ) * cspsDEVfxz[cspsParse-5]
                                  - ( csps_Real_s(  1.0 ) / csps_Real_s(  6.0 ) ) * cspsDEVfxz[cspsParse-6]
                                  );

            /* Integration - Advance frame y-vector x-component */
            cspsDEVfyx[cspsParse] = ( csps_Real_s( 20.0 ) / csps_Real_s( 49.0 ) ) * (
                                  + ( cspsDelta                                 ) * cspsDEVfyz[cspsParse-1] * cspsDEVgry[cspsParse-1]
                                  - ( cspsDelta                                 ) * cspsDEVfyy[cspsParse-1] * cspsDEVgrz[cspsParse-1]
                                  + ( csps_Real_s(  6.0 )                       ) * cspsDEVfyx[cspsParse-1]
                                  - ( csps_Real_s( 15.0 ) / csps_Real_s(  2.0 ) ) * cspsDEVfyx[cspsParse-2]
                                  + ( csps_Real_s( 20.0 ) / csps_Real_s(  3.0 ) ) * cspsDEVfyx[cspsParse-3]
                                  - ( csps_Real_s( 15.0 ) / csps_Real_s(  4.0 ) ) * cspsDEVfyx[cspsParse-4]
                                  + ( csps_Real_s(  6.0 ) / csps_Real_s(  5.0 ) ) * cspsDEVfyx[cspsParse-5]
                                  - ( csps_Real_s(  1.0 ) / csps_Real_s(  6.0 ) ) * cspsDEVfyx[cspsParse-6]
                                  );

            /* Integration - Advance frame y-vector y-component */
            cspsDEVfyy[cspsParse] = ( csps_Real_s( 20.0 ) / csps_Real_s( 49.0 ) ) * (
                                  + ( cspsDelta                                 ) * cspsDEVfyx[cspsParse-1] * cspsDEVgrz[cspsParse-1]
                                  - ( cspsDelta                                 ) * cspsDEVfyz[cspsParse-1] * cspsDEVgrx[cspsParse-1]
                                  + ( csps_Real_s(  6.0 )                       ) * cspsDEVfyy[cspsParse-1]
                                  - ( csps_Real_s( 15.0 ) / csps_Real_s(  2.0 ) ) * cspsDEVfyy[cspsParse-2]
                                  + ( csps_Real_s( 20.0 ) / csps_Real_s(  3.0 ) ) * cspsDEVfyy[cspsParse-3]
                                  - ( csps_Real_s( 15.0 ) / csps_Real_s(  4.0 ) ) * cspsDEVfyy[cspsParse-4]
                                  + ( csps_Real_s(  6.0 ) / csps_Real_s(  5.0 ) ) * cspsDEVfyy[cspsParse-5]
                                  - ( csps_Real_s(  1.0 ) / csps_Real_s(  6.0 ) ) * cspsDEVfyy[cspsParse-6]
                                  );

            /* Integration - Advance frame y-vector z-component */
            cspsDEVfyz[cspsParse] = ( csps_Real_s( 20.0 ) / csps_Real_s( 49.0 ) ) * (
                                  + ( cspsDelta                                 ) * cspsDEVfyy[cspsParse-1] * cspsDEVgrx[cspsParse-1]
                                  - ( cspsDelta                                 ) * cspsDEVfyx[cspsParse-1] * cspsDEVgry[cspsParse-1]
                                  + ( csps_Real_s(  6.0 )                       ) * cspsDEVfyz[cspsParse-1]
                                  - ( csps_Real_s( 15.0 ) / csps_Real_s(  2.0 ) ) * cspsDEVfyz[cspsParse-2]
                                  + ( csps_Real_s( 20.0 ) / csps_Real_s(  3.0 ) ) * cspsDEVfyz[cspsParse-3]
                                  - ( csps_Real_s( 15.0 ) / csps_Real_s(  4.0 ) ) * cspsDEVfyz[cspsParse-4]
                                  + ( csps_Real_s(  6.0 ) / csps_Real_s(  5.0 ) ) * cspsDEVfyz[cspsParse-5]
                                  - ( csps_Real_s(  1.0 ) / csps_Real_s(  6.0 ) ) * cspsDEVfyz[cspsParse-6]
                                  );

            /* Integration - Advance frame z-vector x-component */
            cspsDEVfzx[cspsParse] = ( csps_Real_s( 20.0 ) / csps_Real_s( 49.0 ) ) * (
                                  + ( cspsDelta                                 ) * cspsDEVfzz[cspsParse-1] * cspsDEVgry[cspsParse-1]
                                  - ( cspsDelta                                 ) * cspsDEVfzy[cspsParse-1] * cspsDEVgrz[cspsParse-1]
                                  + ( csps_Real_s(  6.0 )                       ) * cspsDEVfzx[cspsParse-1]
                                  - ( csps_Real_s( 15.0 ) / csps_Real_s(  2.0 ) ) * cspsDEVfzx[cspsParse-2]
                                  + ( csps_Real_s( 20.0 ) / csps_Real_s(  3.0 ) ) * cspsDEVfzx[cspsParse-3]
                                  - ( csps_Real_s( 15.0 ) / csps_Real_s(  4.0 ) ) * cspsDEVfzx[cspsParse-4]
                                  + ( csps_Real_s(  6.0 ) / csps_Real_s(  5.0 ) ) * cspsDEVfzx[cspsParse-5]
                                  - ( csps_Real_s(  1.0 ) / csps_Real_s(  6.0 ) ) * cspsDEVfzx[cspsParse-6]
                                  );

            /* Integration - Advance frame z-vector y-component */
            cspsDEVfzy[cspsParse] = ( csps_Real_s( 20.0 ) / csps_Real_s( 49.0 ) ) * (
                                  + ( cspsDelta                                 ) * cspsDEVfzx[cspsParse-1] * cspsDEVgrz[cspsParse-1]
                                  - ( cspsDelta                                 ) * cspsDEVfzz[cspsParse-1] * cspsDEVgrx[cspsParse-1]
                                  + ( csps_Real_s(  6.0 )                       ) * cspsDEVfzy[cspsParse-1]
                                  - ( csps_Real_s( 15.0 ) / csps_Real_s(  2.0 ) ) * cspsDEVfzy[cspsParse-2]
                                  + ( csps_Real_s( 20.0 ) / csps_Real_s(  3.0 ) ) * cspsDEVfzy[cspsParse-3]
                                  - ( csps_Real_s( 15.0 ) / csps_Real_s(  4.0 ) ) * cspsDEVfzy[cspsParse-4]
                                  + ( csps_Real_s(  6.0 ) / csps_Real_s(  5.0 ) ) * cspsDEVfzy[cspsParse-5]
                                  - ( csps_Real_s(  1.0 ) / csps_Real_s(  6.0 ) ) * cspsDEVfzy[cspsParse-6]
                                  );

            /* Integration - Advance frame z-vector z-component */
            cspsDEVfzz[cspsParse] = ( csps_Real_s( 20.0 ) / csps_Real_s( 49.0 ) ) * (
                                  + ( cspsDelta                                 ) * cspsDEVfzy[cspsParse-1] * cspsDEVgrx[cspsParse-1]
                                  - ( cspsDelta                                 ) * cspsDEVfzx[cspsParse-1] * cspsDEVgry[cspsParse-1]
                                  + ( csps_Real_s(  6.0 )                       ) * cspsDEVfzz[cspsParse-1]
                                  - ( csps_Real_s( 15.0 ) / csps_Real_s(  2.0 ) ) * cspsDEVfzz[cspsParse-2]
                                  + ( csps_Real_s( 20.0 ) / csps_Real_s(  3.0 ) ) * cspsDEVfzz[cspsParse-3]
                                  - ( csps_Real_s( 15.0 ) / csps_Real_s(  4.0 ) ) * cspsDEVfzz[cspsParse-4]
                                  + ( csps_Real_s(  6.0 ) / csps_Real_s(  5.0 ) ) * cspsDEVfzz[cspsParse-5]
                                  - ( csps_Real_s(  1.0 ) / csps_Real_s(  6.0 ) ) * cspsDEVfzz[cspsParse-6]
                                  );

        }

        /* Write stream data */
        csps_stream_write( cspsPath, CSPS_IMU_MODFI_DEV, cspsName, CSPS_IMU_MODFI_MOD, "fxx", cspsDEVfxx, sizeof( csps_Real_t ) * cspsSize );
        csps_stream_write( cspsPath, CSPS_IMU_MODFI_DEV, cspsName, CSPS_IMU_MODFI_MOD, "fxy", cspsDEVfxy, sizeof( csps_Real_t ) * cspsSize );
        csps_stream_write( cspsPath, CSPS_IMU_MODFI_DEV, cspsName, CSPS_IMU_MODFI_MOD, "fxz", cspsDEVfxz, sizeof( csps_Real_t ) * cspsSize );
        csps_stream_write( cspsPath, CSPS_IMU_MODFI_DEV, cspsName, CSPS_IMU_MODFI_MOD, "fyx", cspsDEVfyx, sizeof( csps_Real_t ) * cspsSize );
        csps_stream_write( cspsPath, CSPS_IMU_MODFI_DEV, cspsName, CSPS_IMU_MODFI_MOD, "fyy", cspsDEVfyy, sizeof( csps_Real_t ) * cspsSize );
        csps_stream_write( cspsPath, CSPS_IMU_MODFI_DEV, cspsName, CSPS_IMU_MODFI_MOD, "fyz", cspsDEVfyz, sizeof( csps_Real_t ) * cspsSize );
        csps_stream_write( cspsPath, CSPS_IMU_MODFI_DEV, cspsName, CSPS_IMU_MODFI_MOD, "fzx", cspsDEVfzx, sizeof( csps_Real_t ) * cspsSize );
        csps_stream_write( cspsPath, CSPS_IMU_MODFI_DEV, cspsName, CSPS_IMU_MODFI_MOD, "fzy", cspsDEVfzy, sizeof( csps_Real_t ) * cspsSize );
        csps_stream_write( cspsPath, CSPS_IMU_MODFI_DEV, cspsName, CSPS_IMU_MODFI_MOD, "fzz", cspsDEVfzz, sizeof( csps_Real_t ) * cspsSize );
        csps_stream_write( cspsPath, CSPS_IMU_MODFI_DEV, cspsName, CSPS_IMU_MODFI_MOD, "syn", cspsDEVsyn, sizeof( csps_Time_t ) * cspsSize );

        /* Unallocate buffer memory */
        free( cspsDEVgrx );
        free( cspsDEVgry );
        free( cspsDEVgrz );
        free( cspsDEVfxx );
        free( cspsDEVfxy );
        free( cspsDEVfxz );
        free( cspsDEVfyx );
        free( cspsDEVfyy );
        free( cspsDEVfyz );
        free( cspsDEVfzx );
        free( cspsDEVfzy );
        free( cspsDEVfzz );
        free( cspsDEVsyn );

        /* Return device descriptor */
        return( cspsDevice );

    }


