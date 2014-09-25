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

    # include "csps-imu-mod-SGSFR.h"

/*
    Source - IMU signals frequency reduction
 */

    lp_Void_t lp_imu_mod_SGSFR( 

        const lp_Char_t * const lpPath, 
        const lp_IMU            lpIMU, 
        const lp_Char_t * const lpIMUmod 

    ) {

        /* Downsampling variables */
        lp_Size_t lpParse  = lp_Size_s( 0 );
        lp_Size_t lpIndex  = lp_Size_s( 0 );
        lp_Size_t lpShift  = lp_Size_s( 0 );
        lp_Size_t lpReduce = lp_Size_s( 0 );

        /* Stream size variables */
        lp_Size_t lpSize = lp_Size_s( 0 );

        /* Stream memory variables */
        lp_Real_t * lpIMUgrx = LP_NULL;
        lp_Real_t * lpIMUgry = LP_NULL;
        lp_Real_t * lpIMUgrz = LP_NULL;
        lp_Real_t * lpIMUacx = LP_NULL;
        lp_Real_t * lpIMUacy = LP_NULL;
        lp_Real_t * lpIMUacz = LP_NULL;
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

        /* Compute downsampling reduction factor */
        lpReduce = lpIMU.dvifreq / lpIMU.dvdfreq;

        /* Set file size to last multiple */
        lpSize = ( lpSize / lpReduce ) * lpReduce;

        /* Downsampling procedure */
        while ( lpParse < lpSize ) {

            /* Downsampling accumulation */
            for ( lpIndex = lp_Size_s( 1 ) ; lpIndex < lpReduce ; lpIndex ++ ) {

                /* Quantities accumulation */
                lpIMUgrx[lpParse] += lpIMUgrx[lpParse + lpIndex];
                lpIMUgry[lpParse] += lpIMUgry[lpParse + lpIndex];
                lpIMUgrz[lpParse] += lpIMUgrz[lpParse + lpIndex];
                lpIMUacx[lpParse] += lpIMUacx[lpParse + lpIndex];
                lpIMUacy[lpParse] += lpIMUacy[lpParse + lpIndex];
                lpIMUacz[lpParse] += lpIMUacz[lpParse + lpIndex];

            }

            /* Downsampling mean computation */
            lpIMUgrx[lpParse] /= lpReduce;
            lpIMUgry[lpParse] /= lpReduce;
            lpIMUgrz[lpParse] /= lpReduce;
            lpIMUacx[lpParse] /= lpReduce;
            lpIMUacy[lpParse] /= lpReduce;
            lpIMUacz[lpParse] /= lpReduce;

            /* Downsampling reindexation */
            lpIMUgrx[lpShift] = lpIMUgrx[lpParse];
            lpIMUgry[lpShift] = lpIMUgry[lpParse];
            lpIMUgrz[lpShift] = lpIMUgrz[lpParse];
            lpIMUacx[lpShift] = lpIMUacx[lpParse];
            lpIMUacy[lpShift] = lpIMUacy[lpParse];
            lpIMUacz[lpShift] = lpIMUacz[lpParse];

            /* Timestamp specific downsampling */
            lpIMUsyn[lpShift++] = lpIMUsyn[lpParse + lpIndex - 1];

            /* Update donwsampling parser */
            lpParse += lpReduce;

        }

        /* Write streams */
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_SGSFR_MOD, LP_STREAM_CPN_GRX, lpIMUgrx, sizeof( lp_Real_t ) * lpShift );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_SGSFR_MOD, LP_STREAM_CPN_GRY, lpIMUgry, sizeof( lp_Real_t ) * lpShift );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_SGSFR_MOD, LP_STREAM_CPN_GRZ, lpIMUgrz, sizeof( lp_Real_t ) * lpShift );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_SGSFR_MOD, LP_STREAM_CPN_ACX, lpIMUacx, sizeof( lp_Real_t ) * lpShift );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_SGSFR_MOD, LP_STREAM_CPN_ACY, lpIMUacy, sizeof( lp_Real_t ) * lpShift );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_SGSFR_MOD, LP_STREAM_CPN_ACZ, lpIMUacz, sizeof( lp_Real_t ) * lpShift );
        lp_stream_write( lpPath, lpIMU.dvType, lpIMU.dvTag, LP_IMU_SGSFR_MOD, LP_STREAM_CPN_SYN, lpIMUsyn, sizeof( lp_Time_t ) * lpShift );

        /* Unallocate streams memory */
        lpIMUgrx = lp_stream_delete( lpIMUgrx );
        lpIMUgry = lp_stream_delete( lpIMUgry );
        lpIMUgrz = lp_stream_delete( lpIMUgrz );
        lpIMUacx = lp_stream_delete( lpIMUacx );
        lpIMUacy = lp_stream_delete( lpIMUacy );
        lpIMUacz = lp_stream_delete( lpIMUacz );
        lpIMUsyn = lp_stream_delete( lpIMUsyn );

    }

