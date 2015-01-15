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

    /*! \file   csps-imu-mod-IOBMA.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  IOBMA - Initial Orientation Body Momentum Alignment
     */

/*
    Header - Include guard
 */

    # ifndef __LP_IMU_IOBMA__
    # define __LP_IMU_IOBMA__

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
    # define LP_IMU_IOBMA_MOD "mod-IOBMA"
    # define LP_IMU_IOBMA_DES "Initial Orientation Body Momentum Alignment"

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

    /*! \brief IMU earth alignmemt through device momentum
     *
     *  This function computes initial conditions on inertial frame based on the
     *  assumption that z axis of the IMU is aligned against the gravity vector
     *  and that the x axis of the IMU sensor follows the direction of motion.
     *  The GPS measures are used to align the x axis of the IMU sensor to the
     *  direction of travel.
     *    
     *  \param lpPath   Path to CSPS directory structure
     *  \param lpIMU    IMU device structure
     *  \param lpGPS    GPS device structure
     *  \param lpGPSmod Geographic positions streams initiator module
     */

    lp_Void_t lp_imu_mod_IOBMA(

        lp_Char_t const * const lpPath, 
        lp_IMU_t  const         lpIMU,
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

