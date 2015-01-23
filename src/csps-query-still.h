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

    /*! \file   csps-query-still.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  CSPS trigger query interface
     */

/*
    Header - Include guard
 */

    # ifndef __LP_QUERY_STILL__
    # define __LP_QUERY_STILL__

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

    /* Trigger query structure pointers access */

/*
    Header - Typedefs
 */

/*
    Header - Structures
 */

    /*! \struct lp_Query_Still_struct
     *  \brief Still capture query structure
     *
     *  This structure is use to perform query on detected still range. Usually,
     *  the query is performed through a camera capture timestamp to answer the
     *  capture was made inside a still range.
     *
     *  \var lp_Query_Still_struct::qrStatus
     *  Query status. If LP_FALSE, the query has failed, LP_TRUE otherwise
     *  \var lp_Query_Still_struct::qrStill
     *  Stores LP_TRUE if timestamp is in still range
     *  \var lp_Query_Still_struct::qrSize
     *  Size, in bytes, of streams
     *  \var lp_Query_Still_struct::qrStrmTag
     *  Still range final timestamp stream data 
     *  \var lp_Query_Still_struct::qrStrmSyn
     *  Synchronization stream data
     */

    typedef struct lp_Query_Still_struct {

        /* Query status */
        lp_Enum_t   qrStatus;

        /* Range detection */
        lp_Enum_t   qrStill;

        /* Streams size */
        lp_Size_t   qrSize;

        /* Streams data */
        lp_Time_t * qrStrmTag;
        lp_Time_t * qrStrmSyn;

    } lp_Still_t;

/*
    Header - Function prototypes
 */

    lp_Still_t lp_query_still_create(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule

    );

    lp_Void_t lp_query_still_delete(

        lp_Still_t * const lpStill

    );

    lp_Void_t lp_query_still( 

        lp_Still_t * const lpStill, 
        lp_Time_t    const lpTime

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

