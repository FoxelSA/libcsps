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
    Source - Inertial still range automatic detection
 */

    lp_IMU lp_imu_mod_ISRAD( 

        const lp_Char_t * const lpPath, 
        lp_IMU                  lpIMU, 
        const lp_Char_t * const lpIMUmod 

    ) {

        /* Parsing variables */
        lp_Size_t lpParse = lp_Size_s( 0 );

        /* Stream size variables */
        lp_Size_t lpSize = lp_Size_s( 0 );

        /* Still range description variables */
        lp_Size_t lpBound = lp_Size_s( 0 );
        lp_Size_t lpWidth = lp_Size_s( 0 );

        /* Accumulators variables */
        lp_Real_t lpAccumGRX = lp_Real_s( 0.0 );
        lp_Real_t lpAccumGRY = lp_Real_s( 0.0 );
        lp_Real_t lpAccumGRZ = lp_Real_s( 0.0 );
        lp_Real_t lpAccumACX = lp_Real_s( 0.0 );
        lp_Real_t lpAccumACY = lp_Real_s( 0.0 );
        lp_Real_t lpAccumACZ = lp_Real_s( 0.0 );

        /* Accumulator index variables */
        lp_Size_t lpAccumIDX = lp_Size_s( 0 );

        /* Stream memory variables */
        lp_Real_t * lpDEVgrx = LP_NULL;
        lp_Real_t * lpDEVgry = LP_NULL;
        lp_Real_t * lpDEVgrz = LP_NULL;
        lp_Real_t * lpDEVacx = LP_NULL;
        lp_Real_t * lpDEVacy = LP_NULL;
        lp_Real_t * lpDEVacz = LP_NULL;
        lp_Time_t * lpDEVsyn = LP_NULL;

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod );

        /* Read streams */
        lpDEVgrx = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod, LP_STREAM_CPN_GRX, sizeof( lp_Real_t ) * lpSize );
        lpDEVgry = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod, LP_STREAM_CPN_GRY, sizeof( lp_Real_t ) * lpSize );
        lpDEVgrz = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod, LP_STREAM_CPN_GRZ, sizeof( lp_Real_t ) * lpSize );
        lpDEVacx = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod, LP_STREAM_CPN_ACX, sizeof( lp_Real_t ) * lpSize );
        lpDEVacy = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod, LP_STREAM_CPN_ACY, sizeof( lp_Real_t ) * lpSize );
        lpDEVacz = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod, LP_STREAM_CPN_ACZ, sizeof( lp_Real_t ) * lpSize );
        lpDEVsyn = lp_stream_read( lpPath, lpIMU.dvType, lpIMU.dvTag, lpIMUmod, LP_STREAM_CPN_SYN, sizeof( lp_Time_t ) * lpSize );

        /* Inertial still range automatic detection */
        for ( lpParse = lp_Size_s( 0 ) ; lpParse < lpSize ; lpParse ++ ) {

            /* Update accumulators */
            lpAccumGRX += lpDEVgrx[lpParse];
            lpAccumGRY += lpDEVgry[lpParse];
            lpAccumGRZ += lpDEVgrz[lpParse];
            lpAccumACX += lpDEVacx[lpParse];
            lpAccumACY += lpDEVacy[lpParse];
            lpAccumACZ += lpDEVacz[lpParse];

            /* Update accumulators index */
            lpAccumIDX ++; 

            /* Apply detection condition */
            if ( ( lpParse + 1 == lpSize ) || (

                ( abs( lpDEVgrx[lpParse] - ( lpAccumGRX / lp_Real_c( lpAccumIDX ) ) ) > 0.05 ) ||
                ( abs( lpDEVgry[lpParse] - ( lpAccumGRY / lp_Real_c( lpAccumIDX ) ) ) > 0.05 ) ||
                ( abs( lpDEVgrz[lpParse] - ( lpAccumGRZ / lp_Real_c( lpAccumIDX ) ) ) > 0.05 ) ||
                ( abs( lpDEVacx[lpParse] - ( lpAccumACX / lp_Real_c( lpAccumIDX ) ) ) > 0.50 ) ||
                ( abs( lpDEVacy[lpParse] - ( lpAccumACY / lp_Real_c( lpAccumIDX ) ) ) > 0.50 ) ||
                ( abs( lpDEVacz[lpParse] - ( lpAccumACZ / lp_Real_c( lpAccumIDX ) ) ) > 0.50 )

            ) ) {

                /* Check statistical accumulation minimum */
                if ( ( lpParse - lp_Size_s( 1 ) - lpBound ) > lp_Size_s( 32 ) ) {

                    /* Select maximum width range */
                    if ( ( lpParse - lp_Size_s( 1 ) - lpBound ) > lpWidth ) {

                        /* Assign range boundaries */
                        lpIMU.dvMin = lpDEVsyn[lpBound];
                        lpIMU.dvMax = lpDEVsyn[lpParse - 1];

                        /* Assign selected range width */
                        lpWidth = lpParse - lp_Size_s( 1 ) - lpBound;

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

        /* Unallocate streams memory */
        lpDEVgrx = lp_stream_delete( lpDEVgrx );
        lpDEVgry = lp_stream_delete( lpDEVgry );
        lpDEVgrz = lp_stream_delete( lpDEVgrz );
        lpDEVacx = lp_stream_delete( lpDEVacx );
        lpDEVacy = lp_stream_delete( lpDEVacy );
        lpDEVacz = lp_stream_delete( lpDEVacz );
        lpDEVsyn = lp_stream_delete( lpDEVsyn );

        /* Return device descriptor */
        return( lpIMU );
 
    }

