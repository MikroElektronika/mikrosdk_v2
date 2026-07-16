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
 * @file  st7789_cmd.h
 * @brief ST7789 Display Controller Commands.
 */

/*!
 * @addtogroup middlewaregroup Middleware
 * @{
 */

/*!
 * @addtogroup st7789 ST7789 Display Controller Driver
 * @{
 */

/*!
 * @addtogroup st7789_commands ST7789 Display Controller Commands
 * @brief ST7789 Display Controller Command List
 * @{
 */

#ifndef ST7789_CMD_H
#define ST7789_CMD_H

/**
 * @brief No operation.
 */
#define ST7789_CMD_NOP                     0x00

/**
 * @brief Software reset.
 */
#define ST7789_CMD_SWRESET                 0x01

/**
 * @brief Read display ID.
 */
#define ST7789_CMD_RDDID                   0x04

/**
 * @brief Read display status.
 */
#define ST7789_CMD_RDDST                   0x09

/**
 * @brief Read display power mode.
 */
#define ST7789_CMD_RDDPM                   0x0A

/**
 * @brief Read display MADCTL (Memory Data Access Control) setting.
 */
#define ST7789_CMD_RDDMADCTL               0x0B

/**
 * @brief Read display COLMOD (Interface Pixel Format) setting.
 */
#define ST7789_CMD_RDDCOLMOD               0x0C

/**
 * @brief Read display image mode.
 */
#define ST7789_CMD_RDDIM                   0x0D

/**
 * @brief Read display signal mode.
 */
#define ST7789_CMD_RDDSM                   0x0E

/**
 * @brief Read display self-diagnostic result.
 */
#define ST7789_CMD_RDDSDR                  0x0F

/**
 * @brief Enter sleep mode.
 */
#define ST7789_CMD_SLPIN                   0x10

/**
 * @brief Exit sleep mode.
 */
#define ST7789_CMD_SLPOUT                  0x11

/**
 * @brief Turn on partial display mode.
 */
#define ST7789_CMD_PTLON                   0x12

/**
 * @brief Turn on normal display mode.
 */
#define ST7789_CMD_NORON                   0x13

/**
 * @brief Turn off display inversion.
 */
#define ST7789_CMD_INVOFF                  0x20

/**
 * @brief Turn on display inversion.
 */
#define ST7789_CMD_INVON                   0x21

/**
 * @brief Select default gamma curve.
 */
#define ST7789_CMD_GAMSET                  0x26

/**
 * @brief Turn off the main display.
 */
#define ST7789_CMD_DISPOFF                 0x28

/**
 * @brief Turn on the main display.
 */
#define ST7789_CMD_DISPON                  0x29

/**
 * @brief Set column address area.
 */
#define ST7789_CMD_CASET                   0x2A

/**
 * @brief Set row address area.
 */
#define ST7789_CMD_RASET                   0x2B

/**
 * @brief Write data to display frame memory.
 */
#define ST7789_CMD_RAMWR                   0x2C

/**
 * @brief Read data from display frame memory.
 */
#define ST7789_CMD_RAMRD                   0x2E

/**
 * @brief Define partial display area sizes.
 */
#define ST7789_CMD_PTLAR                   0x30

/**
 * @brief Vertical scrolling definition.
 */
#define ST7789_CMD_VSCRDEF                 0x33

/**
 * @brief Turn off tearing effect output line.
 */
#define ST7789_CMD_TEOFF                   0x34

/**
 * @brief Turn on tearing effect output line.
 */
#define ST7789_CMD_TEON                    0x35

/**
 * @brief Memory data access control (rotation, RGB/BGR order).
 */
#define ST7789_CMD_MADCTL                  0x36

/**
 * @brief Set vertical scrolling start address.
 */
#define ST7789_CMD_VSCRSADD                0x37

/**
 * @brief Turn off idle mode.
 */
#define ST7789_CMD_IDMOFF                  0x38

/**
 * @brief Turn on idle mode (reduced color depth mode).
 */
#define ST7789_CMD_IDMON                   0x39

/**
 * @brief Interface pixel format setting (color depth selection).
 */
#define ST7789_CMD_COLMOD                  0x3A

/**
 * @brief Continue writing data to frame memory from current address.
 */
#define ST7789_CMD_RAMWRC                  0x3C

/**
 * @brief Continue reading data from frame memory from current address.
 */
#define ST7789_CMD_RAMRDC                  0x3E

/**
 * @brief Set tearing effect scanline value.
 */
#define ST7789_CMD_TESCAN                  0x44

/**
 * @brief Read tearing effect scanline value.
 */
#define ST7789_CMD_RDTESCAN                0x45

/**
 * @brief Write display brightness value.
 */
#define ST7789_CMD_WRDISBV                 0x51

/**
 * @brief Read display brightness value.
 */
#define ST7789_CMD_RDDISBV                 0x52

/**
 * @brief Write display control register.
 */
#define ST7789_CMD_WRCTRLD                 0x53

/**
 * @brief Read display control register.
 */
#define ST7789_CMD_RDCTRLD                 0x54

/**
 * @brief Write content adaptive brightness control (CABC) setting.
 */
#define ST7789_CMD_WRCACE                  0x55

/**
 * @brief Read content adaptive brightness control (CABC) setting.
 */
#define ST7789_CMD_RDCABC                  0x56

/**
 * @brief Write minimum brightness for CABC.
 */
#define ST7789_CMD_WRCABCMB                0x5E

/**
 * @brief Read minimum brightness for CABC.
 */
#define ST7789_CMD_RDCABCMB                0x5F

/**
 * @brief Read automatic brightness control self-diagnostic result.
 */
#define ST7789_CMD_RDABCSDR                0x68

/**
 * @brief Read display ID1.
 */
#define ST7789_CMD_RDID1                   0xDA

/**
 * @brief Read display ID2.
 */
#define ST7789_CMD_RDID2                   0xDB

/**
 * @brief Read display ID3.
 */
#define ST7789_CMD_RDID3                   0xDC

/**
 * @brief RAM control.
 */
#define ST7789_CMD_RAMCTRL                 0xB0

/**
 * @brief RGB control.
 */
#define ST7789_CMD_RGBCTRL                 0xB1

/**
 * @brief Porch control. 
 */
#define ST7789_CMD_PORCTRL                 0xB2

/**
 * @brief Frame Rate control.
 */
#define ST7789_CMD_FRCTRL1                 0xB3

/**
 * @brief Partial control. 
 */
#define ST7789_CMD_PARCTRL                 0xB5

/**
 * @brief Gate control setting.
 */
#define ST7789_CMD_GCTRL                   0xB7

/**
 * @brief Gate on timing adjustment.
 */
#define ST7789_CMD_GTADJ                   0xB8

/**
 * @brief Digital gamma enable.
 */
#define ST7789_CMD_DGMEN                   0xBA

/**
 * @brief VCOM voltage setting.
 */
#define ST7789_CMD_VCOMS                   0xBB

/**
 * @brief Power saving mode setting.
 */
#define ST7789_CMD_POWSAVE                 0xBC

/**
 * @brief Display off power saving.
 */
#define ST7789_CMD_DLPOFFSAVE              0xBD

/**
 * @brief LCM control setting.
 */
#define ST7789_CMD_LCMCTRL                 0xC0

/**
 * @brief ID code setting.
 */
#define ST7789_CMD_IDSET                   0xC1

/**
 * @brief VDV and VRH command enable.
 */
#define ST7789_CMD_VDVVRHEN                0xC2

/**
 * @brief VRH set (VAP/VAN voltage control).
 */
#define ST7789_CMD_VRHS                    0xC3

/**
 * @brief VDV set (VCOM alternating voltage control).
 */
#define ST7789_CMD_VDVSET                  0xC4

/**
 * @brief VCOM offset voltage setting.
 */
#define ST7789_CMD_VCMOFSET                0xC5

/**
 * @brief Frame rate control in normal mode 2.
 */
#define ST7789_CMD_FRCTR2                  0xC6

/**
 * @brief CABC (Content Adaptive Brightness Control) control.
 */
#define ST7789_CMD_CABCCTRL                0xC7

/**
 * @brief Register selection 1.
 */
#define ST7789_CMD_REGSEL1                 0xC8

/**
 * @brief Register selection 2.
 */
#define ST7789_CMD_REGSEL2                 0xCA

/**
 * @brief PWM frame rate selection.
 */
#define ST7789_CMD_PWMFRSEL                0xCC

/**
 * @brief Power control 1.
 */
#define ST7789_CMD_PWCTRL1                 0xD0

/**
 * @brief VAP/VAN enable.
 */
#define ST7789_CMD_VAPVANEN                0xD2

/**
 * @brief Command 2 enable part 0.
 */
#define ST7789_CMD_CMD2EN0                 0xDF

/**
 * @brief Command 2 enable part 1.
 */
#define ST7789_CMD_CMD2EN1                 0x5A

/**
 * @brief Command 2 enable part 2.
 */
#define ST7789_CMD_CMD2EN2                 0x69

/**
 * @brief Command 2 enable part 3.
 */
#define ST7789_CMD_CMD2EN3                 0x02

/**
 * @brief Positive voltage gamma control.
 */
#define ST7789_CMD_PVGAMCTRL               0xE0

/**
 * @brief Negative voltage gamma control.
 */
#define ST7789_CMD_NVGAMCTRL               0xE1

/**
 * @brief Digital gamma look-up table for Red.
 */
#define ST7789_CMD_DGMLUTR                 0xE2

/**
 * @brief Digital gamma look-up table for Blue.
 */
#define ST7789_CMD_DGMLUTB                 0xE3

/**
 * @brief Gate drive signal control.
 */
#define ST7789_CMD_GATECTRL                0xE4

/**
 * @brief SPI2 enable.
 */
#define ST7789_CMD_SPI2EN                  0xE7

/**
 * @brief Power control 2.
 */
#define ST7789_CMD_PWCTRL2                 0xE8

/**
 * @brief Equalization control.
 */
#define ST7789_CMD_EQCTRL                  0xE9

/**
 * @brief PROM control.
 */
#define ST7789_CMD_PROMCTRL                0xEC

/**
 * @brief PROM enable.
 */
#define ST7789_CMD_PROMEN                  0xFA

/**
 * @brief NVM (Non-Volatile Memory) setting.
 */
#define ST7789_CMD_NVMSET                  0xFC

/**
 * @brief PROM action.
 */
#define ST7789_CMD_PROMACT                 0xFE



//--------------------------------------------------------------------

/**
 * @defgroup ST7789_set IPS Display 2 Registers Settings
 * @brief Settings for registers of IPS Display 2 Click driver.
 */

/**
 * @addtogroup ST7789_set
 * @{
 */

/**
 * @brief IPS Display 2 MADCTL command setting.
 * @details Specified setting for MADCTL command of IPS Display 2 Click driver.
 */
#define ST7789_MADCTL_DEFAULT              0x00
#define ST7789_MADCTL_MY                   0x80
#define ST7789_MADCTL_MX                   0x40
#define ST7789_MADCTL_MV                   0x20
#define ST7789_MADCTL_ML                   0x10
#define ST7789_MADCTL_RGB                  0x08
#define ST7789_MADCTL_MH                   0x04

/**
 * @brief IPS Display 2 COLMOD command setting.
 * @details Specified setting for COLMOD command of IPS Display 2 Click driver.
 */
#define ST7789_COLMOD_RGB_65K              0x50
#define ST7789_COLMOD_RGB_262K             0x60
#define ST7789_COLMOD_RGB_MASK             0x70
#define ST7789_COLMOD_CTRL_12BIT_PIXEL     0x03
#define ST7789_COLMOD_CTRL_16BIT_PIXEL     0x05
#define ST7789_COLMOD_CTRL_18BIT_PIXEL     0x06
#define ST7789_COLMOD_CTRL_16M_TRUNCATED   0x07
#define ST7789_COLMOD_CTRL_MASK            0x07

/**
 * @brief IPS Display 2 PORCTRL command setting.
 * @details Specified setting for PORCTRL command of IPS Display 2 Click driver.
 */
#define ST7789_PORCTRL_0_BPA_DEFAULT       0x0C
#define ST7789_PORCTRL_0_BPA_MASK          0x7F
#define ST7789_PORCTRL_1_FPA_DEFAULT       0x0C
#define ST7789_PORCTRL_1_FPA_MASK          0x7F
#define ST7789_PORCTRL_2_PSEN_DISABLE      0x00
#define ST7789_PORCTRL_2_PSEN_ENABLE       0x01
#define ST7789_PORCTRL_3_BPB_DEFAULT       0x30
#define ST7789_PORCTRL_3_BPB_MASK          0xF0
#define ST7789_PORCTRL_3_FPB_DEFAULT       0x03
#define ST7789_PORCTRL_3_FPB_MASK          0x0F
#define ST7789_PORCTRL_4_BPC_DEFAULT       0x30
#define ST7789_PORCTRL_4_BPC_MASK          0xF0
#define ST7789_PORCTRL_4_FPC_DEFAULT       0x03
#define ST7789_PORCTRL_4_FPC_MASK          0x0F

/**
 * @brief IPS Display 2 GCTRL command setting.
 * @details Specified setting for GCTRL command of IPS Display 2 Click driver.
 */
#define ST7789_GCTRL_VGHS_DEFAULT          0x30
#define ST7789_GCTRL_VGHS_MASK             0x70
#define ST7789_GCTRL_VGLS_DEFAULT          0x05
#define ST7789_GCTRL_VGLS_MASK             0x07

/**
 * @brief IPS Display 2 VCOMS command setting.
 * @details Specified setting for VCOMS command of IPS Display 2 Click driver.
 */
#define ST7789_VCOMS_VCOM_DEFAULT          0x3A
#define ST7789_VCOMS_VCOM_MASK             0x3F

/**
 * @brief IPS Display 2 LCMCTRL command setting.
 * @details Specified setting for LCMCTRL command of IPS Display 2 Click driver.
 */
#define ST7789_LCMCTRL_XMY                 0x40
#define ST7789_LCMCTRL_XBGR                0x20
#define ST7789_LCMCTRL_XINV                0x10
#define ST7789_LCMCTRL_XMX                 0x08
#define ST7789_LCMCTRL_XMH                 0x04
#define ST7789_LCMCTRL_XMV                 0x02
#define ST7789_LCMCTRL_XGS                 0x01

/**
 * @brief IPS Display 2 VDVVRHEN command setting.
 * @details Specified setting for VDVVRHEN command of IPS Display 2 Click driver.
 */
#define ST7789_VDVVRHEN_CMDEN_DISABLE      0x00
#define ST7789_VDVVRHEN_CMDEN_ENABLE       0x01

/**
 * @brief IPS Display 2 VRHS command setting.
 * @details Specified setting for VRHS command of IPS Display 2 Click driver.
 */
#define ST7789_VRHS_DEFAULT                0x19
#define ST7789_VRHS_MASK                   0x3F

/**
 * @brief IPS Display 2 VDVSET command setting.
 * @details Specified setting for VDVSET command of IPS Display 2 Click driver.
 */
#define ST7789_VDVSET_DEFAULT              0x20
#define ST7789_VDVSET_MASK                 0x3F

/**
 * @brief IPS Display 2 FRCTR2 command setting.
 * @details Specified setting for FRCTR2 command of IPS Display 2 Click driver.
 */
#define ST7789_FRCTR2_NLA_DEFAULT          0x00
#define ST7789_FRCTR2_NLA_MASK             0xE0
#define ST7789_FRCTR2_RTNA_DEFAULT         0x0F
#define ST7789_FRCTR2_RTNA_MASK            0x1F

/**
 * @brief IPS Display 2 PWCTRL1 command setting.
 * @details Specified setting for PWCTRL1 command of IPS Display 2 Click driver.
 */
#define ST7789_PWCTRL1_0_DEFAULT           0xA4
#define ST7789_PWCTRL1_1_AVDD_DEFAULT      0x80
#define ST7789_PWCTRL1_1_AVDD_MASK         0xC0
#define ST7789_PWCTRL1_1_AVCL_DEFAULT      0x20
#define ST7789_PWCTRL1_1_AVCL_MASK         0x30
#define ST7789_PWCTRL1_1_VDS_DEFAULT       0x01
#define ST7789_PWCTRL1_1_VDS_MASK          0x03

/**
 * @brief IPS Display 2 PVGAMCTRL command setting.
 * @details Specified setting for PVGAMCTRL command of IPS Display 2 Click driver.
 */
#define ST7789_PVGAMCTRL_0_V63P_DEFAULT    0xD0
#define ST7789_PVGAMCTRL_0_V63P_MASK       0xF0
#define ST7789_PVGAMCTRL_0_V0P_DEFAULT     0x00
#define ST7789_PVGAMCTRL_0_V0P_MASK        0x0F
#define ST7789_PVGAMCTRL_1_V1P_DEFAULT     0x08
#define ST7789_PVGAMCTRL_1_V1P_MASK        0x3F
#define ST7789_PVGAMCTRL_2_V2P_DEFAULT     0x0E
#define ST7789_PVGAMCTRL_2_V2P_MASK        0x3F
#define ST7789_PVGAMCTRL_3_V4P_DEFAULT     0x09
#define ST7789_PVGAMCTRL_3_V4P_MASK        0x1F
#define ST7789_PVGAMCTRL_4_V6P_DEFAULT     0x09
#define ST7789_PVGAMCTRL_4_V6P_MASK        0x1F
#define ST7789_PVGAMCTRL_5_J0P_DEFAULT     0x00
#define ST7789_PVGAMCTRL_5_J0P_MASK        0x30
#define ST7789_PVGAMCTRL_5_J13P_DEFAULT    0x05
#define ST7789_PVGAMCTRL_5_J13P_MASK       0x0F
#define ST7789_PVGAMCTRL_6_V20P_DEFAULT    0x31
#define ST7789_PVGAMCTRL_6_V20P_MASK       0x7F
#define ST7789_PVGAMCTRL_7_V36P_DEFAULT    0x30
#define ST7789_PVGAMCTRL_7_V36P_MASK       0x70
#define ST7789_PVGAMCTRL_7_V27P_DEFAULT    0x03
#define ST7789_PVGAMCTRL_7_V27P_MASK       0x07
#define ST7789_PVGAMCTRL_8_V43P_DEFAULT    0x48
#define ST7789_PVGAMCTRL_8_V43P_MASK       0x7F
#define ST7789_PVGAMCTRL_9_J1P_DEFAULT     0x10
#define ST7789_PVGAMCTRL_9_11P_MASK        0x30
#define ST7789_PVGAMCTRL_9_V50P_DEFAULT    0x07
#define ST7789_PVGAMCTRL_9_V50P_MASK       0x0F
#define ST7789_PVGAMCTRL_10_V57P_DEFAULT   0x14
#define ST7789_PVGAMCTRL_10_V57P_MASK      0x1F
#define ST7789_PVGAMCTRL_11_V59P_DEFAULT   0x15
#define ST7789_PVGAMCTRL_11_V59P_MASK      0x1F
#define ST7789_PVGAMCTRL_12_V61P_DEFAULT   0x31
#define ST7789_PVGAMCTRL_12_V61P_MASK      0x3F
#define ST7789_PVGAMCTRL_13_V62P_DEFAULT   0x34
#define ST7789_PVGAMCTRL_13_V62P_MASK      0x3F

/**
 * @brief IPS Display 2 NVGAMCTRL command setting.
 * @details Specified setting for NVGAMCTRL command of IPS Display 2 Click driver.
 */
#define ST7789_NVGAMCTRL_0_V63N_DEFAULT    0xD0
#define ST7789_NVGAMCTRL_0_V63N_MASK       0xF0
#define ST7789_NVGAMCTRL_0_V0N_DEFAULT     0x00
#define ST7789_NVGAMCTRL_0_V0N_MASK        0x0F
#define ST7789_NVGAMCTRL_1_V1N_DEFAULT     0x08
#define ST7789_NVGAMCTRL_1_V1N_MASK        0x3F
#define ST7789_NVGAMCTRL_2_V2N_DEFAULT     0x0E
#define ST7789_NVGAMCTRL_2_V2N_MASK        0x3F
#define ST7789_NVGAMCTRL_3_V4N_DEFAULT     0x09
#define ST7789_NVGAMCTRL_3_V4N_MASK        0x1F
#define ST7789_NVGAMCTRL_4_V6N_DEFAULT     0x09
#define ST7789_NVGAMCTRL_4_V6N_MASK        0x1F
#define ST7789_NVGAMCTRL_5_J0N_DEFAULT     0x10
#define ST7789_NVGAMCTRL_5_J0N_MASK        0x30
#define ST7789_NVGAMCTRL_5_J13N_DEFAULT    0x05
#define ST7789_NVGAMCTRL_5_J13N_MASK       0x0F
#define ST7789_NVGAMCTRL_6_V20N_DEFAULT    0x31
#define ST7789_NVGAMCTRL_6_V20N_MASK       0x7F
#define ST7789_NVGAMCTRL_7_V36N_DEFAULT    0x30
#define ST7789_NVGAMCTRL_7_V36N_MASK       0x70
#define ST7789_NVGAMCTRL_7_V27N_DEFAULT    0x03
#define ST7789_NVGAMCTRL_7_V27N_MASK       0x07
#define ST7789_NVGAMCTRL_8_V43N_DEFAULT    0x48
#define ST7789_NVGAMCTRL_8_V43N_MASK       0x7F
#define ST7789_NVGAMCTRL_9_J1N_DEFAULT     0x10
#define ST7789_NVGAMCTRL_9_11N_MASK        0x30
#define ST7789_NVGAMCTRL_9_V50N_DEFAULT    0x07
#define ST7789_NVGAMCTRL_9_V50N_MASK       0x0F
#define ST7789_NVGAMCTRL_10_V57N_DEFAULT   0x14
#define ST7789_NVGAMCTRL_10_V57N_MASK      0x1F
#define ST7789_NVGAMCTRL_11_V59N_DEFAULT   0x15
#define ST7789_NVGAMCTRL_11_V59N_MASK      0x1F
#define ST7789_NVGAMCTRL_12_V61N_DEFAULT   0x31
#define ST7789_NVGAMCTRL_12_V61N_MASK      0x3F
#define ST7789_NVGAMCTRL_13_V62N_DEFAULT   0x34
#define ST7789_NVGAMCTRL_13_V62N_MASK      0x3F

/*! @} */ // st7789
/*! @} */ // st7789
/*! @} */ // mwgroup

#endif // ST7789_CMD_H
// ------------------------------------------------------------------------- END
