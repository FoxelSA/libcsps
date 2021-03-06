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

    /*! \file   csps-system.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  CSPS library topology interpreter
     */

/*
    Header - Include guard
 */

    # ifndef __LP_SYSTEM__
    # define __LP_SYSTEM__

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
    # include "csps-system-device.h"
    # include "csps-system-module.h"
    # include "csps-system-token.h"

/*
    Header - Preprocessor definitions
 */

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

    /*! \brief CSPS topology interpreter
     *
     *  This function is the main library topology parser. Its role is to read
     *  the topology file in order to create device structures stack and to call 
     *  the CSPS module in the desired way.
     *
     *  The provided path has to point a correctly formatted directory structure
     *  according to CSPS standards.
     *
     *  The provided execution level is used to define if a given module engaged
     *  through the topology has to be called. This allows to specify sequences
     *  of topology that are executed at different time within the same topology
     *  file.
     *
     *  \param  lpPath  Path to CSPS directory structure
     *  \param  lpLevel Execution level
     *
     *  \return Returns topology parsing status
     */

    lp_Enum_t lp_system(

        lp_Char_t const * const lpPath,
        lp_Size_t         const lpLevel

    );

    /*! \brief CSPS origin directive parser
     *
     *  This function parses the topology file to retrieve device CSPS-tag and
     *  module CSPS-name that are declared in the origin directive. This parser
     *  allows to retrieve those switches to simplify client softwares stream
     *  access using certified information written in the topology file.
     *
     *  \param  lpPath   Path to CSPS directory structure
     *  \param  lpOrigin Origin directive type
     *  \param  lpDevice Returned device CSPS-tag string
     *  \param  lpModule Returned module CSPS-name string
     *
     *  \return Returns query status : LP_TRUE on success, LP_FALSE otherwise
     */

    lp_Enum_t lp_system_origin( 

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpOrigin,
        lp_Char_t       * const lpDevice,
        lp_Char_t       * const lpModule

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

