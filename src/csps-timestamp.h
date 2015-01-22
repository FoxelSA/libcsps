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

    /*! \file   csps-timestamp.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
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

    /* Define range-fault code */
    # define LP_TIMESTAMP_FAULT     lp_Size_s( -1 )     

/*
    Header - Preprocessor macros
 */

    /* Define casting macro */
    # define lp_Time_c( x )         ( ( lp_Time_t ) ( x ) )

    /* Define litteral suffix */
    # define lp_Time_s( x )         UINT64_C( x )

    /* Define formated output specifiers */
    # define lp_Time_p              PRIu64

    /* Define formated input specifiers */
    # define lp_Time_i              SCNu64

/*
    Header - Typedefs
 */

    /* Define timestamp type */
    typedef uint64_t lp_Time_t;

/*
    Header - Structures
 */

/*
    Header - Function prototypes
 */

    /*! \brief Timestamp extractor from elphel camera FPGA event logger
     *  
     *  Extract timestamp, i.e. unix timestamp and microseconds, from the binary
     *  record of the elphel camera FPGA event logger binary buffer.
     *  
     *  \param  lpRec Pointer to the binary record
     *
     *  \return Returns the extracted timestamp
     */

    lp_Time_t lp_timestamp( 

        lp_Void_t const * const lpRec

    );

    /*! \brief Timestamp composer
     *  
     *  Compose timestamp on the base of an unix timestamp and a microsecond
     *  part. The microsecond part is an integer value in [0,999999] range.
     *  
     *  \param  lpSec Unix timestamp
     *  \param  lpUsec Microsecond integer value
     * 
     *  \return Returns composed timestamp
     */

    lp_Time_t lp_timestamp_compose( 

        lp_Time_t const lpSec, 
        lp_Time_t const lpUsec

    );

    /*! \brief Extract unix timestamp part from timestamp
     *  
     *  Extract the unix timestamp part from a entire timestamp, i.e. unix
     *  timestamp and microseconds.
     *  
     *  \param  lpT Timestamp
     *  
     *  \return Returns extracted unix timestamp
     */

    lp_Time_t lp_timestamp_sec(

        lp_Time_t const lpT

    );

    /*! \brief Extract microseconds part from timestamp
     *  
     *  Extract the microseconds part from a entire timestamp, i.e. unix 
     *  timestamp and microseconds.
     *  
     *  \param  lpT Timestamp
     *
     *  \return Returns extracted microseconds
     */

    lp_Time_t lp_timestamp_usec(

        lp_Time_t const lpT

    );

    /*! \brief Timestamp index dichotomous search
     *  
     *  On the base of a given reference timestamp and a growing timestamps
     *  array, the function searches the array index of the equal or nearest 
     *  lower array timestamp based on the reference timestamp using dichotomous
     *  search.
     *  
     *  When the refrence timestamp is out of the array range, a range fault
     *  code is returned by the function (LP_TIMESTAMP_FAULT).
     *  
     *  \param  lpT         Reference timestamp
     *  \param  lpBuffer    Pointer to growing timestamps array
     *  \param  lpSize      Size of the growing timestamps array, in array type
     *                      units
     *
     *  \return Returns the index value or a range fault code
     */

    lp_Size_t lp_timestamp_index( 

        lp_Time_t const         lpT, 
        lp_Time_t const * const lpBuffer, 
        lp_Size_t const         lpSize

    );

    lp_Size_t lp_timestamp_search( 

        lp_Time_t const         lpTime, 
        lp_Time_t const * const lpBuffer, 
        lp_Size_t const         lpSize

    );

    /*! \brief Timestamp arithmetic - Equality
     *  
     *  Verify timestamps equality.
     *  
     *  \param  lpTa First timestamp
     *  \param  lpTb Second timestamp
     *
     *  \return Returns LP_TRUE if timestamp are equal
     */

    lp_Enum_t lp_timestamp_eq( 

        lp_Time_t const lpTa, 
        lp_Time_t const lpTb

    );

    /*! \brief Timestamp arithmetic - Greater or equal
     *  
     *  Verify timestamps order.
     *  
     *  \param  lpTa First timestamp
     *  \param  lpTb Second timestamp
     * 
     *  \return Returns LP_TRUE first timestamp is greater or equal to the
     *          second timestamp
     */

    lp_Enum_t lp_timestamp_ge( 

        lp_Time_t const lpTa, 
        lp_Time_t const lpTb

    );

    /*! \brief Timestamp arithmetic - Addition
     *  
     *  Add the two timestamps given as parameters.
     *  
     *  \param  lpTa First timestamp
     *  \param  lpTb Second timestamp
     *
     *  \return Returns a timestamp that results from the addition of the two
     *          timestamps
     */

    uint64_t lp_timestamp_add(

        lp_Time_t const lpTa,
        lp_Time_t const lpTb

    );

    /*! \brief Timestamp arithmetic - Difference
     *  
     *  Compute the absolute difference between two timestamps. The resulting
     *  timestamp is then always positive.
     *  
     *  \param  lpTa First timestamp
     *  \param  lpTb Second timestamp
     *
     *  \return Returns a timestamp that stores the absolute difference between
     *          the two timestamps
     */

    lp_Time_t lp_timestamp_diff( 

        lp_Time_t lpTa, 
        lp_Time_t lpTb

    );

    /*! \brief Timestamp conversion - Floating point
     *  
     *  Convert the timestamp integer structure to a representation in floating
     *  point type of the timestamp.
     *  
     *  This function has to be managed with care. Unix timestamp, that stores
     *  seconds from EPOCH are 32-bits integers. The microseconds are integer 
     *  value from 0 to 999999, that is 20-bits at worse. The floating point
     *  type significand has to be able to stores 52 bits in the worst case.
     *  
     *  \param  lpT Timestamp
     *
     *  \return Returns a floating point value that contains the timestamp value
     */

    lp_Real_t lp_timestamp_float(

        lp_Time_t const lpT

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

