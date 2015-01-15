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

    /*! \file   csps-system-tool.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  CSPS library topology interpreter tool functions
     */

/*
    Header - Include guard
 */

    # ifndef __LP_SYSTEM_TOOL__
    # define __LP_SYSTEM_TOOL__

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

/*
    Header - Preprocessor definitions
 */

/*
    Header - Preprocessor macros
 */

    /* Define maximum number of devices */
    # define LP_SYSTEM_LIMIT        lp_Size_s( 1024 )

    /* Define device type constants */
    # define LP_SYSTEM_TYPE_NULL    lp_Enum_s(    0 )
    # define LP_SYSTEM_TYPE_CAM     lp_Enum_s(    1 )
    # define LP_SYSTEM_TYPE_GPS     lp_Enum_s(    2 )
    # define LP_SYSTEM_TYPE_IMU     lp_Enum_s(    3 )

    /* Define topology keywords - generic */
    # define LP_SYSTEM_DEVICE       "device"
    # define LP_SYSTEM_MODULE       "module"
    # define LP_SYSTEM_END          "end"

    /* Define topology keywords - devices */
    # define LP_SYSTEM_CAM          "cam"
    # define LP_SYSTEM_GPS          "gps"
    # define LP_SYSTEM_IMU          "imu"
    # define LP_SYSTEM_NAME         "model"
    # define LP_SYSTEM_TAG          "tag"

    /* Define topology keywords - modules */
    # define LP_SYSTEM_DEVTAG       "device-tag"

    /* Define topology keywords - parameters */
    # define LP_SYSTEM_BLOCK        "block"
    # define LP_SYSTEM_INPUT        "input"
    # define LP_SYSTEM_IFREQ        "freq-in"
    # define LP_SYSTEM_DFREQ        "freq-out"
    # define LP_SYSTEM_ISRL         "maximum"
    # define LP_SYSTEM_ISRA         "minimum"
    # define LP_SYSTEM_ISRGT        "trigger-gyro"
    # define LP_SYSTEM_ISRAT        "trigger-accel"
    # define LP_SYSTEM_XANG         "x-angle"
    # define LP_SYSTEM_YANG         "y-angle"
    # define LP_SYSTEM_ZANG         "z-angle"

/*
    Header - Typedefs
 */

/*
    Header - Structures
 */

    /*! \struct lp_system_stack_struct
     *  \brief Device structures stack
     *
     *  This structure is used to store the device structure that are engaged in
     *  the CSPS process by the provided CSPS topology.
     *
     *  \var lp_system_stack_struct:stSize 
     *  Number of device structure stored in the stack
     *  \var lp_system_stack_struct::stType 
     *  Array that stores the type of device structures stored in the stack
     *  \var lp_system_stack_struct::stDevice
     *  Array that stores pointers to device structures stored in the stack 
     */ 

    typedef struct lp_system_stack_struct {

        /* Stack state */
        lp_Size_t   stSize;

        /* Device type stack */
        lp_Enum_t   stType  [LP_SYSTEM_LIMIT];

        /* Device descriptor stack */
        lp_Void_t * stDevice[LP_SYSTEM_LIMIT];

    } lp_Stack_t;

/*
    Header - Function prototypes
 */

    /*! \brief Device structures stack management
     *
     *  This function is called to initialize stack structure. It has to be
     *  called befor any use of the stack.
     *
     *  \param lpStack  Pointer to device structures stack structure
     */

    lp_Void_t lp_system_stack_create(

        lp_Stack_t * const lpStack

    );

    /*! \brief Device structures stack management
     * 
     *  This function deletes the information about device structure and empty
     *  the stack structure. This function has to be called after stack usage
     *  in order to avoid memory leak.
     *
     *  \param lpStack  Pointer to device structures stack structure
     */

    lp_Void_t lp_system_stack_delete(

        lp_Stack_t * const lpStack

    );

    /*! \brief Device structures stack management
     * 
     *  This function is used to push a device structure in the stack. The stack
     *  size is updated and the pushed device structure is allocated according
     *  to its type. The stack allocation is then usable.
     *
     *  \param  lpStack Pointer to device structures stack structure
     *  \param  lpType  Type of the device structure to push
     *
     *  \return Returns pointer to the pushed device structrue
     */

    lp_Void_t * lp_system_stack_push(

        lp_Stack_t * const lpStack,
        lp_Enum_t    const lpType

    );

    /*! \brief Device structures stack management
     * 
     *  This function allows to get index in the stack of the device referenced
     *  by its tag. If the provided tag has no match in the stack, a null pointer
     *  is returned. Otherwise, the pointer to the found device structure is
     *  returned.
     *
     *  \param  lpStack Pointer to device structures stack structure
     *  \param  lpType  Type of the device structure to push
     *  \parma  lpTag   Tag of the device to search
     *
     *  \return Returns a pointer to the found device structure

    lp_Void_t * lp_system_stack_bytag(

        lp_Stack_t       * const lpStack,
        lp_Enum_t          const lpType,
        lp_Char_t  const * const lpTag

    );

    /*! \brief String token from file
     *
     *  This function simply reads a string token from specified open file. It 
     *  returns the pointer to read token char buffer. Token is read at current
     *  position in file which is updated after reading. If no token have been
     *  read, LP_FALSE is returned.
     * 
     *  \param  lpFile   File from which token is read
     *  \param  lpToken  Read string token char buffer
     *
     *  \return Returns pointer to string allocation that contains read token
     */

    lp_Char_t * lp_system_token(

        FILE      * const lpFile,
        lp_Char_t * const lpToken

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

