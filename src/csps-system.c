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

    lp_Void_t lp_system( 

        const lp_Char_t * const lpPath 

    ) {

        /* CSPS devices */
        lp_CAM lpCAM;
        lp_IMU lpADIS;
        lp_GPS lpLS;

        /* CSPS create devices */
        lpCAM  = lp_device_CAM( LP_DEVICE_EYESIS4PI, "eyesis4pi" );
        lpADIS = lp_device_IMU( LP_DEVICE_ADIS16375, "adis16375" );
        lpLS   = lp_device_GPS( LP_DEVICE_LS20031  , "ls20031"   );

        /* CSPS data extractors */
        lpCAM  = lp_cam_mod_DSIDE( lpPath, lpCAM  ); 
        lpADIS = lp_imu_mod_DSIDE( lpPath, lpADIS );
        lpLS   = lp_gps_mod_DSIDE( lpPath, lpLS   );

        /* CSPS GPS process line */
        lpLS   = lp_gps_mod_SGNQF( lpPath, lpLS, "mod-DSIDE" );

        /* CSPS IMU process line */
        lpADIS = lp_imu_mod_SGSFR( lpPath, lpADIS, "mod-DSIDE" );
        lpADIS = lp_imu_mod_SGNDN( lpPath, lpADIS, "mod-SGSFR" );
        lpADIS = lp_imu_mod_ISRAD( lpPath, lpADIS, "mod-SGSFR" );
        lpADIS = lp_imu_mod_IOISA( lpPath, lpADIS, lpLS, "mod-DSIDE", "mod-ISRAD", "mod-SGNQF" );
        lpADIS = lp_imu_mod_IFETI( lpPath, lpADIS, "mod-SGNDN", "mod-IOISA" );
        lpADIS = lp_imu_mod_GYLAE( lpPath, lpADIS, "mod-SGNDN", "mod-IFETI" );

    }

