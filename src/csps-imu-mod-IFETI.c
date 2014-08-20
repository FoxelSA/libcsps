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

    # include "csps-imu-mod-IFETI.h"

/*
    Source - IMU frame explicit time-integration module
 */

    lp_IMU lp_imu_mod_IFETI( 

        const lp_Char_t * const lpPath, 
        lp_IMU                  lpDevice, 
        const lp_Char_t * const lpPSgr 

    ) {

        /* Integration variables */
        lp_Real_t lpDelta = lp_Real_s( 0.0 );
        lp_Size_t lpParse = lp_Size_s( 0 );

        /* Files size */
        lp_Size_t lpSize = lp_Size_s( 0 );

        /* Initial condition range variables */
        lp_Size_t lpICDw = lp_Size_s( 0 );
        lp_Size_t lpICUp = lp_Size_s( 0 );

        /* Data buffers */
        lp_Real_t * lpDEVgrx = NULL;
        lp_Real_t * lpDEVgry = NULL;
        lp_Real_t * lpDEVgrz = NULL;
        lp_Real_t * lpDEVfxx = NULL;
        lp_Real_t * lpDEVfxy = NULL;
        lp_Real_t * lpDEVfxz = NULL;
        lp_Real_t * lpDEVfyx = NULL;
        lp_Real_t * lpDEVfyy = NULL;
        lp_Real_t * lpDEVfyz = NULL;
        lp_Real_t * lpDEVfzx = NULL;
        lp_Real_t * lpDEVfzy = NULL;
        lp_Real_t * lpDEVfzz = NULL;
        lp_Time_t * lpDEVsyn = NULL;

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, lpPSgr, "syn" ) / sizeof( uint64_t );

        /* Read streams data */
        lpDEVgrx = lp_stream_read( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, lpPSgr, "grx", sizeof( lp_Real_t ) * lpSize );
        lpDEVgry = lp_stream_read( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, lpPSgr, "gry", sizeof( lp_Real_t ) * lpSize );
        lpDEVgrz = lp_stream_read( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, lpPSgr, "grz", sizeof( lp_Real_t ) * lpSize );
        lpDEVsyn = lp_stream_read( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, lpPSgr, "syn", sizeof( lp_Time_t ) * lpSize );

        /* Allocate stream memory */
        lpDEVfxx = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpSize );
        lpDEVfxy = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpSize );
        lpDEVfxz = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpSize );
        lpDEVfyx = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpSize );
        lpDEVfyy = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpSize );
        lpDEVfyz = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpSize );
        lpDEVfzx = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpSize );
        lpDEVfzy = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpSize );
        lpDEVfzz = ( lp_Real_t * ) malloc( sizeof( lp_Real_t ) * lpSize );

        /* Compute time step value */
        lpDelta = lp_Real_s( 1.0 ) / ( ( lp_Real_t ) lpDevice.dvdfreq );

        /* Search intertial still range boundaries timestamps index */
        lpICDw = lp_timestamp_index( lpDevice.dvMin, lpDEVsyn, lpSize );
        lpICUp = lp_timestamp_index( lpDevice.dvMax, lpDEVsyn, lpSize );

        /* Setting initial conditions */
        for ( lpParse = lpICDw ; lpParse <= lpICUp ; lpParse ++ ) {

            /* Assign initial condition on IMU frame */
            lpDEVfxx[lpParse] = lpDevice.dvfxx;
            lpDEVfxy[lpParse] = lpDevice.dvfxy;
            lpDEVfxz[lpParse] = lpDevice.dvfxz;
            lpDEVfyx[lpParse] = lpDevice.dvfyx;
            lpDEVfyy[lpParse] = lpDevice.dvfyy;
            lpDEVfyz[lpParse] = lpDevice.dvfyz;
            lpDEVfzx[lpParse] = lpDevice.dvfzx;
            lpDEVfzy[lpParse] = lpDevice.dvfzy;
            lpDEVfzz[lpParse] = lpDevice.dvfzz;

        }

        /* Frame explicit time-integration - Prograde segment */
        for ( lpParse = lpICUp + lp_Size_s( 1 ) ; lpParse < lpSize ; lpParse ++ ) {

            /* Integration - Advance frame x-vector - x-component */
            lpDEVfxx[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    + lpDEVgry[lpParse-1] * lpDEVfxz[lpParse-1] 
                                    - lpDEVgrz[lpParse-1] * lpDEVfxy[lpParse-1] 

                                )
                                + lpDEVfxx[lpParse-2];

            /* Integration - Advance frame x-vector - y-component */
            lpDEVfxy[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    + lpDEVgrz[lpParse-1] * lpDEVfxx[lpParse-1] 
                                    - lpDEVgrx[lpParse-1] * lpDEVfxz[lpParse-1] 

                                )
                                + lpDEVfxy[lpParse-2];

            /* Integration - Advance frame x-vector - z-component */
            lpDEVfxz[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    + lpDEVgrx[lpParse-1] * lpDEVfxy[lpParse-1] 
                                    - lpDEVgry[lpParse-1] * lpDEVfxx[lpParse-1] 

                                )
                                + lpDEVfxz[lpParse-2];

            /* Integration - Advance frame y-vector - x-component */
            lpDEVfyx[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    + lpDEVgry[lpParse-1] * lpDEVfyz[lpParse-1] 
                                    - lpDEVgrz[lpParse-1] * lpDEVfyy[lpParse-1] 

                                )
                                + lpDEVfyx[lpParse-2];

            /* Integration - Advance frame y-vector - y-component */
            lpDEVfyy[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    + lpDEVgrz[lpParse-1] * lpDEVfyx[lpParse-1] 
                                    - lpDEVgrx[lpParse-1] * lpDEVfyz[lpParse-1] 

                                )
                                + lpDEVfyy[lpParse-2];

            /* Integration - Advance frame y-vector - z-component */
            lpDEVfyz[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    + lpDEVgrx[lpParse-1] * lpDEVfyy[lpParse-1] 
                                    - lpDEVgry[lpParse-1] * lpDEVfyx[lpParse-1] 

                                )
                                + lpDEVfyz[lpParse-2];

            /* Integration - Advance frame z-vector - x-component */
            lpDEVfzx[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    + lpDEVgry[lpParse-1] * lpDEVfzz[lpParse-1] 
                                    - lpDEVgrz[lpParse-1] * lpDEVfzy[lpParse-1] 

                                )
                                + lpDEVfzx[lpParse-2];

            /* Integration - Advance frame z-vector - y-component */
            lpDEVfzy[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    + lpDEVgrz[lpParse-1] * lpDEVfzx[lpParse-1] 
                                    - lpDEVgrx[lpParse-1] * lpDEVfzz[lpParse-1] 

                                )
                                + lpDEVfzy[lpParse-2];

            /* Integration - Advance frame z-vector - z-component */
            lpDEVfzz[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    + lpDEVgrx[lpParse-1] * lpDEVfzy[lpParse-1] 
                                    - lpDEVgry[lpParse-1] * lpDEVfzx[lpParse-1] 

                                )
                                + lpDEVfzz[lpParse-2];

        }

        /* Frame explicit time-integration - Retrograde segment */
        for ( lpParse = lpICDw - lp_Size_s( 1 ) ; lpParse >= 0 ; lpParse -- ) {

            /* Integration - Step back frame x-vector - x-component */
            lpDEVfxx[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    - lpDEVgry[lpParse+1] * lpDEVfxz[lpParse+1] 
                                    + lpDEVgrz[lpParse+1] * lpDEVfxy[lpParse+1] 

                                )
                                + lpDEVfxx[lpParse+2];

            /* Integration - Step back frame x-vector - y-component */
            lpDEVfxy[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    - lpDEVgrz[lpParse+1] * lpDEVfxx[lpParse+1] 
                                    + lpDEVgrx[lpParse+1] * lpDEVfxz[lpParse+1] 

                                )
                                + lpDEVfxy[lpParse+2];

            /* Integration - Step back frame x-vector - z-component */
            lpDEVfxz[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    - lpDEVgrx[lpParse+1] * lpDEVfxy[lpParse+1] 
                                    + lpDEVgry[lpParse+1] * lpDEVfxx[lpParse+1] 

                                )
                                + lpDEVfxz[lpParse+2];

            /* Integration - Step back frame x-vector - x-component */
            lpDEVfyx[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    - lpDEVgry[lpParse+1] * lpDEVfyz[lpParse+1] 
                                    + lpDEVgrz[lpParse+1] * lpDEVfyy[lpParse+1] 

                                )
                                + lpDEVfyx[lpParse+2];

            /* Integration - Step back frame x-vector - y-component */
            lpDEVfyy[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    - lpDEVgrz[lpParse+1] * lpDEVfyx[lpParse+1] 
                                    + lpDEVgrx[lpParse+1] * lpDEVfyz[lpParse+1] 

                                )
                                + lpDEVfyy[lpParse+2];

            /* Integration - Step back frame x-vector - z-component */
            lpDEVfyz[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    - lpDEVgrx[lpParse+1] * lpDEVfyy[lpParse+1] 
                                    + lpDEVgry[lpParse+1] * lpDEVfyx[lpParse+1] 

                                )
                                + lpDEVfyz[lpParse+2];

            /* Integration - Step back frame z-vector - x-component */
            lpDEVfzx[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    - lpDEVgry[lpParse+1] * lpDEVfzz[lpParse+1] 
                                    + lpDEVgrz[lpParse+1] * lpDEVfzy[lpParse+1] 

                                )
                                + lpDEVfzx[lpParse+2];

            /* Integration - Step back frame z-vector - y-component */
            lpDEVfzy[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    - lpDEVgrz[lpParse+1] * lpDEVfzx[lpParse+1] 
                                    + lpDEVgrx[lpParse+1] * lpDEVfzz[lpParse+1] 

                                )
                                + lpDEVfzy[lpParse+2];

            /* Integration - Step back frame z-vector - z-component */
            lpDEVfzz[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    - lpDEVgrx[lpParse+1] * lpDEVfzy[lpParse+1] 
                                    + lpDEVgry[lpParse+1] * lpDEVfzx[lpParse+1] 

                                )
                                + lpDEVfzz[lpParse+2];

        }

        /* Write stream data */
        lp_stream_write( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, LP_IMU_MODULE_IFETI__MOD, "fxx", lpDEVfxx, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, LP_IMU_MODULE_IFETI__MOD, "fxy", lpDEVfxy, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, LP_IMU_MODULE_IFETI__MOD, "fxz", lpDEVfxz, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, LP_IMU_MODULE_IFETI__MOD, "fyx", lpDEVfyx, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, LP_IMU_MODULE_IFETI__MOD, "fyy", lpDEVfyy, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, LP_IMU_MODULE_IFETI__MOD, "fyz", lpDEVfyz, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, LP_IMU_MODULE_IFETI__MOD, "fzx", lpDEVfzx, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, LP_IMU_MODULE_IFETI__MOD, "fzy", lpDEVfzy, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, LP_IMU_MODULE_IFETI__MOD, "fzz", lpDEVfzz, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_MODULE_IFETI__DEV, lpDevice.dvTag, LP_IMU_MODULE_IFETI__MOD, "syn", lpDEVsyn, sizeof( lp_Time_t ) * lpSize );

        /* Unallocate buffer memory */
        free( lpDEVgrx );
        free( lpDEVgry );
        free( lpDEVgrz );
        free( lpDEVfxx );
        free( lpDEVfxy );
        free( lpDEVfxz );
        free( lpDEVfyx );
        free( lpDEVfyy );
        free( lpDEVfyz );
        free( lpDEVfzx );
        free( lpDEVfzy );
        free( lpDEVfzz );
        free( lpDEVsyn );

        /* Return device descriptor */
        return( lpDevice );

    }


