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

    # include "csps-qbf.h"


/*
    Source - GPS signal quality threshold
 */

    lp_Enum_t lp_qbf_threshold( 

        lp_SQBF_t lpQBFValue 

    ) {

        /* Decompose QBF - Fix value */
        lp_Enum_t lpFix = lp_qbf_fix( lpQBFValue );

        /* Decompose QBF - Satellite count */
        lp_Size_t lpSat = lp_qbf_sat( lpQBFValue );

        /* Decompose QBF - HDOP */
        lp_Size_t lpHDP = lp_qbf_hdop100( lpQBFValue );

        /* Verify signal fix value */
        if ( ( lpFix >= LP_QBF_FIX_GPS ) && ( lpFix <= LP_QBF_FIX_FRTK ) ) {

            /* Verify satellite count */
            if ( lpSat >= LP_QBF_THR_MINSAT ) {

                /* Verify HDOP value */
                if ( lpHDP < LP_QBF_THR_MINHDP ) {

                    /* Return un-trigged threshold */
                    return( LP_FALSE );

                } else {

                    /* Return trigged threshold */
                    return( LP_TRUE );

                }

            } else {

                /* Return trigged threshold */
                return( LP_TRUE );

            }

        } else {

            /* Return trigged threshold */
            return( LP_TRUE );

        }

    }

/*
    Source - GPS signal quality buffer composer
 */

    lp_SQBF_t lp_qbf_compose( 

        lp_Enum_t lpFix, 
        lp_Size_t lpSat, 
        lp_Size_t lpHDP100 

    ) {

        /* Compose quality buffer (UUUUUUUUUUUUUUUUDDDDDDDDSSSSSSFF - Unused hDop100 Satellite Fix)  */
        return( ( ( lp_Size_t ) lpFix ) | ( lpSat << lp_Size_s( 4 ) ) | ( lpHDP100 << lp_Size_s( 10 ) ) );

    }

/*
    Source - GPS signal quality buffer decomposers
 */

    lp_Enum_t lp_qbf_fix( 

        lp_SQBF_t lpQBF 

    ) {

        /* Return fix value */
        return( lpQBF % lp_SQBF_s( 16 ) );

    }

    lp_Size_t lp_qbf_sat( 

        lp_SQBF_t lpQBF 

    ) {

        /* Return satellite count value */
        return( ( lpQBF >> lp_SQBF_s( 4 ) ) % lp_SQBF_s( 64 ) );

    }

    lp_Size_t lp_qbf_hdop100( 

        lp_SQBF_t lpQBF 

    ) {

        /* Return dilution of precision times 100 value */
        return( ( lpQBF >> lp_SQBF_s( 10 ) ) % lp_SQBF_s( 65536 ) );

    }

