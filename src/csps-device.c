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
    Source - CAM device descriptor initializer
 */

    lp_Camera_t lp_device_camera( 

        lp_Char_t const * const lpName, 
        lp_Char_t const * const lpTag

    ) {

        /* CAM device structure */
        lp_Camera_t lpDevice;

        /* Detect type of camera */
        if ( 

            ( strcmp( lpName, LP_DEVICE_EYESIS4PI       ) == 0 ) ||
            ( strcmp( lpName, LP_DEVICE_NC353L369IMUGPS ) == 0 )

        ) {

            /* Assign device type name */
            sprintf( lpDevice.dvType, "%s", LP_DEVICE_TYPE_CAM );

            /* Assign device model name */
            sprintf( lpDevice.dvName, "%s", LP_DEVICE_EYESIS4PI );

            /* Assign device name */
            sprintf( lpDevice.dvTag, "%s", lpTag );

        }

        /* Assign configuration - Importation block size */
        lpDevice.dvBlock = lp_Size_s( 1024 );

        /* Return device structure */
        return( lpDevice );

    }

/*
    Source - IMU device descriptor initializer
 */

    lp_IMU_t lp_device_IMU( 

        lp_Char_t const * const lpName, 
        lp_Char_t const * const lpTag

    ) {

        /* IMU device structure */
        lp_IMU_t lpDevice;

        /* Detect type of IMU */
        if ( strcmp( lpName, LP_DEVICE_ADIS16375 ) == 0 ) {

            /* Assign device type name */
            sprintf( lpDevice.dvType, "%s", LP_DEVICE_TYPE_IMU );

            /* Assign device model name */
            sprintf( lpDevice.dvName, "%s", LP_DEVICE_ADIS16375 );

            /* Assign device name */
            sprintf( lpDevice.dvTag, "%s", lpTag );

            /* Assign configuration - Gyroscope */
            lpDevice.dvGYRx = ( lp_Real_s( 0.013108 ) / lp_Real_s( 65536.0 ) ) * ( LP_PI / lp_Real_s( 180.0 ) );
            lpDevice.dvGYRy = ( lp_Real_s( 0.013108 ) / lp_Real_s( 65536.0 ) ) * ( LP_PI / lp_Real_s( 180.0 ) );
            lpDevice.dvGYRz = ( lp_Real_s( 0.013108 ) / lp_Real_s( 65536.0 ) ) * ( LP_PI / lp_Real_s( 180.0 ) );

            /* Assign configuration - Accelerometre */
            lpDevice.dvACCx = ( lp_Real_s( 0.8192 ) * lp_Real_s( 9.80665 ) ) / ( lp_Real_s( 65536000.0 ) );
            lpDevice.dvACCy = ( lp_Real_s( 0.8192 ) * lp_Real_s( 9.80665 ) ) / ( lp_Real_s( 65536000.0 ) );
            lpDevice.dvACCz = ( lp_Real_s( 0.8192 ) * lp_Real_s( 9.80665 ) ) / ( lp_Real_s( 65536000.0 ) );

            /* Assign configuration - Frequency */
            lpDevice.dvifreq = lp_Size_s( 2460 );
            lpDevice.dvdfreq = lp_Size_s(   60 );

        }

        /* Assign configuration - ISR configuration */
        lpDevice.dvISRmax = lp_Size_s(  256 );
        lpDevice.dvISRacc = lp_Size_s(   32 );
        lpDevice.dvISRgrt = lp_Real_s( 0.05 );
        lpDevice.dvISRact = lp_Real_s( 0.50 );

        /* Assign configuration - Initial condition rotation */
        lpDevice.dvICRx = lp_Real_s( 0.0 );
        lpDevice.dvICRy = lp_Real_s( 0.0 );
        lpDevice.dvICRz = lp_Real_s( 0.0 );

        /* Assign configuration - Importation block size */
        lpDevice.dvBlock = lp_Size_s( 1024 );

        /* Return device structure */
        return( lpDevice );

    }

/*
    Source - GPS device descriptor initializer
 */

    lp_GPS_t lp_device_GPS( 

        lp_Char_t const * const lpName, 
        lp_Char_t const * const lpTag 

    ) {

        /* GPS device structure */
        lp_GPS_t lpDevice;

        /* Detect type of GPS */
        if ( strcmp( lpName, LP_DEVICE_LS20031 ) == 0 ) {

            /* Assign device type name */
            sprintf( lpDevice.dvType, "%s", LP_DEVICE_TYPE_GPS );

            /* Assign device model name */
            sprintf( lpDevice.dvName, "%s", LP_DEVICE_LS20031 );

            /* Assign device name */
            sprintf( lpDevice.dvTag, "%s", lpTag );

            /* Assign configuration - Frequency */
            lpDevice.dvifreq = lp_Size_s( 5 );

        }

        /* Assign configuration - Importation block size */
        lpDevice.dvBlock = lp_Size_s( 1024 );

        /* Return device structure */
        return( lpDevice );

    }

