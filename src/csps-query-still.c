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

    # include "csps-query-still.h"

/*
    Source - CSPS query - Still - Handle
 */

    lp_Still_t lp_query_still_origin(

        lp_Char_t const * const lpPath

    ) {

        /* Device and module switch variables */
        lp_Char_t lpDevice[LP_STR_LEN] = { '\0' };
        lp_Char_t lpModule[LP_STR_LEN] = { '\0' };

        /* Retrieve device and module switch through origin directive */
        lp_system_origin( lpPath, LP_SYSTEM_POSITION, lpDevice, lpModule );

        /* Create and return orientation query structure */
        return( lp_query_still_create( lpPath, lpDevice, lpModule ) );

    }

    lp_Still_t lp_query_still_create(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule

    ) {

        /* Returned structure variables */
        lp_Still_t lpStill; 

        /* Initialize structure status */
        lpStill.qrState  = LP_FALSE;
        lpStill.qrStatus = LP_FALSE;        

        /* Initialize query fields */
        lpStill.qrStill = LP_FALSE;

        /* Retrieve stream size */
        lpStill.qrSize = lp_stream_size( lpPath, lpTag, lpModule );

        /* Streams component importation */
        lpStill.qrStrmTag = lp_stream_read( lpPath, lpTag, lpModule, LP_STREAM_CPN_TAG, sizeof( lp_Time_t ) * lpStill.qrSize );
        lpStill.qrStrmSyn = lp_stream_read( lpPath, lpTag, lpModule, LP_STREAM_CPN_SYN, sizeof( lp_Time_t ) * lpStill.qrSize );

        /* Verify structure state */
        if ( ( lpStill.qrStrmTag == NULL ) || ( lpStill.qrStrmSyn == NULL ) ) {

            /* Delete structure */
            lp_query_still_delete( & lpStill );

        } else {

            /* Update structure state */
            lpStill.qrState = LP_TRUE;

        }
        
        /* Return structure */
        return( lpStill );

    }

    lp_Void_t lp_query_still_delete(

        lp_Still_t * const lpStill

    ) {

        /* Reset structure status */
        lpStill->qrState  = LP_FALSE;
        lpStill->qrStatus = LP_FALSE;

        /* Reset stream size */
        lpStill->qrSize = lp_Size_s( 0 );

        /* Unallocate stream components */
        lpStill->qrStrmTag = lp_stream_delete( lpStill->qrStrmTag );
        lpStill->qrStrmSyn = lp_stream_delete( lpStill->qrStrmSyn );

    }

/*
    Source - CSPS query - Still - Method
 */

    lp_Enum_t lp_query_still_state(

        lp_Still_t const * const lpStill

    ) {

        /* Return structure state */
        return( lpStill->qrState );

    }

    lp_Enum_t lp_query_still_status(

        lp_Still_t const * const lpStill

    ) {

        /* Return structure status */
        return( lpStill->qrStatus );

    }

    lp_Size_t lp_query_still_size(

        lp_Still_t const * const lpStill

    ) {

        /* Return stream size */
        return( lpStill->qrSize );

    }

/*
    Source - CSPS query - Still - Query
 */

    lp_Void_t lp_query_still( 

        lp_Still_t * const lpStill, 
        lp_Time_t    const lpTime

    ) {

        /* Parsing variables */
        lp_Size_t lpParse = lp_Size_s( 1 );

        /* Check query structure state */
        if ( lpStill->qrState == LP_TRUE ) {

            /* Reset query structure */
            lpStill->qrStill = LP_FALSE;

            /* Parsing detected still range */
            while ( ( lpParse < lpStill->qrSize ) && ( lpStill->qrStill == LP_FALSE ) ) {

                /* Range detection */
                if ( 

                    ( lp_timestamp_ge( lpTime, lpStill->qrStrmSyn[lpParse] ) == LP_TRUE )
                &&  ( lp_timestamp_ge( lpStill->qrStrmTag[lpParse], lpTime ) == LP_TRUE )

                ) {

                    /* Update detection flag */
                    lpStill->qrStill = LP_TRUE;

                }

                /* Update parsing index */
                lpParse ++;

            }

            /* Update query status */
            lpStill->qrStatus = LP_TRUE;

        } else {

            /* Update query status */
            lpStill->qrStatus = LP_FALSE;

        }

    }

