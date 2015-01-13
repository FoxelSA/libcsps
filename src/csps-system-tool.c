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

    # include "csps-system-tool.h"

/*
    Source - Device stack management
 */

    lp_Void_t lp_system_stack_init(

        lp_Stack_t * const lpStack

    ) {

        /* Parsing variables */
        lp_Size_t lpParse = lp_Size_s( 0 );

        /* Initialize stack state */
        lpStack->stSize = lp_Size_s( 0 );

        /* Device stack parsing */
        for ( lpParse = lp_Size_s( 0 ); lpParse < LP_SYSTEM_LIMIT; lpParse ++ ) {

            /* Initialize descriptor pointer */
            lpStack->stDevice[lpParse] = LP_NULL;

            /* Initialize device type */
            lpStack->stType[lpParse] = LP_SYSTEM_TYPE_NULL;

        }

    }

    lp_Void_t lp_system_stack_clear(

        lp_Stack_t * const lpStack

    ) {

        /* Parsing variables */
        lp_Size_t lpParse = lp_Size_s( 0 );

        /* Device stack parsing */
        for ( lpParse = lp_Size_s( 0 ); lpParse < lpStack->stSize; lpParse ++ ) {

            /* Check descriptor state */
            if ( lpStack->stDevice != LP_NULL ) {

                /* Unallocate descriptor memory */
                free( lpStack->stDevice[lpParse] );

                /* Invalidate descriptor pointer */
                lpStack->stDevice[lpParse] = LP_NULL;

            }

            /* Reset device type */
            lpStack->stType[lpParse] = LP_SYSTEM_TYPE_NULL;

        }

    }

    lp_Void_t * lp_system_stack_push(

        lp_Stack_t * const lpStack,
        lp_Enum_t    const lpType

    ) {

        /* Returned value variables */
        lp_Void_t * lpReturn = LP_NULL;

        /* Select device type */
        if ( lpType == LP_SYSTEM_TYPE_CAM ) {

            /* Allocate descriptor memory */
            lpReturn = ( lpStack->stDevice[lpStack->stSize] = ( lp_Void_t * ) malloc( sizeof( lp_Camera_t ) ) );

        } else
        if ( lpType == LP_SYSTEM_TYPE_GPS ) {

            /* Allocate descriptor memory */
            lpReturn = ( lpStack->stDevice[lpStack->stSize] = ( lp_Void_t * ) malloc( sizeof( lp_GPS_t ) ) );

        } else
        if ( lpType == LP_SYSTEM_TYPE_IMU ) {

            /* Allocate descriptor memory */
            lpReturn = ( lpStack->stDevice[lpStack->stSize] = ( lp_Void_t * ) malloc( sizeof( lp_IMU_t ) ) );

        }

        /* Assign device descriptor type */
        lpStack->stType  [lpStack->stSize] = lpType;

        /* Update stack state */
        lpStack->stSize ++;

        /* Return create descriptor pointer */
        return( lpReturn );

    }

/*
    Source - File string token reader
 */

    lp_Char_t * lp_system_token(

        FILE      * const lpFile,
        lp_Char_t * const lpToken

    ) {

        /* Read token from file */
        if ( fscanf( lpFile, "%s", lpToken ) == 1 ) {

            /* Return token pointer */
            return( lpToken );

        } else {

            /* Return null pointer */
            return( LP_NULL );

        }

    }

