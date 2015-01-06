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

    /*! \file   csps.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  Library common header file
     */

    /*! \mainpage libcsps
     *
     *  \section libcsps
     *  \section _ Crossed signal positioning system
     *
     *  The libcsps library, for crossed signal positioning system library, is 
     *  designed to determine position and orientation of camera devices builded 
     *  with inertial and absolute measurement units such as GPS and IMU. It is
     *  designed to consider the multiple sensor signals provided by the device 
     *  assembly and to cross them in order to obtain the best positions and 
     *  orientations of the camera in time and in three-dimensional space.
     *
     *  \section Documentation
     *
     *  A detailed documentation can be generated through doxygen. A more general
     *  documentation can be consulted at https://github.com/FoxelSA/libcsps/wiki.
     *
     *  \section Copyright
     * 
     *  Copyright (c) 2013-2015 FOXEL SA - http://foxel.ch \n
     *  This program is part of the FOXEL project <http://foxel.ch>.
     *  
     *  Please read the COPYRIGHT.md file for more information.
     *
     *  \section License
     *
     *  This program is licensed under the terms of the GNU Affero General Public
     *  License v3 (GNU AGPL), with two additional terms. The content is licensed
     *  under the terms of the Creative Commons Attribution-ShareAlike 4.0 
     *  International (CC BY-SA) license.
     *
     *  You must read <http://foxel.ch/license> for more information about our 
     *  Licensing terms and our Usage and Attribution guidelines.
     */

/*
    Header - Include guard
 */

    # ifndef __LP__
    # define __LP__

/*
    Header - C/C++ compatibility
 */

    # ifdef __cplusplus
    extern "C" {
    # endif

/*
    Header - Includes
 */

    # include <math.h>
    # include <stdio.h>
    # include <stdlib.h>
    # include <string.h>
    # include <stdint.h>
    # include <inttypes.h>

/*
    Header - Preprocessor definitions
 */

    /* Define default truth values */
    # define LP_FALSE           lp_Enum_s( 0 )
    # define LP_TRUE            lp_Enum_s( 1 )

    /* Define default string length */
    # define LP_STR_LEN         lp_Size_s( 256 )

    /* Define default initializer */
    # define LP_STR_INI         { '\0' }

    /* Define default pointer initializer */
    # define LP_NULL            NULL

    /* Declare mathematical constants */
    # define LP_PI              lp_Real_s( 3.14159265358979323846264338327950 )
    # define LP_PI2             lp_Real_s( 6.28318530717958647692528676655901 )

/*
    Header - Preprocessor macros
 */

    /* Define casting macro */
    # define lp_Size_c( x )     ( ( lp_Size_t ) ( x ) )
    # define lp_Enum_c( x )     ( ( lp_Enum_t ) ( x ) )
    # define lp_Real_c( x )     ( ( lp_Real_t ) ( x ) )
    # define lp_Byte_c( x )     ( ( lp_Byte_t ) ( x ) )
    # define lp_Char_c( x )     ( ( lp_Char_t ) ( x ) )

    /* Define litteral suffix */
    # define lp_Size_s( x )     INT64_C( x )
    # define lp_Enum_s( x )     INT64_C( x )
    # define lp_Real_s( x )     ( x )
    # define lp_Byte_s( x )     UINT8_C( x )
    # define lp_Char_s( x )     ( x )

    /* Define formated output specifiers */
    # define lp_Size_p          PRId64
    # define lp_Enum_p          PRId64
    # define lp_Real_p          "lf"
    # define lp_Byte_p          PRIu8
    # define lp_Char_p          "c"

    /* Define formated input specifiers */
    # define lp_Size_i          SCNu64
    # define lp_Enum_i          SCNu64
    # define lp_Real_i          "lf"
    # define lp_Byte_i          SCNu8
    # define lp_Char_i          "c"

    /* Define floating point operator */
    # define lp_trunc( x )      trunc( x )
    # define lp_floor( x )      floor( x )
    # define lp_ceil( x )       ceil ( x )
    # define lp_fabs( x )       fabs ( x )

    /* Define mathematic operator */
    # define LP_MAX( x, y )     ( ( x > y ) ? x : y )
    # define LP_MIN( x, y )     ( ( x < y ) ? x : y )
    # define LP_RNG( x, y, z )  LP_MAX( LP_MIN( x, z ), y )

    /* Define mathematical function */
    # define LP_ATN(x,y)        ( ( x >= 0 ) ? ( ( y >= 0 ) ? atan( y / x ) : LP_PI2 + atan( y / x ) ) : LP_PI + atan( y / x ) )

/*
    Header - Typedefs
 */

    /* Define general void */
    typedef void    lp_Void_t;

    /* Define general index */
    typedef int64_t lp_Size_t;

    /* Define general enumeration */
    typedef int64_t lp_Enum_t;

    /* Define general floating point */
    typedef double  lp_Real_t;

    /* Define general byte */
    typedef uint8_t lp_Byte_t;

    /* Define general char */
    typedef char    lp_Char_t;

    /* Define general stream */
    typedef FILE *  lp_File_t;

/*
    Header - Structures
 */

/*
    Header - Function prototypes
 */

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

