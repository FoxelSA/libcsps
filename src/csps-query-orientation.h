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

    /*! \file   csps-query-orientation.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  CSPS orientation query interface
     */

/*
    Header - Include guard
 */

    # ifndef __LP_QUERY_ORIENTATION__
    # define __LP_QUERY_ORIENTATION__

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

    /*! \struct lp_Query_Orientation_struct
     *  \brief Orientation query structure
     *  
     *  This structure is used to query an orientation on earth provided through
     *  a unitary matrix.
     *  
     *  \var lp_Query_Orientation_struct::qrStatus
     *  Structure state. If LP_FALSE, the structure cannot be used
     *  \var lp_Query_Orientation_struct::qrStatus
     *  Query status. If LP_FALSE, the query failed
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
     *  \var lp_Query_Orientation_struct::qrWeak
     *  Interpolation parameter distance to nearest physical measure
     *  \var lp_Query_Orientation_struct::qrSize
     *  Size, in bytes, of streams
     *  \var lp_Query_Orientation_struct::qrStrmfxx
     *  Stream component for X-component of x-vector frame
     *  \var lp_Query_Orientation_struct::qrStrmfxy
     *  Stream component for Y-component of x-vector frame
     *  \var lp_Query_Orientation_struct::qrStrmfxz
     *  Stream component for Z-component of x-vector frame
     *  \var lp_Query_Orientation_struct::qrStrmfyx
     *  Stream component for X-component of y-vector frame
     *  \var lp_Query_Orientation_struct::qrStrmfyy
     *  Stream component for Y-component of y-vector frame
     *  \var lp_Query_Orientation_struct::qrStrmfyz
     *  Stream component for Z-component of y-vector frame
     *  \var lp_Query_Orientation_struct::qrStrmfzx
     *  Stream component for X-component of z-vector frame
     *  \var lp_Query_Orientation_struct::qrStrmfzy
     *  Stream component for Y-component of z-vector frame
     *  \var lp_Query_Orientation_struct::qrStrmfzz
     *  Stream component for Z-component of z-vector frame
     *  \var lp_Query_Orientation_struct::qrStrmSyn
     *  Stream component for synchronization
     */

    typedef struct lp_Query_Orientation_struct {

        /* Query status */
        lp_Enum_t   qrState;
        lp_Enum_t   qrStatus;

        /* Query fields */
        lp_Real_t   qrfxx;
        lp_Real_t   qrfxy;
        lp_Real_t   qrfxz;
        lp_Real_t   qrfyx;
        lp_Real_t   qrfyy;
        lp_Real_t   qrfyz;
        lp_Real_t   qrfzx;
        lp_Real_t   qrfzy;
        lp_Real_t   qrfzz;

        /* Extrapolation weakness */
        lp_Real_t   qrWeak;

        /* Stream size */
        lp_Size_t   qrSize;

        /* Stream components */
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

    /*! \brief CSPS query - Orientation - Handle
     */

    lp_Orient_t lp_query_orientation_origin(

        lp_Char_t const * const lpPath

    );

    /*! \brief CSPS query - Orientation - Handle
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

    lp_Orient_t lp_query_orientation_create(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule

    );

    /*! \brief CSPS query - Orientation - Handle
     * 
     *  Deletes the query structure and unallocates the stream components
     *  memory buffers. It also clears the structure state and status.
     *
     *  \param lpOrient Pointer to query structure
     */

    lp_Void_t lp_query_orientation_delete(

        lp_Orient_t * const lpOrient

    );

    /*! \brief CSPS query - Orientation - Method
     *
     *  Returns the state of the query structure.
     *
     *  \param  lpOrient Pointer to query structure
     *
     *  \return Returns LP_TRUE if query structure is correctly initialized
     */

    lp_Enum_t lp_query_orientation_state(

        lp_Orient_t const * const lpOrient

    );

    /*! \brief CSPS query - Position - Method
     *
     *  Returns the status of the query structure.
     *
     *  \param  lpOrient Pointer to query structure
     *
     *  \return Returns LP_TRUE if query succeed
     */

    lp_Enum_t lp_query_orientation_status(

        lp_Orient_t const * const lpOrient

    );

    /*! \brief CSPS query - Orientation - Method
     *
     *  Returns the stream size stored in the query structure.
     *
     *  \param  lpOrient Pointer to query structure
     *
     *  \return Returns the size, in type units, of the imported stream
     */

    lp_Size_t lp_query_orientation_size( 

        lp_Orient_t const * const lpOrient

    );

    /*! \brief CSPS query - Orientation - Method
     *
     *  This method allows to retrieve orientation using linear algebra matrix
     *  formalism to obtain the linear transformation.
     *
     *  \param lpOrient Pointer to query structure
     *  \param lpMatrix Static three by three array in which matrix is returned
     */

    lp_Void_t lp_query_orientation_matrix(

        lp_Orient_t const *  const lpOrient,
        lp_Real_t                  lpMatrix[3][3]

    );

    /*! \brief CSPS query - Orientation - Query
     *  
     *  This function performs a query on orientation based on the provided
     *  timestamp. The query structure has to be already initialized.
     *
     *  If the query fails, the qrStatus field of the structure is set to
     *  LP_FALSE, LP_TRUE otherwise.
     *
     *  \param lpOrient Pointer to query structure
     *  \param lpTime   Timestamp of the position
     */

    lp_Void_t lp_query_orientation(

        lp_Orient_t       * const lpOrient,
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

