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

    /*! \file   csps-imu-mod-IFETI.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  IFETI - Inertial Frame Explicit Time Integration
     */

/*
    Header - Include guard
 */

    # ifndef __LP_IMU_IFETI__
    # define __LP_IMU_IFETI__

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
    # define LP_IMU_IFETI_MOD "mod-IFETI"
    # define LP_IMU_IFETI_DES "Inertial Frame Explicit Time Integration"

    /* Define integration boundaries */
    # define LP_IMU_FRAME_BOUND lp_Size_s( 6 )

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

    /*! \brief IMU frame explicit time-integration
     *  
     *  Integrate the IMU frame over time using a simple explicit numerical 
     *  schemes. The numerical scheme has to variants, one peforming integration
     *  according to time flow and the other against time flow. This is made so
     *  because position in time of initial conditions is not known a priori.
     *  
     *  \param lpPath       Path to CSPS directory structure
     *  \param lpIMU        IMU device structure
     *  \param lpIMUmodGYR  Gyroscope stream initiator module
     *  \param lpIMUmodFRM  Frame stream initiator module
     */

    lp_Void_t lp_imu_mod_IFETI( 

        lp_Char_t const * const lpPath, 
        lp_IMU_t  const         lpIMU, 
        lp_Char_t const * const lpIMUmodGYR,
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

