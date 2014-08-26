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
     *  \author Nils Hamel (n.hamel@foxel.ch)
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

    /* Define stream component types */
    # define LP_STREAM_C_SYN "syn" /* Synchronization */

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
     *  \param lpSize Size, in bytes, of the component size to create
     *  \return Returns pointer to the allocated memory
     */

    lp_Void_t * lp_stream_create(

        lp_Size_t lpSize

    );

    /*! \brief Stream basic manipulation
     *  
     *  Delete a stream component memory allocation.
     * 
     *  \param lpStream Pointer to stream component to unallocate
     *  \return Returns always an invalid pointer
     */

    lp_Void_t * lp_stream_delete(

        lp_Void_t * lpStream

    );

    /*! \brief Stream component size extractor
     *  
     *  Extract the size, in type unit, of the desired stream component
     *  on the base of the size of the synchronization component.
     *  
     *  \param lpPath Path to the CSPS structure
     *  \param lpDevice Device type
     *  \param lpTag Device name
     *  \param lpModule CSPS module to consider
     *  \return Returns the size of the stream in bytes
     */

    lp_Size_t lp_stream_size(

        const lp_Char_t * const lpPath,
        const lp_Char_t * const lpDevice,
        const lp_Char_t * const lpTag,
        const lp_Char_t * const lpModule

    );

    /*! \brief Stream component data reader
     *  
     *  Reads the data contained in the specified stream component.
     *  
     *  \param lpPath Path to the CSPS structure
     *  \param lpDevice Device type
     *  \param lpTag Device name
     *  \param lpModule CSPS module to consider
     *  \param lpType Type of the data stored by the considered stream component
     *  \param lpSize Size of the considered stream component
     *  \return Returns a void pointer to the data
     */

    lp_Void_t * lp_stream_read(

        const lp_Char_t * const lpPath,
        const lp_Char_t * const lpDevice,
        const lp_Char_t * const lpTag,
        const lp_Char_t * const lpModule,
        const lp_Char_t * const lpType,
        lp_Size_t               lpSize

    );

    /*! \brief Stream component data writer
     *  
     *  Writes the memory data into the desired stream component.
     *  
     *  \param lpPath Path to the CSPS structure
     *  \param lpDevice Device type
     *  \param lpTag Device name
     *  \param lpModule CSPS module to consider
     *  \param lpType Type of the data stored by the considered stream component
     *  \param lpStream Void pointer to the memory data
     *  \param lpSize Size, in bytes, of the memory data
     */

    lp_Void_t lp_stream_write(

        const lp_Char_t * const lpPath,
        const lp_Char_t * const lpDevice,
        const lp_Char_t * const lpTag,
        const lp_Char_t * const lpModule,
        const lp_Char_t * const lpType,
        const lp_Void_t * const lpStream,
        lp_Size_t               lpSize

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

