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
    Header - Include guard
 */

    # ifndef __LIBCSPS_CSPS_MATH__
    # define __LIBCSPS_CSPS_MATH__

/*
    Header - C/C++ compatibility
 */

    # ifdef __cplusplus
    extern "C" {
    # endif

/*
    Header - Includes
 */

    # include "csps.h"

/*
    Header - Preprocessor definitions
 */

    /* Spline flags */
    # define CSPS_MATH_SPLINE_RESET csps_Enum_s( 0 )
    # define CSPS_MATH_SPLINE_VALUE csps_Enum_s( 1 )

/*
    Header - Preprocessor macros
 */

/*
    Header - Typedefs
 */

/*
    Header - Structures
 */

/*
    Header - Function prototypes
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

    );

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

    );

/*
    Header - C/C++ compatibility
 */

    # ifdef __cplusplus
    }
    # endif

/*
    Header - Include guard
 */

    # endif


