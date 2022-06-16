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
 * @file  hal_adc.h
 * @brief This file contains all the functions prototypes for the ADC library.
 */

#ifndef _HAL_ADC_H_
#define _HAL_ADC_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_target.h"

/**
 * @brief ADC HAL level handle.
 * @details The context for storing  ADC level object handlers.
 * Contains specific hardware module handle and
 * module init state.
 * @warning User is not to change these values or
 * unexpected behaviour may occur.
 */
typedef struct
{
    handle_t *hal_adc_handle; /*!< ADC HAL level handle */
    handle_t *drv_adc_handle; /*!< ADC DRV level handle */
    bool init_state; /*!< ADC HAL object init state */
} hal_adc_handle_register_t;

/**
 * @details Return values.
 */
typedef enum
{
    HAL_ADC_SUCCESS = 0,                      /*!< Success. */
    HAL_ADC_WRONG_PIN,                        /*!< Wrong pin selected. */
    HAL_ADC_MODULE_ERROR,                     /*!< Object wasn't closed. */

    HAL_ADC_UNSUPPORTED_RESOLUTION = 1100,    /*!< Wrong resolution error. */
    HAL_ADC_UNSUPPORTED_VREF,                 /*!< Wrong voltage referebnce source error. */
    HAL_ADC_WRONG_CHANNEL,                    /*!< Wrong channel error. */
    HAL_ADC_ERROR = (-1)                      /*!< Error. */
} hal_adc_err_t;

/**
 * @details  Predefined enum values for ADC resolution.
 */
typedef enum
{
    HAL_ADC_RESOLUTION_NOT_SET = 0,  /*!< Resolution not set. */
    HAL_ADC_RESOLUTION_6_BIT,        /*!< 6  bit resolution. */
    HAL_ADC_RESOLUTION_8_BIT,        /*!< 8  bit resolution. */
    HAL_ADC_RESOLUTION_10_BIT,       /*!< 10 bit resolution. */
    HAL_ADC_RESOLUTION_12_BIT,       /*!< 12 bit resolution. */
    HAL_ADC_RESOLUTION_14_BIT,       /*!< 14 bit resolution. */
    HAL_ADC_RESOLUTION_16_BIT,       /*!< 16 bit resolution. */

    /*!< Default resolution. */
    HAL_ADC_RESOLUTION_DEFAULT = HAL_ADC_RESOLUTION_CMAKE
} hal_adc_resolution_t;

/**
 * @details  Predefined enum values for ADC voltage reference source.
 */
typedef enum
{
    HAL_ADC_VREF_EXTERNAL = 0,     /*!< External voltage reference source. */
    HAL_ADC_VREF_INTERNAL,         /*!< Internal voltage reference source. */
    HAL_ADC_VREF_DEFAULT = HAL_ADC_VREF_EXTERNAL /*!< Default (external voltage reference source) */
} hal_adc_vref_t;

/**
 * @brief ADC HAL initialization configuration structure, consisted of the following fields :
 * @details User needs to specifiy values herein.
 * @note Take into consideration that any value can be changed explicitly by the user.
 *
 * @b Example
 * @code
 *   // ADC HAL configuration structure.
 *   static hal_adc_config_t hal_adc_cfg;
 *
 *   // Fill structure with default values.
 *   hal_adc_configure_default( &hal_adc_cfg );
 *
 *   // Specify desired ADC pin.
 *   hal_adc_cfg.pin = MIKROBUS_1_AN;
 *
 *   // Set 12 bit ADC resolution.
 *   hal_adc_cfg.resolution = ANALOG_IN_RESOLUTION_12_BIT;
 *
 *   // Set external voltage reference source
 *   hal_adc_cfg.vref_input = ANALOG_IN_VREF_EXTERNAL;
 * @endcode
 */
typedef struct
{
    hal_pin_name_t              pin;        /*!< ADC HAL pin name. */
    hal_adc_resolution_t        resolution; /*!< ADC HAL resolution. See #hal_adc_resolution_t for valid resolution values. */
    hal_adc_vref_t              vref_input; /*!< ADC HAL voltage reference voltage source. See #hal_adc_vref_t for valid voltage reference source values. */
    float                       vref_value; /*!< ADC HAL voltage reference voltage value. */
} hal_adc_config_t;

/**
 * @brief ADC HAL context structure, consisted of the following fields :
 * @details ADC HAL context structure, used by every other function later on.
 *
 * @b Example
 * @code
 *   // ADC HAL context structure.
 *   static hal_adc_t hal_adc;
 * @endcode
 */
typedef struct
{
    handle_t handle; /*!< ADC HAL level handle */
    hal_adc_config_t config; /*!< ADC HAL object init state */
} hal_adc_t;

/*!
 * @addtogroup pergroup Microcontroller Peripherals
 * @{
 */

/*!
 * @addtogroup halgroup Hardware Abstraction Layer
 * @brief This section includes the mikroSDK API Reference for the Hardware Abstraction Layer.
 * @details Hardware Abstraction Layer ( @b HAL ) is a layer
 * of code that allows driver interaction with a hardware device at a
 * general or abstract level rather than at a detailed hardware level.
 * @b HAL can be called from either the @b DRV layer or directly from user code.
 * In either case, the calling program can interact with the device in a
 * more general way than it would otherwise.
 *
 * @note All @b mikroSDK.HAL layer prototypes are architecture independent
 * with the goal of having one unique code base supporting cross-platform
 * devices.
 * @{
 */

/*!
 * @addtogroup haladcgroup ADC HAL
 * @brief ADC Hardware Abstraction Layer API Reference.
 * @details API for configuring and manipulating ADC HAL module.
 * @{
 */

/**
 * @brief Configure ADC HAL configuration structure..
 * @details Configures ADC configuration structure to default initialization values.
 * Take into consideration that this is just
 * structure variable initial values setting.
 * Values need to be redefined by user.
 * @param[in,out] config ADC HAL layer configuration settings.
 * See #hal_adc_config_t structure definition for detailed explanation.
 *
 * @b Default @b values:
 * Function            | Default value                         |
 * --------------------|---------------------------------------|
 * Input pin           | @p HAL_PIN_NC (invalid pin)           |
 * Resolution          | 12 bit                                |
 * Vref input          | External voltage reference source     |
 * Vref value          | -1 (invalid reference voltage value)  |
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // ADC HAL configuration structure.
 *   static hal_adc_config_t hal_adc_cfg;
 *
 *   // Fill structure with default values.
 *   hal_adc_configure_default( &hal_adc_cfg );
 * @endcode
 */
void hal_adc_configure_default( hal_adc_config_t *config );

/**
 * @brief Open the ADC HAL layer object on selected pin.
 * @details Function allocates memory needed for ADC HAL
 * and pin for specified object.
 * @param[in,out] handle ADC handle.
 * @param[in] hal_obj_open_state ADC state, is it open or not.
 * @return The function can return one of the values defined by
 * #hal_adc_err_t, which is size dependant on the architecture.
 *
 * @b Example
 * @code
 *   // ADC HAL context structure.
 *   static hal_adc_t hal_adc;
 *
 *   // ADC HAL configuration structure.
 *   static hal_adc_config_t hal_adc_cfg;
 *
 *   // Fill structure with default values.
 *   adc_configure_default( &hal_adc_cfg );
 *
 *   // Specify desired ADC pin.
 *   hal_adc_cfg.pin. = MIKROBUS_1_AN;
 *
 *   // Allocate resources for ADC HAL.
 *   hal_adc_open( &hal_adc->handle, true );
 * @endcode
 */
err_t hal_adc_open( handle_t *handle, bool hal_obj_open_state );

/**
 * @brief Set ADC HAL sample resolution.
 * @details Initializes ADC HAL on the hardware level and sets
 * sample resolution to specified \p config->resolution value.
 * @param[in] handle ADC handle.
 * @param[in] config ADC HAL configuration structure.
 * See #hal_adc_config_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #hal_adc_err_t, which is size dependant on the architecture.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #hal_adc_open definition for detailed explanation.
 * @warning If desired resolution can not be achieved,
 * error will be returned. Make sure to poll the return value in your code.
 *
 * @b Example
 * @code
 *   // Set resolution.
 *   hal_adc_set_resolution( &hal_adc->handle, &hal_adc->config );
 * @endcode
 */
err_t hal_adc_set_resolution( handle_t *handle, hal_adc_config_t *config );

/**
 * @brief Set ADC HAL reference voltage source to desired value.
 * @details Initializes ADC HAL on the hardware level and sets
 * sample reference voltage source to specified \p config->vref_input value.
 * @param[in] handle ADC handle.
 * @param[in] config ADC HAL configuration structure.
 * See #hal_adc_config_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #hal_adc_err_t, which is size dependant on the architecture.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #hal_adc_open definition for detailed explanation.
 * @warning If desired reference voltage source can not be achieved,
 * error will be returned. Make sure to poll the return value in your code.
 *
 * @b Example
 * @code
 *   // Set voltage reference source.
 *   hal_adc_set_vref_input( &hal_adc->handle, &hal_adc->config );
 * @endcode
 */
err_t hal_adc_set_vref_input( handle_t *handle, hal_adc_config_t *config );

/**
 * @brief Set ADC HAL reference voltage value to desired value.
 * @details Sets sample reference voltage value to
 * specified \p config->vref_value value used later for calculating voltage.
 * @param[in] handle ADC handle.
 * @param[in] config ADC HAL configuration structure.
 * See #hal_adc_config_t structure definition for detailed explanation.
 * @return Nothing.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #hal_adc_open definition for detailed explanation.
 * @warning If desired reference voltage value is not set,
 * calculated voltage value on AN pin will be wrong.
 *
 * @b Example
 * @code
 *   // Set voltage reference value.
 *   hal_adc_set_vref_value( &hal_adc->handle, &hal_adc->config );
 * @endcode
 */
void hal_adc_set_vref_value( handle_t *handle, hal_adc_config_t *config );

/**
 * @brief Read analog value on pin.
 * @param[in] handle ADC handle.
 * @param[out] readDatabuf Data buffer to place read data in.
 * @return The function can return one of the values defined by
 * #hal_adc_err_t, which is size dependant on the architecture.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #hal_adc_open definition for detailed explanation.
 *
 * @b Example
 * @code
 *   hal_adc_read( &hal_adc->handle, readDatabuf );
 * @endcode
 */
err_t hal_adc_read( handle_t *handle, uint16_t *readDatabuf );

/**
 * @brief Read analog voltage value on pin.
 * @param[in] handle ADC handle.
 * @param[out] readDatabuf Data buffer to place read data in.
 * @return The function can return one of the values defined by
 * #hal_adc_err_t, which is size dependant on the architecture.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #hal_adc_open definition for detailed explanation.
 *
 * @b Example
 * @code
 *   hal_adc_read_voltage( &hal_adc->handle, readDatabuf );
 * @endcode
 */
err_t hal_adc_read_voltage( handle_t *handle, float *readDatabuf );

/**
 * @brief Close ADC HAL layer object.
 * @details Closes ADC HAL layer object,
 * clears all buffers used by object and clears config.
 * @param[in,out] handle ADC handle.
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // Close the ADC HAL object handler.
 *   hal_adc_close( &hal_adc->handle );
 * @endcode
 */
err_t hal_adc_close( handle_t *handle );

/*! @} */ // haladcgroup
/*! @} */ // halgroup
/*! @} */ // pergroup

#ifdef __cplusplus
}
#endif

#endif // _HAL_ADC_H_
// ------------------------------------------------------------------------- END
