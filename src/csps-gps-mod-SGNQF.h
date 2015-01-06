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

    /*! \file   csps-gps-mod-SGNQF.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  SGNQF - SiGNal Quality Filtering
     */

/*
    Header - Include guard
 */

    # ifndef __LP_GPS_SGNQF__
    # define __LP_GPS_SGNQF__

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
    # include "csps-path.h"
    # include "csps-qbf.h"
    # include "csps-stream.h"
    # include "csps-timestamp.h"

/*
    Header - Preprocessor definitions
 */

/*
    Header - Preprocessor macros
 */

    /* CSPS module identification */
    # define LP_GPS_SGNQF_MOD "mod-SGNQF"
    # define LP_GPS_SGNQF_DES "SiGNal Quality Filtering"

/*
    Header - Typedefs
 */

/*
    Header - Structures
 */

/*
    Header - Function prototypes
 */

    /*! \brief GPS signal quality filtering
     *  
     *  This module removes GPS measures on the base of the GPS signal quality.
     *  The output stream contains only measures that have a satisfying quality.
     *  
     *  \param lpPath   Path CSPS structure
     *  \param lpGPS    GPS device descriptor
     *  \param lpGPSmod Geographic and signal quality stream initiator module
     */

    lp_Void_t lp_gps_mod_SGNQF( 

        lp_Char_t const * const lpPath, 
        lp_GPS_t  const         lpGPS, 
        lp_Char_t const * const lpGPSmod

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

