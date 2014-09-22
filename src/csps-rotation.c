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

    # include "csps-timestamp.h"

/*
    Source - Single angle rotation
 */

    lp_Void_t lp_rotation_xR3( lp_Real_t lpAngle, lp_Real_t * lpVectorX, lp_Real_t * lpVectorY, lp_Real_t * lpVectorZ ) {

        /* Buffer variables */
        lp_Real_t lpBfy = * lpVectorY;
        lp_Real_t lpBfz = * lpVectorZ;

        /* Apply rotation around referential x-axis */
        * lpVectorY = + cos( lpAngle ) * lpBfy - sin( lpAngle ) * lpBfz;
        * lpVectorZ = + sin( lpAngle ) * lpBfy + cos( lpAngle ) * lpBfz;

    }

    lp_Void_t lp_rotation_yR3( lp_Real_t lpAngle, lp_Real_t * lpVectorX, lp_Real_t * lpVectorY, lp_Real_t * lpVectorZ ) {

        /* Buffer variables */
        lp_Real_t lpBfx = * lpVectorX;
        lp_Real_t lpBfz = * lpVectorZ;

        /* Apply rotation around referential y-axis */
        * lpVectorX = + cos( lpAngle ) * lpBfx + sin( lpAngle ) * lpBfz;
        * lpVectorZ = - sin( lpAngle ) * lpBfx + cos( lpAngle ) * lpBfz;

    }

    lp_Void_t lp_rotation_zR3( lp_Real_t lpAngle, lp_Real_t * lpVectorX, lp_Real_t * lpVectorY, lp_Real_t * lpVectorZ ) {

        /* Buffer variables */
        lp_Real_t lpBfx = * lpVectorX;
        lp_Real_t lpBfy = * lpVectorY;

        /* Apply rotation around referential z-axis */
        * lpVectorX = + cos( lpAngle ) * lpBfx - sin( lpAngle ) * lpBfy;
        * lpVectorY = + sin( lpAngle ) * lpBfx + cos( lpAngle ) * lpBfy;

    }

/*
    Source - Vectors defined rotation
 */

    lp_Void_t lp_matrix_2vR3( 

        lp_Real_t lpVectAX, 
        lp_Real_t lpVectAY, 
        lp_Real_t lpVectAZ,
        lp_Real_t lpVectBX, 
        lp_Real_t lpVectBY, 
        lp_Real_t lpVectBZ,
        lp_Real_t lpMatrix[3][3]

    ) {

        /* Vector norm variables */
        lp_Real_t lpNorm = sqrt( lpVectAX * lpVectAX + lpVectAY * lpVectAY + lpVectAZ * lpVectAZ );

        /* Normalize vector */
        lpVectAX /= lpNorm;
        lpVectAY /= lpNorm;
        lpVectAZ /= lpNorm;

        /* Compute norm */
        lpNorm = sqrt( lpVectBX * lpVectBX + lpVectBY * lpVectBY + lpVectBZ * lpVectBZ );

        /* Normalize vector */
        lpVectBX /= lpNorm;
        lpVectBY /= lpNorm;
        lpVectBZ /= lpNorm;

        /* Cross product variables */
        lp_Real_t lpCross[3] = {

            lpVectAY * lpVectBZ - lpVectAZ * lpVectBY,
            lpVectAZ * lpVectBX - lpVectAX * lpVectBZ,
            lpVectAX * lpVectBY - lpVectAY * lpVectBX

        };

        /* Sine square variables */
        lp_Real_t lpSin = lpCross[0] * lpCross[0] + lpCross[1] * lpCross[1] + lpCross[2] * lpCross[2];

        /* Cosine variables */
        lp_Real_t lpCos = lpVectAX * lpVectBX + lpVectAY * lpVectBY + lpVectAZ * lpVectBZ;

        /* Square factor variables */
        lp_Real_t lpFac = ( lp_Real_s( 1.0 ) - lpCos ) / lpSin;

        /* Build rotation matrix - First column */
        lpMatrix[0][0] = - ( lpCross[1] * lpCross[1] + lpCross[2] * lpCross[2] ) * lpFac + lp_Real_s( 1.0 ); 
        lpMatrix[1][0] = + ( lpCross[0] * lpCross[1] ) * lpFac + lpCross[2];
        lpMatrix[2][0] = + ( lpCross[0] * lpCross[2] ) * lpFac - lpCross[1];

        /* Build rotation matrix - Second column */
        lpMatrix[0][1] = + ( lpCross[0] * lpCross[1] ) * lpFac - lpCross[2];
        lpMatrix[1][1] = - ( lpCross[0] * lpCross[0] + lpCross[2] * lpCross[2] ) * lpFac + lp_Real_s( 1.0 ); 
        lpMatrix[2][1] = + ( lpCross[1] * lpCross[2] ) * lpFac + lpCross[0];

        /* Build rotation matrix - Third column */
        lpMatrix[0][2] = + ( lpCross[0] * lpCross[2] ) * lpFac + lpCross[1];
        lpMatrix[1][2] = + ( lpCross[1] * lpCross[2] ) * lpFac - lpCross[0];
        lpMatrix[2][2] = - ( lpCross[0] * lpCross[0] + lpCross[1] * lpCross[1] ) * lpFac + lp_Real_s( 1.0 ); 

    }
