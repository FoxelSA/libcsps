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

    # include "csps-imu-mod-ISRAD.h"

/*
    Source - IMU Inertial still range automatic detection
 */

    lp_IMU lp_imu_mod_ISRAD( 

        const lp_Char_t * const lpPath, 
        lp_IMU                  lpIMU, 
        const lp_Char_t * const lpIMUmod 

    ) {

        /* Parsing variables */
        lp_Size_t lpParse = lp_Size_s( 0 );
        lp_Size_t lpIndex = lp_Size_s( 2 );

        /* Stream size variables */
        lp_Size_t lpSize = lp_Size_s( 0 );

        /* Still range description variables */
        lp_Size_t lpBound = lp_Size_s( 0 );
        lp_Size_t lpWidth = lp_Size_s( 0 );

        /* Accumulator variables */
        lp_Real_t lpAccumGRX = lp_Real_s( 0.0 );
        lp_Real_t lpAccumGRY = lp_Real_s( 0.0 );
        lp_Real_t lpAccumGRZ = lp_Real_s( 0.0 );
        lp_Real_t lpAccumACX = lp_Real_s( 0.0 );
        lp_Real_t lpAccumACY = lp_Real_s( 0.0 );
        lp_Real_t lpAccumACZ = lp_Real_s( 0.0 );

        /* Accumulator index variables */
        lp_Size_t lpAccumIDX = lp_Size_s( 0 );

        /* Stream memory variables */
        lp_Real_t * lpIMUgrx = LP_NULL;
        lp_Real_t * lpIMUgry = LP_NULL;
        lp_Real_t * lpIMUgrz = LP_NULL;
        lp_Real_t * lpIMUacx = LP_NULL;
        lp_Real_t * lpIMUacy = LP_NULL;
        lp_Real_t * lpIMUacz = LP_NULL;
        lp_Time_t * lpIMUtag = LP_NULL;
        lp_Time_t * lpIMUsyn = LP_NULL;

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod );

        /* Read streams */
        lpIMUgrx = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod, LP_STREAM_CPN_GRX, sizeof( lp_Real_t ) * lpSize );
        lpIMUgry = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod, LP_STREAM_CPN_GRY, sizeof( lp_Real_t ) * lpSize );
        lpIMUgrz = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod, LP_STREAM_CPN_GRZ, sizeof( lp_Real_t ) * lpSize );
        lpIMUacx = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod, LP_STREAM_CPN_ACX, sizeof( lp_Real_t ) * lpSize );
        lpIMUacy = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod, LP_STREAM_CPN_ACY, sizeof( lp_Real_t ) * lpSize );
        lpIMUacz = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod, LP_STREAM_CPN_ACZ, sizeof( lp_Real_t ) * lpSize );
        lpIMUsyn = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod, LP_STREAM_CPN_SYN, sizeof( lp_Time_t ) * lpSize );

        /* Create streams */
        lpIMUtag = ( lp_Time_t * ) lp_stream_create( sizeof( lp_Time_t ) * lpIMU.dvISRmax );

        /* Inertial still range automatic detection */
        for ( lpParse = lp_Size_s( 0 ) ; lpParse < lpSize ; lpParse ++ ) {

            /* Update accumulators */
            lpAccumGRX += lpIMUgrx[lpParse];
            lpAccumGRY += lpIMUgry[lpParse];
            lpAccumGRZ += lpIMUgrz[lpParse];
            lpAccumACX += lpIMUacx[lpParse];
            lpAccumACY += lpIMUacy[lpParse];
            lpAccumACZ += lpIMUacz[lpParse];

            /* Update accumulators index */
            lpAccumIDX ++; 

            /* Apply detection condition */
            if ( ( lpParse + lp_Size_s( 1 ) == lpSize ) || (

                ( abs( lpIMUgrx[lpParse] - ( lpAccumGRX / lp_Real_c( lpAccumIDX ) ) ) > 0.05 ) ||
                ( abs( lpIMUgry[lpParse] - ( lpAccumGRY / lp_Real_c( lpAccumIDX ) ) ) > 0.05 ) ||
                ( abs( lpIMUgrz[lpParse] - ( lpAccumGRZ / lp_Real_c( lpAccumIDX ) ) ) > 0.05 ) ||
                ( abs( lpIMUacx[lpParse] - ( lpAccumACX / lp_Real_c( lpAccumIDX ) ) ) > 0.50 ) ||
                ( abs( lpIMUacy[lpParse] - ( lpAccumACY / lp_Real_c( lpAccumIDX ) ) ) > 0.50 ) ||
                ( abs( lpIMUacz[lpParse] - ( lpAccumACZ / lp_Real_c( lpAccumIDX ) ) ) > 0.50 )

            ) ) {

                /* Check statistical accumulation minimum */
                if ( ( lpParse - lp_Size_s( 1 ) - lpBound ) > lp_Size_s( 32 ) ) {                   

                    /* Verify range count maximum */
                    if ( lpIndex < lpIMU.dvISRmax ) {

                        /* Assign found range */
                        lpIMUtag[lpIndex ++] = lpIMUsyn[lpBound];
                        lpIMUtag[lpIndex ++] = lpIMUsyn[lpParse - 1];

                        /* Select maximum width range */
                        if ( ( lpParse - lp_Size_s( 1 ) - lpBound ) > lpWidth ) {

                            /* Assign range boundaries */
                            lpIMUtag[0] = lpIMUsyn[lpBound];
                            lpIMUtag[1] = lpIMUsyn[lpParse - 1];

                            /* Assign selected range width */
                            lpWidth = lpParse - lp_Size_s( 1 ) - lpBound;

                        }

                    }

                }

                /* Reset search boundary */
                lpBound = lpParse;

                /* Reset accumulators */
                lpAccumGRX = lp_Real_s( 0.0 );
                lpAccumGRY = lp_Real_s( 0.0 );
                lpAccumGRZ = lp_Real_s( 0.0 );
                lpAccumACX = lp_Real_s( 0.0 );
                lpAccumACY = lp_Real_s( 0.0 );
                lpAccumACZ = lp_Real_s( 0.0 );

                /* Reset accumulators index */
                lpAccumIDX = lp_Size_s( 0 );

            }

        }

        /* Write streams */
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_ISRAD_MOD, LP_STREAM_CPN_TAG, lpIMUtag, sizeof( lp_Time_t ) * lpIndex );

        /* Unallocate streams memory */
        lpIMUgrx = lp_stream_delete( lpIMUgrx );
        lpIMUgry = lp_stream_delete( lpIMUgry );
        lpIMUgrz = lp_stream_delete( lpIMUgrz );
        lpIMUacx = lp_stream_delete( lpIMUacx );
        lpIMUacy = lp_stream_delete( lpIMUacy );
        lpIMUacz = lp_stream_delete( lpIMUacz );
        lpIMUtag = lp_stream_delete( lpIMUtag );
        lpIMUsyn = lp_stream_delete( lpIMUsyn );

        /* Return device descriptor */
        return( lpIMU );
 
    }

