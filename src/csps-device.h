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

    /*! \file   csps-device.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  CSPS device descriptors
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
    # include "csps-timestamp.h"

/*
    Header - Preprocessor definitions
 */

    /* Define device type indexes */
    # define LP_DEVICE_ID_CAM               lp_Enum_s( 1 )
    # define LP_DEVICE_ID_GPS               lp_Enum_s( 2 )
    # define LP_DEVICE_ID_IMU               lp_Enum_s( 3 )

    /* Define device types */
    # define LP_DEVICE_TYPE_CAM             "cam"
    # define LP_DEVICE_TYPE_GPS             "gps"
    # define LP_DEVICE_TYPE_IMU             "imu"

    /* Define camera device */
    # define LP_DEVICE_EYESIS4PI            "EYESIS4PI"
    # define LP_DEVICE_EYESIS4PI_LOG        "E4P-LOG-FPGA"
    # define LP_DEVICE_NC353L369IMUGPS      "NC353L-369-IMU-GPS"

    /* Define Eyesis4pi specific constants */
    # define LP_DEVICE_EYESIS4PI_RECLEN     lp_Size_s( 64 )
    # define LP_DEVICE_EYESIS4PI_IMUEVT     lp_Enum_s(  0 )
    # define LP_DEVICE_EYESIS4PI_GPSEVT     lp_Enum_s(  1 )
    # define LP_DEVICE_EYESIS4PI_MASEVT     lp_Enum_s(  2 )

    /* Define IMU device */
    # define LP_DEVICE_ADIS16375            "ADIS16375"
    # define LP_DEVICE_ADIS16375_LOG        "LOG-FPGA"

    /* Define GPS device */
    # define LP_DEVICE_LS20031              "LS20031"
    # define LP_DEVICE_LS20031_LOG          "LOG-FPGA"

/*
    Header - Preprocessor macros
 */

/*
    Header - Typedefs
 */

/*
    Header - Structures
 */

    /*! \struct lp_Camera_struct
     *  \brief Camera device descriptor
     *
     *  The structure stores the description of a camera device engaged
     *  in the CSPS.
     *
     *  \var lp_Camera_struct::dvType
     *  Stores the device type name
     *  \var lp_Camera_struct::dvName 
     *  Stores the device model name
     *  \var lp_Camera_struct::dvTag 
     *  Stores the device tag to differentiate multiple usage of the same model
     *  \var lp_Camera_struct::dvBlock 
     *  Stores the importation block size
     */ 

    typedef struct lp_Camera_struct {

        /* Device type name */
        lp_Char_t dvType[LP_STR_LEN];

        /* Device model name */
        lp_Char_t dvName[LP_STR_LEN];

        /* Device name */
        lp_Char_t dvTag[LP_STR_LEN];

        /* Size of importation block */
        lp_Size_t dvBlock;

    } lp_Camera_t;

    /*! \struct lp_IMU_struct
     *  \brief IMU device descriptor
     *
     *  The structure stores the description of an IMU device engaged
     *  in the CSPS.
     *
     *  \var lp_IMU_struct::dvType
     *  Stores the device type name
     *  \var lp_IMU_struct::dvName 
     *  Stores the device name
     *  \var lp_IMU_struct::dvTag 
     *  Stores the device tag to differentiate multiple usage of the same model
     *  \var lp_IMU_struct::dvGYRx 
     *  Gyroscope factory scale factor for x component
     *  \var lp_IMU_struct::dvGYRy
     *  Gyroscope factory scale factor for y component
     *  \var lp_IMU_struct::dvGYRz 
     *  Gyroscope factory scale factor for z component
     *  \var lp_IMU_struct::dvACCx 
     *  Accelerometer factory scale factor for x component
     *  \var lp_IMU_struct::dvACCy
     *  Accelerometer factory scale factor for y component
     *  \var lp_IMU_struct::dvACCz
     *  Accelerometer factory scale factor for z component
     *  \var lp_IMU_struct::dvISRmax
     *  Maximum number of indexable inertial still ranges
     *  \var lp_IMU_struct::dvISRacc
     *  Minimum samples accumulation for dynamic mean computation
     *  \var lp_IMU_struct::dvISRgrt
     *  Gyroscope signal dynamic mean distance threshold
     *  \var lp_IMU_struct::dvISRact
     *  Acceleration signal dynamic mean distance threshold
     *  \var lp_IMU_struct::dvICRx 
     *  Rotation around x-axis applied on defined initial conditions
     *  \var lp_IMU_struct::dvICRy
     *  Rotation around y-axis applied on defined initial conditions
     *  \var lp_IMU_struct::dvICRz 
     *  Rotation around z-axis applied on defined initial conditions
     *  \var lp_IMU_struct::dvifreq 
     *  Device output sampling frequency
     *  \var lp_IMU_struct::dvdfreq 
     *  Output sampling reduced frequency
     *  \var lp_IMU_struct::dvBlock 
     *  Stores the importation block size
     */ 

    typedef struct lp_IMU_struct {

        /* Device type name */
        lp_Char_t dvType[LP_STR_LEN];

        /* Device model name */
        lp_Char_t dvName[LP_STR_LEN];

        /* Device name */
        lp_Char_t dvTag[LP_STR_LEN];

        /* Gyroscope factory factors */
        lp_Real_t dvGYRx;
        lp_Real_t dvGYRy;
        lp_Real_t dvGYRz;

        /* Accelerometre factory factors */
        lp_Real_t dvACCx;
        lp_Real_t dvACCy;
        lp_Real_t dvACCz;

        /* Inertial still ranges automatic detection */
        lp_Size_t dvISRmax;
        lp_Size_t dvISRacc;
        lp_Real_t dvISRgrt;
        lp_Real_t dvISRact;

        /* Initial conditions manual rotations */
        lp_Real_t dvICRx;
        lp_Real_t dvICRy;
        lp_Real_t dvICRz;

        /* IMU frequencies */
        lp_Size_t dvifreq;
        lp_Size_t dvdfreq;

        /* Size of importation block */
        lp_Size_t dvBlock;

    } lp_IMU_t;

    /*! \struct lp_GPS_struct
     *  \brief GPS device descriptor
     *
     *  The structure stores the description of a GPS device engaged
     *  in the CSPS.
     *
     *  \var lp_GPS_struct::dvType
     *  Stores the device type name
     *  \var lp_GPS_struct::dvName 
     *  Stores the device name
     *  \var lp_GPS_struct::dvTag 
     *  Stores the device tag to differentiate multiple usage of the same model
     *  \var lp_GPS_struct::dvifreq 
     *  Device output sampling frequency
     *  \var lp_GPS_struct::dvBlock 
     *  Stores the importation block size
     */ 

    typedef struct lp_GPS_struct {

        /* Device type name */
        lp_Char_t dvType[LP_STR_LEN];

        /* Device model name */
        lp_Char_t dvName[LP_STR_LEN];

        /* Device name */
        lp_Char_t dvTag[LP_STR_LEN];

        /* GPS frequency */
        lp_Size_t dvifreq;

        /* Size of importation block */
        lp_Size_t dvBlock;

    } lp_GPS_t;

/*
    Header - Function prototypes
 */

    /*! \brief Camera device descriptor creator
     * 
     *  Create camera device descriptor structure. It consider device model to 
     *  assign its device-specific configuration.
     *
     * \param   lpName  Camera device name
     * \param   lpTag   Stores the device tag to differentiate multiple usage of
     *                  the same model
     *
     * \returns Returns created camera descriptor
     */

    lp_Camera_t lp_device_camera( 

        lp_Char_t const * const lpName, 
        lp_Char_t const * const lpTag

    );

    /*! \brief IMU device descriptor creator
     * 
     *  Create IMU device descriptor structure. It consider device model to 
     *  assign its device-specific configuration.
     *
     * \param   lpName  IMU device name
     * \param   lpTag   Stores the device tag to differentiate multiple usage of
     *                  the same model
     *
     * \returns Returns created IMU descriptor
     */

    lp_IMU_t lp_device_IMU( 

        lp_Char_t const * const lpName, 
        lp_Char_t const * const lpTag

    );

    /*! \brief GPS device descriptor creator
     * 
     *  Create GPS device descriptor structure. It consider device model to 
     *  assign its device-specific configuration.
     *
     * \param   lpName  GPS device name
     * \param   lpTag   Stores the device tag to differentiate multiple usage of
     *                  the same model
     *
     * \return Returns created GPS descriptor
     */

    lp_GPS_t lp_device_GPS( 

        lp_Char_t const * const lpName, 
        lp_Char_t const * const lpTag 

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

