/*
 * libcsps - Crossed-signal positioning system library
 *
 * Copyright (c) 2013-2015 FOXEL SA - http://foxel.ch
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

    # include "csps-device-imu.h"

/*
    Source - IMU device structure creator
 */

    lp_IMU_t lp_device_IMU( 

        lp_Char_t const * const lpName, 
        lp_Char_t const * const lpTag

    ) {

        /* IMU device structure */
        lp_IMU_t lpDevice;

        /* Detect type of IMU */
        if ( strcmp( lpName, LP_DEVICE_ADIS16375 ) == 0 ) {

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

        }

        /* Return device structure */
        return( lpDevice );

    }

