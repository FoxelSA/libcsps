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

    # include "csps-math.h"

/*
    Source - C(0) spline function
 */

    csps_Real_t csps_math_spline_czero(

        csps_Enum_t cspsFlag,
        csps_Real_t x,
        csps_Real_t x1,
        csps_Real_t x2,
        csps_Real_t y1,
        csps_Real_t y2,
        csps_Real_t d1,
        csps_Real_t d2

    ) {

        /* Cubic spline factors */
        static csps_Real_t cspsCoeffA = csps_Real_s( 0.0 );
        static csps_Real_t cspsCoeffB = csps_Real_s( 0.0 );

        /* Verify spline function flag */
        if ( cspsFlag == CSPS_MATH_SPLINE_RESET ) {

            /* Compute cubic spline factors - 2-0,3-1 Model */
            cspsCoeffA = + ( d1 ) * ( x2 - x1 ) - ( y2 - y1 );
            cspsCoeffB = - ( d2 ) * ( x2 - x1 ) + ( y2 - y1 );

        }

        /* Compute interpolation parameter */
        x = ( x - x1 ) / ( x2 - x1 );

        /* Compute interpolated value */
        return( ( ( csps_Real_s( 1.0 ) - x ) * y1 ) + ( x * y2 ) + ( x * ( csps_Real_s( 1.0 ) - x ) ) * ( cspsCoeffA * ( csps_Real_s( 1.0 ) - x ) + cspsCoeffB * x ) );

    }

/*
    Source - C(1) spline function
 */

    csps_Real_t csps_math_spline(

        csps_Enum_t cspsFlag,
        csps_Real_t x,
        csps_Real_t x0,
        csps_Real_t x1,
        csps_Real_t x2,
        csps_Real_t x3,
        csps_Real_t y0,
        csps_Real_t y1,
        csps_Real_t y2,
        csps_Real_t y3

    ) {

        /* Cubic spline factors */
        static csps_Real_t cspsCoeffA = csps_Real_s( 0.0 );
        static csps_Real_t cspsCoeffB = csps_Real_s( 0.0 );

        /* Verify spline function flag */
        if ( cspsFlag == CSPS_MATH_SPLINE_RESET ) {

            /* Compute cubic spline factors - 2-0,3-1 Model */
            cspsCoeffA = + ( ( y2 - y0 ) / ( x2 - x0 ) ) * ( x2 - x1 ) - ( y2 - y1 );
            cspsCoeffB = - ( ( y3 - y1 ) / ( x3 - x1 ) ) * ( x2 - x1 ) + ( y2 - y1 );

        }

        /* Compute interpolation parameter */
        x = ( x - x1 ) / ( x2 - x1 );

        /* Compute interpolated value */
        return( ( ( csps_Real_s( 1.0 ) - x ) * y1 ) + ( x * y2 ) + ( x * ( csps_Real_s( 1.0 ) - x ) ) * ( cspsCoeffA * ( csps_Real_s( 1.0 ) - x ) + cspsCoeffB * x ) );

    }

