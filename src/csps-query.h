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

    /*! \file   csps-query.h
     *  \author Nils Hamel (n.hamel@foxel.ch)
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

    /*! \struct lp_QueryTime_struct
     *  \brief Time boundaries query structure
     *  
     *  This structure is used to determine the lowest and highest timestamp
     *  accessible in a given synchronization stream component.
     *
     *  \var lp_QueryTime_struct::qrInitial 
     *  Initial timestamp stored in specified synchronization stream component
     *  \var lp_QueryTime_struct::qrFinal
     *  Final timestamp stored in specified synchronization stream component
     */

    typedef struct lp_QueryTime_struct {

        /* Timestamp range boundaries */
        lp_Time_t qrInitial;
        lp_Time_t qrFinal;

    } lp_QueryTime;

    /*! \struct lp_QueryPosition_struct
     *  \brief WGS84 position query structure
     *  
     *  This structure is used to obtain a position according to WGS84 standard.
     *  
     *  \var lp_QueryPosition_struct::qrStatus
     *  Query status. If LP_FALSE, the query has failed
     *  \var lp_QueryPosition_struct::qrLatitude
     *  Latitude in degrees
     *  \var lp_QueryPosition_struct::qrLongitude
     *  Longitude in degrees
     *  \var lp_QueryPosition_struct::qrAltitude
     *  Altitude, in meters above geoid
     */

    typedef struct lp_QueryPosition_struct {

        /* Query status */
        lp_Enum_t qrStatus;

        /* Position descriptors */
        lp_Real_t qrLatitude;
        lp_Real_t qrLongitude;
        lp_Real_t qrAltitude;

    } lp_QueryPosition;

    /*! \struct lp_QueryOrientation_struct
     *  \brief Orientation query structure
     *  
     *  This structure is used to obtain orientation of the frame attached to
     *  the device.
     *  
     *  \var lp_QueryOrientation_struct::qrStatus
     *  Query status. If LP_FALSE, the query has failed
     *  \var lp_QueryOrientation_struct::qrfxx
     *  X-component of the x-frame vector
     *  \var lp_QueryOrientation_struct::qrfxy
     *  Y-component of the x-frame vector
     *  \var lp_QueryOrientation_struct::qrfxz
     *  Z-component of the x-frame vector
     *  \var lp_QueryOrientation_struct::qrfyx
     *  X-component of the y-frame vector
     *  \var lp_QueryOrientation_struct::qrfyy
     *  Y-component of the y-frame vector
     *  \var lp_QueryOrientation_struct::qrfyz
     *  Z-component of the y-frame vector
     *  \var lp_QueryOrientation_struct::qrfzx
     *  X-component of the z-frame vector
     *  \var lp_QueryOrientation_struct::qrfzy
     *  Y-component of the z-frame vector
     *  \var lp_QueryOrientation_struct::qrfzz
     *  Z-component of the z-frame vector
     */

    typedef struct lp_QueryOrientation_struct {

        /* Query status */
        lp_Enum_t qrStatus;

        /* Orientation descriptor */
        lp_Real_t qrfxx;
        lp_Real_t qrfxy;
        lp_Real_t qrfxz;
        lp_Real_t qrfyx;
        lp_Real_t qrfyy;
        lp_Real_t qrfyz;
        lp_Real_t qrfzx;
        lp_Real_t qrfzy;
        lp_Real_t qrfzz;

    } lp_QueryOrientation;

/*
    Header - Function prototypes
 */

    /*! \brief Query time boudaries
     *  
     *  This function gives the initial and final time that appears
     *  in a given synchronization stream component.
     *  
     *  \param lpPath Path to CSPS structure
     *  \param lpDevice Device type
     *  \param lpTag Device name
     *  \param lpModule CSPS stream to consider
     *  \return Returns a time boundaries structure
     */

    lp_QueryTime lp_query_time(

        const lp_Char_t * const lpPath,
        const lp_Char_t * const lpDevice,
        const lp_Char_t * const lpTag,
        const lp_Char_t * const lpModule

    );

    /*! \brief Query WGS84 position by timestamp
     *  
     *  This function returns WGS84 position according to
     *  specified timestamp. If the given timestamp is
     *  outside of the range, the query fails.
     *  
     *  \param lpPath Path to CSPS structure
     *  \param lpDevice Device type
     *  \param lpTag Device name
     *  \param lpModule CSPS stream to consider
     *  \param lpTimestamp Reference timestamp
     *  \return Returns a WGS84 position structure
     */

    lp_QueryPosition lp_query_position_by_timestamp(

        const lp_Char_t * const lpPath,
        const lp_Char_t * const lpDevice,
        const lp_Char_t * const lpTag,
        const lp_Char_t * const lpModule,
        lp_Time_t               lpTimestamp

    );

    /*! \brief Orientation query by timestamp
     *  
     *  This function returns the orientation according to the
     *  given timestamp. If the given timestamp is outside of
     *  the range, the query fails.
     *  
     *  \param lpPath Path to CSPS structure
     *  \param lpDevice Device type
     *  \param lpTag Device name
     *  \param lpModule CSPS stream to consider
     *  \param lpTimestamp Reference timestamp
     *  \return Returns an orientation structure
     */

    lp_QueryOrientation lp_query_orientation_by_timestamp(

        const lp_Char_t * const lpPath,
        const lp_Char_t * const lpDevice,
        const lp_Char_t * const lpTag,
        const lp_Char_t * const lpModule,
        lp_Time_t               lpTimestamp

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

