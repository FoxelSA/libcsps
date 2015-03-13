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

    /*! \file   csps-query-position.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  CSPS position query interface
     */

/*
    Header - Include guard
 */

    # ifndef __LP_QUERY_POSITION__
    # define __LP_QUERY_POSITION__

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
    # include "csps-system.h"
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

    /*! \struct lp_Query_Position_struct
     *  \brief Ellipsoidal coordinates query structure
     *  
     *  This structure is used to query a position on earth expressed in an
     *  ellipsoidal coordinates system.
     *  
     *  \var lp_Query_Position_struct::qrStatus
     *  Structure state. If LP_FALSE, the structure cannot be used
     *  \var lp_Query_Position_struct::qrStatus
     *  Query status. If LP_FALSE, the query failed
     *  \var lp_Query_Position_struct::qrLatitude
     *  Latitude in decimal degrees
     *  \var lp_Query_Position_struct::qrLongitude
     *  Longitude in decimal degrees
     *  \var lp_Query_Position_struct::qrAltitude
     *  Altitude in meters above mean see level
     *  \var lp_Query_Position_struct::qrWeak
     *  Interpolation parameter distance to nearest physical measure
     *  \var lp_Query_Position_struct::qrSize
     *  Size, in type units, of stream
     *  \var lp_Query_Position_struct::qrStrmLat
     *  Stream component for latitude
     *  \var lp_Query_Position_struct::qrStrmLon
     *  Stream component for longitude
     *  \var lp_Query_Position_struct::qrStrmAlt
     *  Stream component for altitude
     *  \var lp_Query_Position_struct::qrStrmSyn
     *  Stream component for synchronization
     */

    typedef struct lp_Query_Position_struct {

        /* Query status */
        lp_Enum_t   qrState;
        lp_Enum_t   qrStatus;

        /* Query fields */
        lp_Real_t   qrLatitude;
        lp_Real_t   qrLongitude;
        lp_Real_t   qrAltitude;

        /* Extrapolation weakness */
        lp_Real_t   qrWeak;

        /* Stream size */
        lp_Size_t   qrSize;

        /* Stream components */
        lp_Real_t * qrStrmLat;
        lp_Real_t * qrStrmLon;
        lp_Real_t * qrStrmAlt;
        lp_Time_t * qrStrmSyn;

    } lp_Position_t;

/*
    Header - Function prototypes
 */

    /*! \brief CSPS query - Position - Handle
     *
     *  This function is a front-end to lp_query_position_create function that
     *  takes advantage of the origin directive introduced in topology. It 
     *  retrieves the module and device name and tag declared as position origin 
     *  in the topology in order to call lp_query_orientation_create. It then
     *  returns the created query structure on orientation.
     *
     *  \param  lpPath Path to CSPS structure
     *
     *  \return Created query structure
     */

    lp_Position_t lp_query_position_origin(

        lp_Char_t const * const lpPath

    );

    /*! \brief CSPS query - Position - Handle
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

    lp_Position_t lp_query_position_create(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule

    );

    /*! \brief CSPS query - Position - Handle
     * 
     *  Deletes the query structure and unallocates the stream components
     *  memory buffers. It also clears the structure state and status.
     *
     *  \param lpPosition Pointer to query structure
     */

    lp_Void_t lp_query_position_delete( 

        lp_Position_t * const lpPosition 

    );

    /*! \brief CSPS query - Position - Method
     *
     *  Returns the state of the query structure.
     *
     *  \param  lpPosition Pointer to query structure
     *
     *  \return Returns LP_TRUE if query structure is correctly initialized
     */

    lp_Enum_t lp_query_position_state(

        lp_Position_t const * const lpPosition

    );

    /*! \brief CSPS query - Position - Method
     *
     *  Returns the status of the query structure.
     *
     *  \param  lpPosition Pointer to query structure
     *
     *  \return Returns LP_TRUE if query succeed
     */

    lp_Enum_t lp_query_position_status(

        lp_Position_t const * const lpPosition

    );

    /*! \brief CSPS query - Position - Method
     *
     *  Returns the stream size stored in the query structure.
     *
     *  \param  lpPosition Pointer to query structure
     *
     *  \return Returns the size, in type units, of the imported stream
     */

    lp_Size_t lp_query_position_size( 

        lp_Position_t const * const lpPosition

    );

    /*! \brief CSPS query - Position - Query
     *
     *  This function performs a query on ellipsoidal position based on the
     *  provided synchronization timestamp. The query structure has to be 
     *  already initialized.
     *
     *  If the query fails, the qrStatus field of the structure is set to
     *  LP_FALSE, LP_TRUE otherwise.
     *
     *  \param lpPosition Pointer to query structure
     *  \param lpTime     Timestamp of the position
     */

    lp_Void_t lp_query_position(

        lp_Position_t       * const lpPosition,
        lp_Time_t   const         lpTime

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

