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

    # include "csps-system-module.h"

/*
    Source - DSIDE modules interface
 */

    lp_Void_t lp_system_module_cam_DSIDE(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        FILE             * const lpStream

    ) {

        /* String token variables */
        lp_Char_t lpToken[2][LP_STR_LEN] = { LP_STR_INI };

        /* Block size variables */
        lp_Size_t lpBlock = lp_Size_s( 1024 );

        /* Camera descriptor pointer */
        lp_Camera_t * lpDevice = LP_NULL;

        /* Token parser */
        do {

            /* Read token from stream */
            lp_system_token( lpStream, lpToken[0] );

            /* String token analysis */
            if ( strcmp( lpToken[0], LP_SYSTEM_DEVTAG ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[1] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_BLOCK ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[0] );

                /* Convert parameter token */
                lpBlock = lp_Size_r( lpToken[0] );

            }

        /* End condition on end-keyword */
        } while ( strcmp( lpToken[0], LP_SYSTEM_END ) != 0 );

        /* Search device by tag */
        if ( ( lpDevice = ( lp_Camera_t * ) lp_system_stack_bytag( lpStack, LP_SYSTEM_TYPE_CAM, lpToken[1] ) ) != LP_NULL ) {

            /* Module operation */
            lp_cam_mod_DSIDE( lpPath, * lpDevice, lpBlock );

        }

    }

    lp_Void_t lp_system_module_gps_DSIDE(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        FILE             * const lpStream

    ) {

        /* String token variables */
        lp_Char_t lpToken[2][LP_STR_LEN] = { LP_STR_INI };

        /* Block size variables */
        lp_Size_t lpBlock = lp_Size_s( 1024 );

        /* Camera descriptor pointer */
        lp_GPS_t * lpDevice = LP_NULL;

        /* Token parser */
        do {

            /* Read token from stream */
            lp_system_token( lpStream, lpToken[0] );

            /* String token analysis */
            if ( strcmp( lpToken[0], LP_SYSTEM_DEVTAG ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[1] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_BLOCK ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[0] );

                /* Convert parameter token */
                lpBlock = lp_Size_r( lpToken[0] );

            }

        /* End condition on end-keyword */
        } while ( strcmp( lpToken[0], LP_SYSTEM_END ) != 0 );

        /* Search device by tag */
        if ( ( lpDevice = ( lp_GPS_t * ) lp_system_stack_bytag( lpStack, LP_SYSTEM_TYPE_GPS, lpToken[1] ) ) != LP_NULL ) {

            /* Module operation */
            lp_gps_mod_DSIDE( lpPath, * lpDevice, lpBlock );

        }

    }

    lp_Void_t lp_system_module_imu_DSIDE(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        FILE             * const lpStream

    ) {

        /* String token variables */
        lp_Char_t lpToken[2][LP_STR_LEN] = { LP_STR_INI };

        /* Block size variables */
        lp_Size_t lpBlock = lp_Size_s( 1024 );

        /* Camera descriptor pointer */
        lp_IMU_t * lpDevice = LP_NULL;

        /* Token parser */
        do {

            /* Read token from stream */
            lp_system_token( lpStream, lpToken[0] );

            /* String token analysis */
            if ( strcmp( lpToken[0], LP_SYSTEM_DEVTAG ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[1] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_BLOCK ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[0] );

                /* Convert parameter token */
                lpBlock = lp_Size_r( lpToken[0] );

            }

        /* End condition on end-keyword */
        } while ( strcmp( lpToken[0], LP_SYSTEM_END ) != 0 );

        /* Search device by tag */
        if ( ( lpDevice = ( lp_IMU_t * ) lp_system_stack_bytag( lpStack, LP_SYSTEM_TYPE_IMU, lpToken[1] ) ) != LP_NULL ) {

            /* Module operation */
            lp_imu_mod_DSIDE( lpPath, * lpDevice, lpBlock );

        }

    }

/*
    Source - GPS reciever module interface
 */

    lp_Void_t lp_system_module_gps_SGNQF(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        FILE             * const lpStream

    ) {

        /* String token variables */
        lp_Char_t lpToken[3][LP_STR_LEN] = { LP_STR_INI };

        /* Camera descriptor pointer */
        lp_GPS_t * lpDevice = LP_NULL;

        /* Token parser */
        do {

            /* Read token from stream */
            lp_system_token( lpStream, lpToken[0] );

            /* String token analysis */
            if ( strcmp( lpToken[0], LP_SYSTEM_DEVTAG ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[1] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_INPUT ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[2] );

            }

        /* End condition on end-keyword */
        } while ( strcmp( lpToken[0], LP_SYSTEM_END ) != 0 );

        /* Search device by tag */
        if ( ( lpDevice = ( lp_GPS_t * ) lp_system_stack_bytag( lpStack, LP_SYSTEM_TYPE_GPS, lpToken[1] ) ) != LP_NULL ) {

            /* Module operation */
            lp_gps_mod_SGNQF( lpPath, * lpDevice, lpToken[2] );

        }

    }

