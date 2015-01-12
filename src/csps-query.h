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

    /*! \file   csps-query.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  CSPS query interface
     */

/*
    Header - Include guard
 */

    # ifndef __LP_QUERY__
    # define __LP_QUERY__

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

    /* Position query structure pointers access */
    # define lp_query_position_lat( lpStruct )      ( lpStruct.qrStrmLat )
    # define lp_query_position_lon( lpStruct )      ( lpStruct.qrStrmLon )
    # define lp_query_position_alt( lpStruct )      ( lpStruct.qrStrmAlt )
    # define lp_query_position_syn( lpStruct )      ( lpStruct.qrStrmSyn )

    /* Orientation query structure pointers access */
    # define lp_query_orientation_fxx( lpStruct )   ( lpStruct.qrStrmfxx )
    # define lp_query_orientation_fxy( lpStruct )   ( lpStruct.qrStrmfxy )
    # define lp_query_orientation_fxz( lpStruct )   ( lpStruct.qrStrmfxz )
    # define lp_query_orientation_fyx( lpStruct )   ( lpStruct.qrStrmfyx )
    # define lp_query_orientation_fyy( lpStruct )   ( lpStruct.qrStrmfyy )
    # define lp_query_orientation_fyz( lpStruct )   ( lpStruct.qrStrmfyz )
    # define lp_query_orientation_fzx( lpStruct )   ( lpStruct.qrStrmfzx )
    # define lp_query_orientation_fzy( lpStruct )   ( lpStruct.qrStrmfzy )
    # define lp_query_orientation_fzz( lpStruct )   ( lpStruct.qrStrmfzz )
    # define lp_query_orientation_syn( lpStruct )   ( lpStruct.qrStrmSyn )

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

    /*! \struct lp_Query_Position_struct
     *  \brief WGS84 position query structure
     *  
     *  This structure is used to obtain a position according to WGS84 standard
     *  stored in a physical stream.
     *  
     *  \var lp_Query_Position_struct::qrStatus
     *  Query status. If LP_FALSE, the query has failed
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

    /*! \struct lp_Query_Orientation_struct
     *  \brief Orientation query structure
     *  
     *  This structure is used to obtain orientation of the frame attached to
     *  the device assembly stored in three physical streams.
     *  
     *  \var lp_Query_Orientation_struct::qrStatus
     *  Query status. If LP_FALSE, the query has failed
     *  \var lp_Query_Orientation_struct::qrfxx
     *  X-component of the x-frame vector
     *  \var lp_Query_Orientation_struct::qrfxy
     *  Y-component of the x-frame vector
     *  \var lp_Query_Orientation_struct::qrfxz
     *  Z-component of the x-frame vector
     *  \var lp_Query_Orientation_struct::qrfyx
     *  X-component of the y-frame vector
     *  \var lp_Query_Orientation_struct::qrfyy
     *  Y-component of the y-frame vector
     *  \var lp_Query_Orientation_struct::qrfyz
     *  Z-component of the y-frame vector
     *  \var lp_Query_Orientation_struct::qrfzx
     *  X-component of the z-frame vector
     *  \var lp_Query_Orientation_struct::qrfzy
     *  Y-component of the z-frame vector
     *  \var lp_Query_Orientation_struct::qrfzz
     *  Z-component of the z-frame vector
     *  \var lp_Query_Orientation_struct::qrSize
     *  Size, in bytes, of streams
     *  \var lp_Query_Orientation_struct::qrStrmfxx
     *  X-component of x-vector frame stream data
     *  \var lp_Query_Orientation_struct::qrStrmfxy
     *  Y-component of x-vector frame stream data
     *  \var lp_Query_Orientation_struct::qrStrmfxz
     *  Z-component of x-vector frame stream data
     *  \var lp_Query_Orientation_struct::qrStrmfyx
     *  X-component of y-vector frame stream data
     *  \var lp_Query_Orientation_struct::qrStrmfyy
     *  Y-component of y-vector frame stream data
     *  \var lp_Query_Orientation_struct::qrStrmfyz
     *  Z-component of y-vector frame stream data
     *  \var lp_Query_Orientation_struct::qrStrmfzx
     *  X-component of z-vector frame stream data
     *  \var lp_Query_Orientation_struct::qrStrmfzy
     *  Y-component of z-vector frame stream data
     *  \var lp_Query_Orientation_struct::qrStrmfzz
     *  Z-component of z-vector frame stream data
     *  \var lp_Query_Orientation_struct::qrStrmSyn
     *  Synchronization stream data
     */

    typedef struct lp_Query_Orientation_struct {

        /* Query status */
        lp_Enum_t qrStatus;

        /* Orientation matrix */
        lp_Real_t qrfxx;
        lp_Real_t qrfxy;
        lp_Real_t qrfxz;
        lp_Real_t qrfyx;
        lp_Real_t qrfyy;
        lp_Real_t qrfyz;
        lp_Real_t qrfzx;
        lp_Real_t qrfzy;
        lp_Real_t qrfzz;

        /* Streams size */
        lp_Size_t   qrSize;

        /* Streams data */
        lp_Real_t * qrStrmfxx;
        lp_Real_t * qrStrmfxy;
        lp_Real_t * qrStrmfxz;
        lp_Real_t * qrStrmfyx;
        lp_Real_t * qrStrmfyy;
        lp_Real_t * qrStrmfyz;
        lp_Real_t * qrStrmfzx;
        lp_Real_t * qrStrmfzy;
        lp_Real_t * qrStrmfzz;
        lp_Time_t * qrStrmSyn;

    } lp_Orient_t;

/*
    Header - Function prototypes
 */

    /*! \brief CSPS query - Trigger - Initialization
     *
     *  This function creates the query on camera trigger structure neeeded to
     *  perform queries on processed.
     *
     *  \param lpPath   Path CSPS structure
     *  \param lpDevice Device tag
     *  \param lpTag    Device name
     *  \param lpModule Reference stream
     *
     *  \return Created query on camera trigger structure
     */

    lp_Trigger_t lp_query_trigger_read(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpDevice,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule

    );

    /*! \brief CSPS query - Trigger - Deletion
     *
     *  This function deletes the query on camera trigger structure.
     * 
     *  \param lpTrigger Pointer to structure
     */

    lp_Void_t lp_query_trigger_delete(

        lp_Trigger_t * const lpTrigger

    );

    /*! \brief CSPS query - Position - Initialization
     *
     *  This function creates the query on position structure needed to perform
     *  queries on processed data.
     * 
     *  \param lpPath   Path CSPS structure
     *  \param lpDevice Device tag
     *  \param lpTag    Device name
     *  \param lpModule Reference stream
     *
     *  \return Created query on position structure
     */

    lp_Geopos_t lp_query_position_read(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpDevice,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule

    );

    /*! \brief Source - CSPS query - Position - Deletion
     *  
     *  This function deletes the query on position structure.
     *
     *  \param lpGeopos Pointer to structure
     */

    lp_Void_t lp_query_position_delete( 

        lp_Geopos_t * const lpGeopos 

    );

    /*! \brief Source - CSPS query - Position
     *
     *  This function performs a query on position based on the provided query
     *  structure and the provided timestamp. The structure has to be already
     *  initialized according to query necessities.
     *
     *  If the query fails, the qrStatus fields of the structure is set to
     *  LP_FALSE, LP_TRUE otherwise. The query results are stored in the
     *  structure fields.
     *
     *  \param lpGeopos     Pointer to structure
     *  \param lpTimestamp  Timestamp of the position
     *
     */

    lp_Void_t lp_query_position(

        lp_Geopos_t       * const lpGeopos,
        lp_Time_t   const         lpTimestamp

    );

    /*! \brief Source - CSPS query - Orientation
     *
     *  This function creates the query on orientation structure needed to
     *  perform queries on processed data.
     * 
     *  \param lpPath   Path CSPS structure
     *  \param lpDevice Device tag
     *  \param lpTag    Device name
     *  \param lpModule Reference stream
     *
     *  \return Created query on orientation structure
     */

    lp_Orient_t lp_query_orientation_read(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpDevice,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule

    );

    /*! \brief Source - CSPS query - Orientation
     *  
     *  This function deletes the query on orientation structure.
     *
     *  \param lpOrient Pointer to structure
     */

    lp_Void_t lp_query_orientation_delete(

        lp_Orient_t * const lpOrient

    );

    /*! \brief Source - CSPS query - Orientation
     *  
     *  This function perform a query on orientation based on the provided query
     *  structure and the provided timestamp. The structure has to be already
     *  initialized according to query necessities.
     *
     *  If the query fails, the qrStatus fields of the structure is set to
     *  LP_FALSE, LP_TRUE otherwise. The query results are stored in the
     *  decriptor fields.
     *
     *  \param lpOrient     Pointer to structure
     *  \param lpTimestamp  Timestamp of the position
     */

    lp_Void_t lp_query_orientation(

        lp_Orient_t       * const lpOrient,
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

