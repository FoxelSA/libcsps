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

    # include "csps-imu-moddn.h"

/*
    Source - Total variation denoising with iterative clipping IMU signal denoising
 */

    csps_IMU csps_imu_moddn(

        const csps_Char_t * const cspsPath,
        csps_IMU cspsDevice,
        const csps_Char_t * const cspsName,
        const csps_Char_t * const cspsPS__

    ) {
        
        /* Files size */
        csps_Size_t cspsSize = csps_Size_s( 0 );

        /* Data buffers */
        csps_Real_t * cspsDEVgen = NULL;
        csps_Real_t * cspsDEVden = NULL;
        csps_Time_t * cspsDEVsyn = NULL;

        /* Stream element name array */
        csps_Char_t * cspsElement[6] = { "grx", "gry", "grz", "acx", "acy", "acz" };

        /* Processing variables */
        csps_Size_t cspsIndex = csps_Size_s( 0 );

        /* Obtain stream size */
        cspsSize = csps_stream_size( cspsPath, CSPS_IMU_MODDN_DEV, cspsName, cspsPS__, "syn" ) / sizeof( csps_Time_t );

        /* Read streams data */
        cspsDEVsyn = csps_stream_read( cspsPath, CSPS_IMU_MODDN_DEV, cspsName, cspsPS__, "syn", sizeof( csps_Time_t ) * cspsSize );

        /* Write stream data */
        csps_stream_write( cspsPath, CSPS_IMU_MODDN_DEV, cspsName, CSPS_IMU_MODDN_MOD, "syn", cspsDEVsyn, sizeof( csps_Time_t ) * cspsSize );

        /* Unallocate buffer memory */
        free( cspsDEVsyn );

        /* Stream element denoising loop */
        for ( cspsIndex = csps_Size_s( 0 ); cspsIndex < csps_Size_s( 6 ); cspsIndex ++ ) {

            /* Read streams data */
            cspsDEVgen = csps_stream_read( cspsPath, CSPS_IMU_MODDN_DEV, cspsName, cspsPS__, cspsElement[cspsIndex], sizeof( csps_Real_t ) * cspsSize );

            /* Denoising procedure */
            cspsDEVden = csps_imu_moddn_tvic( cspsDEVgen, cspsSize, csps_Size_s( 10 ), csps_Size_s( 32 ) );

            /* Write stream data */
            csps_stream_write( cspsPath, CSPS_IMU_MODDN_DEV, cspsName, CSPS_IMU_MODDN_MOD, cspsElement[cspsIndex], cspsDEVden, sizeof( csps_Real_t ) * cspsSize );

            /* Unallocate buffer memory */
            free( cspsDEVden );

        }

        /* Return device descriptor */
        return( cspsDevice );

    }

/*
    Source - Total variation denoising with iterative clipping algorithm
 */

    csps_Real_t * csps_imu_moddn_tvic(

        const csps_Real_t * const cspsSignal,
        csps_Size_t cspsSize,
        csps_Size_t cspsRegularity,
        csps_Size_t cspsIteration

    ) {

        /* Allocate denoised signal memory */
        csps_Real_t * cspsDenoised = malloc( cspsSize * sizeof( double ) );

        /* Allocate differential array */
        csps_Real_t * cspsDiff = malloc( ( cspsSize - 1 ) * sizeof( double ) );

        /* Iteration index */
        csps_Size_t cspsIter = csps_Size_s( 0 );

        /* Algorithm variables */
        csps_Size_t cspsIndex = csps_Size_s( 0 );
        csps_Size_t cspsPrevi = csps_Size_s( 0 );
        csps_Real_t cspsClip  = cspsRegularity * csps_Real_s( 0.5 );

        /* Iteration loop */
        while ( ( cspsIter ++ ) < cspsIteration ) {

            /* Optimized algorithm */
            for ( cspsIndex = csps_Size_s( 0 ); cspsIndex < cspsSize; cspsIndex ++ ) {

                /* Boundaries managment */
                if ( cspsIndex == csps_Size_s( 0 ) ) {

                    /* Compute part of y - D'z */
                    cspsDenoised[cspsIndex] = cspsSignal[cspsIndex] + cspsDiff[0];

                } else {

                    /* Compute previous index - optimization */
                    cspsPrevi = cspsIndex - csps_Size_s( 1 );

                    /* Boundaries managment */
                    if ( cspsIndex == ( cspsSize - csps_Size_s( 1 ) ) ) {

                        /* Compute part of y - D'z */
                        cspsDenoised[cspsIndex] = cspsSignal[cspsIndex] - cspsDiff[cspsSize-2];

                    } else {

                        /* Compute part of y - D'z */
                        cspsDenoised[cspsIndex] = cspsSignal[cspsIndex] - cspsDiff[cspsPrevi] + cspsDiff[cspsIndex];

                    }

                    /* Compute z + (1/alpha)Dz */
                    cspsDiff[cspsPrevi] = cspsDiff[cspsPrevi] + ( csps_Real_s( 1.0 ) / csps_Real_s( 3.0 ) ) * ( cspsDenoised[cspsIndex] - cspsDenoised[cspsPrevi] );

                    /* Apply iterative clipping */
                    if ( cspsDiff[cspsPrevi] < - cspsClip ) cspsDiff[cspsPrevi] = - cspsClip;
                    if ( cspsDiff[cspsPrevi] > + cspsClip ) cspsDiff[cspsPrevi] = + cspsClip;

                }

            }

        }

        /* Unallocate differential array */
        free( cspsDiff );

        /* Return pointer to denoised signal */
        return( cspsDenoised );

    }

