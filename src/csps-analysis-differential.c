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

    # include "csps-analysis-differential.h"

/*
    Source - Discrete adaptative first order derivative computation
 */

    lp_Real_t lp_analysis_adaptFDF( 

        lp_Real_t const lpMesh0,
        lp_Real_t const lpMesh1,
        lp_Real_t const lpMesh2,
        lp_Real_t const lpSample0,
        lp_Real_t const lpSample1,
        lp_Real_t const lpSample2,
        lp_Real_t const lpTrigger

    ) {

        /* Returned value variables */
        lp_Real_t lpReturn = lp_Real_s( 0.0 );

        /* Compute mesh spacing */
        lp_Real_t lpSpace0 = lpMesh1 - lpMesh0;
        lp_Real_t lpSpace1 = lpMesh2 - lpMesh1;

        /* Adaptative derivative condition */
        if ( ( lpSpace0 / lpSpace1 ) > lpTrigger  ) {

            /* Uncentered FDF on smallest space */
            lpReturn = ( lpSample2 - lpSample1 ) / lpSpace1;

        } else if ( ( lpSpace1 / lpSpace0 ) > lpTrigger ) {

            /* Uncentered FDF on smallest space */
            lpReturn = ( lpSample1 - lpSample0 ) / lpSpace0;

        } else {

            /* Standard centered FDF */
            lpReturn = ( lpSample2 - lpSample0 ) / ( lpMesh2 - lpMesh0 );

        }
        
        /* Return derivative value */
        return( lpReturn );

    }

