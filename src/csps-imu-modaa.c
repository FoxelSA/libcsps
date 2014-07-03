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

    # include "csps-imu-modaa.h"

/*
    Source - IMU absolute acceleration computation module
 */

    csps_IMU csps_imu_modaa(

        const csps_Char_t * const cspsPath,
        csps_IMU cspsDevice,
        const csps_Char_t * const cspsName,
        const csps_Char_t * const cspsPSac,
        const csps_Char_t * const cspsPSf_

    ) {

        /* Integration variables */
        csps_Size_t cspsParse = 0;

        /* Files size */
        csps_Size_t cspsSize = 0;

        /* Data buffers */
        csps_Real_t * cspsDEVacx = NULL;
        csps_Real_t * cspsDEVacy = NULL;
        csps_Real_t * cspsDEVacz = NULL;
        csps_Time_t * cspsDEVasy = NULL;
        csps_Real_t * cspsDEVfxx = NULL;
        csps_Real_t * cspsDEVfxy = NULL;
        csps_Real_t * cspsDEVfxz = NULL;
        csps_Real_t * cspsDEVfyx = NULL;
        csps_Real_t * cspsDEVfyy = NULL;
        csps_Real_t * cspsDEVfyz = NULL;
        csps_Real_t * cspsDEVfzx = NULL;
        csps_Real_t * cspsDEVfzy = NULL;
        csps_Real_t * cspsDEVfzz = NULL;
        csps_Time_t * cspsDEVfsy = NULL;
        csps_Real_t * cspsDEVaax = NULL;
        csps_Real_t * cspsDEVaay = NULL;
        csps_Real_t * cspsDEVaaz = NULL;
        csps_Time_t * cspsDEVsyn = NULL;

        /* Obtain stream size */
        cspsSize = csps_stream_size( cspsPath, CSPS_IMU_MODAA_DEV, cspsName, cspsPSac, "syn" ) / sizeof( csps_Time_t );

        /* Read streams data */
        cspsDEVacx = csps_stream_read( cspsPath, CSPS_IMU_MODAA_DEV, cspsName, cspsPSac, "acx", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVacy = csps_stream_read( cspsPath, CSPS_IMU_MODAA_DEV, cspsName, cspsPSac, "acy", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVacz = csps_stream_read( cspsPath, CSPS_IMU_MODAA_DEV, cspsName, cspsPSac, "acz", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVasy = csps_stream_read( cspsPath, CSPS_IMU_MODAA_DEV, cspsName, cspsPSac, "syn", sizeof( csps_Time_t ) * cspsSize );
        cspsDEVfxx = csps_stream_read( cspsPath, CSPS_IMU_MODAA_DEV, cspsName, cspsPSf_, "fxx", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVfxy = csps_stream_read( cspsPath, CSPS_IMU_MODAA_DEV, cspsName, cspsPSf_, "fxy", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVfxz = csps_stream_read( cspsPath, CSPS_IMU_MODAA_DEV, cspsName, cspsPSf_, "fxz", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVfyx = csps_stream_read( cspsPath, CSPS_IMU_MODAA_DEV, cspsName, cspsPSf_, "fyx", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVfyy = csps_stream_read( cspsPath, CSPS_IMU_MODAA_DEV, cspsName, cspsPSf_, "fyy", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVfyz = csps_stream_read( cspsPath, CSPS_IMU_MODAA_DEV, cspsName, cspsPSf_, "fyz", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVfzx = csps_stream_read( cspsPath, CSPS_IMU_MODAA_DEV, cspsName, cspsPSf_, "fzx", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVfzy = csps_stream_read( cspsPath, CSPS_IMU_MODAA_DEV, cspsName, cspsPSf_, "fzy", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVfzz = csps_stream_read( cspsPath, CSPS_IMU_MODAA_DEV, cspsName, cspsPSf_, "fzz", sizeof( csps_Real_t ) * cspsSize );
        cspsDEVfsy = csps_stream_read( cspsPath, CSPS_IMU_MODAA_DEV, cspsName, cspsPSf_, "syn", sizeof( csps_Time_t ) * cspsSize );

        /* Allocate stream memory */
        cspsDEVaax = ( csps_Real_t * ) malloc( sizeof( csps_Real_t ) * cspsSize );
        cspsDEVaay = ( csps_Real_t * ) malloc( sizeof( csps_Real_t ) * cspsSize );
        cspsDEVaaz = ( csps_Real_t * ) malloc( sizeof( csps_Real_t ) * cspsSize );
        cspsDEVsyn = ( csps_Time_t * ) malloc( sizeof( csps_Time_t ) * cspsSize );

        /* Frame integration procedure */
        for ( cspsParse = csps_Size_s( 0 ) ; cspsParse < cspsSize ; cspsParse ++ ) {

            /* Computation - Advance absolute acceleration x-vector */
            cspsDEVaax[cspsParse] = cspsDEVacx[cspsParse] * cspsDEVfxx[cspsParse] +
                                    cspsDEVacy[cspsParse] * cspsDEVfyx[cspsParse] +
                                    cspsDEVacz[cspsParse] * cspsDEVfzx[cspsParse];

            /* Computation - Advance absolute acceleration y-vector */
            cspsDEVaax[cspsParse] = cspsDEVacx[cspsParse] * cspsDEVfxy[cspsParse] +
                                    cspsDEVacy[cspsParse] * cspsDEVfyy[cspsParse] +
                                    cspsDEVacz[cspsParse] * cspsDEVfzy[cspsParse];

            /* Computation - Advance absolute acceleration z-vector */
            cspsDEVaax[cspsParse] = cspsDEVacx[cspsParse] * cspsDEVfxz[cspsParse] +
                                    cspsDEVacy[cspsParse] * cspsDEVfyz[cspsParse] +
                                    cspsDEVacz[cspsParse] * cspsDEVfzz[cspsParse];

        }

        /* Write stream data */
        csps_stream_write( cspsPath, CSPS_IMU_MODAA_DEV, cspsName, CSPS_IMU_MODAA_MOD, "aax", cspsDEVaax, sizeof( csps_Real_t ) * cspsSize );
        csps_stream_write( cspsPath, CSPS_IMU_MODAA_DEV, cspsName, CSPS_IMU_MODAA_MOD, "aay", cspsDEVaay, sizeof( csps_Real_t ) * cspsSize );
        csps_stream_write( cspsPath, CSPS_IMU_MODAA_DEV, cspsName, CSPS_IMU_MODAA_MOD, "aaz", cspsDEVaaz, sizeof( csps_Real_t ) * cspsSize );
        csps_stream_write( cspsPath, CSPS_IMU_MODAA_DEV, cspsName, CSPS_IMU_MODAA_MOD, "syn", cspsDEVaaz, sizeof( csps_Time_t ) * cspsSize );

        /* Unallocate buffer memory */
        free( cspsDEVacx );
        free( cspsDEVacy );
        free( cspsDEVacz );
        free( cspsDEVasy );
        free( cspsDEVfxx );
        free( cspsDEVfxy );
        free( cspsDEVfxz );
        free( cspsDEVfyx );
        free( cspsDEVfyy );
        free( cspsDEVfyz );
        free( cspsDEVfzx );
        free( cspsDEVfzy );
        free( cspsDEVfzz );
        free( cspsDEVfsy );
        free( cspsDEVaax );
        free( cspsDEVaay );
        free( cspsDEVaaz );
        free( cspsDEVsyn );

        /* Return device descriptor */
        return( cspsDevice );

    }

