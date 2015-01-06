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

    /*! \file   csps-rotation.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  Rotation related module
     */

/*
    Header - Include guard
 */

    # ifndef __LP_ROTATION__
    # define __LP_ROTATION__

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

/*
    Header - Function prototypes
 */

    /*! \brief Rotation of R3 vector
     *  
     *  Performs a rotation of a R3 vector around x-axis of the referential
     *  frame. The input vector components are used to return the rotated vector
     *  components.
     *  
     *  \param lpAngle      Angle of rotation, in radians
     *  \param lpVectorX    X component of the vector
     *  \param lpVectorY    Y component of the vector
     *  \param lpVectorZ    Z component of the vector
     */

    lp_Void_t lp_rotation_xR3( 

        lp_Real_t const         lpAngle, 
        lp_Real_t       * const lpVectorX, 
        lp_Real_t       * const lpVectorY, 
        lp_Real_t       * const lpVectorZ 

    );

    /*! \brief Rotation of R3 vector
     *  
     *  Performs a rotation of a R3 vector around y-axis of the referential 
     *  frame. The input vector components are used to return the rotated vector
     *  components.
     *  
     *  \param lpAngle      Angle of rotation, in radians
     *  \param lpVectorX    X component of the vector
     *  \param lpVectorY    Y component of the vector
     *  \param lpVectorZ    Z component of the vector
     */

    lp_Void_t lp_rotation_yR3(

        lp_Real_t const         lpAngle, 
        lp_Real_t       * const lpVectorX, 
        lp_Real_t       * const lpVectorY, 
        lp_Real_t       * const lpVectorZ 

    );

    /*! \brief Rotation of R3 vector
     *  
     *  Performs a rotation of a R3 vector around z-axis of the referential 
     *  frame. The input vector components are used to return the rotated vector
     *  components.
     *  
     *  \param lpAngle      Angle of rotation, in radians
     *  \param lpVectorX    X component of the vector
     *  \param lpVectorY    Y component of the vector
     *  \param lpVectorZ    Z component of the vector
     */

    lp_Void_t lp_rotation_zR3( 

        lp_Real_t const         lpAngle, 
        lp_Real_t       * const lpVectorX, 
        lp_Real_t       * const lpVectorY, 
        lp_Real_t       * const lpVectorZ 

    );

    /*! \brief Apply rotation matrix on vector
     *  
     *  Performs a rotation, given by the input matrix, of an R3 vector. The
     *  function do not verify the content of the matrix.
     *  
     *  \param lpMatrix     Rotation matrix
     *  \param lpVectorX    X component of the vector to rotate
     *  \param lpVectorY    Y component of the vector to rotate
     *  \param lpVectorZ    Z component of the vector to rotate
     */

    lp_Void_t lp_rotation_mR3( 

        lp_Real_t         lpMatrix[3][3], 
        lp_Real_t * const lpVectorX, 
        lp_Real_t * const lpVectorY, 
        lp_Real_t * const lpVectorZ 

    );

    /*! \brief Apply invert of rotation matrix on vector
     *  
     *  Performs a rotation, given by the inverted input matrix, of an R3 vector.
     *  The function do not verify the content of the matrix.
     *  
     *  \param lpMatrix     Rotation matrix
     *  \param lpVectorX    X component of the vector to rotate
     *  \param lpVectorY    Y component of the vector to rotate
     *  \param lpVectorZ    Z component of the vector to rotate
     */

    lp_Void_t lp_rotation_iR3( 

        lp_Real_t         lpMatrix[3][3], 
        lp_Real_t * const lpVectorX, 
        lp_Real_t * const lpVectorY, 
        lp_Real_t * const lpVectorZ 

    );

    /*! \brief Rotation matrix of R3 defined by a vector and an angle
     *  
     *  The function computes the rotation matrix that rotates R3 elements
     *  around the given vector using the provided angle as parameter.
     *
     *  \param lpVectorX    X component of vector
     *  \param lpVectorY    Y component of vector
     *  \param lpVectorZ    Z component of vector
     *  \param lpAngle      Rotation angle, in radians
     *  \param lpMatrix     Built rotation matrix defined by the vector and the
     *                      angle
     */

    lp_Void_t lp_rotation_matrix_vaR3(

        lp_Real_t       lpVectorX,
        lp_Real_t       lpVectorY,
        lp_Real_t       lpVectorZ,
        lp_Real_t const lpAngle,
        lp_Real_t       lpMatrix[3][3]

    );

    /*! \brief Rotation matrix of R3 defined by two vector
     *  
     *  The function computes the rotation matrix that brought the A vector into
     *  B vector. The input vectors A and B are arbitrary vectors of R3.
     *  
     *  \param lpVectAX     X component of vector A
     *  \param lpVectAY     Y component of vector A
     *  \param lpVectAZ     Z component of vector A
     *  \param lpVectBX     X component of vector B
     *  \param lpVectBY     Y component of vector B
     *  \param lpVectBZ     Z component of vector B
     *  \param lpMatrix     Built rotation matrix defined by the two vectors
     */

    lp_Void_t lp_rotation_matrix_2vR3( 

        lp_Real_t lpVectAX, 
        lp_Real_t lpVectAY, 
        lp_Real_t lpVectAZ,
        lp_Real_t lpVectBX, 
        lp_Real_t lpVectBY, 
        lp_Real_t lpVectBZ,
        lp_Real_t lpMatrix[3][3]

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

