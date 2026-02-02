// #############################################################################
// #### Copyright ##############################################################
// #############################################################################

/*
 * Copyright 2024 BaSSeM
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

// #############################################################################
// #### Description ############################################################
// #############################################################################

// #############################################################################
// #### Control Include(s) #####################################################
// #############################################################################

#include "Platform.h"

// #############################################################################
// #### Control Macro(s) #######################################################
// #############################################################################

#ifndef DEBUG
    #define DEBUG
#endif

#ifdef DEBUG
    #undef DEBUG
#endif

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

#include "../../ADC_Internal.h"
#include "ADC_ADS1262.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

#define ADC_ADS1262_REGISTER_ID_DEFAULT        ( 0x00 ) // xxh
#define ADC_ADS1262_REGISTER_POWER_DEFAULT     ( 0x11 )
#define ADC_ADS1262_REGISTER_INTERFACE_DEFAULT ( 0x05 )
#define ADC_ADS1262_REGISTER_MODE0_DEFAULT     ( 0x00 )
#define ADC_ADS1262_REGISTER_MODE1_DEFAULT     ( 0x80 )
#define ADC_ADS1262_REGISTER_MODE2_DEFAULT     ( 0x04 )
#define ADC_ADS1262_REGISTER_INPMUX_DEFAULT    ( 0x01 )
#define ADC_ADS1262_REGISTER_OFCAL0_DEFAULT    ( 0x00 )
#define ADC_ADS1262_REGISTER_OFCAL1_DEFAULT    ( 0x00 )
#define ADC_ADS1262_REGISTER_OFCAL2_DEFAULT    ( 0x00 )
#define ADC_ADS1262_REGISTER_FSCAL0_DEFAULT    ( 0x00 )
#define ADC_ADS1262_REGISTER_FSCAL1_DEFAULT    ( 0x00 )
#define ADC_ADS1262_REGISTER_FSCAL2_DEFAULT    ( 0x40 )
#define ADC_ADS1262_REGISTER_IDACMUX_DEFAULT   ( 0xBB )
#define ADC_ADS1262_REGISTER_IDACMAG_DEFAULT   ( 0x00 )
#define ADC_ADS1262_REGISTER_REFMUX_DEFAULT    ( 0x00 )
#define ADC_ADS1262_REGISTER_TDACP_DEFAULT     ( 0x00 )
#define ADC_ADS1262_REGISTER_TDACN_DEFAULT     ( 0x00 )
#define ADC_ADS1262_REGISTER_GPIOCON_DEFAULT   ( 0x00 )
#define ADC_ADS1262_REGISTER_GPIODIR_DEFAULT   ( 0x00 )
#define ADC_ADS1262_REGISTER_GPIODAT_DEFAULT   ( 0x00 )
#define ADC_ADS1262_REGISTER_ADC2CFG_DEFAULT   ( 0x00 )
#define ADC_ADS1262_REGISTER_ADC2MUX_DEFAULT   ( 0x01 )
#define ADC_ADS1262_REGISTER_ADC2OFC0_DEFAULT  ( 0x00 )
#define ADC_ADS1262_REGISTER_ADC2OFC1_DEFAULT  ( 0x00 )
#define ADC_ADS1262_REGISTER_ADC2FSC0_DEFAULT  ( 0x00 )
#define ADC_ADS1262_REGISTER_ADC2FSC1_DEFAULT  ( 0x40 )

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef enum ADC_ADS1262_Command
{
    ADC_ADS1262_Command_NOP = 0b00000000,
    ADC_ADS1262_Command_RESET = 0b00000110,
    ADC_ADS1262_Command_START1 = 0b00001000,
    ADC_ADS1262_Command_STOP1 = 0b00001010,
    ADC_ADS1262_Command_START2 = 0b00001100,
    ADC_ADS1262_Command_STOP2 = 0b00001110,
    ADC_ADS1262_Command_RDATA1 = 0b00010010,
    ADC_ADS1262_Command_RDATA2 = 0b00010100,
    ADC_ADS1262_Command_SYOCAL1 = 0b00010110,
    ADC_ADS1262_Command_SYGCAL1 = 0b00010111,
    ADC_ADS1262_Command_SFOCAL1 = 0b00011001,
    ADC_ADS1262_Command_SYOCAL2 = 0b00011011,
    ADC_ADS1262_Command_SYGCAL2 = 0b00011100,
    ADC_ADS1262_Command_SFOCAL2 = 0b00011110,
    ADC_ADS1262_Command_RREG_Byte_1 = 0b00100000,
    ADC_ADS1262_Command_RREG_Byte_0 = 0b00000000,
    ADC_ADS1262_Command_WREG_Byte_1 = 0b01000000,
    ADC_ADS1262_Command_WREG_Byte_0 = 0b00000000,
} ADC_ADS1262_Command_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) ADC_ADS1262_Command_NOP
{
    const ADC_ADS1262_Command_t Command[ 1 ];
} ADC_ADS1262_Command_NOP_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) ADC_ADS1262_Command_RESET
{
    const ADC_ADS1262_Command_t Command[ 1 ];
} ADC_ADS1262_Command_RESET_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) ADC_ADS1262_Command_START1
{
    const ADC_ADS1262_Command_t Command[ 1 ];
} ADC_ADS1262_Command_START1_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) ADC_ADS1262_Command_STOP1
{
    const ADC_ADS1262_Command_t Command[ 1 ];
} ADC_ADS1262_Command_STOP1_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) ADC_ADS1262_Command_START2
{
    const ADC_ADS1262_Command_t Command[ 1 ];
} ADC_ADS1262_Command_START2_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) ADC_ADS1262_Command_STOP2
{
    const ADC_ADS1262_Command_t Command[ 1 ];
} ADC_ADS1262_Command_STOP2_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) ADC_ADS1262_Command_RDATA1
{
    const ADC_ADS1262_Command_t Command[ 1 ];
} ADC_ADS1262_Command_RDATA1_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) ADC_ADS1262_Command_RDATA2
{
    const ADC_ADS1262_Command_t Command[ 1 ];
} ADC_ADS1262_Command_RDATA2_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) ADC_ADS1262_Command_SYOCAL1
{
    const ADC_ADS1262_Command_t Command[ 1 ];
} ADC_ADS1262_Command_SYOCAL1_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) ADC_ADS1262_Command_SYGCAL1
{
    const ADC_ADS1262_Command_t Command[ 1 ];
} ADC_ADS1262_Command_SYGCAL1_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) ADC_ADS1262_Command_SFOCAL1
{
    const ADC_ADS1262_Command_t Command[ 1 ];
} ADC_ADS1262_Command_SFOCAL1_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) ADC_ADS1262_Command_SYOCAL2
{
    const ADC_ADS1262_Command_t Command[ 1 ];
} ADC_ADS1262_Command_SYOCAL2_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) ADC_ADS1262_Command_SYGCAL2
{
    const ADC_ADS1262_Command_t Command[ 1 ];
} ADC_ADS1262_Command_SYGCAL2_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) ADC_ADS1262_Command_SFOCAL2
{
    const ADC_ADS1262_Command_t Command[ 1 ];
} ADC_ADS1262_Command_SFOCAL2_t;

typedef union ADC_ADS1262_Command_RREG
{
    const ADC_ADS1262_Command_t Command[ 2 ];

    struct
    {
        uint8_t Address : 5;
        uint8_t         : 3;
        uint8_t Length  : 5;
        uint8_t         : 3;
    };
} ADC_ADS1262_Command_RREG_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) ADC_ADS1262_Command_WREG
{
    const ADC_ADS1262_Command_t Command[ 2 ];

    struct
    {
        uint8_t Address : 5;
        uint8_t         : 3;
        uint8_t Length  : 5;
        uint8_t         : 3;
    };
} ADC_ADS1262_Command_WREG_t;

typedef union ADC_ADS1262_Register_ID
{
    uint8_t Value;

    struct
    {
        uint8_t REV_ID : 5;
        uint8_t DEV_ID : 3;
    };
} ADC_ADS1262_Register_ID_t;

typedef union ADC_ADS1262_Register_POWER
{
    uint8_t Value;

    struct
    {
        uint8_t INTREF : 1;
        uint8_t VBIAS  : 1;
        uint8_t        : 2;
        uint8_t RESET  : 1;
        uint8_t        : 3;
    };
} ADC_ADS1262_Register_POWER_t;

typedef union ADC_ADS1262_Register_INTERFACE
{
    uint8_t Value;

    struct
    {
        uint8_t CRC     : 2;
        uint8_t STATUS  : 1;
        uint8_t TIMEOUT : 1;
        uint8_t         : 4;
    };
} ADC_ADS1262_Register_INTERFACE_t;

typedef union ADC_ADS1262_Register_MODE0
{
    uint8_t Value;

    struct
    {
        uint8_t DELAY    : 4;
        uint8_t CHOP     : 2;
        uint8_t RUN_MODE : 1;
        uint8_t REFREV   : 1;
    };
} ADC_ADS1262_Register_MODE0_t;

typedef union ADC_ADS1262_Register_MODE1
{
    uint8_t Value;

    struct
    {
        uint8_t SBMAG  : 3;
        uint8_t SBPOL  : 1;
        uint8_t SBADC  : 1;
        uint8_t FILTER : 3;
    };
} ADC_ADS1262_Register_MODE1_t;

typedef union ADC_ADS1262_Register_MODE2
{
    uint8_t Value;

    struct
    {
        uint8_t DR     : 4;
        uint8_t GAIN   : 3;
        uint8_t BYPASS : 1;
    };
} ADC_ADS1262_Register_MODE2_t;

typedef union ADC_ADS1262_Register_INPMUX
{
    uint8_t Value;

    struct
    {
        uint8_t MUXN : 4;
        uint8_t MUXP : 4;
    };
} ADC_ADS1262_Register_INPMUX_t;

typedef union ADC_ADS1262_Register_OFCAL0
{
    uint8_t Value;

    struct
    {
        uint8_t OFC : 8;
    };
} ADC_ADS1262_Register_OFCAL0_t;

typedef union ADC_ADS1262_Register_OFCAL1
{
    uint8_t Value;

    struct
    {
        uint8_t OFC : 8;
    };
} ADC_ADS1262_Register_OFCAL1_t;

typedef union ADC_ADS1262_Register_OFCAL2
{
    uint8_t Value;

    struct
    {
        uint8_t OFC : 8;
    };
} ADC_ADS1262_Register_OFCAL2_t;

typedef union ADC_ADS1262_Register_FSCAL0
{
    uint8_t Value;

    struct
    {
        uint8_t FSC : 8;
    };
} ADC_ADS1262_Register_FSCAL0_t;

typedef union ADC_ADS1262_Register_FSCAL1
{
    uint8_t Value;

    struct
    {
        uint8_t FSC : 8;
    };
} ADC_ADS1262_Register_FSCAL1_t;

typedef union ADC_ADS1262_Register_FSCAL2
{
    uint8_t Value;

    struct
    {
        uint8_t FSC : 8;
    };
} ADC_ADS1262_Register_FSCAL2_t;

typedef union ADC_ADS1262_Register_IDACMUX
{
    uint8_t Value;

    struct
    {
        uint8_t MUX1 : 4;
        uint8_t MUX2 : 4;
    };
} ADC_ADS1262_Register_IDACMUX_t;

typedef union ADC_ADS1262_Register_IDACMAG
{
    uint8_t Value;

    struct
    {
        uint8_t MAG1 : 4;
        uint8_t MAG2 : 4;
    };
} ADC_ADS1262_Register_IDACMAG_t;

typedef union ADC_ADS1262_Register_REFMUX
{
    uint8_t Value;

    struct
    {
        uint8_t RMUXN : 3;
        uint8_t RMUXP : 3;
        uint8_t       : 2;
    };
} ADC_ADS1262_Register_REFMUX_t;

typedef union ADC_ADS1262_Register_TDACP
{
    uint8_t Value;

    struct
    {
        uint8_t MAGP : 4;
        uint8_t      : 2;
        uint8_t OUTP : 2;
    };
} ADC_ADS1262_Register_TDACP_t;

typedef union ADC_ADS1262_Register_TDACN
{
    uint8_t Value;

    struct
    {
        uint8_t MAGN : 4;
        uint8_t      : 2;
        uint8_t OUTN : 2;
    };
} ADC_ADS1262_Register_TDACN_t;

typedef union ADC_ADS1262_Register_GPIOCON
{
    uint8_t Value;

    struct
    {
        uint8_t CON : 8;
    };
} ADC_ADS1262_Register_GPIOCON_t;

typedef union ADC_ADS1262_Register_GPIODIR
{
    uint8_t Value;

    struct
    {
        uint8_t DIR : 8;
    };
} ADC_ADS1262_Register_GPIODIR_t;

typedef union ADC_ADS1262_Register_GPIODAT
{
    uint8_t Value;

    struct
    {
        uint8_t DAT : 8;
    };
} ADC_ADS1262_Register_GPIODAT_t;

typedef union ADC_ADS1262_Register_ADC2CFG
{
    uint8_t Value;

    struct
    {
        uint8_t GAIN2 : 3;
        uint8_t REF2  : 3;
        uint8_t DR2   : 2;
    };
} ADC_ADS1262_Register_ADC2CFG_t;

typedef union ADC_ADS1262_Register_ADC2MUX
{
    uint8_t Value;

    struct
    {
        uint8_t MUXN2 : 4;
        uint8_t MUXP2 : 4;
    };
} ADC_ADS1262_Register_ADC2MUX_t;

typedef union ADC_ADS1262_Register_ADC2OFC0
{
    uint8_t Value;

    struct
    {
        uint8_t OFC2 : 8;
    };
} ADC_ADS1262_Register_ADC2OFC0_t;

typedef union ADC_ADS1262_Register_ADC2OFC1
{
    uint8_t Value;

    struct
    {
        uint8_t OFC2 : 8;
    };
} ADC_ADS1262_Register_ADC2OFC1_t;

typedef union ADC_ADS1262_Register_ADC2FSC0
{
    uint8_t Value;

    struct
    {
        uint8_t FSC2 : 8;
    };
} ADC_ADS1262_Register_ADC2FSC0_t;

typedef union ADC_ADS1262_Register_ADC2FSC1
{
    uint8_t Value;

    struct
    {
        uint8_t FSC2 : 8;
    };
} ADC_ADS1262_Register_ADC2FSC1_t;

typedef union ADC_ADS1262_Byte_STATUS
{
    uint8_t Value;

    struct
    {
        uint8_t RESET    : 1;
        uint8_t PGAD_ALM : 1;
        uint8_t PGAH_ALM : 1;
        uint8_t PGAL_ALM : 1;
        uint8_t REF_ALM  : 1;
        uint8_t EXTCLK   : 1;
        uint8_t ADC1     : 1;
        uint8_t ADC2     : 1;
    };
} ADC_ADS1262_Byte_STATUS_t;

typedef union ADC_ADS1262_Byte_CRC
{
    uint8_t Value;

    struct
    {
        uint8_t SUM : 8;
    };
} ADC_ADS1262_Byte_CRC_t;

typedef ADC_ADS1262_Byte_CRC_t ADC_ADS1262_Byte_CHK_t;

typedef struct ADC_ADS1262_Instance_Context
{
    ADC_ADS1262_Register_ID_t Register_ID;
    ADC_ADS1262_Register_POWER_t Register_POWER;
    ADC_ADS1262_Register_INTERFACE_t Register_INTERFACE;
    ADC_ADS1262_Register_MODE0_t Register_MODE0;
    ADC_ADS1262_Register_MODE1_t Register_MODE1;
    ADC_ADS1262_Register_MODE2_t Register_MODE2;
    ADC_ADS1262_Register_INPMUX_t Register_INPMUX;
    ADC_ADS1262_Register_OFCAL0_t Register_OFCAL0;
    ADC_ADS1262_Register_OFCAL1_t Register_OFCAL1;
    ADC_ADS1262_Register_OFCAL2_t Register_OFCAL2;
    ADC_ADS1262_Register_FSCAL0_t Register_FSCAL0;
    ADC_ADS1262_Register_FSCAL1_t Register_FSCAL1;
    ADC_ADS1262_Register_FSCAL2_t Register_FSCAL2;
    ADC_ADS1262_Register_IDACMUX_t Register_IDACMUX;
    ADC_ADS1262_Register_IDACMAG_t Register_IDACMAG;
    ADC_ADS1262_Register_REFMUX_t Register_REFMUX;
    ADC_ADS1262_Register_TDACP_t Register_TDACP;
    ADC_ADS1262_Register_TDACN_t Register_TDACN;
    ADC_ADS1262_Register_GPIOCON_t Register_GPIOCON;
    ADC_ADS1262_Register_GPIODIR_t Register_GPIODIR;
    ADC_ADS1262_Register_GPIODAT_t Register_GPIODAT;
    ADC_ADS1262_Register_ADC2CFG_t Register_ADC2CFG;
    ADC_ADS1262_Register_ADC2MUX_t Register_ADC2MUX;
    ADC_ADS1262_Register_ADC2OFC0_t Register_ADC2OFC0;
    ADC_ADS1262_Register_ADC2OFC1_t Register_ADC2OFC1;
    ADC_ADS1262_Register_ADC2FSC0_t Register_ADC2FSC0;
    ADC_ADS1262_Register_ADC2FSC1_t Register_ADC2FSC1;
} ADC_ADS1262_Instance_Context_t;

typedef struct ADC_ADS1262_Context
{
    TIM_Timestamp_t Timestamp;
} ADC_ADS1262_Context_t;

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

static ADC_ADS1262_Status_t ADC_ADS1262_Instance_Initialize( ADC_ADS1262_Instance_t * Instance );
static ADC_ADS1262_Status_t ADC_ADS1262_Instance_Cycle( ADC_ADS1262_Instance_t * Instance );
static ADC_ADS1262_Status_t ADC_ADS1262_Instance_DeInitialize( ADC_ADS1262_Instance_t * Instance );
//
static ADC_ADS1262_Status_t ADC_ADS1262_Context_Initialize( void );
static ADC_ADS1262_Status_t ADC_ADS1262_Context_Cycle( void );
static ADC_ADS1262_Status_t ADC_ADS1262_Context_DeInitialize( void );

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

static ADC_ADS1262_Context_t ADC_ADS1262_Context;

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

static ADC_ADS1262_Status_t ADC_ADS1262_Instance_Initialize( ADC_ADS1262_Instance_t * Instance )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_Success;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        Instance->Context->Register_ID.Value = ADC_ADS1262_REGISTER_ID_DEFAULT;
        Instance->Context->Register_POWER.Value = ADC_ADS1262_REGISTER_POWER_DEFAULT;
        Instance->Context->Register_INTERFACE.Value = ADC_ADS1262_REGISTER_INTERFACE_DEFAULT;
        Instance->Context->Register_MODE0.Value = ADC_ADS1262_REGISTER_MODE0_DEFAULT;
        Instance->Context->Register_MODE1.Value = ADC_ADS1262_REGISTER_MODE1_DEFAULT;
        Instance->Context->Register_MODE2.Value = ADC_ADS1262_REGISTER_MODE2_DEFAULT;
        Instance->Context->Register_INPMUX.Value = ADC_ADS1262_REGISTER_INPMUX_DEFAULT;
        Instance->Context->Register_OFCAL0.Value = ADC_ADS1262_REGISTER_OFCAL0_DEFAULT;
        Instance->Context->Register_OFCAL1.Value = ADC_ADS1262_REGISTER_OFCAL1_DEFAULT;
        Instance->Context->Register_OFCAL2.Value = ADC_ADS1262_REGISTER_OFCAL2_DEFAULT;
        Instance->Context->Register_FSCAL0.Value = ADC_ADS1262_REGISTER_FSCAL0_DEFAULT;
        Instance->Context->Register_FSCAL1.Value = ADC_ADS1262_REGISTER_FSCAL1_DEFAULT;
        Instance->Context->Register_FSCAL2.Value = ADC_ADS1262_REGISTER_FSCAL2_DEFAULT;
        Instance->Context->Register_IDACMUX.Value = ADC_ADS1262_REGISTER_IDACMUX_DEFAULT;
        Instance->Context->Register_IDACMAG.Value = ADC_ADS1262_REGISTER_IDACMAG_DEFAULT;
        Instance->Context->Register_REFMUX.Value = ADC_ADS1262_REGISTER_REFMUX_DEFAULT;
        Instance->Context->Register_TDACP.Value = ADC_ADS1262_REGISTER_TDACP_DEFAULT;
        Instance->Context->Register_TDACN.Value = ADC_ADS1262_REGISTER_TDACN_DEFAULT;
        Instance->Context->Register_GPIOCON.Value = ADC_ADS1262_REGISTER_GPIOCON_DEFAULT;
        Instance->Context->Register_GPIODIR.Value = ADC_ADS1262_REGISTER_GPIODIR_DEFAULT;
        Instance->Context->Register_GPIODAT.Value = ADC_ADS1262_REGISTER_GPIODAT_DEFAULT;
        Instance->Context->Register_ADC2CFG.Value = ADC_ADS1262_REGISTER_ADC2CFG_DEFAULT;
        Instance->Context->Register_ADC2MUX.Value = ADC_ADS1262_REGISTER_ADC2MUX_DEFAULT;
        Instance->Context->Register_ADC2OFC0.Value = ADC_ADS1262_REGISTER_ADC2OFC0_DEFAULT;
        Instance->Context->Register_ADC2OFC1.Value = ADC_ADS1262_REGISTER_ADC2OFC1_DEFAULT;
        Instance->Context->Register_ADC2FSC0.Value = ADC_ADS1262_REGISTER_ADC2FSC0_DEFAULT;
        Instance->Context->Register_ADC2FSC1.Value = ADC_ADS1262_REGISTER_ADC2FSC1_DEFAULT;
    }
    while ( 0 );

    return Status;
}

static ADC_ADS1262_Status_t ADC_ADS1262_Instance_Cycle( ADC_ADS1262_Instance_t * Instance )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_Success;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

static ADC_ADS1262_Status_t ADC_ADS1262_Instance_DeInitialize( ADC_ADS1262_Instance_t * Instance )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_Success;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

static ADC_ADS1262_Status_t ADC_ADS1262_Context_Initialize( void )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_Success;
    TIM_Status_t TIM_Status = TIM_Status_Success;

    do
    {
        ADC_Trace( "%s( void )", __FUNCTION__ );

        if ( ( TIM_Status = TIM_GetTimestamp( ADC_TIM, &ADC_ADS1262_Context.Timestamp ) ) != TIM_Status_Success )
        {
            Status = ADC_ADS1262_Status_Error;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static ADC_ADS1262_Status_t ADC_ADS1262_Context_Cycle( void )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_Success;
    TIM_Status_t TIM_Status = TIM_Status_Success;

    do
    {
        ADC_Trace( "%s( void )", __FUNCTION__ );

        if ( ( TIM_Status = TIM_GetTimestamp( ADC_TIM, &ADC_ADS1262_Context.Timestamp ) ) != TIM_Status_Success )
        {
            Status = ADC_ADS1262_Status_Error;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static ADC_ADS1262_Status_t ADC_ADS1262_Context_DeInitialize( void )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_Success;

    do
    {
        ADC_Trace( "%s( void )", __FUNCTION__ );
    }
    while ( 0 );

    return Status;
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

ADC_ADS1262_Status_t ADC_ADS1262_Initialize( ADC_ADS1262_Instance_t * Instance )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_Success;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( ( Status = ADC_ADS1262_Context_Initialize( ) ) != ADC_ADS1262_Status_Success )
        {
            break;
        }

        if ( ( Status = ADC_ADS1262_Instance_Initialize( Instance ) ) != ADC_ADS1262_Status_Success )
        {
            break;
        }
    }
    while ( 0 );

    return Status;
}

ADC_ADS1262_Status_t ADC_ADS1262_Cycle( ADC_ADS1262_Instance_t * Instance )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_Success;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( ( Status = ADC_ADS1262_Context_Cycle( ) ) != ADC_ADS1262_Status_Success )
        {
            break;
        }

        if ( ( Status = ADC_ADS1262_Instance_Cycle( Instance ) ) != ADC_ADS1262_Status_Success )
        {
            break;
        }
    }
    while ( 0 );

    return Status;
}

ADC_ADS1262_Status_t ADC_ADS1262_DeInitialize( ADC_ADS1262_Instance_t * Instance )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_Success;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( ( Status = ADC_ADS1262_Instance_DeInitialize( Instance ) ) != ADC_ADS1262_Status_Success )
        {
            break;
        }

        if ( ( Status = ADC_ADS1262_Context_DeInitialize( ) ) != ADC_ADS1262_Status_Success )
        {
            break;
        }
    }
    while ( 0 );

    return Status;
}

ADC_ADS1262_Status_t ADC_ADS1262_GetIdentification( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_ID_Revision_t * ID_Revision, ADC_ADS1262_ID_Device_t * ID_Device )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_NotSupported;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

ADC_ADS1262_Status_t ADC_ADS1262_SetPower( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_Power_InternalReference_t Power_InternalReference, ADC_ADS1262_Power_LevelShiftVoltage_t Power_LevelShiftVoltage, ADC_ADS1262_Power_ResetIndicator_t * Power_ResetIndicator )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_NotSupported;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

ADC_ADS1262_Status_t ADC_ADS1262_SetInterface( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_Interface_CRC_t Interface_CRC, ADC_ADS1262_Interface_Status_t Interface_Status, ADC_ADS1262_Interface_Timeout_t Interface_Timeout )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_NotSupported;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

ADC_ADS1262_Status_t ADC_ADS1262_SetMode0( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_Mode_ConversionDelay_t Mode_ConversionDelay, ADC_ADS1262_Mode_Chop_t Mode_Chop, ADC_ADS1262_Mode_Conversion_t Mode_Conversion, ADC_ADS1262_Mode_ReferencePolarityMUX_t Mode_ReferencePolarityMUX )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_NotSupported;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

ADC_ADS1262_Status_t ADC_ADS1262_SetMode1( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_Mode_BiasMagnitude_t Mode_BiasMagnitude, ADC_ADS1262_Mode_BiasPolarity_t Mode_BiasPolarity, ADC_ADS1262_Mode_BiasConnection_t Mode_BiasConnection, ADC_ADS1262_Mode_Filter_t Mode_Filter )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_NotSupported;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

ADC_ADS1262_Status_t ADC_ADS1262_SetMode2( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_Mode_DataRate_t Mode_DataRate, ADC_ADS1262_Mode_Gain_t Mode_Gain, ADC_ADS1262_Mode_ProgrammableGainAmplifierBypass_t Mode_ProgrammableGainAmplifierBypass )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_NotSupported;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

ADC_ADS1262_Status_t ADC_ADS1262_SetInputMUX( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_InputMultiplexer_Negative_t InputMultiplexer_Negative, ADC_ADS1262_InputMultiplexer_Positive_t InputMultiplexer_Positive )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_NotSupported;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

ADC_ADS1262_Status_t ADC_ADS1262_SetCalibrationOffset( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_CalibrationOffset_t CalibrationOffset )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_NotSupported;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

ADC_ADS1262_Status_t ADC_ADS1262_SetCalibrationFullScale( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_CalibrationFullScale_t CalibrationFullScale )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_NotSupported;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

ADC_ADS1262_Status_t ADC_ADS1262_SetIDAC_MUX( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_IDAC_1_Multiplexer_t ADC_ADS1262_IDAC_1_Multiplexer, ADC_ADS1262_IDAC_2_Multiplexer_t IDAC_2_Multiplexer )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_NotSupported;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

ADC_ADS1262_Status_t ADC_ADS1262_SetIDAC_Magnitude( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_IDCA_1_Magnitude_t ADC_ADS1262_IDCA_1_Magnitude, ADC_ADS1262_IDCA_2_Magnitude_t IDCA_2_Magnitude )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_NotSupported;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

ADC_ADS1262_Status_t ADC_ADS1262_SetREF_MUX( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_ReferenceMultiplexer_Negative_t ReferenceMultiplexer_Negative, ADC_ADS1262_ReferenceMultiplexer_Positive_t ReferenceMultiplexer_Positive )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_NotSupported;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

ADC_ADS1262_Status_t ADC_ADS1262_SetTDAC_Positive( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_TDACP_Magnitude_t TDACP_Magnitude, ADC_ADS1262_TDACP_Output_t TDACP_Output )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_NotSupported;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

ADC_ADS1262_Status_t ADC_ADS1262_SetTDAC_Negative( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_TDACN_Magnitude_t TDACN_Magnitude, ADC_ADS1262_TDACN_Output_t TDACN_Output )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_NotSupported;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

ADC_ADS1262_Status_t ADC_ADS1262_SetGPIOConnection( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_GPIO_0_Connection_t GPIO_0_Connection, ADC_ADS1262_GPIO_1_Connection_t GPIO_1_Connection, ADC_ADS1262_GPIO_2_Connection_t GPIO_2_Connection, ADC_ADS1262_GPIO_3_Connection_t GPIO_3_Connection, ADC_ADS1262_GPIO_4_Connection_t GPIO_4_Connection, ADC_ADS1262_GPIO_5_Connection_t GPIO_5_Connection, ADC_ADS1262_GPIO_6_Connection_t GPIO_6_Connection, ADC_ADS1262_GPIO_7_Connection_t GPIO_7_Connection )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_NotSupported;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

ADC_ADS1262_Status_t ADC_ADS1262_SetGPIODirection( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_GPIO_0_Direction_t GPIO_0_Direction, ADC_ADS1262_GPIO_1_Direction_t GPIO_1_Direction, ADC_ADS1262_GPIO_2_Direction_t GPIO_2_Direction, ADC_ADS1262_GPIO_3_Direction_t GPIO_3_Direction, ADC_ADS1262_GPIO_4_Direction_t GPIO_4_Direction, ADC_ADS1262_GPIO_5_Direction_t GPIO_5_Direction, ADC_ADS1262_GPIO_6_Direction_t GPIO_6_Direction, ADC_ADS1262_GPIO_7_Direction_t GPIO_7_Direction )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_NotSupported;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

ADC_ADS1262_Status_t ADC_ADS1262_SetGPIOData( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_GPIO_0_Data_t GPIO_0_Data, ADC_ADS1262_GPIO_1_Data_t GPIO_1_Data, ADC_ADS1262_GPIO_2_Data_t GPIO_2_Data, ADC_ADS1262_GPIO_3_Data_t GPIO_3_Data, ADC_ADS1262_GPIO_4_Data_t GPIO_4_Data, ADC_ADS1262_GPIO_5_Data_t GPIO_5_Data, ADC_ADS1262_GPIO_6_Data_t GPIO_6_Data, ADC_ADS1262_GPIO_7_Data_t GPIO_7_Data )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_NotSupported;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

ADC_ADS1262_Status_t ADC_ADS1262_ADC_2_SetConfiguration( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_ADC_2_Mode_Gain_t ADC_2_Mode_Gain, ADC_ADS1262_ADC_2_InputReference_t ADC_2_InputReference, ADC_ADS1262_ADC_2_DataRate_t ADC_2_DataRate )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_NotSupported;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

ADC_ADS1262_Status_t ADC_ADS1262_ADC_2_SetInputMUX( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_ADC_2_InputMultiplexer_Negative_t ADC_2_InputMultiplexer_Negative, ADC_ADS1262_ADC_2_InputMultiplexer_Positive_t ADC_2_InputMultiplexer_Positive )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_NotSupported;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

ADC_ADS1262_Status_t ADC_ADS1262_ADC_2_SetCalibrationOffset( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_ADC_2_CalibrationOffset_t ADC_2_CalibrationOffset )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_NotSupported;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

ADC_ADS1262_Status_t ADC_ADS1262_ADC_2_SetCalibrationFullScale( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_ADC_2_CalibrationFullScale_t ADC_2_CalibrationFullScale )
{
    ADC_ADS1262_Status_t Status = ADC_ADS1262_Status_NotSupported;

    do
    {
        ADC_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

const char ADC_ADS1262_VERSION[] = "0.0.0.v20260202-1914";

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
