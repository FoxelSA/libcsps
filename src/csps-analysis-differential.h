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

    # ifndef __LP_ANALYSIS_DIFFERENTIAL__
    # define __LP_ANALYSIS_DIFFERENTIAL__

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

    /*! \brief Discrete adaptative first order derivative computation
     *
     *  This function is designed for first order derivative computation using
     *  centered order two FDF in case of homogeneous mesh grid over which the
     *  function to derivate is sampled.
     *
     *  If the function detects an non-homogeneous mesh grid, it compare the
     *  two spaces defined by the three mesh nodes and adapt the derivative
     *  computation. If mesh spaces ratio is above or below the trigger value,
     *  the derivative is computed using an order one uncenterned FDF on the
     *  smallest mesh grid space.
     *
     *  \param  lpMesh0     Sample 0 mesh position
     *  \param  lpMesh1     Sample 1 mesh position
     *  \param  lpMesh2     Sample 2 mesh position
     *  \param  lpSample0   Sample 0 value
     *  \param  lpSample1   Sample 1 value
     *  \param  lpSample2   Sample 2 value
     *  \param  lpTrigger   Minimum ratio that trigger derivative adaptation
     *
     *  \return Returns apatative derivative value
     */

    lp_Real_t csps_analysis_adaptFDF( 

        lp_Real_t const lpMesh0,
        lp_Real_t const lpMesh1,
        lp_Real_t const lpMesh2,
        lp_Real_t const lpSample0,
        lp_Real_t const lpSample1,
        lp_Real_t const lpSample2,
        lp_Real_t const lpTrigger

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

