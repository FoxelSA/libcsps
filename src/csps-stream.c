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

    # include "csps-stream.h"

/*
    Source - Stream basic management
 */

    lp_Void_t * lp_stream_create(

        lp_Size_t const lpSize

    ) {

        /* Create stream buffer memory allocation */
        lp_Void_t * lpStream = malloc( lpSize );

        /* Return pointer */
        return( lpStream );

    }

    lp_Void_t * lp_stream_delete(

        lp_Void_t * lpStream

    ) {

        /* Verify pointer and unallocate memory */
        if ( lpStream != NULL ) free( lpStream );

        /* Return null pointer */
        return( NULL );

    }


/*
    Source - Stream size
 */

    lp_Size_t lp_stream_size(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule

    ) {

        /* Stream handle variables */
        lp_File_t lpStreamf = NULL;

        /* Stream size variables */
        lp_Size_t lpSize = lp_Size_s( 0 );

        /* Stream path variables */
        lp_Char_t lpStreamp[LP_STR_LEN] = LP_STR_INI;

        /* Build stream path */
        lp_path_stream( lpPath, lpTag, lpModule, LP_STREAM_CPN_SYN, lpStreamp );

        /* Open stream file */
        if ( ( lpStreamf = fopen( lpStreamp, "rb" ) ) != NULL ) {

            /* Set pointer to EOF */
            fseek( lpStreamf, 0L, SEEK_END );

            /* Read pointer value */
            lpSize = ftell( lpStreamf ) / sizeof( lp_Time_t );

            /* Close stream file */
            fclose( lpStreamf );

        }

        /* Return stream buffer */
        return( lpSize );

    }

/*
    Source - Stream input/output function
 */

    lp_Void_t * lp_stream_read(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule,
        lp_Char_t const * const lpSuffix,
        lp_Size_t const         lpSize

    ) {

        /* Stream handle variables */
        lp_File_t lpStreamf = NULL;

        /* Stream buffer variables */
        lp_Void_t * lpStream = NULL;

        /* Stream path variables */
        lp_Char_t lpStreamp[LP_STR_LEN] = LP_STR_INI;

        /* Verify provided stream size */
        if ( lpSize > 0 ) {

            /* Build stream component path */
            lp_path_stream( lpPath, lpTag, lpModule, lpSuffix, lpStreamp );

            /* Allocate buffer memory */
            lpStream = malloc( lpSize );

            /* Open stream file */
            lpStreamf = fopen( lpStreamp, "rb" );

            /* Read stream file */
            if ( fread( lpStream, 1, lpSize, lpStreamf ) != lpSize ) {

                /* Unallocte buffer memory */
                free( lpStream );

                /* Invalidate pointer */
                lpStream = NULL;

            }

            /* Close stream file */
            fclose( lpStreamf );

        }

        /* Return stream buffer */
        return( lpStream );

    }

    lp_Size_t lp_stream_write(

        lp_Char_t const * const lpPath,
        lp_Char_t const * const lpTag,
        lp_Char_t const * const lpModule,
        lp_Char_t const * const lpSuffix,
        lp_Void_t const * const lpStream,
        lp_Size_t const         lpSize

    ) {

        /* Exported size variables */
        lp_Size_t lpWritten = lp_Size_s( 0 );

        /* Stream handle variables */
        lp_File_t lpStreamf = NULL;

        /* Stream path variables */
        lp_Char_t lpStreamp[LP_STR_LEN] = LP_STR_INI;

        /* Verify provided stream size */
        if ( lpSize > 0 ) {

            /* Build stream component path variables */
            lp_path_stream( lpPath, lpTag, lpModule, lpSuffix, lpStreamp );

            /* Open stream file */
            if ( ( lpStreamf = fopen( lpStreamp, "wb" ) ) != NULL ) {

                /* Write stream file */
                lpWritten = fwrite( lpStream, 1, lpSize, lpStreamf );

                /* Close stream file */
                fclose( lpStreamf );

            }

        }

        /* Return exported size */
        return( lpWritten );

    }

