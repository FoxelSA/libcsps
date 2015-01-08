/*
 * libcsps - Crossed-signal positioning system library
 *
 * Copyright (c) 2013-2015 FOXEL SA - http://foxel.ch
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
    Source - CSPS query - Position
 */

    lp_Geopos_t lp_query_position_read(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpDevice,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule

    ) {

        /* Stream size variables */
        lp_Size_t lpSize = lp_stream_size( lpPath, lpDevice, lpTag, lpModule );

        /* Returned structure variables */
        lp_Geopos_t lpGeopos = {

            /* Setting query status */
            LP_FALSE,

            /* Initialize data fields */
            lp_Real_s( 0.0 ),
            lp_Real_s( 0.0 ),
            lp_Real_s( 0.0 ),

            /* Stream size variables */
            lpSize,

            /* Stream reading */
            lp_stream_read( lpPath, lpDevice, lpTag, lpModule, LP_STREAM_CPN_LAT, sizeof( lp_Real_t ) * lpSize ),
            lp_stream_read( lpPath, lpDevice, lpTag, lpModule, LP_STREAM_CPN_LON, sizeof( lp_Real_t ) * lpSize ),
            lp_stream_read( lpPath, lpDevice, lpTag, lpModule, LP_STREAM_CPN_ALT, sizeof( lp_Real_t ) * lpSize ),
            lp_stream_read( lpPath, lpDevice, lpTag, lpModule, LP_STREAM_CPN_SYN, sizeof( lp_Time_t ) * lpSize )

        };

        /* Return structure */
        return( lpGeopos );

    }

    lp_Void_t lp_query_position_delete( 

        lp_Geopos_t * const lpGeopos 

    ) {

        /* Reset query status */
        lpGeopos->qrStatus = LP_FALSE;

        /* Reset data field */
        lpGeopos->qrLatitude  = lp_Real_s( 0.0 );
        lpGeopos->qrLongitude = lp_Real_s( 0.0 );
        lpGeopos->qrAltitude  = lp_Real_s( 0.0 );

        /* Reset stream size */
        lpGeopos->qrSize = lp_Size_s( 0 );

        /* Unallocate streams */
        lpGeopos->qrStrmlat = lp_stream_delete( lpGeopos->qrStrmlat );
        lpGeopos->qrStrmlon = lp_stream_delete( lpGeopos->qrStrmlon );
        lpGeopos->qrStrmalt = lp_stream_delete( lpGeopos->qrStrmalt );
        lpGeopos->qrStrmsyn = lp_stream_delete( lpGeopos->qrStrmsyn );

    }

    lp_Void_t lp_query_position(

        lp_Geopos_t       * const lpGeopos,
        lp_Time_t   const         lpTimestamp

    ) {

        /* Timestamp index variables */
        lp_Size_t lpParse = lp_Size_s( 0 );

        /* Interpolation sampling nodes variables */
        lp_Size_t lpSample0 = lp_Size_s( 0 );
        lp_Size_t lpSample1 = lp_Size_s( 0 );
        lp_Size_t lpSample2 = lp_Size_s( 0 );
        lp_Size_t lpSample3 = lp_Size_s( 0 );

        /* Interpolation time variables */
        lp_Real_t lpDT1TI = lp_Real_s( 0.0 );
        lp_Real_t lpDT1T2 = lp_Real_s( 0.0 );
        //lp_Real_t lpDT0T2 = lp_Real_s( 0.0 );
        lp_Real_t lpDT1T3 = lp_Real_s( 0.0 );

        lp_Real_t lpDT0T1 = lp_Real_s( 0.0 );

        /* Obtains index of nearest lower or equal timestamp stored in synchronization array */
        if ( ( lpParse = lp_timestamp_index( lpTimestamp, lpGeopos->qrStrmsyn, lpGeopos->qrSize ) ) != LP_TIMESTAMP_FAULT ) {

            /* Cubic interpolation derivative range necessities */
            if ( ( lpParse >= 1 ) && ( lpParse < ( lpGeopos->qrSize - 2 ) ) ) {

                /* Compute quantity interpolation sampling nodes */
                //lpSample0 = LP_RNG( lpParse - 1, 0, lpGeopos->qrSize - lp_Size_s( 1 ) );
                //lpSample1 = LP_RNG( lpParse    , 0, lpGeopos->qrSize - lp_Size_s( 1 ) );
                //lpSample2 = LP_RNG( lpParse + 1, 0, lpGeopos->qrSize - lp_Size_s( 1 ) );
                //lpSample3 = LP_RNG( lpParse + 2, 0, lpGeopos->qrSize - lp_Size_s( 1 ) );
                lpSample0 = lpParse - 1;
                lpSample1 = lpParse;
                lpSample2 = lpParse + 1;
                lpSample3 = lpParse + 2;

                /* Compute time interpolation variable */
                lpDT1TI = lp_timestamp_float( lp_timestamp_diff( lpTimestamp, lpGeopos->qrStrmsyn[lpSample1] ) );

                /* Compute time interpolation sample */
                lpDT1T2 = lp_timestamp_float( lp_timestamp_diff( lpGeopos->qrStrmsyn[lpSample2], lpGeopos->qrStrmsyn[lpSample1] ) );
                //lpDT0T2 = lp_timestamp_float( lp_timestamp_diff( lpGeopos->qrStrmsyn[lpSample2], lpGeopos->qrStrmsyn[lpSample0] ) );
                lpDT1T3 = lp_timestamp_float( lp_timestamp_diff( lpGeopos->qrStrmsyn[lpSample3], lpGeopos->qrStrmsyn[lpSample1] ) );

                lpDT0T1 = lp_timestamp_float( lp_timestamp_diff( lpGeopos->qrStrmsyn[lpSample1], lpGeopos->qrStrmsyn[lpSample0] ) );

                /* Compute interpolation values - Latitude */
                lpGeopos->qrLatitude = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpGeopos->qrStrmlat[lpSample1], lpGeopos->qrStrmlat[lpSample2],

                    /* Standard derivatives */
                    //( lpGeopos->qrStrmlat[lpSample2] - lpGeopos->qrStrmlat[lpSample0] ) / lpDT0T2,
                    //( lpGeopos->qrStrmlat[lpSample3] - lpGeopos->qrStrmlat[lpSample1] ) / lpDT1T3

                    /* Adaptative derivatives */
                    lp_analysis_adaptFDF( - lpDT0T1, lp_Real_s( 0.0 ), lpDT1T2, lpGeopos->qrStrmlat[lpSample0], lpGeopos->qrStrmlat[lpSample1], lpGeopos->qrStrmlat[lpSample2], lp_Real_s( 10.0 ) ),
                    lp_analysis_adaptFDF( + lp_Real_s( 0.0 ), lpDT1T2, lpDT1T3, lpGeopos->qrStrmlat[lpSample1], lpGeopos->qrStrmlat[lpSample2], lpGeopos->qrStrmlat[lpSample3], lp_Real_s( 10.0 ) )

                );

                /* Compute interpolation values - Longitude */
                lpGeopos->qrLongitude = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpGeopos->qrStrmlon[lpSample1], lpGeopos->qrStrmlon[lpSample2],

                    /* Standard derivatives */
                    //( lpGeopos->qrStrmlon[lpSample2] - lpGeopos->qrStrmlon[lpSample0] ) / lpDT0T2,
                    //( lpGeopos->qrStrmlon[lpSample3] - lpGeopos->qrStrmlon[lpSample1] ) / lpDT1T3

                    /* Adaptative derivatives */
                    lp_analysis_adaptFDF( - lpDT0T1, lp_Real_s( 0.0 ), lpDT1T2, lpGeopos->qrStrmlon[lpSample0], lpGeopos->qrStrmlon[lpSample1], lpGeopos->qrStrmlon[lpSample2], lp_Real_s( 10.0 ) ),
                    lp_analysis_adaptFDF( + lp_Real_s( 0.0 ), lpDT1T2, lpDT1T3, lpGeopos->qrStrmlon[lpSample1], lpGeopos->qrStrmlon[lpSample2], lpGeopos->qrStrmlon[lpSample3], lp_Real_s( 10.0 ) )

                );

                /* Compute interpolation values - Altitude */
                lpGeopos->qrAltitude = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpGeopos->qrStrmalt[lpSample1], lpGeopos->qrStrmalt[lpSample2],

                    /* Standard derivatives */
                    //( lpGeopos->qrStrmalt[lpSample2] - lpGeopos->qrStrmalt[lpSample0] ) / lpDT0T2,
                    //( lpGeopos->qrStrmalt[lpSample3] - lpGeopos->qrStrmalt[lpSample1] ) / lpDT1T3

                    /* Adaptative derivatives */
                    lp_analysis_adaptFDF( - lpDT0T1, lp_Real_s( 0.0 ), lpDT1T2, lpGeopos->qrStrmalt[lpSample0], lpGeopos->qrStrmalt[lpSample1], lpGeopos->qrStrmalt[lpSample2], lp_Real_s( 10.0 ) ),
                    lp_analysis_adaptFDF( + lp_Real_s( 0.0 ), lpDT1T2, lpDT1T3, lpGeopos->qrStrmalt[lpSample1], lpGeopos->qrStrmalt[lpSample2], lpGeopos->qrStrmalt[lpSample3], lp_Real_s( 10.0 ) )

                );

                /* Update query status */
                lpGeopos->qrStatus = LP_TRUE;

            } else {

                /* Update query status */
                lpGeopos->qrStatus = LP_FALSE;

            }

        } else {

            /* Update query status */
            lpGeopos->qrStatus = LP_FALSE;

        }

    }

/*
    Source - CSPS query - Orientation
 */

    lp_Orient_t lp_query_orientation_read(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpDevice,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule

    ) {

        /* Stream size variables */
        lp_Size_t lpSize = lp_stream_size( lpPath, lpDevice, lpTag, lpModule );

        /* Returned structure */
        lp_Orient_t lpOrient = {

            /* Setting query status */
            LP_FALSE,

            /* Initialize data fields */
            lp_Real_s( 0.0 ),
            lp_Real_s( 0.0 ),
            lp_Real_s( 0.0 ),
            lp_Real_s( 0.0 ),
            lp_Real_s( 0.0 ),
            lp_Real_s( 0.0 ),
            lp_Real_s( 0.0 ),
            lp_Real_s( 0.0 ),
            lp_Real_s( 0.0 ),

            /* Stream size variables */
            lpSize,

            /* Stream reading */
            lp_stream_read( lpPath, lpDevice, lpTag, lpModule, LP_STREAM_CPN_FXX, sizeof( lp_Real_t ) * lpSize ),
            lp_stream_read( lpPath, lpDevice, lpTag, lpModule, LP_STREAM_CPN_FXY, sizeof( lp_Real_t ) * lpSize ),
            lp_stream_read( lpPath, lpDevice, lpTag, lpModule, LP_STREAM_CPN_FXZ, sizeof( lp_Real_t ) * lpSize ),
            lp_stream_read( lpPath, lpDevice, lpTag, lpModule, LP_STREAM_CPN_FYX, sizeof( lp_Real_t ) * lpSize ),
            lp_stream_read( lpPath, lpDevice, lpTag, lpModule, LP_STREAM_CPN_FYY, sizeof( lp_Real_t ) * lpSize ),
            lp_stream_read( lpPath, lpDevice, lpTag, lpModule, LP_STREAM_CPN_FYZ, sizeof( lp_Real_t ) * lpSize ),
            lp_stream_read( lpPath, lpDevice, lpTag, lpModule, LP_STREAM_CPN_FZX, sizeof( lp_Real_t ) * lpSize ),
            lp_stream_read( lpPath, lpDevice, lpTag, lpModule, LP_STREAM_CPN_FZY, sizeof( lp_Real_t ) * lpSize ),
            lp_stream_read( lpPath, lpDevice, lpTag, lpModule, LP_STREAM_CPN_FZZ, sizeof( lp_Real_t ) * lpSize ),
            lp_stream_read( lpPath, lpDevice, lpTag, lpModule, LP_STREAM_CPN_SYN, sizeof( lp_Time_t ) * lpSize )

        };

        /* Return position structure */
        return( lpOrient );

    }

    lp_Void_t lp_query_orientation_delete(

        lp_Orient_t * const lpOrient

    ) {

        /* Reset query status */
        lpOrient->qrStatus = LP_FALSE;

        /* Reset data field */
        lpOrient->qrfxx = lp_Real_s( 0.0 );
        lpOrient->qrfxy = lp_Real_s( 0.0 );
        lpOrient->qrfxz = lp_Real_s( 0.0 );
        lpOrient->qrfyx = lp_Real_s( 0.0 );
        lpOrient->qrfyy = lp_Real_s( 0.0 );
        lpOrient->qrfyz = lp_Real_s( 0.0 );
        lpOrient->qrfzx = lp_Real_s( 0.0 );
        lpOrient->qrfzy = lp_Real_s( 0.0 );
        lpOrient->qrfzz = lp_Real_s( 0.0 );

        /* Reset stream size */
        lpOrient->qrSize = lp_Size_s( 0 );

        /* Unallocate streams */
        lpOrient->qrStrmfxx = lp_stream_delete( lpOrient->qrStrmfxx );
        lpOrient->qrStrmfxy = lp_stream_delete( lpOrient->qrStrmfxy );
        lpOrient->qrStrmfxz = lp_stream_delete( lpOrient->qrStrmfxz );
        lpOrient->qrStrmfyx = lp_stream_delete( lpOrient->qrStrmfyx );
        lpOrient->qrStrmfyy = lp_stream_delete( lpOrient->qrStrmfyy );
        lpOrient->qrStrmfyz = lp_stream_delete( lpOrient->qrStrmfyz );
        lpOrient->qrStrmfzx = lp_stream_delete( lpOrient->qrStrmfzx );
        lpOrient->qrStrmfzy = lp_stream_delete( lpOrient->qrStrmfzy );
        lpOrient->qrStrmfzz = lp_stream_delete( lpOrient->qrStrmfzz );
        lpOrient->qrStrmsyn = lp_stream_delete( lpOrient->qrStrmsyn );

    }

    lp_Void_t lp_query_orientation(

        lp_Orient_t       * const lpOrient,
        lp_Time_t   const         lpTimestamp

    ) {

        /* Timestamp index variables */
        lp_Size_t lpParse = lp_Size_s( 0 );

        /* Interpolation sampling nodes variables */
        lp_Size_t lpSample0 = lp_Size_s( 0 );
        lp_Size_t lpSample1 = lp_Size_s( 0 );
        lp_Size_t lpSample2 = lp_Size_s( 0 );
        lp_Size_t lpSample3 = lp_Size_s( 0 );

        /* Interpolation time variables */
        lp_Real_t lpDT1TI = lp_Real_s( 0.0 );
        lp_Real_t lpDT1T2 = lp_Real_s( 0.0 );
        lp_Real_t lpDT0T2 = lp_Real_s( 0.0 );
        lp_Real_t lpDT1T3 = lp_Real_s( 0.0 );

        /* Obtains index of nearest lower or equal timestamp stored in synchronization array */
        if ( ( lpParse = lp_timestamp_index( lpTimestamp, lpOrient->qrStrmsyn, lpOrient->qrSize ) ) != LP_TIMESTAMP_FAULT ) {

            /* Compute quantity interpolation sampling nodes */
            lpSample0 = LP_RNG( lpParse - 1, 0, lpOrient->qrSize - lp_Size_s( 1 ) );
            lpSample1 = LP_RNG( lpParse    , 0, lpOrient->qrSize - lp_Size_s( 1 ) );
            lpSample2 = LP_RNG( lpParse + 1, 0, lpOrient->qrSize - lp_Size_s( 1 ) );
            lpSample3 = LP_RNG( lpParse + 2, 0, lpOrient->qrSize - lp_Size_s( 1 ) );

            /* Compute time interpolation variable */
            lpDT1TI = lp_timestamp_float( lp_timestamp_diff( lpTimestamp, lpOrient->qrStrmsyn[lpSample1] ) );

            /* Compute time interpolation sample */
            lpDT1T2 = lp_timestamp_float( lp_timestamp_diff( lpOrient->qrStrmsyn[lpSample2], lpOrient->qrStrmsyn[lpSample1] ) );
            lpDT0T2 = lp_timestamp_float( lp_timestamp_diff( lpOrient->qrStrmsyn[lpSample2], lpOrient->qrStrmsyn[lpSample0] ) );
            lpDT1T3 = lp_timestamp_float( lp_timestamp_diff( lpOrient->qrStrmsyn[lpSample3], lpOrient->qrStrmsyn[lpSample1] ) );

            /* Compute interpolation values - Frame x-component x-vector */
            lpOrient->qrfxx = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpOrient->qrStrmfxx[lpSample1], lpOrient->qrStrmfxx[lpSample2],

                /* Standard derivatives */
                ( lpOrient->qrStrmfxx[lpSample2] - lpOrient->qrStrmfxx[lpSample0] ) / lpDT0T2,
                ( lpOrient->qrStrmfxx[lpSample3] - lpOrient->qrStrmfxx[lpSample1] ) / lpDT1T3

            );

            /* Compute interpolation values - Frame y-component x-vector */
            lpOrient->qrfxy = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpOrient->qrStrmfxy[lpSample1], lpOrient->qrStrmfxy[lpSample2],

                /* Standard derivatives */
                ( lpOrient->qrStrmfxy[lpSample2] - lpOrient->qrStrmfxy[lpSample0] ) / lpDT0T2,
                ( lpOrient->qrStrmfxy[lpSample3] - lpOrient->qrStrmfxy[lpSample1] ) / lpDT1T3

            );

            /* Compute interpolation values - Frame z-component x-vector */
            lpOrient->qrfxz = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpOrient->qrStrmfxz[lpSample1], lpOrient->qrStrmfxz[lpSample2],

                /* Standard derivatives */
                ( lpOrient->qrStrmfxz[lpSample2] - lpOrient->qrStrmfxz[lpSample0] ) / lpDT0T2,
                ( lpOrient->qrStrmfxz[lpSample3] - lpOrient->qrStrmfxz[lpSample1] ) / lpDT1T3

            );

            /* Compute interpolation values - Frame x-component y-vector */
            lpOrient->qrfyx = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpOrient->qrStrmfyx[lpSample1], lpOrient->qrStrmfyx[lpSample2],

                /* Standard derivatives */
                ( lpOrient->qrStrmfyx[lpSample2] - lpOrient->qrStrmfyx[lpSample0] ) / lpDT0T2,
                ( lpOrient->qrStrmfyx[lpSample3] - lpOrient->qrStrmfyx[lpSample1] ) / lpDT1T3

            );

            /* Compute interpolation values - Frame y-component y-vector */
            lpOrient->qrfyy = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpOrient->qrStrmfyy[lpSample1], lpOrient->qrStrmfyy[lpSample2],

                /* Standard derivatives */
                ( lpOrient->qrStrmfyy[lpSample2] - lpOrient->qrStrmfyy[lpSample0] ) / lpDT0T2,
                ( lpOrient->qrStrmfyy[lpSample3] - lpOrient->qrStrmfyy[lpSample1] ) / lpDT1T3

            );

            /* Compute interpolation values - Frame z-component y-vector */
            lpOrient->qrfyz = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpOrient->qrStrmfyz[lpSample1], lpOrient->qrStrmfyz[lpSample2],

                /* Standard derivatives */
                ( lpOrient->qrStrmfyz[lpSample2] - lpOrient->qrStrmfyz[lpSample0] ) / lpDT0T2,
                ( lpOrient->qrStrmfyz[lpSample3] - lpOrient->qrStrmfyz[lpSample1] ) / lpDT1T3

            );

            /* Compute interpolation values - Frame x-component z-vector */
            lpOrient->qrfzx = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpOrient->qrStrmfzx[lpSample1], lpOrient->qrStrmfzx[lpSample2],

                /* Standard derivatives */
                ( lpOrient->qrStrmfzx[lpSample2] - lpOrient->qrStrmfzx[lpSample0] ) / lpDT0T2,
                ( lpOrient->qrStrmfzx[lpSample3] - lpOrient->qrStrmfzx[lpSample1] ) / lpDT1T3

            );

            /* Compute interpolation values - Frame y-component z-vector */
            lpOrient->qrfzy = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpOrient->qrStrmfzy[lpSample1], lpOrient->qrStrmfzy[lpSample2],

                /* Standard derivatives */
                ( lpOrient->qrStrmfzy[lpSample2] - lpOrient->qrStrmfzy[lpSample0] ) / lpDT0T2,
                ( lpOrient->qrStrmfzy[lpSample3] - lpOrient->qrStrmfzy[lpSample1] ) / lpDT1T3

            );

            /* Compute interpolation values - Frame z-component z-vector */
            lpOrient->qrfzz = li_cubic( LI_CUBIC_FLAG_SET, lpDT1TI, lp_Real_s( 0.0 ), lpDT1T2, lpOrient->qrStrmfzz[lpSample1], lpOrient->qrStrmfzz[lpSample2],

                /* Standard derivatives */
                ( lpOrient->qrStrmfzz[lpSample2] - lpOrient->qrStrmfzz[lpSample0] ) / lpDT0T2,
                ( lpOrient->qrStrmfzz[lpSample3] - lpOrient->qrStrmfzz[lpSample1] ) / lpDT1T3

            );

            /* Update query status */
            lpOrient->qrStatus = LP_TRUE;

        } else {

            /* Update query status */
            lpOrient->qrStatus = LP_FALSE;

        }

    }

