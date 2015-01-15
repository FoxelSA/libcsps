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

    /*! \file   csps-imu-mod-ISRAD.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  ISRAD - Inertial Still Range Automatic Detection
     */

/*
    Header - Include guard
 */

    # ifndef __LP_IMU_ISRAD___
    # define __LP_IMU_ISRAD___

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
    # define LP_IMU_ISRAD_MOD   "mod-ISRAD"
    # define LP_IMU_ISRAD_DES   "Inertial Still Range Automatic Detection"

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

    /*! \brief IMU Inertial still range automatic detection
     *  
     *  This function detects the largest intertial still range based on the
     *  accelerations and angular velocities. The threshold values are specified
     *  through the trigger parameters. The minimum of inertial measures that
     *  are able to trigger a still range detection is also provided through
     *  parameters.
     *
     *  Moreover, the first still range definition stored in the output stream
     *  corresponds to the longest detected still range. This longest still
     *  range is then stored twice in the output stream.
     *
     *  The function impose also a maximum of detectable still ranges. This
     *  maximum value is provided as parameter.
     *  
     *  \param lpPath       Path to CSPS directory structure
     *  \param lpIMU        IMU device structure
     *  \param lpIMUmod     Gyroscope and acceleration stream initiator module
     *  \param lpLimit      Maximum number of detectable still range
     *  \param lpAccum      Minimum number of inertial measure able to trigger a
     *                      still range detection
     *  \param lpaTrigger   Trigger threshold for acceleration measures
     *  \param lpgTrigger   Trigger threshold for gyroscopic measures
     */

    lp_Void_t lp_imu_mod_ISRAD( 

        lp_Char_t const * const lpPath, 
        lp_IMU_t  const         lpIMU, 
        lp_Char_t const * const lpIMUmod,
        lp_Size_t const         lpLimit,
        lp_Size_t const         lpAccum,
        lp_Real_t const         lpgTrigger,
        lp_Real_t const         lpaTrigger

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

