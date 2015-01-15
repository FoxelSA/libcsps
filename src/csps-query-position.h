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
    # include "csps-timestamp.h"
    # include "inter-all.h"

/*
    Header - Preprocessor definitions
 */

/*
    Header - Preprocessor macros
 */

    /* Position query structure pointers access */
    # define lp_query_position_lat( lpStruct )      ( lpStruct.qrStrmLat )
    # define lp_query_position_lon( lpStruct )      ( lpStruct.qrStrmLon )
    # define lp_query_position_alt( lpStruct )      ( lpStruct.qrStrmAlt )
    # define lp_query_position_syn( lpStruct )      ( lpStruct.qrStrmSyn )

/*
    Header - Typedefs
 */

/*
    Header - Structures
 */

    /*! \struct lp_Query_Position_struct
     *  \brief WGS84 position query structure
     *  
     *  This structure is used to query a position according to WGS84 standard
     *  stored in a physical stream, typically coming from a GPS reciever.
     *  
     *  \var lp_Query_Position_struct::qrStatus
     *  Query status. If LP_FALSE, the query has failed, LP_TRUE otherwise
     *  \var lp_Query_Position_struct::qrLatitude
     *  Latitude in degrees
     *  \var lp_Query_Position_struct::qrLongitude
     *  Longitude in degrees
     *  \var lp_Query_Position_struct::qrAltitude
     *  Altitude in meters above mean see level
     *  \var lp_Query_Position_struct::qrSize
     *  Size, in bytes, of streams
     *  \var lp_Query_Position_struct::qrStrmLat
     *  Latitude stream data
     *  \var lp_Query_Position_struct::qrStrmLon
     *  Longitude stream data
     *  \var lp_Query_Position_struct::qrStrmAlt
     *  Altitude stream data
     *  \var lp_Query_Position_struct::qrStrmSyn
     *  Synchronization stream data
     */

    typedef struct lp_Query_Position_struct {

        /* Query status */
        lp_Enum_t   qrStatus;

        /* Position vector */
        lp_Real_t   qrLatitude;
        lp_Real_t   qrLongitude;
        lp_Real_t   qrAltitude;

        /* Streams size */
        lp_Size_t   qrSize;

        /* Streams data */
        lp_Real_t * qrStrmLat;
        lp_Real_t * qrStrmLon;
        lp_Real_t * qrStrmAlt;
        lp_Time_t * qrStrmSyn;

    } lp_Geopos_t;

/*
    Header - Function prototypes
 */

    /*! \brief CSPS query - Position - Handle
     *
     *  This function creates the query on position structure needed to perform
     *  queries on processed data.
     * 
     *  \param lpPath   Path to CSPS directory structure
     *  \param lpTag    Device tag name
     *  \param lpModule Query reference stream
     *
     *  \return Created query on position structure
     */

    lp_Geopos_t lp_query_position_create(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule

    );

    /*! \brief CSPS query - Position - Handle
     *  
     *  This function deletes the query on position structure.
     *
     *  \param lpGeopos Pointer to query structure
     */

    lp_Void_t lp_query_position_delete( 

        lp_Geopos_t * const lpGeopos 

    );

    /*! \brief CSPS query - Position - Method
     *
     *  This function allows to get value of the query status stored in the
     *  query structure.
     *
     *  \param lpGeopos Pointer to query structure
     */

    lp_Enum_t lp_query_position_status(

        lp_Geopos_t const * const lpGeopos

    );

    /*! \brief CSPS query - Position - Method
     *
     *  This method allows to get the size, in type units, of the position
     *  imported streams.
     *
     *  \param lpGeopos Pointer to query structure
     */

    lp_Size_t lp_query_position_size( 

        lp_Geopos_t const * const lpGeopos

    );

    /*! \brief CSPS query - Position - Query
     *
     *  This function performs a query on position based on the provided query
     *  structure and the provided timestamp. The structure has to be already
     *  initialized according to query necessities.
     *
     *  If the query fails, the qrStatus fields of the structure is set to
     *  LP_FALSE, LP_TRUE otherwise. The query results are stored in the
     *  structure fields.
     *
     *  \param lpGeopos     Pointer to query structure
     *  \param lpTimestamp  Timestamp of the position
     *
     */

    lp_Void_t lp_query_position(

        lp_Geopos_t       * const lpGeopos,
        lp_Time_t   const         lpTimestamp

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

