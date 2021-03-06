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

    /*! \file   csps-noise.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  Noise reduction algorithms
     */

/*
    Header - Include guard
 */

    # ifndef __LP_NOISE__
    # define __LP_NOISE__

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

    /*! \brief Total variation with iterative clipping
     *  
     *  Performs a total variation with iterative clipping denoising of the 
     *  input data. The denoised signal is then copied in the array of the input
     *  signal.
     *  
     *  \param lpSignal     Pointer to signal data
     *  \param lpSize       Size of the signal, in type units
     *  \param lpRegularity Total variation regularity parameter
     *  \param lpIteration  Number of iterations
     */

    lp_Void_t lp_noise_tvic( 

        lp_Real_t       * const lpSignal, 
        lp_Size_t const         lpSize, 
        lp_Size_t const         lpRegularity, 
        lp_Size_t const         lpIteration 

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

