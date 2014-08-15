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

    # include "csps-imu-modrd.h"

/*
    Source - IMU relative quantities downsampling module
 */

    lp_IMU lp_imu_modrd(

        const lp_Char_t * const lpPath,
        lp_IMU lpDevice,
        const lp_Char_t * const lpName,
        const lp_Char_t * const lpPS__

    ) {

        /* Downsampling variables */
        lp_Size_t lpParse = lp_Size_s( 0 );
        lp_Size_t lpIndex = lp_Size_s( 0 );
        lp_Size_t lpShift = lp_Size_s( 0 );
        lp_Size_t lpReduce = lp_Size_s( 0 );

        /* Files size */
        lp_Size_t lpSize = lp_Size_s( 0 );

        /* Data buffers */
        lp_Real_t * lpDEVgrx = NULL;
        lp_Real_t * lpDEVgry = NULL;
        lp_Real_t * lpDEVgrz = NULL;
        lp_Real_t * lpDEVacx = NULL;
        lp_Real_t * lpDEVacy = NULL;
        lp_Real_t * lpDEVacz = NULL;
        lp_Time_t * lpDEVsyn = NULL;

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, LP_IMU_MODRD_DEV, lpName, lpPS__, "syn" ) / sizeof( lp_Time_t );

        /* Read streams data */
        lpDEVgrx = lp_stream_read( lpPath, LP_IMU_MODRD_DEV, lpName, lpPS__, "grx", sizeof( lp_Real_t ) * lpSize );
        lpDEVgry = lp_stream_read( lpPath, LP_IMU_MODRD_DEV, lpName, lpPS__, "gry", sizeof( lp_Real_t ) * lpSize );
        lpDEVgrz = lp_stream_read( lpPath, LP_IMU_MODRD_DEV, lpName, lpPS__, "grz", sizeof( lp_Real_t ) * lpSize );
        lpDEVacx = lp_stream_read( lpPath, LP_IMU_MODRD_DEV, lpName, lpPS__, "acx", sizeof( lp_Real_t ) * lpSize );
        lpDEVacy = lp_stream_read( lpPath, LP_IMU_MODRD_DEV, lpName, lpPS__, "acy", sizeof( lp_Real_t ) * lpSize );
        lpDEVacz = lp_stream_read( lpPath, LP_IMU_MODRD_DEV, lpName, lpPS__, "acz", sizeof( lp_Real_t ) * lpSize );
        lpDEVsyn = lp_stream_read( lpPath, LP_IMU_MODRD_DEV, lpName, lpPS__, "syn", sizeof( lp_Time_t ) * lpSize );

        /* Compute downsampling reduction factor */
        lpReduce = lpDevice.dvifreq / lpDevice.dvdfreq;

        /* Set file size to last lpReduce multiple */
        lpSize = ( lpSize / lpReduce ) * lpReduce;

        /* Downsampling procedure */
        while ( lpParse < lpSize ) {

            /* Downsampling accumulation */
            for ( lpIndex = lp_Size_s( 1 ) ; lpIndex < lpReduce ; lpIndex ++ ) {

                /* Sampling accumulation */
                lpDEVgrx[lpParse] += lpDEVgrx[lpParse + lpIndex];
                lpDEVgry[lpParse] += lpDEVgry[lpParse + lpIndex];
                lpDEVgrz[lpParse] += lpDEVgrz[lpParse + lpIndex];
                lpDEVacx[lpParse] += lpDEVacx[lpParse + lpIndex];
                lpDEVacy[lpParse] += lpDEVacy[lpParse + lpIndex];
                lpDEVacz[lpParse] += lpDEVacz[lpParse + lpIndex];

            }

            /* Downsampling mean computation */
            lpDEVgrx[lpParse] /= lpReduce;
            lpDEVgry[lpParse] /= lpReduce;
            lpDEVgrz[lpParse] /= lpReduce;
            lpDEVacx[lpParse] /= lpReduce;
            lpDEVacy[lpParse] /= lpReduce;
            lpDEVacz[lpParse] /= lpReduce;

            /* Downsampling reindexation */
            lpDEVgrx[lpShift] = lpDEVgrx[lpParse];
            lpDEVgry[lpShift] = lpDEVgry[lpParse];
            lpDEVgrz[lpShift] = lpDEVgrz[lpParse];
            lpDEVacx[lpShift] = lpDEVacx[lpParse];
            lpDEVacy[lpShift] = lpDEVacy[lpParse];
            lpDEVacz[lpShift] = lpDEVacz[lpParse];

            /* Timestamp specific downsampling */
            lpDEVsyn[lpShift++] = lpDEVsyn[lpParse + lpIndex - 1];

            /* Update donwsampling parser */
            lpParse += lpReduce;

        }

        /* Write stream data */
        lp_stream_write( lpPath, LP_IMU_MODRD_DEV, lpName, LP_IMU_MODRD_MOD, "grx", lpDEVgrx, sizeof( lp_Real_t ) * lpShift );
        lp_stream_write( lpPath, LP_IMU_MODRD_DEV, lpName, LP_IMU_MODRD_MOD, "gry", lpDEVgry, sizeof( lp_Real_t ) * lpShift );
        lp_stream_write( lpPath, LP_IMU_MODRD_DEV, lpName, LP_IMU_MODRD_MOD, "grz", lpDEVgrz, sizeof( lp_Real_t ) * lpShift );
        lp_stream_write( lpPath, LP_IMU_MODRD_DEV, lpName, LP_IMU_MODRD_MOD, "acx", lpDEVacx, sizeof( lp_Real_t ) * lpShift );
        lp_stream_write( lpPath, LP_IMU_MODRD_DEV, lpName, LP_IMU_MODRD_MOD, "acy", lpDEVacy, sizeof( lp_Real_t ) * lpShift );
        lp_stream_write( lpPath, LP_IMU_MODRD_DEV, lpName, LP_IMU_MODRD_MOD, "acz", lpDEVacz, sizeof( lp_Real_t ) * lpShift );
        lp_stream_write( lpPath, LP_IMU_MODRD_DEV, lpName, LP_IMU_MODRD_MOD, "syn", lpDEVsyn, sizeof( lp_Time_t ) * lpShift );

        /* Unallocate buffer memory */
        free( lpDEVgrx );
        free( lpDEVgry );
        free( lpDEVgrz );
        free( lpDEVacx );
        free( lpDEVacy );
        free( lpDEVacz );
        free( lpDEVsyn );

        /* Return device descriptor */
        return( lpDevice );

    }

