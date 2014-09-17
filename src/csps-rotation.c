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

    # include "csps-timestamp.h"

/*
    Source - Single angle rotation
 */

    lp_Void_t lp_rotation_xR3( lp_Real_t lpAngle, lp_Real_t * lpVectorX, lp_Real_t * lpVectorY, lp_Real_t * lpVectorZ ) {

        /* Buffer variables */
        lp_Real_t lpBfy = * lpVectorY;
        lp_Real_t lpBfz = * lpVectorZ;

        /* Apply rotation around referential x-axis */
        * lpVectorY = + cos( lpAngle ) * lpBfy - sin( lpAngle ) * lpBfz;
        * lpVectorZ = + sin( lpAngle ) * lpBfy + cos( lpAngle ) * lpBfz;

    }

    lp_Void_t lp_rotation_yR3( lp_Real_t lpAngle, lp_Real_t * lpVectorX, lp_Real_t * lpVectorY, lp_Real_t * lpVectorZ ) {

        /* Buffer variables */
        lp_Real_t lpBfx = * lpVectorX;
        lp_Real_t lpBfz = * lpVectorZ;

        /* Apply rotation around referential y-axis */
        * lpVectorX = + cos( lpAngle ) * lpBfx + sin( lpAngle ) * lpBfz;
        * lpVectorZ = - sin( lpAngle ) * lpBfx + cos( lpAngle ) * lpBfz;

    }

    lp_Void_t lp_rotation_zR3( lp_Real_t lpAngle, lp_Real_t * lpVectorX, lp_Real_t * lpVectorY, lp_Real_t * lpVectorZ ) {

        /* Buffer variables */
        lp_Real_t lpBfx = * lpVectorX;
        lp_Real_t lpBfy = * lpVectorY;

        /* Apply rotation around referential z-axis */
        * lpVectorX = + cos( lpAngle ) * lpBfx - sin( lpAngle ) * lpBfy;
        * lpVectorY = + sin( lpAngle ) * lpBfx + cos( lpAngle ) * lpBfy;

    }

