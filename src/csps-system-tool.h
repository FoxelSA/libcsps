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

/*
    Header - Typedefs
 */

/*
    Header - Structures
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

    lp_Void_t lp_system_stack_create(

        lp_Stack_t * const lpStack

    );

    lp_Void_t lp_system_stack_delete(

        lp_Stack_t * const lpStack

    );

    lp_Void_t * lp_system_stack_push(

        lp_Stack_t * const lpStack,
        lp_Enum_t    const lpType

    );

    lp_Void_t * lp_system_stack_bytag(

        lp_Stack_t       * const lpStack,
        lp_Enum_t          const lpType,
        lp_Char_t  const * const lpTag

    );

    /*! \brief File string token reader
     *
     *  This function simply reads a string token from specified file. It 
     *  returns the pointer to read token char buffer.
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

