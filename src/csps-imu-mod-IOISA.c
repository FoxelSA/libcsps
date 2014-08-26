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
    Source - Earth self-alignment
 */

    lp_IMU lp_imu_mod_IOISA( 

        const lp_Char_t * const lpPath, 
        lp_IMU                  lpIMU,
        lp_GPS                  lpGPS,
        const lp_Char_t * const lpPMimu,
        const lp_Char_t * const lpPMgps 

    ) {

        /* Downsampling variables */
        lp_Size_t lpParse = lp_Size_s( 0 );

        /* Files size variables */
        lp_Size_t lpSize = lp_Size_s( 0 );

        /* Accumulators variables */
        lp_Real_t lpACCacx = lp_Real_s( 0.0 );
        lp_Real_t lpACCacy = lp_Real_s( 0.0 );
        lp_Real_t lpACCacz = lp_Real_s( 0.0 );
        lp_Real_t lpACCgrx = lp_Real_s( 0.0 );
        lp_Real_t lpACCgry = lp_Real_s( 0.0 );
        lp_Real_t lpACCgrz = lp_Real_s( 0.0 );
        lp_Real_t lpACClat = lp_Real_s( 0.0 );
        lp_Real_t lpACCacn = lp_Real_s( 0.0 );
        lp_Real_t lpACCgrn = lp_Real_s( 0.0 );
        lp_Real_t lpACCabs = lp_Real_s( 0.0 );

        /* Data buffers variables */
        lp_Real_t * lpDEVacx = NULL;
        lp_Real_t * lpDEVacy = NULL;
        lp_Real_t * lpDEVacz = NULL;
        lp_Real_t * lpDEVgrx = NULL;
        lp_Real_t * lpDEVgry = NULL;
        lp_Real_t * lpDEVgrz = NULL;
        lp_Time_t * lpDEVsyn = NULL;
        lp_Real_t * lpGPSlat = NULL;
        lp_Time_t * lpGPSsyn = NULL;

        /* Still range boundaries variables */
        lp_Time_t lpIMUsrDw = lp_Time_s( 0 );
        lp_Time_t lpIMUsrUp = lp_Time_s( 0 );

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, LP_IMU_IOISA_DEV, lpIMU.dvTag, lpPMimu, "syn" ) / sizeof( lp_Time_t );

        /* Read streams data */
        lpDEVacx = lp_stream_read( lpPath, LP_IMU_IOISA_DEV, lpIMU.dvTag, lpPMimu, "acx", sizeof( lp_Real_t ) * lpSize );
        lpDEVacy = lp_stream_read( lpPath, LP_IMU_IOISA_DEV, lpIMU.dvTag, lpPMimu, "acy", sizeof( lp_Real_t ) * lpSize );
        lpDEVacz = lp_stream_read( lpPath, LP_IMU_IOISA_DEV, lpIMU.dvTag, lpPMimu, "acz", sizeof( lp_Real_t ) * lpSize );
        lpDEVgrx = lp_stream_read( lpPath, LP_IMU_IOISA_DEV, lpIMU.dvTag, lpPMimu, "grx", sizeof( lp_Real_t ) * lpSize );
        lpDEVgry = lp_stream_read( lpPath, LP_IMU_IOISA_DEV, lpIMU.dvTag, lpPMimu, "gry", sizeof( lp_Real_t ) * lpSize );
        lpDEVgrz = lp_stream_read( lpPath, LP_IMU_IOISA_DEV, lpIMU.dvTag, lpPMimu, "grz", sizeof( lp_Real_t ) * lpSize );
        lpDEVsyn = lp_stream_read( lpPath, LP_IMU_IOISA_DEV, lpIMU.dvTag, lpPMimu, "syn", sizeof( lp_Time_t ) * lpSize );

        /* Obtain still range boundaries index */
        lpIMUsrDw = lp_timestamp_index( lpIMU.dvMin, lpDEVsyn, lpSize );
        lpIMUsrUp = lp_timestamp_index( lpIMU.dvMax, lpDEVsyn, lpSize );

        /* Quantities accumulation */
        for ( lpParse = lpIMUsrDw ; lpParse <= lpIMUsrUp ; lpParse ++ ) {

            /* Accelerometer signal accumulation */
            lpACCacx += lpDEVacx[lpParse];
            lpACCacy += lpDEVacy[lpParse];
            lpACCacz += lpDEVacz[lpParse];

            /* Gyroscope signal accumulation */
            lpACCgrx += lpDEVgrx[lpParse];
            lpACCgry += lpDEVgry[lpParse];
            lpACCgrz += lpDEVgrz[lpParse];

        }

        /* Unallocate buffer memory */
        free( lpDEVacx );
        free( lpDEVacy );
        free( lpDEVacz );
        free( lpDEVgrx );
        free( lpDEVgry );
        free( lpDEVgrz );
        free( lpDEVsyn );

        /* Accelerometer average computation */
        lpACCacx /= ( lpIMUsrUp - lpIMUsrDw + lp_Size_s( 1 ) );
        lpACCacy /= ( lpIMUsrUp - lpIMUsrDw + lp_Size_s( 1 ) );
        lpACCacz /= ( lpIMUsrUp - lpIMUsrDw + lp_Size_s( 1 ) );

        /* Compute acceleration norm */
        lpACCacn = sqrt( lpACCacx * lpACCacx + lpACCacy * lpACCacy + lpACCacz * lpACCacz );

        /* Gyroscope average computation */
        lpACCgrx /= ( lpIMUsrUp - lpIMUsrDw + lp_Size_s( 1 ) );
        lpACCgry /= ( lpIMUsrUp - lpIMUsrDw + lp_Size_s( 1 ) );
        lpACCgrz /= ( lpIMUsrUp - lpIMUsrDw + lp_Size_s( 1 ) );

        /* Compute angular velocity norm */
        lpACCgrn = sqrt( lpACCgrx * lpACCgrx + lpACCgry * lpACCgry + lpACCgrz * lpACCgrz );

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, "gps", lpGPS.dvTag, lpPMgps, "syn" ) / sizeof( lp_Time_t );

        /* Read streams data */
        lpGPSlat = lp_stream_read( lpPath, "gps", lpGPS.dvTag, lpPMgps, "lat", sizeof( lp_Real_t ) * lpSize );
        lpGPSsyn = lp_stream_read( lpPath, "gps", lpGPS.dvTag, lpPMgps, "syn", sizeof( lp_Time_t ) * lpSize );

        /* Obtain still range boundaries index */
        lpIMUsrDw = lp_timestamp_index( lpIMU.dvMin, lpGPSsyn, lpSize );
        lpIMUsrUp = lp_timestamp_index( lpIMU.dvMax, lpGPSsyn, lpSize );

        /* Quantities accumulation */
        for ( lpParse = lpIMUsrDw ; lpParse <= lpIMUsrUp ; lpParse ++ ) {

            /* Latitude signal accumulation */
            lpACClat += lpGPSlat[lpParse];

        }

        /* Unallocate buffer memory */
        free( lpGPSlat );
        free( lpGPSsyn );

        /* Latitude average computation */
        lpACClat /= ( lpIMUsrUp - lpIMUsrDw + lp_Size_s( 1 ) );

        /* Frame z-vector gravity alignment */
        lpIMU.dvfzx = - lpACCacx / lpACCacn;
        lpIMU.dvfzy = - lpACCacy / lpACCacn;
        lpIMU.dvfzz = - lpACCacz / lpACCacn;

        /* Frame x-vector coarse heading alignment */
        lpIMU.dvfxx = - ( tan( lpACClat ) / lpACCacn ) * lpACCacx + ( lp_Real_s( 1.0 ) / ( lpACCgrn * cos( lpACClat ) ) ) * lpACCgrx;
        lpIMU.dvfxy = - ( tan( lpACClat ) / lpACCacn ) * lpACCacy + ( lp_Real_s( 1.0 ) / ( lpACCgrn * cos( lpACClat ) ) ) * lpACCgry;
        lpIMU.dvfxz = - ( tan( lpACClat ) / lpACCacn ) * lpACCacz + ( lp_Real_s( 1.0 ) / ( lpACCgrn * cos( lpACClat ) ) ) * lpACCgrz;

        /* Frame y-vector computation */
        lpIMU.dvfyx = lpIMU.dvfzy * lpIMU.dvfxz - lpIMU.dvfzz * lpIMU.dvfxy;
        lpIMU.dvfyy = lpIMU.dvfzz * lpIMU.dvfxx - lpIMU.dvfzx * lpIMU.dvfxz;
        lpIMU.dvfyz = lpIMU.dvfzx * lpIMU.dvfxy - lpIMU.dvfzy * lpIMU.dvfxx;

        /* Compute y-vector norm */
        lpACCabs = sqrt( lpIMU.dvfyx * lpIMU.dvfyx + lpIMU.dvfyy * lpIMU.dvfyy + lpIMU.dvfyz * lpIMU.dvfyz );

        /* Frame y-vector normalization */
        lpIMU.dvfyx /= lpACCabs;
        lpIMU.dvfyy /= lpACCabs;
        lpIMU.dvfyz /= lpACCabs;

        /* Frame x-vector orthogonal alignment */
        lpIMU.dvfxx = lpIMU.dvfyy * lpIMU.dvfzz - lpIMU.dvfyz * lpIMU.dvfzy;
        lpIMU.dvfxy = lpIMU.dvfyz * lpIMU.dvfzx - lpIMU.dvfyx * lpIMU.dvfzz;
        lpIMU.dvfxz = lpIMU.dvfyx * lpIMU.dvfzy - lpIMU.dvfyy * lpIMU.dvfzx;

        /* Return device descriptor */
        return( lpIMU );

    }

