/****************************************************************************
**
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is part of the mikroSDK package
**
** Commercial License Usage
**
** Licensees holding valid commercial NECTO compilers AI licenses may use this
** file in accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The mikroElektronika Company.
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
 * @file  ssd1963_cmd.h
 * @brief SSD1963 Display Controller Commands.
 */

/*!
 * @addtogroup middlewaregroup Middleware
 * @{
 */

/*!
 * @addtogroup ssd1963 SSD1963 Display Controller Driver
 * @{
 */

/*!
 * @addtogroup ssd1963_commands SSD1963 Display Controller Commands
 * @brief SSD1963 Display Controller Command List
 * @{
 */

#ifndef SSD1963_CMD_H
#define SSD1963_CMD_H

/**
 * @brief No operation.
 */
#define SSD1963_CMD_NOP 0X00

/**
 * @brief Software Reset.
 */
#define SSD1963_CMD_SOFT_RESET 0x01

/**
 * @brief Get the current power mode.
 */
#define SSD1963_CMD_GET_POWER_MODE 0x0A

/**
 * @brief Get the frame buffer to the display panel read order.
 */
#define SSD1963_CMD_GET_ADDRESS_MODE 0x0B

// #define SSD1963_CMD_RESERVED 0X0C

/**
 * @brief The SSD1963 returns the Display Image Mode.
 */
#define SSD1963_CMD_GET_DISPLAY_MODE 0x0D

/**
 * @brief Get the Tear Effect status.
 */
#define SSD1963_CMD_GET_TEAR_EFFECT_status 0x0E

//#define SSD1963_CMD_RESERVED 0X0F

/**
 * @brief Turn off the panel. This command will pull high the GPIO0. If GPIO0 is configured as normal GPIO or LCD miscellaneous signal with command set_gpio_conf, this command will be ignored.
 */
#define SSD1963_CMD_ENTER_SLEEP_MODE 0x10

/**
 * @brief Turn on the panel. This command will pull low the GPIO0. If GPIO0 is configured as normal GPIO or LCD miscellaneous signal with command set_gpio_conf, this command will be ignored.
 */
#define SSD1963_CMD_EXIT_SLEEP_MODE 0x11

/**
 * @brief Part of the display area is used for image display.
 */
#define SSD1963_CMD_ENTER_PARTIAL_MODE 0x12

/**
 * @brief The whole display area is used for image display.
 */
#define SSD1963_CMD_ENTER_NORMAL_MODE 0x13

/**
 * @brief Displayed image colors are not inverted.
 */
#define SSD1963_CMD_EXIT_INVERT_MODE 0x20

/**
 * @brief Displayed image colors are inverted.
 */
#define SSD1963_CMD_ENTER_INVERT_MODE 0x21

/**
 * @brief Selects the gamma curve used by the display panel.
 */
#define SSD1963_CMD_SET_GAMMA_CURVE 0x26

/**
 * @brief Blanks the display panel.
 */
#define SSD1963_CMD_SET_DISPLAY_OFF 0x28

/**
 * @brief Show the image on the display panel.
 */
#define SSD1963_CMD_SET_DISPLAY_ON 0x29

/**
 * @brief Set the column address.
 */
#define SSD1963_CMD_SET_COLUMN_ADDRESS 0x2A

/**
 * @brief Set the page address.
 */
#define SSD1963_CMD_SET_PAGE_ADDRESS 0x2B

/**
 * @brief Transfer image information from the host processor interface to the SSD1963 starting at the location provided by set_column_address and set_page_address.
 */
#define SSD1963_CMD_WRITE_MEMORY_START 0x2C

/**
 * @brief Transfer image data from the SSD1963 to the host processor interface starting at the location provided by set_column_address and set_page_address.
 */
#define SSD1963_CMD_READ_MEMORY_START 0x2E

/**
 * @brief Defines the partial display area on the display panel.
 */
#define SSD1963_CMD_SET_PARTIAL_AREA 0x30

/**
 * @brief Defines the vertical scrolling and fixed area on display area.
 */
#define SSD1963_CMD_SET_SCROLL_AREA 0x33

/**
 * @brief Synchronization information is not sent from the SSD1963 to the host processor.
 */
#define SSD1963_CMD_SET_TEAR_OFF 0x34

/**
 * @brief Synchronization information is sent from the SSD1963 to the host processor at the start of VFP.
 */
#define SSD1963_CMD_SET_TEAR_ON 0x35

/**
 * @brief Set the read order from frame buffer to the display panel.
 */
#define SSD1963_CMD_SET_ADDRESS_MODE 0x36

/**
 * @brief Defines the vertical scrolling starting point.
 */
#define SSD1963_CMD_SET_SCROLL_START 0x37

/**
 * @brief Full color depth is used for the display panel.
 */
#define SSD1963_CMD_EXIT_IDLE_MODE 0x38

/**
 * @brief Reduce color depth is used on the display panel.
 */
#define SSD1963_CMD_ENTER_IDLE_MODE 0x39

// #define SSD1963_CMD_RESERVED 0X3A

/**
 * @brief Transfer image information from the host processor interface to the SSD1963 from the last written location.
 */
#define SSD1963_CMD_WRITE_MEMORY_CONTINUE 0x3C

/**
 * @brief Read image data from the SSD1963 continuing after the last read_memory_continue or read_memory_start.
 */
#define SSD1963_CMD_READ_MEMORY_CONTINUE 0x3E

/**
 * @brief Synchronization information is sent from the SSD1963 to the host processor when the display panel refresh reaches the provided scan line.
 */
#define SSD1963_CMD_SET_TEAR_SCANLINE 0x44

/**
 * @brief Get the current scan line.
 */
#define SSD1963_CMD_GET_SCANLINE 0x45

/**
 * @brief Read the DDB from the provided location.
 */
#define SSD1963_CMD_READ_DDB 0xA1

// #define SSD1963_CMD_RESERVED 0xA8

/**
 * @brief Set the LCD panel mode and resolution.
 */
#define SSD1963_CMD_SET_LCD_MODE 0xB0

/**
 * @brief Get the current LCD panel mode, pad strength and resolution.
 */
#define SSD1963_CMD_GET_LCD_MODE 0xB1

/**
 * @brief Set front porch
 */
#define SSD1963_CMD_SET_HORI_PERIOD 0xB4

/**
 * @brief Get current front porch settings.
 */
#define SSD1963_CMD_GET_HORI_PERIOD 0xB5

/**
 * @brief Set the vertical blanking interval between last scan line and next LFRAME pulse.
 */
#define SSD1963_CMD_SET_VERT_PERIOD 0xB6

/**
 * @brief Get the vertical blanking interval between last scan line and next LFRAME pulse.
 */
#define SSD1963_CMD_GET_VERT_PERIOD 0xB7

/**
 * @brief Set the GPIO configuration. If the GPIO is not used for LCD, set the direction. Otherwise, they are toggled with LCD signals.
 */
#define SSD1963_CMD_SET_GPIO_CONF 0xB8

/**
 * @brief Get the current GPIO configuration.
 */
#define SSD1963_CMD_GET_GPIO_CONF 0xB9

/**
 * @brief Set GPIO value for GPIO configured as output.
 */
#define SSD1963_CMD_SET_GPIO_VALUE 0xBA

/**
 * @brief Read current GPIO status. If the individual GPIO was configured as input, the value is the status of the corresponding pin. Otherwise, it is the programmed value.
 */
#define SSD1963_CMD_GET_GPIO_STATUS 0xBB

/**
 * @brief Set the image post processor.
 */
#define SSD1963_CMD_SET_POST_PROC 0xBC

/**
 * @brief Get the image post processor.
 */
#define SSD1963_CMD_GET_POST_PROC 0xBD

/**
 * @brief Set the image post processor.
 */
#define SSD1963_CMD_SET_PWM_CONF 0xBE

 /**
 * @brief Get the image post processor.
 */
#define SSD1963_CMD_GET_PWM_CONF 0xBF

/**
 * @brief Set the rise, fall, period and toggling properties of LCD signal generator 0.
 */
#define SSD1963_CMD_SET_LCD_GEN0 0xC0

/**
 * @brief Get the current settings of LCD signal generator 0.
 */
#define SSD1963_CMD_GET_LCD_GEN0 0xC1

/**
 * @brief Set the rise, fall, period and toggling properties of LCD signal generator 1.
 */
#define SSD1963_CMD_SET_LCD_GEN1 0xC2

/**
 * @brief Get the current settings of LCD signal generator 1.
 */
#define SSD1963_CMD_GET_LCD_GEN1 0xC3

/**
 * @brief Set the rise, fall, period and toggling properties of LCD signal generator 2.
 */
#define SSD1963_CMD_SET_LCD_GEN2 0xC4

/**
 * @brief Get the current settings of LCD signal generator 2.
 */
#define SSD1963_CMD_GET_LCD_GEN2 0xC5

/**
 * @brief Set the rise, fall, period and toggling properties of LCD signal generator 3.
 */
#define SSD1963_CMD_SET_LCD_GEN3 0xC6

/**
 * @brief Get the current settings of LCD signal generator 3.
 */
#define SSD1963_CMD_GET_LCD_GEN3 0xC7

/**
 * @brief Set the GPIO0 with respect to the LCD signal generators using ROP operation. No effect if the GPIO0 is configured as general GPIO.
 */
#define SSD1963_CMD_SET_GPIO0_ROP 0xC8

/**
 * @brief Get the GPIO0 properties with respect to the LCD signal generators.
 */
#define SSD1963_CMD_GET_GPIO0_ROP 0xC9

/**
 * @brief Set the GPIO1 with respect to the LCD signal generators using ROP operation. No effect if the GPIO1 is configured as general GPIO.
 */
#define SSD1963_CMD_SET_GPIO1_ROP 0xCA

/**
 * @brief Get the GPIO1 properties with respect to the LCD signal generators.
 */
#define SSD1963_CMD_GET_GPIO1_ROP 0xCB

/**
 * @brief Set the GPIO2 with respect to the LCD signal generators using ROP operation. No effect if the GPIO2 is configured as general GPIO.
 */
#define SSD1963_CMD_SET_GPIO2_ROP 0xCC

/**
 * @brief Get the GPIO2 properties with respect to the LCD signal generators.
 */
#define SSD1963_CMD_GET_GPIO2_ROP 0xCD

/**
 * @brief Set the GPIO3 with respect to the LCD signal generators using ROP operation. No effect if the GPIO3 is configured as general GPIO.
 */
#define SSD1963_CMD_SET_GPIO3_ROP 0xCE

/**
 * @brief Get the GPIO3 properties with respect to the LCD signal generators.
 */
#define SSD1963_CMD_GET_GPIO3_ROP 0xCF

/**
 * @brief Set the dynamic back light configuration.
 */
#define SSD1963_CMD_SET_DBC_CONF 0xD0

/**
 * @brief Get the current dynamic back light configuration.
 */
#define SSD1963_CMD_GET_DBC_CONF 0xD

/**
 * @brief Set the threshold for each level of power saving.
 */
#define SSD1963_CMD_SET_DBC_TH 0xD4

/**
 * @brief Get the threshold for each level of power saving.
 */
#define SSD1963_CMD_GET_DBC_TH 0xD5

/**
 * @brief Start the PLL. Before the start, the system was operated with the crystal oscillator or clock input.
 */
#define SSD1963_CMD_SET_PLL 0xE0

/**
 * @brief Set the PLL.
 */
#define SSD1963_CMD_SET_PLL_MN 0xE2

/**
 * @brief Get the PLL settings.
 */
#define SSD1963_CMD_GET_PLL_MN 0xE3

/**
 * @brief Get the current PLL status.
 */
#define SSD1963_CMD_GET_PLL_STATUS 0xE4

/**
 * @brief Set deep sleep mode.
 */
#define SSD1963_CMD_SET_DEEP_SLEEP 0xE5

/**
 * @brief Set the LSHIFT (pixel clock) frequency.
 */
#define SSD1963_CMD_SET_LSHIFT_FREQ 0xE6

/**
 * @brief Get current LSHIFT (pixel clock) frequency setting.
 */
#define SSD1963_CMD_GET_LSHIFT_FREQ 0xE7

// #define SSD1963_CMD_RESERVED 0xE8
// #define SSD1963_CMD_RESERVED 0xE9

/**
 * @brief Set the pixel data format of the parallel host processor interface.
 */
#define SSD1963_CMD_SET_PIXEL_DATA_INTERFACE 0xF0

/**
 * @brief Get the current pixel data format settings.
 */
#define SSD1963_CMD_GET_PIXEL_DATA_INTERFACE 0xF1

// #define SSD1963_CMD_RESERVED 0xFF

/*! @} */ // ssd1963
/*! @} */ // ssd1963
/*! @} */ // mwgroup

#endif // SSD1963_CMD_H
// ------------------------------------------------------------------------- END
