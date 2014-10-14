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


/*
    Source - Includes
 */

    # include "csps-noise.h"

/*
    Source - Total variation denoising with iterative clipping algorithm
 */

    lp_Void_t lp_noise_tvic( 

        lp_Real_t       * const lpSignal, 
        lp_Size_t const         lpSize, 
        lp_Size_t const         lpRegularity, 
        lp_Size_t const         lpIteration 

    ) {

        /* Allocate denoised signal buffer */
        lp_Real_t * lpBuff = malloc( lpSize * sizeof( lp_Real_t ) );

        /* Allocate differential array */
        lp_Real_t * lpDiff = malloc( ( lpSize - 1 ) * sizeof( lp_Real_t ) );

        /* Iteration index */
        lp_Size_t lpIter = lp_Size_s( 0 );

        /* Algorithm variables */
        lp_Size_t lpIndex = lp_Size_s( 0 );
        lp_Size_t lpPrevi = lp_Size_s( 0 );

        /* Optimization variables */
        lp_Real_t lpClip  = lp_Real_s( 0.5 ) * lpRegularity;

        /* Iteration loop */
        while ( ( lpIter ++ ) < lpIteration ) {

            /* Optimized algorithm */
            for ( lpIndex = lp_Size_s( 0 ); lpIndex < lpSize; lpIndex ++ ) {

                /* Boundaries managment */
                if ( lpIndex == lp_Size_s( 0 ) ) {

                    /* Compute part of y - D'z */
                    lpBuff[lpIndex] = lpSignal[lpIndex] + lpDiff[0];

                } else {

                    /* Compute previous index - optimization */
                    lpPrevi = lpIndex - lp_Size_s( 1 );

                    /* Boundaries managment */
                    if ( lpIndex == ( lpSize - lp_Size_s( 1 ) ) ) {

                        /* Compute part of y - D'z */
                        lpBuff[lpIndex] = lpSignal[lpIndex] - lpDiff[lpSize-2];

                    } else {

                        /* Compute part of y - D'z */
                        lpBuff[lpIndex] = lpSignal[lpIndex] - lpDiff[lpPrevi] + lpDiff[lpIndex];

                    }

                    /* Compute z + (1/alpha)Dz */
                    lpDiff[lpPrevi] = lpDiff[lpPrevi] + ( lp_Real_s( 1.0 ) / lp_Real_s( 3.0 ) ) * ( lpBuff[lpIndex] - lpBuff[lpPrevi] );

                    /* Apply iterative clipping */
                    if ( lpDiff[lpPrevi] < - lpClip ) lpDiff[lpPrevi] = - lpClip;
                    if ( lpDiff[lpPrevi] > + lpClip ) lpDiff[lpPrevi] = + lpClip;

                }

            }

        }

        /* Replace original signal with denoised signal */
        memcpy( lpSignal, lpBuff, lpSize * sizeof( lp_Real_t ) );

        /* Unallocate arrays */
        free( lpBuff );
        free( lpDiff );

    }

