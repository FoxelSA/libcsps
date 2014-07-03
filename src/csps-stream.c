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

    csps_Size_t csps_stream_size(

        const csps_Char_t * const cspsPath,
        const csps_Char_t * const cspsDev,
        const csps_Char_t * const cspsName,
        const csps_Char_t * const cspsPS__,
        const csps_Char_t * const cspsType

    ) {

        /* Stream handle */
        csps_File_t cspsStreamf = NULL;

        /* Stream size */
        csps_Size_t cspsSize = csps_Size_s( 0 );

        /* Stream path */
        csps_Char_t cspsStreamp[CSPS_STR_LEN] = CSPS_STR_INI;

        /* Build stream path */
        csps_path( cspsPath, cspsDev, cspsName, cspsPS__, cspsType, cspsStreamp );

        /* Open stream file */
        cspsStreamf = fopen( cspsStreamp, "rb" );

        /* Read pointer to EOF */
        fseek( cspsStreamf, 0L, SEEK_END );

        /* Read pointer value */
        cspsSize = ftell( cspsStreamf );

        /* Close stream file */
        fclose( cspsStreamf );

        /* Return stream buffer */
        return( cspsSize );

    }

/*
    Source - Stream reader
 */

    csps_Void_t * csps_stream_read(

        const csps_Char_t * const cspsPath,
        const csps_Char_t * const cspsDev,
        const csps_Char_t * const cspsName,
        const csps_Char_t * const cspsPS__,
        const csps_Char_t * const cspsType,
        csps_Size_t cspsSize ) {

        /* Stream handle */
        csps_File_t cspsStreamf = NULL;

        /* Stream buffer */
        csps_Void_t * cspsStream = NULL;

        /* Stream path */
        csps_Char_t cspsStreamp[CSPS_STR_LEN] = CSPS_STR_INI;

        /* Build stream path */
        csps_path( cspsPath, cspsDev, cspsName, cspsPS__, cspsType, cspsStreamp );

        /* Allocate buffer memory */
        cspsStream = malloc( cspsSize );

        /* Open stream file */
        cspsStreamf = fopen( cspsStreamp, "rb" );

        /* Read stream file */
        fread( cspsStream, 1, cspsSize, cspsStreamf );

        /* Close stream file */
        fclose( cspsStreamf );

        /* Return stream buffer */
        return( cspsStream );

    }

/*
    Source - Stream writer
 */

    csps_Void_t csps_stream_write(

        const csps_Char_t * const cspsPath,
        const csps_Char_t * const cspsDev,
        const csps_Char_t * const cspsName,
        const csps_Char_t * const cspsPS__,
        const csps_Char_t * const cspsType,
        const csps_Void_t * const cspsStream,
        csps_Size_t cspsSize

    ) {

        /* Stream handle */
        csps_File_t cspsStreamf = NULL;

        /* Stream path */
        csps_Char_t cspsStreamp[CSPS_STR_LEN] = CSPS_STR_INI;

        /* Build stream path */
        csps_path( cspsPath, cspsDev, cspsName, cspsPS__, cspsType, cspsStreamp );

        /* Open stream file */
        cspsStreamf = fopen( cspsStreamp, "wb" );

        /* Read stream file */
        fwrite( cspsStream, 1, cspsSize, cspsStreamf );

        /* Close stream file */
        fclose( cspsStreamf );

    }

