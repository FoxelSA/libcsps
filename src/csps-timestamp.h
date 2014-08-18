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

    /*! \file   csps-timestamp.h
     *  \author Nils Hamel (n.hamel@foxel.ch)
     *
     *  Timestamp management
     */

/*
    Header - Include guard
 */

    # ifndef __LP_TIMESTAMP__
    # define __LP_TIMESTAMP__

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
    # define LP_TIMESTAMP_ZONE_WET    "WET"
    # define LP_TIMESTAMP_ZONE_WEST   "WEST"
    # define LP_TIMESTAMP_ZONE_CET    "CET"
    # define LP_TIMESTAMP_ZONE_CEST   "CEST"
    # define LP_TIMESTAMP_ZONE_EET    "EET"
    # define LP_TIMESTAMP_ZONE_EEST   "EEST"

/*
    Header - Preprocessor macros
 */

/*
    Header - Typedefs
 */

    /* Define gps signal quality buffer type */
    typedef uint64_t            lp_Time_t;
    typedef int64_t             lp_Diff_t;

    /* Define literal suffix */
    # define lp_Time_s(x)       UINT64_C(x)
    # define lp_Diff_s(x)       INT64_C(x)

    /* Define formated output specifiers */
    # define lp_Time_p          PRIu64
    # define lp_Diff_p          PRId64

    /* Define formated input specifiers */
    # define lp_Time_i          SCNu64
    # define lp_Diff_i          SCNd64

/*
    Header - Structures
 */

/*
    Header - Function prototypes
 */

    /*! \brief Timestamp extractor from elphel camera FPGA event logger
     *  
     *  Extract timestamp, i.e. unix timestamp and microseconds, from the
     *  binary record of the elphel camera FPGA event logger.
     *  
     *  \param lpRec Pointer to the binary record
     *  \return Returns the extracted timestamp
     */

    lp_Time_t lp_timestamp(

        const lp_Void_t * const lpRec

    );

    /*! \brief Timestamp composer
     *  
     *  Compose timestamp on the base of an unix timestamp and a microsecond
     *  part.
     *  
     *  \param lpSec Unix timestamp
     *  \param lpUsec Microsecond integer
     *  \return Returns composed timestamp
     */

    lp_Time_t lp_timestamp_compose(

        lp_Time_t lpSec,
        lp_Time_t lpUsec

    );

    /*! \brief Extract unix timestamp part from timestamp
     *  
     *  Extract the unix timestamp part from a entire timestamp, i.e.
     *  unix timestamp and microseconds.
     *  
     *  \param lpT Timestamp
     *  \return Returns extracted unix timestamp
     */

    lp_Time_t lp_timestamp_sec(

        lp_Time_t lpT

    );

    /*! \brief Extract microseconds part from timestamp
     *  
     *  Extract the microseconds part from a entire timestamp, i.e.
     *  unix timestamp and microseconds.
     *  
     *  \param lpT Timestamp
     *  \return Returns extracted microseconds
     */

    lp_Time_t lp_timestamp_usec(

        lp_Time_t lpT

    );

    /*! \brief Timestamp arithmetic - Equality
     *  
     *  Verify timestamps equality.
     *  
     *  \param lpTa First timestamp
     *  \param lpTb Second timestamp
     *  \return Returns LP_TRUE if timestamp are equal
     */

    lp_Enum_t lp_timestamp_eq(

        lp_Time_t lpTa,
        lp_Time_t lpTb

    );

    /*! \brief Timestamp arithmetic - Greater or equal
     *  
     *  Verify timestamps order.
     *  
     *  \param lpTa First timestamp
     *  \param lpTb Second timestamp
     *  \return Returns LP_TRUE first timestamp is greater or equal to the second timestamp
     */

    lp_Enum_t lp_timestamp_ge(

        lp_Time_t lpTa,
        lp_Time_t lpTb

    );

    /*! \brief Timestamp arithmetic - Addition
     *  
     *  Add the two timestamps given as parameters.
     *  
     *  \param lpTa First timestamp
     *  \param lpTb Second timestamp
     *  \return Returns a timestamp that results from the addition of the two timestamps
     */

    uint64_t lp_timestamp_add(

        lp_Time_t lpTa,
        lp_Time_t lpTb

    );

    /*! \brief Timestamp arithmetic - Difference
     *  
     *  Compute the absolute difference between two 
     *  
     *  \param lpTa First timestamp
     *  \param lpTb Second timestamp
     *  \return Returns a timestamp that stores the absolute difference between the two timestamps
     */

    uint64_t lp_timestamp_diff(

        lp_Time_t lpTa,
        lp_Time_t lpTb

    );

    /*! \brief Timestamp conversion - Floating point
     *  
     *  Convert the timestamp integer structure to a floating point representation
     *  of the timestamp.
     *  
     *  This function has to be managed with care. Unix timestamp, that stores seconds
     *  from EPOCH are 32-bits integers. The microseconds are integer value from 0 to
     *  999999, that is 20-bits at worse. The floating point type significand has to
     *  be able to stores 52 bits in the worst case.
     *  
     *  \param lpT Timestamp
     *  \return Returns a floating point value that contains the timestamp value
     */

    lp_Real_t lp_timestamp_float(

        lp_Time_t lpT

    );

    /*! \brief Convert UTC time to local time
     *  
     *  Convert an UTC timestamp to local time timestamp.
     *  
     *  \param lpZone Targetted local time zone
     *  \param lpUTC UTC timestamp
     *  \return Returns local time timestamp
     */

    lp_Time_t lp_timestamp_local(

        const lp_Char_t * const lpZone,
        lp_Time_t lpUTC

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

