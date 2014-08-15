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

    # ifndef __LP_NMEA__
    # define __LP_NMEA__

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
    # include "csps-device.h"
    # include "csps-qbf.h"

/*
    Header - Preprocessor definitions
 */

    /* Define NMEA sentence model */
    # define LP_NMEA_MODEL_RMC  "QBQBQBQQQQB"
    # define LP_NMEA_MODEL_GGA  "QQBQBQQQQBQBBB"
    # define LP_NMEA_MODEL_GSA  "BQQQQQQQQQQQQQQQQ"
    # define LP_NMEA_MODEL_VTG  "QBQBQBQB"

    /* Define NMEA sentence type */
    # define LP_NMEA_IDENT_RMC  lp_Enum_s(  0 )
    # define LP_NMEA_IDENT_GGA  lp_Enum_s(  1 )
    # define LP_NMEA_IDENT_GSA  lp_Enum_s(  2 )
    # define LP_NMEA_IDENT_VTG  lp_Enum_s(  3 )
    # define LP_NMEA_IDENT_MAX  lp_Enum_s(  4 )
    # define LP_NMEA_IDENT_FAI  lp_Enum_s( 63 )

/*
    Header - Preprocessor macros
 */

    /* Define sexagesimal to floating degree */
    # define LP_NMEA_S2D(x)   ((\
                                lp_trunc((x)/lp_Real_s(100.0))\
                                )+(\
                                ((x)-lp_Real_s(100.0)*lp_trunc((x)/lp_Real_s(100.0)))/lp_Real_s(60.0)\
                                ))

/*
    Header - Typedefs
 */

/*
    Header - Structures
 */

/*
    Header - Function prototypes
 */

    lp_Void_t lp_nmea_gga(

        const lp_Char_t * const lpSentence,
        lp_Real_t * const lpUTC,
        lp_Real_t * const lpLat,
        lp_Real_t * const lpLon,
        lp_Real_t * const lpAlt,
        lp_SQBF_t * const lpQBF

    );

    lp_Enum_t lp_nmea_gga_validate( 

        const lp_Char_t * const lpSentence

    );

    lp_Enum_t lp_nmea_sentence( 

        const lp_Byte_t * const lpRec, 
        const lp_Size_t lpSize, 
        lp_Char_t * const lpSentence

    );

    lp_Byte_t lp_nmea_quartet(

        const lp_Byte_t * const lpRec,
        lp_Size_t lpOffset

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

