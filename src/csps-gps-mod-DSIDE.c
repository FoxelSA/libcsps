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

    # include "csps-gps-mod-DSIDE.h"

/*
    Source - GPS signal extraction switch
 */

    lp_Void_t lp_gps_mod_DSIDE( 

        lp_Char_t const * const lpPath, 
        lp_GPS_t  const         lpGPS

    ) {

        /* Select device */
        if ( strcmp( lpGPS.dvName, LP_DEVICE_LS20031 ) == 0 ) {

            /* LS20031 specific process */
            lp_gps_DSIDE_LS20031( lpPath, lpGPS );

        }

    }

/*
    Source - LS20031 GPS specific extractor
 */

    lp_Void_t lp_gps_DSIDE_LS20031( 

        lp_Char_t const * const lpPath, 
        lp_GPS_t  const         lpGPS 

    ) {

        /* FPGA record buffer variables */
        lp_Byte_t lpRec[LP_DEVICE_EYESIS4PI_RECLEN];

        /* GPS NMEA sentence buffer variables */
        lp_Char_t lpSentence[LP_STR_LEN] = LP_STR_INI;

        /* GPS NMEA sentence type variables */
        lp_Enum_t lpSentenceType = lp_Enum_s( 0 );

        /* Reading variables */
        lp_Enum_t lpReading = LP_TRUE;
        lp_Size_t lpIndex   = lp_Size_s( 0 );
        lp_Size_t lpReaded  = lp_Size_s( 0 );

        /* Stream path variables */
        lp_Char_t lpDEVlogp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpGPSlatp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpGPSlonp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpGPSaltp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpGPSqbfp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpGPSsynp[LP_STR_LEN] = LP_STR_INI;

        /* Stream file variables */
        lp_File_t lpDEVlogf = LP_NULL;
        lp_File_t lpGPSlatf = LP_NULL;
        lp_File_t lpGPSlonf = LP_NULL;
        lp_File_t lpGPSaltf = LP_NULL;
        lp_File_t lpGPSqbff = LP_NULL;
        lp_File_t lpGPSsynf = LP_NULL;

        /* Stream memory variables */
        lp_Real_t * lpGPSlat = LP_NULL;
        lp_Real_t * lpGPSlon = LP_NULL;
        lp_Real_t * lpGPSalt = LP_NULL;
        lp_SQBF_t * lpGPSqbf = LP_NULL;
        lp_Time_t * lpGPSsyn = LP_NULL;

        /* Build device log file paths */
        lp_path_dside( lpPath, LP_DEVICE_LS20031, LP_DEVICE_LS20031_LOG, lpDEVlogp );

        /* Build stream file paths */
        lp_path_stream( lpPath, lpGPS.dvType, lpGPS.dvTag, LP_GPS_DSIDE_MOD, LP_STREAM_CPN_LAT, lpGPSlatp );
        lp_path_stream( lpPath, lpGPS.dvType, lpGPS.dvTag, LP_GPS_DSIDE_MOD, LP_STREAM_CPN_LON, lpGPSlonp );
        lp_path_stream( lpPath, lpGPS.dvType, lpGPS.dvTag, LP_GPS_DSIDE_MOD, LP_STREAM_CPN_ALT, lpGPSaltp );
        lp_path_stream( lpPath, lpGPS.dvType, lpGPS.dvTag, LP_GPS_DSIDE_MOD, LP_STREAM_CPN_TAG, lpGPSqbfp );
        lp_path_stream( lpPath, lpGPS.dvType, lpGPS.dvTag, LP_GPS_DSIDE_MOD, LP_STREAM_CPN_SYN, lpGPSsynp );

        /* Open stream files */
        lpDEVlogf = fopen( lpDEVlogp, "rb" );
        lpGPSlatf = fopen( lpGPSlatp, "wb" );
        lpGPSlonf = fopen( lpGPSlonp, "wb" );
        lpGPSaltf = fopen( lpGPSaltp, "wb" );
        lpGPSqbff = fopen( lpGPSqbfp, "wb" );
        lpGPSsynf = fopen( lpGPSsynp, "wb" );

        /* Create streams */
        lpGPSlat = ( lp_Real_t * ) lp_stream_create( sizeof( lp_Real_t ) * lpGPS.dvBlock );
        lpGPSlon = ( lp_Real_t * ) lp_stream_create( sizeof( lp_Real_t ) * lpGPS.dvBlock );
        lpGPSalt = ( lp_Real_t * ) lp_stream_create( sizeof( lp_Real_t ) * lpGPS.dvBlock );
        lpGPSqbf = ( lp_Time_t * ) lp_stream_create( sizeof( lp_SQBF_t ) * lpGPS.dvBlock );
        lpGPSsyn = ( lp_Time_t * ) lp_stream_create( sizeof( lp_Time_t ) * lpGPS.dvBlock );

        /* FPGA records reading loop */
        while ( lpReading == LP_TRUE ) {

            /* Reset reading index */
            lpIndex = lp_Size_s( 0 );

            /* Reading of FPGA record by block */
            while ( ( lpReading == LP_TRUE ) && ( lpIndex < lpGPS.dvBlock ) ) {

                /* Read and verify FPGA record */
                if ( ( lpReaded = fread( lpRec, 1, LP_DEVICE_EYESIS4PI_RECLEN, lpDEVlogf ) ) == LP_DEVICE_EYESIS4PI_RECLEN ) {

                    /* GPS signal filter */
                    if ( ( lpRec[3] & lp_Byte_s( 0x0F ) ) == LP_DEVICE_EYESIS4PI_GPSEVT ) {

                        /* Read GPS NMEA sentence and retrieve type */
                        lpSentenceType = lp_nmea_sentence( lpRec + lp_Size_s( 8 ), ( LP_DEVICE_EYESIS4PI_RECLEN - lp_Size_s( 8 ) ) << 1, lpSentence );

                        /* GPS NMEA GGA sentence filter */
                        if ( lpSentenceType == LP_NMEA_IDENT_GGA ) {

                            /* GPS NMEA GGA sentence validation */
                            if ( lp_nmea_gga_validate( lpSentence ) == LP_TRUE ) {

                                /* Decompose NMEA GGA sentence */
                                lp_nmea_gga( lpSentence, LP_NULL,

                                    /* Sending data buffers to sentence decomposer */
                                    lpGPSlat + lpIndex,
                                    lpGPSlon + lpIndex,
                                    lpGPSalt + lpIndex,
                                    lpGPSqbf + lpIndex

                                );

                                /* Retrieve FPGA timestamp */
                                lpGPSsyn[lpIndex] = lp_timestamp( ( lp_Void_t * ) lpRec );

                                /* Update reading index */
                                lpIndex += lp_Size_s( 1 );

                            }

                        }

                    }

                } else {

                    /* Stop reading on EOF */
                    lpReading = LP_FALSE;

                }

            }

            /* Verify that the current block is not empty */
            if ( lpIndex > lp_Size_s( 0 ) ) {

                /* Export block in output streams */
                fwrite( lpGPSlat, sizeof( lp_Real_t ) * lpIndex, 1, lpGPSlatf );
                fwrite( lpGPSlon, sizeof( lp_Real_t ) * lpIndex, 1, lpGPSlonf );
                fwrite( lpGPSalt, sizeof( lp_Real_t ) * lpIndex, 1, lpGPSaltf );
                fwrite( lpGPSqbf, sizeof( lp_SQBF_t ) * lpIndex, 1, lpGPSqbff );
                fwrite( lpGPSsyn, sizeof( lp_Time_t ) * lpIndex, 1, lpGPSsynf );

            }

        }

        /* Close stream files */
        fclose( lpDEVlogf );
        fclose( lpGPSlatf );
        fclose( lpGPSlonf );
        fclose( lpGPSaltf );
        fclose( lpGPSqbff );
        fclose( lpGPSsynf );

        /* Unallocate streams */
        lpGPSlat = lp_stream_delete( lpGPSlat );
        lpGPSlon = lp_stream_delete( lpGPSlon );
        lpGPSalt = lp_stream_delete( lpGPSalt );
        lpGPSqbf = lp_stream_delete( lpGPSqbf );
        lpGPSsyn = lp_stream_delete( lpGPSsyn );

    }

