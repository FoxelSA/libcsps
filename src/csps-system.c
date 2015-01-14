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
    Source - CSPS topology interpreter
 */

    lp_Enum_t lp_system_new(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpFile

    ) {

        /* String token variables */
        lp_Char_t lpToken[LP_STR_LEN] = LP_STR_INI;

        /* Device stack variables */
        lp_Stack_t lpStack;

        /* Input stream handle variables */
        FILE * lpStream = LP_NULL;

        /* Create input stream handle */
        if ( ( lpStream = fopen( lpFile, "r" ) ) == LP_NULL ) {

            /* Return failure state */
            return( LP_FALSE );

        } else {

            /* Create device stack */
            lp_system_stack_create( & lpStack );

            /* Topology file parsing */
            while ( lp_system_token( lpStream, lpToken ) != LP_NULL ) {

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

    lp_Void_t lp_system(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpFile

    ) {

        /* Device types stack variables */
        lp_Enum_t lpTypes[LP_SYSTEM_LIMIT] = { lp_Enum_s( 0 ) };

        /* Device descriptors stack variables */
        lp_Void_t * lpDescs[LP_SYSTEM_LIMIT] = { LP_NULL };

        /* Device stack index variables */
        lp_Size_t lpIndex = lp_Size_s( 0 );

        /* File token variables */
        lp_Char_t lpToken[LP_SYSTEM_TOKEN][LP_STR_LEN] = { { '\0' } };

        /* Reading mode variables */
        lp_Enum_t lpMode = LP_SYSTEM_MODE_MAIN;

        /* File handle variables */
        FILE * lpStream = LP_NULL;

        /* Open file containing topology */
        if ( ( lpStream = fopen( lpFile, "r" ) ) != LP_NULL ) {

            /* Read file by token */
            while ( lp_system_token( lpStream, lpToken[0] ) != LP_NULL ) {

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
                                lp_Size_t lpDevCAM = lp_system_device_by_tag( lp_system_token( lpStream, lpToken[1] ), LP_DEVICE_ID_CAM, lpIndex, lpTypes, lpDescs );

                                /* Read parameters */
                                lp_Size_t lpParam1 = lp_Size_r( lp_system_token( lpStream, lpToken[2] ) );

                                /* Module operation */
                                lp_cam_mod_DSIDE( lpPath, * ( ( lp_Camera_t * ) lpDescs[lpDevCAM] ), lpParam1 );

                            } else 
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_GPS "-" LP_GPS_DSIDE_MOD ) == 0 ) {

                                /* Search devices */
                                lp_Size_t lpDevGPS = lp_system_device_by_tag( lp_system_token( lpStream, lpToken[1] ), LP_DEVICE_ID_GPS, lpIndex, lpTypes, lpDescs );

                                /* Read parameters */
                                lp_Size_t lpParam1 = lp_Size_r( lp_system_token( lpStream, lpToken[2] ) );

                                /* Module operation */
                                lp_gps_mod_DSIDE( lpPath, * ( ( lp_GPS_t * ) lpDescs[lpDevGPS] ), lpParam1 );

                            } else
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_IMU "-" LP_IMU_DSIDE_MOD ) == 0 ) {

                                /* Search devices */
                                lp_Size_t lpDevIMU = lp_system_device_by_tag( lp_system_token( lpStream, lpToken[1] ), LP_DEVICE_ID_IMU, lpIndex, lpTypes, lpDescs );

                                /* Module operation */
                                lp_imu_mod_DSIDE( lpPath, * ( ( lp_IMU_t * ) lpDescs[lpDevIMU] ), 512 );

                            } else
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_GPS "-" LP_GPS_SGNQF_MOD ) == 0 ) {

                                /* Search devices */
                                lp_Size_t lpDevGPS = lp_system_device_by_tag( lp_system_token( lpStream, lpToken[1] ), LP_DEVICE_ID_GPS, lpIndex, lpTypes, lpDescs );

                                /* Read token */
                                lp_system_token( lpStream, lpToken[1] );

                                /* Module operation */
                                lp_gps_mod_SGNQF( lpPath, * ( ( lp_GPS_t * ) lpDescs[lpDevGPS] ), lpToken[1] );

                            } else 
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_IMU "-" LP_IMU_SGSFR_MOD ) == 0 ) {

                                /* Search devices */
                                lp_Size_t lpDevIMU = lp_system_device_by_tag( lp_system_token( lpStream, lpToken[1] ), LP_DEVICE_ID_IMU, lpIndex, lpTypes, lpDescs );

                                /* Read token */
                                lp_system_token( lpStream, lpToken[1] );

                                /* Module operation */
                                lp_imu_mod_SGSFR( lpPath, * ( ( lp_IMU_t * ) lpDescs[lpDevIMU] ), lpToken[1], 1, 1 );

                            } else 
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_IMU "-" LP_IMU_SGNDN_MOD ) == 0 ) {

                                /* Search devices */
                                lp_Size_t lpDevice = lp_system_device_by_tag( lp_system_token( lpStream, lpToken[1] ), LP_DEVICE_ID_IMU, lpIndex, lpTypes, lpDescs );

                                /* Read token */
                                lp_system_token( lpStream, lpToken[1] );

                                /* Module operation */
                                lp_imu_mod_SGNDN( lpPath, * ( ( lp_IMU_t * ) lpDescs[lpDevice] ), lpToken[1] );

                            } else 
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_IMU "-" LP_IMU_ISRAD_MOD ) == 0 ) {

                                /* Search devices */
                                lp_Size_t lpDevIMU = lp_system_device_by_tag( lp_system_token( lpStream, lpToken[1] ), LP_DEVICE_ID_IMU, lpIndex, lpTypes, lpDescs );

                                /* Read token */
                                lp_system_token( lpStream, lpToken[1] );

                                /* Module operation */
                                lp_imu_mod_ISRAD( lpPath, * ( ( lp_IMU_t * ) lpDescs[lpDevIMU] ), lpToken[1], 256, 32, 0.05, 0.50 );

                            } else 
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_IMU "-" LP_IMU_IOISA_MOD ) == 0 ) {

                                /* Search devices */
                                lp_Size_t lpDevIMU = lp_system_device_by_tag( lp_system_token( lpStream, lpToken[1] ), LP_DEVICE_ID_IMU, lpIndex, lpTypes, lpDescs );

                                /* Read token */
                                lp_system_token( lpStream, lpToken[1] );
                                lp_system_token( lpStream, lpToken[2] );

                                /* Module operation */
                                lp_imu_mod_IOISA( lpPath, * ( ( lp_IMU_t * ) lpDescs[lpDevIMU] ), lpToken[1], lpToken[2] );

                            } else 
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_IMU "-" LP_IMU_IFETI_MOD ) == 0 ) {

                                /* Search devices */
                                lp_Size_t lpDevIMU = lp_system_device_by_tag( lp_system_token( lpStream, lpToken[1] ), LP_DEVICE_ID_IMU, lpIndex, lpTypes, lpDescs );

                                /* Read token */
                                lp_system_token( lpStream, lpToken[1] );
                                lp_system_token( lpStream, lpToken[2] );

                                /* Module operation */
                                lp_imu_mod_IFETI( lpPath, * ( ( lp_IMU_t * ) lpDescs[lpDevIMU] ), lpToken[1], lpToken[2] );

                            } else 
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_IMU "-" LP_IMU_AACEX_MOD ) == 0 ) {

                                /* Search devices */
                                lp_Size_t lpDevIMU = lp_system_device_by_tag( lp_system_token( lpStream, lpToken[1] ), LP_DEVICE_ID_IMU, lpIndex, lpTypes, lpDescs );

                                /* Read token */
                                lp_system_token( lpStream, lpToken[1] );
                                lp_system_token( lpStream, lpToken[2] );

                                /* Module operation */
                                lp_imu_mod_AACEX( lpPath, * ( ( lp_IMU_t * ) lpDescs[lpDevIMU] ), lpToken[1], lpToken[2] );

                            } else 
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_IMU "-" LP_IMU_IOBMA_MOD ) == 0 ) {

                                /* Search devices */
                                lp_Size_t lpDevIMU = lp_system_device_by_tag( lp_system_token( lpStream, lpToken[1] ), LP_DEVICE_ID_IMU, lpIndex, lpTypes, lpDescs );
                                lp_Size_t lpDevGPS = lp_system_device_by_tag( lp_system_token( lpStream, lpToken[1] ), LP_DEVICE_ID_GPS, lpIndex, lpTypes, lpDescs );

                                /* Read token */
                                lp_system_token( lpStream, lpToken[1] );

                                /* Module operation */
                                lp_imu_mod_IOBMA( lpPath, * ( ( lp_IMU_t * ) lpDescs[lpDevIMU] ), * ( ( lp_GPS_t * ) lpDescs[lpDevGPS] ), lpToken[1] );

                            } else 
                            if ( strcmp( lpToken[0], LP_DEVICE_TYPE_IMU "-" LP_IMU_IFICR_MOD ) == 0 ) {

                                /* Search devices */
                                lp_Size_t lpDevIMU = lp_system_device_by_tag( lp_system_token( lpStream, lpToken[1] ), LP_DEVICE_ID_IMU, lpIndex, lpTypes, lpDescs );

                                /* Read token */
                                lp_system_token( lpStream, lpToken[1] );

                                /* Module operation */
                                lp_imu_mod_IFICR( lpPath, * ( ( lp_IMU_t * ) lpDescs[lpDevIMU] ), lpToken[1], 0, 0, 0 );

                            }

                        } else if ( lpMode == LP_SYSTEM_MODE_ICAM ) {

                            /* Read token */
                            if ( strcmp( lpToken[0], LP_SYSTEM_KW_DVTYPE ) == 0 ) {

                                /* Assign device type */
                                lpTypes[lpIndex] = LP_DEVICE_ID_CAM;

                                /* Allocate structure memory */
                                lpDescs[lpIndex] = malloc( sizeof( lp_Camera_t ) );

                                /* Initialize descriptor */
                                * ( ( lp_Camera_t * ) lpDescs[lpIndex] ) = lp_device_camera( lp_system_token( lpStream, lpToken[1] ), LP_DEVICE_TYPE_CAM );

                            } else 
                            if ( strcmp( lpToken[0], LP_SYSTEM_KW_DVTAGS ) == 0 ) {

                                /* Update device tag */
                                sprintf( ( ( lp_Camera_t * ) lpDescs[lpIndex] )->dvTag, "%s", lp_system_token( lpStream, lpToken[1] ) );

                            }

                        } else if ( lpMode == LP_SYSTEM_MODE_IGPS ) {

                            /* Read token */
                            if ( strcmp( lpToken[0], LP_SYSTEM_KW_DVTYPE ) == 0 ) {

                                /* Assign device type */
                                lpTypes[lpIndex] = LP_DEVICE_ID_GPS;

                                /* Allocate structure memory */
                                lpDescs[lpIndex] = malloc( sizeof( lp_GPS_t ) );

                                /* Initialize descriptor */
                                * ( ( lp_GPS_t * ) lpDescs[lpIndex] ) = lp_device_GPS( lp_system_token( lpStream, lpToken[1] ), LP_DEVICE_TYPE_GPS );

                            } else 
                            if ( strcmp( lpToken[0], LP_SYSTEM_KW_DVTAGS ) == 0 ) {

                                /* Update device tag */
                                sprintf( ( ( lp_GPS_t * ) lpDescs[lpIndex] )->dvTag, "%s", lp_system_token( lpStream, lpToken[1] ) );

                            }

                        } else if ( lpMode == LP_SYSTEM_MODE_IIMU ) {

                            /* Read token */
                            if ( strcmp( lpToken[0], LP_SYSTEM_KW_DVTYPE ) == 0 ) {

                                /* Assign device type */
                                lpTypes[lpIndex] = LP_DEVICE_ID_IMU;

                                /* Allocate structure memory */
                                lpDescs[lpIndex] = malloc( sizeof( lp_IMU_t ) );

                                /* Initialize descriptor */
                                * ( ( lp_IMU_t * ) lpDescs[lpIndex] ) = lp_device_IMU( lp_system_token( lpStream, lpToken[1] ), LP_DEVICE_TYPE_IMU );

                            } else 
                            if ( strcmp( lpToken[0], LP_SYSTEM_KW_DVTAGS ) == 0 ) {

                                /* Update device tag */
                                sprintf( ( ( lp_IMU_t * ) lpDescs[lpIndex] )->dvTag, "%s", lp_system_token( lpStream, lpToken[1] ) );

                            } else 
                            if ( strcmp( lpToken[0], LP_SYSTEM_KW_DVBLOC ) == 0 ) {

                                /* Update device reading block size */
                                sscanf( lp_system_token( lpStream, lpToken[1] ), "%" lp_Size_i, & ( ( ( lp_IMU_t * ) lpDescs[lpIndex] )->dvBlock ) );

                            }  else 
                            if ( strcmp( lpToken[0], LP_SYSTEM_KW_DVFREQ ) == 0 ) {

                                /* Update device reading block size */
                                sscanf( lp_system_token( lpStream, lpToken[1] ), "%" lp_Size_i, & ( ( ( lp_IMU_t * ) lpDescs[lpIndex] )->dvdfreq ) );

                            } else 
                            if ( strcmp( lpToken[0], LP_SYSTEM_KW_DVICRX ) == 0 ) {

                                /* Update device reading block size */
                                sscanf( lp_system_token( lpStream, lpToken[1] ), "%" lp_Real_i, & ( ( ( lp_IMU_t * ) lpDescs[lpIndex] )->dvICRx ) );

                            } else 
                            if ( strcmp( lpToken[0], LP_SYSTEM_KW_DVICRY ) == 0 ) {

                                /* Update device reading block size */
                                sscanf( lp_system_token( lpStream, lpToken[1] ), "%" lp_Real_i, & ( ( ( lp_IMU_t * ) lpDescs[lpIndex] )->dvICRy ) );

                            } else 
                            if ( strcmp( lpToken[0], LP_SYSTEM_KW_DVICRZ ) == 0 ) {

                                /* Update device reading block size */
                                sscanf( lp_system_token( lpStream, lpToken[1] ), "%" lp_Real_i, & ( ( ( lp_IMU_t * ) lpDescs[lpIndex] )->dvICRz ) );

                            } else 
                            if ( strcmp( lpToken[0], LP_SYSTEM_KW_DVIRMX ) == 0 ) {

                                /* Update device reading block size */
                                sscanf( lp_system_token( lpStream, lpToken[1] ), "%" lp_Size_i, & ( ( ( lp_IMU_t * ) lpDescs[lpIndex] )->dvISRmax ) );

                            } else 
                            if ( strcmp( lpToken[0], LP_SYSTEM_KW_DVIRMN ) == 0 ) {

                                /* Update device reading block size */
                                sscanf( lp_system_token( lpStream, lpToken[1] ), "%" lp_Size_i, & ( ( ( lp_IMU_t * ) lpDescs[lpIndex] )->dvISRacc ) );

                            } else 
                            if ( strcmp( lpToken[0], LP_SYSTEM_KW_DVIRTG ) == 0 ) {

                                /* Update device reading block size */
                                sscanf( lp_system_token( lpStream, lpToken[1] ), "%" lp_Real_i, & ( ( ( lp_IMU_t * ) lpDescs[lpIndex] )->dvISRgrt ) );

                            } else 
                            if ( strcmp( lpToken[0], LP_SYSTEM_KW_DVIRTT ) == 0 ) {

                                /* Update device reading block size */
                                sscanf( lp_system_token( lpStream, lpToken[1] ), "%" lp_Real_i, & ( ( ( lp_IMU_t * ) lpDescs[lpIndex] )->dvISRact ) );

                            }

                        }

                    }

                }

            }

            /* Close file */
            fclose( lpStream );

            /* Free memory allocations */
            for ( ; lpIndex >= 0 ; lpIndex -- ) free( lpDescs[lpIndex] );

        }

    }

/*
    Source - Device search in stack
 */

    lp_Size_t lp_system_device_by_tag(

        lp_Char_t const *  const lpTag,
        lp_Enum_t const          lpType,
        lp_Size_t                lpIndex,
        lp_Enum_t const *  const lpTypes,
        lp_Void_t       **       lpDescs

    ) {

        /* Search in devices stack */
        for ( ; lpIndex >= 0; lpIndex -- ) {

            /* Check device type */
            if ( lpTypes[lpIndex] == lpType ) {

                /* Switch on device type */
                if ( lpType == LP_DEVICE_ID_CAM ) {

                    /* Compare device tag to parameter and return index */
                    if ( strcmp( ( ( lp_Camera_t * ) lpDescs[lpIndex] )->dvTag, lpTag ) == 0 ) return( lpIndex );

                } else
                if ( lpType == LP_DEVICE_ID_GPS ) {

                    /* Compare device tag to parameter and return index */
                    if ( strcmp( ( ( lp_GPS_t * ) lpDescs[lpIndex] )->dvTag, lpTag ) == 0 ) return( lpIndex );

                } else
                if ( lpType == LP_DEVICE_ID_IMU ) {

                    /* Compare device tag to parameter and return index */
                    if ( strcmp( ( ( lp_IMU_t * ) lpDescs[lpIndex] )->dvTag, lpTag ) == 0 ) return( lpIndex );

                }

            }

        }

        /* Device not found */
        return( LP_SYSTEM_NODEVICE );

    }

