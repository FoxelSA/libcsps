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

    /*! \file   csps-imu-mod-AACEX.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  AACEX - Absolute ACceleration EXtraction
     */

/*
    Header - Include guard
 */

    # ifndef __LP_IMU_AACEX__
    # define __LP_IMU_AACEX__

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
    # define LP_IMU_AACEX_MOD "mod-AACEX"
    # define LP_IMU_AACEX_DES "Absolute ACceleration EXtraction" 

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

    /*! \brief IMU absolute acceleration extraction
     *  
     *  This module extracts absolute acceleration from IMU signal. It takes
     *  time-integrated IMU frame in order to compute absolute acceleration
     *  vector over time. At this point, gravity component is not removed.
     *  
     *  \param lpPath       Path to CSPS directory structure
     *  \param lpIMU        IMU device structure
     *  \param lpIMUmodACC  Acceleration stream initiator module
     *  \param lpIMUmodFRM  Frame stream initiator module
     */

    lp_Void_t lp_imu_mod_AACEX( 

        lp_Char_t const * const lpPath, 
        lp_IMU_t  const         lpIMU, 
        lp_Char_t const * const lpIMUmodACC, 
        lp_Char_t const * const lpIMUmodFRM

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

