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

    /*! \file   csps-system-module.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  CSPS library topology interpreter modules interface
     */

/*
    Header - Include guard
 */

    # ifndef __LP_SYSTEM_MODULE__
    # define __LP_SYSTEM_MODULE__

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
    # include "csps-cam-mod-DSIDE.h"
    # include "csps-gps-mod-DSIDE.h"
    # include "csps-gps-mod-SGNQF.h"
    # include "csps-imu-mod-AACEX.h"
    # include "csps-imu-mod-DSIDE.h"
    # include "csps-imu-mod-SGNDN.h"
    # include "csps-imu-mod-SGSFR.h"
    # include "csps-imu-mod-IFETI.h"
    # include "csps-imu-mod-IFICR.h"
    # include "csps-imu-mod-IOBMA.h"
    # include "csps-imu-mod-IOISA.h"
    # include "csps-imu-mod-ISRAD.h"
    # include "csps-system-tool.h"

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

    lp_Void_t lp_system_module_cam_DSIDE(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        FILE             * const lpStream

    );

    lp_Void_t lp_system_module_gps_DSIDE(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        FILE             * const lpStream

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

