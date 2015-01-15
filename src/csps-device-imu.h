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

    /*! \file   csps-device-imu.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  CSPS GPS device management
     */

/*
    Header - Include guard
 */

    # ifndef __LP_DEVICE_IMU__
    # define __LP_DEVICE_IMU__

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

/*
    Header - Preprocessor definitions
 */

    /* Define IMU device */
    # define LP_DEVICE_ADIS16375        "ADIS16375"
    # define LP_DEVICE_ADIS16375_LOG    "LOG-FPGA"

/*
    Header - Preprocessor macros
 */

/*
    Header - Typedefs
 */

/*
    Header - Structures
 */

    /*! \struct lp_IMU_struct
     *  \brief IMU device structure
     *
     *  The structure stores the description of an IMU device engaged in the
     *  CSPS.
     *
     *  \var lp_IMU_struct::dvName 
     *  Stores the device model name
     *  \var lp_IMU_struct::dvTag 
     *  Stores the device tag name
     *  \var lp_IMU_struct::dvGYRx 
     *  Gyroscope factory scale factor for x component
     *  \var lp_IMU_struct::dvGYRy
     *  Gyroscope factory scale factor for y component
     *  \var lp_IMU_struct::dvGYRz 
     *  Gyroscope factory scale factor for z component
     *  \var lp_IMU_struct::dvACCx 
     *  Accelerometer factory scale factor for x component
     *  \var lp_IMU_struct::dvACCy
     *  Accelerometer factory scale factor for y component
     *  \var lp_IMU_struct::dvACCz
     *  Accelerometer factory scale factor for z component
     */ 

    typedef struct lp_IMU_struct {

        /* Device model name */
        lp_Char_t dvName[LP_STR_LEN];

        /* Device name */
        lp_Char_t dvTag[LP_STR_LEN];

        /* Gyroscope factory factors */
        lp_Real_t dvGYRx;
        lp_Real_t dvGYRy;
        lp_Real_t dvGYRz;

        /* Accelerometre factory factors */
        lp_Real_t dvACCx;
        lp_Real_t dvACCy;
        lp_Real_t dvACCz;

    } lp_IMU_t;

/*
    Header - Function prototypes
 */

    /*! \brief IMU device structure creator
     * 
     *  This function creates IMU device structure. It consider device model to
     *  assign its specific configuration.
     *
     * \param   lpName  IMU device model name
     * \param   lpTag   IMU device tag name
     *
     * \returns Returns created IMU device structure
     */

    lp_IMU_t lp_device_IMU( 

        lp_Char_t const * const lpName, 
        lp_Char_t const * const lpTag

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

