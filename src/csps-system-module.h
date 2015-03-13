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
    # include "csps-system-token.h"

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

    /*! \brief Extraction modules interface
     * 
     *  This function is the topology parser specific camera extraction module
     *  interface. Its role is to read the module section in the topology file
     *  in order to trigger module execution.
     *
     *  The topology file provided as parameter has to be already openned and
     *  its position has to point token comming just after the 'module' keyword.
     *  The function update the file position to position just after 'end'
     *  keyword at module section end.
     *
     *  \param lpPath   Path to CSPS directory structure
     *  \param lpStack  Pointer to device structures stack
     *  \param lpStream Topology file handle
     */

    lp_Void_t lp_system_module_cam_DSIDE(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        FILE             * const lpStream

    );

    /*! \brief Extraction modules interface
     * 
     *  This function is the topology parser specific GPS extraction module
     *  interface. Its role is to read the module section in the topology file
     *  in order to trigger module execution.
     *
     *  The topology file provided as parameter has to be already openned and
     *  its position has to point token comming just after the 'module' keyword.
     *  The function update the file position to position just after 'end'
     *  keyword at module section end.
     *
     *  \param lpPath   Path to CSPS directory structure
     *  \param lpStack  Pointer to device structures stack
     *  \param lpStream Topology file handle
     */

    lp_Void_t lp_system_module_gps_DSIDE(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        FILE             * const lpStream

    );

    /*! \brief Extraction modules interface
     * 
     *  This function is the topology parser specific IMU extraction module
     *  interface. Its role is to read the module section in the topology file
     *  in order to trigger module execution.
     *
     *  The topology file provided as parameter has to be already openned and
     *  its position has to point token comming just after the 'module' keyword.
     *  The function update the file position to position just after 'end'
     *  keyword at module section end.
     *
     *  \param lpPath   Path to CSPS directory structure
     *  \param lpStack  Pointer to device structures stack
     *  \param lpStream Topology file handle
     */

    lp_Void_t lp_system_module_imu_DSIDE(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        FILE             * const lpStream

    );

    /*! \brief GPS reciever modules interface
     * 
     *  This function is the topology parser specific gps-mod-SGNQF module
     *  interface. Its role is to read the module section in the topology file
     *  in order to trigger module execution.
     *
     *  The topology file provided as parameter has to be already openned and
     *  its position has to point token comming just after the 'module' keyword.
     *  The function update the file position to position just after 'end'
     *  keyword at module section end.
     *
     *  \param lpPath   Path to CSPS directory structure
     *  \param lpStack  Pointer to device structures stack
     *  \param lpStream Topology file handle
     */

    lp_Void_t lp_system_module_gps_SGNQF(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        FILE             * const lpStream

    );

    /*! \brief IMU sensor modules interface
     * 
     *  This function is the topology parser specific imu-mod-SGSFR module
     *  interface. Its role is to read the module section in the topology file
     *  in order to trigger module execution.
     *
     *  The topology file provided as parameter has to be already openned and
     *  its position has to point token comming just after the 'module' keyword.
     *  The function update the file position to position just after 'end'
     *  keyword at module section end.
     *
     *  \param lpPath   Path to CSPS directory structure
     *  \param lpStack  Pointer to device structures stack
     *  \param lpStream Topology file handle
     */

    lp_Void_t lp_system_module_imu_SGSFR(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        FILE             * const lpStream

    );

    /*! \brief IMU sensor modules interface
     * 
     *  This function is the topology parser specific imu-mod-SGNDN module
     *  interface. Its role is to read the module section in the topology file
     *  in order to trigger module execution.
     *
     *  The topology file provided as parameter has to be already openned and
     *  its position has to point token comming just after the 'module' keyword.
     *  The function update the file position to position just after 'end'
     *  keyword at module section end.
     *
     *  \param lpPath   Path to CSPS directory structure
     *  \param lpStack  Pointer to device structures stack
     *  \param lpStream Topology file handle
     */

    lp_Void_t lp_system_module_imu_SGNDN(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        FILE             * const lpStream

    );

    /*! \brief IMU sensor modules interface
     * 
     *  This function is the topology parser specific imu-mod-ISRAD module
     *  interface. Its role is to read the module section in the topology file
     *  in order to trigger module execution.
     *
     *  The topology file provided as parameter has to be already openned and
     *  its position has to point token comming just after the 'module' keyword.
     *  The function update the file position to position just after 'end'
     *  keyword at module section end.
     *
     *  \param lpPath   Path to CSPS directory structure
     *  \param lpStack  Pointer to device structures stack
     *  \param lpStream Topology file handle
     */

    lp_Void_t lp_system_module_imu_ISRAD(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        FILE             * const lpStream

    );

    /*! \brief IMU sensor modules interface
     * 
     *  This function is the topology parser specific imu-mod-IOISA module
     *  interface. Its role is to read the module section in the topology file
     *  in order to trigger module execution.
     *
     *  The topology file provided as parameter has to be already openned and
     *  its position has to point token comming just after the 'module' keyword.
     *  The function update the file position to position just after 'end'
     *  keyword at module section end.
     *
     *  \param lpPath   Path to CSPS directory structure
     *  \param lpStack  Pointer to device structures stack
     *  \param lpStream Topology file handle
     */

    lp_Void_t lp_system_module_imu_IOISA(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        FILE             * const lpStream

    );

    /*! \brief IMU sensor modules interface
     * 
     *  This function is the topology parser specific imu-mod-IOBMA module
     *  interface. Its role is to read the module section in the topology file
     *  in order to trigger module execution.
     *
     *  The topology file provided as parameter has to be already openned and
     *  its position has to point token comming just after the 'module' keyword.
     *  The function update the file position to position just after 'end'
     *  keyword at module section end.
     *
     *  \param lpPath   Path to CSPS directory structure
     *  \param lpStack  Pointer to device structures stack
     *  \param lpStream Topology file handle
     */

    lp_Void_t lp_system_module_imu_IOBMA(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        FILE             * const lpStream

    );

    /*! \brief IMU sensor modules interface
     * 
     *  This function is the topology parser specific imu-mod-IFICR module
     *  interface. Its role is to read the module section in the topology file
     *  in order to trigger module execution.
     *
     *  The topology file provided as parameter has to be already openned and
     *  its position has to point token comming just after the 'module' keyword.
     *  The function update the file position to position just after 'end'
     *  keyword at module section end.
     *
     *  \param lpPath   Path to CSPS directory structure
     *  \param lpStack  Pointer to device structures stack
     *  \param lpStream Topology file handle
     */

    lp_Void_t lp_system_module_imu_IFICR(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        FILE             * const lpStream

    );

    /*! \brief IMU sensor modules interface
     * 
     *  This function is the topology parser specific imu-mod-IFETI module
     *  interface. Its role is to read the module section in the topology file
     *  in order to trigger module execution.
     *
     *  The topology file provided as parameter has to be already openned and
     *  its position has to point token comming just after the 'module' keyword.
     *  The function update the file position to position just after 'end'
     *  keyword at module section end.
     *
     *  \param lpPath   Path to CSPS directory structure
     *  \param lpStack  Pointer to device structures stack
     *  \param lpStream Topology file handle
     */

    lp_Void_t lp_system_module_imu_IFETI(

        lp_Char_t  const * const lpPath,
        lp_Stack_t       * const lpStack,
        FILE             * const lpStream

    );

    /*! \brief IMU sensor modules interface
     * 
     *  This function is the topology parser specific imu-mod-AACEX module
     *  interface. Its role is to read the module section in the topology file
     *  in order to trigger module execution.
     *
     *  The topology file provided as parameter has to be already openned and
     *  its position has to point token comming just after the 'module' keyword.
     *  The function update the file position to position just after 'end'
     *  keyword at module section end.
     *
     *  \param lpPath   Path to CSPS directory structure
     *  \param lpStack  Pointer to device structures stack
     *  \param lpStream Topology file handle
     */

    lp_Void_t lp_system_module_imu_AACEX(

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

