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

    # include "csps-imu-mod-IOISA.h"

/*
    Source - IMU earth self-alignment
 */

    lp_Void_t lp_imu_mod_IOISA( 

        lp_Char_t const * const lpPath, 
        lp_IMU_t  const         lpIMU,
        lp_Char_t const * const lpIMUmodISD,
        lp_Char_t const * const lpIMUmodTAG

    ) {

        /* Parsing variables */
        lp_Size_t lpParse = lp_Size_s( 0 );

        /* Stream size variables */
        lp_Size_t lpSize = lp_Size_s( 0 );

        /* Inertial still range variables */
        lp_Time_t lpISRdwt = lp_Time_s( 0 );
        lp_Time_t lpISRupt = lp_Time_s( 0 );
        lp_Size_t lpISRdwi = lp_Size_s( 0 );
        lp_Size_t lpISRupi = lp_Size_s( 0 );

        /* Accumulator variables */
        lp_Real_t lpACCacx = lp_Real_s( 0.0 );
        lp_Real_t lpACCacy = lp_Real_s( 0.0 );
        lp_Real_t lpACCacz = lp_Real_s( 0.0 );
        lp_Real_t lpACCgrx = lp_Real_s( 0.0 );
        lp_Real_t lpACCgry = lp_Real_s( 0.0 );
        lp_Real_t lpACCgrz = lp_Real_s( 0.0 );
        lp_Real_t lpACCacn = lp_Real_s( 0.0 );
        lp_Real_t lpACCgrn = lp_Real_s( 0.0 );

        /* Stream memory variables */
        lp_Real_t * lpIMUacx = NULL;
        lp_Real_t * lpIMUacy = NULL;
        lp_Real_t * lpIMUacz = NULL;
        lp_Real_t * lpIMUgrx = NULL;
        lp_Real_t * lpIMUgry = NULL;
        lp_Real_t * lpIMUgrz = NULL;
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
        lp_Time_t * lpIMUtag = NULL;
        lp_Time_t * lpIMUrsn = NULL;

        /* Matrix variables */
        lp_Real_t lpMatrix[3][3] = { 

            { lp_Real_s( 0.0 ), lp_Real_s( 0.0 ), lp_Real_s( 0.0 ) },
            { lp_Real_s( 0.0 ), lp_Real_s( 0.0 ), lp_Real_s( 0.0 ) },
            { lp_Real_s( 0.0 ), lp_Real_s( 0.0 ), lp_Real_s( 0.0 ) }

        };

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, lpIMU.dvTag, lpIMUmodISD );

        /* Read streams */
        lpIMUtag = lp_stream_read( lpPath, lpIMU.dvTag, lpIMUmodTAG, LP_STREAM_CPN_TAG, sizeof( lp_Time_t ) * lpSize );
        lpIMUrsn = lp_stream_read( lpPath, lpIMU.dvTag, lpIMUmodTAG, LP_STREAM_CPN_SYN, sizeof( lp_Time_t ) * lpSize );

        /* Extract inertial still range boundaries */
        lpISRdwt = lpIMUrsn[0];
        lpISRupt = lpIMUtag[0];

        /* Unallocate streams */
        lpIMUtag = lp_stream_delete( lpIMUtag );
        lpIMUrsn = lp_stream_delete( lpIMUrsn );

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, lpIMU.dvTag, lpIMUmodISD );

        /* Read streams */
        lpIMUacx = lp_stream_read( lpPath, lpIMU.dvTag, lpIMUmodISD, LP_STREAM_CPN_ACX, sizeof( lp_Real_t ) * lpSize );
        lpIMUacy = lp_stream_read( lpPath, lpIMU.dvTag, lpIMUmodISD, LP_STREAM_CPN_ACY, sizeof( lp_Real_t ) * lpSize );
        lpIMUacz = lp_stream_read( lpPath, lpIMU.dvTag, lpIMUmodISD, LP_STREAM_CPN_ACZ, sizeof( lp_Real_t ) * lpSize );
        lpIMUgrx = lp_stream_read( lpPath, lpIMU.dvTag, lpIMUmodISD, LP_STREAM_CPN_GRX, sizeof( lp_Real_t ) * lpSize );
        lpIMUgry = lp_stream_read( lpPath, lpIMU.dvTag, lpIMUmodISD, LP_STREAM_CPN_GRY, sizeof( lp_Real_t ) * lpSize );
        lpIMUgrz = lp_stream_read( lpPath, lpIMU.dvTag, lpIMUmodISD, LP_STREAM_CPN_GRZ, sizeof( lp_Real_t ) * lpSize );
        lpIMUisn = lp_stream_read( lpPath, lpIMU.dvTag, lpIMUmodISD, LP_STREAM_CPN_SYN, sizeof( lp_Time_t ) * lpSize );

        /* Obtain still range corresponding index */
        lpISRdwi = lp_timestamp_index( lpISRdwt, lpIMUisn, lpSize );
        lpISRupi = lp_timestamp_index( lpISRupt, lpIMUisn, lpSize );

        /* Quantities accumulation */
        for ( lpParse = lpISRdwi ; lpParse <= lpISRupi ; lpParse ++ ) {

            /* Accelerometer signals accumulation */
            lpACCacx += lpIMUacx[lpParse];
            lpACCacy += lpIMUacy[lpParse];
            lpACCacz += lpIMUacz[lpParse];

            /* Gyroscope signals accumulation */
            lpACCgrx += lpIMUgrx[lpParse];
            lpACCgry += lpIMUgry[lpParse];
            lpACCgrz += lpIMUgrz[lpParse];

        }

        /* Accelerometer average computation */
        lpACCacx /= ( lpISRupi - lpISRdwi + lp_Size_s( 1 ) );
        lpACCacy /= ( lpISRupi - lpISRdwi + lp_Size_s( 1 ) );
        lpACCacz /= ( lpISRupi - lpISRdwi + lp_Size_s( 1 ) );

        /* Compute acceleration norm */
        lpACCacn = sqrt( lpACCacx * lpACCacx + lpACCacy * lpACCacy + lpACCacz * lpACCacz );

        /* Normalize mean acceleration */
        lpACCacx /= lpACCacn;
        lpACCacy /= lpACCacn;
        lpACCacz /= lpACCacn;

        /* Gyroscope average computation */
        lpACCgrx /= ( lpISRupi - lpISRdwi + lp_Size_s( 1 ) );
        lpACCgry /= ( lpISRupi - lpISRdwi + lp_Size_s( 1 ) );
        lpACCgrz /= ( lpISRupi - lpISRdwi + lp_Size_s( 1 ) );

        /* Compute angular velocity norm */
        lpACCgrn = sqrt( lpACCgrx * lpACCgrx + lpACCgry * lpACCgry + lpACCgrz * lpACCgrz );

        /* Normalize mean angular velocity */
        lpACCgrx /= lpACCgrn;
        lpACCgry /= lpACCgrn;
        lpACCgrz /= lpACCgrn;

        /* Unallocate streams */
        lpIMUacx = lp_stream_delete( lpIMUacx );
        lpIMUacy = lp_stream_delete( lpIMUacy );
        lpIMUacz = lp_stream_delete( lpIMUacz );
        lpIMUgrx = lp_stream_delete( lpIMUgrx );
        lpIMUgry = lp_stream_delete( lpIMUgry );
        lpIMUgrz = lp_stream_delete( lpIMUgrz );
        lpIMUisn = lp_stream_delete( lpIMUisn );

        /* Create streams */
        lpIMUixx = lp_stream_create( sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUixy = lp_stream_create( sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUixz = lp_stream_create( sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUiyx = lp_stream_create( sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUiyy = lp_stream_create( sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUiyz = lp_stream_create( sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUizx = lp_stream_create( sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUizy = lp_stream_create( sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUizz = lp_stream_create( sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lpIMUisn = lp_stream_create( sizeof( lp_Time_t ) * lp_Size_s( 2 ) );

        /* Compute rotation matrix - Rotate inertial frame z-vector on counter-gravity mean */
        lp_rotation_matrix_2vR3( lp_Real_s( 0.0 ), lp_Real_s( 0.0 ), lp_Real_s( 1.0 ), lpACCacx, lpACCacy, lpACCacz, lpMatrix );

        /* Counter-gravity aligned frame */
        lpIMUixx[0] = lpMatrix[0][0]; lpIMUixy[0] = lpMatrix[1][0]; lpIMUixz[0] = lpMatrix[2][0];
        lpIMUiyx[0] = lpMatrix[0][1]; lpIMUiyy[0] = lpMatrix[1][1]; lpIMUiyz[0] = lpMatrix[2][1];
        lpIMUizx[0] = lpMatrix[0][2]; lpIMUizy[0] = lpMatrix[1][2]; lpIMUizz[0] = lpMatrix[2][2];

        /* Compute gyroscope mean in counter-gravity aligned frame */
        lp_rotation_iR3( lpMatrix, & ( lpACCgrx ), & ( lpACCgry ), & ( lpACCgrz ) );

        /* Compute rotation matrix around z-vector of counter-gravity aligned frame */
        lp_rotation_matrix_vaR3( lpIMUizx[0], lpIMUizy[0], lpIMUizz[0], LP_ATN( lpACCgrx, lpACCgry ) - LP_PI * 0.5, lpMatrix );

        /* Rotation around z-axis of counter-gravity aligned frame */
        lp_rotation_mR3( lpMatrix, & ( lpIMUixx[0] ), & ( lpIMUixy[0] ), & ( lpIMUixz[0] ) );
        lp_rotation_mR3( lpMatrix, & ( lpIMUiyx[0] ), & ( lpIMUiyy[0] ), & ( lpIMUiyz[0] ) );
        lp_rotation_mR3( lpMatrix, & ( lpIMUizx[0] ), & ( lpIMUizy[0] ), & ( lpIMUizz[0] ) );

        /* Assign second components */
        lpIMUixx[1] = lpIMUixx[0];
        lpIMUixy[1] = lpIMUixy[0];
        lpIMUixz[1] = lpIMUixz[0];
        lpIMUiyx[1] = lpIMUiyx[0];
        lpIMUiyy[1] = lpIMUiyy[0];
        lpIMUiyz[1] = lpIMUiyz[0];
        lpIMUizx[1] = lpIMUizx[0];
        lpIMUizy[1] = lpIMUizy[0];
        lpIMUizz[1] = lpIMUizz[0];

        /* Assign initial condition timestamps */
        lpIMUisn[0] = lpISRdwt;
        lpIMUisn[1] = lpISRupt;

        /* Write streams */
        lp_stream_write( lpPath, lpIMU.dvTag, LP_IMU_IOISA_MOD, LP_STREAM_CPN_IXX, lpIMUixx, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvTag, LP_IMU_IOISA_MOD, LP_STREAM_CPN_IXY, lpIMUixy, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvTag, LP_IMU_IOISA_MOD, LP_STREAM_CPN_IXZ, lpIMUixz, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvTag, LP_IMU_IOISA_MOD, LP_STREAM_CPN_IYX, lpIMUiyx, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvTag, LP_IMU_IOISA_MOD, LP_STREAM_CPN_IYY, lpIMUiyy, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvTag, LP_IMU_IOISA_MOD, LP_STREAM_CPN_IYZ, lpIMUiyz, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvTag, LP_IMU_IOISA_MOD, LP_STREAM_CPN_IZX, lpIMUizx, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvTag, LP_IMU_IOISA_MOD, LP_STREAM_CPN_IZY, lpIMUizy, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvTag, LP_IMU_IOISA_MOD, LP_STREAM_CPN_IZZ, lpIMUizz, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvTag, LP_IMU_IOISA_MOD, LP_STREAM_CPN_SYN, lpIMUisn, sizeof( lp_Time_t ) * lp_Size_s( 2 ) );

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

    }

