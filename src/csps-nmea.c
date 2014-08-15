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

    # include "csps-nmea.h"

/*
    Source - GPS NMEA GGA sentence decomposer
 */

    lp_Void_t lp_nmea_gga(

        const lp_Char_t * const lpSentence,
        lp_Real_t * const lpUTC,
        lp_Real_t * const lpLat,
        lp_Real_t * const lpLon,
        lp_Real_t * const lpAlt,
        lp_SQBF_t * const lpQBF

    ) {

        /* Parse variable */
        lp_Size_t lpParse = lp_Size_s( 0 );
        lp_Size_t lpIndex = lp_Size_s( 0 );

        /* Reading buffers */
        lp_Char_t lpBuf = lp_Char_s( 0 );
        lp_Enum_t lpFix = lp_Enum_s( 0 );
        lp_Size_t lpSat = lp_Size_s( 0 );
        lp_Real_t lpHDP = lp_Real_s( 0.0 );

        /* Sentence length */
        lp_Size_t cspsLen = strlen( lpSentence ) - lp_Size_s( 1 );

        /* Decomposition process */
        while ( lpIndex < cspsLen ) {

            /* Verify decomposition length */
            if ( * ( lpSentence + lpIndex + lp_Size_s( 1 ) ) != ',' ) {

                /* Verify parse variable */
                switch( lpParse ) {

                    case ( lp_Size_s( 0 ) ) : {

                        /* Verify return buffer */
                        if ( lpUTC != NULL ) {

                            /* Assign readed value */
                            sscanf( lpSentence + lpIndex + lp_Size_s( 1 ), "%" lp_Real_i, lpUTC );

                            /* Reformat variable buffer */
                            ( * lpUTC ) = ( * lpUTC ) * lp_Real_s( 1000.0 );

                        }

                    } break;

                    case ( lp_Size_s( 1 ) ) : {

                        /* Verify return buffer */
                        if ( lpLat != NULL ) {

                            /* Assign readed value */
                            sscanf( lpSentence + lpIndex + lp_Size_s( 1 ), "%" lp_Real_i, lpLat );

                            /* Reformat variable buffer */
                            ( * lpLat ) = LP_NMEA_S2D( * lpLat );

                        }

                    } break;

                    case ( lp_Size_s( 2 ) ) : {

                        /* Verify return buffer */
                        if ( lpLat != NULL ) {

                            /* Assign readed value */
                            sscanf( lpSentence + lpIndex + lp_Size_s( 1 ), "%" lp_Char_i, & lpBuf );

                            /* Reformat variable buffer */
                            ( * lpLat ) = ( * lpLat ) * ( ( lpBuf == 'N' ) ?  lp_Real_s( + 1.0 ) : lp_Real_s( - 1.0 ) );

                        }

                    } break;

                    case ( lp_Size_s( 3 ) ) : {

                        /* Verify return buffer */
                        if ( lpLon != NULL ) {

                            /* Assign readed value */
                            sscanf( lpSentence + lpIndex + lp_Size_s( 1 ), "%" lp_Real_i, lpLon );

                            /* Reformat variable buffer */
                            ( * lpLon ) = LP_NMEA_S2D( * lpLon );

                        }

                    } break;

                    case ( lp_Size_s( 4 ) ) : {

                        /* Verify return buffer */
                        if ( lpLon != NULL ) {

                            /* Assign readed value */
                            sscanf( lpSentence + lpIndex + lp_Size_s( 1 ), "%" lp_Char_i, & lpBuf );

                            /* Reformat variable buffer */
                            ( * lpLon ) = * lpLon * ( ( lpBuf == 'E' ) ?  lp_Real_s( + 1.0 ) : lp_Real_s( - 1.0 ) );

                        }

                    } break;

                    case ( lp_Size_s( 5 ) ) : {

                        /* Assign buffer */
                        sscanf( lpSentence + lpIndex + lp_Size_s( 1 ), "%" lp_Enum_i, & lpFix );

                    } break;

                    case ( lp_Size_s( 6 ) ) : {

                        /* Assign buffer */
                        sscanf( lpSentence + lpIndex + lp_Size_s( 1 ), "%" lp_Size_i, & lpSat );

                    } break;

                    case ( lp_Size_s( 7 ) ) : {

                        /* Assign buffer */
                        sscanf( lpSentence + lpIndex + lp_Size_s( 1 ), "%" lp_Real_i, & lpHDP );

                    } break;

                    case ( lp_Size_s( 8 ) ) : {

                        /* Verify return buffer and assign */
                        if ( lpAlt != NULL ) { sscanf( lpSentence + lpIndex + lp_Size_s( 1 ), "%" lp_Real_i, lpAlt ); }

                    } break;

                };

            }

            /* Update decomposition */
            while ( ( * ( lpSentence + ( ++ lpIndex ) ) != ',' ) && ( lpIndex < cspsLen ) );

            /* Update parse variable */
            lpParse += lp_Size_s( 1 );

        }

        /* Verify return buffer */
        if ( lpQBF != NULL ) {

            /* Composing signal quality buffer */
            ( * lpQBF ) = lp_qbf_compose( lpFix, lpSat, lpHDP * lp_Real_s( 100.0 ) );

        }

    }

/*
    Source - GPS NMEA sentence validation
 */

    lp_Enum_t lp_nmea_gga_validate( const lp_Char_t * const lpSentence ) {

        /* Parse variables */
        lp_Size_t lpIndex = lp_Size_s( 0 );

        /* Validation stack */
        lp_Size_t lpStack = lp_Size_s( 0 );

        /* Sentence lenght */
        lp_Size_t lpLength = strlen( lpSentence );

        /* Parse NMEA/GGA sentence */
        while ( ( lpStack < 11 ) && ( lpIndex < lpLength ) ) {

            /* Check for commas characters */
            if ( * ( lpSentence + ( lpIndex ++ ) ) == ',' ) lpStack ++;

        }

        /* End of string reached too early */
        if ( ( lpIndex == lpLength ) && ( lpStack != 11 ) ) {

            /* Unvalidate sentence */
            return( LP_FALSE );

        } else {

            /* Check for GGA specific format */
            if ( * ( lpSentence + lpIndex ) == 'M' ) {

                /* Validate sentence */
                return( LP_TRUE );

            } else {

                /* Unvalidate sentence */
                return( LP_FALSE );

            }

        }

    }

/*
    Source - GPS NMEA sentence reader
 */

    lp_Enum_t lp_nmea_sentence( const lp_Byte_t * const lpRec, const lp_Size_t lpSize, lp_Char_t * const lpSentence ) {

        /* Sentence element models */
        const lp_Char_t * const lpModel[LP_NMEA_IDENT_MAX] = { 

            LP_NMEA_MODEL_RMC,
            LP_NMEA_MODEL_GGA, 
            LP_NMEA_MODEL_GSA, 
            LP_NMEA_MODEL_VTG 

        };

        /* Reading variables */
        lp_Size_t lpOffset = lp_Size_s( 0 );
        lp_Size_t lpPointer = lp_Size_s( 0 );
        lp_Size_t lpParse = lp_Size_s( 0 );

        /* Reading element buffer */
        lp_Byte_t lpElement = lp_Char_s( 0 );

        /* Element model length */
        lp_Size_t lpModelLen = lp_Size_s( 0 );

        /* Obtain sentence type */
        lp_Enum_t lpType = lp_nmea_quartet( lpRec, lpOffset ++ );

        /* Verify sentence type */
        if ( lpType < LP_NMEA_IDENT_MAX ) {

            /* Obtain element model length */
            lpModelLen = strlen( lpModel[ lpType ] );

            /* Read sentence based on element model */
            for ( lpParse = lp_Size_s( 0 ); lpParse < lpModelLen; lpParse ++ ) {

                /* Reset element buffer */
                lpElement = lp_Char_s( 0 );

                /* Verify sentence element type */
                if ( lpModel[lpType][lpParse] == 'Q' ) {

                    /* Read elements of type quartet */
                    while ( ( lpElement != lp_Char_s( 0x0F ) ) && ( lpPointer < lpSize ) ) {

                        /* Obtain element */
                        lpElement = lp_nmea_quartet( lpRec, lpOffset ++ );

                        /* Analyze element value */
                        if ( ( lpElement >= lp_Char_s( 0 ) ) && ( lpElement < lp_Char_s( 10 ) ) ) {

                            /* Assign element to sentence */
                            lpSentence[lpPointer++] = ( lpElement + lp_Char_s( 0x30 ) );

                        } else if ( lpElement != lp_Char_s( 0x0F ) ) {

                            /* Assign element to sentence */
                            lpSentence[lpPointer++] = ( lpElement + lp_Char_s( 0x20 ) );

                        }

                    }

                } else {

                    /* Read Elements of type byte */
                    while ( ( ( lpElement & lp_Char_s( 0x80 ) ) == lp_Char_s( 0 ) ) && ( lpPointer < lpSize ) ) {

                        /* Obtain element */
                        lpElement = lp_nmea_quartet( lpRec, lpOffset ) | ( lp_nmea_quartet( lpRec, lpOffset + lp_Size_s( 1 ) ) << lp_Size_s( 4 ) );

                        /* Update offset */
                        lpOffset += lp_Size_s( 2 );

                        /* Analyze element value */
                        if ( ( lpElement & lp_Char_s( 0x7F ) ) != lp_Char_s( 0x7F ) ) {

                            /* Assign element to sentence */
                            lpSentence[lpPointer++] = ( lpElement & lp_Char_s( 0x7F ) );

                        }

                    }

                }

                /* Insert comma separation */
                lpSentence[lpPointer++] = ',';

            }

            /* NMEA sentence failure verification */
            if ( lpPointer != lpSize ) {

                /* Complete string sentence with null character */
                lpSentence[lpPointer] = '\0';

                /* Return readed sentence type */
                return( lpType );

            }

        }

        /* Return a empty sentence */
        lpSentence[0] = '\0';

        /* Return failure code */
        return( LP_NMEA_IDENT_FAI );

    }

/*
    Source - GPS NMEA sentence quartet reader from FPGA logs
 */

    lp_Byte_t lp_nmea_quartet( const lp_Byte_t * const lpRec, lp_Size_t lpOffset ) {

        /* Return quartet value according to offset */
        return( ( lpRec[ lpOffset >> 1 ] >> ( ( lpOffset % lp_Size_s( 2 ) ) * lp_Size_s( 4 ) ) ) % lp_Size_s( 16 ) );

    }

