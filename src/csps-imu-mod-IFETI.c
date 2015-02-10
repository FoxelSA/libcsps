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


/*
    Source - Includes
 */

    # include "csps-imu-mod-IFETI.h"

/*
    Source - IMU frame explicit time-integration
 */

    lp_Void_t lp_imu_mod_IFETI( 

        lp_Char_t const * const lpPath, 
        lp_IMU_t  const         lpIMU, 
        lp_Char_t const * const lpIMUmodGYR,
        lp_Char_t const * const lpIMUmodFRM

    ) {

        /* Parsing variables */
        lp_Size_t lpParse = lp_Size_s( 0 );

        /* Integration variables */
        lp_Real_t lpDelta = lp_Real_s( 0.0 );

        /* Files size */
        lp_Size_t lpSize = lp_Size_s( 0 );

        /* Initial condition range variables */
        lp_Size_t lpISRdwi = lp_Size_s( 0 );
        lp_Size_t lpISRupi = lp_Size_s( 0 );

        /* Stream memory variables */
        lp_Real_t * lpIMUgrx = NULL;
        lp_Real_t * lpIMUgry = NULL;
        lp_Real_t * lpIMUgrz = NULL;
        lp_Time_t * lpIMUgsn = NULL;
        lp_Real_t * lpIMUixx = NULL;
        lp_Real_t * lpIMUixy = NULL;
        lp_Real_t * lpIMUixz = NULL;
        lp_Real_t * lpIMUiyx = NULL;
        lp_Real_t * lpIMUiyy = NULL;
        lp_Real_t * lpIMUiyz = NULL;
        lp_Real_t * lpIMUizx = NULL;
        lp_Real_t * lpIMUizy = NULL;
        lp_Real_t * lpIMUizz = NULL;
        lp_Time_t * lpIMUisn = NULL;
        lp_Real_t * lpIMUfxx = NULL;
        lp_Real_t * lpIMUfxy = NULL;
        lp_Real_t * lpIMUfxz = NULL;
        lp_Real_t * lpIMUfyx = NULL;
        lp_Real_t * lpIMUfyy = NULL;
        lp_Real_t * lpIMUfyz = NULL;
        lp_Real_t * lpIMUfzx = NULL;
        lp_Real_t * lpIMUfzy = NULL;
        lp_Real_t * lpIMUfzz = NULL;

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, lpIMU.dvTag, lpIMUmodGYR );

        /* Read streams */
        lpIMUgrx = lp_stream_read( lpPath, lpIMU.dvTag, lpIMUmodGYR, LP_STREAM_CPN_GRX, sizeof( lp_Real_t ) * lpSize );
        lpIMUgry = lp_stream_read( lpPath, lpIMU.dvTag, lpIMUmodGYR, LP_STREAM_CPN_GRY, sizeof( lp_Real_t ) * lpSize );
        lpIMUgrz = lp_stream_read( lpPath, lpIMU.dvTag, lpIMUmodGYR, LP_STREAM_CPN_GRZ, sizeof( lp_Real_t ) * lpSize );
        lpIMUgsn = lp_stream_read( lpPath, lpIMU.dvTag, lpIMUmodGYR, LP_STREAM_CPN_SYN, sizeof( lp_Time_t ) * lpSize );

        /* Create streams */
        lpIMUfxx = ( lp_Real_t * ) lp_stream_create( sizeof( lp_Real_t ) * lpSize );
        lpIMUfxy = ( lp_Real_t * ) lp_stream_create( sizeof( lp_Real_t ) * lpSize );
        lpIMUfxz = ( lp_Real_t * ) lp_stream_create( sizeof( lp_Real_t ) * lpSize );
        lpIMUfyx = ( lp_Real_t * ) lp_stream_create( sizeof( lp_Real_t ) * lpSize );
        lpIMUfyy = ( lp_Real_t * ) lp_stream_create( sizeof( lp_Real_t ) * lpSize );
        lpIMUfyz = ( lp_Real_t * ) lp_stream_create( sizeof( lp_Real_t ) * lpSize );
        lpIMUfzx = ( lp_Real_t * ) lp_stream_create( sizeof( lp_Real_t ) * lpSize );
        lpIMUfzy = ( lp_Real_t * ) lp_stream_create( sizeof( lp_Real_t ) * lpSize );
        lpIMUfzz = ( lp_Real_t * ) lp_stream_create( sizeof( lp_Real_t ) * lpSize );

        /* Read streams */
        lpIMUixx = lp_stream_read( lpPath, lpIMU.dvTag, lpIMUmodFRM, LP_STREAM_CPN_IXX, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUixy = lp_stream_read( lpPath, lpIMU.dvTag, lpIMUmodFRM, LP_STREAM_CPN_IXY, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUixz = lp_stream_read( lpPath, lpIMU.dvTag, lpIMUmodFRM, LP_STREAM_CPN_IXZ, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUiyx = lp_stream_read( lpPath, lpIMU.dvTag, lpIMUmodFRM, LP_STREAM_CPN_IYX, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUiyy = lp_stream_read( lpPath, lpIMU.dvTag, lpIMUmodFRM, LP_STREAM_CPN_IYY, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUiyz = lp_stream_read( lpPath, lpIMU.dvTag, lpIMUmodFRM, LP_STREAM_CPN_IYZ, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUizx = lp_stream_read( lpPath, lpIMU.dvTag, lpIMUmodFRM, LP_STREAM_CPN_IZX, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUizy = lp_stream_read( lpPath, lpIMU.dvTag, lpIMUmodFRM, LP_STREAM_CPN_IZY, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUizz = lp_stream_read( lpPath, lpIMU.dvTag, lpIMUmodFRM, LP_STREAM_CPN_IZZ, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUisn = lp_stream_read( lpPath, lpIMU.dvTag, lpIMUmodFRM, LP_STREAM_CPN_SYN, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );

        /* Detect initial condition time range - Down boundary */
        if ( lp_timestamp_ge( lpIMUgsn[0], lpIMUisn[0] ) == LP_TRUE ) {

            /* Clamp down boundary */
            lpISRdwi = 0;

        } else if ( lp_timestamp_ge( lpIMUisn[0], lpIMUgsn[lpSize-1] ) == LP_TRUE ) {

            /* Clamp down boundary */
            lpISRdwi = lpSize - lp_Size_s( 1 );

        } else {

            /* Dichotomous search of timestamp */
            lpISRdwi = lp_timestamp_search( lpIMUisn[0], lpIMUgsn, lpSize );

        }

        /* Detect initial condition time range - Down boundary */
        if ( lp_timestamp_ge( lpIMUgsn[0], lpIMUisn[1] ) == LP_TRUE ) {

            /* Clamp down boundary */
            lpISRupi = 0;

        } else if ( lp_timestamp_ge( lpIMUisn[1], lpIMUgsn[lpSize-1] ) == LP_TRUE ) {

            /* Clamp down boundary */
            lpISRupi = lpSize - lp_Size_s( 1 );

        } else {

            /* Dichotomous search of timestamp */
            lpISRupi = lp_timestamp_search( lpIMUisn[1], lpIMUgsn, lpSize );

        }

        /* Singular initial condition management */
        if ( lpISRdwi == lpISRupi ) {

            /* Check boundary proximity */
            if ( lpISRupi == ( lpSize - lp_Size_s( 1 ) ) ) {

                /* Update initial condition range definition */
                lpISRdwi--;

            } else {

                /* Update initial condition range definition */
                lpISRupi++;

            }

        }

        /* Setting initial conditions */
        for ( lpParse = lpISRdwi ; lpParse <= lpISRupi ; lpParse ++ ) {

            /* Assign initial condition on frame unit vectors */
            lpIMUfxx[lpParse] = lpIMUixx[0];
            lpIMUfxy[lpParse] = lpIMUixy[0];
            lpIMUfxz[lpParse] = lpIMUixz[0];
            lpIMUfyx[lpParse] = lpIMUiyx[0];
            lpIMUfyy[lpParse] = lpIMUiyy[0];
            lpIMUfyz[lpParse] = lpIMUiyz[0];
            lpIMUfzx[lpParse] = lpIMUizx[0];
            lpIMUfzy[lpParse] = lpIMUizy[0];
            lpIMUfzz[lpParse] = lpIMUizz[0];

        }

        /* Frame explicit time-integration - Prograde segment */
        for ( lpParse = lpISRupi + lp_Size_s( 1 ) ; lpParse < lpSize ; lpParse ++ ) {

            /* Compute current time step */
            lpDelta = lp_timestamp_float( lp_timestamp_diff( lpIMUgsn[lpParse], lpIMUgsn[lpParse-1] ) );

            /* Integration - Advance frame x-vector - x-component */
            lpIMUfxx[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    + lpIMUgry[lpParse-1] * lpIMUfxz[lpParse-1] 
                                    - lpIMUgrz[lpParse-1] * lpIMUfxy[lpParse-1] 

                                ) + lpIMUfxx[lpParse-2];

            /* Integration - Advance frame x-vector - y-component */
            lpIMUfxy[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    + lpIMUgrz[lpParse-1] * lpIMUfxx[lpParse-1] 
                                    - lpIMUgrx[lpParse-1] * lpIMUfxz[lpParse-1] 

                                ) + lpIMUfxy[lpParse-2];

            /* Integration - Advance frame x-vector - z-component */
            lpIMUfxz[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    + lpIMUgrx[lpParse-1] * lpIMUfxy[lpParse-1] 
                                    - lpIMUgry[lpParse-1] * lpIMUfxx[lpParse-1] 

                                ) + lpIMUfxz[lpParse-2];

            /* Integration - Advance frame y-vector - x-component */
            lpIMUfyx[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    + lpIMUgry[lpParse-1] * lpIMUfyz[lpParse-1] 
                                    - lpIMUgrz[lpParse-1] * lpIMUfyy[lpParse-1] 

                                ) + lpIMUfyx[lpParse-2];

            /* Integration - Advance frame y-vector - y-component */
            lpIMUfyy[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    + lpIMUgrz[lpParse-1] * lpIMUfyx[lpParse-1] 
                                    - lpIMUgrx[lpParse-1] * lpIMUfyz[lpParse-1] 

                                ) + lpIMUfyy[lpParse-2];

            /* Integration - Advance frame y-vector - z-component */
            lpIMUfyz[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    + lpIMUgrx[lpParse-1] * lpIMUfyy[lpParse-1] 
                                    - lpIMUgry[lpParse-1] * lpIMUfyx[lpParse-1] 

                                ) + lpIMUfyz[lpParse-2];

            /* Integration - Advance frame z-vector - x-component */
            lpIMUfzx[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    + lpIMUgry[lpParse-1] * lpIMUfzz[lpParse-1] 
                                    - lpIMUgrz[lpParse-1] * lpIMUfzy[lpParse-1] 

                                ) + lpIMUfzx[lpParse-2];

            /* Integration - Advance frame z-vector - y-component */
            lpIMUfzy[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    + lpIMUgrz[lpParse-1] * lpIMUfzx[lpParse-1] 
                                    - lpIMUgrx[lpParse-1] * lpIMUfzz[lpParse-1] 

                                ) + lpIMUfzy[lpParse-2];

            /* Integration - Advance frame z-vector - z-component */
            lpIMUfzz[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    + lpIMUgrx[lpParse-1] * lpIMUfzy[lpParse-1] 
                                    - lpIMUgry[lpParse-1] * lpIMUfzx[lpParse-1] 

                                ) + lpIMUfzz[lpParse-2];

        }

        /* Frame explicit time-integration - Retrograde segment */
        for ( lpParse = lpISRdwi - lp_Size_s( 1 ) ; lpParse >= 0 ; lpParse -- ) {

            /* Compute current time step */
            lpDelta = lp_timestamp_float( lp_timestamp_diff( lpIMUgsn[lpParse+1], lpIMUgsn[lpParse] ) );

            /* Integration - Step back frame x-vector - x-component */
            lpIMUfxx[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    - lpIMUgry[lpParse+1] * lpIMUfxz[lpParse+1] 
                                    + lpIMUgrz[lpParse+1] * lpIMUfxy[lpParse+1] 

                                ) + lpIMUfxx[lpParse+2];

            /* Integration - Step back frame x-vector - y-component */
            lpIMUfxy[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    - lpIMUgrz[lpParse+1] * lpIMUfxx[lpParse+1] 
                                    + lpIMUgrx[lpParse+1] * lpIMUfxz[lpParse+1] 

                                ) + lpIMUfxy[lpParse+2];

            /* Integration - Step back frame x-vector - z-component */
            lpIMUfxz[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    - lpIMUgrx[lpParse+1] * lpIMUfxy[lpParse+1] 
                                    + lpIMUgry[lpParse+1] * lpIMUfxx[lpParse+1] 

                                ) + lpIMUfxz[lpParse+2];

            /* Integration - Step back frame x-vector - x-component */
            lpIMUfyx[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    - lpIMUgry[lpParse+1] * lpIMUfyz[lpParse+1] 
                                    + lpIMUgrz[lpParse+1] * lpIMUfyy[lpParse+1] 

                                ) + lpIMUfyx[lpParse+2];

            /* Integration - Step back frame x-vector - y-component */
            lpIMUfyy[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    - lpIMUgrz[lpParse+1] * lpIMUfyx[lpParse+1] 
                                    + lpIMUgrx[lpParse+1] * lpIMUfyz[lpParse+1] 

                                ) + lpIMUfyy[lpParse+2];

            /* Integration - Step back frame x-vector - z-component */
            lpIMUfyz[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    - lpIMUgrx[lpParse+1] * lpIMUfyy[lpParse+1] 
                                    + lpIMUgry[lpParse+1] * lpIMUfyx[lpParse+1] 

                                ) + lpIMUfyz[lpParse+2];

            /* Integration - Step back frame z-vector - x-component */
            lpIMUfzx[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    - lpIMUgry[lpParse+1] * lpIMUfzz[lpParse+1] 
                                    + lpIMUgrz[lpParse+1] * lpIMUfzy[lpParse+1] 

                                ) + lpIMUfzx[lpParse+2];

            /* Integration - Step back frame z-vector - y-component */
            lpIMUfzy[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    - lpIMUgrz[lpParse+1] * lpIMUfzx[lpParse+1] 
                                    + lpIMUgrx[lpParse+1] * lpIMUfzz[lpParse+1] 

                                ) + lpIMUfzy[lpParse+2];

            /* Integration - Step back frame z-vector - z-component */
            lpIMUfzz[lpParse] = lp_Real_s( 2.0 ) * lpDelta * ( 

                                    - lpIMUgrx[lpParse+1] * lpIMUfzy[lpParse+1] 
                                    + lpIMUgry[lpParse+1] * lpIMUfzx[lpParse+1] 

                                ) + lpIMUfzz[lpParse+2];

        }

        /* Write streams */
        lp_stream_write( lpPath, lpIMU.dvTag, LP_IMU_IFETI_MOD, LP_STREAM_CPN_FXX, lpIMUfxx, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, lpIMU.dvTag, LP_IMU_IFETI_MOD, LP_STREAM_CPN_FXY, lpIMUfxy, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, lpIMU.dvTag, LP_IMU_IFETI_MOD, LP_STREAM_CPN_FXZ, lpIMUfxz, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, lpIMU.dvTag, LP_IMU_IFETI_MOD, LP_STREAM_CPN_FYX, lpIMUfyx, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, lpIMU.dvTag, LP_IMU_IFETI_MOD, LP_STREAM_CPN_FYY, lpIMUfyy, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, lpIMU.dvTag, LP_IMU_IFETI_MOD, LP_STREAM_CPN_FYZ, lpIMUfyz, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, lpIMU.dvTag, LP_IMU_IFETI_MOD, LP_STREAM_CPN_FZX, lpIMUfzx, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, lpIMU.dvTag, LP_IMU_IFETI_MOD, LP_STREAM_CPN_FZY, lpIMUfzy, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, lpIMU.dvTag, LP_IMU_IFETI_MOD, LP_STREAM_CPN_FZZ, lpIMUfzz, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, lpIMU.dvTag, LP_IMU_IFETI_MOD, LP_STREAM_CPN_SYN, lpIMUgsn, sizeof( lp_Time_t ) * lpSize );

        /* Unallocate streams */
        lpIMUixx = lp_stream_delete( lpIMUixx );
        lpIMUixy = lp_stream_delete( lpIMUixy );
        lpIMUixz = lp_stream_delete( lpIMUixz );
        lpIMUiyx = lp_stream_delete( lpIMUiyx );
        lpIMUiyy = lp_stream_delete( lpIMUiyy );
        lpIMUiyz = lp_stream_delete( lpIMUiyz );
        lpIMUizx = lp_stream_delete( lpIMUizx );
        lpIMUizy = lp_stream_delete( lpIMUizy );
        lpIMUizz = lp_stream_delete( lpIMUizz );
        lpIMUisn = lp_stream_delete( lpIMUisn );
        lpIMUgrx = lp_stream_delete( lpIMUgrx );
        lpIMUgry = lp_stream_delete( lpIMUgry );
        lpIMUgrz = lp_stream_delete( lpIMUgrz );
        lpIMUfxx = lp_stream_delete( lpIMUfxx );
        lpIMUfxy = lp_stream_delete( lpIMUfxy );
        lpIMUfxz = lp_stream_delete( lpIMUfxz );
        lpIMUfyx = lp_stream_delete( lpIMUfyx );
        lpIMUfyy = lp_stream_delete( lpIMUfyy );
        lpIMUfyz = lp_stream_delete( lpIMUfyz );
        lpIMUfzx = lp_stream_delete( lpIMUfzx );
        lpIMUfzy = lp_stream_delete( lpIMUfzy );
        lpIMUfzz = lp_stream_delete( lpIMUfzz );
        lpIMUgsn = lp_stream_delete( lpIMUgsn );

    }


