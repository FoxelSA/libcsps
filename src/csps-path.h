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

    /*! \brief General topology path
     *
     *  Builds standard path for topology file in CSPS directory structure and
     *  returns it in provided string.
     *
     *  \param  lpRoot Path to CSPS directory structure
     *  \param  lpPath Pointer to built path string
     *
     *  \return Returns pointer to built path
     */

    lp_Char_t * lp_path_topology( 

        lp_Char_t const * const lpRoot, 
        lp_Char_t       * const lpPath

    );

    /*! \brief CSPS devices path
     *  
     *  Builds standard path for device incomming logs and returns it in the
     *  provided string. The path building is based on camera model and the
     *  desired log.
     *  
     *  \param  lpBase   Path to CSPS directory structure
     *  \param  lpDevice Device CSPS-tag
     *  \param  lpLogs   Logs to consider
     *  \param  lpPath   Pointer to string that recieve path
     *
     *  \return Returns pointer to built path
     */

    lp_Char_t * lp_path_dside(

        lp_Char_t const * const lpRoot,
        lp_Char_t const * const lpDevice,
        lp_Char_t const * const lpLogs,
        lp_Char_t       * const lpPath

    );

    /*! \brief CSPS streams path
     *  
     *  Builds standard path for stream component and returns it in the provided
     *  string.
     *  
     *  \param  lpBase      Path to CSPS directory structure
     *  \param  lpTag       Device CSPS-tag
     *  \param  lpModule    Modulde CSPS-name
     *  \param  lpComponent Stream component tag
     *  \param  lpPath      Pointer to string that recieve path
     *
     *  \return Returns pointer to built path
     */

    lp_Char_t * lp_path_stream( 

        lp_Char_t const * const lpRoot,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule,
        lp_Char_t const * const lpComponent,
        lp_Char_t       * const lpPath

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

