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

    # include "csps-cam-modde.h"

/*
    Source - Camera data extractor module
 */

    csps_CAM csps_cam_modde( const csps_Char_t * const cspsPath, csps_CAM cspsDevice, const csps_Char_t * const cspsName ) {

        /* Select device */
        if ( strcmp( cspsDevice.dvName, CSPS_DEVICE_CAM_EYESIS4PI ) == 0 ) {

            /* Eyesis4pi specific process */
            return( csps_cam_EYESIS4PI( cspsPath, cspsDevice, cspsName ) );

        } else {

            /* Unknown device - Return descriptor */
            return( cspsDevice );

        }

    }

/*
    Source - Camera EYESIS4PI specific extractor
 */

    csps_CAM csps_cam_EYESIS4PI( const csps_Char_t * const cspsPath, csps_CAM cspsDevice, const csps_Char_t * const cspsName ) {

        /* FPGA record buffer */
        csps_Byte_t cspsRec[CSPS_DEVICE_CAM_EYESIS4PI_RECLEN];

        /* Reading variables */
        csps_Enum_t cspsReading = CSPS_TRUE;
        csps_Size_t cspsIndex = csps_Size_s( 0 );
        csps_Size_t cspsReaded = csps_Size_s( 0 );

        /* Paths string buffer */
        csps_Char_t cspsDEVlogp[CSPS_STR_LEN] = CSPS_STR_INI;
        csps_Char_t cspsDEVmasp[CSPS_STR_LEN] = CSPS_STR_INI;
        csps_Char_t cspsDEVsynp[CSPS_STR_LEN] = CSPS_STR_INI;

        /* Stream handles */
        csps_File_t cspsDEVlogf = NULL;
        csps_File_t cspsDEVmasf = NULL;
        csps_File_t cspsDEVsynf = NULL;

        /* Data buffers */
        csps_Time_t * cspsDEVmas = NULL;
        csps_Time_t * cspsDEVsyn = NULL;

        /* Build raw log file paths */
        csps_path( cspsPath, CSPS_DEVICE_CAM_EYESIS4PI, NULL, NULL, NULL, cspsDEVlogp );

        /* Build file paths */
        csps_path( cspsPath, CSPS_CAM_MODDE_DEV, cspsName, CSPS_CAM_MODDE_MOD, "mas", cspsDEVmasp );
        csps_path( cspsPath, CSPS_CAM_MODDE_DEV, cspsName, CSPS_CAM_MODDE_MOD, "syn", cspsDEVsynp );

        /* Open file streams */
        cspsDEVlogf = fopen( cspsDEVlogp, "rb" );
        cspsDEVmasf = fopen( cspsDEVmasp, "wb" );
        cspsDEVsynf = fopen( cspsDEVsynp, "wb" );

        /* Allocate buffer memory */
        cspsDEVmas = ( csps_Time_t * ) malloc( sizeof( csps_Time_t ) * cspsDevice.dvBlock );
        cspsDEVsyn = ( csps_Time_t * ) malloc( sizeof( csps_Time_t ) * cspsDevice.dvBlock );

        /* FPGA records reading loop */
        while ( cspsReading == CSPS_TRUE ) {

            /* Reset reading index */
            cspsIndex = csps_Size_s( 0 );

            /* Reading of FPGA record by group */
            while ( ( cspsReading == CSPS_TRUE ) && ( cspsIndex < cspsDevice.dvBlock ) ) {

                /* Read FPGA record */
                cspsReaded = fread( cspsRec, 1, CSPS_DEVICE_CAM_EYESIS4PI_RECLEN, cspsDEVlogf );

                /* Verify FPGA record reading */
                if ( cspsReaded == CSPS_DEVICE_CAM_EYESIS4PI_RECLEN ) {

                    /* Master signal filter */
                    if ( ( cspsRec[3] & csps_Byte_s( 0x0F ) ) == CSPS_DEVICE_CAM_EYESIS4PI_MASEVT ) {

                        /* Retrieve FPGA master timestamp */
                        cspsDEVmas[cspsIndex] = csps_timestamp( ( csps_Void_t * ) ( cspsRec + csps_Size_s( 8 ) ) );

                        /* Retrieve FPGA local timestamp */
                        cspsDEVsyn[cspsIndex] = csps_timestamp( ( csps_Void_t * ) cspsRec );

                        /* Update reading index */
                        cspsIndex += csps_Size_s( 1 );

                    }

                } else {

                    /* Stop reading on EOF */
                    cspsReading = CSPS_FALSE;

                }

            }

            /* Verify that the current block is not empty */
            if ( cspsIndex > csps_Size_s( 0 ) ) {

                /* Export block in output streams */
                fwrite( cspsDEVmas, sizeof( csps_Time_t ) * cspsIndex, 1, cspsDEVmasf );
                fwrite( cspsDEVsyn, sizeof( csps_Time_t ) * cspsIndex, 1, cspsDEVsynf );

            }

        }

        /* Close file stream */
        fclose( cspsDEVlogf );
        fclose( cspsDEVmasf );
        fclose( cspsDEVsynf );

        /* Unallocate buffer memory */
        free( cspsDEVmas );
        free( cspsDEVsyn );

        /* Return device descriptor */
        return( cspsDevice );

    }

