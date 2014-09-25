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

    # include "csps-cam-mod-DSIDE.h"

/*
    Source - Camera signal extraction switch
 */

    lp_Void_t lp_cam_mod_DSIDE( 

        const lp_Char_t * const lpPath, 
        const lp_CAM            lpCAM 

    ) {

        /* Select device */
        if ( strcmp( lpCAM.dvName, LP_DEVICE_EYESIS4PI ) == 0 ) {

            /* Eyesis4pi specific process */
            lp_cam_DSIDE_EYESIS4PI( lpPath, lpCAM );

        } else if ( strcmp( lpCAM.dvName, LP_DEVICE_NC353L369IMUGPS ) == 0 ) {

            /* NC353L369 specific process (same as Eyesis4Pi) */
            lp_cam_DSIDE_EYESIS4PI( lpPath, lpCAM );

        }

    }

/*
    Source - Camera Eyesis4pi specific extractor
 */

    lp_Void_t lp_cam_DSIDE_EYESIS4PI( 

        const lp_Char_t * const lpPath, 
        const lp_CAM            lpCAM 

    ) {

        /* FPGA record buffer variables */
        lp_Byte_t lpRec[LP_DEVICE_EYESIS4PI_RECLEN];

        /* Reading variables */
        lp_Enum_t lpReading = LP_TRUE;
        lp_Size_t lpIndex   = lp_Size_s( 0 );
        lp_Size_t lpReaded  = lp_Size_s( 0 );

        /* Stream path variables */
        lp_Char_t lpDEVlogp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpDEVmasp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpDEVsynp[LP_STR_LEN] = LP_STR_INI;

        /* Stream file variables */
        lp_File_t lpDEVlogf = LP_NULL;
        lp_File_t lpDEVmasf = LP_NULL;
        lp_File_t lpDEVsynf = LP_NULL;

        /* Stream memory variables */
        lp_Time_t * lpDEVmas = LP_NULL;
        lp_Time_t * lpDEVsyn = LP_NULL;

        /* Build device log file paths */
        lp_path_dside( lpPath, LP_DEVICE_EYESIS4PI, LP_DEVICE_EYESIS4PI_LOG_FPGA, lpDEVlogp );

        /* Build stream file paths */
        lp_path_stream( lpPath, lpCAM.dvType, lpCAM.dvTag, LP_CAM_DSIDE_MOD, LP_STREAM_CPN_TAG, lpDEVmasp );
        lp_path_stream( lpPath, lpCAM.dvType, lpCAM.dvTag, LP_CAM_DSIDE_MOD, LP_STREAM_CPN_SYN, lpDEVsynp );

        /* Open stream files */
        lpDEVlogf = fopen( lpDEVlogp, "rb" );
        lpDEVmasf = fopen( lpDEVmasp, "wb" );
        lpDEVsynf = fopen( lpDEVsynp, "wb" );

        /* Create streams */
        lpDEVmas = ( lp_Time_t * ) lp_stream_create( sizeof( lp_Time_t ) * lpCAM.dvBlock );
        lpDEVsyn = ( lp_Time_t * ) lp_stream_create( sizeof( lp_Time_t ) * lpCAM.dvBlock );

        /* FPGA records reading loop */
        while ( lpReading == LP_TRUE ) {

            /* Reset reading index */
            lpIndex = lp_Size_s( 0 );

            /* Reading of FPGA record by block */
            while ( ( lpReading == LP_TRUE ) && ( lpIndex < lpCAM.dvBlock ) ) {

                /* Read and verify FPGA record */
                if ( ( lpReaded = fread( lpRec, 1, LP_DEVICE_EYESIS4PI_RECLEN, lpDEVlogf ) ) == LP_DEVICE_EYESIS4PI_RECLEN ) {

                    /* Camera signal filter */
                    if ( ( lpRec[3] & lp_Byte_s( 0x0F ) ) == LP_DEVICE_EYESIS4PI_MASEVT ) {

                        /* Retrieve FPGA master timestamp */
                        lpDEVmas[lpIndex] = lp_timestamp( ( lp_Void_t * ) ( lpRec + lp_Size_s( 8 ) ) );

                        /* Retrieve FPGA local timestamp */
                        lpDEVsyn[lpIndex] = lp_timestamp( ( lp_Void_t * ) lpRec );

                        /* Update reading index */
                        lpIndex += lp_Size_s( 1 );

                    }

                } else {

                    /* Stop reading on EOF */
                    lpReading = LP_FALSE;

                }

            }

            /* Verify that the current block is not empty */
            if ( lpIndex > lp_Size_s( 0 ) ) {

                /* Export block in output streams */
                fwrite( lpDEVmas, sizeof( lp_Time_t ) * lpIndex, 1, lpDEVmasf );
                fwrite( lpDEVsyn, sizeof( lp_Time_t ) * lpIndex, 1, lpDEVsynf );

            }

        }

        /* Close stream files */
        fclose( lpDEVlogf );
        fclose( lpDEVmasf );
        fclose( lpDEVsynf );

        /* Unallocate streams */
        free( lpDEVmas );
        free( lpDEVsyn );

    }

