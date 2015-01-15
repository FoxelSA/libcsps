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

    /*! \file   csps-query-trigger.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  CSPS trigger query interface
     */

/*
    Header - Include guard
 */

    # ifndef __LP_QUERY_TRIGGER__
    # define __LP_QUERY_TRIGGER__

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
    # define lp_query_trigger_tag( lpStruct )       ( lpStruct.qrStrmTag )
    # define lp_query_trigger_syn( lpStruct )       ( lpStruct.qrStrmSyn )

/*
    Header - Typedefs
 */

/*
    Header - Structures
 */

    /*! \struct lp_Query_Trigger_struct
     *  \brief Camera trigger query structure
     *
     *  This structure is used to stored necessary informations that synchronize
     *  camera trigger timestamps, used by some devices to name the camera 
     *  images, with the synchronization clock used as link between devices
     *  (camera triggers, GPS measures, IMU measures ...).
     *
     *  \var lp_Query_Trigger_struct::qrStatus
     *  Query status. If LP_FALSE, the query has failed
     *  \var lp_Query_Trigger_struct::qrSize
     *  Size, in bytes, of streams
     *  \var lp_Query_Trigger_struct::qrStrmTag
     *  Camera trigger timestamp stream data
     *  \var lp_Query_Trigger_struct::qrStrmSyn
     *  Synchronization stream data
     */

    typedef struct lp_Query_Trigger_struct {

        /* Query status */
        lp_Enum_t   qrStatus;

        /* Streams size */
        lp_Size_t   qrSize;

        /* Streams data */
        lp_Time_t * qrStrmTag;
        lp_Time_t * qrStrmSyn;

    } lp_Trigger_t;

/*
    Header - Function prototypes
 */


    /*! \brief CSPS query - Trigger - Initialization
     *
     *  This function creates the query on camera trigger structure neeeded to
     *  perform queries on processed.
     *
     *  \param  lpPath Path CSPS structure
     *  \param  lpTag Device name
     *  \param  lpModule Reference stream
     *
     *  \return Created query on camera trigger structure
     */

    lp_Trigger_t lp_query_trigger_read(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule

    );

    /*! \brief CSPS query - Trigger - Deletion
     * 
     *  This function deletes the query on camera trigger structure.
     *
     *  \param lpTrigger Pointer to query structure
     */

    lp_Void_t lp_query_trigger_delete(

        lp_Trigger_t * const lpTrigger

    );

    /*! \brief CSPS query - Trigger - Method
     *
     *  This method allows to get the size, in bytes, of the camera trigger
     *  imported streams.
     *
     *  \param lpTrigger Pointer to query structure
     */

    lp_Size_t lp_query_trigger_size(

        lp_Trigger_t const * const lpTrigger

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

