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

    # include "csps-imu-mod-DSIDE.h"

/*
    Source - IMU signal extraction switch
 */

    lp_Void_t lp_imu_mod_DSIDE( 

        lp_Char_t const * const lpPath, 
        lp_IMU_t  const         lpIMU

    ) {

        /* Select device */
        if ( strcmp( lpIMU.dvName, LP_DEVICE_ADIS16375 ) == 0 ) {

            /* ADIS16375 specific process */
            lp_imu_DSIDE_ADIS16375( lpPath, lpIMU );

        }

    }

/*
    Source - ADIS16375 IMU specific extractor
 */

    lp_Void_t lp_imu_DSIDE_ADIS16375( 

        lp_Char_t const * const lpPath, 
        lp_IMU_t  const         lpIMU

    ) {

        /* FPGA record buffer variables */
        lp_Byte_t lpRec[LP_DEVICE_EYESIS4PI_RECLEN];

        /* Reading variables */
        lp_Enum_t lpReading = LP_TRUE;
        lp_Size_t lpIndex   = lp_Size_s( 0 );
        lp_Size_t lpReaded  = lp_Size_s( 0 );

        /* Stream path variables */
        lp_Char_t lpDEVlogp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpIMUgrxp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpIMUgryp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpIMUgrzp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpIMUacxp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpIMUacyp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpIMUaczp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpIMUsynp[LP_STR_LEN] = LP_STR_INI;

        /* Stream file variables */
        lp_File_t lpDEVlogf = LP_NULL;
        lp_File_t lpIMUgrxf = LP_NULL;
        lp_File_t lpIMUgryf = LP_NULL;
        lp_File_t lpIMUgrzf = LP_NULL;
        lp_File_t lpIMUacxf = LP_NULL;
        lp_File_t lpIMUacyf = LP_NULL;
        lp_File_t lpIMUaczf = LP_NULL;
        lp_File_t lpIMUsynf = LP_NULL;

        /* Stream memory variables */
        lp_Real_t * lpIMUgrx = LP_NULL;
        lp_Real_t * lpIMUgry = LP_NULL;
        lp_Real_t * lpIMUgrz = LP_NULL;
        lp_Real_t * lpIMUacx = LP_NULL;
        lp_Real_t * lpIMUacy = LP_NULL;
        lp_Real_t * lpIMUacz = LP_NULL;
        lp_Time_t * lpIMUsyn = LP_NULL;

        /* Build device log file paths */
        lp_path_dside( lpPath, LP_DEVICE_ADIS16375, LP_DEVICE_ADIS16375_LOG, lpDEVlogp );

        /* Build stream file paths */
        lp_path_stream( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_DSIDE_MOD, LP_STREAM_CPN_GRX, lpIMUgrxp );
        lp_path_stream( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_DSIDE_MOD, LP_STREAM_CPN_GRY, lpIMUgryp );
        lp_path_stream( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_DSIDE_MOD, LP_STREAM_CPN_GRZ, lpIMUgrzp );
        lp_path_stream( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_DSIDE_MOD, LP_STREAM_CPN_ACX, lpIMUacxp );
        lp_path_stream( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_DSIDE_MOD, LP_STREAM_CPN_ACY, lpIMUacyp );
        lp_path_stream( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_DSIDE_MOD, LP_STREAM_CPN_ACZ, lpIMUaczp );
        lp_path_stream( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_DSIDE_MOD, LP_STREAM_CPN_SYN, lpIMUsynp );

        /* Open stream files */
        lpDEVlogf = fopen( lpDEVlogp, "rb" );
        lpIMUgrxf = fopen( lpIMUgrxp, "wb" );
        lpIMUgryf = fopen( lpIMUgryp, "wb" );
        lpIMUgrzf = fopen( lpIMUgrzp, "wb" );
        lpIMUacxf = fopen( lpIMUacxp, "wb" );
        lpIMUacyf = fopen( lpIMUacyp, "wb" );
        lpIMUaczf = fopen( lpIMUaczp, "wb" );
        lpIMUsynf = fopen( lpIMUsynp, "wb" );

        /* Create streams */
        lpIMUgrx = ( lp_Real_t * ) lp_stream_create( sizeof( lp_Real_t ) * lpIMU.dvBlock );
        lpIMUgry = ( lp_Real_t * ) lp_stream_create( sizeof( lp_Real_t ) * lpIMU.dvBlock );
        lpIMUgrz = ( lp_Real_t * ) lp_stream_create( sizeof( lp_Real_t ) * lpIMU.dvBlock );
        lpIMUacx = ( lp_Real_t * ) lp_stream_create( sizeof( lp_Real_t ) * lpIMU.dvBlock );
        lpIMUacy = ( lp_Real_t * ) lp_stream_create( sizeof( lp_Real_t ) * lpIMU.dvBlock );
        lpIMUacz = ( lp_Real_t * ) lp_stream_create( sizeof( lp_Real_t ) * lpIMU.dvBlock );
        lpIMUsyn = ( lp_Time_t * ) lp_stream_create( sizeof( lp_Time_t ) * lpIMU.dvBlock );

        /* FPGA records reading loop */
        while ( lpReading == LP_TRUE ) {

            /* Reset reading index */
            lpIndex = lp_Size_s( 0 );

            /* Reading of FPGA record by block */
            while ( ( lpReading == LP_TRUE ) && ( lpIndex < lpIMU.dvBlock ) ) {

                /* Read and verify FPGA record */
                if ( ( lpReaded = fread( lpRec, 1, LP_DEVICE_EYESIS4PI_RECLEN, lpDEVlogf ) ) == LP_DEVICE_EYESIS4PI_RECLEN ) {

                    /* IMU signal filter */
                    if ( ( lpRec[3] & lp_Byte_s( 0x0F ) ) == LP_DEVICE_EYESIS4PI_IMUEVT ) {

                        /* Assign readed data */
                        lpIMUgrx[lpIndex] = ( ( lp_Real_t ) ( ( int32_t * ) lpRec )[2] ) * lpIMU.dvGYRx;
                        lpIMUgry[lpIndex] = ( ( lp_Real_t ) ( ( int32_t * ) lpRec )[3] ) * lpIMU.dvGYRy;
                        lpIMUgrz[lpIndex] = ( ( lp_Real_t ) ( ( int32_t * ) lpRec )[4] ) * lpIMU.dvGYRz;
                        lpIMUacx[lpIndex] = ( ( lp_Real_t ) ( ( int32_t * ) lpRec )[5] ) * lpIMU.dvACCx;
                        lpIMUacy[lpIndex] = ( ( lp_Real_t ) ( ( int32_t * ) lpRec )[6] ) * lpIMU.dvACCy;
                        lpIMUacz[lpIndex] = ( ( lp_Real_t ) ( ( int32_t * ) lpRec )[7] ) * lpIMU.dvACCz;

                        /* Retrieve FPGA timestamp */
                        lpIMUsyn[lpIndex] = lp_timestamp( ( lp_Void_t * ) lpRec );

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
                fwrite( lpIMUgrx, sizeof( lp_Real_t ) * lpIndex, 1, lpIMUgrxf );
                fwrite( lpIMUgry, sizeof( lp_Real_t ) * lpIndex, 1, lpIMUgryf );
                fwrite( lpIMUgrz, sizeof( lp_Real_t ) * lpIndex, 1, lpIMUgrzf );
                fwrite( lpIMUacx, sizeof( lp_Real_t ) * lpIndex, 1, lpIMUacxf );
                fwrite( lpIMUacy, sizeof( lp_Real_t ) * lpIndex, 1, lpIMUacyf );
                fwrite( lpIMUacz, sizeof( lp_Real_t ) * lpIndex, 1, lpIMUaczf );
                fwrite( lpIMUsyn, sizeof( lp_Time_t ) * lpIndex, 1, lpIMUsynf );

            }

        }

        /* Close stream files */
        fclose( lpDEVlogf );
        fclose( lpIMUgrxf );
        fclose( lpIMUgryf );
        fclose( lpIMUgrzf );
        fclose( lpIMUacxf );
        fclose( lpIMUacyf );
        fclose( lpIMUaczf );
        fclose( lpIMUsynf );

        /* Unallocate streams */
        lpIMUgrx = lp_stream_delete( lpIMUgrx );
        lpIMUgry = lp_stream_delete( lpIMUgry );
        lpIMUgrz = lp_stream_delete( lpIMUgrz );
        lpIMUacx = lp_stream_delete( lpIMUacx );
        lpIMUacy = lp_stream_delete( lpIMUacy );
        lpIMUacz = lp_stream_delete( lpIMUacz );
        lpIMUsyn = lp_stream_delete( lpIMUsyn );

    }

