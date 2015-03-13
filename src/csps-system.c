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

    # include "csps-system.h"

/*
    Source - CSPS topology parser
 */

    lp_Enum_t lp_system(

        lp_Char_t const * const lpPath

    ) {

        /* String token variables */
        lp_Char_t lpToken[LP_STR_LEN] = LP_STR_INI;

        /* Topology file variables */
        lp_Char_t lpTopo[LP_STR_LEN] = { '\0' };

        /* Device stack variables */
        lp_Stack_t lpStack;

        /* Input stream handle variables */
        FILE * lpStream = NULL;

        /* Create input stream handle */
        if ( ( lpStream = fopen( lp_path_topology( lpPath, lpTopo ), "r" ) ) == NULL ) {

            /* Return failure state */
            return( LP_FALSE );

        } else {

            /* Create device stack */
            lp_system_stack_create( & lpStack );

            /* Topology file parsing */
            while ( lp_system_token( lpStream, lpToken ) != NULL ) {

                /* Token analysis */
                if ( strcmp( lpToken, LP_SYSTEM_DEVICE ) == 0 ) {

                    /* Read secondary token */
                    lp_system_token( lpStream, lpToken );

                    /* Secondary token analysis */
                    if ( strcmp( lpToken, LP_SYSTEM_CAM ) == 0 ) {

                        /* Specific device parser */
                        lp_system_device_cam( & lpStack, lpStream );

                    } else
                    if ( strcmp( lpToken, LP_SYSTEM_GPS ) == 0 ) {

                        /* Specific device parser */
                        lp_system_device_gps( & lpStack, lpStream );

                    } else
                    if ( strcmp( lpToken, LP_SYSTEM_IMU ) == 0 ) {

                        /* Specific device parser */
                        lp_system_device_imu( & lpStack, lpStream );

                    }

                } else
                if ( strcmp( lpToken, LP_SYSTEM_MODULE ) == 0 ) {

                    /* Read secondary token */
                    lp_system_token( lpStream, lpToken );

                    /* Secondary token analysis */
                    if ( strcmp( lpToken, LP_DEVICE_TYPE_CAM "-" LP_CAM_DSIDE_MOD ) == 0 ) {

                        /* Specific module parser */
                        lp_system_module_cam_DSIDE( lpPath, & lpStack, lpStream );

                    } else
                    if ( strcmp( lpToken, LP_DEVICE_TYPE_GPS "-" LP_GPS_DSIDE_MOD ) == 0 ) {

                        /* Specific module parser */
                        lp_system_module_gps_DSIDE( lpPath, & lpStack, lpStream );

                    } else
                    if ( strcmp( lpToken, LP_DEVICE_TYPE_IMU "-" LP_IMU_DSIDE_MOD ) == 0 ) {

                        /* Specific module parser */
                        lp_system_module_imu_DSIDE( lpPath, & lpStack, lpStream );

                    } else
                    if ( strcmp( lpToken, LP_DEVICE_TYPE_GPS "-" LP_GPS_SGNQF_MOD ) == 0 ) {

                        /* Specific module parser */
                        lp_system_module_gps_SGNQF( lpPath, & lpStack, lpStream );

                    } else
                    if ( strcmp( lpToken, LP_DEVICE_TYPE_IMU "-" LP_IMU_SGSFR_MOD ) == 0 ) {

                        /* Specific module parser */
                        lp_system_module_imu_SGSFR( lpPath, & lpStack, lpStream );

                    } else
                    if ( strcmp( lpToken, LP_DEVICE_TYPE_IMU "-" LP_IMU_SGNDN_MOD ) == 0 ) {

                        /* Specific module parser */
                        lp_system_module_imu_SGNDN( lpPath, & lpStack, lpStream );

                    } else
                    if ( strcmp( lpToken, LP_DEVICE_TYPE_IMU "-" LP_IMU_ISRAD_MOD ) == 0 ) {

                        /* Specific module parser */
                        lp_system_module_imu_ISRAD( lpPath, & lpStack, lpStream );

                    } else
                    if ( strcmp( lpToken, LP_DEVICE_TYPE_IMU "-" LP_IMU_IOISA_MOD ) == 0 ) {

                        /* Specific module parser */
                        lp_system_module_imu_IOISA( lpPath, & lpStack, lpStream );

                    } else
                    if ( strcmp( lpToken, LP_DEVICE_TYPE_IMU "-" LP_IMU_IOBMA_MOD ) == 0 ) {

                        /* Specific module parser */
                        lp_system_module_imu_IOBMA( lpPath, & lpStack, lpStream );

                    } else
                    if ( strcmp( lpToken, LP_DEVICE_TYPE_IMU "-" LP_IMU_IFICR_MOD ) == 0 ) {

                        /* Specific module parser */
                        lp_system_module_imu_IFICR( lpPath, & lpStack, lpStream );

                    } else
                    if ( strcmp( lpToken, LP_DEVICE_TYPE_IMU "-" LP_IMU_IFETI_MOD ) == 0 ) {

                        /* Specific module parser */
                        lp_system_module_imu_IFETI( lpPath, & lpStack, lpStream );

                    } else
                    if ( strcmp( lpToken, LP_DEVICE_TYPE_IMU "-" LP_IMU_AACEX_MOD ) == 0 ) {

                        /* Specific module parser */
                        lp_system_module_imu_AACEX( lpPath, & lpStack, lpStream );

                    }

                } else {

                    /* Search end token */
                    while ( strcmp( lp_system_token( lpStream, lpToken ), LP_SYSTEM_END ) != 0 );

                }

                /* Clear token */
                memset( lpToken, 0, LP_STR_LEN );
                
            }

            /* Delete device stack */
            lp_system_stack_delete( & lpStack );

            /* Delete input stream handle */
            fclose( lpStream );

        }

        /* Return success state */
        return( LP_TRUE );

    }

/*
    Source - CSPS origin directive parser
 */

    lp_Enum_t lp_system_origin( 

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpOrigin,
        lp_Char_t       * const lpDevice,
        lp_Char_t       * const lpModule

    ) {

        /* String token variables */
        lp_Char_t lpToken[LP_STR_LEN] = { '\0' };

        /* Topology file variables */
        lp_Char_t lpTopo[LP_STR_LEN] = { '\0' };

        /* Returned variables */
        lp_Enum_t lpReturn = LP_FALSE;

        /* Stream variables */
        FILE * lpStream = NULL;

        /* Create input stream */
        if ( ( lpStream = fopen( lp_path_topology( lpPath, lpTopo ), "r" ) ) != NULL ) {

            /* Parsing topology file */
            while ( ( lp_system_token( lpStream, lpToken ) != NULL ) && ( lpReturn == LP_FALSE ) ) {

                /* Detect origin directive */
                if ( strcmp( lpToken, LP_SYSTEM_ORIGIN ) == 0 ) {

                    /* Detect origin directive type */
                    if ( strcmp( lp_system_token( lpStream, lpToken ), lpOrigin ) == 0 ) {

                        /* Read origin device and module */
                        lp_system_token( lpStream, lpDevice );
                        lp_system_token( lpStream, lpModule );

                        /* Verify origin directive consistency */
                        if ( strcmp( lp_system_token( lpStream, lpToken ), LP_SYSTEM_END ) == 0 ) {

                            /* Update status */
                            lpReturn = LP_TRUE;

                        }

                    }

                }

            }

            /* Close input stream */
            fclose( lpStream );

        }

        /* Return status */
        return( lpReturn );

    }

