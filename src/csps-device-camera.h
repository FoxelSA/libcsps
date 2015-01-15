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

    /*! \file   csps-device-camera.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  CSPS camera device management
     */

/*
    Header - Include guard
 */

    # ifndef __LP_DEVICE_CAMERA__
    # define __LP_DEVICE_CAMERA__

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

    /* Define camera device */
    # define LP_DEVICE_EYESIS4PI            "EYESIS4PI"
    # define LP_DEVICE_EYESIS4PI_LOG        "E4P-LOG-FPGA"
    # define LP_DEVICE_NC353L369IMUGPS      "NC353L-369-IMU-GPS"

    /* Define Eyesis4pi specific constants */
    # define LP_DEVICE_EYESIS4PI_RECLEN     lp_Size_s( 64 )
    # define LP_DEVICE_EYESIS4PI_IMUEVT     lp_Enum_s(  0 )
    # define LP_DEVICE_EYESIS4PI_GPSEVT     lp_Enum_s(  1 )
    # define LP_DEVICE_EYESIS4PI_MASEVT     lp_Enum_s(  2 )

/*
    Header - Preprocessor macros
 */

/*
    Header - Typedefs
 */

/*
    Header - Structures
 */

    /*! \struct lp_Camera_struct
     *  \brief Camera device structure
     *
     *  The structure stores the description of a camera device engaged in the
     *  CSPS processing.
     *
     *  \var lp_Camera_struct::dvName 
     *  Stores the device model name
     *  \var lp_Camera_struct::dvTag 
     *  Stores the device tag name
     */ 

    typedef struct lp_Camera_struct {

        /* Device model name */
        lp_Char_t dvName[LP_STR_LEN];

        /* Device name */
        lp_Char_t dvTag[LP_STR_LEN];

    } lp_Camera_t;

/*
    Header - Function prototypes
 */

    /*! \brief Camera device structure creator
     * 
     *  This function creates camera device structure. It consider device model
     *  to assign its specific configuration.
     *
     * \param   lpName  Camera device model name
     * \param   lpTag   Camera device tag name
     *
     * \returns Returns created camera device structure
     */

    lp_Camera_t lp_device_camera( 

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

