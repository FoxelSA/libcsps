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

    # ifndef __LP_QUERY__
    # define __LP_QUERY__

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
    # include "csps-stream.h"
    # include "csps-timestamp.h"
    # include "inter-all.h"

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

    typedef struct lp_QueryTime_struct {

        /* Timestamp range boundaries */
        lp_Time_t qrInitial;
        lp_Time_t qrFinal;

    } lp_QueryTime;

    typedef struct lp_QueryPosition_struct {

        /* Query status */
        lp_Enum_t qrStatus;

        /* Position descriptors */
        lp_Real_t qrLatitude;
        lp_Real_t qrLongitude;
        lp_Real_t qrAltitude;

    } lp_QueryPosition;

    typedef struct lp_QueryOrientation_struct {

        /* Query status */
        lp_Enum_t qrStatus;

        /* Orientation descriptor */
        lp_Real_t qrfxx;
        lp_Real_t qrfxy;
        lp_Real_t qrfxz;
        lp_Real_t qrfyx;
        lp_Real_t qrfyy;
        lp_Real_t qrfyz;
        lp_Real_t qrfzx;
        lp_Real_t qrfzy;
        lp_Real_t qrfzz;

    } lp_QueryOrientation;

/*
    Header - Function prototypes
 */

    lp_QueryTime lp_query_time(

        const lp_Char_t * const cspsPath,
        const lp_Char_t * const cspsTag,
        const lp_Char_t * const cspsName,
        const lp_Char_t * const cspsPS__

    );

    lp_QueryPosition lp_query_position_by_timestamp(

        const lp_Char_t * const cspsPath,
        const lp_Char_t * const cspsTag,
        const lp_Char_t * const cspsName,
        const lp_Char_t * const cspsPS__,
        lp_Time_t cspsTimestamp

    );

    lp_QueryOrientation lp_query_orientation_by_timestamp(

        const lp_Char_t * const cspsPath,
        const lp_Char_t * const cspsTag,
        const lp_Char_t * const cspsName,
        const lp_Char_t * const cspsPS__,
        lp_Time_t cspsTimestamp

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

