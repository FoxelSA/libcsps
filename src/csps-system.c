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

    # include "csps-system.h"

/*
    Source - CSPS main module
 */

    csps_Void_t csps_system( const csps_Char_t * const cspsPath ) {

        /* CSPS devices */
        csps_CAM cspsCAM;
        csps_IMU cspsADIS;
        csps_GPS cspsLS;

        /* CSPS create devices */
        cspsCAM  = csps_device_CAM( CSPS_DEVICE_CAM_EYESIS4PI );
        cspsADIS = csps_device_IMU( CSPS_DEVICE_IMU_ADIS16375 );
        cspsLS   = csps_device_GPS( CSPS_DEVICE_GPS_LS20031   );

        /* CSPS data extractors */
        cspsCAM  = csps_cam_modde( cspsPath, cspsCAM , "eyesis4pi" );
        cspsADIS = csps_imu_modde( cspsPath, cspsADIS, "adis16375" );
        cspsLS   = csps_gps_modde( cspsPath, cspsLS  , "ls20031"   );

        /* CSPS GPS process line */
        cspsLS   = csps_gps_modrs( cspsPath, cspsLS  , "ls20031"  , "modde" );

        /* CSPS IMU process line */
        cspsADIS = csps_imu_modrd( cspsPath, cspsADIS, "adis16375", "modde" );
        cspsADIS = csps_imu_modga( cspsPath, cspsADIS, "adis16375", "modrd" );
        cspsADIS = csps_imu_modfi( cspsPath, cspsADIS, "adis16375", "modrd" );
        cspsADIS = csps_imu_modaa( cspsPath, cspsADIS, "adis16375", "modrd", "modfi" );

    }

