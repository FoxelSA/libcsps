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
    Source - Camera data extractor module
 */

    lp_CAM lp_cam_mod_DSIDE( 

        const lp_Char_t * const lpPath, 
        lp_CAM                  lpDevice 

    ) {

        /* Select device */
        if ( strcmp( lpDevice.dvName, LP_DEVICE_CAM_EYESIS4PI ) == 0 ) {

            /* Eyesis4pi specific process */
            return( lp_cam_DSIDE_EYESIS4PI( lpPath, lpDevice ) );

        } else {

            /* Unknown device - Return descriptor */
            return( lpDevice );

        }

    }

/*
    Source - Camera EYESIS4PI specific extractor
 */

    lp_CAM lp_cam_DSIDE_EYESIS4PI( 

        const lp_Char_t * const lpPath, 
        lp_CAM                  lpDevice 

    ) {

        /* FPGA record buffer */
        lp_Byte_t lpRec[LP_DEVICE_CAM_EYESIS4PI_RECLEN];

        /* Reading variables */
        lp_Enum_t lpReading = LP_TRUE;
        lp_Size_t lpIndex   = lp_Size_s( 0 );
        lp_Size_t lpReaded  = lp_Size_s( 0 );

        /* Paths string buffer */
        lp_Char_t lpDEVlogp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpDEVmasp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpDEVsynp[LP_STR_LEN] = LP_STR_INI;

        /* Stream handles */
        lp_File_t lpDEVlogf = NULL;
        lp_File_t lpDEVmasf = NULL;
        lp_File_t lpDEVsynf = NULL;

        /* Data buffers */
        lp_Time_t * lpDEVmas = NULL;
        lp_Time_t * lpDEVsyn = NULL;

        /* Build raw log file paths */
        lp_path( lpPath, LP_DEVICE_CAM_EYESIS4PI, NULL, NULL, NULL, lpDEVlogp );

        /* Build file paths */
        lp_path( lpPath, LP_CAM_MODULE_DSIDE_DEV, lpDevice.dvTag, LP_CAM_MODULE_DSIDE_MOD, "mas", lpDEVmasp );
        lp_path( lpPath, LP_CAM_MODULE_DSIDE_DEV, lpDevice.dvTag, LP_CAM_MODULE_DSIDE_MOD, "syn", lpDEVsynp );

        /* Open file streams */
        lpDEVlogf = fopen( lpDEVlogp, "rb" );
        lpDEVmasf = fopen( lpDEVmasp, "wb" );
        lpDEVsynf = fopen( lpDEVsynp, "wb" );

        /* Allocate buffer memory */
        lpDEVmas = ( lp_Time_t * ) malloc( sizeof( lp_Time_t ) * lpDevice.dvBlock );
        lpDEVsyn = ( lp_Time_t * ) malloc( sizeof( lp_Time_t ) * lpDevice.dvBlock );

        /* FPGA records reading loop */
        while ( lpReading == LP_TRUE ) {

            /* Reset reading index */
            lpIndex = lp_Size_s( 0 );

            /* Reading of FPGA record by group */
            while ( ( lpReading == LP_TRUE ) && ( lpIndex < lpDevice.dvBlock ) ) {

                /* Read FPGA record */
                lpReaded = fread( lpRec, 1, LP_DEVICE_CAM_EYESIS4PI_RECLEN, lpDEVlogf );

                /* Verify FPGA record reading */
                if ( lpReaded == LP_DEVICE_CAM_EYESIS4PI_RECLEN ) {

                    /* Master signal filter */
                    if ( ( lpRec[3] & lp_Byte_s( 0x0F ) ) == LP_DEVICE_CAM_EYESIS4PI_MASEVT ) {

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

        /* Close file stream */
        fclose( lpDEVlogf );
        fclose( lpDEVmasf );
        fclose( lpDEVsynf );

        /* Unallocate buffer memory */
        free( lpDEVmas );
        free( lpDEVsyn );

        /* Return device descriptor */
        return( lpDevice );

    }

