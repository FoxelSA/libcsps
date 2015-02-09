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

/*
    Header - Typedefs
 */

/*
    Header - Structures
 */

    /*! \struct lp_Query_Trigger_struct
     *  \brief Camera trigger query structure
     *
     *  This structure is used to perform queries on camera trigger timestamps
     *  synchronization. Its results consist in two timestamps that links
     *  camera triggers to other devices triggers.
     *
     *  \var lp_Query_Trigger_struct::qrStatus
     *  Structure state. If LP_FALSE, the structure cannot be used
     *  \var lp_Query_Trigger_struct::qrStatus
     *  Query status. If LP_FALSE, the query failed
     *  \var lp_Query_Trigger_struct::qrMaster
     *  Camera trigger timestamp
     *  \var lp_Query_Trigger_struct::qrSynch
     *  Synchronization timestamp
     *  \var lp_Query_Trigger_struct::qrSize
     *  Size, in type units, of stream
     *  \var lp_Query_Trigger_struct::qrStrmTag
     *  Stream component for trigger
     *  \var lp_Query_Trigger_struct::qrStrmSyn
     *  Stream component for synchronization
     */

    typedef struct lp_Query_Trigger_struct {

        /* Structure status */
        lp_Enum_t   qrState;
        lp_Enum_t   qrStatus;

        /* Query fields */
        lp_Time_t   qrMaster;
        lp_Time_t   qrSynch;

        /* Streams size */
        lp_Size_t   qrSize;

        /* Streams components */
        lp_Time_t * qrStrmTag;
        lp_Time_t * qrStrmSyn;

    } lp_Trigger_t;

/*
    Header - Function prototypes
 */


    /*! \brief CSPS query - Trigger - Handle
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

    lp_Trigger_t lp_query_trigger_create(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule

    );

    /*! \brief CSPS query - Trigger - Handle
     * 
     *  Deletes the query structure and unallocates the stream components
     *  memory buffers. It also clears the structure state and status.
     *
     *  \param lpTrigger Pointer to query structure
     */

    lp_Void_t lp_query_trigger_delete(

        lp_Trigger_t * const lpTrigger

    );

    /*! \brief CSPS query - Trigger - Method
     *
     *  Returns the state of the query structure.
     *
     *  \param  lpTrigger Pointer to query structure
     *
     *  \return Returns LP_TRUE if query structure is correctly initialized
     */

    lp_Enum_t lp_query_trigger_state(

        lp_Trigger_t const * const lpTrigger

    );

    /*! \brief CSPS query - Trigger - Method
     *
     *  Returns the status of the query structure.
     *
     *  \param  lpTrigger Pointer to query structure
     *
     *  \return Returns LP_TRUE if query succeed
     */

    lp_Enum_t lp_query_trigger_status(

        lp_Trigger_t const * const lpTrigger

    );

    /*! \brief CSPS query - Trigger - Method
     *
     *  Returns the stream size stored in the query structure.
     *
     *  \param  lpTrigger Pointer to query structure
     *
     *  \return Returns the size, in type units, of the imported stream
     */

    lp_Size_t lp_query_trigger_size(

        lp_Trigger_t const * const lpTrigger

    );

    /*! \brief CSPS query - Trigger - Query
     *
     *  This function allows to query the synchronization timestamp associated
     *  with the provided master timestamp. The query structure has to be
     *  already initialized.
     *
     *  If the query fails, the qrStatus field of the structure is set to
     *  LP_FALSE, LP_TRUE otherwise.
     *
     *  \param lpTrigger Pointer to query structure
     *  \param lpMaster  Master timestamp
     */

    lp_Void_t lp_query_trigger_bymaster(

        lp_Trigger_t * const lpTrigger,
        lp_Time_t      const lpMaster

    );

    /*! \brief CSPS query - Trigger - Query
     *
     *  This function allows to query associated master and synchronization
     *  timestamps based on their offset in the stream. The query structure
     *  has to be already initialized.
     *
     *  If the query fails, the qrStatus field of the structure is set to
     *  LP_FALSE, LP_TRUE otherwise.
     *
     *  \param lpTrigger Pointer to query structure
     *  \param lpIndex   Offset in stream data of the queried values
     */

    lp_Void_t lp_query_trigger_byindex(

        lp_Trigger_t * const lpTrigger,
        lp_Size_t      const lpIndex

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

