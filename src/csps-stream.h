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

    # ifndef __LP_STREAM__
    # define __LP_STREAM__

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
    # include "csps-path.h"

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

    lp_Size_t lp_stream_size(

        const lp_Char_t * const lpPath,
        const lp_Char_t * const lpDev,
        const lp_Char_t * const lpName,
        const lp_Char_t * const lpPS__,
        const lp_Char_t * const lpType

    );

    lp_Void_t * lp_stream_read(

        const lp_Char_t * const lpPath,
        const lp_Char_t * const lpDev,
        const lp_Char_t * const lpName,
        const lp_Char_t * const lpPS__,
        const lp_Char_t * const lpType,
        lp_Size_t lpSize

    );

    lp_Void_t lp_stream_write(

        const lp_Char_t * const lpPath,
        const lp_Char_t * const lpDev,
        const lp_Char_t * const lpName,
        const lp_Char_t * const lpPS__,
        const lp_Char_t * const lpType,
        const lp_Void_t * const lpStream,
        lp_Size_t lpSize

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

