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
 * @file  hal_pwm.h
 * @brief This file contains all the functions prototypes for the PWM library.
 */

#ifndef _HAL_PWM_H_
#define _HAL_PWM_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_target.h"
#include "hal_ll_tim.h"

/**
 * @def Macros used in PWM HAL.
 */
#define HAL_PWM_MIN_DUTY_RATIO 0 /*!< Minimum duty ratio value. */
#define HAL_PWM_MAX_DUTY_RATIO 1 /*!< Maximum duty ratio value. */

/**
 * @brief PWM HAL level handle.
 * @details The context for storing  HAL level object handlers.
 * Contains specific hardware module handle and
 * said module init state.
 * @warning User is not to change these values or
 * unexpected behaviour may occur.
 */
typedef struct
{
    handle_t *hal_pwm_handle; /*!< PWM HAL level handle */
    handle_t *drv_pwm_handle; /*!< PWM DRV level handle */
    bool init_state;          /*!< PWM HAL object init state */
} hal_pwm_handle_register_t;

/**
 * @brief PWM HAL config structure, consisted of the following fields:
 * @details The context structure for storing HAL configuration.
 * User shall define the values stored within.
 * @warning The following example describes how to fill a #hal_pwm_config_t structure.
 * Take into consideration that different hardware might not have the same pin.
 * Make sure to accommodate pin name based on your hardware specifics.
 *
 * @b Example
 * @code
 *   hal_pwm_config_t hal_pwm_cfg;
 *
 *   hal_pwm_cfg.pin      = MIKROBUS_1_PWM;
 *   hal_pwm_cfg.freq_hz  = 5000;
 * @endcode
 */
typedef struct
{
    hal_pin_name_t pin; /*!< PWM pin name. */
    uint32_t freq_hz;   /*!< PWM Frequency in Hz. */
} hal_pwm_config_t;

/**
 * @brief The PWM HAL context structure.
 * @details The context structure for storing HAL internal state.
 * The contents of the context structure are used by the module and must not be altered.
 * Reading or writing data directly from a control structure by user should be avoided.
 */
typedef struct
{
    handle_t handle;         /*!< PWM HAL handle. */
    hal_pwm_config_t config; /*!< PWM HAL configuration structure. */
} hal_pwm_t;

/**
 * @details Return values.
 */
typedef enum
{
    HAL_PWM_SUCCESS = 0,  /*!< Success. */
    HAL_PWM_MODULE_ERROR, /*!< Module Error. */
    HAL_PWM_WRONG_PIN,    /*!< Wrong pin. */

    HAL_PWM_ERROR = (-1) /*!< Error. */
} hal_pwm_err_t;

/*!
 * @addtogroup pergroup Microcontroller Peripherals
 * @{
 */

/*!
 * @addtogroup halgroup Hardware Abstraction Layer
 * @{
 */

/*!
 * @addtogroup halpwmgroup PWM HAL
 * @brief PWM Hardware Abstraction Layer API Reference.
 * @details API for configuring and manipulating PWM HAL module.
 * @{
 */

/**
 * @brief Configure PWM configuration structure.
 * @details Configures structure to default init values.
 * Take into consideration that this is just
 * structure variable initial values setting.
 * Values need to be redefined by user.
 * @param[in,out] config PWM HAL configuration settings.
 * See #hal_pwm_config_t structure definition for detailed explanation.
 *
 * @b Default @b values:
 * Function            | Default value             |
 * --------------------|---------------------------|
 * PWM pin             | HAL_PIN_NC (invalid pin)  |
 * Frequency in Hz     | 0 (Frequency set to 0)    |
 * @return Nothing.
 *
 * @b Example
 * @code
 *   hal_pwm_config_t hal_pwm_cfg;
 *
 *   hal_pwm_configure_default( &hal_pwm_cfg );
 * @endcode
 */
void hal_pwm_configure_default( hal_pwm_config_t *config );

/**
 * @brief Open the PWM HAL object on selected pin.
 * @details Opens the PWM HAL object on selected pin.
 * Allocates memory and pin for specified object.
 * @param[in,out] handle PWM handle.
 * See #hal_pwm_t structure definition for detailed explanation.
 * @param[in] hal_obj_open_state PWM state, is it open or not.
 * @return The function can return one of the values defined by
 * #hal_pwm_err_t, which is size dependant on the architecture.
 * @warning The following example describes how the function is used.
 * Take into consideration that different hardware might not have the same pin.
 * Make sure to accommodate pin name based on your hardware specifics.
 *
 * @b Example
 * @code
 *   hal_pwm_t hal_pwm;
 *   hal_pwm_config_t hal_pwm_cfg;
 *   hal_pwm_configure_default( &hal_pwm_cfg );
 *   hal_pwm_cfg.pin = MIKROBUS_1_PWM;
 *   hal_pwm_cfg.freq_hz = 5000;
 *
 *   hal_pwm_open( &hal_pwm->handle, true );
 * @endcode
 */
err_t hal_pwm_open( handle_t *handle, bool hal_obj_open_state );

/**
 * @brief Set PWM frequency in Hertz.
 * @details This function is used to set the PWM frequency,
 * it stops PWM module and sets duty cycle on 0.
 * Take into consideration that the module
 * will be re-initialized on the hardware level.
 * @param[in] handle PWM handle.
 * See #hal_pwm_t structure definition for detailed explanation.
 * @param[in] config PWM configuration structure.
 * See #hal_pwm_config_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #hal_pwm_err_t, which is size dependant on the architecture.
 * @pre Before calling this function, the user is expected to call #hal_pwm_open
 * @post This function stops PWM module and sets duty cycle on 0.
 * @note This function should be called first after #hal_pwm_open for the
 * PWM module to work. After calling this function, the user is expected
 * to call #hal_pwm_start and #pwm_set_duty.
 *
 * @b Example
 * @code
 *   hal_pwm_set_freq( &hal_pwm->handle, hal_pwm_cfg.freq_hz );
 * @endcode
 */
err_t hal_pwm_set_freq( handle_t *handle, hal_pwm_config_t *config );

/**
 * @brief Start PWM HAL context object.
 * @details Initializes PWM module on hardware level,
 * if not already initialized and starts PWM module.
 * @param[in] handle PWM handle.
 * @return The function can return one of the values defined by
 * #hal_pwm_err_t, which is size dependant on the architecture.
 * @pre Before calling this function, the user is expected
 * to set frequency by using #hal_pwm_set_freq function.
 *
 * @b Example
 * @code
 *   hal_pwm_start( &hal_pwm->handle );
 * @endcode
 */
err_t hal_pwm_start( handle_t *handle );

/**
 * @brief Set PWM duty cycle in percentages.
 * @details Set PWM duty cycle in percentages.
 * The user should enter the \p duty_ratio in percentages.
 * The \p duty_ratio value should be between 0 and 1,
 * (where 0 represents 0% and 1 represents 100%).
 * If the user sets value for \p duty_ratio to be less than 0,
 * \p duty_ratio is automatically set to 0(0%), and If the
 * user sets value for \p duty_ratio to be greater than 1,
 * \p duty_ratio is automatically set to 1(100%).
 * @param[in] handle PWM handle.
 * @param[in] duty_ratio PWM duty_ratio.
 * @return The function can return one of the values defined by
 * #hal_pwm_err_t, which is size dependant on the architecture.
 * @pre This function should be called after
 * the #hal_pwm_start function for the PWM to work.
 *
 * @b Example
 * @code
 *   hal_pwm_set_duty( &hal_pwm->handle, 0.5 );
 * @endcode
 */
err_t hal_pwm_set_duty( handle_t *handle, float duty_ratio );

/**
 * @brief Stop PWM module.
 * @details Disable output for specific PWM module.
 * @param[in] handle PWM handle.
 * @return The function can return one of the values defined by
 * #hal_pwm_err_t, which is size dependant on the architecture.
 * @pre In order to stop PWM module user should first start PWM module.
 * See #hal_pwm_start function definition for detailed explanation.
 * @note The PWM Module needs to be initialized so that
 * the stop can be done.
 *
 * @b Example
 * @code
 *   hal_pwm_stop( &hal_pwm->handle );
 * @endcode
 */
err_t hal_pwm_stop( handle_t *handle );

/**
 * @brief  Close PWM HAL object.
 * @details De-allocates hardware resources for specific HAL object and
 * de-initializes the module on a hardware level.
 * @param[in,out] handle PWM handle.
 * @return Nothing.
 *
 * @b Example
 * @code
 *   hal_pwm_close( &hal_pwm->handle );
 * @endcode
 */
err_t hal_pwm_close( handle_t *handle );

/*! @} */ // halpwmgroup
/*! @} */ // halgroup
/*! @} */ // pergroup

#ifdef __cplusplus
}
#endif

#endif // _HAL_PWM_H_
// ------------------------------------------------------------------------- END
