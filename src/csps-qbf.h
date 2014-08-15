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
    Header - Include guard
 */

    # ifndef __LP_QBF__
    # define __LP_QBF__

/*
    Header - C/C++ compatibility
 */

    # ifdef __cplusplus
    extern "C" {
    # endif

/*
    Header - Includes
 */

    # include "csps.h"

/*
    Header - Preprocessor definitions
 */

    /* Define signal fix */
    # define LP_QBF_FIX_INVALID       lp_Enum_s( 0 )
    # define LP_QBF_FIX_GPS           lp_Enum_s( 1 )
    # define LP_QBF_FIX_DGPS          lp_Enum_s( 2 )
    # define LP_QBF_FIX_PPS           lp_Enum_s( 3 )
    # define LP_QBF_FIX_RTK           lp_Enum_s( 4 )
    # define LP_QBF_FIX_FRTK          lp_Enum_s( 5 )
    # define LP_QBF_FIX_ESTIMAT       lp_Enum_s( 6 )
    # define LP_QBF_FIX_MANUAL        lp_Enum_s( 7 )
    # define LP_QBF_FIX_SIMULATION    lp_Enum_s( 8 )

    /* Define threshold parameters */
    # define LP_QBF_THR_MINSAT        lp_Size_s(   7 )
    # define LP_QBF_THR_MINHDP        lp_Size_s( 200 )

/*
    Header - Preprocessor macros
 */
    
    /* Define casting macro */
    # define lp_SQBF_c(x)   ( ( lp_SQBF_t ) x )

    /* Define litteral suffix */
    # define lp_SQBF_s(x)   UINT64_C(x)

    /* Define formated output specifiers */
    # define lp_SQBF_p      PRIu64

    /* Define formated input specifiers */
    # define lp_SQBF_i      SCNu64

/*
    Header - Typedefs
 */

    /* Define gps signal quality buffer type */
    typedef uint64_t lp_SQBF_t;

/*
    Header - Structures
 */

/*
    Header - Function prototypes
 */

    lp_Enum_t lp_qbf_threshold(

        lp_SQBF_t lpQBFValue

    );

    lp_SQBF_t lp_qbf_compose(

        lp_Enum_t lpFix,
        lp_Size_t lpSat,
        lp_Size_t lpHDP100

    );

    lp_Enum_t lp_qbf_fix(

        lp_SQBF_t lpQBF

    );

    lp_Size_t lp_qbf_sat(

        lp_SQBF_t lpQBF

    );

    lp_Size_t lp_qbf_hdop100(

        lp_SQBF_t lpQBF

    );

/*
    Header - C/C++ compatibility
 */

    # ifdef __cplusplus
    }
    # endif

/*
    Header - Include guard
 */

    # endif

