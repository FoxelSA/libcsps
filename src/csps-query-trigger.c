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

        /* Returned structure variables */
        lp_Trigger_t lpTrigger;

        /* Initialize structure status */
        lpTrigger.qrState  = LP_FALSE;
        lpTrigger.qrStatus = LP_FALSE;

        /* Initialize query fields */
        lpTrigger.qrMaster = lp_Time_s( 0 );
        lpTrigger.qrSynch  = lp_Time_s( 0 );

        /* Retrieve stream size */
        lpTrigger.qrSize = lp_stream_size( lpPath, lpTag, lpModule );

        /* Streams component importation */
        lpTrigger.qrStrmTag = lp_stream_read( lpPath, lpTag, lpModule, LP_STREAM_CPN_TAG, sizeof( lp_Time_t ) * lpTrigger.qrSize );
        lpTrigger.qrStrmSyn = lp_stream_read( lpPath, lpTag, lpModule, LP_STREAM_CPN_SYN, sizeof( lp_Time_t ) * lpTrigger.qrSize );

        /* Verify structure state */
        if ( ( lpTrigger.qrStrmTag == NULL ) || ( lpTrigger.qrStrmSyn == NULL ) ) {

            /* Delete structure */
            lp_query_trigger_delete( & lpTrigger );

        } else {

            /* Update structure state */
            lpTrigger.qrState = LP_TRUE;

        }

        /* Return structure */
        return( lpTrigger );

    }

    lp_Void_t lp_query_trigger_delete(

        lp_Trigger_t * const lpTrigger

    ) {

        /* Reset structure status */
        lpTrigger->qrState  = LP_FALSE;
        lpTrigger->qrStatus = LP_FALSE;

        /* Reset stream size */
        lpTrigger->qrSize = lp_Size_s( 0 );

        /* Unallocate stream components */
        lpTrigger->qrStrmTag = lp_stream_delete( lpTrigger->qrStrmTag );
        lpTrigger->qrStrmSyn = lp_stream_delete( lpTrigger->qrStrmSyn );

    }

/*
    Source - CSPS query - Trigger - Method
 */

    lp_Enum_t lp_query_trigger_state(

        lp_Trigger_t const * const lpTrigger

    ) {

        /* Return structure state */
        return( lpTrigger->qrState );

    }


    lp_Enum_t lp_query_trigger_status(

        lp_Trigger_t const * const lpTrigger

    ) {

        /* Return structure status */
        return( lpTrigger->qrStatus );

    }

    lp_Size_t lp_query_trigger_size(

        lp_Trigger_t const * const lpTrigger

    ) {

        /* Return stream size */
        return( lpTrigger->qrSize );

    }

/*
    Source - CSPS query - Trigger - Query
 */

    lp_Void_t lp_query_trigger_bymaster(

        lp_Trigger_t * const lpTrigger,
        lp_Time_t      const lpMaster

    ) {

        /* Array index variables */
        lp_Size_t lpIndex = lp_Size_s( 0 );

        /* Check query structure state */
        if ( lpTrigger->qrState == LP_TRUE ) {

            /* Master timestamp index search */
            lpIndex = lp_timestamp_search( lpMaster, lpTrigger->qrStrmTag, lpTrigger->qrSize );

            /* Search result verification */
            if ( lpIndex != LP_TIMESTAMP_FAULT ) {

                /* Strict match verification */
                if ( lp_timestamp_eq( lpMaster, ( lpTrigger->qrStrmTag )[lpIndex] ) == LP_TRUE ) {

                    /* Assign query fields */
                    lpTrigger->qrMaster = ( lpTrigger->qrStrmTag )[lpIndex];
                    lpTrigger->qrSynch  = ( lpTrigger->qrStrmSyn )[lpIndex];

                    /* Update query status */
                    lpTrigger->qrStatus = LP_TRUE;

                } else {

                    /* Update query status */
                    lpTrigger->qrStatus = LP_FALSE;

                }

            } else {

                /* Update query status */
                lpTrigger->qrStatus = LP_FALSE;

            }

        } else {

            /* Update query status */
            lpTrigger->qrStatus = LP_FALSE;

        }

    }

    lp_Void_t lp_query_trigger_byindex(

        lp_Trigger_t * const lpTrigger,
        lp_Size_t      const lpIndex

    ) {

        /* Check query structure state */
        if ( lpTrigger->qrState == LP_TRUE ) {

            /* Check query range */
            if ( ( lpIndex >= 0 ) || ( lpIndex < lpTrigger->qrSize ) ) {

                /* Assign query fields */
                lpTrigger->qrMaster = ( lpTrigger->qrStrmTag )[lpIndex];
                lpTrigger->qrSynch  = ( lpTrigger->qrStrmSyn )[lpIndex];

                /* Update query status */
                lpTrigger->qrStatus = LP_TRUE;

            } else {

                /* Update query status */
                lpTrigger->qrStatus = LP_FALSE;

            }

        }

    }

