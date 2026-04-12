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

/**
 *  @file
 *
 *  @brief Platform ADC ADS1262 Driver
 */

// #############################################################################
// #### Control Include(s) #####################################################
// #############################################################################

// #############################################################################
// #### Control Macro(s) #######################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

/**
 *  @addtogroup Platform_ADC_Driver
 *
 *  @{
 */

/**
 *  @defgroup Platform_ADC_ADS1262 ADS1262
 *
 *  @{
 */

#ifndef ADC_ADS1262_H_
    #define ADC_ADS1262_H_

    #ifdef __cplusplus
extern "C"
{
    #endif /* __cplusplus */

    // #############################################################################
    // #### Include(s) #############################################################
    // #############################################################################

    #include <stdint.h>

    // #############################################################################
    // #### Public Macro(s) ########################################################
    // #############################################################################

    // #############################################################################
    // #### Public Type(s) #########################################################
    // #############################################################################

    /**
     *  @brief ADC ADS1262 Operation Status
     *
     *  @enum ADC_ADS1262_Status_t
     */
    typedef enum ADC_ADS1262_Status
    {
        ADC_ADS1262_Status_Success = 0,     ///< Success
        ADC_ADS1262_Status_ArgumentInvalid, ///< Argument Invalid
        ADC_ADS1262_Status_NotSupported,    ///< Not Supported
        ADC_ADS1262_Status_Error,           ///< General Error
        ADC_ADS1262_Status_Busy,            ///< Busy
        ADC_ADS1262_Status_Timeout,         ///< Timeout
    } ADC_ADS1262_Status_t;

    /**
     *  @brief ADC ADS1262 Instance Context
     *
     *  @struct ADC_ADS1262_InstanceContext_t
     */
    typedef struct ADC_ADS1262_InstanceContext ADC_ADS1262_InstanceContext_t;

    /**
     *  @brief ADC ADS1262 Instance
     *
     *  @struct ADC_ADS1262_Instance_t
     */
    typedef struct ADC_ADS1262_Instance
    {
        SPI_t SPI;
        GPIO_t Start;
        GPIO_t ChipSelect;
        GPIO_t DataOut;
        GPIO_t DataReady;
        GPIO_t Reset;

        // @note Managed Internally
        ADC_ADS1262_InstanceContext_t * Context;
    } ADC_ADS1262_Instance_t;

    typedef uint8_t ADC_ADS1262_ID_Revision_t;

    typedef enum ADC_ADS1262_ID_Device
    {
        ADC_ADS1262_ID_Device_ADS1262 = 0,
        ADC_ADS1262_ID_Device_ADS1263,
    } ADC_ADS1262_ID_Device_t;

    typedef enum ADC_ADS1262_Power_InternalReference
    {
        ADC_ADS1262_Power_InternalReference_Disable = 0,
        ADC_ADS1262_Power_InternalReference_Enable,
    } ADC_ADS1262_Power_InternalReference_t;

    typedef enum ADC_ADS1262_Power_LevelShiftVoltage
    {
        ADC_ADS1262_Power_LevelShiftVoltage_Disable = 0,
        ADC_ADS1262_Power_LevelShiftVoltage_Enable,
    } ADC_ADS1262_Power_LevelShiftVoltage_t;

    typedef enum ADC_ADS1262_Power_ResetIndicator
    {
        ADC_ADS1262_Power_ResetIndicator_False = 0,
        ADC_ADS1262_Power_ResetIndicator_True,
    } ADC_ADS1262_Power_ResetIndicator_t;

    typedef enum ADC_ADS1262_Interface_CRC
    {
        ADC_ADS1262_Interface_CRC_Disable = 0,
        ADC_ADS1262_Interface_CRC_EnableChecksum,
        ADC_ADS1262_Interface_CRC_EnableCRC,
    } ADC_ADS1262_Interface_CRC_t;

    typedef enum ADC_ADS1262_Interface_Status
    {
        ADC_ADS1262_Interface_Status_Disable = 0,
        ADC_ADS1262_Interface_Status_Enable,
    } ADC_ADS1262_Interface_Status_t;

    typedef enum ADC_ADS1262_Interface_Timeout
    {
        ADC_ADS1262_Interface_Timeout_Disable = 0,
        ADC_ADS1262_Interface_Timeout_Enable,
    } ADC_ADS1262_Interface_Timeout_t;

    typedef enum ADC_ADS1262_Mode_ConversionDelay
    {
        ADC_ADS1262_Mode_ConversionDelay_Disable = 0,
        ADC_ADS1262_Mode_ConversionDelay_8700ns, // 8.7 us
        ADC_ADS1262_Mode_ConversionDelay_17us,
        ADC_ADS1262_Mode_ConversionDelay_35us,
        ADC_ADS1262_Mode_ConversionDelay_69us,
        ADC_ADS1262_Mode_ConversionDelay_139us,
        ADC_ADS1262_Mode_ConversionDelay_278us,
        ADC_ADS1262_Mode_ConversionDelay_555us,
        ADC_ADS1262_Mode_ConversionDelay_1100us, // 1.1 ms
        ADC_ADS1262_Mode_ConversionDelay_2200us, // 2.2 ms
        ADC_ADS1262_Mode_ConversionDelay_4400us, // 4.4 ms
        ADC_ADS1262_Mode_ConversionDelay_8800us, // 8.8 ms
    } ADC_ADS1262_Mode_ConversionDelay_t;

    typedef enum ADC_ADS1262_Mode_Chop
    {
        ADC_ADS1262_Mode_Chop_Disable = 0,
        ADC_ADS1262_Mode_Chop_Input,
        ADC_ADS1262_Mode_Chop_IDAC,
        ADC_ADS1262_Mode_Chop_Both,
    } ADC_ADS1262_Mode_Chop_t;

    typedef enum ADC_ADS1262_Mode_Conversion
    {
        ADC_ADS1262_Mode_Conversion_Continuous = 0,
        ADC_ADS1262_Mode_Conversion_Single,
    } ADC_ADS1262_Mode_Conversion_t;

    typedef enum ADC_ADS1262_Mode_ReferencePolarityMUX
    {
        ADC_ADS1262_Mode_ReferencePolarityMUX_Normal = 0,
        ADC_ADS1262_Mode_ReferencePolarityMUX_Reverse,
    } ADC_ADS1262_Mode_ReferencePolarityMUX_t;

    typedef enum ADC_ADS1262_Mode_BiasMagnitude
    {
        ADC_ADS1262_Mode_BiasMagnitude_Disable = 0,

        // Current Bias
        ADC_ADS1262_Mode_BiasMagnitude_500nA,
        ADC_ADS1262_Mode_BiasMagnitude_2uA,
        ADC_ADS1262_Mode_BiasMagnitude_10uA,
        ADC_ADS1262_Mode_BiasMagnitude_50uA,
        ADC_ADS1262_Mode_BiasMagnitude_200uA,

        // Resistor Bias
        ADC_ADS1262_Mode_BiasMagnitude_10MOhm,
    } ADC_ADS1262_Mode_BiasMagnitude_t;

    typedef enum ADC_ADS1262_Mode_BiasPolarity
    {
        ADC_ADS1262_Mode_BiasPolarity_PullUp = 0,
        ADC_ADS1262_Mode_BiasPolarity_PullDown,
    } ADC_ADS1262_Mode_BiasPolarity_t;

    typedef enum ADC_ADS1262_Mode_BiasConnection
    {
        ADC_ADS1262_Mode_BiasConnection_ADC_1 = 0,
        ADC_ADS1262_Mode_BiasConnection_ADC_2,
    } ADC_ADS1262_Mode_BiasConnection_t;

    typedef enum ADC_ADS1262_Mode_Filter
    {
        ADC_ADS1262_Mode_Filter_Sinc_1 = 0,
        ADC_ADS1262_Mode_Filter_Sinc_2,
        ADC_ADS1262_Mode_Filter_Sinc_3,
        ADC_ADS1262_Mode_Filter_Sinc_4,
        ADC_ADS1262_Mode_Filter_FIR,
    } ADC_ADS1262_Mode_Filter_t;

    typedef enum ADC_ADS1262_Mode_DataRate
    {
        ADC_ADS1262_Mode_DataRate_2_5_SPS = 0, // 2.5 SPS
        ADC_ADS1262_Mode_DataRate_5_SPS,
        ADC_ADS1262_Mode_DataRate_10_SPS,
        ADC_ADS1262_Mode_DataRate_16_6_SPS, // 16.6 SPS
        ADC_ADS1262_Mode_DataRate_20_SPS,
        ADC_ADS1262_Mode_DataRate_50_SPS,
        ADC_ADS1262_Mode_DataRate_60_SPS,
        ADC_ADS1262_Mode_DataRate_100_SPS,
        ADC_ADS1262_Mode_DataRate_400_SPS,
        ADC_ADS1262_Mode_DataRate_1200_SPS,
        ADC_ADS1262_Mode_DataRate_2400_SPS,
        ADC_ADS1262_Mode_DataRate_4800_SPS,
        ADC_ADS1262_Mode_DataRate_7200_SPS,
        ADC_ADS1262_Mode_DataRate_14400_SPS,
        ADC_ADS1262_Mode_DataRate_19200_SPS,
        ADC_ADS1262_Mode_DataRate_38400_SPS,
    } ADC_ADS1262_Mode_DataRate_t;

    typedef enum ADC_ADS1262_Mode_Gain
    {
        ADC_ADS1262_Mode_Gain_x1 = 0,
        ADC_ADS1262_Mode_Gain_x2,
        ADC_ADS1262_Mode_Gain_x4,
        ADC_ADS1262_Mode_Gain_x8,
        ADC_ADS1262_Mode_Gain_x16,
        ADC_ADS1262_Mode_Gain_x32,
    } ADC_ADS1262_Mode_Gain_t;

    typedef enum ADC_ADS1262_Mode_ProgrammableGainAmplifierBypass
    {
        ADC_ADS1262_Mode_ProgrammableGainAmplifierBypass_Disable = 0,
        ADC_ADS1262_Mode_ProgrammableGainAmplifierBypass_Enable,
    } ADC_ADS1262_Mode_ProgrammableGainAmplifierBypass_t;

    typedef enum ADC_ADS1262_InputMultiplexer_Negative
    {
        ADC_ADS1262_InputMultiplexer_Negative_AIN0 = 0,
        ADC_ADS1262_InputMultiplexer_Negative_AIN1,
        ADC_ADS1262_InputMultiplexer_Negative_AIN2,
        ADC_ADS1262_InputMultiplexer_Negative_AIN3,
        ADC_ADS1262_InputMultiplexer_Negative_AIN4,
        ADC_ADS1262_InputMultiplexer_Negative_AIN5,
        ADC_ADS1262_InputMultiplexer_Negative_AIN6,
        ADC_ADS1262_InputMultiplexer_Negative_AIN7,
        ADC_ADS1262_InputMultiplexer_Negative_AIN8,
        ADC_ADS1262_InputMultiplexer_Negative_AIN9,
        ADC_ADS1262_InputMultiplexer_Negative_AINCOM,
        ADC_ADS1262_InputMultiplexer_Negative_Temperature,
        ADC_ADS1262_InputMultiplexer_Negative_SupplyAnalog,
        ADC_ADS1262_InputMultiplexer_Negative_SupplyDigital,
        ADC_ADS1262_InputMultiplexer_Negative_TDAC,
        ADC_ADS1262_InputMultiplexer_Negative_Float,
    } ADC_ADS1262_InputMultiplexer_Negative_t;

    typedef enum ADC_ADS1262_InputMultiplexer_Positive
    {
        ADC_ADS1262_InputMultiplexer_Positive_AIN0 = 0,
        ADC_ADS1262_InputMultiplexer_Positive_AIN1,
        ADC_ADS1262_InputMultiplexer_Positive_AIN2,
        ADC_ADS1262_InputMultiplexer_Positive_AIN3,
        ADC_ADS1262_InputMultiplexer_Positive_AIN4,
        ADC_ADS1262_InputMultiplexer_Positive_AIN5,
        ADC_ADS1262_InputMultiplexer_Positive_AIN6,
        ADC_ADS1262_InputMultiplexer_Positive_AIN7,
        ADC_ADS1262_InputMultiplexer_Positive_AIN8,
        ADC_ADS1262_InputMultiplexer_Positive_AIN9,
        ADC_ADS1262_InputMultiplexer_Positive_AINCOM,
        ADC_ADS1262_InputMultiplexer_Positive_Temperature,
        ADC_ADS1262_InputMultiplexer_Positive_SupplyAnalog,
        ADC_ADS1262_InputMultiplexer_Positive_SupplyDigital,
        ADC_ADS1262_InputMultiplexer_Positive_TDAC,
        ADC_ADS1262_InputMultiplexer_Positive_Float,
    } ADC_ADS1262_InputMultiplexer_Positive_t;

    typedef int32_t ADC_ADS1262_CalibrationOffset_t;

    typedef int32_t ADC_ADS1262_CalibrationFullScale_t;

    typedef enum ADC_ADS1262_IDAC_1_Multiplexer
    {
        ADC_ADS1262_IDAC_1_Multiplexer_AIN0 = 0,
        ADC_ADS1262_IDAC_1_Multiplexer_AIN1,
        ADC_ADS1262_IDAC_1_Multiplexer_AIN2,
        ADC_ADS1262_IDAC_1_Multiplexer_AIN3,
        ADC_ADS1262_IDAC_1_Multiplexer_AIN4,
        ADC_ADS1262_IDAC_1_Multiplexer_AIN5,
        ADC_ADS1262_IDAC_1_Multiplexer_AIN6,
        ADC_ADS1262_IDAC_1_Multiplexer_AIN7,
        ADC_ADS1262_IDAC_1_Multiplexer_AIN8,
        ADC_ADS1262_IDAC_1_Multiplexer_AIN9,
        ADC_ADS1262_IDAC_1_Multiplexer_AINCOM,
        ADC_ADS1262_IDAC_1_Multiplexer_Float,
    } ADC_ADS1262_IDAC_1_Multiplexer_t;

    typedef enum ADC_ADS1262_IDAC_2_Multiplexer
    {
        ADC_ADS1262_IDAC_2_Multiplexer_AIN0 = 0,
        ADC_ADS1262_IDAC_2_Multiplexer_AIN1,
        ADC_ADS1262_IDAC_2_Multiplexer_AIN2,
        ADC_ADS1262_IDAC_2_Multiplexer_AIN3,
        ADC_ADS1262_IDAC_2_Multiplexer_AIN4,
        ADC_ADS1262_IDAC_2_Multiplexer_AIN5,
        ADC_ADS1262_IDAC_2_Multiplexer_AIN6,
        ADC_ADS1262_IDAC_2_Multiplexer_AIN7,
        ADC_ADS1262_IDAC_2_Multiplexer_AIN8,
        ADC_ADS1262_IDAC_2_Multiplexer_AIN9,
        ADC_ADS1262_IDAC_2_Multiplexer_AINCOM,
        ADC_ADS1262_IDAC_2_Multiplexer_Float,
    } ADC_ADS1262_IDAC_2_Multiplexer_t;

    typedef enum ADC_ADS1262_IDCA_1_Magnitude
    {
        ADC_ADS1262_IDCA_1_Magnitude_Disable = 0,
        ADC_ADS1262_IDCA_1_Magnitude_50uA,
        ADC_ADS1262_IDCA_1_Magnitude_100uA,
        ADC_ADS1262_IDCA_1_Magnitude_250uA,
        ADC_ADS1262_IDCA_1_Magnitude_500uA,
        ADC_ADS1262_IDCA_1_Magnitude_750uA,
        ADC_ADS1262_IDCA_1_Magnitude_1000uA,
        ADC_ADS1262_IDCA_1_Magnitude_1500uA,
        ADC_ADS1262_IDCA_1_Magnitude_2000uA,
        ADC_ADS1262_IDCA_1_Magnitude_2500uA,
        ADC_ADS1262_IDCA_1_Magnitude_3000uA,
    } ADC_ADS1262_IDCA_1_Magnitude_t;

    typedef enum ADC_ADS1262_IDCA_2_Magnitude
    {
        ADC_ADS1262_IDCA_2_Magnitude_Disable = 0,
        ADC_ADS1262_IDCA_2_Magnitude_50uA,
        ADC_ADS1262_IDCA_2_Magnitude_100uA,
        ADC_ADS1262_IDCA_2_Magnitude_250uA,
        ADC_ADS1262_IDCA_2_Magnitude_500uA,
        ADC_ADS1262_IDCA_2_Magnitude_750uA,
        ADC_ADS1262_IDCA_2_Magnitude_1000uA,
        ADC_ADS1262_IDCA_2_Magnitude_1500uA,
        ADC_ADS1262_IDCA_2_Magnitude_2000uA,
        ADC_ADS1262_IDCA_2_Magnitude_2500uA,
        ADC_ADS1262_IDCA_2_Magnitude_3000uA,
    } ADC_ADS1262_IDCA_2_Magnitude_t;

    typedef enum ADC_ADS1262_ReferenceMultiplexer_Negative
    {
        ADC_ADS1262_ReferenceMultiplexer_Negative_InternalReference = 0,
        ADC_ADS1262_ReferenceMultiplexer_Negative_ExternalAIN1,
        ADC_ADS1262_ReferenceMultiplexer_Negative_ExternalAIN3,
        ADC_ADS1262_ReferenceMultiplexer_Negative_ExternalAIN5,
        ADC_ADS1262_ReferenceMultiplexer_Negative_InternalSupplyAnalog,
    } ADC_ADS1262_ReferenceMultiplexer_Negative_t;

    typedef enum ADC_ADS1262_ReferenceMultiplexer_Positive
    {
        ADC_ADS1262_ReferenceMultiplexer_Positive_InternalReference = 0,
        ADC_ADS1262_ReferenceMultiplexer_Positive_ExternalAIN0,
        ADC_ADS1262_ReferenceMultiplexer_Positive_ExternalAIN2,
        ADC_ADS1262_ReferenceMultiplexer_Positive_ExternalAIN4,
        ADC_ADS1262_ReferenceMultiplexer_Positive_InternalSupplyAnalog,
    } ADC_ADS1262_ReferenceMultiplexer_Positive_t;

    typedef enum ADC_ADS1262_TDACP_Magnitude
    {
        ADC_ADS1262_TDACP_Magnitude_2500mV = 0,
        ADC_ADS1262_TDACP_Magnitude_2508mV, // 2.5078125 V
        ADC_ADS1262_TDACP_Magnitude_2516mV, // 2.515625 V
        ADC_ADS1262_TDACP_Magnitude_2531mV, // 2.53125 V
        ADC_ADS1262_TDACP_Magnitude_2562mV, // 2.5625 V
        ADC_ADS1262_TDACP_Magnitude_2625mV,
        ADC_ADS1262_TDACP_Magnitude_2750mV,
        ADC_ADS1262_TDACP_Magnitude_3000mV,
        ADC_ADS1262_TDACP_Magnitude_3500mV,
        ADC_ADS1262_TDACP_Magnitude_4500mV,
        ADC_ADS1262_TDACP_Magnitude_2492mV = 0b10001, // 2.4921875 V
        ADC_ADS1262_TDACP_Magnitude_2484mV,           // 2.484375 V
        ADC_ADS1262_TDACP_Magnitude_2469mV,           // 2.46875 V
        ADC_ADS1262_TDACP_Magnitude_2437mV,           // 2.4375 V
        ADC_ADS1262_TDACP_Magnitude_2375mV,
        ADC_ADS1262_TDACP_Magnitude_2250mV,
        ADC_ADS1262_TDACP_Magnitude_2000mV,
        ADC_ADS1262_TDACP_Magnitude_1500mV,
        ADC_ADS1262_TDACP_Magnitude_500mV,
    } ADC_ADS1262_TDACP_Magnitude_t;

    typedef enum ADC_ADS1262_TDACP_Output
    {
        ADC_ADS1262_TDACP_Output_Float = 0,
        ADC_ADS1262_TDACP_Output_AIN6,
    } ADC_ADS1262_TDACP_Output_t;

    typedef enum ADC_ADS1262_TDACN_Magnitude
    {
        ADC_ADS1262_TDACN_Magnitude_2500mV = 0,
        ADC_ADS1262_TDACN_Magnitude_2508mV, // 2.5078125 V
        ADC_ADS1262_TDACN_Magnitude_2516mV, // 2.515625 V
        ADC_ADS1262_TDACN_Magnitude_2531mV, // 2.53125 V
        ADC_ADS1262_TDACN_Magnitude_2562mV, // 2.5625 V
        ADC_ADS1262_TDACN_Magnitude_2625mV,
        ADC_ADS1262_TDACN_Magnitude_2750mV,
        ADC_ADS1262_TDACN_Magnitude_3000mV,
        ADC_ADS1262_TDACN_Magnitude_3500mV,
        ADC_ADS1262_TDACN_Magnitude_4500mV,
        ADC_ADS1262_TDACN_Magnitude_2492mV = 0b10001, // 2.4921875 V
        ADC_ADS1262_TDACN_Magnitude_2484mV,           // 2.484375 V
        ADC_ADS1262_TDACN_Magnitude_2469mV,           // 2.46875 V
        ADC_ADS1262_TDACN_Magnitude_2437mV,           // 2.4375 V
        ADC_ADS1262_TDACN_Magnitude_2375mV,
        ADC_ADS1262_TDACN_Magnitude_2250mV,
        ADC_ADS1262_TDACN_Magnitude_2000mV,
        ADC_ADS1262_TDACN_Magnitude_1500mV,
        ADC_ADS1262_TDACN_Magnitude_500mV,
    } ADC_ADS1262_TDACN_Magnitude_t;

    typedef enum ADC_ADS1262_TDACN_Output
    {
        ADC_ADS1262_TDACN_Output_Float = 0,
        ADC_ADS1262_TDACN_Output_AIN7,
    } ADC_ADS1262_TDACN_Output_t;

    typedef enum ADC_ADS1262_GPIO_0_Connection
    {
        ADC_ADS1262_GPIO_0_Connection_Float = 0,
        ADC_ADS1262_GPIO_0_Connection_AIN3,
    } ADC_ADS1262_GPIO_0_Connection_t;

    typedef enum ADC_ADS1262_GPIO_1_Connection
    {
        ADC_ADS1262_GPIO_1_Connection_Float = 0,
        ADC_ADS1262_GPIO_1_Connection_AIN4,
    } ADC_ADS1262_GPIO_1_Connection_t;

    typedef enum ADC_ADS1262_GPIO_2_Connection
    {
        ADC_ADS1262_GPIO_2_Connection_Float = 0,
        ADC_ADS1262_GPIO_2_Connection_AIN5,
    } ADC_ADS1262_GPIO_2_Connection_t;

    typedef enum ADC_ADS1262_GPIO_3_Connection
    {
        ADC_ADS1262_GPIO_3_Connection_Float = 0,
        ADC_ADS1262_GPIO_3_Connection_AIN6,
    } ADC_ADS1262_GPIO_3_Connection_t;

    typedef enum ADC_ADS1262_GPIO_4_Connection
    {
        ADC_ADS1262_GPIO_4_Connection_Float = 0,
        ADC_ADS1262_GPIO_4_Connection_AIN7,
    } ADC_ADS1262_GPIO_4_Connection_t;

    typedef enum ADC_ADS1262_GPIO_5_Connection
    {
        ADC_ADS1262_GPIO_5_Connection_Float = 0,
        ADC_ADS1262_GPIO_5_Connection_AIN8,
    } ADC_ADS1262_GPIO_5_Connection_t;

    typedef enum ADC_ADS1262_GPIO_6_Connection
    {
        ADC_ADS1262_GPIO_6_Connection_Float = 0,
        ADC_ADS1262_GPIO_6_Connection_AIN9,
    } ADC_ADS1262_GPIO_6_Connection_t;

    typedef enum ADC_ADS1262_GPIO_7_Connection
    {
        ADC_ADS1262_GPIO_7_Connection_Float = 0,
        ADC_ADS1262_GPIO_7_Connection_AINCOM,
    } ADC_ADS1262_GPIO_7_Connection_t;

    typedef enum ADC_ADS1262_GPIO_0_Direction
    {
        ADC_ADS1262_GPIO_0_Direction_Output = 0,
        ADC_ADS1262_GPIO_0_Direction_Input,
    } ADC_ADS1262_GPIO_0_Direction_t;

    typedef enum ADC_ADS1262_GPIO_1_Direction
    {
        ADC_ADS1262_GPIO_1_Direction_Output = 0,
        ADC_ADS1262_GPIO_1_Direction_Input,
    } ADC_ADS1262_GPIO_1_Direction_t;

    typedef enum ADC_ADS1262_GPIO_2_Direction
    {
        ADC_ADS1262_GPIO_2_Direction_Output = 0,
        ADC_ADS1262_GPIO_2_Direction_Input,
    } ADC_ADS1262_GPIO_2_Direction_t;

    typedef enum ADC_ADS1262_GPIO_3_Direction
    {
        ADC_ADS1262_GPIO_3_Direction_Output = 0,
        ADC_ADS1262_GPIO_3_Direction_Input,
    } ADC_ADS1262_GPIO_3_Direction_t;

    typedef enum ADC_ADS1262_GPIO_4_Direction
    {
        ADC_ADS1262_GPIO_4_Direction_Output = 0,
        ADC_ADS1262_GPIO_4_Direction_Input,
    } ADC_ADS1262_GPIO_4_Direction_t;

    typedef enum ADC_ADS1262_GPIO_5_Direction
    {
        ADC_ADS1262_GPIO_5_Direction_Output = 0,
        ADC_ADS1262_GPIO_5_Direction_Input,
    } ADC_ADS1262_GPIO_5_Direction_t;

    typedef enum ADC_ADS1262_GPIO_6_Direction
    {
        ADC_ADS1262_GPIO_6_Direction_Output = 0,
        ADC_ADS1262_GPIO_6_Direction_Input,
    } ADC_ADS1262_GPIO_6_Direction_t;

    typedef enum ADC_ADS1262_GPIO_7_Direction
    {
        ADC_ADS1262_GPIO_7_Direction_Output = 0,
        ADC_ADS1262_GPIO_7_Direction_Input,
    } ADC_ADS1262_GPIO_7_Direction_t;

    typedef enum ADC_ADS1262_GPIO_0_Data
    {
        ADC_ADS1262_GPIO_0_Data_Low = 0,
        ADC_ADS1262_GPIO_0_Data_High,
    } ADC_ADS1262_GPIO_0_Data_t;

    typedef enum ADC_ADS1262_GPIO_1_Data
    {
        ADC_ADS1262_GPIO_1_Data_Low = 0,
        ADC_ADS1262_GPIO_1_Data_High,
    } ADC_ADS1262_GPIO_1_Data_t;

    typedef enum ADC_ADS1262_GPIO_2_Data
    {
        ADC_ADS1262_GPIO_2_Data_Low = 0,
        ADC_ADS1262_GPIO_2_Data_High,
    } ADC_ADS1262_GPIO_2_Data_t;

    typedef enum ADC_ADS1262_GPIO_3_Data
    {
        ADC_ADS1262_GPIO_3_Data_Low = 0,
        ADC_ADS1262_GPIO_3_Data_High,
    } ADC_ADS1262_GPIO_3_Data_t;

    typedef enum ADC_ADS1262_GPIO_4_Data
    {
        ADC_ADS1262_GPIO_4_Data_Low = 0,
        ADC_ADS1262_GPIO_4_Data_High,
    } ADC_ADS1262_GPIO_4_Data_t;

    typedef enum ADC_ADS1262_GPIO_5_Data
    {
        ADC_ADS1262_GPIO_5_Data_Low = 0,
        ADC_ADS1262_GPIO_5_Data_High,
    } ADC_ADS1262_GPIO_5_Data_t;

    typedef enum ADC_ADS1262_GPIO_6_Data
    {
        ADC_ADS1262_GPIO_6_Data_Low = 0,
        ADC_ADS1262_GPIO_6_Data_High,
    } ADC_ADS1262_GPIO_6_Data_t;

    typedef enum ADC_ADS1262_GPIO_7_Data
    {
        ADC_ADS1262_GPIO_7_Data_Low = 0,
        ADC_ADS1262_GPIO_7_Data_High,
    } ADC_ADS1262_GPIO_7_Data_t;

    typedef enum ADC_ADS1262_ADC_2_Mode_Gain
    {
        ADC_ADS1262_ADC_2_Mode_Gain_x1 = 0,
        ADC_ADS1262_ADC_2_Mode_Gain_x2,
        ADC_ADS1262_ADC_2_Mode_Gain_x4,
        ADC_ADS1262_ADC_2_Mode_Gain_x8,
        ADC_ADS1262_ADC_2_Mode_Gain_x16,
        ADC_ADS1262_ADC_2_Mode_Gain_x32,
        ADC_ADS1262_ADC_2_Mode_Gain_x64,
        ADC_ADS1262_ADC_2_Mode_Gain_x128,
    } ADC_ADS1262_ADC_2_Mode_Gain_t;

    typedef enum ADC_ADS1262_ADC_2_InputReference
    {
        ADC_ADS1262_ADC_2_InputReference_InternalReference = 0,
        ADC_ADS1262_ADC_2_InputReference_ExternalAIN0_AIN1,
        ADC_ADS1262_ADC_2_InputReference_ExternalAIN2_AIN3,
        ADC_ADS1262_ADC_2_InputReference_ExternalAIN4_AIN5,
        ADC_ADS1262_ADC_2_InputReference_InternalSupplyAnalog,
    } ADC_ADS1262_ADC_2_InputReference_t;

    typedef enum ADC_ADS1262_ADC_2_DataRate
    {
        ADC_ADS1262_ADC_2_DataRate_10_SPS = 0,
        ADC_ADS1262_ADC_2_DataRate_100_SPS,
        ADC_ADS1262_ADC_2_DataRate_400_SPS,
        ADC_ADS1262_ADC_2_DataRate_800_SPS,
    } ADC_ADS1262_ADC_2_DataRate_t;

    typedef enum ADC_ADS1262_ADC_2_InputMultiplexer_Negative
    {
        ADC_ADS1262_ADC_2_InputMultiplexer_Negative_AIN0 = 0,
        ADC_ADS1262_ADC_2_InputMultiplexer_Negative_AIN1,
        ADC_ADS1262_ADC_2_InputMultiplexer_Negative_AIN2,
        ADC_ADS1262_ADC_2_InputMultiplexer_Negative_AIN3,
        ADC_ADS1262_ADC_2_InputMultiplexer_Negative_AIN4,
        ADC_ADS1262_ADC_2_InputMultiplexer_Negative_AIN5,
        ADC_ADS1262_ADC_2_InputMultiplexer_Negative_AIN6,
        ADC_ADS1262_ADC_2_InputMultiplexer_Negative_AIN7,
        ADC_ADS1262_ADC_2_InputMultiplexer_Negative_AIN8,
        ADC_ADS1262_ADC_2_InputMultiplexer_Negative_AIN9,
        ADC_ADS1262_ADC_2_InputMultiplexer_Negative_AINCOM,
        ADC_ADS1262_ADC_2_InputMultiplexer_Negative_Temperature,
        ADC_ADS1262_ADC_2_InputMultiplexer_Negative_SupplyAnalog,
        ADC_ADS1262_ADC_2_InputMultiplexer_Negative_SupplyDigital,
        ADC_ADS1262_ADC_2_InputMultiplexer_Negative_TDAC,
        ADC_ADS1262_ADC_2_InputMultiplexer_Negative_Float,
    } ADC_ADS1262_ADC_2_InputMultiplexer_Negative_t;

    typedef enum ADC_ADS1262_ADC_2_InputMultiplexer_Positive
    {
        ADC_ADS1262_ADC_2_InputMultiplexer_Positive_AIN0 = 0,
        ADC_ADS1262_ADC_2_InputMultiplexer_Positive_AIN1,
        ADC_ADS1262_ADC_2_InputMultiplexer_Positive_AIN2,
        ADC_ADS1262_ADC_2_InputMultiplexer_Positive_AIN3,
        ADC_ADS1262_ADC_2_InputMultiplexer_Positive_AIN4,
        ADC_ADS1262_ADC_2_InputMultiplexer_Positive_AIN5,
        ADC_ADS1262_ADC_2_InputMultiplexer_Positive_AIN6,
        ADC_ADS1262_ADC_2_InputMultiplexer_Positive_AIN7,
        ADC_ADS1262_ADC_2_InputMultiplexer_Positive_AIN8,
        ADC_ADS1262_ADC_2_InputMultiplexer_Positive_AIN9,
        ADC_ADS1262_ADC_2_InputMultiplexer_Positive_AINCOM,
        ADC_ADS1262_ADC_2_InputMultiplexer_Positive_Temperature,
        ADC_ADS1262_ADC_2_InputMultiplexer_Positive_SupplyAnalog,
        ADC_ADS1262_ADC_2_InputMultiplexer_Positive_SupplyDigital,
        ADC_ADS1262_ADC_2_InputMultiplexer_Positive_TDAC,
        ADC_ADS1262_ADC_2_InputMultiplexer_Positive_Float,
    } ADC_ADS1262_ADC_2_InputMultiplexer_Positive_t;

    typedef int32_t ADC_ADS1262_ADC_2_CalibrationOffset_t;

    typedef int32_t ADC_ADS1262_ADC_2_CalibrationFullScale_t;

    // #############################################################################
    // #### Public Method(s) #######################################################
    // #############################################################################

    ADC_ADS1262_Status_t ADC_ADS1262_Initialize( ADC_ADS1262_Instance_t * Instance );
    ADC_ADS1262_Status_t ADC_ADS1262_Cycle( ADC_ADS1262_Instance_t * Instance );
    ADC_ADS1262_Status_t ADC_ADS1262_DeInitialize( ADC_ADS1262_Instance_t * Instance );

    ADC_ADS1262_Status_t ADC_ADS1262_GetIdentification( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_ID_Revision_t * ADC_ADS1262_ID_Revision, ADC_ADS1262_ID_Device_t * ADC_ADS1262_ID_Device );
    ADC_ADS1262_Status_t ADC_ADS1262_SetPower( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_Power_InternalReference_t ADC_ADS1262_Power_InternalReference, ADC_ADS1262_Power_LevelShiftVoltage_t ADC_ADS1262_Power_LevelShiftVoltage, ADC_ADS1262_Power_ResetIndicator_t * ADC_ADS1262_Power_ResetIndicator );
    ADC_ADS1262_Status_t ADC_ADS1262_SetInterface( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_Interface_CRC_t ADC_ADS1262_Interface_CRC, ADC_ADS1262_Interface_Status_t ADC_ADS1262_Interface_Status, ADC_ADS1262_Interface_Timeout_t ADC_ADS1262_Interface_Timeout );
    ADC_ADS1262_Status_t ADC_ADS1262_SetMode0( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_Mode_ConversionDelay_t ADC_ADS1262_Mode_ConversionDelay, ADC_ADS1262_Mode_Chop_t ADC_ADS1262_Mode_Chop, ADC_ADS1262_Mode_Conversion_t ADC_ADS1262_Mode_Conversion, ADC_ADS1262_Mode_ReferencePolarityMUX_t ADC_ADS1262_Mode_ReferencePolarityMUX );
    ADC_ADS1262_Status_t ADC_ADS1262_SetMode1( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_Mode_BiasMagnitude_t ADC_ADS1262_Mode_BiasMagnitude, ADC_ADS1262_Mode_BiasPolarity_t ADC_ADS1262_Mode_BiasPolarity, ADC_ADS1262_Mode_BiasConnection_t ADC_ADS1262_Mode_BiasConnection, ADC_ADS1262_Mode_Filter_t ADC_ADS1262_Mode_Filter );
    ADC_ADS1262_Status_t ADC_ADS1262_SetMode2( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_Mode_DataRate_t ADC_ADS1262_Mode_DataRate, ADC_ADS1262_Mode_Gain_t ADC_ADS1262_Mode_Gain, ADC_ADS1262_Mode_ProgrammableGainAmplifierBypass_t ADC_ADS1262_Mode_ProgrammableGainAmplifierBypass );
    ADC_ADS1262_Status_t ADC_ADS1262_SetInputMUX( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_InputMultiplexer_Negative_t ADC_ADS1262_InputMultiplexer_Negative, ADC_ADS1262_InputMultiplexer_Positive_t ADC_ADS1262_InputMultiplexer_Positive );
    ADC_ADS1262_Status_t ADC_ADS1262_SetCalibrationOffset( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_CalibrationOffset_t ADC_ADS1262_CalibrationOffset );
    ADC_ADS1262_Status_t ADC_ADS1262_SetCalibrationFullScale( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_CalibrationFullScale_t ADC_ADS1262_CalibrationFullScale );
    ADC_ADS1262_Status_t ADC_ADS1262_SetIDAC_MUX( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_IDAC_1_Multiplexer_t ADC_ADS1262_IDAC_1_Multiplexer, ADC_ADS1262_IDAC_2_Multiplexer_t ADC_ADS1262_IDAC_2_Multiplexer );
    ADC_ADS1262_Status_t ADC_ADS1262_SetIDAC_Magnitude( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_IDCA_1_Magnitude_t ADC_ADS1262_IDCA_1_Magnitude, ADC_ADS1262_IDCA_2_Magnitude_t ADC_ADS1262_IDCA_2_Magnitude );
    ADC_ADS1262_Status_t ADC_ADS1262_SetREF_MUX( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_ReferenceMultiplexer_Negative_t ADC_ADS1262_ReferenceMultiplexer_Negative, ADC_ADS1262_ReferenceMultiplexer_Positive_t ADC_ADS1262_ReferenceMultiplexer_Positive );
    ADC_ADS1262_Status_t ADC_ADS1262_SetTDAC_Positive( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_TDACP_Magnitude_t ADC_ADS1262_TDACP_Magnitude, ADC_ADS1262_TDACP_Output_t ADC_ADS1262_TDACP_Output );
    ADC_ADS1262_Status_t ADC_ADS1262_SetTDAC_Negative( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_TDACN_Magnitude_t ADC_ADS1262_TDACN_Magnitude, ADC_ADS1262_TDACN_Output_t ADC_ADS1262_TDACN_Output );
    ADC_ADS1262_Status_t ADC_ADS1262_SetGPIOConnection( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_GPIO_0_Connection_t ADC_ADS1262_GPIO_0_Connection, ADC_ADS1262_GPIO_1_Connection_t ADC_ADS1262_GPIO_1_Connection, ADC_ADS1262_GPIO_2_Connection_t ADC_ADS1262_GPIO_2_Connection, ADC_ADS1262_GPIO_3_Connection_t ADC_ADS1262_GPIO_3_Connection, ADC_ADS1262_GPIO_4_Connection_t ADC_ADS1262_GPIO_4_Connection, ADC_ADS1262_GPIO_5_Connection_t ADC_ADS1262_GPIO_5_Connection, ADC_ADS1262_GPIO_6_Connection_t ADC_ADS1262_GPIO_6_Connection, ADC_ADS1262_GPIO_7_Connection_t ADC_ADS1262_GPIO_7_Connection );
    ADC_ADS1262_Status_t ADC_ADS1262_SetGPIODirection( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_GPIO_0_Direction_t ADC_ADS1262_GPIO_0_Direction, ADC_ADS1262_GPIO_1_Direction_t ADC_ADS1262_GPIO_1_Direction, ADC_ADS1262_GPIO_2_Direction_t ADC_ADS1262_GPIO_2_Direction, ADC_ADS1262_GPIO_3_Direction_t ADC_ADS1262_GPIO_3_Direction, ADC_ADS1262_GPIO_4_Direction_t ADC_ADS1262_GPIO_4_Direction, ADC_ADS1262_GPIO_5_Direction_t ADC_ADS1262_GPIO_5_Direction, ADC_ADS1262_GPIO_6_Direction_t ADC_ADS1262_GPIO_6_Direction, ADC_ADS1262_GPIO_7_Direction_t ADC_ADS1262_GPIO_7_Direction );
    ADC_ADS1262_Status_t ADC_ADS1262_SetGPIOData( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_GPIO_0_Data_t ADC_ADS1262_GPIO_0_Data, ADC_ADS1262_GPIO_1_Data_t ADC_ADS1262_GPIO_1_Data, ADC_ADS1262_GPIO_2_Data_t ADC_ADS1262_GPIO_2_Data, ADC_ADS1262_GPIO_3_Data_t ADC_ADS1262_GPIO_3_Data, ADC_ADS1262_GPIO_4_Data_t ADC_ADS1262_GPIO_4_Data, ADC_ADS1262_GPIO_5_Data_t ADC_ADS1262_GPIO_5_Data, ADC_ADS1262_GPIO_6_Data_t ADC_ADS1262_GPIO_6_Data, ADC_ADS1262_GPIO_7_Data_t ADC_ADS1262_GPIO_7_Data );

    ADC_ADS1262_Status_t ADC_ADS1262_ADC_2_SetConfiguration( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_ADC_2_Mode_Gain_t ADC_ADS1262_ADC_2_Mode_Gain, ADC_ADS1262_ADC_2_InputReference_t ADC_ADS1262_ADC_2_InputReference, ADC_ADS1262_ADC_2_DataRate_t ADC_ADS1262_ADC_2_DataRate );
    ADC_ADS1262_Status_t ADC_ADS1262_ADC_2_SetInputMUX( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_ADC_2_InputMultiplexer_Negative_t ADC_ADS1262_ADC_2_InputMultiplexer_Negative, ADC_ADS1262_ADC_2_InputMultiplexer_Positive_t ADC_ADS1262_ADC_2_InputMultiplexer_Positive );
    ADC_ADS1262_Status_t ADC_ADS1262_ADC_2_SetCalibrationOffset( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_ADC_2_CalibrationOffset_t ADC_ADS1262_ADC_2_CalibrationOffset );
    ADC_ADS1262_Status_t ADC_ADS1262_ADC_2_SetCalibrationFullScale( ADC_ADS1262_Instance_t * Instance, ADC_ADS1262_ADC_2_CalibrationFullScale_t ADC_ADS1262_ADC_2_CalibrationFullScale );

    // #############################################################################
    // #### Public Variable(s) #####################################################
    // #############################################################################

    /**
     *  @brief Version
     */
    extern const char ADC_ADS1262_VERSION[];

    // #############################################################################
    // #### File Guard #############################################################
    // #############################################################################

    #ifdef __cplusplus
} /* extern "C" */
    #endif /* __cplusplus */

#endif /* ADC_ADS1262_H_ */

/**
 *  @}
 *
 *  @}
 */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
