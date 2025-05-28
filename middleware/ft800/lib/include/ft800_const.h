/****************************************************************************
**
** Copyright (C) ${COPYRIGHT_YEAR} MikroElektronika d.o.o.
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
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file  ft800_const.h
 * @brief FT800 Display Controller Constants.
 */

/*!
 * @addtogroup middlewaregroup Middleware
 * @{
 */

/*!
 * @addtogroup ft800 FT800 Display Controller Driver
 * @{
 */

/*!
 * @addtogroup ft800_constants FT800 Display Controller Registers
 * @brief FT800 Display Controller Constants List
 * @{
 */

#ifndef FT800_REG_H
#define FT800_REG_H


/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_RX_DATA_BUFF                5

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_TX_DATA_BUFF                3

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_RAM_G_HEADER                3

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_EVENT_GEST_ZOOM_OUT                0x49

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_EVENT_GEST_ZOOM_IN                0x48

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_EVENT_GEST_DOWN                0x18

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_EVENT_GEST_UP                0x10

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_EVENT_GEST_RIGHT                0x14

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_EVENT_GEST_LEFT                0x1C

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_COMMAND_OFFSET                4

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_SPI_RECEIVE_DATA_LENGTH_5                5

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_SPI_RECEIVE_DATA_LENGTH_3                3

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_SPI_RECEIVE_DATA_LENGTH_2                2

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_SPI_SEND_DATA_LENGTH_7                7

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_SPI_SEND_DATA_LENGTH_5                5

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_SPI_SEND_DATA_LENGTH_4                4

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_SPI_SEND_DATA_LENGTH_3                3

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CHAR_HEIGHT_31                36

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CHAR_HEIGHT_30                30

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CHAR_HEIGHT_29                25

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CHAR_HEIGHT_28                21

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CHAR_HEIGHT_27                16

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CHAR_HEIGHT_26                13

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_TEXT_SCALE_Y                2

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_TEXT_SCALE_X                2

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_LETTER_WIDTH_31                24

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_LETTER_WIDTH_30                17

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_LETTER_WIDTH_29                14

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_LETTER_WIDTH_28                12

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_LETTER_WIDTH_27                10

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_LETTER_WIDTH_26                8

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_TEXT_HEIGHT_MIDDLE_31                18

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_TEXT_HEIGHT_MIDDLE_30                15

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_TEXT_HEIGHT_MIDDLE_29                12

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_TEXT_HEIGHT_MIDDLE_28                10

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_TEXT_HEIGHT_MIDDLE_27                8

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_TEXT_HEIGHT_MIDDLE_26                6

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_TEXT_FONT_SIZE_31                 31

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_TEXT_FONT_SIZE_30                 30

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_TEXT_FONT_SIZE_29                 29

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_TEXT_FONT_SIZE_28                 28

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_TEXT_FONT_SIZE_27                 27

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_TEXT_FONT_SIZE_26                 26

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_TEXT_SIZE_80                 80

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_TEXT_SIZE_64                 64

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_TEXT_SIZE_48                 48

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_TEXT_SIZE_32                 32

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_TEXT_SIZE_16                 16

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_RECTANGLE_GRADIENT_OFFSET_X                 1

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_RECTANGLE_GRADIENT_OFFSET_Y                 1

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_RECTANGLE_GRADIENT_WIDTH_SCALE                 2

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_RECTANGLE_GRADIENT_HEIGHT_SCALE                 2

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_RECTANGLE_EDGES_THETA_SCALE                 3.14159 / 2.0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_RECTANGLE_EDGES_HEIGHT_SCALE                 2

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_RECTANGLE_EDGES_WIDTH_SCALE                 2

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_RECTANGLE_EDGES_RADIUS_SCALE                 2

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_RECTANGLE_EDGES_SEGMENT                 10

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_ELLIPSE_GRADIENT_INTPOL_OFFSET          1

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_ELLIPSE_GRADIENT_INTPOL_OFFSET_Y          0.5

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_ELLIPSE_GRADIENT_NORMAL_VALUE          1.0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_ELLIPSE_GRADIENT_SEGMENTS              100

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_ELLIPSE_GRADIENT_HEIGHT_SCALE              2.0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_ELLIPSE_GRADIENT_WIDTH_SCALE              2.0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_ELLIPSE_EDGES_THETA_SCALE                2.0 / 3.14159

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_ELLIPSE_EDGES_SEGMENTS              100

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_ELLIPSE_EDGES_HEIGHT_SCALE              2.0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_ELLIPSE_EDGES_WIDTH_SCALE              2.0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CIRCLE_GRADIENT_OFFSET_X          1

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CIRCLE_GRADIENT_OFFSET_Y          1

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CIRCLE_GRADIENT_NORMAL_VALUE          1.0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CIRCLE_GRADIENT_RADIUS_SCALE              2.0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CIRCLE_GRADIENT_WIDTH_SCALE              2.0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CIRCLE_EDGES_SEGMENTS                100

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CIRCLE_EDGES_THETA_SCALE                2.0 / 3.14159

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CIRCLE_EDGES_WIDTH_SCALE                2.0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_RGB_BLUE_SCALE                255.0 / 31.0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_RGB_GREEN_SCALE                255.0 / 63.0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_RGB_RED_SCALE                255.0 / 31.0


/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_IMAGE_BITMAP_LAYOUT_FORMAT                7

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_IMAGE_PADDING_SIZE                4

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_IMAGE_PADDING_ALIGMENT                4

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_IMAGE_SIZE_CONST_2                6

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_IMAGE_SIZE_CONST_1                2

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_ELLIPSE_WIDTH_SCALE                2.0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_ELLIPSE_HEIGHT_SCALE                2.0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_RADIO_BUTTON_HEIGHT_SCALE_R                2.0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_RADIO_BUTTON_HEIGHT_SCALE_L                2.0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_RADIO_BUTTON_CENTER_SCALE_R                2.0 / 3.0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_RADIO_BUTTON_PEN_OFFSET_SCALE                2

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_RADIO_BUTTON_CENTER_SCALE_L                2.0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CHECK_BOX_CORNER_RADIUS_SCALE                2

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CHECK_BOX_PEN_OFFSET_SCALE                2

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CHECK_BOX_SIGN_SCALE_3                2.0 / 3.0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CHECK_BOX_SIGN_SCALE_2                1.0 / 3.0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CHECK_BOX_SIGN_SCALE_1                10.0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_PROGRESS_BAR_NUMBER_Y_OFFSET                13

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_PROGRESS_BAR_NUMBER_HEIGHT_SCALE                2

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_PROGRESS_BAR_NUMBER_WIDTH_SCALE                5

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_PROGRESS_BAR_PERCENTAGE_SCALE                100

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_PROGRESS_BAR_OFFSET_X_RIGHT                52

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_PROGRESS_BAR_OFFSET_X_LEFT                26

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_BOX_RADIUS_SCALE                2

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CIRCLE_RADIUS_SCALE                2

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_BUTTON_RADIUS_SCALE                2

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_ALIGMENT_ADDRES                0x03

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_TOUCH_ACTIVATION_VALUE                0x03

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CALIBRATE_TEXT_FONT                0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CALIBRATE_TEXT_Y                  120

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CALIBRATE_TEXT_X                  80


/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_RAM_DL_OFFSET_4                  4

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_RAM_DL_OFFSET_8                  8

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_PCLK_VALUE                  0x05

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_PWM_DUTY_VALUE                  0x80

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_PWM_HZ_VALUE                  0x00FA

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_GPIO_VALUE                  0x80

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_GPIO_DIR_VALUE                  0x80

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_DLSWAP_VALUE                  2

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CLR_BUFF_MASK                  1

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_RGB_INIT_VALUE                 255

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_CSPREAD_VALUE                 0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_VSIZE_VALUE                  272

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_HSIZE_VALUE                  480

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_PCLK_POL_VALUE                 1

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_VSYNC1_VALUE                  10

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_VSYNC0_VALUE                  0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_VOFFSET_VALUE                  12

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_VCYCLE_VALUE                  292

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_HSYNC1_VALUE                  41

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_HSYNC0_VALUE                  0

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_HOFFSET_VALUE                  43

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_HCYCLE_VALUE                  548

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_PCLK_INIT_VALUE                  0x00

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_GPIO_INIT_VALUE                  0x00

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_POINT_SIZE_SCALE                  16

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_SPI_INIT_SPEED                    18000000

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_SPI_SPEED                          4500000

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_READED_COORD_MASK                   0xFFFF

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_COMMAND_MASK                        0xFFFF

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_SELECT_LSB_BITS_1                   0x01

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_SELECT_LSB_BITS_2                   0x03

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_SELECT_LSB_BITS_3                   0x07

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_SELECT_LSB_BITS_4                   0x0F

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_SELECT_LSB_BITS_5                   0x1F

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_SELECT_LSB_BITS_6                   0x3F

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_SELECT_LSB_BITS_7                   0x7F

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_SELECT_BYTE                          0xFF

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_SENT_COMMAND_LABEL                   0x40

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_SENT_DATA_LABEL                      0x80

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_RECEIVE_DATA_LABEL                   0x3F

/**
 * @brief FT800 Offset Value.
 * @details Macro for 2 bytes offset for FT800 series controllers.
 */
#define FT800_OFFSET_COMMAND_PARAM_BYTES_2         16

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_OFFSET_RECEIVED_DATA_BYTES_1          8

/**
 * @brief FT800 Offset Value.
 * @details Macro for 2 bytes offset for FT800 series controllers.
 */
#define FT800_OFFSET_RECEIVED_DATA_BYTES_2          16

/**
 * @brief FT800 Offset Value.
 * @details Macro for 3 bytes offset for FT800 series controllers.
 */
#define FT800_OFFSET_RECEIVED_DATA_BYTES_3          24

/**
 * @brief FT800 Offset Value.
 * @details Macro for 4 bytes offset for FT800 series controllers.
 */
#define FT800__OFFSET_RECEIVED_DATA_BYTES_4         32

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_OFFSET_RGB_COLOR_GREEN                5

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_OFFSET_RGB_COLOR_RED                  11

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_OFFSET_READED_COORD_BYTES_2           16

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_OFFSET_RECEIVED_ADDRES_BYTES_1        8

/**
 * @brief FT800 Offset Value.
 * @details Macro for 2 bytes offset for FT800 series controllers.
 */
#define FT800_OFFSET_RECEIVED_ADDRES_BYTES_2        16

/**
 * @brief FT800 Offset Value.
 * @details Macro for 3 bytes offset for FT800 series controllers.
 */
#define FT800_OFFSET_RECEIVED_ADDRES_BYTES_3        24

/**
 * @brief FT800 Offset Value.
 * @details Macro for 4 bytes offset for FT800 series controllers.
 */
#define FT800__OFFSET_RECEIVED_ADDRES_BYTES_4       32

/**
 * @brief FT800 Offset Value.
 * @details Macro for 1 bytes offset for FT800 series controllers.
 */
#define FT800_OFFSET_SENT_ADDRES_BYTES_1        8

/**
 * @brief FT800 Offset Value.
 * @details Macro for 2 bytes offset for FT800 series controllers.
 */
#define FT800_OFFSET_SENT_ADDRES_BYTES_2        16

/**
 * @brief FT800 Offset Value.
 * @details Macro for 3 bytes offset for FT800 series controllers.
 */
#define FT800_OFFSET_SENT_ADDRES_BYTES_3        24

/**
 * @brief FT800 Offset Value.
 * @details Macro for 4 bytes offset for FT800 series controllers.
 */
#define FT800__OFFSET_SENT_ADDRES_BYTES_4       32

/**
 * @brief FT800 Data Length Size.
 * @details Macro for 1 bytes of data for FT800 series controllers.
 */
#define FT800_DATA_LENGTH_BYTES_1   8

/**
 * @brief FT800 Data Length Size.
 * @details Macro for 2 bytes of data for FT800 series controllers.
 */
#define FT800_DATA_LENGTH_BYTES_2   16

/**
 * @brief FT800 Data Length Size.
 * @detailsMacro for 3 bytes of data for FT800 series controllers.
 */
#define FT800_DATA_LENGTH_BYTES_3   24

/**
 * @brief FT800 Data Length Size.
 * @details Macro for 4 bytes of data for FT800 series controllers.
 */
#define FT800_DATA_LENGTH_BYTES_4   32

/**
 * @brief FT800 Gesture Items Limit Setting.
 * @details Gesture items limit for FT800 series controllers.
 */
#define FT800_TOUCH_NUM     1

/**
 * @brief FT800 Gesture Items Limit Setting.
 * @details Gesture items limit for FT800 series controllers.
 */
#define FT800_GESTURE_ITEMS_MAX     7

  /*! @} */ // ft800_constants
 /*! @} */ // ft800
/*! @} */ // mwgroup

#endif 
// ------------------------------------------------------------------------- END
