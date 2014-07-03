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

    # include "csps-path.h"

/*
    Source - General path database
 */

    void csps_path(

        const csps_Char_t * cspsBase,
        const csps_Char_t * cspsTag,
        const csps_Char_t * cspsName,
        const csps_Char_t * cspsStep,
        const csps_Char_t * cspsType,
        csps_Char_t * const cspsPath

        ) {

        /* Select type of path */
        if ( strcmp( cspsTag, CSPS_DEVICE_IMU_ADIS16375 ) == 0 ) {

            /* Path for ADIS16375 IMU FPGA log file */
            sprintf( cspsPath, "%s/" CSPS_PATH_FGPA "/log-data.bin", cspsBase );

        /* Select type of path */
        } else if ( strcmp( cspsTag, CSPS_DEVICE_GPS_LS20031 ) == 0 ) {

            /* Path for LS20031 GPS FPGA log file */
            sprintf( cspsPath, "%s/" CSPS_PATH_FGPA "/log-data.bin", cspsBase );

        /* Select type of path */
        } else if ( strcmp( cspsTag, CSPS_DEVICE_CAM_EYESIS4PI ) == 0 ) {

            /* Path for EYESIS4PI GPS FPGA log file */
            sprintf( cspsPath, "%s/" CSPS_PATH_FGPA "/log-data.bin", cspsBase );

        /* Select type of path */
        } else if ( strcmp( cspsTag, "gps" ) == 0 ) {

            /* Path to GPS data stream files */
            sprintf( cspsPath, "%s/" CSPS_PATH_CSPS "/csps-stream-gps-%s-%s-%s.bin", cspsBase, cspsName, cspsStep, cspsType );

        /* Select type of path */
        } else if ( strcmp( cspsTag, "imu" ) == 0 ) {

            /* Path to IMU data stream files */
            sprintf( cspsPath, "%s/" CSPS_PATH_CSPS "/csps-stream-imu-%s-%s-%s.bin", cspsBase, cspsName, cspsStep, cspsType );

        /* Select type of path */
        } else if ( strcmp( cspsTag, "cam" ) == 0 ) {

            /* Path to IMU data stream files */
            sprintf( cspsPath, "%s/" CSPS_PATH_CSPS "/csps-stream-cam-%s-%s-%s.bin", cspsBase, cspsName, cspsStep, cspsType );

        }

    }

