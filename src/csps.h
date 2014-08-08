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

    # ifndef __LIBCSPS_CSPS__
    # define __LIBCSPS_CSPS__

/*
    Header - C/C++ compatibility
 */

    # ifdef __cplusplus
    extern "C" {
    # endif

/*
    Header - Includes
 */

    # include <stdio.h>
    # include <stdlib.h>
    # include <math.h>
    # include <string.h>
    # include <stdint.h>
    # include <inttypes.h>

/*
    Header - Preprocessor definitions
 */

    /* Define debuging marker */
    //# define CSPS_DEBUG(s) { fprintf( stdout, "DEVPOINT(%d,%s,%s)\n", __LINE__, __FILE__, s ); }

    /* Define default truth values */
    # define CSPS_FALSE             csps_Enum_s( 0 )
    # define CSPS_TRUE              csps_Enum_s( 1 )

    /* Define default string length */
    # define CSPS_STR_LEN           csps_Size_s( 256 )

    /* Define default initializer */
    # define CSPS_STR_INI           ""

    /* Declare mathematical constants */
    # define CSPS_PI                csps_Real_s( 3.14159265358979323846264338327 )

/*
    Header - Preprocessor macros
 */

/*
    Header - Typedefs
 */

    /* Define general void */
    typedef void    csps_Void_t;

    /* Define general index */
    typedef int64_t csps_Size_t;

    /* Define general enumeration */
    typedef int64_t csps_Enum_t;

    /* Define general floating point */
    typedef double  csps_Real_t;

    /* Define general byte */
    typedef uint8_t csps_Byte_t;

    /* Define general char */
    typedef char    csps_Char_t;

    /* Define general stream */
    typedef FILE *  csps_File_t;

    /* Define literal suffix */
    # define csps_Size_s( x )   INT64_C( x )
    # define csps_Enum_s( x )   INT64_C( x )
    # define csps_Real_s( x )   ( x )
    # define csps_Byte_s( x )   UINT8_C( x )
    # define csps_Char_s( x )   ( x )

    /* Define formated output specifiers */
    # define csps_Size_p        PRId64
    # define csps_Enum_p        PRId64
    # define csps_Real_p        "lf"
    # define csps_Byte_p        PRIu8
    # define csps_Char_p        "c"

    /* Define formated input specifiers */
    # define csps_Size_i        SCNu64
    # define csps_Enum_i        SCNu64
    # define csps_Real_i        "lf"
    # define csps_Byte_i        SCNu8
    # define csps_Char_i        "c"

    /* Define floating point operator */
    # define csps_trunc( x )    trunc( x )

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

