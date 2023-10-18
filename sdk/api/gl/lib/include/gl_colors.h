/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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

/**
 * \file gl_colors.h
 * \brief Definition of colors. Here predefined colors can be found.
 */
#ifndef _GL_COLORS_H_
#define _GL_COLORS_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 *  This type is used for color representation.
 */
typedef uint16_t gl_color_t;

/**
 *  Macro used for making specific color out of hex.
 */
#define GL_HEX2COLOR( hex ) ((gl_color_t)((((hex) & 0xF80000)>>8) | (((hex) & 0x00FC00)>>5) | (((hex) & 0x0000F8)>>3)))

/**
 *  Macro used for making color out of RGB values.
 */
#define GL_RGB2COLOR( r, g, b ) (gl_color_t) ((((gl_color_t)r >> 3) << 11) | (((gl_color_t)g >> 2) << 5) | ((gl_color_t)b >> 3))

/**
 *  Macro for getting value for red color from RGB out of given @ref gl_color_t.
 */
#define GL_RED_OF( c ) (((gl_color_t)c >> 11) << 3)

/**
 *  Macro for getting value for green color from RGB out of given @ref gl_color_t.
 */
#define GL_GREEN_OF( c ) (((gl_color_t)c >> 5) << 2)

/**
 *  Macro for getting value for blue color from RGB out of given @ref gl_color_t.
 */
#define GL_BLUE_OF( c ) ((gl_color_t)c << 3)

/**
 *  Macro for getting brightness of the given color.
 */
#define GL_LUMA_OF( c ) ((GL_RED_OF(c)+((gl_color_t)GL_GREEN_OF(c)<<1)+GL_BLUE_OF(c))>>2)

/**
 * \details Graphic Library color palette. Name of color corespond to the standard name which can be found at <a href="https://www.w3schools.com/colors/colors_hex.asp">lw3school</a>.
 */
enum gl_palette
{
    GL_ALICE_BLUE = GL_HEX2COLOR(0xF0F8FF),                              /**< ALICE_BLUE color. */
    GL_ANTIQUE_WHITE = GL_HEX2COLOR(0xFAEBD7),                           /**< ANTIQUE_WHITE color. */
    GL_AQUA = GL_HEX2COLOR(0x00FFFF),                                    /**< AQUA color. */
    GL_AQUAMARINE = GL_HEX2COLOR(0x7FFFD4),                              /**< AQUAMARINE color. */
    GL_AZURE = GL_HEX2COLOR(0xF0FFFF),                                   /**< AZURE color. */
    GL_BEIGE = GL_HEX2COLOR(0xF5F5DC),                                   /**< BEIGE color. */
    GL_BISQUE = GL_HEX2COLOR(0xFFE4C4),                                  /**< BISQUE color. */
    GL_BLACK = GL_HEX2COLOR(0x000000),                                   /**< BLACK color. */
    GL_BLANCHED_ALMOND = GL_HEX2COLOR(0xFFEBCD),                         /**< BLANCHED_ALMOND color. */
    GL_BLUE = GL_HEX2COLOR(0x0000FF),                                    /**< BLUE color. */
    GL_BLUE_VIOLET = GL_HEX2COLOR(0x8A2BE2),                             /**< BLUE_VIOLET color. */
    GL_BROWN = GL_HEX2COLOR(0xA52A2A),                                   /**< BROWN color. */
    GL_BURLY_WOOD = GL_HEX2COLOR(0xDEB887),                              /**< BURLY_WOOD color. */
    GL_CADET_BLUE = GL_HEX2COLOR(0x5F9EA0),                              /**< CADET_BLUE color. */
    GL_CHARTREUSE = GL_HEX2COLOR(0x7FFF00),                              /**< CHARTREUSE color. */
    GL_CHOCOLATE = GL_HEX2COLOR(0xD2691E),                               /**< CHOCOLATE color. */
    GL_CORAL = GL_HEX2COLOR(0xFF7F50),                                   /**< CORAL color. */
    GL_CORNFLOWER_BLUE = GL_HEX2COLOR(0x6495ED),                         /**< CORNFLOWER_BLUE color. */
    GL_CORNSILK = GL_HEX2COLOR(0xFFF8DC),                                /**< CORNSILK color. */
    GL_CRIMSON = GL_HEX2COLOR(0xDC143C),                                 /**< CRIMSON color. */
    GL_CYAN = GL_HEX2COLOR(0x00FFFF),                                    /**< CYAN color. */
    GL_DARK_BLUE = GL_HEX2COLOR(0x00008B),                               /**< DARK_BLUE color. */
    GL_DARK_CYAN = GL_HEX2COLOR(0x008B8B),                               /**< DARK_CYAN color. */
    GL_DARK_GOLDEN_ROD = GL_HEX2COLOR(0xB8860B),                         /**< DARK_GOLDEN_ROD color. */
    GL_DARK_GRAY = GL_HEX2COLOR(0xA9A9A9),                               /**< DARK_GRAY color. */
    GL_DARK_GREY = GL_HEX2COLOR(0xA9A9A9),                               /**< DARK_GREY color. */
    GL_DARK_GREEN = GL_HEX2COLOR(0x006400),                              /**< DARK_GREEN color. */
    GL_DARK_KHAKI = GL_HEX2COLOR(0xBDB76B),                              /**< DARK_KHAKI color. */
    GL_DARK_MAGENTA = GL_HEX2COLOR(0x8B008B),                            /**< DARK_MAGENTA color. */
    GL_DARK_OLIVE_GREEN = GL_HEX2COLOR(0x556B2F),                        /**< DARK_OLIVE_GREEN color. */
    GL_DARK_ORANGE = GL_HEX2COLOR(0xFF8C00),                             /**< DARK_ORANGE color. */
    GL_DARK_ORCHID = GL_HEX2COLOR(0x9932CC),                             /**< DARK_ORCHID color. */
    GL_DARK_RED = GL_HEX2COLOR(0x8B0000),                                /**< DARK_RED color. */
    GL_DARK_SALMON = GL_HEX2COLOR(0xE9967A),                             /**< DARK_SALMON color. */
    GL_DARK_SEA_GREEN = GL_HEX2COLOR(0x8FBC8F),                          /**< DARK_SEA_GREEN color. */
    GL_DARK_SLATE_BLUE = GL_HEX2COLOR(0x483D8B),                         /**< DARK_SLATE_BLUE color. */
    GL_DARK_SLATE_GRAY = GL_HEX2COLOR(0x2F4F4F),                         /**< DARK_SLATE_GRAY color. */
    GL_DARK_SLATE_GREY = GL_HEX2COLOR(0x2F4F4F),                         /**< DARK_SLATE_GREY color. */
    GL_DARK_TURQUOISE = GL_HEX2COLOR(0x00CED1),                          /**< DARK_TURQUOISE color. */
    GL_DARK_VIOLET = GL_HEX2COLOR(0x9400D3),                             /**< DARK_VIOLET color. */
    GL_DEEP_PINK = GL_HEX2COLOR(0xFF1493),                               /**< DEEP_PINK color. */
    GL_DEEP_SKY_BLUE = GL_HEX2COLOR(0x00BFFF),                           /**< DEEP_SKY_BLUE color. */
    GL_DIM_GRAY = GL_HEX2COLOR(0x696969),                                /**< DIM_GRAY color. */
    GL_DIM_GREY = GL_HEX2COLOR(0x696969),                                /**< DIM_GREY color. */
    GL_DODGER_BLUE = GL_HEX2COLOR(0x1E90FF),                             /**< DODGER_BLUE color. */
    GL_FIRE_BRICK = GL_HEX2COLOR(0xB22222),                              /**< FIRE_BRICK color. */
    GL_FLORAL_WHITE = GL_HEX2COLOR(0xFFFAF0),                            /**< FLORAL_WHITE color. */
    GL_FOREST_GREEN = GL_HEX2COLOR(0x228B22),                            /**< FOREST_GREEN color. */
    GL_FUCHSIA = GL_HEX2COLOR(0xFF00FF),                                 /**< FUCHSIA color. */
    GL_GAINSBORO = GL_HEX2COLOR(0xDCDCDC),                               /**< GAINSBORO color. */
    GL_GHOST_WHITE = GL_HEX2COLOR(0xF8F8FF),                             /**< GHOST_WHITE color. */
    GL_GOLD = GL_HEX2COLOR(0xFFD700),                                    /**< GOLD color. */
    GL_GOLDEN_ROD = GL_HEX2COLOR(0xDAA520),                              /**< GOLDEN_ROD color. */
    GL_GRAY = GL_HEX2COLOR(0x808080),                                    /**< GRAY color. */
    GL_GREY = GL_HEX2COLOR(0x808080),                                    /**< GREY color. */
    GL_GREEN = GL_HEX2COLOR(0x008000),                                   /**< GREEN color. */
    GL_GREEN_YELLOW = GL_HEX2COLOR(0xADFF2F),                            /**< GREEN_YELLOW color. */
    GL_HONEY_DEW = GL_HEX2COLOR(0xF0FFF0),                               /**< HONEY_DEW color. */
    GL_HOT_PINK = GL_HEX2COLOR(0xFF69B4),                                /**< HOT_PINK color. */
    GL_INDIAN_RED = GL_HEX2COLOR(0xCD5C5C),                              /**< INDIAN_RED color. */
    GL_INDIGO = GL_HEX2COLOR(0x4B0082),                                  /**< INDIGO color. */
    GL_IVORY = GL_HEX2COLOR(0xFFFFF0),                                   /**< IVORY color. */
    GL_KHAKI = GL_HEX2COLOR(0xF0E68C),                                   /**< KHAKI color. */
    GL_LAVENDER = GL_HEX2COLOR(0xE6E6FA),                                /**< LAVENDER color. */
    GL_LAVENDER_BLUSH = GL_HEX2COLOR(0xFFF0F5),                          /**< LAVENDER_BLUSH color. */
    GL_LAWN_GREEN = GL_HEX2COLOR(0x7CFC00),                              /**< LAWN_GREEN color. */
    GL_LEMON_CHIFFON = GL_HEX2COLOR(0xFFFACD),                           /**< LEMON_CHIFFON color. */
    GL_LIGHT_BLUE = GL_HEX2COLOR(0xADD8E6),                              /**< LIGHT_BLUE color. */
    GL_LIGHT_CORAL = GL_HEX2COLOR(0xF08080),                             /**< LIGHT_CORAL color. */
    GL_LIGHT_CYAN = GL_HEX2COLOR(0xE0FFFF),                              /**< LIGHT_CYAN color. */
    GL_LIGHT_GOLDEN_ROD_YELLOW = GL_HEX2COLOR(0xFAFAD2),                 /**< LIGHT_GOLDEN_ROD_YELLOW color. */
    GL_LIGHT_GRAY = GL_HEX2COLOR(0xD3D3D3),                              /**< LIGHT_GRAY color. */
    GL_LIGHT_GREY = GL_HEX2COLOR(0xD3D3D3),                              /**< LIGHT_GREY color. */
    GL_LIGHT_GREEN = GL_HEX2COLOR(0x90EE90),                             /**< LIGHT_GREEN color. */
    GL_LIGHT_PINK = GL_HEX2COLOR(0xFFB6C1),                              /**< LIGHT_PINK color. */
    GL_LIGHT_SALMON = GL_HEX2COLOR(0xFFA07A),                            /**< LIGHT_SALMON color. */
    GL_LIGHT_SEA_GREEN = GL_HEX2COLOR(0x20B2AA),                         /**< LIGHT_SEA_GREEN color. */
    GL_LIGHT_SKY_BLUE = GL_HEX2COLOR(0x87CEFA),                          /**< LIGHT_SKY_BLUE color. */
    GL_LIGHT_SLATE_GRAY = GL_HEX2COLOR(0x778899),                        /**< LIGHT_SLATE_GRAY color. */
    GL_LIGHT_SLATE_GREY = GL_HEX2COLOR(0x778899),                        /**< LIGHT_SLATE_GREY color. */
    GL_LIGHT_STEEL_BLUE = GL_HEX2COLOR(0xB0C4DE),                        /**< LIGHT_STEEL_BLUE color. */
    GL_LIGHT_YELLOW = GL_HEX2COLOR(0xFFFFE0),                            /**<_LIGHT_YELLOW color. */
    GL_LIME = GL_HEX2COLOR(0x00FF00),                                    /**< LIME color. */
    GL_LIME_GREEN = GL_HEX2COLOR(0x32CD32),                              /**< LIME_GREEN color. */
    GL_LINEN = GL_HEX2COLOR(0xFAF0E6),                                   /**< LINEN color. */
    GL_MAGENTA = GL_HEX2COLOR(0xFF00FF),                                 /**< MAGENTA color. */
    GL_MAROON = GL_HEX2COLOR(0x800000),                                  /**< MAROON color. */
    GL_MEDIUM_AQUA_MARINE = GL_HEX2COLOR(0x66CDAA),                      /**< MEDIUM_AQUA_MARINE color. */
    GL_MEDIUM_BLUE = GL_HEX2COLOR(0x0000CD),                             /**< MEDIUM_BLUE color. */
    GL_MEDIUM_ORCHID = GL_HEX2COLOR(0xBA55D3),                           /**< MEDIUM_ORCHID color. */
    GL_MEDIUM_PURPLE = GL_HEX2COLOR(0x9370DB),                           /**< MEDIUM_PURPLE color. */
    GL_MEDIUM_SEA_GREEN = GL_HEX2COLOR(0x3CB371),                        /**< MEDIUM_SEA_GREEN color. */
    GL_MEDIUM_SLATE_BLUE = GL_HEX2COLOR(0x7B68EE),                       /**< MEDIUM_SLATE_BLUE color. */
    GL_MEDIUM_SPRING_GREEN = GL_HEX2COLOR(0x00FA9A),                     /**< MEDIUM_SPRING_GREEN color. */
    GL_MEDIUM_TURQUOISE = GL_HEX2COLOR(0x48D1CC),                        /**< MEDIUM_TURQUOISE color. */
    GL_MEDIUM_VIOLET_RED = GL_HEX2COLOR(0xC71585),                       /**< MEDIUM_VIOLET_RED color. */
    GL_MIDNIGHT_BLUE = GL_HEX2COLOR(0x191970),                           /**< MIDNIGHT_BLUE color. */
    GL_MINT_CREAM = GL_HEX2COLOR(0xF5FFFA),                              /**< MINT_CREAM color. */
    GL_MISTY_ROSE = GL_HEX2COLOR(0xFFE4E1),                              /**< MISTY_ROSE color. */
    GL_MOCCASIN = GL_HEX2COLOR(0xFFE4B5),                                /**< MOCCASIN color. */
    GL_NAVAJO_WHITE = GL_HEX2COLOR(0xFFDEAD),                            /**< NAVAJO_WHITE color. */
    GL_NAVY = GL_HEX2COLOR(0x000080),                                    /**< NAVY color. */
    GL_OLD_LACE = GL_HEX2COLOR(0xFDF5E6),                                /**< OLD_LACE color. */
    GL_OLIVE = GL_HEX2COLOR(0x808000),                                   /**< OLIVE color. */
    GL_OLIVE_DRAB = GL_HEX2COLOR(0x6B8E23),                              /**< OLIVE_DRAB color. */
    GL_ORANGE = GL_HEX2COLOR(0xFFA500),                                  /**< ORANGE color. */
    GL_ORANGE_RED = GL_HEX2COLOR(0xFF4500),                              /**< ORANGE_RED color. */
    GL_ORCHID = GL_HEX2COLOR(0xDA70D6),                                  /**< ORCHID color. */
    GL_PALE_GOLDEN_ROD = GL_HEX2COLOR(0xEEE8AA),                         /**< PALE_GOLDEN_ROD color. */
    GL_PALE_GREEN = GL_HEX2COLOR(0x98FB98),                              /**< PALE_GREEN color. */
    GL_PALE_TURQUOISE = GL_HEX2COLOR(0xAFEEEE),                          /**< PALE_TURQUOISE color. */
    GL_PALE_VIOLET_RED = GL_HEX2COLOR(0xDB7093),                         /**< PALE_VIOLET_RED color. */
    GL_PAPAYA_WHIP = GL_HEX2COLOR(0xFFEFD5),                             /**< PAPAYA_WHIP color. */
    GL_PEACH_PUFF = GL_HEX2COLOR(0xFFDAB9),                              /**< PEACH_PUFF color. */
    GL_PERU = GL_HEX2COLOR(0xCD853F),                                    /**< PERU color. */
    GL_PINK = GL_HEX2COLOR(0xFFC0CB),                                    /**< PINK color. */
    GL_PLUM = GL_HEX2COLOR(0xDDA0DD),                                    /**< PLUM color. */
    GL_POWDER_BLUE = GL_HEX2COLOR(0xB0E0E6),                             /**< POWDER_BLUE color. */
    GL_PURPLE = GL_HEX2COLOR(0x800080),                                  /**< PURPLE color. */
    GL_REBECCA_PURPLE = GL_HEX2COLOR(0x663399),                          /**< REBECCA_PURPLE color. */
    GL_RED = GL_HEX2COLOR(0xFF0000),                                     /**< RED color. */
    GL_ROSY_BROWN = GL_HEX2COLOR(0xBC8F8F),                              /**< ROSY_BROWN color. */
    GL_ROYAL_BLUE = GL_HEX2COLOR(0x4169E1),                              /**< ROYAL_BLUE color. */
    GL_SADDLE_BROWN = GL_HEX2COLOR(0x8B4513),                            /**< SADDLE_BROWN color. */
    GL_SALMON = GL_HEX2COLOR(0xFA8072),                                  /**< SALMON color. */
    GL_SANDY_BROWN = GL_HEX2COLOR(0xF4A460),                             /**< SANDY_BROWN color. */
    GL_SEA_GREEN = GL_HEX2COLOR(0x2E8B57),                               /**< SEA_GREEN color. */
    GL_SEA_SHELL = GL_HEX2COLOR(0xFFF5EE),                               /**< SEA_SHELL color. */
    GL_SIENNA = GL_HEX2COLOR(0xA0522D),                                  /**< SIENNA color. */
    GL_SILVER = GL_HEX2COLOR(0xC0C0C0),                                  /**< SILVER color. */
    GL_SKY_BLUE = GL_HEX2COLOR(0x87CEEB),                                /**< SKY_BLUE color. */
    GL_SLATE_BLUE = GL_HEX2COLOR(0x6A5ACD),                              /**< SLATE_BLUE color. */
    GL_SLATE_GRAY = GL_HEX2COLOR(0x708090),                              /**< SLATE_GRAY color. */
    GL_SLATE_GREY = GL_HEX2COLOR(0x708090),                              /**< SLATE_GREY color. */
    GL_SNOW = GL_HEX2COLOR(0xFFFAFA),                                    /**< SNOW color. */
    GL_SPRING_GREEN = GL_HEX2COLOR(0x00FF7F),                            /**< SPRING_GREEN color. */
    GL_STEEL_BLUE = GL_HEX2COLOR(0x4682B4),                              /**< STEEL_BLUE color. */
    GL_TAN = GL_HEX2COLOR(0xD2B48C),                                     /**< TAN color. */
    GL_TEAL = GL_HEX2COLOR(0x008080),                                    /**< TEAL color. */
    GL_THISTLE = GL_HEX2COLOR(0xD8BFD8),                                 /**< THISTLE color. */
    GL_TOMATO = GL_HEX2COLOR(0xFF6347),                                  /**< TOMATO color. */
    GL_TURQUOISE = GL_HEX2COLOR(0x40E0D0),                               /**< TURQUOISE color. */
    GL_VIOLET = GL_HEX2COLOR(0xEE82EE),                                  /**< VIOLET color. */
    GL_WHEAT = GL_HEX2COLOR(0xF5DEB3),                                   /**< WHEAT color. */
    GL_WHITE = GL_HEX2COLOR(0xFFFFFF),                                   /**< WHITE color. */
    GL_WHITE_SMOKE = GL_HEX2COLOR(0xF5F5F5),                             /**< WHITE_SMOKE color. */
    GL_YELLOW = GL_HEX2COLOR(0xFFFF00),                                  /**< YELLOW color. */
    GL_YELLOW_GREEN = GL_HEX2COLOR(0x9ACD32),                            /**< YELLOW_GREEN color. */

    GL_EAGLE_GREEN = GL_RGB2COLOR(8, 76, 97),                            /**< EAGLE_GREEN color. */
    GL_YELLY_BEAN = GL_RGB2COLOR(219, 80, 74),                           /**< YELLY_BEAN color. */
    GL_CITRINE  = GL_RGB2COLOR(227, 181, 5),                             /**< CITRINE color. */
    GL_PAYNES_GRAY = GL_RGB2COLOR(79, 109, 122),                         /**< PAYNES_GRAY color. */
    GL_DARK_GUNMENT = GL_RGB2COLOR(33, 35, 51),                          /**< DARK_GUNMENT color. */
    GL_CHARLESTON_GREEN = GL_RGB2COLOR(36, 37, 48)                       /**< CHARLESTON_GREEN color. */
};

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _GL_COLORS_H_
// ------------------------------------------------------------------------- END
