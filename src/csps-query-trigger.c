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

    # include "csps-query-trigger.h"

/*
    Source - CSPS query - Trigger - Handle
 */

    lp_Trigger_t lp_query_trigger_create(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule

    ) {

        /* Stream size variables */
        lp_Size_t lpSize = lp_stream_size( lpPath, lpTag, lpModule );

        /* Returned structure variables */
        lp_Trigger_t lpTrigger = { 

            /* Setting query status */
            LP_FALSE,

            /* Initialize data fields */
            lp_Time_s( 0 ),
            lp_Time_s( 0 ),

            /* Setting stream size */
            lpSize, 

            /* Streams data importation */
            lp_stream_read( lpPath, lpTag, lpModule, LP_STREAM_CPN_TAG, sizeof( lp_Time_t ) * lpSize ),
            lp_stream_read( lpPath, lpTag, lpModule, LP_STREAM_CPN_SYN, sizeof( lp_Time_t ) * lpSize )

        };

        /* Return structure */
        return( lpTrigger );

    }

    lp_Void_t lp_query_trigger_delete(

        lp_Trigger_t * const lpTrigger

    ) {

        /* Reset query status */
        lpTrigger->qrStatus = LP_FALSE;

        /* Reset stream size */
        lpTrigger->qrSize = lp_Size_s( 0 );

        /* Unallocate streams */
        lpTrigger->qrStrmTag = lp_stream_delete( lpTrigger->qrStrmTag );
        lpTrigger->qrStrmSyn = lp_stream_delete( lpTrigger->qrStrmSyn );

    }

/*
    Source - CSPS query - Trigger - Method
 */

    lp_Size_t lp_query_trigger_size(

        lp_Trigger_t const * const lpTrigger

    ) {

        /* Return imported streams size */
        return( lpTrigger->qrSize );

    }

/*
    Source - CSPS query - Trigger - Query
 */

    lp_Void_t lp_query_trigger(

        lp_Trigger_t * const lpTrigger,
        lp_Size_t      const lpOffset

    ) {

        /* Check query offset range */
        if ( ( lpOffset >= 0 ) || ( lpOffset < lpTrigger->qrSize ) ) {

            /* Assign timestamp associated to offset */
            lpTrigger->qrMaster = ( lpTrigger->qrStrmTag )[lpOffset];
            lpTrigger->qrSynch  = ( lpTrigger->qrStrmSyn )[lpOffset];

            /* Update query status */
            lpTrigger->qrStatus = LP_TRUE;

        } else {

            /* Update query status */
            lpTrigger->qrStatus = LP_FALSE;

        }

    }

