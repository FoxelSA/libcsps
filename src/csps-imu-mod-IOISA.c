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

    # include "csps-imu-mod-IOISA.h"

/*
    Source - IMU earth self-alignment
 */

    lp_Void_t lp_imu_mod_IOISA( 

        const lp_Char_t * const lpPath, 
        lp_IMU                  lpIMU,
        lp_GPS                  lpGPS,
        const lp_Char_t * const lpIMUmodISD,
        const lp_Char_t * const lpIMUmodTAG,
        const lp_Char_t * const lpIMUmodGEO 

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
        lp_Real_t lpACClat = lp_Real_s( 0.0 );
        lp_Real_t lpACCacn = lp_Real_s( 0.0 );
        lp_Real_t lpACCgrn = lp_Real_s( 0.0 );
        lp_Real_t lpACCabs = lp_Real_s( 0.0 );

        /* Stream memory variables */
        lp_Real_t * lpIMUacx = LP_NULL;
        lp_Real_t * lpIMUacy = LP_NULL;
        lp_Real_t * lpIMUacz = LP_NULL;
        lp_Real_t * lpIMUgrx = LP_NULL;
        lp_Real_t * lpIMUgry = LP_NULL;
        lp_Real_t * lpIMUgrz = LP_NULL;
        lp_Real_t * lpIMUixx = LP_NULL;
        lp_Real_t * lpIMUixy = LP_NULL;
        lp_Real_t * lpIMUixz = LP_NULL;
        lp_Real_t * lpIMUiyx = LP_NULL;
        lp_Real_t * lpIMUiyy = LP_NULL;
        lp_Real_t * lpIMUiyz = LP_NULL;
        lp_Real_t * lpIMUizx = LP_NULL;
        lp_Real_t * lpIMUizy = LP_NULL;
        lp_Real_t * lpIMUizz = LP_NULL;
        lp_Time_t * lpIMUsyn = LP_NULL;
        lp_Time_t * lpIMUtag = LP_NULL;
        lp_Real_t * lpGPSlat = LP_NULL;
        lp_Time_t * lpGPSsyn = LP_NULL;

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodISD );

        /* Read streams */
        lpIMUtag = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodTAG, LP_STREAM_CPN_TAG, sizeof( lp_Time_t ) * lpSize );

        /* Extract inertial still range boundaries */
        lpISRdwt = lpIMUtag[0];
        lpISRupt = lpIMUtag[1];

        /* Unallocate streams */
        lpIMUtag = lp_stream_delete( lpIMUtag );

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodISD );

        /* Read streams */
        lpIMUacx = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodISD, LP_STREAM_CPN_ACX, sizeof( lp_Real_t ) * lpSize );
        lpIMUacy = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodISD, LP_STREAM_CPN_ACY, sizeof( lp_Real_t ) * lpSize );
        lpIMUacz = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodISD, LP_STREAM_CPN_ACZ, sizeof( lp_Real_t ) * lpSize );
        lpIMUgrx = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodISD, LP_STREAM_CPN_GRX, sizeof( lp_Real_t ) * lpSize );
        lpIMUgry = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodISD, LP_STREAM_CPN_GRY, sizeof( lp_Real_t ) * lpSize );
        lpIMUgrz = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodISD, LP_STREAM_CPN_GRZ, sizeof( lp_Real_t ) * lpSize );
        lpIMUsyn = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmodISD, LP_STREAM_CPN_SYN, sizeof( lp_Time_t ) * lpSize );

        /* Obtain still range corresponding index */
        lpISRdwi = lp_timestamp_index( lpISRdwt, lpIMUsyn, lpSize );
        lpISRupi = lp_timestamp_index( lpISRupt, lpIMUsyn, lpSize );

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

        /* Gyroscope average computation */
        lpACCgrx /= ( lpISRupi - lpISRdwi + lp_Size_s( 1 ) );
        lpACCgry /= ( lpISRupi - lpISRdwi + lp_Size_s( 1 ) );
        lpACCgrz /= ( lpISRupi - lpISRdwi + lp_Size_s( 1 ) );

        /* Compute angular velocity norm */
        lpACCgrn = sqrt( lpACCgrx * lpACCgrx + lpACCgry * lpACCgry + lpACCgrz * lpACCgrz );

        /* Unallocate streams */
        lpIMUacx = lp_stream_delete( lpIMUacx );
        lpIMUacy = lp_stream_delete( lpIMUacy );
        lpIMUacz = lp_stream_delete( lpIMUacz );
        lpIMUgrx = lp_stream_delete( lpIMUgrx );
        lpIMUgry = lp_stream_delete( lpIMUgry );
        lpIMUgrz = lp_stream_delete( lpIMUgrz );
        lpIMUsyn = lp_stream_delete( lpIMUsyn );

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, lpGPS.dvType, lpGPS.dvTag, lpIMUmodGEO );

        /* Read streams */
        lpGPSlat = lp_stream_read( lpPath, lpGPS.dvType, lpGPS.dvTag, lpIMUmodGEO, LP_STREAM_CPN_LAT, sizeof( lp_Real_t ) * lpSize );
        lpGPSsyn = lp_stream_read( lpPath, lpGPS.dvType, lpGPS.dvTag, lpIMUmodGEO, LP_STREAM_CPN_SYN, sizeof( lp_Time_t ) * lpSize );

        /* Obtain still range corresponding index */
        lpISRdwi = lp_timestamp_index( lpISRdwt, lpGPSsyn, lpSize );
        lpISRupi = lp_timestamp_index( lpISRupt, lpGPSsyn, lpSize );

        /* Quantities accumulation */
        for ( lpParse = lpISRdwi ; lpParse <= lpISRupi ; lpParse ++ ) {

            /* Latitude signal accumulation */
            lpACClat += lpGPSlat[lpParse];

        }

        /* Latitude average computation */
        lpACClat /= ( lpISRupi - lpISRdwi + lp_Size_s( 1 ) );

        /* Unallocate streams */
        lpGPSlat = lp_stream_delete( lpGPSlat );
        lpGPSsyn = lp_stream_delete( lpGPSsyn );

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
        lpIMUsyn = lp_stream_create( sizeof( lp_Time_t ) * lp_Size_s( 2 ) );

        /* Frame z-vector gravity alignment */
        lpIMUizx[0] = - lpACCacx / lpACCacn;
        lpIMUizy[0] = - lpACCacy / lpACCacn;
        lpIMUizz[0] = - lpACCacz / lpACCacn;

        /* Frame x-vector coarse heading alignment */
        lpIMUixx[0] = + ( tan( lpACClat ) / lpACCacn ) * lpACCacx - ( lp_Real_s( 1.0 ) / ( lpACCgrn * cos( lpACClat ) ) ) * lpACCgrx;
        lpIMUixy[0] = + ( tan( lpACClat ) / lpACCacn ) * lpACCacy - ( lp_Real_s( 1.0 ) / ( lpACCgrn * cos( lpACClat ) ) ) * lpACCgry;
        lpIMUixz[0] = + ( tan( lpACClat ) / lpACCacn ) * lpACCacz - ( lp_Real_s( 1.0 ) / ( lpACCgrn * cos( lpACClat ) ) ) * lpACCgrz;

        /* Frame y-vector computation */
        lpIMUiyx[0] = + lpIMUizy[0] * lpIMUixz[0] - lpIMUizz[0] * lpIMUixy[0];
        lpIMUiyy[0] = + lpIMUizz[0] * lpIMUixx[0] - lpIMUizx[0] * lpIMUixz[0];
        lpIMUiyz[0] = + lpIMUizx[0] * lpIMUixy[0] - lpIMUizy[0] * lpIMUixx[0];

        /* Compute y-vector norm */
        lpACCabs = sqrt( lpIMUiyx[0] * lpIMUiyx[0] + lpIMUiyy[0] * lpIMUiyy[0] + lpIMUiyz[0] * lpIMUiyz[0] );

        /* Frame y-vector normalization */
        lpIMUiyx[0] /= lpACCabs;
        lpIMUiyy[0] /= lpACCabs;
        lpIMUiyz[0] /= lpACCabs;

        /* Frame x-vector orthogonal alignment */
        lpIMUixx[0] = lpIMUiyy[0] * lpIMUizz[0] - lpIMUiyz[0] * lpIMUizy[0];
        lpIMUixy[0] = lpIMUiyz[0] * lpIMUizx[0] - lpIMUiyx[0] * lpIMUizz[0];
        lpIMUixz[0] = lpIMUiyx[0] * lpIMUizy[0] - lpIMUiyy[0] * lpIMUizx[0];

        /* Assign second component */
        lpIMUixx[1] = lpIMUixx[0];
        lpIMUixy[1] = lpIMUixy[0];
        lpIMUixz[1] = lpIMUixz[0];
        lpIMUiyx[1] = lpIMUiyx[0];
        lpIMUiyy[1] = lpIMUiyy[0];
        lpIMUiyz[1] = lpIMUiyz[0];
        lpIMUizx[1] = lpIMUizx[0];
        lpIMUizy[1] = lpIMUizy[0];
        lpIMUizz[1] = lpIMUizz[0];

        /* Assign initial condition timestamp */
        lpIMUsyn[0] = lpISRdwt;
        lpIMUsyn[1] = lpISRupt;

        /* Write streams */
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IOISA_MOD, LP_STREAM_CPN_IXX, lpIMUixx, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IOISA_MOD, LP_STREAM_CPN_IXY, lpIMUixy, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IOISA_MOD, LP_STREAM_CPN_IXZ, lpIMUixz, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IOISA_MOD, LP_STREAM_CPN_IYX, lpIMUiyx, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IOISA_MOD, LP_STREAM_CPN_IYY, lpIMUiyy, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IOISA_MOD, LP_STREAM_CPN_IYZ, lpIMUiyz, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IOISA_MOD, LP_STREAM_CPN_IZX, lpIMUizx, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IOISA_MOD, LP_STREAM_CPN_IZY, lpIMUizy, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IOISA_MOD, LP_STREAM_CPN_IZZ, lpIMUizz, sizeof( lp_Real_t ) * lp_Size_s( 2 ) );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_IOISA_MOD, LP_STREAM_CPN_SYN, lpIMUsyn, sizeof( lp_Time_t ) * lp_Size_s( 2 ) );

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
        lpIMUsyn = lp_stream_delete( lpIMUsyn );

    }

