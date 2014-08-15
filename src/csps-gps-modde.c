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

    # include "csps-gps-modde.h"

/*
    Source - GPS data extractor module
 */

    lp_GPS lp_gps_modde( const lp_Char_t * const lpPath, lp_GPS lpDevice) {

        /* Select device */
        if ( strcmp( lpDevice.dvName, LP_DEVICE_GPS_LS20031 ) == 0 ) {

            /* ADIS16375 specific process */
            return ( lp_gps_LS20031( lpPath, lpDevice ) );

        } else {

            /* Unknown device - Return descriptor */
            return( lpDevice );

        }

    }

/*
    Source - GPS LS20031 specific extractor
 */

    lp_GPS lp_gps_LS20031( const lp_Char_t * const lpPath, lp_GPS lpDevice ) {

        /* FPGA record buffer */
        lp_Byte_t lpRec[LP_DEVICE_CAM_EYESIS4PI_RECLEN];

        /* GPS NMEA sentence buffer */
        lp_Char_t lpSentence[LP_STR_LEN] = LP_STR_INI;

        /* GPS NMEA sentence type */
        lp_Enum_t lpSentenceType = lp_Enum_s( 0 );

        /* Reading variables */
        lp_Enum_t lpReading = LP_TRUE;
        lp_Size_t lpIndex = lp_Size_s( 0 );
        lp_Size_t lpParse = lp_Size_s( 0 );
        lp_Size_t lpReaded = lp_Size_s( 0 );

        /* Timestamp buffer value */
        lp_Time_t lpTimestamp = lp_Time_s( 0 );
        lp_Time_t lpInitBreak = lp_Time_s( 0 );

        /* FPGA GPS event logger microsecond rebuilding variable */
        lp_Size_t lpModShift = lp_Size_s( 0 );

        /* Paths string buffer */
        lp_Char_t lpDEVlogp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpDEVsynp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpDEVlatp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpDEVlonp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpDEValtp[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpDEVqbfp[LP_STR_LEN] = LP_STR_INI;

        /* Stream handles */
        lp_File_t lpDEVlogf = NULL;
        lp_File_t lpDEVsynf = NULL;
        lp_File_t lpDEVlatf = NULL;
        lp_File_t lpDEVlonf = NULL;
        lp_File_t lpDEValtf = NULL;
        lp_File_t lpDEVqbff = NULL;

        /* Data buffers */
        lp_Real_t * lpDEVlat = NULL;
        lp_Real_t * lpDEVlon = NULL;
        lp_Real_t * lpDEValt = NULL;
        lp_Time_t * lpDEVqbf = NULL;
        lp_Time_t * lpDEVsyn = NULL;

        /* Build raw log file paths */
        lp_path( lpPath, LP_DEVICE_GPS_LS20031, NULL, NULL, NULL, lpDEVlogp );

        /* Build file paths */
        lp_path( lpPath, LP_GPS_MODDE_DEV, lpDevice.dvTag, LP_GPS_MODDE_MOD, "lat", lpDEVlatp );
        lp_path( lpPath, LP_GPS_MODDE_DEV, lpDevice.dvTag, LP_GPS_MODDE_MOD, "lon", lpDEVlonp );
        lp_path( lpPath, LP_GPS_MODDE_DEV, lpDevice.dvTag, LP_GPS_MODDE_MOD, "alt", lpDEValtp );
        lp_path( lpPath, LP_GPS_MODDE_DEV, lpDevice.dvTag, LP_GPS_MODDE_MOD, "qbf", lpDEVqbfp );
        lp_path( lpPath, LP_GPS_MODDE_DEV, lpDevice.dvTag, LP_GPS_MODDE_MOD, "syn", lpDEVsynp );

        /* Open file streams */
        lpDEVlogf = fopen( lpDEVlogp, "rb" );
        lpDEVlatf = fopen( lpDEVlatp, "wb" );
        lpDEVlonf = fopen( lpDEVlonp, "wb" );
        lpDEValtf = fopen( lpDEValtp, "wb" );
        lpDEVqbff = fopen( lpDEVqbfp, "wb" );
        lpDEVsynf = fopen( lpDEVsynp, "wb" );

        /* Allocate buffer memory */
        lpDEVlat = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpDevice.dvBlock );
        lpDEVlon = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpDevice.dvBlock );
        lpDEValt = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpDevice.dvBlock );
        lpDEVqbf = ( lp_Time_t * ) malloc( sizeof( lp_Time_t ) * lpDevice.dvBlock );
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

                    /* GPS signal filter */
                    if ( ( lpRec[3] & lp_Byte_s( 0x0F ) ) == LP_DEVICE_CAM_EYESIS4PI_GPSEVT ) {

                        /* Read GPS NMEA sentence and retrieve type */
                        lpSentenceType = lp_nmea_sentence( lpRec + lp_Size_s( 8 ), ( LP_DEVICE_CAM_EYESIS4PI_RECLEN - lp_Size_s( 8 ) ) << 1, lpSentence );

                        /* GPS NMEA GGA sentence filter */
                        if ( lpSentenceType == LP_NMEA_IDENT_GGA ) {

                            /* GPS NMEA GGA sentence validation */
                            if ( lp_nmea_gga_validate( lpSentence ) == LP_TRUE ) {

                                /* Decompose NMEA GGA sentence */
                                lp_nmea_gga( lpSentence, NULL,

                                    /* Sending data buffers to decomposer */
                                    lpDEVlat + lpIndex,
                                    lpDEVlon + lpIndex,
                                    lpDEValt + lpIndex,
                                    lpDEVqbf + lpIndex

                                );

                                /* Check rebuilding mode */
                                if ( lpModShift == lp_Size_s( 0 ) ) {

                                    /* Rebuild FPGA timestamp based on 1pps trigger */
                                    if ( lpParse == lp_Size_s( 0 ) ) {

                                        /* Consider FPGA initial timestamp for first segment reconstruction */
                                        lpDEVsyn[lpIndex] = lp_timestamp( ( lp_Void_t * ) lpRec );

                                        /* Memorize initial unix timestamp second */
                                        lpInitBreak = lp_timestamp_sec( lpDEVsyn[lpIndex] );

                                    } else {

                                        /* Search for initial complete second range */
                                        if ( lp_timestamp_sec( lp_timestamp( ( lp_Void_t * ) lpRec ) ) == lpInitBreak ) {

                                            /* Build current timestamp based on previous */
                                            lpDEVsyn[lpIndex] = lp_timestamp_add( lpTimestamp, lp_Time_s( 200000 ) );

                                        } else {

                                            /* Consider FPGA timestamp for initial reset */
                                            lpDEVsyn[lpIndex] = lp_timestamp( ( lp_Void_t * ) lpRec );

                                            /* Set the modular shift parameter */
                                            lpModShift = lpParse;

                                        }

                                    }

                                } else {

                                    /* Verify congurence reset condition */
                                    if ( ( ( lpParse - lpModShift ) % lpDevice.dvifreq ) == 0 ) {

                                        /* Consider FPGA timestamp for periodic reset */
                                        lpDEVsyn[lpIndex] = lp_timestamp( ( lp_Void_t * ) lpRec );

                                    } else {

                                        /* Build current timestamp based on previous */
                                        lpDEVsyn[lpIndex] = lp_timestamp_add( lpTimestamp, lp_Time_s( 200000 ) );

                                    }

                                }

                                /* Memorize current timestemp */
                                lpTimestamp = lpDEVsyn[lpIndex];

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
                fwrite( lpDEVlat, sizeof( lp_Real_t ) * lpIndex, 1, lpDEVlatf );
                fwrite( lpDEVlon, sizeof( lp_Real_t ) * lpIndex, 1, lpDEVlonf );
                fwrite( lpDEValt, sizeof( lp_Real_t ) * lpIndex, 1, lpDEValtf );
                fwrite( lpDEVqbf, sizeof( lp_Time_t ) * lpIndex, 1, lpDEVqbff );
                fwrite( lpDEVsyn, sizeof( lp_Time_t ) * lpIndex, 1, lpDEVsynf );

            }

        }

        /* Close file stream */
        fclose( lpDEVlogf );
        fclose( lpDEVlatf );
        fclose( lpDEVlonf );
        fclose( lpDEValtf );
        fclose( lpDEVqbff );
        fclose( lpDEVsynf );

        /* Unallocate buffer memory */
        free( lpDEVsyn );
        free( lpDEVlat );
        free( lpDEVlon );
        free( lpDEValt );
        free( lpDEVqbf );

        /* Return device descriptor */
        return( lpDevice );

    }

