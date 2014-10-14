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
    Source - General DSIDE path builder
 */

    lp_Void_t lp_path_dside(

        lp_Char_t const * const lpBase,
        lp_Char_t const * const lpDevice,
        lp_Char_t const * const lpLogs,
        lp_Char_t       * const lpPath

    ) {

        /* Select device */
        if ( strcmp( lpDevice, LP_DEVICE_EYESIS4PI ) == 0 ) {

            /* Select logs */
            if ( strcmp( lpLogs, LP_DEVICE_EYESIS4PI_LOG ) == 0 ) {

                /* Build path */
                sprintf( lpPath, "%s/" LP_PATH_DEVICES "/eyesis4pi/fpga-log.bin", lpBase );

            }

        } else if ( strcmp( lpDevice, LP_DEVICE_ADIS16375 ) == 0 ) {

            /* Select logs */
            if ( strcmp( lpLogs, LP_DEVICE_ADIS16375_LOG ) == 0 ) {

                /* Build path */
                sprintf( lpPath, "%s/" LP_PATH_DEVICES "/eyesis4pi/fpga-log.bin", lpBase );

            }

        } else if ( strcmp( lpDevice, LP_DEVICE_LS20031 ) == 0 ) {

            /* Select logs */
            if ( strcmp( lpLogs, LP_DEVICE_LS20031_LOG ) == 0 ) {

                /* Build path */
                sprintf( lpPath, "%s/" LP_PATH_DEVICES "/eyesis4pi/fpga-log.bin", lpBase );

            }

        }

    }

/*
    Source - General stream path builder
 */

    lp_Void_t lp_path_stream( 

        lp_Char_t const * const lpBase,
        lp_Char_t const * const lpDevice,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule,
        lp_Char_t const * const lpType,
        lp_Char_t       * const lpPath

    ) {

        /* Build path */
        sprintf( lpPath, "%s/" LP_PATH_STREAMS "/csps-stream-%s-%s-%s-%s.bin", lpBase, lpDevice, lpTag, lpModule, lpType );

    }

