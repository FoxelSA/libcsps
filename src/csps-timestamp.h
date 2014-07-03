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

    # ifndef __LIBCSPS_CSPS_TIMESTAMP__
    # define __LIBCSPS_CSPS_TIMESTAMP__

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

    /* Define timezone designation */
    # define CSPS_TIMESTAMP_ZONE_WET    "WET"
    # define CSPS_TIMESTAMP_ZONE_WEST   "WEST"
    # define CSPS_TIMESTAMP_ZONE_CET    "CET"
    # define CSPS_TIMESTAMP_ZONE_CEST   "CEST"
    # define CSPS_TIMESTAMP_ZONE_EET    "EET"
    # define CSPS_TIMESTAMP_ZONE_EEST   "EEST"

/*
    Header - Preprocessor macros
 */

/*
    Header - Typedefs
 */

    /* Define gps signal quality buffer type */
    typedef uint64_t            csps_Time_t;
    typedef int64_t             csps_Diff_t;

    /* Define literal suffix */
    # define csps_Time_s(x)     UINT64_C(x)
    # define csps_Diff_s(x)     INT64_C(x)

    /* Define formated output specifiers */
    # define csps_Time_p        PRIu64
    # define csps_Diff_p        PRId64

    /* Define formated input specifiers */
    # define csps_Time_i        SCNu64
    # define csps_Diff_i        SCNd64

/*
    Header - Structures
 */

/*
    Header - Function prototypes
 */

    csps_Time_t csps_timestamp(

        const csps_Void_t * const cspsRec

    );

    csps_Time_t csps_timestamp_compose(

        csps_Time_t cspsSec,
        csps_Time_t cspsUsec

    );

    csps_Time_t csps_timestamp_sec(

        csps_Time_t cspsT

    );

    csps_Time_t csps_timestamp_usec(

        csps_Time_t cspsT

    );

    csps_Enum_t csps_timestamp_eq(

        csps_Time_t cspsTa,
        csps_Time_t cspsTb

    );

    csps_Enum_t csps_timestamp_ge(

        csps_Time_t cspsTa,
        csps_Time_t cspsTb

    );

    uint64_t csps_timestamp_add(

        csps_Time_t cspsTa,
        csps_Time_t cspsTb

    );

    uint64_t csps_timestamp_diff(

        csps_Time_t cspsTa,
        csps_Time_t cspsTb

    );

    csps_Real_t csps_timestamp_float(

        csps_Time_t cspsT

    );

    csps_Time_t csps_timestamp_local(

        const csps_Char_t * const cspsZone,
        csps_Time_t cspsUTC

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

