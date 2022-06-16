/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is part of the mikroSDK package
**
** Commercial License Usage
**
** Licensees holding valid commercial NECTO compilers AI licenses may use this
** file in accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The MikroElektronika Company.
** For licensing terms and conditions see
** https://www.mikroe.com/legal/software-license-agreement.
** For further information use the contact form at
** https://www.mikroe.com/contact.
**
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used for
** non-commercial projects under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file  drv_analog_in.h
 * @brief API for Analog input driver.
 */

#ifndef _DRV_ANALOG_IN_H_
#define _DRV_ANALOG_IN_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_name.h"
#include "hal_adc.h"

/**
 * @details Return values.
 */
typedef enum
{
    ADC_SUCCESS = 0,              /*!< Success. */
    ADC_ERROR = (-1)              /*!< Error. */
} analog_in_err_t;

/**
 * @details Analog input driver reference voltage enum.
 */
typedef enum
{
    ANALOG_IN_VREF_EXTERNAL = 0,  /*!< External reference. */
    ANALOG_IN_VREF_INTERNAL       /*!< Internal reference. */
} analog_in_vref_t;

/**
 * @details Analog input driver resolution enum.
 */
typedef enum
{
    ANALOG_IN_RESOLUTION_NOT_SET = 0,  /*!< Resolution not set. */
    ANALOG_IN_RESOLUTION_6_BIT,        /*!< 6 bit resolution. */
    ANALOG_IN_RESOLUTION_8_BIT,        /*!< 8 bit resolution. */
    ANALOG_IN_RESOLUTION_10_BIT,       /*!< 10 bit resolution. */
    ANALOG_IN_RESOLUTION_12_BIT,       /*!< 12 bit resolution. */
    ANALOG_IN_RESOLUTION_14_BIT,       /*!< 14 bit resolution. */
    ANALOG_IN_RESOLUTION_16_BIT,       /*!< 16 bit resolution. */

    /*!< Default resolution. */
    ANALOG_IN_RESOLUTION_DEFAULT = ANALOG_IN_RESOLUTION_CMAKE
} analog_in_resolution_t;

/**
 * @brief Analog input driver configuration structure.
 * @details The context structure for storing driver configuration.
 * User shall define the values stored within.
 * @warning The following example describes how to fill a #analog_in_config_t structure.
 * Take into consideration that different hardware might not have the same possibilities.
 * Make sure to accommodate resolution and vref based on your hardware specifics.
 *
 * @b Example
 * @code
 *   // Analog input driver configuration structure
 *   analog_in_config_t analog_in_cfg;
 *
 *   analog_in_cfg.input_pin  = MIKROBUS_1_AN;
 *   analog_in_cfg.resolution = ANALOG_IN_RESOLUTION_12_BIT;
 *   analog_in_cfg.vref_input = ANALOG_IN_VREF_EXTERNAL;
 * @endcode
 */
typedef struct
{
    pin_name_t input_pin;               /*!< Analog input pin. */
    analog_in_resolution_t resolution;  /*!< Resolution. */
    analog_in_vref_t vref_input;        /*!< Voltage reference input. */
    float vref_value;                   /*!< Voltage reference value. */
} analog_in_config_t;

/**
 * @brief Analog input driver context structure, consisted of the following fields :
 * @details Analog input driver context structure.
 * The contents of the context structure are used by the driver and must not be altered.
 * Reading or writing data directly from a control structure by user should be avoided.
 *
 * @b Example
 * @code
 *   // Analog input driver context structure.
 *   static analog_in_t analog_in;
 * @endcode
 */
typedef struct
{
    handle_t handle;            /*!< Analog in handle. */
    analog_in_config_t config;  /*!< Analog in configuration structure. */
} analog_in_t;

/*!
 * @addtogroup pergroup Microcontroller Peripherals
 * @brief This section includes the mikroSDK API Reference for the Microcontroller Peripherals.
 * @details Microcontroller Peripherals can be separated into two hierarchical layers - Driver and Hardware Abstraction Layer :
 *
 * <b>Device drivers</b> are the software libraries that initialize
 * the hardware and manage access to the hardware by higher layers
 * of software. Device drivers are the architecture independent
 * liaison between the hardware and the middleware,
 * application layers and plugins.
 *
 * <b>Hardware Abstraction Layer</b> is a layer
 * of code that allows driver interaction with a hardware device at a
 * general or abstract level rather than at a detailed hardware level.
 * @b HAL can be called from either the @b DRV layer or directly from user code.
 * In either case, the calling program can interact with the device in a
 * more general way than it would otherwise.
 *
 * @note All @b mikroSDK.HAL and @b mikroSDK.Driver layers prototypes are architecture independent
 * with the goal of having one unique code base supporting cross-platform
 * devices.
 * @{
 */

/*!
 * @addtogroup drvgroup Driver Layer
 * @brief This section includes the mikroSDK API Reference for the Driver.
 * @details
 * Device drivers are the software libraries that initialize
 * the hardware and manage access to the hardware by higher layers
 * of software. Device drivers are the architecture independent
 * liaison between the hardware and the middleware,
 * application layers and plugins.
 *
 * @note All @b mikroSDK.Driver layer prototypes are architecture independent
 * with the goal of having one unique code base supporting cross-platform
 * devices.
 * @{
 */

/*!
 * @addtogroup drvadcgroup ADC Driver
 * @brief ADC Driver API Reference.
 * @details The ADC driver provides standard ADC functionality including setting the analog pin and reading the ADC value from it. It also allows configuration of ADC resolution, voltage reference source and value.
 * @{
 */

/**
 * @brief Configure ADC configuration structure.
 * @details Configures ADC configuration structure to default initialization values.
 * Take into consideration that this is just
 * structure variable initial values setting.
 * Values need to be redefined by user.
 * @param[in,out] config ADC driver configuration settings.
 * See #analog_in_config_t structure definition for detailed explanation.
 *
 * @b Default @b values:
 * Function            | Default value                         |
 * --------------------|---------------------------------------|
 * Input pin           | 0xFFFFFFFF (invalid pin)              |
 * Resolution          | 12 bit                                |
 * Vref input          | External reference voltage            |
 * Vref value          | -1 (invalid reference voltage value)  |
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // Analog input driver configuration structure.
 *   analog_in_config_t analog_in_cfg;
 *
 *   // Fill structure with default values.
 *   analog_in_configure_default( &analog_in_cfg );
 * @endcode
 */
void analog_in_configure_default( analog_in_config_t *config );

/**
 * @brief Open the ADC driver object on selected pin.
 * @details Opens the ADC driver object on selected pins.
 * Allocates memory and pin for specified object.
 * @param[in,out] obj ADC driver object.
 * See #analog_in_t structure definition for detailed explanation.
 * @param[in] config ADC driver configuration settings.
 * See #analog_in_config_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #analog_in_err_t, which is size dependant on the architecture.
 * @pre Make sure that \p config structure has been adequately
 * populated beforehand.
 * See @ref analog_in_configure_default definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // Analog input driver context structure.
 *   analog_in_t analog_in;
 *
 *   // Analog input driver configuration structure.
 *   analog_in_config_t analog_in_cfg;
 *
 *   // Fill structure with default values.
 *   analog_in_configure_default( &analog_in_cfg );
 *
 *   // Fill analog input pin.
 *   analog_in_cfg.pin = MIKROBUS_1_AN;
 *
 *   // Open the driver on the selected pin.
 *   analog_in_open( &analog_in, &analog_in_cfg );
 * @endcode
 */
err_t analog_in_open( analog_in_t *obj, analog_in_config_t *config );

/**
 * @brief Set ADC driver sample resolution.
 * @details Sets ADC driver resolution to passed value if possible.
 * If not possible, returns error.
 * Make sure to check for return value.
 * Take into consideration that the driver
 * will be re-initialized on the hardware level.
 * @param[in] obj ADC driver context object.
 * @param[in] resolution ADC driver sample resolution value. See #analog_in_resolution_t for valid values.
 * @return The function can return one of the values defined by
 * #analog_in_err_t, which is size dependant on the architecture.
 * @pre Before calling this function, the user is expected to call #analog_in_open
 * @post This function sets ADC resolution.
 * @note Driver will be re-initialized on the hardware level
 *
 * @b Example
 * @code
 *   // Analog input driver context structure.
 *   analog_in_t analog_in;
 *
 *   // Analog input driver configuration structure.
 *   analog_in_config_t analog_in_cfg;
 *
 *   // Fill sample resolution.
 *   analog_in_cfg.resolution = ANALOG_IN_RESOLUTION_10_BIT;
 *
 *   // Set sample resolution.
 *   analog_in_set_resolution( &analog_in, analog_in_cfg.resolution );
 * @endcode
 */
err_t analog_in_set_resolution( analog_in_t *obj, analog_in_resolution_t resolution );

/**
 * @brief Set ADC driver voltage reference source.
 * @details Sets ADC driver voltage reference source to passed value if possible.
 * If not possible, returns error.
 * Make sure to check for return value.
 * Take into consideration that the driver
 * will be re-initialized on the hardware level.
 * @param[in] obj ADC driver context object.
 * @param[in] vref ADC driver voltage reference source value. See #analog_in_vref_t for valid values.
 * @return The function can return one of the values defined by
 * #analog_in_err_t, which is size dependant on the architecture.
 * @pre Before calling this function, the user is expected to call #analog_in_open
 * @post This function sets ADC voltage reference source.
 * @note Driver will be re-initialized on the hardware level
 *
 * @b Example
 * @code
 *   // Analog input driver context structure.
 *   analog_in_t analog_in;
 *
 *   // Analog input driver configuration structure.
 *   analog_in_config_t analog_in_cfg;
 *
 *   // Fill voltage reference source.
 *   analog_in_cfg.vref_input = ANALOG_IN_VREF_EXTERNAL;
 *
 *   // Set voltage reference source.
 *   analog_in_set_vref_input( &analog_in, analog_in_cfg.vref );
 * @endcode
 */
err_t analog_in_set_vref_input( analog_in_t *obj, analog_in_vref_t vref );

/**
 * @brief Set ADC driver voltage reference value.
 * @details Sets ADC driver voltage reference value to passed value if possible.
 * If not possible, returns error.
 * Make sure to check for return value.
 * Take into consideration that the driver
 * will be re-initialized on the hardware level.
 * @param[in] obj ADC driver context object.
 * @param[in] vref_value ADC driver voltage reference value.
 * @return The function can return one of the values defined by
 * #analog_in_err_t, which is size dependant on the architecture.
 * @pre Before calling this function, the user is expected to call #analog_in_open
 * @post This function sets ADC voltage reference
 * value neccessary for voltage calculation.
 * @note Setting wrong voltage reference value will result
 * with bad voltage calculation.
 *
 * @b Example
 * @code
 *   // Analog input driver context structure.
 *   analog_in_t analog_in;
 *
 *   // Analog input driver configuration structure.
 *   analog_in_config_t analog_in_cfg;
 *
 *   // Fill voltage reference value.
 *   analog_in_cfg.vref_value = 2.048;
 *
 *   // Set voltage reference value.
 *   analog_in_set_vref_value( &analog_in, analog_in_cfg.vref_value );
 * @endcode
 */
err_t analog_in_set_vref_value( analog_in_t *obj, float vref_value );

/**
 * @brief Read analog value from pin.
 * @details Function perform a read on the configured
 * analog pin.
 * @param[in] obj Analog input driver object.
 * See #analog_in_t structure definition for detailed explanation.
 * @param[out] readDatabuf Data buffer to place read data in.
 * @return The function can return one of the values defined by
 * #analog_in_err_t, which is size dependant on the architecture.
 * @note The ADC driver needs to be initialized so that
 * the read can be done.
 *
 * @b Example
 * @code
 *   // Analog input driver context structure.
 *   analog_in_t analog_in;
 *
 *   // ADC data buffer.
 *   float *readDatabuf;
 *
 *   // Read analog value and store it to buffer.
 *   analog_in_read( &analog_in, &readDatabuf );
 * @endcode
 */
err_t analog_in_read( analog_in_t *obj, uint16_t *readDatabuf );

/**
 * @brief Read analog voltage value from pin.
 * @details Function perform a read on the configured
 * analog pin and converts it into voltage.
 * @param[in] obj Analog input driver object.
 * See #analog_in_t structure definition for detailed explanation.
 * @param[out] readDatabuf Data buffer to place read data in.
 * @return The function can return one of the values defined by
 * #analog_in_err_t, which is size dependant on the architecture.
 * @note The ADC driver needs to be initialized so that
 * the read can be done. User should set right reference voltage value
 * in order to get correct voltage value from this function.
 *
 * @b Example
 * @code
 *   // Analog input driver context structure.
 *   analog_in_t analog_in;
 *
 *   // ADC data buffer.
 *   float *readDatabuf;
 *
 *   // Read analog voltage value and store to buffer.
 *   analog_in_read_voltage( &analog_in, &readDatabuf );
 * @endcode
 */
err_t analog_in_read_voltage( analog_in_t *obj, float *readDatabuf );

/**
 * @brief  Close ADC driver context object.
 * @details De-allocates hardware resources for specific driver object.
 * @param[in] obj ADC driver object.
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // Analog input driver context structure.
 *   analog_in_t analog_in;
 *
 *   // Close ADC driver context object.
 *   analog_in_close( &analog_in );
 * @endcode
 */
void analog_in_close( analog_in_t *obj );

/*! @} */ // drvadcgroup
/*! @} */ // drvgroup
/*! @} */ // pergroup

#ifdef __cplusplus
}
#endif

#endif // _DRV_ANALOG_IN_H_
// ------------------------------------------------------------------------- END
