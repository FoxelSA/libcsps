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

/*
    Header - Typedefs
 */

/*
    Header - Structures
 */

    /*! \struct lp_Query_Timestamp_struct
     *  \brief Camera record and device synchronization
     *
     *  This structure is used to obtain time difference between camera
     *  records and the master clock used to synchronize signals.
     *  
     *  \var lp_Query_Timestamp_struct::qrStatus
     *  Query status. If LP_FALSE, the query has failed
     *  \var lp_Query_Timestamp_struct::qrTimestamp
     *  Image clock timestamp corresponding to the camera record
     *  \var lp_Query_Position_struct::qrSize
     *  Size, in bytes, of streams
     *  \var lp_Query_Position_struct::qrQRYtag
     *  Camera trigger timestamp data
     *  \var lp_Query_Position_struct::qrQRYsyn
     *  Synchronization stream data
     */

    typedef struct lp_Query_Timestamp_struct {

        /* Query status */
        lp_Enum_t   qrStatus;

        /* Event-logger correspondance */
        lp_Time_t   qrTimestamp;

        /* Streams size */
        lp_Size_t   qrSize;

        /* Streams data */
        lp_Time_t * qrQRYtag;
        lp_Time_t * qrQRYsyn;

    } lp_Query_Timestamp_t;

    /*! \struct lp_Query_Position_struct
     *  \brief WGS84 position query structure
     *  
     *  This structure is used to obtain a position according to WGS84 standard.
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
     *  \var lp_Query_Position_struct::qrQRYlat
     *  Latitude stream data
     *  \var lp_Query_Position_struct::qrQRYlon
     *  Longitude stream data
     *  \var lp_Query_Position_struct::qrQRYalt
     *  Altitude stream data
     *  \var lp_Query_Position_struct::qrQRYsyn
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
        lp_Real_t * qrStrmlat;
        lp_Real_t * qrStrmlon;
        lp_Real_t * qrStrmalt;
        lp_Time_t * qrStrmsyn;

    } lp_Query_Position_t, lp_Geopos_t;

    /*! \struct lp_Query_Orientation_struct
     *  \brief Orientation query structure
     *  
     *  This structure is used to obtain orientation of the frame attached to
     *  the device.
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
     *  \var lp_Query_Position_struct::qrSize
     *  Size, in bytes, of streams
     *  \var lp_Query_Position_struct::qrQRYfxx
     *  X-component of x-vector frame stream data
     *  \var lp_Query_Position_struct::qrQRYfxy
     *  Y-component of x-vector frame stream data
     *  \var lp_Query_Position_struct::qrQRYfxz
     *  Z-component of x-vector frame stream data
     *  \var lp_Query_Position_struct::qrQRYfyx
     *  X-component of y-vector frame stream data
     *  \var lp_Query_Position_struct::qrQRYfyy
     *  Y-component of y-vector frame stream data
     *  \var lp_Query_Position_struct::qrQRYfyz
     *  Z-component of y-vector frame stream data
     *  \var lp_Query_Position_struct::qrQRYfzx
     *  X-component of z-vector frame stream data
     *  \var lp_Query_Position_struct::qrQRYfzy
     *  Y-component of z-vector frame stream data
     *  \var lp_Query_Position_struct::qrQRYfzz
     *  Z-component of z-vector frame stream data
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
        lp_Real_t * qrQRYfxx;
        lp_Real_t * qrQRYfxy;
        lp_Real_t * qrQRYfxz;
        lp_Real_t * qrQRYfyx;
        lp_Real_t * qrQRYfyy;
        lp_Real_t * qrQRYfyz;
        lp_Real_t * qrQRYfzx;
        lp_Real_t * qrQRYfzy;
        lp_Real_t * qrQRYfzz;
        lp_Time_t * qrQRYsyn;

    } lp_Query_Orientation_t, lp_Orient_t;

/*
    Header - Function prototypes
 */

    /*! \brief CSPS query - Position - Initialization
     *  
     *
     *  \return
     */

    lp_Geopos_t lp_query_position_read(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpDevice,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule

    );

    /*! \brief Source - CSPS query - Position - Deletion
     *  
     *
     *  \return
     */

    lp_Void_t lp_query_position_delete( 

        lp_Geopos_t * const lpGeopos 

    );

    /*! \brief Source - CSPS query - Position
     *  
     *
     *  \return
     */

    lp_Void_t lp_query_position(

        lp_Geopos_t       * const lpGeopos,
        lp_Time_t   const         lpTimestamp

    );

    lp_Query_Orientation_t lp_query_orientation_create(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpDevice,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule

    );

    lp_Enum_t lp_query_orientation(

        lp_Time_t              const         lpTimestamp,
        lp_Query_Orientation_t       * const lpOrientation

    );

    lp_Void_t lp_query_orientation_delete(

        lp_Query_Orientation_t * const lpOrientation

    );

    /*! \brief Query master clock timestamp for camera record
     *  
     *  This function returns timestamp from the master clock on the base of the
     *  timestamp used to designate image record.
     *  
     *  \param  lpPath      Path CSPS structure
     *  \param  lpDevice    Device tag
     *  \param  lpTag       Device name
     *  \param  lpModule    CSPS stream to consider
     *  \param  lpTimestamp Reference timestamp
     *
     *  \return Returns a timestamp structure
     */

    lp_Query_Timestamp_t lp_query_timestamp_by_timestamp(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpDevice,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule,        
        lp_Time_t const         lpTimestamp

    );

    /*! \brief Query WGS84 position by timestamp
     *  
     *  This function returns WGS84 position according to specified timestamp.
     *  If the given timestamp is outside of the range, the query fails.
     *  
     *  \param  lpPath      Path CSPS structure
     *  \param  lpDevice    Device tag
     *  \param  lpTag       Device name
     *  \param  lpModule    CSPS stream to consider
     *  \param  lpTimestamp Reference timestamp
     *
     *  \return Returns a WGS84 position structure
     */

    lp_Query_Position_t lp_query_position_by_timestamp(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpDevice,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule,
        lp_Time_t const         lpTimestamp

    );

    /*! \brief Orientation query by timestamp
     *  
     *  This function returns the orientation according to the given timestamp.
     *  If the given timestamp is outside of the range, the query fails.
     *  
     *  \param  lpPath      Path CSPS structure
     *  \param  lpDevice    Device tag
     *  \param  lpTag       Device name
     *  \param  lpModule    CSPS stream to consider
     *  \param  lpTimestamp Reference timestamp
     *
     *  \return Returns an orientation structure
     */

    lp_Query_Orientation_t lp_query_orientation_by_timestamp(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpDevice,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule,
        lp_Time_t const         lpTimestamp

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

