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
        lp_IMU                  lpDevice, 
        const lp_Char_t * const lpPS__ 

    ) {
        
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
        lpSize = lp_stream_size( lpPath, LP_IMU_SGNDN_DEV, lpDevice.dvTag, lpPS__ );

        /* Read streams data */
        lpDEVgrx = lp_stream_read( lpPath, LP_IMU_SGNDN_DEV, lpDevice.dvTag, lpPS__, "grx", sizeof( lp_Real_t ) * lpSize );
        lpDEVgry = lp_stream_read( lpPath, LP_IMU_SGNDN_DEV, lpDevice.dvTag, lpPS__, "gry", sizeof( lp_Real_t ) * lpSize );
        lpDEVgrz = lp_stream_read( lpPath, LP_IMU_SGNDN_DEV, lpDevice.dvTag, lpPS__, "grz", sizeof( lp_Real_t ) * lpSize );
        lpDEVacx = lp_stream_read( lpPath, LP_IMU_SGNDN_DEV, lpDevice.dvTag, lpPS__, "acx", sizeof( lp_Real_t ) * lpSize );
        lpDEVacy = lp_stream_read( lpPath, LP_IMU_SGNDN_DEV, lpDevice.dvTag, lpPS__, "acy", sizeof( lp_Real_t ) * lpSize );
        lpDEVacz = lp_stream_read( lpPath, LP_IMU_SGNDN_DEV, lpDevice.dvTag, lpPS__, "acz", sizeof( lp_Real_t ) * lpSize );
        lpDEVsyn = lp_stream_read( lpPath, LP_IMU_SGNDN_DEV, lpDevice.dvTag, lpPS__, "syn", sizeof( lp_Time_t ) * lpSize );

        /* Denoising procedure */
        lp_noise_tvic( lpDEVgrx, lpSize, lp_Size_s( 10 ), lp_Size_s( 32 ) );
        lp_noise_tvic( lpDEVgry, lpSize, lp_Size_s( 10 ), lp_Size_s( 32 ) );
        lp_noise_tvic( lpDEVgrz, lpSize, lp_Size_s( 10 ), lp_Size_s( 32 ) );
        lp_noise_tvic( lpDEVacx, lpSize, lp_Size_s( 10 ), lp_Size_s( 32 ) );
        lp_noise_tvic( lpDEVacy, lpSize, lp_Size_s( 10 ), lp_Size_s( 32 ) );
        lp_noise_tvic( lpDEVacz, lpSize, lp_Size_s( 10 ), lp_Size_s( 32 ) );

        /* Write stream data */
        lp_stream_write( lpPath, LP_IMU_SGNDN_DEV, lpDevice.dvTag, LP_IMU_SGNDN_MOD, "grx", lpDEVgrx, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_SGNDN_DEV, lpDevice.dvTag, LP_IMU_SGNDN_MOD, "gry", lpDEVgry, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_SGNDN_DEV, lpDevice.dvTag, LP_IMU_SGNDN_MOD, "grz", lpDEVgrz, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_SGNDN_DEV, lpDevice.dvTag, LP_IMU_SGNDN_MOD, "acx", lpDEVacx, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_SGNDN_DEV, lpDevice.dvTag, LP_IMU_SGNDN_MOD, "acy", lpDEVacy, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_SGNDN_DEV, lpDevice.dvTag, LP_IMU_SGNDN_MOD, "acz", lpDEVacz, sizeof( lp_Real_t ) * lpSize );
        lp_stream_write( lpPath, LP_IMU_SGNDN_DEV, lpDevice.dvTag, LP_IMU_SGNDN_MOD, "syn", lpDEVsyn, sizeof( lp_Time_t ) * lpSize );

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

