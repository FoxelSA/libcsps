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

    # include "csps-device-gps.h"

/*
    Source - GPS device structure creator
 */

    lp_GPS_t lp_device_GPS( 

        lp_Char_t const * const lpName, 
        lp_Char_t const * const lpTag 

    ) {

        /* GPS device structure */
        lp_GPS_t lpDevice;

        /* Detect type of GPS */
        if ( strcmp( lpName, LP_DEVICE_LS20031 ) == 0 ) {

            /* Assign device model name */
            sprintf( lpDevice.dvName, "%s", LP_DEVICE_LS20031 );

            /* Assign device name */
            sprintf( lpDevice.dvTag, "%s", lpTag );

        }

        /* Return device structure */
        return( lpDevice );

    }

