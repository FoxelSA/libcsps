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

    # include "csps-imu-modga.h"

/*
    Source - Gravity alignment procedure
 */

    csps_IMU csps_imu_modga(

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
        csps_Real_t cspsACCnrm = csps_Real_s( 0.0 );

        /* Data buffers */
        csps_Real_t * cspsDEVacx = NULL;
        csps_Real_t * cspsDEVacy = NULL;
        csps_Real_t * cspsDEVacz = NULL;
        csps_Time_t * cspsDEVsyn = NULL;

        /* Obtain stream size */
        cspsSize = csps_stream_size( cspsPath, CSPS_IMU_MODGA_DEV, cspsName, cspsPS__, "syn" ) / sizeof( csps_Time_t );

        /* Read streams data */
        cspsDEVacx = csps_stream_read( cspsPath, CSPS_IMU_MODGA_DEV, cspsName, cspsPS__, "acx", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVacy = csps_stream_read( cspsPath, CSPS_IMU_MODGA_DEV, cspsName, cspsPS__, "acy", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVacz = csps_stream_read( cspsPath, CSPS_IMU_MODGA_DEV, cspsName, cspsPS__, "acz", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVsyn = csps_stream_read( cspsPath, CSPS_IMU_MODGA_DEV, cspsName, cspsPS__, "syn", sizeof( csps_Time_t ) * cspsSize );

        /* Downsampling procedure */
        while ( cspsParse < ( csps_Size_s( 5 ) * cspsDevice.dvdfreq ) ) {

            /* Acceleration accumulation */
            cspsACCacx += cspsDEVacx[cspsParse];
            cspsACCacy += cspsDEVacy[cspsParse];
            cspsACCacz += cspsDEVacz[cspsParse];

            /* Update parse index */
            cspsParse += csps_Size_s( 1 );

        }

        /* Acceleration accumulation average */
        cspsACCacx /= cspsParse;
        cspsACCacy /= cspsParse;
        cspsACCacz /= cspsParse;

        /* Compute average acceleration norm */
        cspsACCnrm = sqrt( cspsACCacx * cspsACCacx + cspsACCacy * cspsACCacy + cspsACCacz * cspsACCacz );

        /* Initial frame generate - z-vector */
        cspsDevice.dvfzx = + cspsACCacx / cspsACCnrm;
        cspsDevice.dvfzy = + cspsACCacy / cspsACCnrm;
        cspsDevice.dvfzz = + cspsACCacz / cspsACCnrm;

        /* Initial frame generate - x-vector */
        cspsDevice.dvfxx = + cspsDevice.dvfzy;
        cspsDevice.dvfxy = - cspsDevice.dvfzx;
        cspsDevice.dvfxz = + csps_Real_s( 0.0 );

        /* Vector renormalization x-vector */
        cspsACCnrm = sqrt( cspsDevice.dvfxx * cspsDevice.dvfxx + cspsDevice.dvfxy * cspsDevice.dvfxy + cspsDevice.dvfxz * cspsDevice.dvfxz );

        /* Vector renormalization x-vector */
        cspsDevice.dvfxx /= cspsACCnrm;
        cspsDevice.dvfxy /= cspsACCnrm;
        cspsDevice.dvfxz /= cspsACCnrm;

        /* Initial frame generate - y-vector */
        cspsDevice.dvfyx = cspsDevice.dvfzy * cspsDevice.dvfxz - cspsDevice.dvfzz * cspsDevice.dvfxy;
        cspsDevice.dvfyy = cspsDevice.dvfzz * cspsDevice.dvfxx - cspsDevice.dvfzx * cspsDevice.dvfxz;
        cspsDevice.dvfyz = cspsDevice.dvfzx * cspsDevice.dvfxy - cspsDevice.dvfzy * cspsDevice.dvfxx;

        /* Unallocate buffer memory */
        free( cspsDEVacx );
        free( cspsDEVacy );
        free( cspsDEVacz );
        free( cspsDEVsyn );

        /* Return device descriptor */
        return( cspsDevice );

    }

