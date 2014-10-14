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

    /*! \file   csps-stream.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  CSPS stream management
     */

/*
    Header - Include guard
 */

    # ifndef __LP_STREAM__
    # define __LP_STREAM__

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
    # include "csps-path.h"
    # include "csps-timestamp.h"

/*
    Header - Preprocessor definitions
 */

    /* Define stream component - Tags */
    # define LP_STREAM_CPN_TAG      "tag"

    /* Define stream component - GPS measure */
    # define LP_STREAM_CPN_LAT      "lat"
    # define LP_STREAM_CPN_LON      "lon"
    # define LP_STREAM_CPN_ALT      "alt"

    /* Define stream component - Acceleration */
    # define LP_STREAM_CPN_ACX      "acx"
    # define LP_STREAM_CPN_ACY      "acy"
    # define LP_STREAM_CPN_ACZ      "acz"

    /* Define stream component - Gyroscope */
    # define LP_STREAM_CPN_GRX      "grx"
    # define LP_STREAM_CPN_GRY      "gry"
    # define LP_STREAM_CPN_GRZ      "grz"

    /* Define stream component - Frame */
    # define LP_STREAM_CPN_FXX      "fxx"
    # define LP_STREAM_CPN_FXY      "fxy"
    # define LP_STREAM_CPN_FXZ      "fxz"
    # define LP_STREAM_CPN_FYX      "fyx"
    # define LP_STREAM_CPN_FYY      "fyy"
    # define LP_STREAM_CPN_FYZ      "fyz"
    # define LP_STREAM_CPN_FZX      "fzx"
    # define LP_STREAM_CPN_FZY      "fzy"
    # define LP_STREAM_CPN_FZZ      "fzz"

    /* Define stream component - Initial condition */
    # define LP_STREAM_CPN_IXX      "ixx"
    # define LP_STREAM_CPN_IXY      "ixy"
    # define LP_STREAM_CPN_IXZ      "ixz"
    # define LP_STREAM_CPN_IYX      "iyx"
    # define LP_STREAM_CPN_IYY      "iyy"
    # define LP_STREAM_CPN_IYZ      "iyz"
    # define LP_STREAM_CPN_IZX      "izx"
    # define LP_STREAM_CPN_IZY      "izy"
    # define LP_STREAM_CPN_IZZ      "izz"

    /* Define stream component - Synchronization */
    # define LP_STREAM_CPN_SYN      "syn"

/*
    Header - Preprocessor macros
 */

/*
    Header - Typedefs
 */

/*
    Header - Structures
 */

/*
    Header - Function prototypes
 */

    /*! \brief Stream basic manipulation
     *  
     *  Create a stream component memory allocation.
     * 
     *  \param  lpSize  Size, in bytes, of the component to create
     *  
     *  \return Returns pointer to the allocated memory
     */

    lp_Void_t * lp_stream_create(

        lp_Size_t const lpSize

    );

    /*! \brief Stream basic manipulation
     *  
     *  Delete a stream component memory allocation.
     * 
     *  \param  lpStream Pointer to stream component to unallocate
     *  
     *  \return Returns always an invalid pointer (NULL)
     */

    lp_Void_t * lp_stream_delete(

        lp_Void_t * lpStream

    );

    /*! \brief Stream component size extractor
     *  
     *  Extract the size, in type units, of the desired stream component on the
     *  base of the size of the synchronization component.
     *  
     *  \param  lpPath      Path CSPS structure
     *  \param  lpDevice    Device type
     *  \param  lpTag       Device name
     *  \param  lpModule    CSPS module to consider
     * 
     *  \return Returns the size of the stream in type units
     */

    lp_Size_t lp_stream_size(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpDevice,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule

    );

    /*! \brief Stream component data reader
     *  
     *  Reads the data contained in the specified stream component.
     *  
     *  \param lpPath   Path CSPS structure
     *  \param lpDevice Device type
     *  \param lpTag    Device name
     *  \param lpModule CSPS module to consider
     *  \param lpSuffix Suffix of the data stored by the considered stream 
     *                  component
     *  \param lpSize   Size of the considered stream component
     *
     *  \return Returns a void pointer to the data
     */

    lp_Void_t * lp_stream_read(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpDevice,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule,
        lp_Char_t const * const lpSuffix,
        lp_Size_t const         lpSize

    );

    /*! \brief Stream component data writer
     *  
     *  Writes the memory data into the desired stream component.
     *  
     *  \param lpPath   Path CSPS structure
     *  \param lpDevice Device type
     *  \param lpTag    Device name
     *  \param lpModule CSPS module to consider
     *  \param lpSuffix Suffix of the data stored by the considered stream
     *                  component
     *  \param lpStream Void pointer to the memory data
     *  \param lpSize   Size, in bytes, of the memory data
     */

    lp_Void_t lp_stream_write(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpDevice,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule,
        lp_Char_t const * const lpSuffix,
        lp_Void_t const * const lpStream,
        lp_Size_t const         lpSize

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

