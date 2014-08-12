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

    # ifndef __LP_DEVICE__
    # define __LP_DEVICE__

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

    /* Define camera device name */
    # define CSPS_DEVICE_CAM_EYESIS4PI          "EYESIS4PI"

    /* Define IMU device name */
    # define CSPS_DEVICE_IMU_ADIS16375          "ADIS16375"

    /* Define GPS device name */
    # define CSPS_DEVICE_GPS_LS20031            "LS20031"

    /* Define eyesis4pi fpga log record size */
    # define CSPS_DEVICE_CAM_EYESIS4PI_RECLEN   csps_Size_s( 64 )

    /* Define eyesis4pi event flags */
    # define CSPS_DEVICE_CAM_EYESIS4PI_IMUEVT   csps_Enum_s(  0 )
    # define CSPS_DEVICE_CAM_EYESIS4PI_GPSEVT   csps_Enum_s(  1 )
    # define CSPS_DEVICE_CAM_EYESIS4PI_MASEVT   csps_Enum_s(  2 )

/*
    Header - Preprocessor macros
 */

/*
    Header - Typedefs
 */

/*
    Header - Structures
 */

    typedef struct csps_CAM_struct {

        /* Device name */
        csps_Char_t dvName[CSPS_STR_LEN];

        /* Size of importation block */
        csps_Size_t dvBlock;

    } csps_CAM;


    typedef struct csps_IMU_struct {

        /* Device name */
        csps_Char_t dvName[CSPS_STR_LEN];

        /* Gyroscope factory factors */
        csps_Real_t dvGYRx;
        csps_Real_t dvGYRy;
        csps_Real_t dvGYRz;

        /* Accelerometre factory factors */
        csps_Real_t dvACCx;
        csps_Real_t dvACCy;
        csps_Real_t dvACCz;

        /* Initial frame parameters */
        csps_Real_t dvfxx;
        csps_Real_t dvfxy;
        csps_Real_t dvfxz;
        csps_Real_t dvfyx;
        csps_Real_t dvfyy;
        csps_Real_t dvfyz;
        csps_Real_t dvfzx;
        csps_Real_t dvfzy;
        csps_Real_t dvfzz;

        /* IMU frequencies */
        csps_Size_t dvifreq; /* Device frequency */
        csps_Size_t dvdfreq; /* Downsampled frequency */

        /* Size of importation block */
        csps_Size_t dvBlock;

    } csps_IMU;

    typedef struct csps_GPS_struct {

        /* Device name */
        csps_Char_t dvName[CSPS_STR_LEN];

        /* GPS frequency */
        csps_Size_t dvifreq;

        /* Size of importation block */
        csps_Size_t dvBlock;

    } csps_GPS;

/*
    Header - Function prototypes
 */

    csps_CAM csps_device_CAM(

        const csps_Char_t * const cspsName

    );

    csps_IMU csps_device_IMU(

        const csps_Char_t * const cspsName

    );

    csps_GPS csps_device_GPS(

        const csps_Char_t * const cspsName

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

