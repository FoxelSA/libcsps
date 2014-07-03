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

    /* Standard includes */
    # include <stdio.h>
    # include <stdlib.h>
    # include <unistd.h>

    /* CSPS includes*/
    # include "../src/csps-all.h"

/*
    Source - Usage display
 */

    void usage( void ) {

        /* Display usage */
        printf( "Usage : csps-demo -p path_to_structure" );

    }

/*
    Source - Demonstration function
 */

    int main ( int argc, char ** argv ) {

        /* getopt variable */
        int cspsGetOpt = 0;

        /* getopt reader */
        while ( ( cspsGetOpt = getopt( argc, argv, "p:h" ) ) != -1 ) {

            switch ( cspsGetOpt ) {

                /* CSPS demonstration */
                case 'p' : {

                    /* CSPS timestamp range */
                    csps_QueryTime cspsTime;

                    /* CSPS retrieve extremum timestamp */
                    cspsTime = csps_query_time( optarg, "imu", "adis16375", "modde" );

                    /* CSPS display timestamp range */
                    printf( "Timerange of the processed structure (IMU based/Device timezone)\n" );
                    printf( "    From : %" PRIu64 " [raw]\n", cspsTime.qrInitial );
                    printf( "    To   : %" PRIu64 " [raw]\n", cspsTime.qrFinal   );
                    printf( "    From : %" PRIu64 ".%5" PRIu64 " [s]\n", csps_timestamp_sec( cspsTime.qrInitial ), csps_timestamp_usec( cspsTime.qrInitial ) );
                    printf( "    To   : %" PRIu64 ".%5" PRIu64 " [s]\n", csps_timestamp_sec( cspsTime.qrFinal   ), csps_timestamp_usec( cspsTime.qrFinal   ) );

                    /* Return to system */
                    return( EXIT_SUCCESS );

                } break;

                /* Display help */
                case 'h' : {

                    /* Display usage */
                    usage();

                    /* Return to system */
                    return( EXIT_SUCCESS );

                } break;

                /* Display help */
                default : {

                    /* Display usage */
                    usage();

                    /* Return to system */
                    return( EXIT_FAILURE );

                }

            }

        }

    }

