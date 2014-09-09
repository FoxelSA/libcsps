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

    # include "csps-system.h"

/*
    Source - CSPS topology interpreter
 */

    lp_Void_t lp_system(

        const lp_Char_t * const lpPath,
        const lp_Char_t * const lpFile

    ) {

        /* Device types stack variables */
        lp_Enum_t lpTypes[LP_SYSTEM_DEVICE] = { lp_Enum_s( 0 ) };

        /* Device descriptors stack variables */
        lp_Void_t * lpDescs[LP_SYSTEM_DEVICE] = { LP_NULL };

        /* Device stack index variables */
        lp_Size_t lpIndex = lp_Size_s( 0 );

        /* File token variables */
        lp_Char_t lpToken[LP_SYSTEM_TOKEN][LP_STR_LEN] = { { '\0' } };

        /* Reading mode variables */
        lp_Enum_t lpMode = LP_SYSTEM_MODE_MAIN;

        /* File handle variables */
        FILE * lpHandle = LP_NULL;

        /* Open file containing topology */
        if ( ( lpHandle = fopen( lpFile, "r" ) ) != LP_NULL ) {

            /* Read file by token */
            while ( lp_system_token( lpHandle, lpToken[0] ) != LP_NULL ) {

                /* Check current mode */
                if ( lpMode == LP_SYSTEM_MODE_MAIN ) {

                    /* Check token value */
                    if ( strcmp( lpToken[0], LP_SYSTEM_KW_DEVICE ) == 0 ) {

                        /* Update mode */
                        lpMode = LP_SYSTEM_MODE_IDEV;

                    } else 
                    if ( strcmp( lpToken[0], LP_SYSTEM_KW_MODULE ) == 0 ) {

                        /* Update mode */
                        lpMode = LP_SYSTEM_MODE_XMOD;

                    }

                } else {

                    /* Check end of line */
                    if ( strcmp( lpToken[0], LP_SYSTEM_KW_ENDLIN ) == 0 ) {

                        /* Check previous mode */
                        if ( lpMode >= LP_SYSTEM_MODE_ICAM ) lpIndex ++;

                        /* Update mode */
                        lpMode = LP_SYSTEM_MODE_MAIN;

                    } else {

                        /* Check current mode */
                        if ( lpMode == LP_SYSTEM_MODE_IDEV ) {

                            /* Check token value */
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_CAM ) == 0 ) {

                                /* Update mode */
                                lpMode = LP_SYSTEM_MODE_ICAM;

                            } else 
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_GPS ) == 0 ) {

                                /* Update mode */
                                lpMode = LP_SYSTEM_MODE_IGPS;

                            } else 
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_IMU ) == 0 ) {

                                /* Update mode */
                                lpMode = LP_SYSTEM_MODE_IIMU;

                            }

                        } else if ( lpMode == LP_SYSTEM_MODE_XMOD ) {

                            /* Module selection */
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_CAM "-" LP_CAM_DSIDE_MOD ) == 0 ) {

                                /* Search devices */
                                lp_Size_t lpDevCAM = lp_system_device_by_tag( lp_system_token( lpHandle, lpToken[1] ), LP_DEVICE_ID_CAM, lpIndex, lpTypes, lpDescs );

                                /* Module operation */
                                lp_cam_mod_DSIDE( lpPath, * ( ( lp_CAM * ) lpDescs[lpDevCAM] ) );

                            } else 
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_GPS "-" LP_GPS_DSIDE_MOD ) == 0 ) {

                                /* Search devices */
                                lp_Size_t lpDevGPS = lp_system_device_by_tag( lp_system_token( lpHandle, lpToken[1] ), LP_DEVICE_ID_GPS, lpIndex, lpTypes, lpDescs );

                                /* Module operation */
                                lp_gps_mod_DSIDE( lpPath, * ( ( lp_GPS * ) lpDescs[lpDevGPS] ) );

                            } else
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_IMU "-" LP_IMU_DSIDE_MOD ) == 0 ) {

                                /* Search devices */
                                lp_Size_t lpDevIMU = lp_system_device_by_tag( lp_system_token( lpHandle, lpToken[1] ), LP_DEVICE_ID_IMU, lpIndex, lpTypes, lpDescs );

                                /* Module operation */
                                lp_imu_mod_DSIDE( lpPath, * ( ( lp_IMU * ) lpDescs[lpDevIMU] ) );

                            } else
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_GPS "-" LP_GPS_SGNQF_MOD ) == 0 ) {

                                /* Search devices */
                                lp_Size_t lpDevGPS = lp_system_device_by_tag( lp_system_token( lpHandle, lpToken[1] ), LP_DEVICE_ID_GPS, lpIndex, lpTypes, lpDescs );

                                /* Read token */
                                lp_system_token( lpHandle, lpToken[1] );

                                /* Module operation */
                                lp_gps_mod_SGNQF( lpPath, * ( ( lp_GPS * ) lpDescs[lpDevGPS] ), lpToken[1] );

                            } else 
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_IMU "-" LP_IMU_SGSFR_MOD ) == 0 ) {

                                /* Search devices */
                                lp_Size_t lpDevIMU = lp_system_device_by_tag( lp_system_token( lpHandle, lpToken[1] ), LP_DEVICE_ID_IMU, lpIndex, lpTypes, lpDescs );

                                /* Read token */
                                lp_system_token( lpHandle, lpToken[1] );

                                /* Module operation */
                                lp_imu_mod_SGSFR( lpPath, * ( ( lp_IMU * ) lpDescs[lpDevIMU] ), lpToken[1] );

                            } else 
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_IMU "-" LP_IMU_SGNDN_MOD ) == 0 ) {

                                /* Search devices */
                                lp_Size_t lpDevice = lp_system_device_by_tag( lp_system_token( lpHandle, lpToken[1] ), LP_DEVICE_ID_IMU, lpIndex, lpTypes, lpDescs );

                                /* Read token */
                                lp_system_token( lpHandle, lpToken[1] );

                                /* Module operation */
                                lp_imu_mod_SGNDN( lpPath, * ( ( lp_IMU * ) lpDescs[lpDevice] ), lpToken[1] );

                            } else 
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_IMU "-" LP_IMU_ISRAD_MOD ) == 0 ) {

                                /* Search devices */
                                lp_Size_t lpDevIMU = lp_system_device_by_tag( lp_system_token( lpHandle, lpToken[1] ), LP_DEVICE_ID_IMU, lpIndex, lpTypes, lpDescs );

                                /* Read token */
                                lp_system_token( lpHandle, lpToken[1] );

                                /* Module operation */
                                lp_imu_mod_ISRAD( lpPath, * ( ( lp_IMU * ) lpDescs[lpDevIMU] ), lpToken[1] );

                            } else 
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_IMU "-" LP_IMU_IOISA_MOD ) == 0 ) {

                                /* Search devices */
                                lp_Size_t lpDevIMU = lp_system_device_by_tag( lp_system_token( lpHandle, lpToken[1] ), LP_DEVICE_ID_IMU, lpIndex, lpTypes, lpDescs );
                                lp_Size_t lpDevGPS = lp_system_device_by_tag( lp_system_token( lpHandle, lpToken[1] ), LP_DEVICE_ID_GPS, lpIndex, lpTypes, lpDescs );

                                /* Read token */
                                lp_system_token( lpHandle, lpToken[1] );
                                lp_system_token( lpHandle, lpToken[2] );
                                lp_system_token( lpHandle, lpToken[3] );

                                /* Module operation */
                                lp_imu_mod_IOISA( lpPath, * ( ( lp_IMU * ) lpDescs[lpDevIMU] ), * ( ( lp_GPS * ) lpDescs[lpDevGPS] ), lpToken[1], lpToken[2], lpToken[3] );

                            } else 
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_IMU "-" LP_IMU_IFETI_MOD ) == 0 ) {

                                /* Search devices */
                                lp_Size_t lpDevIMU = lp_system_device_by_tag( lp_system_token( lpHandle, lpToken[1] ), LP_DEVICE_ID_IMU, lpIndex, lpTypes, lpDescs );

                                /* Read token */
                                lp_system_token( lpHandle, lpToken[1] );
                                lp_system_token( lpHandle, lpToken[2] );

                                /* Module operation */
                                lp_imu_mod_IFETI( lpPath, * ( ( lp_IMU * ) lpDescs[lpDevIMU] ), lpToken[1], lpToken[2] );

                            } else 
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_IMU "-" LP_IMU_GYLAE_MOD ) == 0 ) {

                                /* Search devices */
                                lp_Size_t lpDevIMU = lp_system_device_by_tag( lp_system_token( lpHandle, lpToken[1] ), LP_DEVICE_ID_IMU, lpIndex, lpTypes, lpDescs );

                                /* Read token */
                                lp_system_token( lpHandle, lpToken[1] );
                                lp_system_token( lpHandle, lpToken[2] );

                                /* Module operation */
                                lp_imu_mod_GYLAE( lpPath, * ( ( lp_IMU * ) lpDescs[lpDevIMU] ), lpToken[1], lpToken[2] );

                            } else 
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_IMU "-" LP_IMU_BAIFA_MOD ) == 0 ) {

                                /* Search devices */
                                lp_Size_t lpDevIMU = lp_system_device_by_tag( lp_system_token( lpHandle, lpToken[1] ), LP_DEVICE_ID_IMU, lpIndex, lpTypes, lpDescs );
                                lp_Size_t lpDevGPS = lp_system_device_by_tag( lp_system_token( lpHandle, lpToken[1] ), LP_DEVICE_ID_GPS, lpIndex, lpTypes, lpDescs );

                                /* Read token */
                                lp_system_token( lpHandle, lpToken[1] );

                                /* Module operation */
                                lp_imu_mod_BAIFA( lpPath, * ( ( lp_IMU * ) lpDescs[lpDevIMU] ), * ( ( lp_GPS * ) lpDescs[lpDevGPS] ), lpToken[1] );

                            }

                        } else if ( lpMode == LP_SYSTEM_MODE_ICAM ) {

                            /* Read token */
                            if ( strcmp( lpToken[0], LP_SYSTEM_KW_DVTYPE ) == 0 ) {

                                /* Assign device type */
                                lpTypes[lpIndex] = LP_DEVICE_ID_CAM;

                                /* Allocate structure memory */
                                lpDescs[lpIndex] = malloc( sizeof( lp_CAM ) );

                                /* Initialize descriptor */
                                * ( ( lp_CAM * ) lpDescs[lpIndex] ) = lp_device_CAM( lp_system_token( lpHandle, lpToken[1] ), LP_DEVICE_TYPE_CAM );

                            } else 
                            if ( strcmp( lpToken[0], LP_SYSTEM_KW_DVTAGS ) == 0 ) {

                                /* Update device tag */
                                sprintf( ( ( lp_CAM * ) lpDescs[lpIndex] )->dvTag, "%s", lp_system_token( lpHandle, lpToken[1] ) );

                            }

                        } else if ( lpMode == LP_SYSTEM_MODE_IGPS ) {

                            /* Read token */
                            if ( strcmp( lpToken[0], LP_SYSTEM_KW_DVTYPE ) == 0 ) {

                                /* Assign device type */
                                lpTypes[lpIndex] = LP_DEVICE_ID_GPS;

                                /* Allocate structure memory */
                                lpDescs[lpIndex] = malloc( sizeof( lp_GPS ) );

                                /* Initialize descriptor */
                                * ( ( lp_GPS * ) lpDescs[lpIndex] ) = lp_device_GPS( lp_system_token( lpHandle, lpToken[1] ), LP_DEVICE_TYPE_GPS );

                            } else 
                            if ( strcmp( lpToken[0], LP_SYSTEM_KW_DVTAGS ) == 0 ) {

                                /* Update device tag */
                                sprintf( ( ( lp_GPS * ) lpDescs[lpIndex] )->dvTag, "%s", lp_system_token( lpHandle, lpToken[1] ) );

                            }

                        } else if ( lpMode == LP_SYSTEM_MODE_IIMU ) {

                            /* Read token */
                            if ( strcmp( lpToken[0], LP_SYSTEM_KW_DVTYPE ) == 0 ) {

                                /* Assign device type */
                                lpTypes[lpIndex] = LP_DEVICE_ID_IMU;

                                /* Allocate structure memory */
                                lpDescs[lpIndex] = malloc( sizeof( lp_IMU ) );

                                /* Initialize descriptor */
                                * ( ( lp_IMU * ) lpDescs[lpIndex] ) = lp_device_IMU( lp_system_token( lpHandle, lpToken[1] ), LP_DEVICE_TYPE_IMU );

                            } else 
                            if ( strcmp( lpToken[0], LP_SYSTEM_KW_DVTAGS ) == 0 ) {

                                /* Update device tag */
                                sprintf( ( ( lp_IMU * ) lpDescs[lpIndex] )->dvTag, "%s", lp_system_token( lpHandle, lpToken[1] ) );

                            }

                        }

                    }

                }

            }

            /* Close file */
            fclose( lpHandle );

            /* Free memory allocations */
            for ( ; lpIndex >= 0 ; lpIndex -- ) free( lpDescs[lpIndex] );

        }

    }

/*
    Source - File token reader
 */

    lp_Char_t * lp_system_token(

        FILE      * lpFile,
        lp_Char_t * lpToken

    ) {

        /* Read token from file */
        if ( fscanf( lpFile, "%s", lpToken ) == 1 ) {

            /* Return token pointer */
            return( lpToken );

        } else {

            /* Return null pointer */
            return( LP_NULL );

        }

    }

/*
    Source - Device search in stack
 */

    lp_Size_t lp_system_device_by_tag(

        const lp_Char_t * const lpTag,
        const lp_Enum_t         lpType,
        lp_Size_t               lpIndex,
        lp_Enum_t *             lpTypes,
        lp_Void_t **            lpDescs

    ) {

        /* Search in devices stack */
        for ( ; lpIndex >= 0; lpIndex -- ) {

            /* Check device type */
            if ( lpTypes[lpIndex] == lpType ) {

                /* Switch on device type */
                if ( lpType == LP_DEVICE_ID_CAM ) {

                    /* Compare device tag to parameter and return index */
                    if ( strcmp( ( ( lp_CAM * ) lpDescs[lpIndex] )->dvTag, lpTag ) == 0 ) return( lpIndex );

                } else
                if ( lpType == LP_DEVICE_ID_GPS ) {

                    /* Compare device tag to parameter and return index */
                    if ( strcmp( ( ( lp_GPS * ) lpDescs[lpIndex] )->dvTag, lpTag ) == 0 ) return( lpIndex );

                } else
                if ( lpType == LP_DEVICE_ID_IMU ) {

                    /* Compare device tag to parameter and return index */
                    if ( strcmp( ( ( lp_IMU * ) lpDescs[lpIndex] )->dvTag, lpTag ) == 0 ) return( lpIndex );

                }

            }

        }

        /* Device not found */
        return( LP_SYSTEM_NODEVICE );

    }

