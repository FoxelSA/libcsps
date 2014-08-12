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

    # ifndef __LIBCSPS_CSPS_NMEA__
    # define __LIBCSPS_CSPS_NMEA__

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
    # define CSPS_NMEA_MODEL_RMC  "QBQBQBQQQQB"
    # define CSPS_NMEA_MODEL_GGA  "QQBQBQQQQBQBBB"
    # define CSPS_NMEA_MODEL_GSA  "BQQQQQQQQQQQQQQQQ"
    # define CSPS_NMEA_MODEL_VTG  "QBQBQBQB"

    /* Define NMEA sentence type */
    # define CSPS_NMEA_IDENT_RMC  csps_Enum_s(  0 )
    # define CSPS_NMEA_IDENT_GGA  csps_Enum_s(  1 )
    # define CSPS_NMEA_IDENT_GSA  csps_Enum_s(  2 )
    # define CSPS_NMEA_IDENT_VTG  csps_Enum_s(  3 )
    # define CSPS_NMEA_IDENT_MAX  csps_Enum_s(  4 )
    # define CSPS_NMEA_IDENT_FAI  csps_Enum_s( 63 )

/*
    Header - Preprocessor macros
 */

    /* Define sexagesimal to floating degree */
    # define CSPS_NMEA_S2D(x)   ((\
                                csps_trunc((x)/csps_Real_s(100.0))\
                                )+(\
                                ((x)-csps_Real_s(100.0)*csps_trunc((x)/csps_Real_s(100.0)))/csps_Real_s(60.0)\
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

    csps_Void_t csps_nmea_gga(

        const csps_Char_t * const cspsSentence,
        csps_Real_t * const cspsUTC,
        csps_Real_t * const cspsLat,
        csps_Real_t * const cspsLon,
        csps_Real_t * const cspsAlt,
        csps_SQBF_t * const cspsQBF

    );

    csps_Enum_t csps_nmea_gga_validate( 

        const csps_Char_t * const cspsSentence

    );

    csps_Enum_t csps_nmea_sentence( 

        const csps_Byte_t * const cspsRec, 
        const csps_Size_t cspsSize, 
        csps_Char_t * const cspsSentence

    );

    csps_Byte_t csps_nmea_quartet(

        const csps_Byte_t * const cspsRec,
        csps_Size_t cspsOffset

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

