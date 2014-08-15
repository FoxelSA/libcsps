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


/*
    Header - Include guard
 */

    # ifndef __LP_GPS_MODRS__
    # define __LP_GPS_MODRS__

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
    # include "csps-qbf.h"
    # include "csps-stream.h"
    # include "csps-timestamp.h"

/*
    Header - Preprocessor definitions
 */

/*
    Header - Preprocessor macros
 */

    /* CSPS module identification */
    # define LP_GPS_MODRS_DEV "gps"
    # define LP_GPS_MODRS_MOD "modrs"

    /* Define derivative computation range */
    # define LP_GPS_MODRS_BOUND lp_Size_s( 8 )

/*
    Header - Typedefs
 */

/*
    Header - Structures
 */

/*
    Header - Function prototypes
 */

    /*! \brief GPS signal loss component removal module
     *  
     *  This module removes GPS measure on the base of the signal quality. The
     *  output stream contains only measure that have a satisfying quality.
     *  
     *  \param lpPath Path to the CSPS directory structure
     *  \param lpDevice GPS device descriptor
     *  \param lpName GPS device name
     *  \param CSPS input stream
     */

    lp_GPS lp_gps_modrs(

        const lp_Char_t * const lpPath,
        lp_GPS lpDevice,
        const lp_Char_t * const lpName,
        const lp_Char_t * const lpPS__

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

