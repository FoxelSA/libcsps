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

    # include "csps-device.h"

/*
    Source - CAM device builder
 */

    csps_CAM csps_device_CAM( const csps_Char_t * const cspsName ) {

        /* CAM device structure */
        csps_CAM cspsDevice;

        /* Detect type of camera */
        if ( strcmp( cspsName, CSPS_DEVICE_CAM_EYESIS4PI ) == 0 ) {

            /* Assign device name */
            sprintf( cspsDevice.dvName, "%s", CSPS_DEVICE_CAM_EYESIS4PI );

            /* Assign configuration - Importation block size */
            cspsDevice.dvBlock = csps_Size_s( 1024 );

        }

        /* Return device structure */
        return( cspsDevice );

    }

/*
    Source - IMU device builder
 */

    csps_IMU csps_device_IMU( const csps_Char_t * const cspsName ) {

        /* IMU device structure */
        csps_IMU cspsDevice;

        /* Detect type of IMU */
        if ( strcmp( cspsName, CSPS_DEVICE_IMU_ADIS16375 ) == 0 ) {

            /* Assign device name */
            sprintf( cspsDevice.dvName, "%s", CSPS_DEVICE_IMU_ADIS16375 );

            /* Assign configuration - Gyroscope */
            cspsDevice.dvGYRx = ( csps_Real_s( 0.013108 ) / csps_Real_s( 65536.0 ) ) * ( CSPS_PI / csps_Real_s( 180.0 ) );
            cspsDevice.dvGYRy = ( csps_Real_s( 0.013108 ) / csps_Real_s( 65536.0 ) ) * ( CSPS_PI / csps_Real_s( 180.0 ) );
            cspsDevice.dvGYRz = ( csps_Real_s( 0.013108 ) / csps_Real_s( 65536.0 ) ) * ( CSPS_PI / csps_Real_s( 180.0 ) );

            /* Assign configuration - Accelerometre */
            cspsDevice.dvACCx = ( csps_Real_s( 0.8192 ) * csps_Real_s( 9.80665 ) ) / ( csps_Real_s( 65536000.0 ) );
            cspsDevice.dvACCy = ( csps_Real_s( 0.8192 ) * csps_Real_s( 9.80665 ) ) / ( csps_Real_s( 65536000.0 ) );
            cspsDevice.dvACCz = ( csps_Real_s( 0.8192 ) * csps_Real_s( 9.80665 ) ) / ( csps_Real_s( 65536000.0 ) );

            /* Assign configuration - Default initial frame */
            cspsDevice.dvfxx = csps_Real_s( 1.0 );
            cspsDevice.dvfxy = csps_Real_s( 0.0 );
            cspsDevice.dvfxz = csps_Real_s( 0.0 );
            cspsDevice.dvfyx = csps_Real_s( 0.0 );
            cspsDevice.dvfyy = csps_Real_s( 1.0 );
            cspsDevice.dvfyz = csps_Real_s( 0.0 );
            cspsDevice.dvfzx = csps_Real_s( 0.0 );
            cspsDevice.dvfzy = csps_Real_s( 0.0 );
            cspsDevice.dvfzz = csps_Real_s( 1.0 );

            /* Assign configuration - Frequency */
            cspsDevice.dvifreq = csps_Size_s( 2460 );
            cspsDevice.dvdfreq = csps_Size_s(   60 );

            /* Assign configuration - Importation block size */
            cspsDevice.dvBlock = csps_Size_s( 1024 );

        }

        /* Return device structure */
        return( cspsDevice );

    }

/*
    Source - GPS device builder
 */

    csps_GPS csps_device_GPS( const csps_Char_t * const cspsName ) {

        /* GPS device structure */
        csps_GPS cspsDevice;

        /* Detect type of GPS */
        if ( strcmp( cspsName, CSPS_DEVICE_GPS_LS20031 ) == 0 ) {

            /* Assign device name */
            sprintf( cspsDevice.dvName, "%s", CSPS_DEVICE_GPS_LS20031 );

            /* Assign configuration - Frequency */
            cspsDevice.dvifreq = csps_Size_s( 5 );

            /* Assign configuration - Importation block size */
            cspsDevice.dvBlock = csps_Size_s( 1024 );

        }

        /* Return device structure */
        return( cspsDevice );

    }

