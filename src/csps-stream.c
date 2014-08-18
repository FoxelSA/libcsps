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

    # include "csps-stream.h"

/*
    Source - Stream size
 */

    lp_Size_t lp_stream_size(

        const lp_Char_t * const lpPath,
        const lp_Char_t * const lpDevice,
        const lp_Char_t * const lpTag,
        const lp_Char_t * const lpModule,
        const lp_Char_t * const lpType

    ) {

        /* Stream handle */
        lp_File_t lpStreamf = NULL;

        /* Stream size */
        lp_Size_t lpSize = lp_Size_s( 0 );

        /* Stream path */
        lp_Char_t lpStreamp[LP_STR_LEN] = LP_STR_INI;

        /* Build stream path */
        lp_path( lpPath, lpDevice, lpTag, lpModule, lpType, lpStreamp );

        /* Open stream file */
        lpStreamf = fopen( lpStreamp, "rb" );

        /* Read pointer to EOF */
        fseek( lpStreamf, 0L, SEEK_END );

        /* Read pointer value */
        lpSize = ftell( lpStreamf );

        /* Close stream file */
        fclose( lpStreamf );

        /* Return stream buffer */
        return( lpSize );

    }

/*
    Source - Stream create
 */

    lp_Void_t * lp_stream_create(

        lp_Size_t lpSize

    ) {

        /* Stream buffer */
        lp_Void_t * lpStream = malloc( lpSize );

        /* Return pointer */
        return( lpStream );

    }

/*
    Source - Stream reader
 */

    lp_Void_t * lp_stream_read(

        const lp_Char_t * const lpPath,
        const lp_Char_t * const lpDevice,
        const lp_Char_t * const lpTag,
        const lp_Char_t * const lpModule,
        const lp_Char_t * const lpType,
        lp_Size_t lpSize

    ) {

        /* Stream handle */
        lp_File_t lpStreamf = NULL;

        /* Stream buffer */
        lp_Void_t * lpStream = NULL;

        /* Stream path */
        lp_Char_t lpStreamp[LP_STR_LEN] = LP_STR_INI;

        /* Build stream path */
        lp_path( lpPath, lpDevice, lpTag, lpModule, lpType, lpStreamp );

        /* Allocate buffer memory */
        lpStream = malloc( lpSize );

        /* Open stream file */
        lpStreamf = fopen( lpStreamp, "rb" );

        /* Read stream file */
        fread( lpStream, 1, lpSize, lpStreamf );

        /* Close stream file */
        fclose( lpStreamf );

        /* Return stream buffer */
        return( lpStream );

    }

/*
    Source - Stream writer
 */

    lp_Void_t lp_stream_write(

        const lp_Char_t * const lpPath,
        const lp_Char_t * const lpDevice,
        const lp_Char_t * const lpTag,
        const lp_Char_t * const lpModule,
        const lp_Char_t * const lpType,
        const lp_Void_t * const lpStream,
        lp_Size_t lpSize

    ) {

        /* Stream handle */
        lp_File_t lpStreamf = NULL;

        /* Stream path */
        lp_Char_t lpStreamp[LP_STR_LEN] = LP_STR_INI;

        /* Build stream path */
        lp_path( lpPath, lpDevice, lpTag, lpModule, lpType, lpStreamp );

        /* Open stream file */
        lpStreamf = fopen( lpStreamp, "wb" );

        /* Read stream file */
        fwrite( lpStream, 1, lpSize, lpStreamf );

        /* Close stream file */
        fclose( lpStreamf );

    }

