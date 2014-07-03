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

    csps_Enum_t csps_qbf_threshold( csps_SQBF_t cspsQBFValue ) {

        /* Decompose QBF - Fix value */
        csps_Enum_t cspsFix = csps_qbf_fix( cspsQBFValue );

        /* Decompose QBF - Satellite count */
        csps_Size_t cspsSat = csps_qbf_sat( cspsQBFValue );

        /* Decompose QBF - HDOP */
        csps_Size_t cspsHDP = csps_qbf_hdop100( cspsQBFValue );

        /* Verify signal fix value */
        if ( ( cspsFix >= CSPS_QBF_FIX_GPS ) && ( cspsFix <= CSPS_QBF_FIX_FRTK ) ) {

            /* Verify satellite count */
            if ( cspsSat >= CSPS_QBF_THR_MINSAT ) {

                /* Verify HDOP value */
                if ( cspsHDP < CSPS_QBF_THR_MINHDP ) {

                    /* Return un-trigged threshold */
                    return( CSPS_FALSE );

                } else {

                    /* Return trigged threshold */
                    return( CSPS_TRUE );

                }

            } else {

                /* Return trigged threshold */
                return( CSPS_TRUE );

            }

        } else {

            /* Return trigged threshold */
            return( CSPS_TRUE );

        }

    }

/*
    Source - GPS signal quality buffer composer
 */

    csps_SQBF_t csps_qbf_compose( csps_Enum_t cspsFix, csps_Size_t cspsSat, csps_Size_t cspsHDP100 ) {

        /* Compose quality buffer (UUUUUUUUUUUUUUUUDDDDDDDDSSSSSSFF - Unused HDOP100 Fix)  */
        return( ( ( csps_Size_t ) cspsFix ) | ( cspsSat << csps_Size_s( 4 ) ) | ( cspsHDP100 << csps_Size_s( 10 ) ) );

    }

/*
    Source - GPS signal quality buffer decomposer
 */

    csps_Enum_t csps_qbf_fix( csps_SQBF_t cspsQBF ) {

        /* Return fix value */
        return( cspsQBF % csps_SQBF_s( 16 ) );

    }

    csps_Size_t csps_qbf_sat( csps_SQBF_t cspsQBF ) {

        /* Return fix value */
        return( ( cspsQBF >> csps_SQBF_s( 4 ) ) % csps_SQBF_s( 64 ) );

    }

    csps_Size_t csps_qbf_hdop100( csps_SQBF_t cspsQBF ) {

        /* Return fix value */
        return( ( cspsQBF >> csps_SQBF_s( 10 ) ) % csps_SQBF_s( 65536 ) );

    }

