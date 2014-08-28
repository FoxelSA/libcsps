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

    /*! \file   csps-imu-mod-IOISA.h
     *  \author Nils Hamel (n.hamel@foxel.ch)
     *
     *  IMU earth self-alignment module (IOISA - Initial Orientation Inertial Self-Alignment)
     */

/*
    Header - Include guard
 */

    # ifndef __LP_IMU_IOISA__
    # define __LP_IMU_IOISA__

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
    # define LP_IMU_IOISA_MOD "mod-IOISA"
    # define LP_IMU_IOISA_DES "Initial Orientation Inertial Self-Alignment"

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

    /*! \brief IMU earth self-alignment
     *  
     *  This function performs IMU earth self-alignment. The process
     *  consider measures performed during inertial still ranges.
     *  
     *  \param lpPath Path to CSPS structure
     *  \param lpIMU IMU device descriptor
     *  \param lpGPS GPS device descriptor
     *  \param lpIMUmod IMU module stream name
     *  \param lpGPSmod GPS module stream name
     *  \return Returns IMU device descriptor
     */

    lp_IMU lp_imu_mod_IOISA(

        const lp_Char_t * const lpPath, 
        lp_IMU                  lpIMU,
        lp_GPS                  lpGPS,
        const lp_Char_t * const lpIMUmod,
        const lp_Char_t * const lpIMUmod_tag,
        const lp_Char_t * const lpGPSmod 

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

