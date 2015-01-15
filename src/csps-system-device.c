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

    # include "csps-system-device.h"

/*
    Source - Camera devices interface
 */

    lp_Void_t lp_system_device_cam(

        lp_Stack_t * const lpStack,
        FILE       * const lpStream

    ) {

        /* String token variables */
        lp_Char_t lpToken[3][LP_STR_LEN] = { LP_STR_INI };

        /* Device allocation pointer */
        lp_Camera_t * lpCamera = LP_NULL;

        /* Token parser */
        do {

            /* Read token from stream */
            lp_system_token( lpStream, lpToken[0] );

            /* String token analysis */
            if ( strcmp( lpToken[0], LP_SYSTEM_NAME ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[1] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_TAG ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[2] );

            }

        /* End condition on end-keyword */
        } while ( strcmp( lpToken[0], LP_SYSTEM_END ) != 0 );

        /* Push device on stack */
        if ( ( lpCamera = ( lp_Camera_t * ) lp_system_stack_push( lpStack, LP_SYSTEM_TYPE_CAM ) ) != LP_NULL ) {

            /* Create camera device */
            * lpCamera = lp_device_camera( lpToken[1], lpToken[2] );

        }

    }

/*
    Source - GPS recievers interface
 */

    lp_Void_t lp_system_device_gps(

        lp_Stack_t * const lpStack,
        FILE       * const lpStream

    ) {

        /* String token variables */
        lp_Char_t lpToken[3][LP_STR_LEN] = { LP_STR_INI };

        /* Device allocation pointer */
        lp_GPS_t * lpGPS = LP_NULL;

        /* Token parser */
        do {

            /* Read token from stream */
            lp_system_token( lpStream, lpToken[0] );

            /* String token analysis */
            if ( strcmp( lpToken[0], LP_SYSTEM_NAME ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[1] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_TAG ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[2] );

            }

        /* End condition on end-keyword */
        } while ( strcmp( lpToken[0], LP_SYSTEM_END ) != 0 );

        /* Push device on stack */
        if ( ( lpGPS = ( lp_GPS_t * ) lp_system_stack_push( lpStack, LP_SYSTEM_TYPE_GPS ) ) != LP_NULL ) {

            /* Create camera device */
            * lpGPS = lp_device_GPS( lpToken[1], lpToken[2] );

        }

    }

/*
    Source - IMU sensor interface
 */

    lp_Void_t lp_system_device_imu(

        lp_Stack_t * const lpStack,
        FILE       * const lpStream

    ) {

        /* String token variables */
        lp_Char_t lpToken[3][LP_STR_LEN] = { LP_STR_INI };

        /* Device allocation pointer */
        lp_IMU_t * lpIMU = LP_NULL;

        /* Token parser */
        do {

            /* Read token from stream */
            lp_system_token( lpStream, lpToken[0] );

            /* String token analysis */
            if ( strcmp( lpToken[0], LP_SYSTEM_NAME ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[1] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_TAG ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[2] );

            }

        /* End condition on end-keyword */
        } while ( strcmp( lpToken[0], LP_SYSTEM_END ) != 0 );

        /* Push device on stack */
        if ( ( lpIMU = ( lp_IMU_t * ) lp_system_stack_push( lpStack, LP_SYSTEM_TYPE_IMU ) ) != LP_NULL ) {

            /* Create camera device */
            * lpIMU = lp_device_IMU( lpToken[1], lpToken[2] );

        }

    }

