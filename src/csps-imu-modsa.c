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

    # include "csps-imu-modsa.h"

/*
    Source - Gravity alignment procedure
 */

    csps_IMU csps_imu_modsa(

        const csps_Char_t * const cspsPath,
        csps_IMU cspsDevice,
        const csps_Char_t * const cspsName,
        const csps_Char_t * const cspsPS__

    ) {

        /* Downsampling variables */
        csps_Size_t cspsParse = csps_Size_s( 0 );

        /* Files size */
        csps_Size_t cspsSize = csps_Size_s( 0 );

        /* Acceleration accumulation */
        csps_Real_t cspsACCacx = csps_Real_s( 0.0 );
        csps_Real_t cspsACCacy = csps_Real_s( 0.0 );
        csps_Real_t cspsACCacz = csps_Real_s( 0.0 );
        csps_Real_t cspsACCgrx = csps_Real_s( 0.0 );
        csps_Real_t cspsACCgry = csps_Real_s( 0.0 );
        csps_Real_t cspsACCgrz = csps_Real_s( 0.0 );
        csps_Real_t cspsACCnrm = csps_Real_s( 0.0 );

        /* Data buffers */
        csps_Real_t * cspsDEVacx = NULL;
        csps_Real_t * cspsDEVacy = NULL;
        csps_Real_t * cspsDEVacz = NULL;
        csps_Real_t * cspsDEVgrx = NULL;
        csps_Real_t * cspsDEVgry = NULL;
        csps_Real_t * cspsDEVgrz = NULL;
        csps_Time_t * cspsDEVsyn = NULL;

        /* Obtain stream size */
        cspsSize = csps_stream_size( cspsPath, CSPS_IMU_MODGA_DEV, cspsName, cspsPS__, "syn" ) / sizeof( csps_Time_t );

        /* Read streams data */
        cspsDEVacx = csps_stream_read( cspsPath, CSPS_IMU_MODGA_DEV, cspsName, cspsPS__, "acx", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVacy = csps_stream_read( cspsPath, CSPS_IMU_MODGA_DEV, cspsName, cspsPS__, "acy", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVacz = csps_stream_read( cspsPath, CSPS_IMU_MODGA_DEV, cspsName, cspsPS__, "acz", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVgrx = csps_stream_read( cspsPath, CSPS_IMU_MODGA_DEV, cspsName, cspsPS__, "grx", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVgry = csps_stream_read( cspsPath, CSPS_IMU_MODGA_DEV, cspsName, cspsPS__, "gry", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVgrz = csps_stream_read( cspsPath, CSPS_IMU_MODGA_DEV, cspsName, cspsPS__, "grz", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVsyn = csps_stream_read( cspsPath, CSPS_IMU_MODGA_DEV, cspsName, cspsPS__, "syn", sizeof( csps_Time_t ) * cspsSize );

        /* Downsampling procedure */
        while ( cspsParse < ( csps_Size_s( 5 ) * cspsDevice.dvdfreq ) ) {

            /* Accelerometer signal accumulation */
            cspsACCacx += cspsDEVacx[cspsParse];
            cspsACCacy += cspsDEVacy[cspsParse];
            cspsACCacz += cspsDEVacz[cspsParse];

            /* Gyroscope signal accumulation */
            cspsACCgrx += cspsDEVgrx[cspsParse];
            cspsACCgry += cspsDEVgry[cspsParse];
            cspsACCgrz += cspsDEVgrz[cspsParse];

            /* Update parse index */
            cspsParse += csps_Size_s( 1 );

        }

        /* Accelerometer accumulation average */
        cspsACCacx /= cspsParse;
        cspsACCacy /= cspsParse;
        cspsACCacz /= cspsParse;

        /* Compute average acceleration norm */
        cspsACCnrm = sqrt( cspsACCacx * cspsACCacx + cspsACCacy * cspsACCacy + cspsACCacz * cspsACCacz );

        /* Normalize acceleration vector */
        cspsACCacx /= cspsACCnrm;
        cspsACCacy /= cspsACCnrm;
        cspsACCacz /= cspsACCnrm;

        /* Gyroscope accumulation average */
        cspsACCgrx /= cspsParse;
        cspsACCgry /= cspsParse;
        cspsACCgrz /= cspsParse;

        /* Compute average acceleration norm */
        cspsACCnrm = sqrt( cspsACCgrx * cspsACCgrx + cspsACCgry * cspsACCgry + cspsACCgrz * cspsACCgrz );

        /* Normalize acceleration vector */
        cspsACCgrx /= cspsACCnrm;
        cspsACCgry /= cspsACCnrm;
        cspsACCgrz /= cspsACCnrm;

        /* Align z-vector to gravity reaction */
        cspsDevice.dvfzx = + cspsACCacx;
        cspsDevice.dvfzy = + cspsACCacy;
        cspsDevice.dvfzz = + cspsACCacz;

        /* Align x-vector to gravity/earth rate normal */
        cspsDevice.dvfyx = - cspsACCacy * cspsACCgrz + cspsACCacz * cspsACCgry;
        cspsDevice.dvfyy = - cspsACCacz * cspsACCgrx + cspsACCacx * cspsACCgrz;
        cspsDevice.dvfyz = - cspsACCacx * cspsACCgry + cspsACCacy * cspsACCgrx;

        /* Align y-vector to x-z crossed product */
        cspsDevice.dvfxx = - cspsDevice.dvfyy * cspsDevice.dvfzz + cspsDevice.dvfyz * cspsDevice.dvfzy;
        cspsDevice.dvfxy = - cspsDevice.dvfyz * cspsDevice.dvfzx + cspsDevice.dvfyx * cspsDevice.dvfzz;
        cspsDevice.dvfxz = - cspsDevice.dvfyx * cspsDevice.dvfzy + cspsDevice.dvfyy * cspsDevice.dvfzx;

        /* Unallocate buffer memory */
        free( cspsDEVacx );
        free( cspsDEVacy );
        free( cspsDEVacz );
        free( cspsDEVgrx );
        free( cspsDEVgry );
        free( cspsDEVgrz );
        free( cspsDEVsyn );

        /* Return device descriptor */
        return( cspsDevice );

    }

