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

    # include "csps-gps-mod-SGNQF.h"

/*
    Source - GPS signal loss compensator
 */

    lp_GPS lp_gps_mod_SGNQF( 

        const lp_Char_t * const lpPath, 
        lp_GPS                  lpDevice, 
        const lp_Char_t * const lpPS__ 

    ) {

        /* Integration variables */
        lp_Size_t lpParse = lp_Size_s( 0 );
        lp_Size_t lpIndex = lp_Size_s( 0 );

        /* Files size */
        lp_Size_t lpSize = lp_Size_s( 0 );

        /* Data buffers */
        lp_Real_t * lpDEVlat = NULL;
        lp_Real_t * lpDEVlon = NULL;
        lp_Real_t * lpDEValt = NULL;
        lp_Time_t * lpDEVsyn = NULL;
        lp_Time_t * lpDEVqbf = NULL;

        /* Obtain stream size */
        lpSize = lp_stream_size( lpPath, lpDevice.dvType, lpDevice.dvTag, lpPS__ );

        /* Read streams data */
        lpDEVlat = lp_stream_read( lpPath, lpDevice.dvType, lpDevice.dvTag, lpPS__, LP_STREAM_CPN_LAT, sizeof( lp_Real_t ) * lpSize );
        lpDEVlon = lp_stream_read( lpPath, lpDevice.dvType, lpDevice.dvTag, lpPS__, LP_STREAM_CPN_LON, sizeof( lp_Real_t ) * lpSize );
        lpDEValt = lp_stream_read( lpPath, lpDevice.dvType, lpDevice.dvTag, lpPS__, LP_STREAM_CPN_ALT, sizeof( lp_Real_t ) * lpSize );
        lpDEVqbf = lp_stream_read( lpPath, lpDevice.dvType, lpDevice.dvTag, lpPS__, LP_STREAM_CPN_QBF, sizeof( lp_Time_t ) * lpSize );
        lpDEVsyn = lp_stream_read( lpPath, lpDevice.dvType, lpDevice.dvTag, lpPS__, LP_STREAM_CPN_SYN, sizeof( lp_Time_t ) * lpSize );

        /* Signal quality filtering */
        for ( lpParse = lp_Size_s( 0 ) ; lpParse < lpSize - lp_Size_s( 1 ) ; lpParse ++ ) {

            /* Check signal QBF threshold */
            if ( lp_qbf_threshold( lpDEVqbf[lpParse] ) == LP_FALSE ) {

                /* Rethrow values */
                lpDEVlat[lpIndex] = lpDEVlat[lpParse];
                lpDEVlon[lpIndex] = lpDEVlon[lpParse];
                lpDEValt[lpIndex] = lpDEValt[lpParse];
                lpDEVsyn[lpIndex] = lpDEVsyn[lpParse];
                lpDEVqbf[lpIndex] = lpDEVqbf[lpParse];

                /* Update rethrown value index */
                lpIndex ++;

            }

        }

        /* Write stream data */
        lp_stream_write( lpPath, lpDevice.dvType, lpDevice.dvTag, LP_GPS_SGNQF_MOD, LP_STREAM_CPN_LAT, lpDEVlat, sizeof( lp_Real_t ) * lpIndex );
        lp_stream_write( lpPath, lpDevice.dvType, lpDevice.dvTag, LP_GPS_SGNQF_MOD, LP_STREAM_CPN_LON, lpDEVlon, sizeof( lp_Real_t ) * lpIndex );
        lp_stream_write( lpPath, lpDevice.dvType, lpDevice.dvTag, LP_GPS_SGNQF_MOD, LP_STREAM_CPN_ALT, lpDEValt, sizeof( lp_Real_t ) * lpIndex );
        lp_stream_write( lpPath, lpDevice.dvType, lpDevice.dvTag, LP_GPS_SGNQF_MOD, LP_STREAM_CPN_QBF, lpDEVqbf, sizeof( lp_Time_t ) * lpIndex );
        lp_stream_write( lpPath, lpDevice.dvType, lpDevice.dvTag, LP_GPS_SGNQF_MOD, LP_STREAM_CPN_SYN, lpDEVsyn, sizeof( lp_Time_t ) * lpIndex );

        /* Unallocate buffer memory */
        free( lpDEVlat );
        free( lpDEVlon );
        free( lpDEValt );
        free( lpDEVsyn );
        free( lpDEVqbf );

        /* Return device descriptor */
        return( lpDevice );

    }

