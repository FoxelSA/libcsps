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

    # include "csps-imu-mod-SGNDN.h"

/*
    Source - Total variation denoising with iterative clipping IMU signal denoising
 */

    lp_IMU lp_imu_mod_SGNDN(

        const lp_Char_t * const lpPath,
        lp_IMU lpDevice,
        const lp_Char_t * const lpPS__

    ) {
        
        /* Files size */
        lp_Size_t lpSize = lp_Size_s( 0 );

        /* Data buffers */
        lp_Real_t * lpDEVgen = NULL;
        lp_Real_t * lpDEVden = NULL;
        lp_Time_t * lpDEVsyn = NULL;

        /* Stream element name array */
        lp_Char_t * cspsElement[6] = { "grx", "gry", "grz", "acx", "acy", "acz" };

        /* Processing variables */
        lp_Size_t lpIndex = lp_Size_s( 0 );

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, LP_IMU_MODULE_SGNDN__DEV, lpDevice.dvTag, lpPS__, "syn" ) / sizeof( lp_Time_t );

        /* Read streams data */
        lpDEVsyn = lp_stream_read( lpPath, LP_IMU_MODULE_SGNDN__DEV, lpDevice.dvTag, lpPS__, "syn", sizeof( lp_Time_t ) * lpSize );

        /* Write stream data */
        lp_stream_write( lpPath, LP_IMU_MODULE_SGNDN__DEV, lpDevice.dvTag, LP_IMU_MODULE_SGNDN__MOD, "syn", lpDEVsyn, sizeof( lp_Time_t ) * lpSize );

        /* Unallocate buffer memory */
        free( lpDEVsyn );

        /* Stream element denoising loop */
        for ( lpIndex = lp_Size_s( 0 ); lpIndex < lp_Size_s( 6 ); lpIndex ++ ) {

            /* Read streams data */
            lpDEVgen = lp_stream_read( lpPath, LP_IMU_MODULE_SGNDN__DEV, lpDevice.dvTag, lpPS__, cspsElement[lpIndex], sizeof( lp_Real_t ) * lpSize );

            /* Denoising procedure */
            lpDEVden = lp_imu_mod_SGNDN_tvic( lpDEVgen, lpSize, lp_Size_s( 10 ), lp_Size_s( 32 ) );

            /* Write stream data */
            lp_stream_write( lpPath, LP_IMU_MODULE_SGNDN__DEV, lpDevice.dvTag, LP_IMU_MODULE_SGNDN__MOD, cspsElement[lpIndex], lpDEVden, sizeof( lp_Real_t ) * lpSize );

            /* Unallocate buffer memory */
            free( lpDEVden );

        }

        /* Return device descriptor */
        return( lpDevice );

    }

/*
    Source - Total variation denoising with iterative clipping algorithm
 */

    lp_Real_t * lp_imu_mod_SGNDN_tvic(

        const lp_Real_t * const lpSignal,
        lp_Size_t lpSize,
        lp_Size_t lpRegularity,
        lp_Size_t lpIteration

    ) {

        /* Allocate denoised signal memory */
        lp_Real_t * lpDenoised = malloc( lpSize * sizeof( double ) );

        /* Allocate differential array */
        lp_Real_t * lpDiff = malloc( ( lpSize - 1 ) * sizeof( double ) );

        /* Iteration index */
        lp_Size_t lpIter = lp_Size_s( 0 );

        /* Algorithm variables */
        lp_Size_t lpIndex = lp_Size_s( 0 );
        lp_Size_t lpPrevi = lp_Size_s( 0 );
        lp_Real_t lpClip  = lpRegularity * lp_Real_s( 0.5 );

        /* Iteration loop */
        while ( ( lpIter ++ ) < lpIteration ) {

            /* Optimized algorithm */
            for ( lpIndex = lp_Size_s( 0 ); lpIndex < lpSize; lpIndex ++ ) {

                /* Boundaries managment */
                if ( lpIndex == lp_Size_s( 0 ) ) {

                    /* Compute part of y - D'z */
                    lpDenoised[lpIndex] = lpSignal[lpIndex] + lpDiff[0];

                } else {

                    /* Compute previous index - optimization */
                    lpPrevi = lpIndex - lp_Size_s( 1 );

                    /* Boundaries managment */
                    if ( lpIndex == ( lpSize - lp_Size_s( 1 ) ) ) {

                        /* Compute part of y - D'z */
                        lpDenoised[lpIndex] = lpSignal[lpIndex] - lpDiff[lpSize-2];

                    } else {

                        /* Compute part of y - D'z */
                        lpDenoised[lpIndex] = lpSignal[lpIndex] - lpDiff[lpPrevi] + lpDiff[lpIndex];

                    }

                    /* Compute z + (1/alpha)Dz */
                    lpDiff[lpPrevi] = lpDiff[lpPrevi] + ( lp_Real_s( 1.0 ) / lp_Real_s( 3.0 ) ) * ( lpDenoised[lpIndex] - lpDenoised[lpPrevi] );

                    /* Apply iterative clipping */
                    if ( lpDiff[lpPrevi] < - lpClip ) lpDiff[lpPrevi] = - lpClip;
                    if ( lpDiff[lpPrevi] > + lpClip ) lpDiff[lpPrevi] = + lpClip;

                }

            }

        }

        /* Unallocate differential array */
        free( lpDiff );

        /* Return pointer to denoised signal */
        return( lpDenoised );

    }

