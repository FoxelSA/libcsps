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

    /*! \file   csps-path.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  CSPS structure path management
     */

/*
    Header - Include guard
 */

    # ifndef __LP_PATH__
    # define __LP_PATH__

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

/*
    Header - Preprocessor definitions
 */

    /* Define csps device directory */
    # define LP_PATH_DEVICES  "devices"

    /* Define csps stream directory */
    # define LP_PATH_STREAMS  "streams"

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

    /*! \brief CSPS devices path builder
     *  
     *  Build standard path for DSIDE module logs and returns it in
     *  char array.
     *  
     *  \param lpBase Path CSPS structure
     *  \param lpDevice Device name
     *  \param lpLogs Logs to consider
     *  \param lpPath Pointer to string that recieve path
     */

    lp_Void_t lp_path_dside(

        const lp_Char_t * const lpBase,
        const lp_Char_t * const lpDevice,
        const lp_Char_t * const lpLogs,
        lp_Char_t * const       lpPath

    );

    /*! \brief CSPS streams path builder
     *  
     *  Build standard path for module streams components and returns it
     *  in char array.
     *  
     *  \param lpBase Path CSPS structure
     *  \param lpDevice Device type
     *  \param lpTag Device specific name
     *  \param lpModule Modulde name
     *  \param lpType Component data type
     *  \param lpPath Pointer to string that recieve path
     */

    lp_Void_t lp_path_stream( 

        const lp_Char_t * const lpBase,
        const lp_Char_t * const lpDevice,
        const lp_Char_t * const lpTag,
        const lp_Char_t * const lpModule,
        const lp_Char_t * const lpType,
        lp_Char_t * const       lpPath

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

