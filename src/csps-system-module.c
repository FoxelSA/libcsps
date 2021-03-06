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
    Source - Extraction modules interface
 */

    lp_Void_t lp_system_module_cam_DSIDE(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        lp_Size_t          const lpLevel,
        FILE             * const lpStream

    ) {

        /* String token variables */
        lp_Char_t lpToken[2][LP_STR_LEN] = { LP_STR_INI };

        /* Device and module stacking variables */
        lp_Size_t lpStacking = lp_Size_s( 1 );

        /* Block size variables */
        lp_Size_t lpBlock = lp_Size_s( 1024 );

        /* Execution level variables */
        lp_Size_t lprLevel = lp_Size_s( 1 );

        /* Camera descriptor pointer */
        lp_Camera_t * lpCamera = NULL;

        /* Token parser */
        do {

            /* Read token from stream */
            lp_system_token( lpStream, lpToken[0] );

            /* String token analysis */
            if ( strcmp( lpToken[0], LP_SYSTEM_LEVEL ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[0] );

                /* Convert parameter token */
                lprLevel = lp_Size_r( lpToken[0] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_DINPUT ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[lpStacking++] );

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
        if ( ( lpCamera = ( lp_Camera_t * ) lp_system_stack_bytag( lpStack, LP_SYSTEM_TYPE_CAM, lpToken[1] ) ) != NULL ) {

            /* Module operation according to execution level */
            if ( lprLevel <= lpLevel ) lp_cam_mod_DSIDE( lpPath, * lpCamera, lpBlock );

        }

    }

    lp_Void_t lp_system_module_gps_DSIDE(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        lp_Size_t          const lpLevel,
        FILE             * const lpStream

    ) {

        /* String token variables */
        lp_Char_t lpToken[2][LP_STR_LEN] = { LP_STR_INI };

        /* Device and module stacking variables */
        lp_Size_t lpStacking = lp_Size_s( 1 );

        /* Block size variables */
        lp_Size_t lpBlock = lp_Size_s( 1024 );

        /* Execution level variables */
        lp_Size_t lprLevel = lp_Size_s( 1 );

        /* Camera descriptor pointer */
        lp_GPS_t * lpGPS = NULL;

        /* Token parser */
        do {

            /* Read token from stream */
            lp_system_token( lpStream, lpToken[0] );

            /* String token analysis */
            if ( strcmp( lpToken[0], LP_SYSTEM_LEVEL ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[0] );

                /* Convert parameter token */
                lprLevel = lp_Size_r( lpToken[0] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_DINPUT ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[lpStacking++] );

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
        if ( ( lpGPS = ( lp_GPS_t * ) lp_system_stack_bytag( lpStack, LP_SYSTEM_TYPE_GPS, lpToken[1] ) ) != NULL ) {

            /* Module operation according to execution level */
            if ( lprLevel <= lpLevel ) lp_gps_mod_DSIDE( lpPath, * lpGPS, lpBlock );

        }

    }

    lp_Void_t lp_system_module_imu_DSIDE(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        lp_Size_t          const lpLevel,
        FILE             * const lpStream

    ) {

        /* String token variables */
        lp_Char_t lpToken[2][LP_STR_LEN] = { LP_STR_INI };

        /* Device and module stacking variables */
        lp_Size_t lpStacking = lp_Size_s( 1 );

        /* Block size variables */
        lp_Size_t lpBlock = lp_Size_s( 1024 );

        /* Execution level variables */
        lp_Size_t lprLevel = lp_Size_s( 1 );

        /* Camera descriptor pointer */
        lp_IMU_t * lpIMU = NULL;

        /* Token parser */
        do {

            /* Read token from stream */
            lp_system_token( lpStream, lpToken[0] );

            /* String token analysis */
            if ( strcmp( lpToken[0], LP_SYSTEM_LEVEL ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[0] );

                /* Convert parameter token */
                lprLevel = lp_Size_r( lpToken[0] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_DINPUT ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[lpStacking++] );

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
        if ( ( lpIMU = ( lp_IMU_t * ) lp_system_stack_bytag( lpStack, LP_SYSTEM_TYPE_IMU, lpToken[1] ) ) != NULL ) {

            /* Module operation according to execution level */
            if ( lprLevel <= lpLevel ) lp_imu_mod_DSIDE( lpPath, * lpIMU, lpBlock );

        }

    }

/*
    Source - GPS reciever modules interface
 */

    lp_Void_t lp_system_module_gps_SGNQF(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        lp_Size_t          const lpLevel,
        FILE             * const lpStream

    ) {

        /* String token variables */
        lp_Char_t lpToken[3][LP_STR_LEN] = { LP_STR_INI };

        /* Device and module stacking variables */
        lp_Size_t lpStacking = lp_Size_s( 1 );

        /* Execution level variables */
        lp_Size_t lprLevel = lp_Size_s( 1 );

        /* Camera descriptor pointer */
        lp_GPS_t * lpGPS = NULL;

        /* Token parser */
        do {

            /* Read token from stream */
            lp_system_token( lpStream, lpToken[0] );

            /* String token analysis */
            if ( strcmp( lpToken[0], LP_SYSTEM_LEVEL ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[0] );

                /* Convert parameter token */
                lprLevel = lp_Size_r( lpToken[0] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_DINPUT ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[lpStacking++] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_MINPUT ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[lpStacking++] );

            }

        /* End condition on end-keyword */
        } while ( strcmp( lpToken[0], LP_SYSTEM_END ) != 0 );

        /* Search device by tag */
        if ( ( lpGPS = ( lp_GPS_t * ) lp_system_stack_bytag( lpStack, LP_SYSTEM_TYPE_GPS, lpToken[1] ) ) != NULL ) {

            /* Module operation according to execution level */
            if ( lprLevel <= lpLevel ) lp_gps_mod_SGNQF( lpPath, * lpGPS, lpToken[2] );

        }

    }

/*
    Source - IMU sensor modules interface
 */

    lp_Void_t lp_system_module_imu_SGSFR(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        lp_Size_t          const lpLevel,
        FILE             * const lpStream

    ) {

        /* String token variables */
        lp_Char_t lpToken[3][LP_STR_LEN] = { LP_STR_INI };

        /* Device and module stacking variables */
        lp_Size_t lpStacking = lp_Size_s( 1 );

        /* Parameters variables */
        lp_Real_t lpiFreq = lp_Real_s( 1.0 );
        lp_Real_t lpdFreq = lp_Real_s( 1.0 );

        /* Execution level variables */
        lp_Size_t lprLevel = lp_Size_s( 1 );

        /* Camera descriptor pointer */
        lp_IMU_t * lpIMU = NULL;

        /* Token parser */
        do {

            /* Read token from stream */
            lp_system_token( lpStream, lpToken[0] );

            /* String token analysis */
            if ( strcmp( lpToken[0], LP_SYSTEM_LEVEL ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[0] );

                /* Convert parameter token */
                lprLevel = lp_Size_r( lpToken[0] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_DINPUT ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[lpStacking++] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_MINPUT ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[lpStacking++] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_IFREQ ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[0] );

                /* Interprete parameter */
                lpiFreq = lp_Real_r( lpToken[0] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_DFREQ ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[0] );

                /* Interprete parameter */
                lpdFreq = lp_Real_r( lpToken[0] );

            }

        /* End condition on end-keyword */
        } while ( strcmp( lpToken[0], LP_SYSTEM_END ) != 0 );

        /* Search device by tag */
        if ( ( lpIMU = ( lp_IMU_t * ) lp_system_stack_bytag( lpStack, LP_SYSTEM_TYPE_IMU, lpToken[1] ) ) != NULL ) {

            /* Module operation according to execution level */
            if ( lprLevel <= lpLevel ) lp_imu_mod_SGSFR( lpPath, * lpIMU, lpToken[2], lpiFreq, lpdFreq );

        }

    }

    lp_Void_t lp_system_module_imu_SGNDN(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        lp_Size_t          const lpLevel,
        FILE             * const lpStream

    ) {

        /* String token variables */
        lp_Char_t lpToken[3][LP_STR_LEN] = { LP_STR_INI };

        /* Device and module stacking variables */
        lp_Size_t lpStacking = lp_Size_s( 1 );

        /* Execution level variables */
        lp_Size_t lprLevel = lp_Size_s( 1 );

        /* Camera descriptor pointer */
        lp_IMU_t * lpIMU = NULL;

        /* Token parser */
        do {

            /* Read token from stream */
            lp_system_token( lpStream, lpToken[0] );

            /* String token analysis */
            if ( strcmp( lpToken[0], LP_SYSTEM_LEVEL ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[0] );

                /* Convert parameter token */
                lprLevel = lp_Size_r( lpToken[0] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_DINPUT ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[lpStacking++] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_MINPUT ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[lpStacking++] );

            }

        /* End condition on end-keyword */
        } while ( strcmp( lpToken[0], LP_SYSTEM_END ) != 0 );

        /* Search device by tag */
        if ( ( lpIMU = ( lp_IMU_t * ) lp_system_stack_bytag( lpStack, LP_SYSTEM_TYPE_IMU, lpToken[1] ) ) != NULL ) {

            /* Module operation according to execution level */
            if ( lprLevel <= lpLevel ) lp_imu_mod_SGNDN( lpPath, * lpIMU, lpToken[2] );

        }

    }
  
    lp_Void_t lp_system_module_imu_ISRAD(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        lp_Size_t          const lpLevel,
        FILE             * const lpStream

    ) {

        /* String token variables */
        lp_Char_t lpToken[3][LP_STR_LEN] = { LP_STR_INI };

        /* Device and module stacking variables */
        lp_Size_t lpStacking = lp_Size_s( 1 );

        /* Integer parameters variables */
        lp_Size_t lpLimit = lp_Size_s( 256 );
        lp_Size_t lpAccum = lp_Size_s(  32 );

        /* Real parameters variables */
        lp_Real_t lpgTrigger = lp_Real_s( 0.05 );
        lp_Real_t lpaTrigger = lp_Real_s( 0.50 );

        /* Execution level variables */
        lp_Size_t lprLevel = lp_Size_s( 1 );

        /* Camera descriptor pointer */
        lp_IMU_t * lpIMU = NULL;

        /* Token parser */
        do {

            /* Read token from stream */
            lp_system_token( lpStream, lpToken[0] );

            /* String token analysis */
            if ( strcmp( lpToken[0], LP_SYSTEM_LEVEL ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[0] );

                /* Convert parameter token */
                lprLevel = lp_Size_r( lpToken[0] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_DINPUT ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[lpStacking++] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_MINPUT ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[lpStacking++] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_ISRL ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[0] );

                /* Interprete parameter */
                lpLimit = lp_Size_r( lpToken[0] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_ISRA ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[0] );

                /* Interprete parameter */
                lpAccum = lp_Size_r( lpToken[0] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_ISRGT ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[0] );

                /* Interprete parameter */
                lpgTrigger = lp_Real_r( lpToken[0] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_ISRAT ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[0] );

                /* Interprete parameter */
                lpaTrigger = lp_Real_r( lpToken[0] );

            }

        /* End condition on end-keyword */
        } while ( strcmp( lpToken[0], LP_SYSTEM_END ) != 0 );

        /* Search device by tag */
        if ( ( lpIMU = ( lp_IMU_t * ) lp_system_stack_bytag( lpStack, LP_SYSTEM_TYPE_IMU, lpToken[1] ) ) != NULL ) {

            /* Module operation according to execution level */
            if ( lprLevel <= lpLevel ) lp_imu_mod_ISRAD( lpPath, * lpIMU, lpToken[2], lpLimit, lpAccum, lpgTrigger, lpaTrigger );

        }

    }

    lp_Void_t lp_system_module_imu_IOISA(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        lp_Size_t          const lpLevel,
        FILE             * const lpStream

    ) {

        /* String token variables */
        lp_Char_t lpToken[4][LP_STR_LEN] = { LP_STR_INI };

        /* Device and module stacking variables */
        lp_Size_t lpStacking = lp_Size_s( 1 );

        /* Execution level variables */
        lp_Size_t lprLevel = lp_Size_s( 1 );

        /* Camera descriptor pointer */
        lp_IMU_t * lpIMU = NULL;

        /* Token parser */
        do {

            /* Read token from stream */
            lp_system_token( lpStream, lpToken[0] );

            /* String token analysis */
            if ( strcmp( lpToken[0], LP_SYSTEM_LEVEL ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[0] );

                /* Convert parameter token */
                lprLevel = lp_Size_r( lpToken[0] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_DINPUT ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[lpStacking++] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_MINPUT ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[lpStacking++] );

            }

        /* End condition on end-keyword */
        } while ( strcmp( lpToken[0], LP_SYSTEM_END ) != 0 );

        /* Search device by tag */
        if ( ( lpIMU = ( lp_IMU_t * ) lp_system_stack_bytag( lpStack, LP_SYSTEM_TYPE_IMU, lpToken[1] ) ) != NULL ) {

            /* Module operation according to execution level */
            if ( lprLevel <= lpLevel ) lp_imu_mod_IOISA( lpPath, * lpIMU, lpToken[2], lpToken[3] );

        }

    }

    lp_Void_t lp_system_module_imu_IOBMA(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        lp_Size_t          const lpLevel,
        FILE             * const lpStream

    ) {

        /* String token variables */
        lp_Char_t lpToken[4][LP_STR_LEN] = { LP_STR_INI };

        /* Device and module stacking variables */
        lp_Size_t lpStacking = lp_Size_s( 1 );

        /* Execution level variables */
        lp_Size_t lprLevel = lp_Size_s( 1 );

        /* Camera descriptor pointer */
        lp_IMU_t * lpIMU = NULL;
        lp_GPS_t * lpGPS = NULL;

        /* Token parser */
        do {

            /* Read token from stream */
            lp_system_token( lpStream, lpToken[0] );

            /* String token analysis */
            if ( strcmp( lpToken[0], LP_SYSTEM_LEVEL ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[0] );

                /* Convert parameter token */
                lprLevel = lp_Size_r( lpToken[0] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_DINPUT ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[lpStacking++] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_MINPUT ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[lpStacking++] );

            }

        /* End condition on end-keyword */
        } while ( strcmp( lpToken[0], LP_SYSTEM_END ) != 0 );

        /* Search device by tag */
        if ( ( ( lpIMU = ( lp_IMU_t * ) lp_system_stack_bytag( lpStack, LP_SYSTEM_TYPE_IMU, lpToken[1] ) ) != NULL ) && 
             ( ( lpGPS = ( lp_GPS_t * ) lp_system_stack_bytag( lpStack, LP_SYSTEM_TYPE_GPS, lpToken[2] ) ) != NULL ) ) {

            /* Module operation according to execution level */
            if ( lprLevel <= lpLevel ) lp_imu_mod_IOBMA( lpPath, * lpIMU, * lpGPS, lpToken[3] );

        }

    }

    lp_Void_t lp_system_module_imu_IFICR(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        lp_Size_t          const lpLevel,
        FILE             * const lpStream

    ) {

        /* String token variables */
        lp_Char_t lpToken[3][LP_STR_LEN] = { LP_STR_INI };

        /* Device and module stacking variables */
        lp_Size_t lpStacking = lp_Size_s( 1 );

        /* Angle parameter variables */
        lp_Real_t lpxAngle = lp_Real_s( 0.0 );
        lp_Real_t lpyAngle = lp_Real_s( 0.0 );
        lp_Real_t lpzAngle = lp_Real_s( 0.0 );

        /* Execution level variables */
        lp_Size_t lprLevel = lp_Size_s( 1 );

        /* Camera descriptor pointer */
        lp_IMU_t * lpIMU = NULL;

        /* Token parser */
        do {

            /* Read token from stream */
            lp_system_token( lpStream, lpToken[0] );

            /* String token analysis */
            if ( strcmp( lpToken[0], LP_SYSTEM_LEVEL ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[0] );

                /* Convert parameter token */
                lprLevel = lp_Size_r( lpToken[0] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_DINPUT ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[lpStacking++] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_MINPUT ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[lpStacking++] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_XANG ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[0] );

                /* Interprete parameter */
                lpxAngle = lp_Real_r( lpToken[0] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_YANG ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[0] );

                /* Interprete parameter */
                lpyAngle = lp_Real_r( lpToken[0] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_ZANG ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[0] );

                /* Interprete parameter */
                lpzAngle = lp_Real_r( lpToken[0] );

            }

        /* End condition on end-keyword */
        } while ( strcmp( lpToken[0], LP_SYSTEM_END ) != 0 );

        /* Search device by tag */
        if ( ( lpIMU = ( lp_IMU_t * ) lp_system_stack_bytag( lpStack, LP_SYSTEM_TYPE_IMU, lpToken[1] ) ) != NULL ) {

            /* Module operation according to execution level */
            if ( lprLevel <= lpLevel ) lp_imu_mod_IFICR( lpPath, * lpIMU, lpToken[2], lpxAngle, lpyAngle, lpzAngle );

        }

    }
  
    lp_Void_t lp_system_module_imu_IFETI(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        lp_Size_t          const lpLevel,
        FILE             * const lpStream

    ) {

        /* String token variables */
        lp_Char_t lpToken[4][LP_STR_LEN] = { LP_STR_INI };

        /* Device and module stacking variables */
        lp_Size_t lpStacking = lp_Size_s( 1 );

        /* Execution level variables */
        lp_Size_t lprLevel = lp_Size_s( 1 );

        /* Camera descriptor pointer */
        lp_IMU_t * lpIMU = NULL;

        /* Token parser */
        do {

            /* Read token from stream */
            lp_system_token( lpStream, lpToken[0] );

            /* String token analysis */
            if ( strcmp( lpToken[0], LP_SYSTEM_LEVEL ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[0] );

                /* Convert parameter token */
                lprLevel = lp_Size_r( lpToken[0] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_DINPUT ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[lpStacking++] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_MINPUT ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[lpStacking++] );

            }

        /* End condition on end-keyword */
        } while ( strcmp( lpToken[0], LP_SYSTEM_END ) != 0 );

        /* Search device by tag */
        if ( ( lpIMU = ( lp_IMU_t * ) lp_system_stack_bytag( lpStack, LP_SYSTEM_TYPE_IMU, lpToken[1] ) ) != NULL ) {

            /* Module operation according to execution level */
            if ( lprLevel <= lpLevel ) lp_imu_mod_IFETI( lpPath, * lpIMU, lpToken[2], lpToken[3] );

        }

    }

    lp_Void_t lp_system_module_imu_AACEX(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        lp_Size_t          const lpLevel,
        FILE             * const lpStream

    ) {

        /* String token variables */
        lp_Char_t lpToken[4][LP_STR_LEN] = { LP_STR_INI };

        /* Device and module stacking variables */
        lp_Size_t lpStacking = lp_Size_s( 1 );

        /* Execution level variables */
        lp_Size_t lprLevel = lp_Size_s( 1 );

        /* Camera descriptor pointer */
        lp_IMU_t * lpIMU = NULL;

        /* Token parser */
        do {

            /* Read token from stream */
            lp_system_token( lpStream, lpToken[0] );

            /* String token analysis */
            if ( strcmp( lpToken[0], LP_SYSTEM_LEVEL ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[0] );

                /* Convert parameter token */
                lprLevel = lp_Size_r( lpToken[0] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_DINPUT ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[lpStacking++] );

            } else
            if ( strcmp( lpToken[0], LP_SYSTEM_MINPUT ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpToken[lpStacking++] );

            }

        /* End condition on end-keyword */
        } while ( strcmp( lpToken[0], LP_SYSTEM_END ) != 0 );

        /* Search device by tag */
        if ( ( lpIMU = ( lp_IMU_t * ) lp_system_stack_bytag( lpStack, LP_SYSTEM_TYPE_IMU, lpToken[1] ) ) != NULL ) {

            /* Module operation according to execution level */
            if ( lprLevel <= lpLevel ) lp_imu_mod_AACEX( lpPath, * lpIMU, lpToken[2], lpToken[3] );

        }

    }

