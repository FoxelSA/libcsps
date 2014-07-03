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

    # include "csps-imu-modde.h"

/*
    Source - IMU data extractor module
 */

    csps_IMU csps_imu_modde( const csps_Char_t * const cspsPath, csps_IMU cspsDevice, const csps_Char_t * const cspsName ) {

        /* Select device */
        if ( strcmp( cspsDevice.dvName, CSPS_DEVICE_IMU_ADIS16375 ) == 0 ) {

            /* ADIS16375 specific process */
            return( csps_imu_ADIS16375( cspsPath, cspsDevice, cspsName ) );

        } else {

            /* Unknown device - Return descriptor */
            return( cspsDevice );

        }

    }

/*
    Source - IMU ADIS16375 specific extractor
 */

    csps_IMU csps_imu_ADIS16375( const csps_Char_t * const cspsPath, csps_IMU cspsDevice, const csps_Char_t * const cspsName ) {

        /* FPGA record buffer */
        csps_Byte_t cspsRec[CSPS_DEVICE_FPGA_RECLEN];

        /* Reading variables */
        csps_Enum_t cspsReading = CSPS_TRUE;
        csps_Size_t cspsIndex = csps_Size_s( 0 );
        csps_Size_t cspsReaded = csps_Size_s( 0 );

        /* Paths string buffer */
        csps_Char_t cspsDEVlogp[CSPS_STR_LEN] = CSPS_STR_INI;
        csps_Char_t cspsDEVgrxp[CSPS_STR_LEN] = CSPS_STR_INI;
        csps_Char_t cspsDEVgryp[CSPS_STR_LEN] = CSPS_STR_INI;
        csps_Char_t cspsDEVgrzp[CSPS_STR_LEN] = CSPS_STR_INI;
        csps_Char_t cspsDEVacxp[CSPS_STR_LEN] = CSPS_STR_INI;
        csps_Char_t cspsDEVacyp[CSPS_STR_LEN] = CSPS_STR_INI;
        csps_Char_t cspsDEVaczp[CSPS_STR_LEN] = CSPS_STR_INI;
        csps_Char_t cspsDEVsynp[CSPS_STR_LEN] = CSPS_STR_INI;

        /* Stream handles */
        csps_File_t cspsDEVlogf = NULL;
        csps_File_t cspsDEVgrxf = NULL;
        csps_File_t cspsDEVgryf = NULL;
        csps_File_t cspsDEVgrzf = NULL;
        csps_File_t cspsDEVacxf = NULL;
        csps_File_t cspsDEVacyf = NULL;
        csps_File_t cspsDEVaczf = NULL;
        csps_File_t cspsDEVsynf = NULL;

        /* Data buffers */
        csps_Real_t * cspsDEVgrx = NULL;
        csps_Real_t * cspsDEVgry = NULL;
        csps_Real_t * cspsDEVgrz = NULL;
        csps_Real_t * cspsDEVacx = NULL;
        csps_Real_t * cspsDEVacy = NULL;
        csps_Real_t * cspsDEVacz = NULL;
        csps_Time_t * cspsDEVsyn = NULL;

        /* Build raw log file paths */
        csps_path( cspsPath, CSPS_DEVICE_IMU_ADIS16375, NULL, NULL, NULL, cspsDEVlogp );

        /* Build file paths */
        csps_path( cspsPath, CSPS_IMU_MODDE_DEV, cspsName, CSPS_IMU_MODDE_MOD, "grx", cspsDEVgrxp );
        csps_path( cspsPath, CSPS_IMU_MODDE_DEV, cspsName, CSPS_IMU_MODDE_MOD, "gry", cspsDEVgryp );
        csps_path( cspsPath, CSPS_IMU_MODDE_DEV, cspsName, CSPS_IMU_MODDE_MOD, "grz", cspsDEVgrzp );
        csps_path( cspsPath, CSPS_IMU_MODDE_DEV, cspsName, CSPS_IMU_MODDE_MOD, "acx", cspsDEVacxp );
        csps_path( cspsPath, CSPS_IMU_MODDE_DEV, cspsName, CSPS_IMU_MODDE_MOD, "acy", cspsDEVacyp );
        csps_path( cspsPath, CSPS_IMU_MODDE_DEV, cspsName, CSPS_IMU_MODDE_MOD, "acz", cspsDEVaczp );
        csps_path( cspsPath, CSPS_IMU_MODDE_DEV, cspsName, CSPS_IMU_MODDE_MOD, "syn", cspsDEVsynp );

        /* Open file streams */
        cspsDEVlogf = fopen( cspsDEVlogp, "rb" );
        cspsDEVgrxf = fopen( cspsDEVgrxp, "wb" );
        cspsDEVgryf = fopen( cspsDEVgryp, "wb" );
        cspsDEVgrzf = fopen( cspsDEVgrzp, "wb" );
        cspsDEVacxf = fopen( cspsDEVacxp, "wb" );
        cspsDEVacyf = fopen( cspsDEVacyp, "wb" );
        cspsDEVaczf = fopen( cspsDEVaczp, "wb" );
        cspsDEVsynf = fopen( cspsDEVsynp, "wb" );

        /* Allocate buffer memory */
        cspsDEVgrx = ( csps_Real_t * ) malloc( sizeof( csps_Real_t ) * cspsDevice.dvBlock );
        cspsDEVgry = ( csps_Real_t * ) malloc( sizeof( csps_Real_t ) * cspsDevice.dvBlock );
        cspsDEVgrz = ( csps_Real_t * ) malloc( sizeof( csps_Real_t ) * cspsDevice.dvBlock );
        cspsDEVacx = ( csps_Real_t * ) malloc( sizeof( csps_Real_t ) * cspsDevice.dvBlock );
        cspsDEVacy = ( csps_Real_t * ) malloc( sizeof( csps_Real_t ) * cspsDevice.dvBlock );
        cspsDEVacz = ( csps_Real_t * ) malloc( sizeof( csps_Real_t ) * cspsDevice.dvBlock );
        cspsDEVsyn = ( csps_Time_t * ) malloc( sizeof( csps_Time_t ) * cspsDevice.dvBlock );

        /* FPGA records reading loop */
        while ( cspsReading == CSPS_TRUE ) {

            /* Reset reading index */
            cspsIndex = csps_Size_s( 0 );

            /* Reading of FPGA record by group */
            while ( ( cspsReading == CSPS_TRUE ) && ( cspsIndex < cspsDevice.dvBlock ) ) {

                /* Read FPGA record */
                cspsReaded = fread( cspsRec, 1, CSPS_DEVICE_FPGA_RECLEN, cspsDEVlogf );

                /* Verify FPGA record reading */
                if ( cspsReaded == CSPS_DEVICE_FPGA_RECLEN ) {

                    /* IMU signal filter */
                    if ( ( cspsRec[3] & csps_Byte_s( 0x0F ) ) == CSPS_DEVICE_FPGA_EVENT_IMU ) {

                        /* Assign readed data */
                        cspsDEVgrx[cspsIndex] = ( ( csps_Real_t ) ( ( int32_t * ) cspsRec )[2] ) * cspsDevice.dvGYRx;
                        cspsDEVgry[cspsIndex] = ( ( csps_Real_t ) ( ( int32_t * ) cspsRec )[3] ) * cspsDevice.dvGYRy;
                        cspsDEVgrz[cspsIndex] = ( ( csps_Real_t ) ( ( int32_t * ) cspsRec )[4] ) * cspsDevice.dvGYRz;
                        cspsDEVacx[cspsIndex] = ( ( csps_Real_t ) ( ( int32_t * ) cspsRec )[5] ) * cspsDevice.dvACCx;
                        cspsDEVacy[cspsIndex] = ( ( csps_Real_t ) ( ( int32_t * ) cspsRec )[6] ) * cspsDevice.dvACCy;
                        cspsDEVacz[cspsIndex] = ( ( csps_Real_t ) ( ( int32_t * ) cspsRec )[7] ) * cspsDevice.dvACCz;

                        /* Retrieve FPGA timestamp */
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
                fwrite( cspsDEVgrx, sizeof( csps_Real_t ) * cspsIndex, 1, cspsDEVgrxf );
                fwrite( cspsDEVgry, sizeof( csps_Real_t ) * cspsIndex, 1, cspsDEVgryf );
                fwrite( cspsDEVgrz, sizeof( csps_Real_t ) * cspsIndex, 1, cspsDEVgrzf );
                fwrite( cspsDEVacx, sizeof( csps_Real_t ) * cspsIndex, 1, cspsDEVacxf );
                fwrite( cspsDEVacy, sizeof( csps_Real_t ) * cspsIndex, 1, cspsDEVacyf );
                fwrite( cspsDEVacz, sizeof( csps_Real_t ) * cspsIndex, 1, cspsDEVaczf );
                fwrite( cspsDEVsyn, sizeof( csps_Time_t ) * cspsIndex, 1, cspsDEVsynf );

            }

        }

        /* Close file stream */
        fclose( cspsDEVlogf );
        fclose( cspsDEVgrxf );
        fclose( cspsDEVgryf );
        fclose( cspsDEVgrzf );
        fclose( cspsDEVacxf );
        fclose( cspsDEVacyf );
        fclose( cspsDEVaczf );
        fclose( cspsDEVsynf );

        /* Unallocate buffer memory */
        free( cspsDEVgrx );
        free( cspsDEVgry );
        free( cspsDEVgrz );
        free( cspsDEVacx );
        free( cspsDEVacy );
        free( cspsDEVacz );
        free( cspsDEVsyn );

        /* Return device descriptor */
        return( cspsDevice );

    }

