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
        const lp_Char_t * const lpTag,
        const lp_Char_t * const lpName,
        const lp_Char_t * const lpPS__

    ) {

        /* Files size */
        lp_Size_t lpSize = lp_Size_s( 0 );

        /* Data buffers */
        lp_Time_t * lpVPDsyn = NULL;

        /* Returned structure */
        lp_QueryTime lpTime;

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, lpTag, lpName, lpPS__, "syn" ) / sizeof( lp_Time_t );

        /* Read streams data */
        lpVPDsyn = lp_stream_read( lpPath, lpTag, lpName, lpPS__, "syn", sizeof( lp_Time_t ) * lpSize );

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
        const lp_Char_t * const lpTag,
        const lp_Char_t * const lpName,
        const lp_Char_t * const lpPS__,
        lp_Time_t lpTimestamp

    ) {

        /* Query variables */
        lp_Size_t lpParse = lp_Size_s( 0 );

        /* Files size */
        lp_Size_t lpSize = lp_Size_s( 0 );

        /* Interpolation parameters */
        lp_Size_t lpShift0 = lp_Size_s( 0 );
        lp_Size_t lpShift1 = lp_Size_s( 0 );
        lp_Size_t lpShift2 = lp_Size_s( 0 );
        lp_Size_t lpShift3 = lp_Size_s( 0 );

        /* Data buffers */
        lp_Real_t * lpVPDlat = NULL;
        lp_Real_t * lpVPDlon = NULL;
        lp_Real_t * lpVPDalt = NULL;
        lp_Time_t * lpVPDsyn = NULL;

        /* Returned structure */
        lp_QueryPosition lpPosition;

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, lpTag, lpName, lpPS__, "syn" ) / sizeof( lp_Time_t );

        /* Read streams data */
        lpVPDlat = lp_stream_read( lpPath, lpTag, lpName, lpPS__, "lat", sizeof( lp_Real_t ) * lpSize );
        lpVPDlon = lp_stream_read( lpPath, lpTag, lpName, lpPS__, "lon", sizeof( lp_Real_t ) * lpSize );
        lpVPDalt = lp_stream_read( lpPath, lpTag, lpName, lpPS__, "alt", sizeof( lp_Real_t ) * lpSize );
        lpVPDsyn = lp_stream_read( lpPath, lpTag, lpName, lpPS__, "syn", sizeof( lp_Time_t ) * lpSize );

        /* Verify time range */
        if ( ( lp_timestamp_ge( lpTimestamp, lpVPDsyn[0] ) == LP_TRUE ) && ( lp_timestamp_ge( lpVPDsyn[lpSize-1], lpTimestamp ) == LP_TRUE ) ) {

            /* Search position by timestamp */
            while ( lp_timestamp_ge( lpTimestamp, lpVPDsyn[++lpParse] ) == LP_TRUE );

            /* Create interpolation parameters */
            if ( lpParse == lp_Size_s( 0 ) ) {

                /* Left boundary correction */
                lpShift0 = lp_Size_s( 0 );
                lpShift1 = lp_Size_s( 0 );
                lpShift2 = lp_Size_s( 1 );
                lpShift3 = lp_Size_s( 2 );

            } else if ( lpParse == ( lpSize - lp_Size_s( 1 ) ) ) {

                /* Right boundary correction */
                lpShift0 = lpSize - lp_Size_s( 3 );
                lpShift1 = lpSize - lp_Size_s( 2 );
                lpShift2 = lpSize - lp_Size_s( 1 );
                lpShift3 = lpSize - lp_Size_s( 1 );

            } else {

                /* Usual range parameters */
                lpShift0 = lpParse - lp_Size_s( 2 );
                lpShift1 = lpParse - lp_Size_s( 1 );
                lpShift2 = lpParse;
                lpShift3 = lpParse + lp_Size_s( 1 );

            }

            /* Compute interpolation values - Latitude */
            lpPosition.qrLatitude = lp_math_spline( LP_MATH_SPLINE_RESET,

                lp_timestamp_float( lp_timestamp_diff( lpTimestamp       , lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift0], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift1], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift2], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift3], lpVPDsyn[lpShift0] ) ),
                lpVPDlat[lpShift0],
                lpVPDlat[lpShift1],
                lpVPDlat[lpShift2],
                lpVPDlat[lpShift3]

            );

            /* Compute interpolation values - Longitude */
            lpPosition.qrLongitude = lp_math_spline( LP_MATH_SPLINE_RESET,

                lp_timestamp_float( lp_timestamp_diff( lpTimestamp       , lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift0], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift1], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift2], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift3], lpVPDsyn[lpShift0] ) ),
                lpVPDlon[lpShift0],
                lpVPDlon[lpShift1],
                lpVPDlon[lpShift2],
                lpVPDlon[lpShift3]

            );

            /* Compute interpolation values - Altitude */
            lpPosition.qrAltitude = lp_math_spline( LP_MATH_SPLINE_RESET,

                lp_timestamp_float( lp_timestamp_diff( lpTimestamp       , lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift0], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift1], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift2], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift3], lpVPDsyn[lpShift0] ) ),
                lpVPDalt[lpShift0],
                lpVPDalt[lpShift1],
                lpVPDalt[lpShift2],
                lpVPDalt[lpShift3]

            );

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
        const lp_Char_t * const lpTag,
        const lp_Char_t * const lpName,
        const lp_Char_t * const lpPS__,
        lp_Time_t lpTimestamp

    ) {

        /* Query variables */
        lp_Size_t lpParse = lp_Size_s( 0 );

        /* Files size */
        lp_Size_t lpSize = lp_Size_s( 0 );

        /* Interpolation parameters */
        lp_Size_t lpShift0 = lp_Size_s( 0 );
        lp_Size_t lpShift1 = lp_Size_s( 0 );
        lp_Size_t lpShift2 = lp_Size_s( 0 );
        lp_Size_t lpShift3 = lp_Size_s( 0 );

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

        /* Returned structure */
        lp_QueryOrientation lpOrientation;

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, lpTag, lpName, lpPS__, "syn" ) / sizeof( lp_Time_t );

        /* Read streams data */
        lpVPDfxx = lp_stream_read( lpPath, lpTag, lpName, lpPS__, "fxx", sizeof( lp_Real_t ) * lpSize );
        lpVPDfxy = lp_stream_read( lpPath, lpTag, lpName, lpPS__, "fxy", sizeof( lp_Real_t ) * lpSize );
        lpVPDfxz = lp_stream_read( lpPath, lpTag, lpName, lpPS__, "fxz", sizeof( lp_Real_t ) * lpSize );
        lpVPDfyx = lp_stream_read( lpPath, lpTag, lpName, lpPS__, "fyx", sizeof( lp_Real_t ) * lpSize );
        lpVPDfyy = lp_stream_read( lpPath, lpTag, lpName, lpPS__, "fyy", sizeof( lp_Real_t ) * lpSize );
        lpVPDfyz = lp_stream_read( lpPath, lpTag, lpName, lpPS__, "fyz", sizeof( lp_Real_t ) * lpSize );
        lpVPDfzx = lp_stream_read( lpPath, lpTag, lpName, lpPS__, "fzx", sizeof( lp_Real_t ) * lpSize );
        lpVPDfzy = lp_stream_read( lpPath, lpTag, lpName, lpPS__, "fzy", sizeof( lp_Real_t ) * lpSize );
        lpVPDfzz = lp_stream_read( lpPath, lpTag, lpName, lpPS__, "fzz", sizeof( lp_Real_t ) * lpSize );
        lpVPDsyn = lp_stream_read( lpPath, lpTag, lpName, lpPS__, "syn", sizeof( lp_Time_t ) * lpSize );

        /* Verify time range */
        if ( ( lp_timestamp_ge( lpTimestamp, lpVPDsyn[0] ) == LP_TRUE ) && ( lp_timestamp_ge( lpVPDsyn[lpSize-1], lpTimestamp ) == LP_TRUE ) ) {

            /* Search position by timestamp */
            while ( lp_timestamp_ge( lpTimestamp, lpVPDsyn[++lpParse] ) == LP_TRUE );

            /* Create interpolation parameters */
            if ( lpParse == lp_Size_s( 0 ) ) {

                /* Left boundary correction */
                lpShift0 = lp_Size_s( 0 );
                lpShift1 = lp_Size_s( 0 );
                lpShift2 = lp_Size_s( 1 );
                lpShift3 = lp_Size_s( 2 );

            } else if ( lpParse == ( lpSize - lp_Size_s( 1 ) ) ) {

                /* Right boundary correction */
                lpShift0 = lpSize - lp_Size_s( 3 );
                lpShift1 = lpSize - lp_Size_s( 2 );
                lpShift2 = lpSize - lp_Size_s( 1 );
                lpShift3 = lpSize - lp_Size_s( 1 );

            } else {

                /* Usual range parameters */
                lpShift0 = lpParse - lp_Size_s( 2 );
                lpShift1 = lpParse - lp_Size_s( 1 );
                lpShift2 = lpParse;
                lpShift3 = lpParse + lp_Size_s( 1 );

            }

            /* Compute interpolation values - Frame x-component x-vector */
            lpOrientation.qrfxx = lp_math_spline( LP_MATH_SPLINE_RESET,

                lp_timestamp_float( lp_timestamp_diff( lpTimestamp         , lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift0], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift1], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift2], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift3], lpVPDsyn[lpShift0] ) ),
                lpVPDfxx[lpShift0],
                lpVPDfxx[lpShift1],
                lpVPDfxx[lpShift2],
                lpVPDfxx[lpShift3]

            );

            /* Compute interpolation values - Frame y-component x-vector */
            lpOrientation.qrfxy = lp_math_spline( LP_MATH_SPLINE_RESET,

                lp_timestamp_float( lp_timestamp_diff( lpTimestamp         , lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift0], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift1], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift2], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift3], lpVPDsyn[lpShift0] ) ),
                lpVPDfxy[lpShift0],
                lpVPDfxy[lpShift1],
                lpVPDfxy[lpShift2],
                lpVPDfxy[lpShift3]

            );

            /* Compute interpolation values - Frame z-component x-vector */
            lpOrientation.qrfxz = lp_math_spline( LP_MATH_SPLINE_RESET,

                lp_timestamp_float( lp_timestamp_diff( lpTimestamp         , lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift0], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift1], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift2], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift3], lpVPDsyn[lpShift0] ) ),
                lpVPDfxz[lpShift0],
                lpVPDfxz[lpShift1],
                lpVPDfxz[lpShift2],
                lpVPDfxz[lpShift3]

            );

            /* Compute interpolation values - Frame x-component y-vector */
            lpOrientation.qrfyx = lp_math_spline( LP_MATH_SPLINE_RESET,

                lp_timestamp_float( lp_timestamp_diff( lpTimestamp         , lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift0], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift1], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift2], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift3], lpVPDsyn[lpShift0] ) ),
                lpVPDfyx[lpShift0],
                lpVPDfyx[lpShift1],
                lpVPDfyx[lpShift2],
                lpVPDfyx[lpShift3]

            );

            /* Compute interpolation values - Frame y-component y-vector */
            lpOrientation.qrfyy = lp_math_spline( LP_MATH_SPLINE_RESET,

                lp_timestamp_float( lp_timestamp_diff( lpTimestamp         , lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift0], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift1], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift2], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift3], lpVPDsyn[lpShift0] ) ),
                lpVPDfyy[lpShift0],
                lpVPDfyy[lpShift1],
                lpVPDfyy[lpShift2],
                lpVPDfyy[lpShift3]

            );

            /* Compute interpolation values - Frame z-component y-vector */
            lpOrientation.qrfyz = lp_math_spline( LP_MATH_SPLINE_RESET,

                lp_timestamp_float( lp_timestamp_diff( lpTimestamp         , lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift0], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift1], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift2], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift3], lpVPDsyn[lpShift0] ) ),
                lpVPDfyz[lpShift0],
                lpVPDfyz[lpShift1],
                lpVPDfyz[lpShift2],
                lpVPDfyz[lpShift3]

            );

            /* Compute interpolation values - Frame x-component z-vector */
            lpOrientation.qrfzx = lp_math_spline( LP_MATH_SPLINE_RESET,

                lp_timestamp_float( lp_timestamp_diff( lpTimestamp         , lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift0], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift1], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift2], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift3], lpVPDsyn[lpShift0] ) ),
                lpVPDfzx[lpShift0],
                lpVPDfzx[lpShift1],
                lpVPDfzx[lpShift2],
                lpVPDfzx[lpShift3]

            );

            /* Compute interpolation values - Frame y-component z-vector */
            lpOrientation.qrfzy = lp_math_spline( LP_MATH_SPLINE_RESET,

                lp_timestamp_float( lp_timestamp_diff( lpTimestamp         , lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift0], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift1], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift2], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift3], lpVPDsyn[lpShift0] ) ),
                lpVPDfzy[lpShift0],
                lpVPDfzy[lpShift1],
                lpVPDfzy[lpShift2],
                lpVPDfzy[lpShift3]

            );

            /* Compute interpolation values - Frame z-component z-vector */
            lpOrientation.qrfzz = lp_math_spline( LP_MATH_SPLINE_RESET,

                lp_timestamp_float( lp_timestamp_diff( lpTimestamp         , lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift0], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift1], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift2], lpVPDsyn[lpShift0] ) ),
                lp_timestamp_float( lp_timestamp_diff( lpVPDsyn[lpShift3], lpVPDsyn[lpShift0] ) ),
                lpVPDfzz[lpShift0],
                lpVPDfzz[lpShift1],
                lpVPDfzz[lpShift2],
                lpVPDfzz[lpShift3]

            );

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

