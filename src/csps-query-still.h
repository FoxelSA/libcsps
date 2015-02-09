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
     *  This structure is used to perform queries on automatically detected
     *  still ranges. The results consist in a boolean value that indicates if
     *  the provided timestamp is in a still range.
     *
     *  \var lp_Query_Still_struct::qrStatus
     *  Structure state. If LP_FALSE, the structure cannot be used
     *  \var lp_Query_Still_struct::qrStatus
     *  Query status. If LP_FALSE, the query failed
     *  \var lp_Query_Still_struct::qrStill
     *  Stores LP_TRUE if timestamp is in still range
     *  \var lp_Query_Still_struct::qrSize
     *  Size, in type units, of stream
     *  \var lp_Query_Still_struct::qrStrmTag
     *  Stream component for still ranges final timestamps
     *  \var lp_Query_Still_struct::qrStrmSyn
     *  Stream component for synchronization
     */

    typedef struct lp_Query_Still_struct {

        /* Query status */
        lp_Enum_t   qrState;
        lp_Enum_t   qrStatus;

        /* Query fields */
        lp_Enum_t   qrStill;

        /* Stream size */
        lp_Size_t   qrSize;

        /* Stream components */
        lp_Time_t * qrStrmTag;
        lp_Time_t * qrStrmSyn;

    } lp_Still_t;

/*
    Header - Function prototypes
 */

    /*! \brief CSPS query - Still - Handle
     *
     *  Creates and initialize the query structure on the base of the provided
     *  switches. This structure can then be used to perform queries. Before
     *  any query, the structure initialization have to be checked.
     *
     *  \param  lpPath   Path to CSPS structure
     *  \param  lpTag    CSPS-tag of device
     *  \param  lpModule CSPS-name of module
     *
     *  \return Created query structure
     */

    lp_Still_t lp_query_still_create(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule

    );

    /*! \brief CSPS query - Still - Handle
     * 
     *  Deletes the query structure and unallocates the stream components
     *  memory buffers. It also clears the structure state and status.
     *
     *  \param lpStill Pointer to query structure
     */

    lp_Void_t lp_query_still_delete(

        lp_Still_t * const lpStill

    );

    /*! \brief CSPS query - Still - Method
     *
     *  Returns the state of the query structure.
     *
     *  \param  lpStill Pointer to query structure
     *
     *  \return Returns LP_TRUE if query structure is correctly initialized
     */

    lp_Enum_t lp_query_still_state(

        lp_Still_t const * const lpStill

    );

    /*! \brief CSPS query - Still - Method
     *
     *  Returns the status of the query structure.
     *
     *  \param  lpStill Pointer to query structure
     *
     *  \return Returns LP_TRUE if query succeed
     */

    lp_Enum_t lp_query_still_status(

        lp_Still_t const * const lpStill

    );

    /*! \brief CSPS query - Still - Method
     *
     *  Returns the stream size stored in the query structure.
     *
     *  \param  lpStill Pointer to query structure
     *
     *  \return Returns the size, in type units, of the imported stream
     */

    lp_Size_t lp_query_still_size(

        lp_Still_t const * const lpStill

    );

    /*! \brief CSPS query - Still - Query
     *
     *  This function allows to detect if a given synchronization timestamp is
     *  contained in a detected still range. The query structure has to be
     *  already initialized.
     *
     *  If the query fails, the qrStatus field of the structure is set to
     *  LP_FALSE, LP_TRUE otherwise.
     *
     *  \param lpStill Pointer to query structure
     *  \param lpTime  Synchronization timestamp
     */

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

