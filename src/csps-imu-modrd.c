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

    csps_IMU csps_imu_modrd(

        const csps_Char_t * const cspsPath,
        csps_IMU cspsDevice,
        const csps_Char_t * const cspsName,
        const csps_Char_t * const cspsPS__

    ) {

        /* Downsampling variables */
        csps_Size_t cspsParse = csps_Size_s( 0 );
        csps_Size_t cspsIndex = csps_Size_s( 0 );
        csps_Size_t cspsShift = csps_Size_s( 0 );
        csps_Size_t cspsReduce = csps_Size_s( 0 );

        /* Files size */
        csps_Size_t cspsSize = csps_Size_s( 0 );

        /* Data buffers */
        csps_Real_t * cspsDEVgrx = NULL;
        csps_Real_t * cspsDEVgry = NULL;
        csps_Real_t * cspsDEVgrz = NULL;
        csps_Real_t * cspsDEVacx = NULL;
        csps_Real_t * cspsDEVacy = NULL;
        csps_Real_t * cspsDEVacz = NULL;
        csps_Time_t * cspsDEVsyn = NULL;

        /* Obtain stream size */
        cspsSize = csps_stream_size( cspsPath, CSPS_IMU_MODRD_DEV, cspsName, cspsPS__, "syn" ) / sizeof( csps_Time_t );

        /* Read streams data */
        cspsDEVgrx = csps_stream_read( cspsPath, CSPS_IMU_MODRD_DEV, cspsName, cspsPS__, "grx", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVgry = csps_stream_read( cspsPath, CSPS_IMU_MODRD_DEV, cspsName, cspsPS__, "gry", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVgrz = csps_stream_read( cspsPath, CSPS_IMU_MODRD_DEV, cspsName, cspsPS__, "grz", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVacx = csps_stream_read( cspsPath, CSPS_IMU_MODRD_DEV, cspsName, cspsPS__, "acx", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVacy = csps_stream_read( cspsPath, CSPS_IMU_MODRD_DEV, cspsName, cspsPS__, "acy", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVacz = csps_stream_read( cspsPath, CSPS_IMU_MODRD_DEV, cspsName, cspsPS__, "acz", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVsyn = csps_stream_read( cspsPath, CSPS_IMU_MODRD_DEV, cspsName, cspsPS__, "syn", sizeof( csps_Time_t ) * cspsSize );

        /* Compute downsampling reduction factor */
        cspsReduce = cspsDevice.dvifreq / cspsDevice.dvdfreq;

        /* Set file size to last cspsReduce multiple */
        cspsSize = ( cspsSize / cspsReduce ) * cspsReduce;

        /* Downsampling procedure */
        while ( cspsParse < cspsSize ) {

            /* Downsampling accumulation */
            for ( cspsIndex = csps_Size_s( 1 ) ; cspsIndex < cspsReduce ; cspsIndex ++ ) {

                /* Sampling accumulation */
                cspsDEVgrx[cspsParse] += cspsDEVgrx[cspsParse + cspsIndex];
                cspsDEVgry[cspsParse] += cspsDEVgry[cspsParse + cspsIndex];
                cspsDEVgrz[cspsParse] += cspsDEVgrz[cspsParse + cspsIndex];
                cspsDEVacx[cspsParse] += cspsDEVacx[cspsParse + cspsIndex];
                cspsDEVacy[cspsParse] += cspsDEVacy[cspsParse + cspsIndex];
                cspsDEVacz[cspsParse] += cspsDEVacz[cspsParse + cspsIndex];

            }

            /* Downsampling mean computation */
            cspsDEVgrx[cspsParse] /= cspsReduce;
            cspsDEVgry[cspsParse] /= cspsReduce;
            cspsDEVgrz[cspsParse] /= cspsReduce;
            cspsDEVacx[cspsParse] /= cspsReduce;
            cspsDEVacy[cspsParse] /= cspsReduce;
            cspsDEVacz[cspsParse] /= cspsReduce;

            /* Downsampling reindexation */
            cspsDEVgrx[cspsShift] = cspsDEVgrx[cspsParse];
            cspsDEVgry[cspsShift] = cspsDEVgry[cspsParse];
            cspsDEVgrz[cspsShift] = cspsDEVgrz[cspsParse];
            cspsDEVacx[cspsShift] = cspsDEVacx[cspsParse];
            cspsDEVacy[cspsShift] = cspsDEVacy[cspsParse];
            cspsDEVacz[cspsShift] = cspsDEVacz[cspsParse];

            /* Timestamp specific downsampling */
            cspsDEVsyn[cspsShift++] = cspsDEVsyn[cspsParse + cspsIndex - 1];

            /* Update donwsampling parser */
            cspsParse += cspsReduce;

        }

        /* Write stream data */
        csps_stream_write( cspsPath, CSPS_IMU_MODRD_DEV, cspsName, CSPS_IMU_MODRD_MOD, "grx", cspsDEVgrx, sizeof( csps_Real_t ) * cspsShift );
        csps_stream_write( cspsPath, CSPS_IMU_MODRD_DEV, cspsName, CSPS_IMU_MODRD_MOD, "gry", cspsDEVgry, sizeof( csps_Real_t ) * cspsShift );
        csps_stream_write( cspsPath, CSPS_IMU_MODRD_DEV, cspsName, CSPS_IMU_MODRD_MOD, "grz", cspsDEVgrz, sizeof( csps_Real_t ) * cspsShift );
        csps_stream_write( cspsPath, CSPS_IMU_MODRD_DEV, cspsName, CSPS_IMU_MODRD_MOD, "acx", cspsDEVacx, sizeof( csps_Real_t ) * cspsShift );
        csps_stream_write( cspsPath, CSPS_IMU_MODRD_DEV, cspsName, CSPS_IMU_MODRD_MOD, "acy", cspsDEVacy, sizeof( csps_Real_t ) * cspsShift );
        csps_stream_write( cspsPath, CSPS_IMU_MODRD_DEV, cspsName, CSPS_IMU_MODRD_MOD, "acz", cspsDEVacz, sizeof( csps_Real_t ) * cspsShift );
        csps_stream_write( cspsPath, CSPS_IMU_MODRD_DEV, cspsName, CSPS_IMU_MODRD_MOD, "syn", cspsDEVsyn, sizeof( csps_Time_t ) * cspsShift );

        /* Unallocate buffer memory */
        free( cspsDEVgrx );
        free( cspsDEVgry );
        free( cspsDEVgrz );
        free( cspsDEVacx );
        free( cspsDEVacy );
        free( cspsDEVacz );
        free( cspsDEVsyn );

        /* Return device descriptor */
        return( cspsDevice );

    }

