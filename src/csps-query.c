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

    # include "csps-query.h"

/*
    Source - CSPS query - Time range
 */

    lp_QueryTime lp_query_time(

        const lp_Char_t * const lpPath,
        const lp_Char_t * const lpDevice,
        const lp_Char_t * const lpTag,
        const lp_Char_t * const lpModule

    ) {

        /* Files size */
        lp_Size_t lpSize = lp_Size_s( 0 );

        /* Data buffers */
        lp_Time_t * lpVPDsyn = NULL;

        /* Returned structure */
        lp_QueryTime lpTime;

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, lpDevice, lpTag, lpModule, "syn" ) / sizeof( lp_Time_t );

        /* Read streams data */
        lpVPDsyn = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "syn", sizeof( lp_Time_t ) * lpSize );

        /* Extract timestamp boundaries */
        lpTime.qrInitial = lpVPDsyn[0];
        lpTime.qrFinal   = lpVPDsyn[lpSize-1];

        /* Unallocate buffer memory */
        free( lpVPDsyn );

        /* Return time structure */
        return( lpTime );

    }

/*
    Source - CSPS query - Position
 */

    lp_QueryPosition lp_query_position_by_timestamp(

        const lp_Char_t * const lpPath,
        const lp_Char_t * const lpDevice,
        const lp_Char_t * const lpTag,
        const lp_Char_t * const lpModule,
        lp_Time_t               lpTimestamp

    ) {

        /* Returned structure */
        lp_QueryPosition lpPosition;

        /* Query variables */
        lp_Size_t lpParse = lp_Size_s( 0 );

        /* Files size */
        lp_Size_t lpSize = lp_Size_s( 0 );

        /* Interpolation sampling nodes */
        lp_Size_t lpSample0 = lp_Size_s( 0 );
        lp_Size_t lpSample1 = lp_Size_s( 0 );
        lp_Size_t lpSample2 = lp_Size_s( 0 );
        lp_Size_t lpSample3 = lp_Size_s( 0 );

        /* Interpolation time */
        lp_Real_t lpTimeI = lp_Real_s( 0.0 );
        lp_Real_t lpTime1 = lp_Real_s( 0.0 );
        lp_Real_t lpTime2 = lp_Real_s( 0.0 );
        lp_Real_t lpTime3 = lp_Real_s( 0.0 );

        /* Data buffers */
        lp_Real_t * lpVPDlat = NULL;
        lp_Real_t * lpVPDlon = NULL;
        lp_Real_t * lpVPDalt = NULL;
        lp_Time_t * lpVPDsyn = NULL;

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, lpDevice, lpTag, lpModule, "syn" ) / sizeof( lp_Time_t );

        /* Read streams data */
        lpVPDlat = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "lat", sizeof( lp_Real_t ) * lpSize );
        lpVPDlon = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "lon", sizeof( lp_Real_t ) * lpSize );
        lpVPDalt = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "alt", sizeof( lp_Real_t ) * lpSize );
        lpVPDsyn = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "syn", sizeof( lp_Time_t ) * lpSize );

        /* Obtains index of nearest lower or equal timestamp stored in synchronization array */
        if ( ( lpParse = lp_timestamp_index( lpTimestamp, lpVPDsyn, lpSize ) ) != LP_TIMESTAMP_FAULT ) {

            /* Compute quantity interpolation sampling nodes */
            lpSample0 = LP_RNG( lpParse - 1, 0, lpSize - lp_Size_s( 1 ) );
            lpSample1 = LP_RNG( lpParse    , 0, lpSize - lp_Size_s( 1 ) );
            lpSample2 = LP_RNG( lpParse + 1, 0, lpSize - lp_Size_s( 1 ) );
            lpSample3 = LP_RNG( lpParse + 2, 0, lpSize - lp_Size_s( 1 ) );

            /* Compute time interpolation variable */
            lpTimeI = lp_timestamp_float( lp_timestamp_diff( lpTimestamp, lpVPDsyn[lpSample0] ) );

            /* Compute time interpolation sample */
            lpTime1 = lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpSample1], lpVPDsyn[lpSample0] ) );
            lpTime2 = lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpSample2], lpVPDsyn[lpSample0] ) );
            lpTime3 = lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpSample3], lpVPDsyn[lpSample0] ) );

            /* Compute interpolation values - Latitude */
            lpPosition.qrLatitude = li_cubic( LI_CUBIC_FLAG_SET, lpTimeI, lpTime1, lpTime2, lpVPDlat[lpSample1], lpVPDlat[lpSample2],

                /* Standard derivatives */
                ( lpVPDlat[lpSample2] - lpVPDlat[lpSample0] ) / ( lpTime2  ),
                ( lpVPDlat[lpSample3] - lpVPDlat[lpSample1] ) / ( lpTime3 - lpTime1 )

            );

            /* Compute interpolation values - Longitude */
            lpPosition.qrLongitude = li_cubic( LI_CUBIC_FLAG_SET, lpTimeI, lpTime1, lpTime2, lpVPDlon[lpSample1], lpVPDlon[lpSample2],

                /* Standard derivatives */
                ( lpVPDlon[lpSample2] - lpVPDlon[lpSample0] ) / ( lpTime2 ),
                ( lpVPDlon[lpSample3] - lpVPDlon[lpSample1] ) / ( lpTime3 - lpTime1 )

            );

            /* Compute interpolation values - Altitude */
            lpPosition.qrAltitude = li_cubic( LI_CUBIC_FLAG_SET, lpTimeI, lpTime1, lpTime2, lpVPDalt[lpSample1], lpVPDalt[lpSample2],

                /* Standard derivatives */
                ( lpVPDalt[lpSample2] - lpVPDalt[lpSample0] ) / ( lpTime2 ),
                ( lpVPDalt[lpSample3] - lpVPDalt[lpSample1] ) / ( lpTime3 - lpTime1 )

            );

            # if defined LP_DEBUG

                //fprintf( stderr, "%" lp_Size_p " %" lp_Real_p " %" lp_Real_p " %" lp_Real_p " %" lp_Real_p " %" lp_Real_p "\n", 

                //    lpParse,
                //    lpTimeI,
                //    lpTime0,
                //    lpTime1,
                //    lpTime2,
                //    lpTime3

                //);

                fprintf( stderr, "%" lp_Size_p " %" lp_Real_p " %" lp_Real_p " %" lp_Real_p "\n", lpParse, lpPosition.qrLatitude, lpPosition.qrLongitude, lpPosition.qrAltitude );

            # endif

            /* Update query status */
            lpPosition.qrStatus = LP_TRUE;

        } else {

            /* Update query status */
            lpPosition.qrStatus = LP_FALSE;

        }

        /* Unallocate buffer memory */
        free( lpVPDlat );
        free( lpVPDlon );
        free( lpVPDalt );
        free( lpVPDsyn );

        /* Return position structure */
        return( lpPosition );

    }

/*
    Source - CSPS query - Orientation
 */

    lp_QueryOrientation lp_query_orientation_by_timestamp(

        const lp_Char_t * const lpPath,
        const lp_Char_t * const lpDevice,
        const lp_Char_t * const lpTag,
        const lp_Char_t * const lpModule,
        lp_Time_t               lpTimestamp

    ) {

        /* Returned structure */
        lp_QueryOrientation lpOrientation;

        /* Query variables */
        lp_Size_t lpParse = lp_Size_s( 0 );

        /* Files size */
        lp_Size_t lpSize = lp_Size_s( 0 );

        /* Interpolation sampling nodes */
        lp_Size_t lpSample0 = lp_Size_s( 0 );
        lp_Size_t lpSample1 = lp_Size_s( 0 );
        lp_Size_t lpSample2 = lp_Size_s( 0 );
        lp_Size_t lpSample3 = lp_Size_s( 0 );

        /* Interpolation time */
        lp_Real_t lpTimeI = lp_Real_s( 0.0 );
        lp_Real_t lpTime1 = lp_Real_s( 0.0 );
        lp_Real_t lpTime2 = lp_Real_s( 0.0 );
        lp_Real_t lpTime3 = lp_Real_s( 0.0 );

        /* Data buffers */
        lp_Real_t * lpVPDfxx = NULL;
        lp_Real_t * lpVPDfxy = NULL;
        lp_Real_t * lpVPDfxz = NULL;
        lp_Real_t * lpVPDfyx = NULL;
        lp_Real_t * lpVPDfyy = NULL;
        lp_Real_t * lpVPDfyz = NULL;
        lp_Real_t * lpVPDfzx = NULL;
        lp_Real_t * lpVPDfzy = NULL;
        lp_Real_t * lpVPDfzz = NULL;
        lp_Time_t * lpVPDsyn = NULL;

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, lpDevice, lpTag, lpModule, "syn" ) / sizeof( lp_Time_t );

        /* Read streams data */
        lpVPDfxx = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "fxx", sizeof( lp_Real_t ) * lpSize );
        lpVPDfxy = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "fxy", sizeof( lp_Real_t ) * lpSize );
        lpVPDfxz = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "fxz", sizeof( lp_Real_t ) * lpSize );
        lpVPDfyx = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "fyx", sizeof( lp_Real_t ) * lpSize );
        lpVPDfyy = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "fyy", sizeof( lp_Real_t ) * lpSize );
        lpVPDfyz = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "fyz", sizeof( lp_Real_t ) * lpSize );
        lpVPDfzx = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "fzx", sizeof( lp_Real_t ) * lpSize );
        lpVPDfzy = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "fzy", sizeof( lp_Real_t ) * lpSize );
        lpVPDfzz = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "fzz", sizeof( lp_Real_t ) * lpSize );
        lpVPDsyn = lp_stream_read( lpPath, lpDevice, lpTag, lpModule, "syn", sizeof( lp_Time_t ) * lpSize );

        /* Obtains index of nearest lower or equal timestamp stored in synchronization array */
        if ( ( lpParse = lp_timestamp_index( lpTimestamp, lpVPDsyn, lpSize ) ) != LP_TIMESTAMP_FAULT ) {

            /* Compute quantity interpolation sampling nodes */
            lpSample0 = LP_RNG( lpParse - 1, 0, lpSize - lp_Size_s( 1 ) );
            lpSample1 = LP_RNG( lpParse    , 0, lpSize - lp_Size_s( 1 ) );
            lpSample2 = LP_RNG( lpParse + 1, 0, lpSize - lp_Size_s( 1 ) );
            lpSample3 = LP_RNG( lpParse + 2, 0, lpSize - lp_Size_s( 1 ) );

            /* Compute time interpolation variable */
            lpTimeI = lp_timestamp_float( lp_timestamp_diff( lpTimestamp, lpVPDsyn[lpSample0] ) );

            /* Compute time interpolation sample */
            lpTime1 = lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpSample1], lpVPDsyn[lpSample0] ) );
            lpTime2 = lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpSample2], lpVPDsyn[lpSample0] ) );
            lpTime3 = lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpSample3], lpVPDsyn[lpSample0] ) );

            /* Compute interpolation values - Frame x-component x-vector */
            lpOrientation.qrfxx = li_cubic( LI_CUBIC_FLAG_SET, lpTimeI, lpTime1, lpTime2, lpVPDfxx[lpSample1], lpVPDfxx[lpSample2],

                /* Standard derivatives */
                ( lpVPDfxx[lpSample2] - lpVPDfxx[lpSample0] ) / ( lpTime2 ),
                ( lpVPDfxx[lpSample3] - lpVPDfxx[lpSample1] ) / ( lpTime3 - lpTime1)

            );

            /* Compute interpolation values - Frame y-component x-vector */
            lpOrientation.qrfxy = li_cubic( LI_CUBIC_FLAG_SET, lpTimeI, lpTime1, lpTime2, lpVPDfxy[lpSample1], lpVPDfxy[lpSample2],

                /* Standard derivatives */
                ( lpVPDfxy[lpSample2] - lpVPDfxy[lpSample0] ) / ( lpTime2 ),
                ( lpVPDfxy[lpSample3] - lpVPDfxy[lpSample1] ) / ( lpTime3 - lpTime1)

            );

            /* Compute interpolation values - Frame z-component x-vector */
            lpOrientation.qrfxz = li_cubic( LI_CUBIC_FLAG_SET, lpTimeI, lpTime1, lpTime2, lpVPDfxz[lpSample1], lpVPDfxz[lpSample2],

                /* Standard derivatives */
                ( lpVPDfxz[lpSample2] - lpVPDfxz[lpSample0] ) / ( lpTime2 ),
                ( lpVPDfxz[lpSample3] - lpVPDfxz[lpSample1] ) / ( lpTime3 - lpTime1)

            );

            /* Compute interpolation values - Frame x-component y-vector */
            lpOrientation.qrfyx = li_cubic( LI_CUBIC_FLAG_SET, lpTimeI, lpTime1, lpTime2, lpVPDfyx[lpSample1], lpVPDfyx[lpSample2],

                /* Standard derivatives */
                ( lpVPDfyx[lpSample2] - lpVPDfyx[lpSample0] ) / ( lpTime2 ),
                ( lpVPDfyx[lpSample3] - lpVPDfyx[lpSample1] ) / ( lpTime3 - lpTime1)

            );

            /* Compute interpolation values - Frame y-component y-vector */
            lpOrientation.qrfyy = li_cubic( LI_CUBIC_FLAG_SET, lpTimeI, lpTime1, lpTime2, lpVPDfyy[lpSample1], lpVPDfyy[lpSample2],

                /* Standard derivatives */
                ( lpVPDfyy[lpSample2] - lpVPDfyy[lpSample0] ) / ( lpTime2 ),
                ( lpVPDfyy[lpSample3] - lpVPDfyy[lpSample1] ) / ( lpTime3 - lpTime1)

            );

            /* Compute interpolation values - Frame z-component y-vector */
            lpOrientation.qrfyz = li_cubic( LI_CUBIC_FLAG_SET, lpTimeI, lpTime1, lpTime2, lpVPDfyz[lpSample1], lpVPDfyz[lpSample2],

                /* Standard derivatives */
                ( lpVPDfyz[lpSample2] - lpVPDfyz[lpSample0] ) / ( lpTime2 ),
                ( lpVPDfyz[lpSample3] - lpVPDfyz[lpSample1] ) / ( lpTime3 - lpTime1)

            );

            /* Compute interpolation values - Frame x-component z-vector */
            lpOrientation.qrfzx = li_cubic( LI_CUBIC_FLAG_SET, lpTimeI, lpTime1, lpTime2, lpVPDfzx[lpSample1], lpVPDfzx[lpSample2],

                /* Standard derivatives */
                ( lpVPDfzx[lpSample2] - lpVPDfzx[lpSample0] ) / ( lpTime2 ),
                ( lpVPDfzx[lpSample3] - lpVPDfzx[lpSample1] ) / ( lpTime3 - lpTime1)

            );

            /* Compute interpolation values - Frame y-component z-vector */
            lpOrientation.qrfzy = li_cubic( LI_CUBIC_FLAG_SET, lpTimeI, lpTime1, lpTime2, lpVPDfzy[lpSample1], lpVPDfzy[lpSample2],

                /* Standard derivatives */
                ( lpVPDfzy[lpSample2] - lpVPDfzy[lpSample0] ) / ( lpTime2 ),
                ( lpVPDfzy[lpSample3] - lpVPDfzy[lpSample1] ) / ( lpTime3 - lpTime1)

            );

            /* Compute interpolation values - Frame z-component z-vector */
            lpOrientation.qrfzz = li_cubic( LI_CUBIC_FLAG_SET, lpTimeI, lpTime1, lpTime2, lpVPDfzz[lpSample1], lpVPDfzz[lpSample2],

                /* Standard derivatives */
                ( lpVPDfzz[lpSample2] - lpVPDfzz[lpSample0] ) / ( lpTime2 ),
                ( lpVPDfzz[lpSample3] - lpVPDfzz[lpSample1] ) / ( lpTime3 - lpTime1)

            );

            /* Update query status */
            lpOrientation.qrStatus = LP_TRUE;

        } else {

            /* Update query status */
            lpOrientation.qrStatus = LP_FALSE;

        }

        /* Unallocate buffer memory */
        free( lpVPDfxx );
        free( lpVPDfxy );
        free( lpVPDfxz );
        free( lpVPDfyx );
        free( lpVPDfyy );
        free( lpVPDfyz );
        free( lpVPDfzx );
        free( lpVPDfzy );
        free( lpVPDfzz );
        free( lpVPDsyn );

        /* Return position structure */
        return( lpOrientation );

    }

