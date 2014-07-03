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

    # ifndef __LIBCSPS_CSPS_QBF__
    # define __LIBCSPS_CSPS_QBF__

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

/*
    Header - Preprocessor macros
 */

    /* Define signal fix */
    # define CSPS_QBF_FIX_INVALID       csps_Enum_s( 0 )
    # define CSPS_QBF_FIX_GPS           csps_Enum_s( 1 )
    # define CSPS_QBF_FIX_DGPS          csps_Enum_s( 2 )
    # define CSPS_QBF_FIX_PPS           csps_Enum_s( 3 )
    # define CSPS_QBF_FIX_RTK           csps_Enum_s( 4 )
    # define CSPS_QBF_FIX_FRTK          csps_Enum_s( 5 )
    # define CSPS_QBF_FIX_ESTIMAT       csps_Enum_s( 6 )
    # define CSPS_QBF_FIX_MANUAL        csps_Enum_s( 7 )
    # define CSPS_QBF_FIX_SIMULATION    csps_Enum_s( 8 )

    /* Define threshold parameters */
    # define CSPS_QBF_THR_MINSAT        csps_Size_s(   7 )
    # define CSPS_QBF_THR_MINHDP        csps_Size_s( 200 )

/*
    Header - Typedefs
 */

    /* Define gps signal quality buffer type */
    typedef uint64_t csps_SQBF_t;

    /* Define literal suffix */
    # define csps_SQBF_s(x)  UINT64_C(x)

    /* Define formated output specifiers */
    # define csps_SQBF_p    PRIu64

    /* Define formated input specifiers */
    # define csps_SQBF_i    SCNu64

/*
    Header - Structures
 */

/*
    Header - Function prototypes
 */

    csps_Enum_t csps_qbf_threshold(

        csps_SQBF_t cspsQBFValue

    );

    csps_SQBF_t csps_qbf_compose(

        csps_Enum_t cspsFix,
        csps_Size_t cspsSat,
        csps_Size_t cspsHDP100

    );

    csps_Enum_t csps_qbf_fix(

        csps_SQBF_t cspsQBF

    );

    csps_Size_t csps_qbf_sat(

        csps_SQBF_t cspsQBF

    );

    csps_Size_t csps_qbf_hdop100(

        csps_SQBF_t cspsQBF

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

