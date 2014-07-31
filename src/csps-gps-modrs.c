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

    # include "csps-gps-modrs.h"

/*
    Source - GPS signal loss compensator
 */

    csps_GPS csps_gps_modrs(

        const csps_Char_t * const cspsPath,
        csps_GPS cspsDevice,
        const csps_Char_t * const cspsName,
        const csps_Char_t * const cspsPS__

    ) {

        /* Integration variables */
        csps_Size_t cspsParse = csps_Size_s( 0 );
        csps_Size_t cspsIndex = csps_Size_s( 0 );

        /* Files size */
        csps_Size_t cspsSize = csps_Size_s( 0 );

        /* Signal loss range */
        csps_Size_t cspsLoss = csps_Size_s( 0 );

        /* Derivation variables */
        csps_Size_t cspsDR1cnt = csps_Size_s(   0 );
        csps_Size_t cspsDR2cnt = csps_Size_s(   0 );
        csps_Real_t cspsDR1lat = csps_Real_s( 0.0 );
        csps_Real_t cspsDR2lat = csps_Real_s( 0.0 );
        csps_Real_t cspsDR1lon = csps_Real_s( 0.0 );
        csps_Real_t cspsDR2lon = csps_Real_s( 0.0 );
        csps_Real_t cspsDR1alt = csps_Real_s( 0.0 );
        csps_Real_t cspsDR2alt = csps_Real_s( 0.0 );

        /* Data buffers */
        csps_Real_t * cspsDEVlat = NULL;
        csps_Real_t * cspsDEVlon = NULL;
        csps_Real_t * cspsDEValt = NULL;
        csps_Time_t * cspsDEVsyn = NULL;
        csps_Time_t * cspsDEVqbf = NULL;

        /* Obtain stream size */
        cspsSize = csps_stream_size( cspsPath, CSPS_GPS_MODRS_DEV, cspsName, cspsPS__, "syn" ) / sizeof( csps_Time_t );

        /* Read streams data */
        cspsDEVlat = csps_stream_read( cspsPath, CSPS_GPS_MODRS_DEV, cspsName, cspsPS__, "lat", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVlon = csps_stream_read( cspsPath, CSPS_GPS_MODRS_DEV, cspsName, cspsPS__, "lon", sizeof( csps_Real_t ) * cspsSize );
        cspsDEValt = csps_stream_read( cspsPath, CSPS_GPS_MODRS_DEV, cspsName, cspsPS__, "alt", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVsyn = csps_stream_read( cspsPath, CSPS_GPS_MODRS_DEV, cspsName, cspsPS__, "syn", sizeof( csps_Time_t ) * cspsSize );
        cspsDEVqbf = csps_stream_read( cspsPath, CSPS_GPS_MODRS_DEV, cspsName, cspsPS__, "qbf", sizeof( csps_Time_t ) * cspsSize );

        /* Frame integration procedure */
        for ( cspsParse = CSPS_GPS_MODRS_BOUND ; cspsParse < cspsSize - CSPS_GPS_MODRS_BOUND ; cspsParse ++ ) {

            /* Save index value */
            cspsLoss = cspsParse;

            /* Search signal loss range */
            while ( csps_qbf_threshold( cspsDEVqbf[cspsParse] ) != CSPS_FALSE ) cspsParse++;

            /* Check boundaries */
            if ( cspsLoss < ( cspsSize - CSPS_GPS_MODRS_BOUND ) ) {

                /* Verify if loss range is present */
                if ( ( cspsLoss -- ) != cspsParse ) {

                    /* Reset derivative variables */
                    cspsDR1cnt = csps_Size_s(   0 );
                    cspsDR2cnt = csps_Size_s(   0 );
                    cspsDR1lat = csps_Real_s( 0.0 );
                    cspsDR2lat = csps_Real_s( 0.0 );
                    cspsDR1lon = csps_Real_s( 0.0 );
                    cspsDR2lon = csps_Real_s( 0.0 );
                    cspsDR1alt = csps_Real_s( 0.0 );
                    cspsDR2alt = csps_Real_s( 0.0 );

                    /* Computation of the derivatives */
                    for ( cspsIndex = csps_Size_s( 1 ) ; cspsIndex <= CSPS_GPS_MODRS_BOUND - csps_Size_s( 1 ) ; cspsIndex ++ ) {

                        /* Verify signal quality */
                        if ( ( csps_qbf_threshold( cspsDEVqbf[cspsLoss - cspsIndex] ) == CSPS_FALSE ) || ( cspsIndex == 1 ) ) {

                            /* Compute left bound derivative */
                            cspsDR1lat += ( cspsDEVlat[cspsLoss] - cspsDEVlat[cspsLoss - cspsIndex] ) /
                                          ( csps_timestamp_float( csps_timestamp_diff( cspsDEVsyn[cspsLoss], cspsDEVsyn[cspsLoss - cspsIndex] ) ) );
                            cspsDR1lon += ( cspsDEVlon[cspsLoss] - cspsDEVlon[cspsLoss - cspsIndex] ) /
                                          ( csps_timestamp_float( csps_timestamp_diff( cspsDEVsyn[cspsLoss], cspsDEVsyn[cspsLoss - cspsIndex] ) ) );
                            cspsDR1alt += ( cspsDEValt[cspsLoss] - cspsDEValt[cspsLoss - cspsIndex] ) /
                                          ( csps_timestamp_float( csps_timestamp_diff( cspsDEVsyn[cspsLoss], cspsDEVsyn[cspsLoss - cspsIndex] ) ) );

                            /* Update derivative count */
                            cspsDR1cnt += csps_Size_s( 1 );

                        }

                        /* Verify signal quality */
                        if ( ( csps_qbf_threshold( cspsDEVqbf[cspsParse + cspsIndex] ) == CSPS_FALSE ) || ( cspsIndex == 1 ) ) {

                            /* Compute right bound derivative */
                            cspsDR2lat += ( cspsDEVlat[cspsParse + cspsIndex] - cspsDEVlat[cspsParse] ) /
                                          ( csps_timestamp_float( csps_timestamp_diff( cspsDEVsyn[cspsParse + cspsIndex], cspsDEVsyn[cspsParse] ) ) );
                            cspsDR2lon += ( cspsDEVlon[cspsParse + cspsIndex] - cspsDEVlon[cspsParse] ) /
                                          ( csps_timestamp_float( csps_timestamp_diff( cspsDEVsyn[cspsParse + cspsIndex], cspsDEVsyn[cspsParse] ) ) );
                            cspsDR2alt += ( cspsDEValt[cspsParse + cspsIndex] - cspsDEValt[cspsParse] ) /
                                          ( csps_timestamp_float( csps_timestamp_diff( cspsDEVsyn[cspsParse + cspsIndex], cspsDEVsyn[cspsParse] ) ) );

                            /* Update derivative count */
                            cspsDR2cnt += csps_Size_s( 1 );

                        }

                    }

                    /* Compute derivative mean */
                    cspsDR1lat /= ( csps_Real_t ) cspsDR1cnt;
                    cspsDR2lat /= ( csps_Real_t ) cspsDR2cnt;
                    cspsDR1lon /= ( csps_Real_t ) cspsDR1cnt;
                    cspsDR2lon /= ( csps_Real_t ) cspsDR2cnt;
                    cspsDR1alt /= ( csps_Real_t ) cspsDR1cnt;
                    cspsDR2alt /= ( csps_Real_t ) cspsDR2cnt;

                    /* Signal rebuilding loop */
                    for ( cspsIndex = cspsLoss ; cspsIndex < cspsParse ; cspsIndex ++ ) {

                        /* Signal rebuilding by spline */
                        cspsDEVlat[cspsIndex] = csps_math_spline_czero( CSPS_MATH_SPLINE_RESET,

                            csps_timestamp_float( csps_timestamp_diff( cspsDEVsyn[cspsIndex], cspsDEVsyn[cspsLoss] ) ),
                            csps_timestamp_float( csps_timestamp_diff( cspsDEVsyn[cspsLoss ], cspsDEVsyn[cspsLoss] ) ),
                            csps_timestamp_float( csps_timestamp_diff( cspsDEVsyn[cspsParse], cspsDEVsyn[cspsLoss] ) ),
                            cspsDEVlat[cspsLoss ],
                            cspsDEVlat[cspsParse],
                            cspsDR1lat,
                            cspsDR2lat

                        );

                        /* Signal rebuilding by spline */
                        cspsDEVlon[cspsIndex] = csps_math_spline_czero( CSPS_MATH_SPLINE_RESET,

                            csps_timestamp_float( csps_timestamp_diff( cspsDEVsyn[cspsIndex], cspsDEVsyn[cspsLoss] ) ),
                            csps_timestamp_float( csps_timestamp_diff( cspsDEVsyn[cspsLoss ], cspsDEVsyn[cspsLoss] ) ),
                            csps_timestamp_float( csps_timestamp_diff( cspsDEVsyn[cspsParse], cspsDEVsyn[cspsLoss] ) ),
                            cspsDEVlon[cspsLoss ],
                            cspsDEVlon[cspsParse],
                            cspsDR1lon,
                            cspsDR2lon

                        );

                        /* Signal rebuilding by spline */
                        cspsDEValt[cspsIndex] = csps_math_spline_czero( CSPS_MATH_SPLINE_RESET,

                            csps_timestamp_float( csps_timestamp_diff( cspsDEVsyn[cspsIndex], cspsDEVsyn[cspsLoss] ) ),
                            csps_timestamp_float( csps_timestamp_diff( cspsDEVsyn[cspsLoss ], cspsDEVsyn[cspsLoss] ) ),
                            csps_timestamp_float( csps_timestamp_diff( cspsDEVsyn[cspsParse], cspsDEVsyn[cspsLoss] ) ),
                            cspsDEValt[cspsLoss ],
                            cspsDEValt[cspsParse],
                            cspsDR1alt,
                            cspsDR2alt

                        );

                    }

                }

            }

        }

        /* Write stream data */
        csps_stream_write( cspsPath, CSPS_GPS_MODRS_DEV, cspsName, CSPS_GPS_MODRS_MOD, "lat", cspsDEVlat, sizeof( csps_Real_t ) * cspsSize );
        csps_stream_write( cspsPath, CSPS_GPS_MODRS_DEV, cspsName, CSPS_GPS_MODRS_MOD, "lon", cspsDEVlon, sizeof( csps_Real_t ) * cspsSize );
        csps_stream_write( cspsPath, CSPS_GPS_MODRS_DEV, cspsName, CSPS_GPS_MODRS_MOD, "alt", cspsDEValt, sizeof( csps_Real_t ) * cspsSize );
        csps_stream_write( cspsPath, CSPS_GPS_MODRS_DEV, cspsName, CSPS_GPS_MODRS_MOD, "syn", cspsDEVsyn, sizeof( csps_Time_t ) * cspsSize );
        csps_stream_write( cspsPath, CSPS_GPS_MODRS_DEV, cspsName, CSPS_GPS_MODRS_MOD, "qbf", cspsDEVqbf, sizeof( csps_Time_t ) * cspsSize );

        /* Unallocate buffer memory */
        free( cspsDEVlat );
        free( cspsDEVlon );
        free( cspsDEValt );
        free( cspsDEVsyn );
        free( cspsDEVqbf );

        /* Return device descriptor */
        return( cspsDevice );

    }

