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

    lp_GPS lp_gps_mod_DSIDE( 

        const lp_Char_t * const lpPath, 
        lp_GPS                  lpDevice

    ) {

        /* Select device */
        if ( strcmp( lpDevice.dvName, LP_DEVICE_LS20031 ) == 0 ) {

            /* LS20031 specific process */
            return ( lp_gps_DSIDE_LS20031( lpPath, lpDevice ) );

        } else {

            /* Unknown device - Return descriptor */
            return( lpDevice );

        }

    }

/*
    Source - LS20031 GPS specific extractor
 */

    lp_GPS lp_gps_DSIDE_LS20031( 

        const lp_Char_t * const lpPath, 
        lp_GPS                  lpDevice 

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
        lp_Size_t lpParse   = lp_Size_s( 0 );
        lp_Size_t lpReaded  = lp_Size_s( 0 );

        /* Timestamp buffer variables */
        lp_Time_t lpTimestamp = lp_Time_s( 0 );
        lp_Time_t lpInitBreak = lp_Time_s( 0 );

        /* FPGA GPS event logger microsecond rebuilding variables */
        lp_Size_t lpModShift = lp_Size_s( 0 );

        /* Stream path variables */
        lp_Char_t lpDEVlogp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpGPSlatp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpGPSlonp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpGPSaltp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpGPSqbfp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpGPSsynp[LP_STR_LEN] = LP_STR_INI;

        /* Stream stream file variables */
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
        lp_Time_t * lpGPSqbf = LP_NULL;
        lp_Time_t * lpGPSsyn = LP_NULL;

        /* Build device log file paths */
        lp_path_dside( lpPath, LP_DEVICE_LS20031, LP_DEVICE_LS20031_LOG_FPGA, lpDEVlogp );

        /* Build stream file paths */
        lp_path_stream( lpPath, lpDevice.dvType, lpDevice.dvTag, LP_GPS_DSIDE_MOD, LP_STREAM_CPN_LAT, lpGPSlatp );
        lp_path_stream( lpPath, lpDevice.dvType, lpDevice.dvTag, LP_GPS_DSIDE_MOD, LP_STREAM_CPN_LON, lpGPSlonp );
        lp_path_stream( lpPath, lpDevice.dvType, lpDevice.dvTag, LP_GPS_DSIDE_MOD, LP_STREAM_CPN_ALT, lpGPSaltp );
        lp_path_stream( lpPath, lpDevice.dvType, lpDevice.dvTag, LP_GPS_DSIDE_MOD, LP_STREAM_CPN_QBF, lpGPSqbfp );
        lp_path_stream( lpPath, lpDevice.dvType, lpDevice.dvTag, LP_GPS_DSIDE_MOD, LP_STREAM_CPN_SYN, lpGPSsynp );

        /* Open stream files */
        lpDEVlogf = fopen( lpDEVlogp, "rb" );
        lpGPSlatf = fopen( lpGPSlatp, "wb" );
        lpGPSlonf = fopen( lpGPSlonp, "wb" );
        lpGPSaltf = fopen( lpGPSaltp, "wb" );
        lpGPSqbff = fopen( lpGPSqbfp, "wb" );
        lpGPSsynf = fopen( lpGPSsynp, "wb" );

        /* Allocate stream memory */
        lpGPSlat = ( lp_Real_t * ) lp_stream_create( sizeof( lp_Real_t ) * lpDevice.dvBlock );
        lpGPSlon = ( lp_Real_t * ) lp_stream_create( sizeof( lp_Real_t ) * lpDevice.dvBlock );
        lpGPSalt = ( lp_Real_t * ) lp_stream_create( sizeof( lp_Real_t ) * lpDevice.dvBlock );
        lpGPSqbf = ( lp_Time_t * ) lp_stream_create( sizeof( lp_Time_t ) * lpDevice.dvBlock );
        lpGPSsyn = ( lp_Time_t * ) lp_stream_create( sizeof( lp_Time_t ) * lpDevice.dvBlock );

        /* FPGA records reading loop */
        while ( lpReading == LP_TRUE ) {

            /* Reset reading index */
            lpIndex = lp_Size_s( 0 );

            /* Reading of FPGA record by block */
            while ( ( lpReading == LP_TRUE ) && ( lpIndex < lpDevice.dvBlock ) ) {

                /* Read and verify FPGA record reading */
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

                                /* Verify FPGA timestamp rebuilding mode */
                                if ( lpModShift == lp_Size_s( 0 ) ) {

                                    /* Rebuild FPGA timestamp based on 1pps trigger */
                                    if ( lpParse == lp_Size_s( 0 ) ) {

                                        /* Consider FPGA initial timestamp for first segment reconstruction */
                                        lpGPSsyn[lpIndex] = lp_timestamp( ( lp_Void_t * ) lpRec );

                                        /* Memorize initial unix timestamp second */
                                        lpInitBreak = lp_timestamp_sec( lpGPSsyn[lpIndex] );

                                    } else {

                                        /* Search for initial complete second range */
                                        if ( lp_timestamp_sec( lp_timestamp( ( lp_Void_t * ) lpRec ) ) == lpInitBreak ) {

                                            /* Build current timestamp based on previous */
                                            lpGPSsyn[lpIndex] = lp_timestamp_add( lpTimestamp, lp_Time_s( 200000 ) );

                                        } else {

                                            /* Consider FPGA timestamp for initial reset */
                                            lpGPSsyn[lpIndex] = lp_timestamp( ( lp_Void_t * ) lpRec );

                                            /* Set the modular shift parameter */
                                            lpModShift = lpParse;

                                        }

                                    }

                                } else {

                                    /* Verify congruence reset condition */
                                    if ( ( ( lpParse - lpModShift ) % lpDevice.dvifreq ) == 0 ) {

                                        /* Consider FPGA timestamp for periodic reset */
                                        lpGPSsyn[lpIndex] = lp_timestamp( ( lp_Void_t * ) lpRec );

                                    } else {

                                        /* Build current timestamp based on previous */
                                        lpGPSsyn[lpIndex] = lp_timestamp_add( lpTimestamp, lp_Time_s( 200000 ) );

                                    }

                                }

                                /* Memorize current timestemp */
                                lpTimestamp = lpGPSsyn[lpIndex];

                                /* Update reading index */
                                lpIndex += lp_Size_s( 1 );

                                /* Update overall parse index */
                                lpParse += lp_Size_s( 1 );

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
                fwrite( lpGPSqbf, sizeof( lp_Time_t ) * lpIndex, 1, lpGPSqbff );
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

        /* Unallocate stream memory */
        lpGPSlat = lp_stream_delete( lpGPSlat );
        lpGPSlon = lp_stream_delete( lpGPSlon );
        lpGPSalt = lp_stream_delete( lpGPSalt );
        lpGPSqbf = lp_stream_delete( lpGPSqbf );
        lpGPSsyn = lp_stream_delete( lpGPSsyn );

        /* Return device descriptor */
        return( lpDevice );

    }

