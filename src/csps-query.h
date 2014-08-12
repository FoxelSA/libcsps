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

    # ifndef __LIBCSPS_CSPS_QUERY__
    # define __LIBCSPS_CSPS_QUERY__

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
    # include "csps-math.h"
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

    typedef struct csps_QueryTime_struct {

        /* Timestamp range boundaries */
        csps_Time_t qrInitial;
        csps_Time_t qrFinal;

    } csps_QueryTime;

    typedef struct csps_QueryPosition_struct {

        /* Position descriptors */
        csps_Real_t qrLatitude;
        csps_Real_t qrLongitude;
        csps_Real_t qrAltitude;

    } csps_QueryPosition;

    typedef struct cspsQueryOrientation_struct {

        /* Orientation descriptor */
        csps_Real_t qrfxx;
        csps_Real_t qrfxy;
        csps_Real_t qrfxz;
        csps_Real_t qrfyx;
        csps_Real_t qrfyy;
        csps_Real_t qrfyz;
        csps_Real_t qrfzx;
        csps_Real_t qrfzy;
        csps_Real_t qrfzz;

    } csps_QueryOrientation;

/*
    Header - Function prototypes
 */

    csps_QueryTime csps_query_time(

        const csps_Char_t * const cspsPath,
        const csps_Char_t * const cspsTag,
        const csps_Char_t * const cspsName,
        const csps_Char_t * const cspsPS__

    );

    csps_QueryPosition csps_query_position_by_timestamp(

        const csps_Char_t * const cspsPath,
        const csps_Char_t * const cspsTag,
        const csps_Char_t * const cspsName,
        const csps_Char_t * const cspsPS__,
        csps_Time_t cspsTimestamp

    );

    csps_QueryOrientation csps_query_orientation_by_timestamp(

        const csps_Char_t * const cspsPath,
        const csps_Char_t * const cspsTag,
        const csps_Char_t * const cspsName,
        const csps_Char_t * const cspsPS__,
        csps_Time_t cspsTimestamp

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

