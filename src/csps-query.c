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

    csps_QueryTime csps_query_time(

        const csps_Char_t * const cspsPath,
        const csps_Char_t * const cspsTag,
        const csps_Char_t * const cspsName,
        const csps_Char_t * const cspsPS__

    ) {

        /* Files size */
        csps_Size_t cspsSize = csps_Size_s( 0 );

        /* Data buffers */
        csps_Time_t * cspsVPDsyn = NULL;

        /* Returned structure */
        csps_QueryTime cspsTime;

        /* Obtain stream size */
        cspsSize = csps_stream_size( cspsPath, cspsTag, cspsName, cspsPS__, "syn" ) / sizeof( csps_Time_t );

        /* Read streams data */
        cspsVPDsyn = csps_stream_read( cspsPath, cspsTag, cspsName, cspsPS__, "syn", sizeof( csps_Time_t ) * cspsSize );

        /* Extract timestamp boundaries */
        cspsTime.qrInitial = cspsVPDsyn[0];
        cspsTime.qrFinal   = cspsVPDsyn[cspsSize-1];

        /* Unallocate buffer memory */
        free( cspsVPDsyn );

        /* Return time structure */
        return( cspsTime );

    }

/*
    Source - CSPS query - Position
 */

    csps_QueryPosition csps_query_position_by_timestamp(

        const csps_Char_t * const cspsPath,
        const csps_Char_t * const cspsTag,
        const csps_Char_t * const cspsName,
        const csps_Char_t * const cspsPS__,
        csps_Time_t cspsTimestamp

    ) {

        /* Query variables */
        csps_Size_t cspsParse = csps_Size_s( 0 );

        /* Files size */
        csps_Size_t cspsSize = csps_Size_s( 0 );

        /* Interpolation parameters */
        csps_Size_t cspsShift0 = csps_Size_s( 0 );
        csps_Size_t cspsShift1 = csps_Size_s( 0 );
        csps_Size_t cspsShift2 = csps_Size_s( 0 );
        csps_Size_t cspsShift3 = csps_Size_s( 0 );

        /* Data buffers */
        csps_Real_t * cspsVPDlat = NULL;
        csps_Real_t * cspsVPDlon = NULL;
        csps_Real_t * cspsVPDalt = NULL;
        csps_Time_t * cspsVPDsyn = NULL;

        /* Returned structure */
        csps_QueryPosition cspsPosition;

        /* Obtain stream size */
        cspsSize = csps_stream_size( cspsPath, cspsTag, cspsName, cspsPS__, "syn" ) / sizeof( csps_Time_t );

        /* Read streams data */
        cspsVPDlat = csps_stream_read( cspsPath, cspsTag, cspsName, cspsPS__, "lat", sizeof( csps_Real_t ) * cspsSize );
        cspsVPDlon = csps_stream_read( cspsPath, cspsTag, cspsName, cspsPS__, "lon", sizeof( csps_Real_t ) * cspsSize );
        cspsVPDalt = csps_stream_read( cspsPath, cspsTag, cspsName, cspsPS__, "alt", sizeof( csps_Real_t ) * cspsSize );
        cspsVPDsyn = csps_stream_read( cspsPath, cspsTag, cspsName, cspsPS__, "syn", sizeof( csps_Time_t ) * cspsSize );

        /* Verify time range */
        if ( ( csps_timestamp_ge( cspsTimestamp, cspsVPDsyn[0] ) == CSPS_TRUE ) && ( csps_timestamp_ge( cspsVPDsyn[cspsSize-1], cspsTimestamp ) == CSPS_TRUE ) ) {

            /* Search position by timestamp */
            while ( csps_timestamp_ge( cspsTimestamp, cspsVPDsyn[++cspsParse] ) == CSPS_TRUE );

            /* Create interpolation parameters */
            if ( cspsParse == csps_Size_s( 0 ) ) {

                /* Left boundary correction */
                cspsShift0 = csps_Size_s( 0 );
                cspsShift1 = csps_Size_s( 0 );
                cspsShift2 = csps_Size_s( 1 );
                cspsShift3 = csps_Size_s( 2 );

            } else if ( cspsParse == ( cspsSize - csps_Size_s( 1 ) ) ) {

                /* Right boundary correction */
                cspsShift0 = cspsSize - csps_Size_s( 3 );
                cspsShift1 = cspsSize - csps_Size_s( 2 );
                cspsShift2 = cspsSize - csps_Size_s( 1 );
                cspsShift3 = cspsSize - csps_Size_s( 1 );

            } else {

                /* Usual range parameters */
                cspsShift0 = cspsParse - csps_Size_s( 2 );
                cspsShift1 = cspsParse - csps_Size_s( 1 );
                cspsShift2 = cspsParse;
                cspsShift3 = cspsParse + csps_Size_s( 1 );

            }

            /* Compute interpolation values - Latitude */
            cspsPosition.qrLatitude = csps_math_spline( CSPS_MATH_SPLINE_RESET,

                csps_timestamp_float( csps_timestamp_diff( cspsTimestamp         , cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift0], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift1], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift2], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift3], cspsVPDsyn[cspsShift0] ) ),
                cspsVPDlat[cspsShift0],
                cspsVPDlat[cspsShift1],
                cspsVPDlat[cspsShift2],
                cspsVPDlat[cspsShift3]

            );

            /* Compute interpolation values - Longitude */
            cspsPosition.qrLongitude = csps_math_spline( CSPS_MATH_SPLINE_RESET,

                csps_timestamp_float( csps_timestamp_diff( cspsTimestamp         , cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift0], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift1], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift2], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift3], cspsVPDsyn[cspsShift0] ) ),
                cspsVPDlon[cspsShift0],
                cspsVPDlon[cspsShift1],
                cspsVPDlon[cspsShift2],
                cspsVPDlon[cspsShift3]

            );

            /* Compute interpolation values - Altitude */
            cspsPosition.qrAltitude = csps_math_spline( CSPS_MATH_SPLINE_RESET,

                csps_timestamp_float( csps_timestamp_diff( cspsTimestamp         , cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift0], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift1], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift2], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift3], cspsVPDsyn[cspsShift0] ) ),
                cspsVPDalt[cspsShift0],
                cspsVPDalt[cspsShift1],
                cspsVPDalt[cspsShift2],
                cspsVPDalt[cspsShift3]

            );

        }

        /* Unallocate buffer memory */
        free( cspsVPDlat );
        free( cspsVPDlon );
        free( cspsVPDalt );
        free( cspsVPDsyn );

        /* Return position structure */
        return( cspsPosition );

    }

/*
    Source - CSPS query - Orientation
 */

    csps_QueryOrientation csps_query_orientation_by_timestamp(

        const csps_Char_t * const cspsPath,
        const csps_Char_t * const cspsTag,
        const csps_Char_t * const cspsName,
        const csps_Char_t * const cspsPS__,
        csps_Time_t cspsTimestamp

    ) {

        /* Query variables */
        csps_Size_t cspsParse = csps_Size_s( 0 );

        /* Files size */
        csps_Size_t cspsSize = csps_Size_s( 0 );

        /* Interpolation parameters */
        csps_Size_t cspsShift0 = csps_Size_s( 0 );
        csps_Size_t cspsShift1 = csps_Size_s( 0 );
        csps_Size_t cspsShift2 = csps_Size_s( 0 );
        csps_Size_t cspsShift3 = csps_Size_s( 0 );

        /* Data buffers */
        csps_Real_t * cspsVPDfxx = NULL;
        csps_Real_t * cspsVPDfxy = NULL;
        csps_Real_t * cspsVPDfxz = NULL;
        csps_Real_t * cspsVPDfyx = NULL;
        csps_Real_t * cspsVPDfyy = NULL;
        csps_Real_t * cspsVPDfyz = NULL;
        csps_Real_t * cspsVPDfzx = NULL;
        csps_Real_t * cspsVPDfzy = NULL;
        csps_Real_t * cspsVPDfzz = NULL;
        csps_Time_t * cspsVPDsyn = NULL;

        /* Returned structure */
        csps_QueryOrientation cspsOrientation;

        /* Obtain stream size */
        cspsSize = csps_stream_size( cspsPath, cspsTag, cspsName, cspsPS__, "syn" ) / sizeof( csps_Time_t );

        /* Read streams data */
        cspsVPDfxx = csps_stream_read( cspsPath, cspsTag, cspsName, cspsPS__, "fxx", sizeof( csps_Real_t ) * cspsSize );
        cspsVPDfxy = csps_stream_read( cspsPath, cspsTag, cspsName, cspsPS__, "fxy", sizeof( csps_Real_t ) * cspsSize );
        cspsVPDfxz = csps_stream_read( cspsPath, cspsTag, cspsName, cspsPS__, "fxz", sizeof( csps_Real_t ) * cspsSize );
        cspsVPDfyx = csps_stream_read( cspsPath, cspsTag, cspsName, cspsPS__, "fyx", sizeof( csps_Real_t ) * cspsSize );
        cspsVPDfyy = csps_stream_read( cspsPath, cspsTag, cspsName, cspsPS__, "fyy", sizeof( csps_Real_t ) * cspsSize );
        cspsVPDfyz = csps_stream_read( cspsPath, cspsTag, cspsName, cspsPS__, "fyz", sizeof( csps_Real_t ) * cspsSize );
        cspsVPDfzx = csps_stream_read( cspsPath, cspsTag, cspsName, cspsPS__, "fzx", sizeof( csps_Real_t ) * cspsSize );
        cspsVPDfzy = csps_stream_read( cspsPath, cspsTag, cspsName, cspsPS__, "fzy", sizeof( csps_Real_t ) * cspsSize );
        cspsVPDfzz = csps_stream_read( cspsPath, cspsTag, cspsName, cspsPS__, "fzz", sizeof( csps_Real_t ) * cspsSize );
        cspsVPDsyn = csps_stream_read( cspsPath, cspsTag, cspsName, cspsPS__, "syn", sizeof( csps_Time_t ) * cspsSize );

        /* Verify time range */
        if ( ( csps_timestamp_ge( cspsTimestamp, cspsVPDsyn[0] ) == CSPS_TRUE ) && ( csps_timestamp_ge( cspsVPDsyn[cspsSize-1], cspsTimestamp ) == CSPS_TRUE ) ) {

            /* Search position by timestamp */
            while ( csps_timestamp_ge( cspsTimestamp, cspsVPDsyn[++cspsParse] ) == CSPS_TRUE );

            /* Create interpolation parameters */
            if ( cspsParse == csps_Size_s( 0 ) ) {

                /* Left boundary correction */
                cspsShift0 = csps_Size_s( 0 );
                cspsShift1 = csps_Size_s( 0 );
                cspsShift2 = csps_Size_s( 1 );
                cspsShift3 = csps_Size_s( 2 );

            } else if ( cspsParse == ( cspsSize - csps_Size_s( 1 ) ) ) {

                /* Right boundary correction */
                cspsShift0 = cspsSize - csps_Size_s( 3 );
                cspsShift1 = cspsSize - csps_Size_s( 2 );
                cspsShift2 = cspsSize - csps_Size_s( 1 );
                cspsShift3 = cspsSize - csps_Size_s( 1 );

            } else {

                /* Usual range parameters */
                cspsShift0 = cspsParse - csps_Size_s( 2 );
                cspsShift1 = cspsParse - csps_Size_s( 1 );
                cspsShift2 = cspsParse;
                cspsShift3 = cspsParse + csps_Size_s( 1 );

            }

            /* Compute interpolation values - Frame x-component x-vector */
            cspsOrientation.qrfxx = csps_math_spline( CSPS_MATH_SPLINE_RESET,

                csps_timestamp_float( csps_timestamp_diff( cspsTimestamp         , cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift0], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift1], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift2], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift3], cspsVPDsyn[cspsShift0] ) ),
                cspsVPDfxx[cspsShift0],
                cspsVPDfxx[cspsShift1],
                cspsVPDfxx[cspsShift2],
                cspsVPDfxx[cspsShift3]

            );

            /* Compute interpolation values - Frame y-component x-vector */
            cspsOrientation.qrfxy = csps_math_spline( CSPS_MATH_SPLINE_RESET,

                csps_timestamp_float( csps_timestamp_diff( cspsTimestamp         , cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift0], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift1], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift2], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift3], cspsVPDsyn[cspsShift0] ) ),
                cspsVPDfxy[cspsShift0],
                cspsVPDfxy[cspsShift1],
                cspsVPDfxy[cspsShift2],
                cspsVPDfxy[cspsShift3]

            );

            /* Compute interpolation values - Frame z-component x-vector */
            cspsOrientation.qrfxz = csps_math_spline( CSPS_MATH_SPLINE_RESET,

                csps_timestamp_float( csps_timestamp_diff( cspsTimestamp         , cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift0], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift1], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift2], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift3], cspsVPDsyn[cspsShift0] ) ),
                cspsVPDfxz[cspsShift0],
                cspsVPDfxz[cspsShift1],
                cspsVPDfxz[cspsShift2],
                cspsVPDfxz[cspsShift3]

            );

            /* Compute interpolation values - Frame x-component y-vector */
            cspsOrientation.qrfyx = csps_math_spline( CSPS_MATH_SPLINE_RESET,

                csps_timestamp_float( csps_timestamp_diff( cspsTimestamp         , cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift0], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift1], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift2], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift3], cspsVPDsyn[cspsShift0] ) ),
                cspsVPDfyx[cspsShift0],
                cspsVPDfyx[cspsShift1],
                cspsVPDfyx[cspsShift2],
                cspsVPDfyx[cspsShift3]

            );

            /* Compute interpolation values - Frame y-component y-vector */
            cspsOrientation.qrfyy = csps_math_spline( CSPS_MATH_SPLINE_RESET,

                csps_timestamp_float( csps_timestamp_diff( cspsTimestamp         , cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift0], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift1], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift2], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift3], cspsVPDsyn[cspsShift0] ) ),
                cspsVPDfyy[cspsShift0],
                cspsVPDfyy[cspsShift1],
                cspsVPDfyy[cspsShift2],
                cspsVPDfyy[cspsShift3]

            );

            /* Compute interpolation values - Frame z-component y-vector */
            cspsOrientation.qrfyz = csps_math_spline( CSPS_MATH_SPLINE_RESET,

                csps_timestamp_float( csps_timestamp_diff( cspsTimestamp         , cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift0], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift1], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift2], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift3], cspsVPDsyn[cspsShift0] ) ),
                cspsVPDfyz[cspsShift0],
                cspsVPDfyz[cspsShift1],
                cspsVPDfyz[cspsShift2],
                cspsVPDfyz[cspsShift3]

            );

            /* Compute interpolation values - Frame x-component z-vector */
            cspsOrientation.qrfzx = csps_math_spline( CSPS_MATH_SPLINE_RESET,

                csps_timestamp_float( csps_timestamp_diff( cspsTimestamp         , cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift0], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift1], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift2], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift3], cspsVPDsyn[cspsShift0] ) ),
                cspsVPDfzx[cspsShift0],
                cspsVPDfzx[cspsShift1],
                cspsVPDfzx[cspsShift2],
                cspsVPDfzx[cspsShift3]

            );

            /* Compute interpolation values - Frame y-component z-vector */
            cspsOrientation.qrfzy = csps_math_spline( CSPS_MATH_SPLINE_RESET,

                csps_timestamp_float( csps_timestamp_diff( cspsTimestamp         , cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift0], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift1], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift2], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift3], cspsVPDsyn[cspsShift0] ) ),
                cspsVPDfzy[cspsShift0],
                cspsVPDfzy[cspsShift1],
                cspsVPDfzy[cspsShift2],
                cspsVPDfzy[cspsShift3]

            );

            /* Compute interpolation values - Frame z-component z-vector */
            cspsOrientation.qrfzz = csps_math_spline( CSPS_MATH_SPLINE_RESET,

                csps_timestamp_float( csps_timestamp_diff( cspsTimestamp         , cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift0], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift1], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift2], cspsVPDsyn[cspsShift0] ) ),
                csps_timestamp_float( csps_timestamp_diff( cspsVPDsyn[cspsShift3], cspsVPDsyn[cspsShift0] ) ),
                cspsVPDfzz[cspsShift0],
                cspsVPDfzz[cspsShift1],
                cspsVPDfzz[cspsShift2],
                cspsVPDfzz[cspsShift3]

            );

        }

        /* Unallocate buffer memory */
        free( cspsVPDfxx );
        free( cspsVPDfxy );
        free( cspsVPDfxz );
        free( cspsVPDfyx );
        free( cspsVPDfyy );
        free( cspsVPDfyz );
        free( cspsVPDfzx );
        free( cspsVPDfzy );
        free( cspsVPDfzz );
        free( cspsVPDsyn );

        /* Return position structure */
        return( cspsOrientation );

    }

