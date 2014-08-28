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

    /*! \file   csps-cam-mod-DSIDE.h
     *  \author Nils Hamel (n.hamel@foxel.ch)
     *
     *  Camera signal extraction module (DSIDE - Device-Specitic Initial Data
     *  Extraction)
     */

/*
    Header - Include guard
 */

    # ifndef __LP_CAM_DSIDE__
    # define __LP_CAM_DSIDE__

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
    # include "csps-stream.h"
    # include "csps-timestamp.h"

/*
    Header - Preprocessor definitions
 */

    /* CSPS module identification */
    # define LP_CAM_DSIDE_MOD "mod-DSIDE"
    # define LP_CAM_DSIDE_DES "Device-Specitic Initial Data Extraction"

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

    /*! \brief Camera signal extraction switch
     *  
     *  Switch on device-specific extractor. On the base of the
     *  descriptor, the device-specific extractor is called.
     *
     *  \param lpPath Path CSPS structure
     *  \param lpDevice Device descriptor
     *  \return Returns device descriptor
     */

    lp_CAM lp_cam_mod_DSIDE(

        const lp_Char_t * const lpPath,
        lp_CAM                  lpDevice

    );

    /*! \brief Eyesis4PI specific initial data extractor
     *
     *  Eyesis4PI device specific extraction sub-module.
     *
     *  \param lpPath Path CSPS structure
     *  \param lpDevice Device descriptor
     *  \return Returns device descriptor
     */

    lp_CAM lp_cam_DSIDE_EYESIS4PI(

        const lp_Char_t * const lpPath,
        lp_CAM                  lpDevice

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

