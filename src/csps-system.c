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

    lp_Void_t lp_system( const lp_Char_t * const lpPath ) {

        /* CSPS devices */
        lp_CAM lpCAM;
        lp_IMU lpADIS;
        lp_GPS lpLS;

        /* CSPS create devices */
        lpCAM  = lp_device_CAM( LP_DEVICE_CAM_EYESIS4PI, "cam-a" );
        lpADIS = lp_device_IMU( LP_DEVICE_IMU_ADIS16375, "imu-a" );
        lpLS   = lp_device_GPS( LP_DEVICE_GPS_LS20031  , "gps-a" );

        /* CSPS data extractors */
        lpCAM  = lp_cam_modde( lpPath, lpCAM  );
        lpADIS = lp_imu_modde( lpPath, lpADIS );
        lpLS   = lp_gps_modde( lpPath, lpLS   );

        /* CSPS GPS process line */
        lpLS   = lp_gps_modrs( lpPath, lpLS, "modde" );

        /* CSPS IMU process line */
        lpADIS = lp_imu_modrd( lpPath, lpADIS, "modde" );
        lpADIS = lp_imu_moddn( lpPath, lpADIS, "modrd" );
        lpADIS = lp_imu_modsa( lpPath, lpADIS, "moddn" );
        lpADIS = lp_imu_modfi( lpPath, lpADIS, "moddn" );
        lpADIS = lp_imu_modaa( lpPath, lpADIS, "moddn", "modfi" );

    }

