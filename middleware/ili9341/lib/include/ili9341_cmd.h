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
 * @file  ili9341_cmd.h
 * @brief ILI9341 Display Controller Commands.
 */

/*!
 * @addtogroup middlewaregroup Middleware
 * @{
 */

/*!
 * @addtogroup ili9341 ILI9341 Display Controller Driver
 * @{
 */

/*!
 * @addtogroup ili9341_commands ILI9341 Display Controller Commands
 * @brief ILI9341 Display Controller Command List
 * @{
 */

#ifndef _ILI9341_CMD_H_
#define _ILI9341_CMD_H_

/**
 * @brief No operation.
 */
#define ILI9341_CMD_NO_OPERATION 0x00

/**
 * @brief When the Software Reset command is written, it causes a software reset. It resets the commands and parameters to their
 * S/W Reset default values.
 */
#define ILI9341_CMD_SOFTWARE_RESET 0x01

/**
 * @brief This read byte returns 24 bits display identification information.
 * The 1st parameter is dummy data.
 * The 2nd parameter (ID1 [7:0]): LCD module’s manufacturer ID.
 * The 3rd parameter (ID2 [7:0]): LCD module/driver version ID.
 * The 4th parameter (ID3 [7:0]): LCD module/driver ID.
 */
#define ILI9341_CMD_READ_DISPLAY_INDETIFICATION_IINFORMATION 0x04

/**
 * @brief These commands indicate the current status of the display.
 */
#define ILI9341_CMD_READ_DISPLAY_STATUS                 0x09
#define ILI9341_CMD_READ_DISPLAY_POWER_MODE             0x0A
#define ILI9341_CMD_READ_DISPLAY_MADCTL                 0x0B
#define ILI9341_CMD_READ_DISPLAY_PIXEL_FORMAT           0x0C
#define ILI9341_CMD_READ_DISPLAY_IMAGE_FORMAT           0x0D
#define ILI9341_CMD_READ_DISPLAY_SIGNAL_MODE            0x0E
#define ILI9341_CMD_READ_DISPLAY_SELF_DIAGNOSTIC_RESULT 0x0F

/**
 * @brief This command causes the LCD module to enter the minimum power consumption mode. In this mode e.g. the DC/DC
 * converter is stopped, Internal oscillator is stopped, and panel scanning is stopped.
 * MCU interface and memory are still working and the memory keeps its contents.
 */
#define ILI9341_CMD_ENTER_SLEEP_MODE 0x10

/**
 * @brief This command turns off sleep mode.
 * In this mode e.g. the DC/DC converter is enabled, Internal oscillator is started, and panel scanning is started.
 */
#define ILI9341_CMD_SLEEP_OUT 0x11

/**
 * @brief This command turns on partial mode The partial mode window is described by the Partial Area command (30H). To leave
 * Partial mode, the Normal Display Mode On command (13H) should be written.
 */
#define ILI9341_CMD_PARTIAL_MODE_ON 0x12

/**
 * @brief This command returns the display to normal mode.
 * Normal display mode on means Partial mode off.
 * Exit from NORON by the Partial mode On command (12h).
 */
#define ILI9341_CMD_NORMAL_DISPLAY_MODE_ON 0x13

/**
 * @brief This command is used to recover from display inversion mode.
 * This command makes no change of the content of frame memory.
 * This command doesn’t change any other status.
 */
#define ILI9341_CMD_DISPLAY_INVERSION_MODE_OFF 0x20

/**
 * @brief This command is used to enter into display inversion mode.
 * This command makes no change of the content of frame memory. Every bit is inverted from the frame memory to the display.
 * This command doesn’t change any other status.
 * To exit Display inversion mode, the Display inversion OFF command (20h) should be written.
 */
#define ILI9341_CMD_DISPLAY_INVERSION_MODE_ON 0x21

/**
 * @brief This command is used to select the desired Gamma curve for the current display. A maximum of 4 fixed gamma curves can be selected.
 * The curve is selected by setting the appropriate bit in the parameter.
 * GC [7:0]
 * 0x01 : Gamma curve 1
 * 0x02 : Gamma curve 2
 * 0x04 : Gamma curve 3
 * 0x08 : Gamma curve 4
 */
#define ILI9341_CMD_GAMMA_SET            0x26
#define ILI9341_PARAM_1_GAMMA_CURVE_BITS 0x01

/**
 * @brief This command is used to enter into DISPLAY OFF mode. In this mode, the output from Frame Memory is disabled and blank
 * page inserted.
 * This command makes no change of contents of frame memory.
 * This command does not change any other status.
 * There will be no abnormal visible effect on the display.
 */
#define ILI9341_CMD_DISPLAY_OFF 0x28

/**
 * @brief This command is used to recover from DISPLAY OFF mode. Output from the Frame Memory is enabled.
 * This command makes no change of contents of frame memory.
 * This command does not change any other status.
 */
#define ILI9341_CMD_DISPLAY_ON 0x29

/**
 * @brief This command is used to define area of frame memory where MCU can access. This command makes no change on the
 * other driver status. The values of SC [15:0] and EC [15:0] are referred when RAMWR command comes. Each value
 * represents one column line in the Frame Memory.
 */
#define ILI9341_CMD_COLUMN_ADDRESS_SET 0x2A
/**
 * @brief This command is used to define area of frame memory where MCU can access. This command makes no change on the
 * other driver status. The values of SP [15:0] and EP [15:0] are referred when RAMWR command comes. Each value
 * represents one Page line in the Frame Memory.
 */
#define ILI9341_CMD_PAGE_ADDRESS_SET 0x2B

/**
 * @brief This command is used to transfer data from MCU to frame memory. This command makes no change to the other driver
 * status. When this command is accepted, the column register and the page register are reset to the Start Column/Start
 * Page positions. The Start Column/Start Page positions are different in accordance with MADCTL setting.) Then D [17:0] is
 * stored in frame memory and the column register and the page register incremented. Sending any other command can stop
 * frame Write.
 */
#define ILI9341_CMD_MEMORY_WRITE 0x2C

/**
 * @brief This command is used to define the LUT for 16-bit to 18-bit color depth conversion.
 * 128 bytes must be written to the LUT regardless of the color mode. Only the values in Section 7.4 are referred.
 * This command has no effect on other commands, parameter and contents of frame memory. Visible change takes effect
 * next time the frame memory is written to.
 */
#define ILI9341_CMD_COLOR_SET 0x2D

/**
 * @brief This command transfers image data from ILI9341’s frame memory to the host processor starting at the pixel location
 * specified by preceding set_column_address and set_page_address commands.
 */
#define ILI9341_CMD_MEMORY_READ 0x2E

/**
 * @brief This command defines the partial mode’s display area. There are 2 parameters associated with this command, the first
 * defines the Start Row (SR) and the second the End Row (ER). SR and ER refer to the
 * Frame Memory Line Pointer.
 */
#define ILI9341_CMD_PARTIAL_AREA 0x30

/**
 * @brief This command defines the Vertical Scrolling Area of the display.
 * When MADCTL B4=0
 * The 1st & 2nd parameter TFA [15...0] describes the Top Fixed Area (in No. of lines from Top of the Frame Memory and
 * Display).
 * The 3rd & 4th parameter VSA [15...0] describes the height of the Vertical Scrolling Area (in No. of lines of the Frame
 * Memory [not the display] from the Vertical Scrolling Start Address). The first line read from Frame Memory appears
 * immediately after the bottom most line of the Top Fixed Area.
 * The 5th & 6th parameter BFA [15...0] describes the Bottom Fixed Area (in No. of lines from Bottom of the Frame Memory
 * and Display). TFA, VSA and BFA refer to the Frame Memory Line Pointer.
 */
#define ILI9341_CMD_VERTICAL_SCROLLING_DEFINITION 0x33

/**
 * @brief This command is used to turn OFF (Active Low) the Tearing Effect output signal from the TE signal line.
 */
#define ILI9341_CMD_TEARING_EFFECT_LINE_OFF 0x34

/**
 * @brief This command is used to turn ON the Tearing Effect output signal from the TE signal line. This output is not affected by
 * changing MADCTL bit B4. The Tearing Effect Line On has one parameter which describes the mode of the Tearing Effect
 * Output Line.
 */
#define ILI9341_CMD_TEARING_EFFECT_LINE_ON 0x35

/**
 * @brief This command defines read/write scanning direction of frame memory.
 * This command makes no change on the other driver status.
 * bit[2] MH : Horizontal refresh order
 * bit[3] BGR : RGB-BGR order
 * bit[4] ML : Vertical refresh order
 * bit[5] MV : Row/Column exchange
 * bit[6] MX : Column address order
 * bit[7] MY : Row address order
 */
#define ILI9341_CMD_MEMORY_ACCESS_CONTROL 0x36
#define ILI9341_PARAM_1_NO_ROTATION       0x28
#define ILI9341_PARAM_1_ROTATE_180        0xE8
#define ILI9341_PARAM_1_ROTATE_90         0x48
#define ILI9341_PARAM_1_ROTATE_270        0x88

/**
 * @brief This command is used together with Vertical Scrolling Definition (33h). These two commands describe the scrolling area
 * and the scrolling mode. The Vertical Scrolling Start Address command has one parameter which describes the address of
 * the line in the Frame Memory that will be written as the first line after the last line of the Top Fixed Area.
 */
#define ILI9341_CMD_VERTICAL_SCROLLING_START_ADDRESS 0x37

/**
 * @brief This command is used to recover from Idle mode on.
 * In the idle off mode, LCD can display maximum 262,144 colors.
 */
#define ILI9341_CMD_IDLE_MODE_OFF 0x38

/**
 * @brief This command is used to enter into Idle mode on.
 * In the idle on mode, color expression is reduced. The primary and the secondary colors using MSB of each R, G and B in the
 * Frame Memory, 8 color depth data is displayed.
 */
#define ILI9341_CMD_IDLE_MODE_ON 0x39

/**
 * @brief This command sets the pixel format for the RGB image data used by the interface. DPI [2:0] is the pixel format select of RGB
 * interface and DBI [2:0] is the pixel format of MCU interface. If a particular interface, either RGB interface or MCU interface, is
 * not used then the corresponding bits in the parameter are ignored.
 * bit[6:4] DPI : RGB interface format
 * 101 : 16 bits/pixel
 * 110 : 18 bits/pixel
 * bit[2:0] DBI : MCU interface format
 * 101 : 16 bits/pixel
 * 110 : 18 bits/pixel
 */
#define ILI9341_CMD_PIXEL_FORMAT_SET                   0x3A
#define ILI9341_PARAM_1_18_BITS_INTERFACE_PIXEL_FORMAT 0x66

/**
 * @brief This command transfers image data from the host processor to the display module’s frame memory continuing from the
 * pixel location following the previous write_memory_continue or write_memory_start command.
 */
#define ILI9341_CMD_WRITE_MEMORY_CONTINUE 0x3C

/**
 * @brief This command transfers image data from the display module’s frame memory to the host processor continuing from the
 * location following the previous read_memory_continue (3Eh) or read_memory_start (2Eh) command.
 */
#define ILI9341_CMD_READ_MEMORY_CONTINUE 0x3E

/**
 * @brief This command turns on the display Tearing Effect output signal on the TE signal line when the display reaches line STS.
 * The TE signal is not affected by changing set_address_mode bit B4. The Tearing Effect Line On has one parameter that
 * describes the Tearing Effect Output Line mode.
 */
#define ILI9341_CMD_SET_TEAR_SCANLINE 0x44

/**
 * @brief The display returns the current scan line, GTS, used to update the display device. The total number of scan lines on a
 * display device is defined as VSYNC + VBP + VACT + VFP. The first scan line is defined as the first line of V-Sync and is
 * denoted as Line 0.
 * When in Sleep Mode, the value returned by get_scanline is undefined.
 */
#define ILI9341_CMD_GET_SCANLINE 0x45

/**
 * @brief This command is used to adjust the brightness value of the display.
 * It should be checked what is the relationship between this written value and output brightness of the display. This relationship
 * is defined on the display module specification.
 * In principle relationship is that 00h value means the lowest brightness and FFh value means the highest brightness.
 */
#define ILI9341_CMD_WRITE_DISPLAY_BRIGHTNESS 0x51

/**
 * @brief This command returns the brightness value of the display.
 * It should be checked what the relationship between this returned value and output brightness of the display. This
 * relationship is defined on the display module specification.
 * In principle the relationship is that 00h value means the lowest brightness and FFh value means the highest brightness.
 */
#define ILI9341_CMD_READ_DISPLAY_BRIGHTNESS 0x52

/**
 * @brief This command is used to control display brightness.
 */
#define ILI9341_CMD_WRITE_CTRL_DISPLAY 0x53

/**
 * @brief This command is used to return brightness setting.
 */
#define ILI9341_CMD_READ_CTRL_DISPLAY 0x54

/**
 * @brief This command is used to set parameters for image content based adaptive brightness control functionality.
 * There is possible to use 4 different modes for content adaptive image functionality.
 */
#define ILI9341_CMD_WRITE_CONTENT_ADAPTIVE_BRIGHTNESS_CONTROL 0x55

/**
 * @brief This command is used to read the settings for image content based adaptive brightness control functionality.
 * It is possible to use 4 different modes for content adaptive image functionality.
 */
#define ILI9341_CMD_READ_CONTENT_ADAPTIVE_BRIGHTNESS_CONTROL 0x56

/**
 * @brief This command is used to set the minimum brightness value of the display for CABC function.
 * CMB[7:0]: CABC minimum brightness control, this parameter is used to avoid too much brightness reduction.
 * When CABC is active, CABC cannot reduce the display brightness to less than CABC minimum brightness setting. Image
 * processing function is worked as normal, even if the brightness cannot be changed.
 * This function does not affect to the other function, manual brightness setting. Manual brightness can be set the display
 * brightness to less than CABC minimum brightness. Smooth transition and dimming function can be worked as normal.
 * When display brightness is turned off (BCTRL=0 of “Write CTRL Display (53h)”), CABC minimum brightness setting is
 * ignored.
 * In principle relationship is that 00h value means the lowest brightness for CABC and FFh value means the highest
 * brightness for CABC.
 */
#define ILI9341_CMD_WRITE_CABC_MINIMUM_BRIGHTNESS 0x5E

/**
 * @brief This command returns the minimum brightness value of CABC function.
 * In principle the relationship is that 00h value means the lowest brightness and FFh value means the highest brightness.
 * CMB[7:0] is CABC minimum brightness specified with “Write CABC minimum brightness (5Eh)” command. In principle
 * relationship is that 00h value means the lowest brightness for CABC and FFh value means the highest brightness for
 * CABC.
 */
#define ILI9341_CMD_READ_CABC_MINIMUM_BRIGHTNESS 0x5F

/**
 * @brief This read byte identifies the LCD module’s manufacturer ID and it is specified by User.
 */
#define ILI9341_CMD_READ_ID_1 0xDA

/**
 * @brief This read byte is used to track the LCD module/driver version. It is defined by display supplier (with User’s agreement) and
 * changes each time a revision is made to the display, material or construction specifications.
 */
#define ILI9341_CMD_READ_ID_2 0xDB

/**
 * @brief This read byte identifies the LCD module/driver and It is specified by User.
 */
#define ILI9341_CMD_READ_ID_3 0xDC

/**
 * @brief Sets the operation status of the display interface. The setting becomes effective as soon as the command is received.
 */
#define ILI9341_CMD_RGB_INTERFACE_SIGNAL_CONTROL 0xB0

/**
 * @brief
 * PARAM_1
 * bit[1:0] DIVA : division ratio for internal clocks when Normal mode.
 * PARAM_2
 * bit[4:0] RTNA : is used to set 1H (line) period of Normal mode at MCU interface.
 */
#define ILI9341_CMD_FRAME_CONTROL_NORMAL_MODE              0xB1
#define ILI9341_PARAM_1_INTERNAL_CLOCK_DIVISION_RATIO_BITS 0x00
#define ILI9341_PARAM_2_CLOCK_PER_LINE_BITS                0x1B

/**
 * @brief Sets the division ratio for internal clocks of Idle mode at MCU interface.
 */
#define ILI9341_CMD_FRAME_CONTROL_IDLE_MODE 0xB2

/**
 * @brief Sets the division ratio for internal clocks of Partial mode (Idle mode off) at MCU interface.
 */
#define ILI9341_CMD_FRAME_CONTROL_PARTIAL_MODE 0xB3

/**
 * @brief Display inversion mode set
 * NLA: Inversion setting in full colors normal mode (Normal mode on)
 * NLB: Inversion setting in Idle mode (Idle mode on)
 * NLC: Inversion setting in full colors partial mode (Partial mode on / Idle mode off).
 */
#define ILI9341_CMD_DISPLAY_INVERSION_CONTROL 0xB4

/**
 * @brief VFP [6:0] / VBP [6:0]: The VFP [6:0] and VBP [6:0] bits specify the line number of vertical front and back porch period
 * respectively.
 * HFP [4:0] / HBP [4:0]: The HFP [4:0] and HBP [4:0] bits specify the line number of horizontal front and back porch period
 * respectively.
 */
#define ILI9341_CMD_BLANKING_PORCH_CONTROL 0xB5

/**
 * @brief
 * PARAM_1
 * PTG [3:2]: Set the scan mode in non-display area.
 * PT [1:0]: Determine source/VCOM output in a non-display area in the partial display mode.
 * PARAM_2
 * SS [5] : Select the shift direction of outputs from the source driver.
 * REV [7] : Select whether the liquid crystal type is normally white type or normally black type.
 * ISC [3:0] : Specify the scan cycle interval of gate driver in non-display area when PTG [1:0] =”10” to select interval scan.
 * Then scan cycle is set as odd number from 0~29 frame periods. The polarity is inverted every scan cycle.
 * GS [6] : Sets the direction of scan by the gate driver in the range determined by SCN [4:0] and NL [4:0]. The scan direction
 * determined by GS = 0 can be reversed by setting GS = 1.
 * SM: Sets the gate driver pin arrangement in combination with the GS bit to select the optimal scan mode for the module.
 * PARAM_3
 * NL [5:0]: Sets the number of lines to drive the LCD at an interval of 8 lines. The GRAM address mapping is not affected
 * by the number of lines set by NL [5:0]. The number of lines must be the same or more than the number of lines necessary
 * for the size of the liquid crystal panel.
 * PARAM_4
 * PCDIV [5:0] : External fosc = DOTCLK/(2*(PCDIV+1))
*/
#define ILI9341_CMD_DISPLAY_FUNCTION_CONTROL  0xB6
#define ILI9341_PARAM_1_PTG_PT_BITS           0x0A
#define ILI9341_PARAM_2_ISC_SM_SS_GS_REV_BITS 0x82
#define ILI9341_PARAM_3_NL_BITS               0x27
#define ILI9341_PARAM_4_PCDIV_BITS            0x00

/**
 * @brief
 * GAS [0] : Low voltage detection control.
 * 0 : Enable
 * 1 : Disable
 * GON/DTE [2:1] : Set the output level of gate driver G1 ~ G320.
 * 00 : VGH
 * 01 : VGH
 * 10 : VGL
 * 11 : Normal display
 */
#define ILI9341_CMD_ENTRY_MODE_SET       0xB7
#define ILI9341_PARAM_1_GAS_DTE_GON_BITS 0x06

/**
 * @brief TH_UI [3:0]: These bits are used to set the percentage of grayscale data accumulate histogram value in the user interface
 * (UI) mode. This ratio of maximum number of pixels that makes display image white (=data “255”) to the total of
 * pixels by image processing.
 */
#define ILI9341_CMD_BACKLIGHT_CONTROL_1 0xB8

/**
 * @brief TH_ST [3:0]: These bits are used to set the percentage of grayscale data accumulate histogram value in the still picture
 * mode. This ratio of maximum number of pixels that makes display image white (=data “255”) to the total of pixels
 * by image processing.
 * TH_MV [3:0]: These bits are used to set the percentage of grayscale data accumulate histogram value in the moving image
 * mode. This ratio of maximum number of pixels that makes display image white (=data “255”) to the total of pixels
 * by image processing.
 */
#define ILI9341_CMD_BACKLIGHT_CONTROL_2 0xB9

/**
 * @brief DTH_UI [3:0]: This parameter is used set the minimum limitation of grayscale threshold value in User Icon (UI) image mode.
 * This register setting will limit the minimum Dth value to prevent the display image from being too white and
 * the display quality is not acceptable.
 */
#define ILI9341_CMD_BACKLIGHT_CONTROL_3 0xBA

/**
 * @brief DTH_ST [3:0]/DTH_MV [3:0]: This parameter is used set the minimum limitation of grayscale threshold value. This register
 * setting will limit the minimum Dth value to prevent the display image from being too white and the
 * display quality is not acceptable.
 */
#define ILI9341_CMD_BACKLIGHT_CONTROL_4 0xBB

/**
 * @brief DIM1 [2:0]: This parameter is used to set the transition time of brightness level to avoid the sharp brightness transition on
 * vision.
 * DIM2 [3:0]: This parameter is used to set the threshold of brightness change.
 * When the brightness transition difference is smaller than DIM2 [3:0], the brightness transition will be ignored.
 */
#define ILI9341_CMD_BACKLIGHT_CONTROL_5 0xBC

/**
 * @brief PWM_DIV [7:0]: PWM_OUT output frequency control. This command is used to adjust the PWM waveform frequency of
 * PWM_OUT. The PWM frequency can be calculated by using the following equation.
 */
#define ILI9341_CMD_BACKLIGHT_CONTROL_7 0xBE

/**
 * @brief LEDPWMPOL: The bit is used to define polarity of LEDPWM signal.
 * LEDONPOL: This bit is used to control LEDON pin.
 * LEDONR: This bit is used to control LEDON pin.
 */
#define ILI9341_CMD_BACKLIGHT_CONTROL_8 0xBF

/**
 * @brief VRH [5:0]: Set the GVDD level, which is a reference level for the VCOM level and the grayscale voltage level.
 */
#define ILI9341_CMD_POWER_CONTROL_1             0xC0
#define ILI9341_PARAM_1_GVDD_VOLTAGE_LEVEL_BITS 0x21

/**
 * @brief BT [2:0]: Sets the factor used in the step-up circuits.
 * Select the optimal step-up factor for the operating voltage. To reduce power consumption, set a smaller factor.
 */
#define ILI9341_CMD_POWER_CONTROL_2                           0xC1
#define ILI9341_PARAM_1_OPERATING_VOLTAGE_STEP_UP_FACTOR_BITS 0x10

/**
 * @brief
 * PARAM_1
 * bit[6:0] VMH : Set the VCOMH voltage.
 * PARAM_2
 * bit[6:0] VML : Set the VCOML voltage.
 */
#define ILI9341_CMD_VCOM_CONTROL_1         0xC5
#define ILI9341_PARAM_1_VCOMH_VOLTAGE_BITS 0x31
#define ILI9341_PARAM_2_VCOML_VOLTAGE_BITS 0x3C

/**
 * @brief nVM bit[7] : nVM equals to “0” after power on reset and VCOM offset equals to program MTP value. When nVM set to “1”, setting
 * of VMF [6:0] becomes valid and VCOMH/VCOML can be adjusted.
 * VMF [6:0]: Set the VCOM offset voltage.
 */
#define ILI9341_CMD_VCOM_CONTROL_2               0xC7
#define ILI9341_PARAM_1_VCOM_OFFSET_VOLTAGE_BITS 0xC0

/**
 * @brief This command is used to program the NV memory data. After a successful MTP operation, the information of PGM_DATA
 * [7:0] will programmed to NV memory.
 * PGM_ADR [2:0]: The select bits of ID1, ID2, ID3 and VMF [6:0] programming can be OTP x 3 times.
 * PGM_DATA [7:0]: The programmed data.
 */
#define ILI9341_CMD_NV_MEMMORY_WRITE 0xD0

/**
 * @brief KEY [23:0]: NV memory programming protection key. When writing MTP data to D1h, this register must be set to
 * 0x55AA66h to enable MTP programming. If D1h register is not written with 0x55AA66h, then NV memory programming will
 * be aborted.
 */
#define ILI9341_CMD_NV_MEMORY_PROTECTION_KEY 0xD1

/**
 * @brief ID1_CNT [2:0] / ID2_CNT [2:0] / ID3_CNT [2:0] / VMF_CNT [2:0]: ID and VMF all can be OPT x 3 times, NV memory
 * program record. The bits will increase “+1” automatically after writing the PGM_DATA [7:0] to NV memory.
 * BUSY: The status bit of NV memory programming.
 */
#define ILI9341_CMD_NV_MEMORY_STATUS_READ 0xD2

/**
 * @brief Read IC device code.
 */
#define ILI9341_CMD_READ_ID_4 0xD3

/**
 * @brief Set the gray scale voltage to adjust the gamma characteristics of the TFT panel.
 * PARAM_1  VP63 [3:0]
 * PARAM_2  VP62 [5:0]
 * PARAM_3  VP61 [5:0]
 * PARAM_4  VP59 [3:0]
 * PARAM_5  VP57 [4:0]
 * PARAM_6  VP50 [3:0]
 * PARAM_7  VP43 [6:0]
 * PARAM_8  VP36 [3:0]
 *          VP27 [7:4]
 * PARAM_9  VP20 [6:0]
 * PARAM_10 VP13 [3:0]
 * PARAM_11 VP6 [4:0]
 * PARAM_12 VP4 [3:0]
 * PARAM_13 VP2 [5:0]
 * PARAM_14 VP1 [5:0]
 * PARAM_15 VP0 [3:0]
 */
#define ILI9341_CMD_POSITIVE_GAMMA_CORRECTION           0xE0
#define ILI9341_PARAM_1_POSITIVE_GAMMA_CORRECTION_BITS  0x1F
#define ILI9341_PARAM_2_POSITIVE_GAMMA_CORRECTION_BITS  0x1A
#define ILI9341_PARAM_3_POSITIVE_GAMMA_CORRECTION_BITS  0x18
#define ILI9341_PARAM_4_POSITIVE_GAMMA_CORRECTION_BITS  0x0A
#define ILI9341_PARAM_5_POSITIVE_GAMMA_CORRECTION_BITS  0x0F
#define ILI9341_PARAM_6_POSITIVE_GAMMA_CORRECTION_BITS  0x06
#define ILI9341_PARAM_7_POSITIVE_GAMMA_CORRECTION_BITS  0x45
#define ILI9341_PARAM_8_POSITIVE_GAMMA_CORRECTION_BITS  0x87
#define ILI9341_PARAM_9_POSITIVE_GAMMA_CORRECTION_BITS  0x32
#define ILI9341_PARAM_10_POSITIVE_GAMMA_CORRECTION_BITS 0x0A
#define ILI9341_PARAM_11_POSITIVE_GAMMA_CORRECTION_BITS 0x07
#define ILI9341_PARAM_12_POSITIVE_GAMMA_CORRECTION_BITS 0x02
#define ILI9341_PARAM_13_POSITIVE_GAMMA_CORRECTION_BITS 0x07
#define ILI9341_PARAM_14_POSITIVE_GAMMA_CORRECTION_BITS 0x05
#define ILI9341_PARAM_15_POSITIVE_GAMMA_CORRECTION_BITS 0x00
/**
 * @brief Set the gray scale voltage to adjust the gamma characteristics of the TFT panel.
 * PARAM_1  VN63 [3:0]
 * PARAM_2  VN62 [5:0]
 * PARAM_3  VN61 [5:0]
 * PARAM_4  VN59 [3:0]
 * PARAM_5  VN57 [4:0]
 * PARAM_6  VN50 [3:0]
 * PARAM_7  VN43 [6:0]
 * PARAM_8  VN36 [7:4]
 *          VN27 [3:0]
 * PARAM_9  VN20 [6:0]
 * PARAM_10 VN13 [3:0]
 * PARAM_11 VN6 [4:0]
 * PARAM_12 VN4 [3:0]
 * PARAM_13 VN2 [5:0]
 * PARAM_14 VN1 [5:0]
 * PARAM_15 VN0 [3:0]
 */
#define ILI9341_CMD_NEGATIVE_GAMMA_CORRECTION           0xE1
#define ILI9341_PARAM_1_NEGATIVE_GAMMA_CORRECTION_BITS  0x00
#define ILI9341_PARAM_2_NEGATIVE_GAMMA_CORRECTION_BITS  0x25
#define ILI9341_PARAM_3_NEGATIVE_GAMMA_CORRECTION_BITS  0x27
#define ILI9341_PARAM_4_NEGATIVE_GAMMA_CORRECTION_BITS  0x05
#define ILI9341_PARAM_5_NEGATIVE_GAMMA_CORRECTION_BITS  0x10
#define ILI9341_PARAM_6_NEGATIVE_GAMMA_CORRECTION_BITS  0x09
#define ILI9341_PARAM_7_NEGATIVE_GAMMA_CORRECTION_BITS  0x3A
#define ILI9341_PARAM_8_NEGATIVE_GAMMA_CORRECTION_BITS  0x78
#define ILI9341_PARAM_9_NEGATIVE_GAMMA_CORRECTION_BITS  0x4D
#define ILI9341_PARAM_10_NEGATIVE_GAMMA_CORRECTION_BITS 0x05
#define ILI9341_PARAM_11_NEGATIVE_GAMMA_CORRECTION_BITS 0x18
#define ILI9341_PARAM_12_NEGATIVE_GAMMA_CORRECTION_BITS 0x0D
#define ILI9341_PARAM_13_NEGATIVE_GAMMA_CORRECTION_BITS 0x38
#define ILI9341_PARAM_14_NEGATIVE_GAMMA_CORRECTION_BITS 0x3A
#define ILI9341_PARAM_15_NEGATIVE_GAMMA_CORRECTION_BITS 0x1F
/**
 * @brief RCAx [3:0]: Gamma Macro-adjustment registers for red gamma curve.
 * BCAx [3:0]: Gamma Macro-adjustment registers for blue gamma curve.
 */
#define ILI9341_CMD_DIGITAL_GAMMA_CONTROL_1 0xE2

/**
 * @brief RFAx [3:0]: Gamma Micro-adjustment register for red gamma curve.
 * BFAx [3:0]: Gamma Micro-adjustment register for blue gamma curve.
 */
#define ILI9341_CMD_DIGITAL_GAMMA_CONTROL_2 0xE3

/**
 * @brief MY_EOR / MX_EOR / MV_EOR / BGR_EOR:
 * The set value of MADCTL is used in the IC is derived as exclusive OR between 1st Parameter of IFCTL and MADCTL
 * Parameter.
 * MDT [1:0]: Select the method of display data transferring.
 * WEMODE: Memory write control
 * WEMODE=0: When the transfer number of data exceeds (EC-SC+1)*(EP-SP+1), the exceeding data will be ignored.
 * WEMODE=1: When the transfer number of data exceeds (EC-SC+1)*(EP-SP+1), the column and page number will be
 * reset, and the exceeding data will be written into the following column and page.
 * ENDIAN: Select Little Endian Interface bit. At Little Endian mode, the host sends LSB data first.
 * DM [1:0]: Select the display operation mode.
 * RM: Select the interface to access the GRAM.
 * RIM: Specify the RGB interface mode when the RGB interface is used. These bits should be set before display operation
 * through the RGB interface and should not be set during operation.
 * EPF [1:0]: 65K color mode data format.
 */
#define ILI9341_CMD_INTERFACE_CONTROL 0xF6

/**
 * @brief Extended Register commands
 */

/**
 * @brief
 * PARAM_1, PARAM_2, PARAM_3 No settable bits
 * PARAM_4 vcore controle
 * bit[2:0] REG_VD
 * 000: 1.55v
 * 001: 1.4v
 * 010: 1.5v
 * 011: 1.65v
 * 100: 1.6v
 * 101: 1.7v
 * 110: reserved
 * 111: reserved
 * PARAM_5 ddvdh controle
 * bit[2:0] VBC
 * 000: 5.8v
 * 001: 5.7v
 * 010: 5.6v
 * 011: 5.5v
 * 100: 5.4v
 * 101: 5.3v
 * 110: 5.2v
 * 111: reserved
 */
#define ILI9341_CMD_POWER_CONTROL_A          0xCB
#define ILI9341_PARAM_1_POWER_CONTROL_A_BITS 0x39
#define ILI9341_PARAM_2_POWER_CONTROL_A_BITS 0x2C
#define ILI9341_PARAM_3_POWER_CONTROL_A_BITS 0x00
#define ILI9341_PARAM_4_VCORE_CONTROL_BITS   0x34
#define ILI9341_PARAM_5_DDVDH_CONTROL_BITS   0x02

/**
 * @brief power control B
 * PARAM_1
 * No settable bits.
 * PARAM_2
 * power control[1:0]
 * bit[5]: DRV_ena : For VCOM driving ability enhancement, DRV_ena = 1: Enable, and vice versa
 * bit[6]: PCEQ: PC and EQ operation for power saving
 * PARAM_3
 * bit[2:0]: DRV_vmh[2:0] 3’b000 adjust over drive width for VMH(000: 1 op_clk ~111: 8 op_clk)
 * bit[3]: DRV_vml[0] 1’b0
 * bit[4]: DC_ena: Discharge path enable. Enable high for ESD protection, 1: enable and vice versa
 * bit[7:6] : DRV_vml[2:1] 2’b00
 */
#define ILI9341_CMD_POWER_CONTROL_B          0xCF
#define ILI9341_PARAM_1_POWER_CONTROL_B_BITS 0x00
#define ILI9341_PARAM_2_POWER_CONTROL_B_BITS 0x81
#define ILI9341_PARAM_3_POWER_CONTROL_B_BITS 0x30
/**
 * @brief EQ timing for Internal clock
 * PARAM_1 gate driver non-overlap timing control
 * bit[0] NOW
 * 0:default non-overlap time
 * 1:default + 1unit
 * PARAM_2
 * bit[4] EQ timing control
 * 0:default – 1unit
 * 1:default EQ timing
 * bit[0] CR timing control
 * 0: default – 1unit
 * 1:default CR timing
 * PARAM_3 pre-charge timing control
 * bit[1:0] PC
 * 00:default – 2unit
 * 01:default – 1unit
 * 10: default pre-charge timing
 * 11: reserved
 */
#define ILI9341_CMD_DRIVER_TIMING_CONTROL_A            0xE8
#define ILI9341_PARAM_1_GATE_DRIVER_NON_OVERLAP_BITS   0x84
#define ILI9341_PARAM_2_EQ_CR_TIMING_CONTROL_BITS      0x11
#define ILI9341_PARAM_3_PRE_CHARGE_TIMING_CONTROL_BITS 0x7A

/**
 * @brief timing for External clock
 */
#define ILI9341_CMD_EXT_DRIVER_TIMING_CONTROL_A 0xE9

/**
 * @brief gate driver timing control
 * PARAM_1
 * bit[1:0] VG_SW_T1 : EQ to GND
 * bit[3:2] VG_SW_T2 : EQ to DDVDH
 * bit[5:4] VG_SW_T3 : EQ to DDVDH
 * bit[7:6] VG_SW_T4 : EQ to GND
 * 00: 0 unit
 * 01: 1 unit
 * 10: 2 unit
 * 11: 3 unit
 * PARAM_2 No settable bits
 */
#define ILI9341_CMD_DRIVER_TIMING_CONTROL_B               0xEA
#define ILI9341_PARAM_1_GATE_DRIVER_TIMING_CONTROL_B_BITS 0x66
#define ILI9341_PARAM_2_DRIVER_TIMING_CONTROL_B_BITS      0x00

/**
 * @brief power on sequence control
 * PARAM_1 soft start control
 * 00:soft start keep 3 frame
 * 01:soft start keep 2 frame
 * 10:soft start keep 1 frame
 * 11:disable
 * PARAM_2 and PARAM_3
 * 00:1st frame enable
 * 01:2nd frame enable
 * 10:3rd frame enable
 * 11:4th frame enable
 * PARAM_4 DDVDH enhance mode(only for 8 external capacitors)
 * 0: disable
 * 1: enable
 */
#define ILI9341_CMD_POWER_ON_SEQUENCE_CONTROL          0xED
#define ILI9341_PARAM_1_SOFT_START_CONTROL_BITS        0x55
#define ILI9341_PARAM_2_DDVDH_VCL_ENABLE_BITS          0x01
#define ILI9341_PARAM_3_VGL_VGH_ENABLE_BITS            0x23
#define ILI9341_PARAM_4_DDVDH_ENHANCE_MODE_ENABLE_BITS 0x01

/**
 * @brief Enable 3 gamma control
 * 3G_enb [0]
 * 0 : disable
 * 1 : enable
 */
#define ILI9341_CMD_ENABLE_3G                    0xF2
#define ILI9341_PARAM_1_GAMA_CONTROL_ENABLE_BITS 0x02

/**
 * @brief ratio control
 * bit[5:4] Ratio
 * 00:reserved
 * 01:reserved
 * 10:DDVDH=2xVCI
 * 11:DDVDH=3xVCI
 */
#define ILI9341_CMD_PUMP_RATIO_CONTROL          0xF7
#define ILI9341_PARAM_1_PUMP_RATIO_CONTROL_BITS 0x10

/*! @} */ // ILI9341
/*! @} */ // ILI9341
/*! @} */ // mwgroup

#endif // _ILI9341_CMD_H_
// ------------------------------------------------------------------------- END
