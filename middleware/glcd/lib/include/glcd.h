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

const CHAR font[] = {
    { ' ',  0x0000 },     // 0
    { '!',  0x0808080800080000 },     // 1
    { '"',  0x2828000000000000 },     // 2
    { '#',  0x287C287C28000000 },     // 3
    { '$',  0x081E281C0A3C0800 },     // 4
    { '%',  0x6094681629060000 },     // 5
    { '&',  0x1C20201926190000 },     // 6
    { '\'', 0x0808000000000000 },     // 7
    { '(',  0x0810202010080000 },     // 8
    { ')',  0x1008040408100000 },     // 9
    { '*',  0x2A1C3E1C2A000000 },     // 10
    { '+',  0x08083E0808000000 },     // 11
    { ',',  0x0000000000810000 },     // 12
    { '-',  0x003C000000000000 },     // 13
    { '.',  0x0000000000800000 },     // 14
    { '/',  0x2040810204000000 },     // 15
    { '0',  0x1824424224180000 },     // 16
    { '1',  0x08180808081C0000 },     // 17
    { '2',  0x3C420418207E0000 },     // 18
    { '3',  0x3C420418423C0000 },     // 19
    { '4',  0x081828487C080000 },     // 20
    { '5',  0x7E407C02423C0000 },     // 21
    { '6',  0x3C407C42423C0000 },     // 22
    { '7',  0x7E04081020400000 },     // 23
    { '8',  0x3C423C42423C0000 },     // 24
    { '9',  0x3C42423E023C0000 },     // 25
    { ':',  0x0000000800008000 },     // 26
    { ';',  0x0000000800010000 },     // 27
    { '<',  0x0618601806000000 },     // 28
    { '=',  0x007E00007E000000 },     // 29
    { '>',  0x6018061860000000 },     // 30
    { '?',  0x3844041800100000 },     // 31
    { '@',  0x3C449C945C201C00 },     // 32
    { 'A',  0x1818243C42420000 },     // 33
    { 'B',  0x7844784444780000 },     // 34
    { 'C',  0x3844808044380000 },     // 35
    { 'D',  0x7844444444780000 },     // 36
    { 'E',  0x7C407840407C0000 },     // 37
    { 'F',  0x7C40784040400000 },     // 38
    { 'G',  0x3844809C44380000 },     // 39
    { 'H',  0x42427E4242420000 },     // 40
    { 'I',  0x3E080808083E0000 },     // 41
    { 'J',  0x1C04040444380000 },     // 42
    { 'K',  0x4448507048440000 },     // 43
    { 'L',  0x40404040407E0000 },     // 44
    { 'M',  0x4163554941410000 },     // 45
    { 'N',  0x4262524A46420000 },     // 46
    { 'O',  0x1C222222221C0000 },     // 47
    { 'P',  0x7844784040400000 },     // 48
    { 'Q',  0x1C222222221C0200 },     // 49
    { 'R',  0x7844785048440000 },     // 50
    { 'S',  0x1C22100C221C0000 },     // 51
    { 'T',  0x7F08080808080000 },     // 52
    { 'U',  0x42424242423C0000 },     // 53
    { 'V',  0x8142422424180000 },     // 54
    { 'W',  0x4141495563410000 },     // 55
    { 'X',  0x4224181824420000 },     // 56
    { 'Y',  0x4122140808080000 },     // 57
    { 'Z',  0x7E040810207E0000 },     // 58
    { '[',  0x3820202020380000 },     // 59
    { '\\', 0x4020100804020000 },     // 60
    { ']',  0x3808080808380000 },     // 61
    { '^',  0x1028000000000000 },     // 62
    { '_',  0x00000000007E0000 },     // 63
    { '`',  0x1008000000000000 },     // 64
    { 'a',  0x003C023E463A0000 },     // 65
    { 'b',  0x40407C42625C0000 },     // 66
    { 'c',  0x001C20201C000000 },     // 67
    { 'd',  0x0008080838483800 },     // 68
    { 'e',  0x003C427E403C0000 },     // 69
    { 'f',  0x0018103810100000 },     // 70
    { 'g',  0x00344C4434043800 },     // 71
    { 'h',  0x2020382424240000 },     // 72
    { 'i',  0x0008001808080800 },     // 73
    { 'j',  0x0008001808283800 },     // 74
    { 'k',  0x20202428302C0000 },     // 75
    { 'l',  0x1010101010180000 },     // 76
    { 'm',  0x00665A4242000000 },     // 77
    { 'n',  0x002E322222000000 },     // 78
    { 'o',  0x003C42423C000000 },     // 79
    { 'p',  0x005C62427C404000 },     // 80
    { 'q',  0x003A46423E020200 },     // 81
    { 'r',  0x002C322020000000 },     // 82
    { 's',  0x001C201804380000 },     // 83
    { 't',  0x00103C1010180000 },     // 84
    { 'u',  0x002222261A000000 },     // 85
    { 'v',  0x0042422418000000 },     // 86
    { 'w',  0x0081815A66000000 },     // 87
    { 'x',  0x0042241866000000 },     // 88
    { 'y',  0x0042211408106000 },     // 89
    { 'z',  0x003C08103C000000 },     // 90
    { '{',  0x1C103030101C0000 },     // 91
    { '|',  0x0808080808080800 },     // 92
    { '}',  0x38080C0C08380000 },     // 93
    { '~',  0x0000324C00000000 },     // 94
};

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