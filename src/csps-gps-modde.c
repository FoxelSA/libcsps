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

    csps_GPS csps_gps_modde( const csps_Char_t * const cspsPath, csps_GPS cspsDevice, const csps_Char_t * const cspsName ) {

        /* Select device */
        if ( strcmp( cspsDevice.dvName, CSPS_DEVICE_GPS_LS20031 ) == 0 ) {

            /* ADIS16375 specific process */
            return ( csps_gps_LS20031( cspsPath, cspsDevice, cspsName ) );

        } else {

            /* Unknown device - Return descriptor */
            return( cspsDevice );

        }

    }

/*
    Source - GPS LS20031 specific extractor
 */

    csps_GPS csps_gps_LS20031( const csps_Char_t * const cspsPath, csps_GPS cspsDevice, const csps_Char_t * const cspsName ) {

        /* FPGA record buffer */
        csps_Byte_t cspsRec[CSPS_DEVICE_FPGA_RECLEN];

        /* GPS NMEA sentence buffer */
        csps_Char_t cspsSentence[CSPS_STR_LEN] = CSPS_STR_INI;

        /* GPS NMEA sentence type */
        csps_Enum_t cspsSentenceType = csps_Enum_s( 0 );

        /* Reading variables */
        csps_Enum_t cspsReading = CSPS_TRUE;
        csps_Size_t cspsIndex = csps_Size_s( 0 );
        csps_Size_t cspsParse = csps_Size_s( 0 );
        csps_Size_t cspsReaded = csps_Size_s( 0 );

        /* Timestamp buffer value */
        csps_Time_t cspsTimestamp = csps_Time_s( 0 );
        csps_Time_t cspsInitBreak = csps_Time_s( 0 );

        /* FPGA GPS event logger microsecond rebuilding variable */
        csps_Size_t cspsModShift = csps_Size_s( 0 );

        /* Paths string buffer */
        csps_Char_t cspsDEVlogp[CSPS_STR_LEN] = CSPS_STR_INI;
        csps_Char_t cspsDEVsynp[CSPS_STR_LEN] = CSPS_STR_INI;
        csps_Char_t cspsDEVlatp[CSPS_STR_LEN] = CSPS_STR_INI;
        csps_Char_t cspsDEVlonp[CSPS_STR_LEN] = CSPS_STR_INI;
        csps_Char_t cspsDEValtp[CSPS_STR_LEN] = CSPS_STR_INI;
        csps_Char_t cspsDEVqbfp[CSPS_STR_LEN] = CSPS_STR_INI;

        /* Stream handles */
        csps_File_t cspsDEVlogf = NULL;
        csps_File_t cspsDEVsynf = NULL;
        csps_File_t cspsDEVlatf = NULL;
        csps_File_t cspsDEVlonf = NULL;
        csps_File_t cspsDEValtf = NULL;
        csps_File_t cspsDEVqbff = NULL;

        /* Data buffers */
        csps_Real_t * cspsDEVlat = NULL;
        csps_Real_t * cspsDEVlon = NULL;
        csps_Real_t * cspsDEValt = NULL;
        csps_Time_t * cspsDEVqbf = NULL;
        csps_Time_t * cspsDEVsyn = NULL;

        /* Build raw log file paths */
        csps_path( cspsPath, CSPS_DEVICE_GPS_LS20031, NULL, NULL, NULL, cspsDEVlogp );

        /* Build file paths */
        csps_path( cspsPath, CSPS_GPS_MODDE_DEV, cspsName, CSPS_GPS_MODDE_MOD, "lat", cspsDEVlatp );
        csps_path( cspsPath, CSPS_GPS_MODDE_DEV, cspsName, CSPS_GPS_MODDE_MOD, "lon", cspsDEVlonp );
        csps_path( cspsPath, CSPS_GPS_MODDE_DEV, cspsName, CSPS_GPS_MODDE_MOD, "alt", cspsDEValtp );
        csps_path( cspsPath, CSPS_GPS_MODDE_DEV, cspsName, CSPS_GPS_MODDE_MOD, "qbf", cspsDEVqbfp );
        csps_path( cspsPath, CSPS_GPS_MODDE_DEV, cspsName, CSPS_GPS_MODDE_MOD, "syn", cspsDEVsynp );

        /* Open file streams */
        cspsDEVlogf = fopen( cspsDEVlogp, "rb" );
        cspsDEVlatf = fopen( cspsDEVlatp, "wb" );
        cspsDEVlonf = fopen( cspsDEVlonp, "wb" );
        cspsDEValtf = fopen( cspsDEValtp, "wb" );
        cspsDEVqbff = fopen( cspsDEVqbfp, "wb" );
        cspsDEVsynf = fopen( cspsDEVsynp, "wb" );

        /* Allocate buffer memory */
        cspsDEVlat = ( csps_Real_t * ) malloc( sizeof( csps_Real_t ) * cspsDevice.dvBlock );
        cspsDEVlon = ( csps_Real_t * ) malloc( sizeof( csps_Real_t ) * cspsDevice.dvBlock );
        cspsDEValt = ( csps_Real_t * ) malloc( sizeof( csps_Real_t ) * cspsDevice.dvBlock );
        cspsDEVqbf = ( csps_Time_t * ) malloc( sizeof( csps_Time_t ) * cspsDevice.dvBlock );
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

                    /* GPS signal filter */
                    if ( ( cspsRec[3] & csps_Byte_s( 0x0F ) ) == CSPS_DEVICE_FPGA_EVENT_GPS ) {

                        /* Read GPS NMEA sentence and retrieve type */
                        cspsSentenceType = csps_nmea_sentence( cspsRec + csps_Size_s( 8 ), cspsSentence );

                        /* GPS NMEA GGA sentence filter */
                        if ( cspsSentenceType == CSPS_NMEA_IDENT_GGA ) {

                            /* GPS NMEA GGA sentence validation */
                            if ( csps_nmea_gga_validate( cspsSentence ) == CSPS_TRUE ) {

                                /* Decompose NMEA GGA sentence */
                                csps_nmea_gga( cspsSentence, NULL,

                                    /* Sending data buffers to decomposer */
                                    cspsDEVlat + cspsIndex,
                                    cspsDEVlon + cspsIndex,
                                    cspsDEValt + cspsIndex,
                                    cspsDEVqbf + cspsIndex

                                );

                                /* Check rebuilding mode */
                                if ( cspsModShift == csps_Size_s( 0 ) ) {

                                    /* Rebuild FPGA timestamp based on 1pps trigger */
                                    if ( cspsParse == csps_Size_s( 0 ) ) {

                                        /* Consider FPGA initial timestamp for first segment reconstruction */
                                        cspsDEVsyn[cspsIndex] = csps_timestamp( ( csps_Void_t * ) cspsRec );

                                        /* Memorize initial unix timestamp second */
                                        cspsInitBreak = csps_timestamp_sec( cspsDEVsyn[cspsIndex] );

                                    } else {

                                        /* Search for initial complete second range */
                                        if ( csps_timestamp_sec( csps_timestamp( ( csps_Void_t * ) cspsRec ) ) == cspsInitBreak ) {

                                            /* Build current timestamp based on previous */
                                            cspsDEVsyn[cspsIndex] = csps_timestamp_add( cspsTimestamp, csps_Time_s( 200000 ) );

                                        } else {

                                            /* Consider FPGA timestamp for initial reset */
                                            cspsDEVsyn[cspsIndex] = csps_timestamp( ( csps_Void_t * ) cspsRec );

                                            /* Set the modular shift parameter */
                                            cspsModShift = cspsParse;

                                        }

                                    }

                                } else {

                                    /* Verify congurence reset condition */
                                    if ( ( ( cspsParse - cspsModShift ) % cspsDevice.dvifreq ) == 0 ) {

                                        /* Consider FPGA timestamp for periodic reset */
                                        cspsDEVsyn[cspsIndex] = csps_timestamp( ( csps_Void_t * ) cspsRec );

                                    } else {

                                        /* Build current timestamp based on previous */
                                        cspsDEVsyn[cspsIndex] = csps_timestamp_add( cspsTimestamp, csps_Time_s( 200000 ) );

                                    }

                                }

                                /* Memorize current timestemp */
                                cspsTimestamp = cspsDEVsyn[cspsIndex];

                                fprintf( stdout, "%lu.%lu  ", csps_timestamp_sec( csps_timestamp( ( csps_Void_t * ) cspsRec ) ), csps_timestamp_usec( csps_timestamp( ( csps_Void_t * ) cspsRec ) ) );
                                fprintf( stdout, "%lu.%lu\n", csps_timestamp_sec( cspsDEVsyn[cspsIndex] ), csps_timestamp_usec( cspsDEVsyn[cspsIndex] ) );

                                /* Update reading index */
                                cspsIndex += csps_Size_s( 1 );

                                /* Update overall parse index */
                                cspsParse += csps_Size_s( 1 );

                            }

                        }

                    }

                } else {

                    /* Stop reading on EOF */
                    cspsReading = CSPS_FALSE;

                }

            }

            /* Verify that the current block is not empty */
            if ( cspsIndex > csps_Size_s( 0 ) ) {

                /* Export block in output streams */
                fwrite( cspsDEVlat, sizeof( csps_Real_t ) * cspsIndex, 1, cspsDEVlatf );
                fwrite( cspsDEVlon, sizeof( csps_Real_t ) * cspsIndex, 1, cspsDEVlonf );
                fwrite( cspsDEValt, sizeof( csps_Real_t ) * cspsIndex, 1, cspsDEValtf );
                fwrite( cspsDEVqbf, sizeof( csps_Time_t ) * cspsIndex, 1, cspsDEVqbff );
                fwrite( cspsDEVsyn, sizeof( csps_Time_t ) * cspsIndex, 1, cspsDEVsynf );

            }

        }

        /* Close file stream */
        fclose( cspsDEVlogf );
        fclose( cspsDEVlatf );
        fclose( cspsDEVlonf );
        fclose( cspsDEValtf );
        fclose( cspsDEVqbff );
        fclose( cspsDEVsynf );

        /* Unallocate buffer memory */
        free( cspsDEVsyn );
        free( cspsDEVlat );
        free( cspsDEVlon );
        free( cspsDEValt );
        free( cspsDEVqbf );

        /* Return device descriptor */
        return( cspsDevice );

    }

