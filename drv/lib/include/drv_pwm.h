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
 * @file  drv_pwm.h
 * @brief API for PWM driver.
 */

#ifndef _DRV_PWM_H_
#define _DRV_PWM_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_name.h"
#include "hal_pwm.h"

/**
 * @details Return values.
 */
typedef enum
{
    PWM_SUCCESS = 0,    /*!< Success. */
    PWM_ERROR = (-1)    /*!< Error. */
} pwm_err_t;

/**
 * @brief PWM driver config structure, consisted of the following fields:
 * @details The context structure for storing driver configuration.
 * User shall define the values stored within.
 * @warning The following example describes how to fill a #pwm_config_t structure.
 * Take into consideration that different hardware might not have the same pin.
 * Make sure to accommodate pin name based on your hardware specifics.
 *
 * @b Example
 * @code
 *   // PWM driver configuration structure.
 *   pwm_config_t pwm_cfg;
 *
 *   // Set PWM pin.
 *   pwm_cfg.pin = MIKROBUS_1_PWM;
 *
 *   // Set PWM frequency.
 *   pwm_cfg.freq_hz = 5000;
 * @endcode
 */
typedef struct
{
    pin_name_t pin;    /*!< PWM pin. */
    uint32_t freq_hz;  /*!< PWM Frequency in Hz. */
} pwm_config_t;


/**
 * @brief PWM driver context structure.
 * @details The context structure for storing driver internal state.
 * The contents of the context structure are used by the module and must not be altered.
 * Reading or writing data directly from a control structure by user should be avoided.
 */
typedef struct
{
    handle_t handle;        /*!< PWM driver handle. */
    pwm_config_t config;    /*!< PWM driver configuration structure. */
} pwm_t;

/*!
 * @addtogroup pergroup Microcontroller Peripherals
 * @{
 */

/*!
 * @addtogroup drvgroup Driver Layer
 * @{
 */

/*!
 * @addtogroup drvpwmgroup PWM Driver
 * @brief PWM Driver API Reference.
 * @details The PWM driver provides standard PMM functionality including setting the duty cycle and frequency.
 * @{
 */

/**
 * @brief Configure PWM config structure.
 * @details Configures structure to default initialization values.
 * Take into consideration that this is just
 * structure variable initial values setting.
 * Values need to be redefined by user.
 * @param[in,out] config PWM driver configuration settings.
 * See #pwm_config_t structure definition for detailed explanation.
 *
 * @b Default @b values:
 * Function            | Default value             |
 * --------------------|---------------------------|
 * PWM pin             | 0xFFFFFFFF (invalid pin)  |
 * Frequency in Hz     | 0 (Frequency set to 0)    |
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // PWM driver configuration structure.
 *   pwm_config_t pwm_cfg;
 *
 *   // Fill structure with default values.
 *   pwm_configure_default( &pwm_cfg );
 * @endcode
 */
void pwm_configure_default( pwm_config_t *config );

/**
 * @brief Open the PWM driver object on selected pin.
 * @details Opens the PWM driver object on selected pins.
 * Allocates memory and pin for specified object.
 * @param[in,out] obj PWM driver object.
 * See #pwm_t structure definition for detailed explanation.
 * @param[in] config PWM driver configuration settings.
 * See #pwm_config_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #pwm_err_t, which is size dependant on the architecture.
 * @pre Make sure that \p pwm_config_t structure has been adequately
 * filled out.
 * See #pwm_configure_default definition for detailed explanation.
 * @note This function needs to be called before other driver functions.
 * It is recommended to check return value for error.
 * @warning The following example describes how the function is used.
 * Take into consideration that different hardware might not have the same pin.
 * Make sure to accommodate pin name based on your hardware specifics.
 *
 * @b Example
 * @code
 *   // PWM driver context structure.
 *   pwm_t pwm;
 *
 *   // PWM driver configuration structure.
 *   pwm_config_t pwm_cfg;
 *
 *   // Fill structure with default values.
 *   pwm_configure_default( &pwm_cfg );
 *
 *   // Fill structure with pin name.
 *   pwm_cfg.pin = MIKROBUS_1_PWM;
 *
 *   // Fill structure with PWM frequency.
 *   pwm_cfg.freq_hz = 5000;
 *
 *   // Open PWM driver.
 *   pwm_open( &pwm, &pwm_cfg );
 * @endcode
 */
err_t pwm_open( pwm_t *obj, pwm_config_t *config );

/**
 * @brief Set PWM frequency in Hertz.
 * @details This function is used to set the PWM frequency,
 * it stops PWM module and sets duty_cycle on 0.
 * Take into consideration that the module
 * will be re-initialized on the hardware level.
 * @param[in] obj PWM driver context object.
 * See #pwm_t structure definition for detailed explanation.
 * @param[in] freq_hz PWM frequency in HZ.
 * @return The function can return one of the values defined by
 * #pwm_err_t, which is size dependant on the architecture.
 * @pre Before calling this function, the user is expected to call #pwm_open function.
 * @post This function stops PWM module and sets duty cycle on 0.
 * @note This function should be called first after #pwm_open for the
 * PWM module to work. After calling this function, the user is expected
 * to call #pwm_start and #pwm_set_duty.
 *
 * @b Example
 * @code
 *   // PWM driver context structure.
 *   pwm_t pwm;
 *
 *   // Fill structure with PWM frequency.
 *   pwm_cfg.freq_hz = 5000;
 *
 *   // Set PWM frequency.
 *   pwm_set_freq( &pwm, pwm_cfg.freq_hz );
 * @endcode
 */
err_t pwm_set_freq( pwm_t *obj, uint32_t freq_hz );

/**
 * @brief Enable counter and start PWM module.
 * @details Initializes PWM module on hardware level,
 * if not already initialized and starts PWM module.
 * @param[in] obj PWM driver object.
 * See #pwm_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #pwm_err_t, which is size dependant on the architecture.
 * @pre Before calling this function, the user is expected
 * to set frequency by using #pwm_set_freq function.
 *
 * @b Example
 * @code
 *   // PWM driver context structure.
 *   pwm_t pwm;
 *
 *   // Start PWM module.
 *   pwm_start( &pwm );
 * @endcode
 */
err_t pwm_start( pwm_t *obj );

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
 * @param[in] obj PWM driver object.
 * See #pwm_t structure definition for detailed explanation.
 * @param[in] duty_ratio PWM duty_ratio.
 * @return The function can return one of the values defined by
 * #pwm_err_t, which is size dependant on the architecture.
 * @pre This function should be called after
 * the #pwm_start function for the PWM to work.
 *
 * @b Example
 * @code
 *   // PWM driver context structure.
 *   pwm_t pwm;
 *
 *   // PWM duty ratio.
 *   float duty_ratio = 0,5;
 *
 *   // Set PWM duty ratio.
 *   pwm_set_duty( &pwm, duty_ratio );
 * @endcode
 */
err_t pwm_set_duty( pwm_t *obj, float duty_ratio );

/**
 * @brief Stop PWM module.
 * @details Disable output for specific PWM module.
 * @param[in] obj PWM driver object.
 * See #pwm_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #pwm_err_t, which is size dependant on the architecture.
 * @pre In order to stop PWM module user should first start PWM module.
 * See #pwm_start function definition for detailed explanation.
 * @note The PWM Module needs to be initialized so that
 * the stop can be done.
 *
 * @b Example
 * @code
 *   // PWM driver context structure.
 *   pwm_t pwm;
 *
 *   // Stop PWM module.
 *   pwm_stop( &pwm );
 * @endcode
 */
err_t pwm_stop( pwm_t *obj );

/**
 * @brief  Close PWM driver context object.
 * @details De-allocates hardware resources for specific driver object and
 * de-initializes the module on a hardware level.
 * @param[in,out] obj PWM driver object.
 * See #pwm_t structure definition for detailed explanation.
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // PWM driver context structure.
 *   pwm_t pwm;
 *
 *   // Close PWM driver.
 *   pwm_close( &pwm );
 * @endcode
 */
void pwm_close( pwm_t *obj );

/*! @} */ // drvpwmgroup
/*! @} */ // drvgroup
/*! @} */ // pergroup

#ifdef __cplusplus
}
#endif

#endif // _DRV_PWM_H_
// ------------------------------------------------------------------------- END
