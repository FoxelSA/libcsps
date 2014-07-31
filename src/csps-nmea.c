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

    csps_Void_t csps_nmea_gga(

        const csps_Char_t * const cspsSentence,
        csps_Real_t * const cspsUTC,
        csps_Real_t * const cspsLat,
        csps_Real_t * const cspsLon,
        csps_Real_t * const cspsAlt,
        csps_SQBF_t * const cspsQBF

    ) {

        /* Parse variable */
        csps_Size_t cspsParse = csps_Size_s( 0 );
        csps_Size_t cspsIndex = csps_Size_s( 0 );

        /* Reading buffers */
        csps_Char_t cspsBuf = csps_Char_s( 0 );
        csps_Enum_t cspsFix = csps_Enum_s( 0 );
        csps_Size_t cspsSat = csps_Size_s( 0 );
        csps_Real_t cspsHDP = csps_Real_s( 0.0 );

        /* Sentence length */
        csps_Size_t cspsLen = strlen( cspsSentence ) - csps_Size_s( 1 );

        /* Decomposition process */
        while ( cspsIndex < cspsLen ) {

            /* Verify decomposition length */
            if ( * ( cspsSentence + cspsIndex + csps_Size_s( 1 ) ) != ',' ) {

                /* Verify parse variable */
                switch( cspsParse ) {

                    case ( csps_Size_s( 0 ) ) : {

                        /* Verify return buffer */
                        if ( cspsUTC != NULL ) {

                            /* Assign readed value */
                            sscanf( cspsSentence + cspsIndex + csps_Size_s( 1 ), "%" csps_Real_i, cspsUTC );

                            /* Reformat variable buffer */
                            ( * cspsUTC ) = ( * cspsUTC ) * csps_Real_s( 1000.0 );

                        }

                    } break;

                    case ( csps_Size_s( 1 ) ) : {

                        /* Verify return buffer */
                        if ( cspsLat != NULL ) {

                            /* Assign readed value */
                            sscanf( cspsSentence + cspsIndex + csps_Size_s( 1 ), "%" csps_Real_i, cspsLat );

                            /* Reformat variable buffer */
                            ( * cspsLat ) = CSPS_NMEA_S2D( * cspsLat );

                        }

                    } break;

                    case ( csps_Size_s( 2 ) ) : {

                        /* Verify return buffer */
                        if ( cspsLat != NULL ) {

                            /* Assign readed value */
                            sscanf( cspsSentence + cspsIndex + csps_Size_s( 1 ), "%" csps_Char_i, & cspsBuf );

                            /* Reformat variable buffer */
                            ( * cspsLat ) = ( * cspsLat ) * ( ( cspsBuf == 'N' ) ?  csps_Real_s( + 1.0 ) : csps_Real_s( - 1.0 ) );

                        }

                    } break;

                    case ( csps_Size_s( 3 ) ) : {

                        /* Verify return buffer */
                        if ( cspsLon != NULL ) {

                            /* Assign readed value */
                            sscanf( cspsSentence + cspsIndex + csps_Size_s( 1 ), "%" csps_Real_i, cspsLon );

                            /* Reformat variable buffer */
                            ( * cspsLon ) = CSPS_NMEA_S2D( * cspsLon );

                        }

                    } break;

                    case ( csps_Size_s( 4 ) ) : {

                        /* Verify return buffer */
                        if ( cspsLon != NULL ) {

                            /* Assign readed value */
                            sscanf( cspsSentence + cspsIndex + csps_Size_s( 1 ), "%" csps_Char_i, & cspsBuf );

                            /* Reformat variable buffer */
                            ( * cspsLon ) = * cspsLon * ( ( cspsBuf == 'E' ) ?  csps_Real_s( + 1.0 ) : csps_Real_s( - 1.0 ) );

                        }

                    } break;

                    case ( csps_Size_s( 5 ) ) : {

                        /* Assign buffer */
                        sscanf( cspsSentence + cspsIndex + csps_Size_s( 1 ), "%" csps_Enum_i, & cspsFix );

                    } break;

                    case ( csps_Size_s( 6 ) ) : {

                        /* Assign buffer */
                        sscanf( cspsSentence + cspsIndex + csps_Size_s( 1 ), "%" csps_Size_i, & cspsSat );

                    } break;

                    case ( csps_Size_s( 7 ) ) : {

                        /* Assign buffer */
                        sscanf( cspsSentence + cspsIndex + csps_Size_s( 1 ), "%" csps_Real_i, & cspsHDP );

                    } break;

                    case ( csps_Size_s( 8 ) ) : {

                        /* Verify return buffer and assign */
                        if ( cspsAlt != NULL ) { sscanf( cspsSentence + cspsIndex + csps_Size_s( 1 ), "%" csps_Real_i, cspsAlt ); }

                    } break;

                };

            }

            /* Update decomposition */
            while ( ( * ( cspsSentence + ( ++ cspsIndex ) ) != ',' ) && ( cspsIndex < cspsLen ) );

            /* Update parse variable */
            cspsParse += csps_Size_s( 1 );

        }

        /* Verify return buffer */
        if ( cspsQBF != NULL ) {

            /* Composing signal quality buffer */
            ( * cspsQBF ) = csps_qbf_compose( cspsFix, cspsSat, cspsHDP * csps_Real_s( 100.0 ) );

        }

    }

/*
    Source - GPS NMEA sentence validation
 */

    csps_Enum_t csps_nmea_gga_validate( const csps_Char_t * const cspsSentence ) {

        /* Parse variables */
        csps_Size_t cspsIndex = csps_Size_s( 0 );

        /* Validation stack */
        csps_Size_t cspsStack = csps_Size_s( 0 );

        /* Sentence lenght */
        csps_Size_t cspsLength = strlen( cspsSentence );

        /* Parse NMEA/GGA sentence */
        while ( ( cspsStack < 11 ) && ( cspsIndex < cspsLength ) ) {

            /* Check for commas characters */
            if ( * ( cspsSentence + ( cspsIndex ++ ) ) == ',' ) cspsStack ++;

        }

        /* End of string reached too early */
        if ( ( cspsIndex == cspsLength ) && ( cspsStack != 11 ) ) {

            /* Unvalidate sentence */
            return( CSPS_FALSE );

        } else {

            /* Check for GGA specific format */
            if ( * ( cspsSentence + cspsIndex ) == 'M' ) {

                /* Validate sentence */
                return( CSPS_TRUE );

            } else {

                /* Unvalidate sentence */
                return( CSPS_FALSE );

            }

        }

    }

/*
    Source - GPS NMEA sentence reader
 */

    csps_Enum_t csps_nmea_sentence( const csps_Byte_t * const cspsRec, csps_Char_t * const cspsSentence ) {

        /* Sentence element models */
        const csps_Char_t * const cspsModel[CSPS_NMEA_IDENT_MAX] = { CSPS_NMEA_MODEL_RMC, CSPS_NMEA_MODEL_GGA, CSPS_NMEA_MODEL_GSA, CSPS_NMEA_MODEL_VTG };

        /* Reading variables */
        csps_Size_t cspsOffset = csps_Size_s( 0 );
        csps_Size_t cspsPointer = csps_Size_s( 0 );
        csps_Size_t cspsParse = csps_Size_s( 0 );

        /* Reading element buffer */
        csps_Byte_t cspsElement = csps_Char_s( 0 );

        /* Element model length */
        csps_Size_t cspsModelLen = csps_Size_s( 0 );

        /* Obtain sentence type */
        csps_Enum_t cspsType = csps_nmea_quartet( cspsRec, cspsOffset ++ );

        /* Verify sentence type */
        if ( cspsType < CSPS_NMEA_IDENT_MAX ) {

            /* Obtain element model length */
            cspsModelLen = strlen( cspsModel[ cspsType ] );

            /* Read sentence based on element model */
            for ( cspsParse = csps_Size_s( 0 ); cspsParse < cspsModelLen; cspsParse ++ ) {

                /* Reset element buffer */
                cspsElement = csps_Char_s( 0 );

                /* Verify sentence element type */
                if ( cspsModel[cspsType][cspsParse] == 'Q' ) {

                    /* Read elements of type quartet */
                    while ( ( cspsElement != csps_Char_s( 0x0F ) ) && ( cspsPointer < CSPS_DEVICE_FPGA_RECLEN ) ) {

                        /* Obtain element */
                        cspsElement = csps_nmea_quartet( cspsRec, cspsOffset ++ );

                        /* Analyze element value */
                        if ( ( cspsElement >= csps_Char_s( 0 ) ) && ( cspsElement < csps_Char_s( 10 ) ) ) {

                            /* Assign element to sentence */
                            cspsSentence[cspsPointer++] = ( cspsElement + csps_Char_s( 0x30 ) );

                        } else if ( cspsElement != csps_Char_s( 0x0F ) ) {

                            /* Assign element to sentence */
                            cspsSentence[cspsPointer++] = ( cspsElement + csps_Char_s( 0x20 ) );

                        }

                    }

                } else {

                    /* Read Elements of type byte */
                    while ( ( ( cspsElement & csps_Char_s( 0x80 ) ) == csps_Char_s( 0 ) ) && ( cspsPointer < CSPS_DEVICE_FPGA_RECLEN ) ) {

                        /* Obtain element */
                        cspsElement = csps_nmea_quartet( cspsRec, cspsOffset ) | ( csps_nmea_quartet( cspsRec, cspsOffset + csps_Size_s( 1 ) ) << csps_Size_s( 4 ) );

                        /* Update offset */
                        cspsOffset += csps_Size_s( 2 );

                        /* Analyze element value */
                        if ( ( cspsElement & csps_Char_s( 0x7F ) ) != csps_Char_s( 0x7F ) ) {

                            /* Assign element to sentence */
                            cspsSentence[cspsPointer++] = ( cspsElement & csps_Char_s( 0x7F ) );

                        }

                    }

                }

                /* Insert comma separation */
                cspsSentence[cspsPointer++] = ',';

            }

            /* NMEA sentence failure verification */
            if ( cspsPointer != CSPS_DEVICE_FPGA_RECLEN ) {

                /* Complete string sentence with null character */
                cspsSentence[cspsPointer] = '\0';

                /* Return readed sentence type */
                return( cspsType );

            }

        }

        /* Return a empty sentence */
        cspsSentence[0] = '\0';

        /* Return failure code */
        return( CSPS_NMEA_IDENT_FAI );

    }

/*
    Source - GPS NMEA sentence quartet reader from FPGA logs
 */

    csps_Byte_t csps_nmea_quartet( const csps_Byte_t * const cspsRec, csps_Size_t cspsOffset ) {

        /* Return quartet value according to offset */
        return( ( cspsRec[ cspsOffset >> 1 ] >> ( ( cspsOffset % csps_Size_s( 2 ) ) * csps_Size_s( 4 ) ) ) % csps_Size_s( 16 ) );

    }

