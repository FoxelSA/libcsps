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

    # include "csps-imu-mod-IOISA.h"

/*
    Source - Gravity alignment procedure
 */

    lp_IMU lp_imu_mod_IOISA( const lp_Char_t * const lpPath, lp_IMU lpDevice, const lp_Char_t * const lpPS__ ) {

        /* Downsampling variables */
        lp_Size_t lpParse = lp_Size_s( 0 );

        /* Files size */
        lp_Size_t lpSize = lp_Size_s( 0 );

        /* Acceleration accumulation */
        lp_Real_t lpACCacx = lp_Real_s( 0.0 );
        lp_Real_t lpACCacy = lp_Real_s( 0.0 );
        lp_Real_t lpACCacz = lp_Real_s( 0.0 );
        lp_Real_t lpACCgrx = lp_Real_s( 0.0 );
        lp_Real_t lpACCgry = lp_Real_s( 0.0 );
        lp_Real_t lpACCgrz = lp_Real_s( 0.0 );
        lp_Real_t lpACCnrm = lp_Real_s( 0.0 );

        /* Data buffers */
        lp_Real_t * lpDEVacx = NULL;
        lp_Real_t * lpDEVacy = NULL;
        lp_Real_t * lpDEVacz = NULL;
        lp_Real_t * lpDEVgrx = NULL;
        lp_Real_t * lpDEVgry = NULL;
        lp_Real_t * lpDEVgrz = NULL;
        lp_Time_t * lpDEVsyn = NULL;

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, LP_IMU_MODULE_IOISA__DEV, lpDevice.dvTag, lpPS__, "syn" ) / sizeof( lp_Time_t );

        /* Read streams data */
        lpDEVacx = lp_stream_read( lpPath, LP_IMU_MODULE_IOISA__DEV, lpDevice.dvTag, lpPS__, "acx", sizeof( lp_Real_t ) * lpSize );
        lpDEVacy = lp_stream_read( lpPath, LP_IMU_MODULE_IOISA__DEV, lpDevice.dvTag, lpPS__, "acy", sizeof( lp_Real_t ) * lpSize );
        lpDEVacz = lp_stream_read( lpPath, LP_IMU_MODULE_IOISA__DEV, lpDevice.dvTag, lpPS__, "acz", sizeof( lp_Real_t ) * lpSize );
        lpDEVgrx = lp_stream_read( lpPath, LP_IMU_MODULE_IOISA__DEV, lpDevice.dvTag, lpPS__, "grx", sizeof( lp_Real_t ) * lpSize );
        lpDEVgry = lp_stream_read( lpPath, LP_IMU_MODULE_IOISA__DEV, lpDevice.dvTag, lpPS__, "gry", sizeof( lp_Real_t ) * lpSize );
        lpDEVgrz = lp_stream_read( lpPath, LP_IMU_MODULE_IOISA__DEV, lpDevice.dvTag, lpPS__, "grz", sizeof( lp_Real_t ) * lpSize );
        lpDEVsyn = lp_stream_read( lpPath, LP_IMU_MODULE_IOISA__DEV, lpDevice.dvTag, lpPS__, "syn", sizeof( lp_Time_t ) * lpSize );

        /* Downsampling procedure */
        while ( lpParse < ( lp_Size_s( 5 ) * lpDevice.dvdfreq ) ) {

            /* Accelerometer signal accumulation */
            lpACCacx += lpDEVacx[lpParse];
            lpACCacy += lpDEVacy[lpParse];
            lpACCacz += lpDEVacz[lpParse];

            /* Gyroscope signal accumulation */
            lpACCgrx += lpDEVgrx[lpParse];
            lpACCgry += lpDEVgry[lpParse];
            lpACCgrz += lpDEVgrz[lpParse];

            /* Update parse index */
            lpParse += lp_Size_s( 1 );

        }

        /* Accelerometer accumulation average */
        lpACCacx /= lpParse;
        lpACCacy /= lpParse;
        lpACCacz /= lpParse;

        /* Compute average acceleration norm */
        lpACCnrm = sqrt( lpACCacx * lpACCacx + lpACCacy * lpACCacy + lpACCacz * lpACCacz );

        /* Normalize acceleration vector */
        lpACCacx /= lpACCnrm;
        lpACCacy /= lpACCnrm;
        lpACCacz /= lpACCnrm;

        /* Gyroscope accumulation average */
        lpACCgrx /= lpParse;
        lpACCgry /= lpParse;
        lpACCgrz /= lpParse;

        /* Compute average acceleration norm */
        lpACCnrm = sqrt( lpACCgrx * lpACCgrx + lpACCgry * lpACCgry + lpACCgrz * lpACCgrz );

        /* Normalize acceleration vector */
        lpACCgrx /= lpACCnrm;
        lpACCgry /= lpACCnrm;
        lpACCgrz /= lpACCnrm;

        /* Align z-vector to gravity reaction */
        lpDevice.dvfzx = + lpACCacx;
        lpDevice.dvfzy = + lpACCacy;
        lpDevice.dvfzz = + lpACCacz;

        /* Align x-vector to gravity/earth rate normal */
        lpDevice.dvfyx = - lpACCacy * lpACCgrz + lpACCacz * lpACCgry;
        lpDevice.dvfyy = - lpACCacz * lpACCgrx + lpACCacx * lpACCgrz;
        lpDevice.dvfyz = - lpACCacx * lpACCgry + lpACCacy * lpACCgrx;

        /* Align y-vector to x-z crossed product */
        lpDevice.dvfxx = - lpDevice.dvfyy * lpDevice.dvfzz + lpDevice.dvfyz * lpDevice.dvfzy;
        lpDevice.dvfxy = - lpDevice.dvfyz * lpDevice.dvfzx + lpDevice.dvfyx * lpDevice.dvfzz;
        lpDevice.dvfxz = - lpDevice.dvfyx * lpDevice.dvfzy + lpDevice.dvfyy * lpDevice.dvfzx;

        /* Unallocate buffer memory */
        free( lpDEVacx );
        free( lpDEVacy );
        free( lpDEVacz );
        free( lpDEVgrx );
        free( lpDEVgry );
        free( lpDEVgrz );
        free( lpDEVsyn );

        /* Return device descriptor */
        return( lpDevice );

    }

