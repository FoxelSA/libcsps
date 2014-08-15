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

    lp_IMU lp_imu_modde( const lp_Char_t * const lpPath, lp_IMU lpDevice, const lp_Char_t * const lpName ) {

        /* Select device */
        if ( strcmp( lpDevice.dvName, LP_DEVICE_IMU_ADIS16375 ) == 0 ) {

            /* ADIS16375 specific process */
            return( lp_imu_ADIS16375( lpPath, lpDevice, lpName ) );

        } else {

            /* Unknown device - Return descriptor */
            return( lpDevice );

        }

    }

/*
    Source - IMU ADIS16375 specific extractor
 */

    lp_IMU lp_imu_ADIS16375( const lp_Char_t * const lpPath, lp_IMU lpDevice, const lp_Char_t * const lpName ) {

        /* FPGA record buffer */
        lp_Byte_t lpRec[LP_DEVICE_CAM_EYESIS4PI_RECLEN];

        /* Reading variables */
        lp_Enum_t lpReading = LP_TRUE;
        lp_Size_t lpIndex = lp_Size_s( 0 );
        lp_Size_t lpReaded = lp_Size_s( 0 );

        /* Paths string buffer */
        lp_Char_t lpDEVlogp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpDEVgrxp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpDEVgryp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpDEVgrzp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpDEVacxp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpDEVacyp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpDEVaczp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpDEVsynp[LP_STR_LEN] = LP_STR_INI;

        /* Stream handles */
        lp_File_t lpDEVlogf = NULL;
        lp_File_t lpDEVgrxf = NULL;
        lp_File_t lpDEVgryf = NULL;
        lp_File_t lpDEVgrzf = NULL;
        lp_File_t lpDEVacxf = NULL;
        lp_File_t lpDEVacyf = NULL;
        lp_File_t lpDEVaczf = NULL;
        lp_File_t lpDEVsynf = NULL;

        /* Data buffers */
        lp_Real_t * lpDEVgrx = NULL;
        lp_Real_t * lpDEVgry = NULL;
        lp_Real_t * lpDEVgrz = NULL;
        lp_Real_t * lpDEVacx = NULL;
        lp_Real_t * lpDEVacy = NULL;
        lp_Real_t * lpDEVacz = NULL;
        lp_Time_t * lpDEVsyn = NULL;

        /* Build raw log file paths */
        lp_path( lpPath, LP_DEVICE_IMU_ADIS16375, NULL, NULL, NULL, lpDEVlogp );

        /* Build file paths */
        lp_path( lpPath, LP_IMU_MODDE_DEV, lpName, LP_IMU_MODDE_MOD, "grx", lpDEVgrxp );
        lp_path( lpPath, LP_IMU_MODDE_DEV, lpName, LP_IMU_MODDE_MOD, "gry", lpDEVgryp );
        lp_path( lpPath, LP_IMU_MODDE_DEV, lpName, LP_IMU_MODDE_MOD, "grz", lpDEVgrzp );
        lp_path( lpPath, LP_IMU_MODDE_DEV, lpName, LP_IMU_MODDE_MOD, "acx", lpDEVacxp );
        lp_path( lpPath, LP_IMU_MODDE_DEV, lpName, LP_IMU_MODDE_MOD, "acy", lpDEVacyp );
        lp_path( lpPath, LP_IMU_MODDE_DEV, lpName, LP_IMU_MODDE_MOD, "acz", lpDEVaczp );
        lp_path( lpPath, LP_IMU_MODDE_DEV, lpName, LP_IMU_MODDE_MOD, "syn", lpDEVsynp );

        /* Open file streams */
        lpDEVlogf = fopen( lpDEVlogp, "rb" );
        lpDEVgrxf = fopen( lpDEVgrxp, "wb" );
        lpDEVgryf = fopen( lpDEVgryp, "wb" );
        lpDEVgrzf = fopen( lpDEVgrzp, "wb" );
        lpDEVacxf = fopen( lpDEVacxp, "wb" );
        lpDEVacyf = fopen( lpDEVacyp, "wb" );
        lpDEVaczf = fopen( lpDEVaczp, "wb" );
        lpDEVsynf = fopen( lpDEVsynp, "wb" );

        /* Allocate buffer memory */
        lpDEVgrx = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpDevice.dvBlock );
        lpDEVgry = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpDevice.dvBlock );
        lpDEVgrz = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpDevice.dvBlock );
        lpDEVacx = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpDevice.dvBlock );
        lpDEVacy = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpDevice.dvBlock );
        lpDEVacz = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpDevice.dvBlock );
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

                    /* IMU signal filter */
                    if ( ( lpRec[3] & lp_Byte_s( 0x0F ) ) == LP_DEVICE_CAM_EYESIS4PI_IMUEVT ) {

                        /* Assign readed data */
                        lpDEVgrx[lpIndex] = ( ( lp_Real_t ) ( ( int32_t * ) lpRec )[2] ) * lpDevice.dvGYRx;
                        lpDEVgry[lpIndex] = ( ( lp_Real_t ) ( ( int32_t * ) lpRec )[3] ) * lpDevice.dvGYRy;
                        lpDEVgrz[lpIndex] = ( ( lp_Real_t ) ( ( int32_t * ) lpRec )[4] ) * lpDevice.dvGYRz;
                        lpDEVacx[lpIndex] = ( ( lp_Real_t ) ( ( int32_t * ) lpRec )[5] ) * lpDevice.dvACCx;
                        lpDEVacy[lpIndex] = ( ( lp_Real_t ) ( ( int32_t * ) lpRec )[6] ) * lpDevice.dvACCy;
                        lpDEVacz[lpIndex] = ( ( lp_Real_t ) ( ( int32_t * ) lpRec )[7] ) * lpDevice.dvACCz;

                        /* Retrieve FPGA timestamp */
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
                fwrite( lpDEVgrx, sizeof( lp_Real_t ) * lpIndex, 1, lpDEVgrxf );
                fwrite( lpDEVgry, sizeof( lp_Real_t ) * lpIndex, 1, lpDEVgryf );
                fwrite( lpDEVgrz, sizeof( lp_Real_t ) * lpIndex, 1, lpDEVgrzf );
                fwrite( lpDEVacx, sizeof( lp_Real_t ) * lpIndex, 1, lpDEVacxf );
                fwrite( lpDEVacy, sizeof( lp_Real_t ) * lpIndex, 1, lpDEVacyf );
                fwrite( lpDEVacz, sizeof( lp_Real_t ) * lpIndex, 1, lpDEVaczf );
                fwrite( lpDEVsyn, sizeof( lp_Time_t ) * lpIndex, 1, lpDEVsynf );

            }

        }

        /* Close file stream */
        fclose( lpDEVlogf );
        fclose( lpDEVgrxf );
        fclose( lpDEVgryf );
        fclose( lpDEVgrzf );
        fclose( lpDEVacxf );
        fclose( lpDEVacyf );
        fclose( lpDEVaczf );
        fclose( lpDEVsynf );

        /* Unallocate buffer memory */
        free( lpDEVgrx );
        free( lpDEVgry );
        free( lpDEVgrz );
        free( lpDEVacx );
        free( lpDEVacy );
        free( lpDEVacz );
        free( lpDEVsyn );

        /* Return device descriptor */
        return( lpDevice );

    }

