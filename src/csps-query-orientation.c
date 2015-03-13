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

    # include "csps-query-orientation.h"

/*
    Source - CSPS query - Orientation - Handle
 */

    lp_Orient_t lp_query_orientation_origin(

        lp_Char_t const * const lpPath

    ) {

        /* Device and module switch variables */
        lp_Char_t lpDevice[LP_STR_LEN] = { '\0' };
        lp_Char_t lpModule[LP_STR_LEN] = { '\0' };

        /* Retrieve device and module switch through origin directive */
        lp_system_origin( lpPath, LP_SYSTEM_ORIENTATION, lpDevice, lpModule );

        /* Create and return orientation query structure */
        return( lp_query_orientation_create( lpPath, lpDevice, lpModule ) );

    }

    lp_Orient_t lp_query_orientation_create(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule

    ) {
        /* Returned structure variables */
        lp_Orient_t lpOrient;

        /* Initialize structure status */
        lpOrient.qrState  = LP_FALSE;
        lpOrient.qrStatus = LP_FALSE;  
        
        /* Initialize query fields */
        lpOrient.qrfxx = lp_Real_s( 0.0 );
        lpOrient.qrfxy = lp_Real_s( 0.0 );
        lpOrient.qrfxz = lp_Real_s( 0.0 );
        lpOrient.qrfyx = lp_Real_s( 0.0 );
        lpOrient.qrfyy = lp_Real_s( 0.0 );
        lpOrient.qrfyz = lp_Real_s( 0.0 );
        lpOrient.qrfzx = lp_Real_s( 0.0 );
        lpOrient.qrfzy = lp_Real_s( 0.0 );
        lpOrient.qrfzz = lp_Real_s( 0.0 );

        /* Initialize query complements */
        lpOrient.qrWeak = lp_Enum_s( 0 );

        /* Retrieve stream size */
        lpOrient.qrSize = lp_stream_size( lpPath, lpTag, lpModule );

        /* Streams component importation */
        lpOrient.qrStrmfxx = lp_stream_read( lpPath, lpTag, lpModule, LP_STREAM_CPN_FXX, sizeof( lp_Real_t ) * lpOrient.qrSize );
        lpOrient.qrStrmfxy = lp_stream_read( lpPath, lpTag, lpModule, LP_STREAM_CPN_FXY, sizeof( lp_Real_t ) * lpOrient.qrSize );
        lpOrient.qrStrmfxz = lp_stream_read( lpPath, lpTag, lpModule, LP_STREAM_CPN_FXZ, sizeof( lp_Real_t ) * lpOrient.qrSize );
        lpOrient.qrStrmfyx = lp_stream_read( lpPath, lpTag, lpModule, LP_STREAM_CPN_FYX, sizeof( lp_Real_t ) * lpOrient.qrSize );
        lpOrient.qrStrmfyy = lp_stream_read( lpPath, lpTag, lpModule, LP_STREAM_CPN_FYY, sizeof( lp_Real_t ) * lpOrient.qrSize );
        lpOrient.qrStrmfyz = lp_stream_read( lpPath, lpTag, lpModule, LP_STREAM_CPN_FYZ, sizeof( lp_Real_t ) * lpOrient.qrSize );
        lpOrient.qrStrmfzx = lp_stream_read( lpPath, lpTag, lpModule, LP_STREAM_CPN_FZX, sizeof( lp_Real_t ) * lpOrient.qrSize );
        lpOrient.qrStrmfzy = lp_stream_read( lpPath, lpTag, lpModule, LP_STREAM_CPN_FZY, sizeof( lp_Real_t ) * lpOrient.qrSize );
        lpOrient.qrStrmfzz = lp_stream_read( lpPath, lpTag, lpModule, LP_STREAM_CPN_FZZ, sizeof( lp_Real_t ) * lpOrient.qrSize );
        lpOrient.qrStrmSyn = lp_stream_read( lpPath, lpTag, lpModule, LP_STREAM_CPN_SYN, sizeof( lp_Time_t ) * lpOrient.qrSize );

        /* Verify structure state */
        if ( 

            ( lpOrient.qrStrmfxx == NULL ) || 
            ( lpOrient.qrStrmfxy == NULL ) || 
            ( lpOrient.qrStrmfxz == NULL ) || 
            ( lpOrient.qrStrmfyx == NULL ) || 
            ( lpOrient.qrStrmfyy == NULL ) || 
            ( lpOrient.qrStrmfyz == NULL ) || 
            ( lpOrient.qrStrmfzx == NULL ) || 
            ( lpOrient.qrStrmfzy == NULL ) || 
            ( lpOrient.qrStrmfzz == NULL ) || 
            ( lpOrient.qrStrmSyn == NULL )

        ) {

            /* Delete structure */
            lp_query_orientation_delete( & lpOrient );

        } else {

            /* Update structure state */
            lpOrient.qrState = LP_TRUE;

        }        

        /* Return position structure */
        return( lpOrient );

    }

    lp_Void_t lp_query_orientation_delete(

        lp_Orient_t * const lpOrient

    ) {

        /* Reset structure status */
        lpOrient->qrState  = LP_FALSE;
        lpOrient->qrStatus = LP_FALSE;

        /* Reset stream size */
        lpOrient->qrSize = lp_Size_s( 0 );

        /* Unallocate stream components */
        lpOrient->qrStrmfxx = lp_stream_delete( lpOrient->qrStrmfxx );
        lpOrient->qrStrmfxy = lp_stream_delete( lpOrient->qrStrmfxy );
        lpOrient->qrStrmfxz = lp_stream_delete( lpOrient->qrStrmfxz );
        lpOrient->qrStrmfyx = lp_stream_delete( lpOrient->qrStrmfyx );
        lpOrient->qrStrmfyy = lp_stream_delete( lpOrient->qrStrmfyy );
        lpOrient->qrStrmfyz = lp_stream_delete( lpOrient->qrStrmfyz );
        lpOrient->qrStrmfzx = lp_stream_delete( lpOrient->qrStrmfzx );
        lpOrient->qrStrmfzy = lp_stream_delete( lpOrient->qrStrmfzy );
        lpOrient->qrStrmfzz = lp_stream_delete( lpOrient->qrStrmfzz );
        lpOrient->qrStrmSyn = lp_stream_delete( lpOrient->qrStrmSyn );

    }

/*
    Source - CSPS query - Orientation - Method
 */

    lp_Enum_t lp_query_orientation_state(

        lp_Orient_t const * const lpOrient

    ) {

        /* Return query structure status */
        return( lpOrient->qrState );

    }

    lp_Enum_t lp_query_orientation_status(

        lp_Orient_t const * const lpOrient

    ) {

        /* Return query structure status */
        return( lpOrient->qrStatus );

    }

    lp_Size_t lp_query_orientation_size( 

        lp_Orient_t const * const lpOrient

    ) {

        /* Return imported streams size */
        return( lpOrient->qrSize );

    }

    lp_Void_t lp_query_orientation_matrix(

        lp_Orient_t const *  const lpOrient,
        lp_Real_t                  lpMatrix[3][3]

    ) {

        /* Assign matrix coefficients */
        lpMatrix[0][0] = lpOrient->qrfxx;
        lpMatrix[1][0] = lpOrient->qrfxy;
        lpMatrix[2][0] = lpOrient->qrfxz;
        lpMatrix[0][1] = lpOrient->qrfyx;
        lpMatrix[1][1] = lpOrient->qrfyy;
        lpMatrix[2][1] = lpOrient->qrfyz;
        lpMatrix[0][2] = lpOrient->qrfzx;
        lpMatrix[1][2] = lpOrient->qrfzy;
        lpMatrix[2][2] = lpOrient->qrfzz;

    }

/*
    Source - CSPS query - Orientation - Query
 */

    lp_Void_t lp_query_orientation(

        lp_Orient_t       * const lpOrient,
        lp_Time_t   const         lpTime

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
        lp_Real_t lpDTIT2 = lp_Real_s( 0.0 );
        lp_Real_t lpDT1T2 = lp_Real_s( 0.0 );
        lp_Real_t lpDT0T2 = lp_Real_s( 0.0 );
        lp_Real_t lpDT1T3 = lp_Real_s( 0.0 );

        /* Check query structure state */
        if ( lpOrient->qrState == LP_TRUE ) {

            /* Obtains index of nearest lower or equal timestamp stored in synchronization array */
            if ( ( lpParse = lp_timestamp_search( lpTime, lpOrient->qrStrmSyn, lpOrient->qrSize ) ) != LP_TIMESTAMP_FAULT ) {

                /* Cubic interpolation derivative range necessities */
                if ( ( lpParse >= lp_Size_s( 1 ) ) && ( lpParse < ( lpOrient->qrSize - lp_Size_s( 2 ) ) ) ) {

                    /* Compute quantity interpolation sampling nodes */
                    lpSample0 = lpParse - 1;
                    lpSample1 = lpParse;
                    lpSample2 = lpParse + 1;
                    lpSample3 = lpParse + 2;

                    /* Compute time interpolation variable */
                    lpDT1TI = lp_timestamp_float( lp_timestamp_diff( lpTime, lpOrient->qrStrmSyn[lpSample1] ) );
                    lpDTIT2 = lp_timestamp_float( lp_timestamp_diff( lpTime, lpOrient->qrStrmSyn[lpSample2] ) );

                    /* Compute time interpolation sample */
                    lpDT1T2 = lp_timestamp_float( lp_timestamp_diff( lpOrient->qrStrmSyn[lpSample2], lpOrient->qrStrmSyn[lpSample1] ) );
                    lpDT0T2 = lp_timestamp_float( lp_timestamp_diff( lpOrient->qrStrmSyn[lpSample2], lpOrient->qrStrmSyn[lpSample0] ) );
                    lpDT1T3 = lp_timestamp_float( lp_timestamp_diff( lpOrient->qrStrmSyn[lpSample3], lpOrient->qrStrmSyn[lpSample1] ) );

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

                    /* Assign exptrapolation weakness */
                    lpOrient->qrWeak = ( lpDT1TI > lpDTIT2 ) ? lpDTIT2 : lpDT1TI;

                    /* Update query status */
                    lpOrient->qrStatus = LP_TRUE;

                } else {

                    /* Update query status */
                    lpOrient->qrStatus = LP_FALSE;

                }

            } else {

                /* Update query status */
                lpOrient->qrStatus = LP_FALSE;

            }

        } else {

            /* Update query status */
            lpOrient->qrStatus = LP_FALSE;

        }

    }

