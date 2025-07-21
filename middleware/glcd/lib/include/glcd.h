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
#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_port.h"

typedef enum {
    ON = 0x3F, on = 0x3F, On = 0x3F, oN = 0x3F, 
    
    OFF = 0x3E, Off = 0x3E, oFf = 0x3E, ofF = 0x3E,
    OFf = 0x3E, oFF = 0x3E, OfF = 0x3E, off = 0x3E,
} display_cfg_t;

/**
 * @brief Enumeration for line drawing directions.
 * @details This enumeration defines the possible directions for drawing lines on the GLCD.
 * It includes vertical, horizontal, and diagonal directions.
 */
typedef enum { VERTICAL_LINE, HORIZONTAL_LINE, DIAGONAL } line_dir_t;

/**
 * @brief Enumeration for rectangle drawing modes.
 * @details This enumeration defines the modes for drawing rectangles on the GLCD.
 * It includes center dimensions, corner dimensions, and three points mode. 
 */
typedef enum { CENTER_DIMENSIONS, CORNER_DIMENSIONS, THREE_POINTS } rect_mode_t;

/**
 * @brief Enumeration for polygon drawing modes.
 * @details This enumeration defines the number of sides for regular polygons that can be drawn on the GLCD.
 * It includes modes for triangles, rectangles, pentagons, hexagons, heptagons, octagons, nonagons, and decagons.
 * 
 * @note The user can specify the number of sides when drawing polygons using the GLCD_Draw_Regular_Polygon function.
 * He can also use GLCD_Draw_Shape to draw custom shapes defined by segments.
 */
typedef enum { TRIANGLE = 3, RECTANGLE = 4, PENTAGON = 5, HEXAGON = 6, HEPTAGON = 7, OCTAGON = 8, NONAGON = 9, DECAGON = 10 } polygon_mode_t;

/**
 * @brief Enumeration for circle drawing modes.
 * @details This enumeration defines the precision levels for drawing circles on the GLCD.
 * It includes fast, default, and high precision modes, which determine the number of points used to approximate the circle.
 */
typedef enum { FAST = 15, DEFAULT = 100, PRECISION = 3000 } circle_mode_t;


#define IS_ON( x )              ( (x == ON) || (x == oN) || (x == on) || (x == oN) )
#define IS_OFF( x )             ( (x == OFF) || (x == Off) || (x == oFf) || (x == ofF) || (x == OFf) || (x == oFF) || (x == ofF) || (x == off) )

#define PI                      3.14159265359
#define CS_SIZE                 2
#define PAGE_SIZE               8
#define COL_PER_CHIP            64
#define ROW_SIZE                ( CS_SIZE * COL_PER_CHIP )

/* Pins defintion for GLCD usage */
#define E_PIN                   PE15
#define RW_PIN                  PE13
#define RS_PIN                  PE12
#define CS2_PIN                 PE11
#define CS1_PIN                 PE10
#define RESET_PIN               PE8

/* GLCD Structure context/config creation and basic geometry (point, segment, rect, ...) structure*/
/**
 * @name point
 * @brief A structure representing a 2D point on the GLCD screen.
 * 
 * @param x : ( uint8_t ) X-coordinate (0–127)
 * @param y : ( uint8_t ) Y-coordinate (0–63)
 */
typedef struct point { uint8_t x; uint8_t y; } point;

/**
 * @name segment
 * @brief A structure representing a segment (line) defined by two points and a line thickness.
 * 
 * @param pts       : ( point[2] ) Two endpoints of the segment
 * @param line_size : ( uint8_t ) Thickness of the segment
 */
typedef struct segment { point pts[2]; uint8_t line_size; } segment;

/**
 * @name rect
 * @brief A rectangle structure that defines dimensions, border thickness, and style.
 * 
 * @param w         : ( uint8_t ) Width of the rectangle (0-127)
 * @param h         : ( uint8_t ) Height of the rectangle (0-63)
 * @param line_size : ( uint8_t ) Thickness of the rectangle border (0-63)
 * @param filled    : ( bool ) If true, the rectangle will be filled
 * @param rounded   : ( bool ) If true, rounded corners will be drawn (not yet implemented)
 * 
 * @note The user must define this structure manually before passing it to drawing functions.
 */
typedef struct rect { uint8_t w; uint8_t h; uint8_t line_size; bool filled; bool rounded; } rect;

/**
 * @name circle
 * @brief A circle structure that encapsulates the essential parameters required for rendering.
 * 
 * @param o         : ( point ) Origin (center) of the circle
 * @param r         : ( uint8_t ) Radius of the circle
 * @param line_size : ( uint8_t ) Line thickness
 * @param filled    : ( bool ) If true, fills the circle
 * 
 * @note The user needs to define this structure before using it in the GLCD_Draw_Circle function.
 */
typedef struct circle { point o; uint8_t r; uint8_t line_size; bool filled; } circle;

/**
 * @name ellipse
 * @brief A structure representing an ellipse defined by its foci, semi-major axis, and style options.
 * 
 * @param mid_foci   : ( point[2] ) Two focal points of the ellipse
 * @param a          : ( float ) Semi-major axis length
 * @param line_size  : ( uint8_t ) Thickness of the ellipse's contour
 * @param filled     : ( bool ) If true, the ellipse will be filled
 * 
 * @note The two focal points must be distinct but a is calculated regarless (the user dont need
 * to bother about this parameter).
 */
typedef struct ellipse { point mid_foci[2]; float a; uint8_t line_size; bool filled; } ellipse;

/**
 * @name CHAR
 * @brief A character font structure that maps an ASCII character to its 8x8 bitmap.
 * 
 * @param c            : ( char ) The character symbol
 * @param bitmap_code  : ( uint64_t ) 8x8 bitmap representation of the character (column-wise)
 * 
 * @note Used internally by GLCD_Write_Char and GLCD_Write_Text functions.
 */
typedef struct CHAR { char c; uint64_t bitmap_code; } CHAR;

/**
 * @brief Main GLCD structure for managing configuration, GPIO control and framebuffer buffer.
 * 
 * @param data_out : ( port_t ) Port used for data output to the GLCD (1 byte)
 * @param cs1d     : ( digital_out_t ) Chip select 1 control
 * @param cs2d     : ( digital_out_t ) Chip select 2 control
 * @param ed       : ( digital_out_t ) Enable signal
 * @param resetd   : ( digital_out_t ) Reset signal
 * @param rsd      : ( digital_out_t ) Register select (data/instruction)
 * @param rwd      : ( digital_out_t ) Read/write control signal
 * @param buffer   : ( uint8_t[][][] ) Frame buffer: 2 chips with 8 pages and 64 columns
 * 
 * @note The user must initialize this structure using GLCD_Init() before use.
 */
typedef struct glcd {
    port_t data_out;
    digital_out_t cs1d; 
    digital_out_t cs2d;
    digital_out_t ed;
    digital_out_t resetd; 
    digital_out_t rsd; 
    digital_out_t rwd;
    uint8_t buffer[CS_SIZE][PAGE_SIZE][COL_PER_CHIP];
} glcd_t;

/* -------------------------------------------------- Initialize functions -------------------------------------------------- */
void GLCD_Port_Init                         ( glcd_t* glcd );
void GLCD_Init                              ( glcd_t* glcd );
void GLCD_Set_Page                          ( glcd_t* glcd, uint8_t page );
void GLCD_Set_Y                             ( glcd_t* glcd, uint8_t y_pos );
void GLCD_Clear                             ( glcd_t *glcd );
void GLCD_Display                           ( glcd_t* glcd, display_cfg_t turn_on_off );
void Apply_changes                          ( glcd_t* glcd );
void CS_Config                              ( glcd_t* glcd, bool cs1, bool cs2 );

/* -------------------------------------------------- Read and Write functions -------------------------------------------------- */
uint8_t GLCD_Read                           ( glcd_t* glcd, uint8_t page, uint8_t lign );
uint8_t GLCD_Read_LL                        ( glcd_t* glcd, uint8_t page, uint8_t column );
void GLCD_Write                             ( glcd_t *glcd, uint8_t page, uint8_t column, uint8_t data_to_write );
void GLCD_Write_Char                        ( glcd_t* glcd, point* p, char c );
void GLCD_Write_Text                        ( glcd_t* glcd, point* p, const char* c );

/* -------------------------------------------------- Drawing functions -------------------------------------------------- */
void GLCD_Fill_Screen                       ( glcd_t* glcd, uint8_t pattern );
void GLCD_Draw_Dots                         ( glcd_t* glcd, const point* pts, uint8_t size, uint8_t dot_size );
void GLCD_Draw_Line                         ( glcd_t* glcd, const segment* s, uint8_t s_size, line_dir_t direction );
void GLCD_Draw_Rect                         ( glcd_t* glcd, const point* p, uint16_t psize, const rect* r, uint16_t rsize );
void GLCD_Draw_Rect_Giving_Points           ( glcd_t* glcd, const point* p, uint8_t size, uint8_t dot_size, bool is_filled, bool round_edges);
void GLCD_Draw_Shape                        ( glcd_t* glcd, const segment* edges, uint8_t size, bool is_filled, bool round_edges );
void GLCD_Draw_Regular_Polygon              ( glcd_t* glcd, const point* ori, uint8_t num_of_ori, const polygon_mode_t* pol, uint8_t num_of_pol, bool is_filled );
void GLCD_Draw_Circle                       ( glcd_t* glcd, const circle* c, uint16_t csize, circle_mode_t precision );
void GLCD_Draw_Ellipse                      ( glcd_t* glcd, const ellipse* e, uint16_t esize, circle_mode_t precision );

/* -------------------------------------------------- Utils -------------------------------------------------- */
float distance                              ( point a, point b );
void Sort_Points_Nearest_Neighbor           ( const segment* input, segment* output, uint8_t size );
void Fill_Polygon                           ( glcd_t* glcd, const segment* edges, uint8_t size );
void Fill_Circle                            ( glcd_t* glcd, const point* contour, uint16_t precision, uint8_t dot_size );
static int dot_product                      (point a, point b, point c);
uint64_t Transpose_Word                     ( uint64_t word );
uint64_t Find_Matching_Char_From_Bitmap     ( char c );
uint8_t Reverse_Byte                        ( uint8_t b );