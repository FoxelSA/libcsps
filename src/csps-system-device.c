/*
 * libcsps - Crossed-signal positioning system library
 *
 * Copyright (c) 2013-2015 FOXEL SA - http://foxel.ch
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

    # include "csps-system-device.h"

/*
    Source - Camera devices interface
 */

    lp_Void_t lp_system_device_cam(

        FILE * const lpStream

    ) {

        /* String token variables */
        lp_Char_t lpToken[LP_STR_LEN] = LP_STR_INI;

        /* String buffer variables */
        lp_Char_t lpModel[LP_STR_LEN] = LP_STR_INI;
        lp_Char_t lpTag  [LP_STR_LEN] = LP_STR_INI;

        do {

            /* Read token from stream */
            lp_system_token( lpStream, lpToken );

            /* String token analysis */
            if ( strcmp( lpToken, LP_SYSTEM_KW_TAG ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpTag );

            } else
            if ( strcmp( lpToken, LP_SYSTEM_KW_MODEL ) == 0 ) {

                /* Read parameter token */
                lp_system_token( lpStream, lpModel );

            }

        /* End condition on end-keyword */
        } while ( strcmp( lpToken, LP_SYSTEM_KW_END ) != 0 );

    }

