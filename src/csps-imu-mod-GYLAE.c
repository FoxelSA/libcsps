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

    # include "csps-imu-mod-GYLAE.h"

/*
    Source - IMU absolute acceleration computation module
 */

    lp_IMU lp_imu_mod_GYLAE( 

        const lp_Char_t * const lpPath, 
        lp_IMU                  lpDevice, 
        const lp_Char_t * const lpPSac, 
        const lp_Char_t * const lpPSf_ 

    ) {

        /* Integration variables */
        lp_Size_t lpParse = 0;

        /* Files size */
        lp_Size_t lpSize = 0;

        /* Data buffers */
        lp_Real_t * lpDEVacx = NULL;
        lp_Real_t * lpDEVacy = NULL;
        lp_Real_t * lpDEVacz = NULL;
        lp_Time_t * lpDEVasy = NULL;
        lp_Real_t * lpDEVfxx = NULL;
        lp_Real_t * lpDEVfxy = NULL;
        lp_Real_t * lpDEVfxz = NULL;
        lp_Real_t * lpDEVfyx = NULL;
        lp_Real_t * lpDEVfyy = NULL;
        lp_Real_t * lpDEVfyz = NULL;
        lp_Real_t * lpDEVfzx = NULL;
        lp_Real_t * lpDEVfzy = NULL;
        lp_Real_t * lpDEVfzz = NULL;
        lp_Time_t * lpDEVfsy = NULL;
        lp_Real_t * lpDEVaax = NULL;
        lp_Real_t * lpDEVaay = NULL;
        lp_Real_t * lpDEVaaz = NULL;
        lp_Time_t * lpDEVsyn = NULL;

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, LP_IMU_MODULE_GYLAE__DEV, lpDevice.dvTag, lpPSac, "syn" ) / sizeof( lp_Time_t );

        /* Read streams data */
        lpDEVacx = lp_stream_read( lpPath, LP_IMU_MODULE_GYLAE__DEV, lpDevice.dvTag, lpPSac, "acx", sizeof( lp_Real_t ) * lpSize );
        lpDEVacy = lp_stream_read( lpPath, LP_IMU_MODULE_GYLAE__DEV, lpDevice.dvTag, lpPSac, "acy", sizeof( lp_Real_t ) * lpSize );
        lpDEVacz = lp_stream_read( lpPath, LP_IMU_MODULE_GYLAE__DEV, lpDevice.dvTag, lpPSac, "acz", sizeof( lp_Real_t ) * lpSize );
        lpDEVasy = lp_stream_read( lpPath, LP_IMU_MODULE_GYLAE__DEV, lpDevice.dvTag, lpPSac, "syn", sizeof( lp_Time_t ) * lpSize );
        lpDEVfxx = lp_stream_read( lpPath, LP_IMU_MODULE_GYLAE__DEV, lpDevice.dvTag, lpPSf_, "fxx", sizeof( lp_Real_t ) * lpSize );
        lpDEVfxy = lp_stream_read( lpPath, LP_IMU_MODULE_GYLAE__DEV, lpDevice.dvTag, lpPSf_, "fxy", sizeof( lp_Real_t ) * lpSize );
        lpDEVfxz = lp_stream_read( lpPath, LP_IMU_MODULE_GYLAE__DEV, lpDevice.dvTag, lpPSf_, "fxz", sizeof( lp_Real_t ) * lpSize );
        lpDEVfyx = lp_stream_read( lpPath, LP_IMU_MODULE_GYLAE__DEV, lpDevice.dvTag, lpPSf_, "fyx", sizeof( lp_Real_t ) * lpSize );
        lpDEVfyy = lp_stream_read( lpPath, LP_IMU_MODULE_GYLAE__DEV, lpDevice.dvTag, lpPSf_, "fyy", sizeof( lp_Real_t ) * lpSize );
        lpDEVfyz = lp_stream_read( lpPath, LP_IMU_MODULE_GYLAE__DEV, lpDevice.dvTag, lpPSf_, "fyz", sizeof( lp_Real_t ) * lpSize );
        lpDEVfzx = lp_stream_read( lpPath, LP_IMU_MODULE_GYLAE__DEV, lpDevice.dvTag, lpPSf_, "fzx", sizeof( lp_Real_t ) * lpSize );
        lpDEVfzy = lp_stream_read( lpPath, LP_IMU_MODULE_GYLAE__DEV, lpDevice.dvTag, lpPSf_, "fzy", sizeof( lp_Real_t ) * lpSize );
        lpDEVfzz = lp_stream_read( lpPath, LP_IMU_MODULE_GYLAE__DEV, lpDevice.dvTag, lpPSf_, "fzz", sizeof( lp_Real_t ) * lpSize );
        lpDEVfsy = lp_stream_read( lpPath, LP_IMU_MODULE_GYLAE__DEV, lpDevice.dvTag, lpPSf_, "syn", sizeof( lp_Time_t ) * lpSize );

        /* Allocate stream memory */
        lpDEVaax = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpSize );
        lpDEVaay = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpSize );
        lpDEVaaz = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpSize );
        lpDEVsyn = ( lp_Time_t * ) malloc( sizeof( lp_Time_t ) * lpSize );

        /* Frame integration procedure */
        for ( lpParse = lp_Size_s( 0 ) ; lpParse < lpSize ; lpParse ++ ) {

            /* Computation - Advance absolute acceleration x-vector */
            lpDEVaax[lpParse] = lpDEVacx[lpParse] * lpDEVfxx[lpParse] +
                                    lpDEVacy[lpParse] * lpDEVfyx[lpParse] +
                                    lpDEVacz[lpParse] * lpDEVfzx[lpParse];

            /* Computation - Advance absolute acceleration y-vector */
            lpDEVaax[lpParse] = lpDEVacx[lpParse] * lpDEVfxy[lpParse] +
                                    lpDEVacy[lpParse] * lpDEVfyy[lpParse] +
                                    lpDEVacz[lpParse] * lpDEVfzy[lpParse];

            /* Computation - Advance absolute acceleration z-vector */
            lpDEVaax[lpParse] = lpDEVacx[lpParse] * lpDEVfxz[lpParse] +
                                    lpDEVacy[lpParse] * lpDEVfyz[lpParse] +
                                    lpDEVacz[lpParse] * lpDEVfzz[lpParse];

        }

        /* Write stream data */
        lp_stream_write( lpPath, LP_IMU_MODULE_GYLAE__DEV, lpDevice.dvTag, LP_IMU_MODULE_GYLAE__MOD, "aax", lpDEVaax, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_MODULE_GYLAE__DEV, lpDevice.dvTag, LP_IMU_MODULE_GYLAE__MOD, "aay", lpDEVaay, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_MODULE_GYLAE__DEV, lpDevice.dvTag, LP_IMU_MODULE_GYLAE__MOD, "aaz", lpDEVaaz, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_MODULE_GYLAE__DEV, lpDevice.dvTag, LP_IMU_MODULE_GYLAE__MOD, "syn", lpDEVaaz, sizeof( lp_Time_t ) * lpSize );

        /* Unallocate buffer memory */
        free( lpDEVacx );
        free( lpDEVacy );
        free( lpDEVacz );
        free( lpDEVasy );
        free( lpDEVfxx );
        free( lpDEVfxy );
        free( lpDEVfxz );
        free( lpDEVfyx );
        free( lpDEVfyy );
        free( lpDEVfyz );
        free( lpDEVfzx );
        free( lpDEVfzy );
        free( lpDEVfzz );
        free( lpDEVfsy );
        free( lpDEVaax );
        free( lpDEVaay );
        free( lpDEVaaz );
        free( lpDEVsyn );

        /* Return device descriptor */
        return( lpDevice );

    }

