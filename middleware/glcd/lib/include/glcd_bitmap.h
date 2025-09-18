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
 * @file glcd_bitmap.h
 * @brief GLCD (Graphic Liquid Crystal Display) Bitmap.
 */

#include <stdint.h>

static uint8_t bitmap_space[8]             = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // ' '
static uint8_t bitmap_exclamation[8]       = { 0x08, 0x08, 0x08, 0x08, 0x00, 0x08, 0x00, 0x00 }; // '!'
static uint8_t bitmap_quotedbl[8]          = { 0x28, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // '"'
static uint8_t bitmap_hash[8]              = { 0x28, 0x7C, 0x28, 0x7C, 0x28, 0x00, 0x00, 0x00 }; // '#'
static uint8_t bitmap_dollar[8]            = { 0x08, 0x1E, 0x28, 0x1C, 0x0A, 0x3C, 0x08, 0x00 }; // '$'
static uint8_t bitmap_percent[8]           = { 0x60, 0x94, 0x68, 0x16, 0x29, 0x06, 0x00, 0x00 }; // '%'
static uint8_t bitmap_ampersand[8]         = { 0x1C, 0x20, 0x20, 0x19, 0x26, 0x19, 0x00, 0x00 }; // '&'
static uint8_t bitmap_apostrophe[8]        = { 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // '\'
static uint8_t bitmap_parenleft[8]         = { 0x08, 0x10, 0x20, 0x20, 0x10, 0x08, 0x00, 0x00 }; // '('
static uint8_t bitmap_parenright[8]        = { 0x10, 0x08, 0x04, 0x04, 0x08, 0x10, 0x00, 0x00 }; // ')'
static uint8_t bitmap_asterisk[8]          = { 0x2A, 0x1C, 0x3E, 0x1C, 0x2A, 0x00, 0x00, 0x00 }; // '*'
static uint8_t bitmap_plus[8]              = { 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00, 0x00, 0x00 }; // '+'
static uint8_t bitmap_comma[8]             = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x00, 0x00 }; // ','
static uint8_t bitmap_minus[8]             = { 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // '-'
static uint8_t bitmap_period[8]            = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00 }; // '.'
static uint8_t bitmap_slash[8]             = { 0x20, 0x40, 0x81, 0x02, 0x04, 0x00, 0x00, 0x00 }; // '/'
static uint8_t bitmap_0[8]                 = { 0x18, 0x24, 0x42, 0x42, 0x24, 0x18, 0x00, 0x00 }; // '0'
static uint8_t bitmap_1[8]                 = { 0x08, 0x18, 0x08, 0x08, 0x08, 0x1C, 0x00, 0x00 }; // '1'
static uint8_t bitmap_2[8]                 = { 0x3C, 0x42, 0x04, 0x18, 0x20, 0x7E, 0x00, 0x00 }; // '2'
static uint8_t bitmap_3[8]                 = { 0x3C, 0x42, 0x04, 0x18, 0x42, 0x3C, 0x00, 0x00 }; // '3'
static uint8_t bitmap_4[8]                 = { 0x08, 0x18, 0x28, 0x48, 0x7C, 0x08, 0x00, 0x00 }; // '4'
static uint8_t bitmap_5[8]                 = { 0x7E, 0x40, 0x7C, 0x02, 0x42, 0x3C, 0x00, 0x00 }; // '5'
static uint8_t bitmap_6[8]                 = { 0x3C, 0x40, 0x7C, 0x42, 0x42, 0x3C, 0x00, 0x00 }; // '6'
static uint8_t bitmap_7[8]                 = { 0x7E, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00, 0x00 }; // '7'
static uint8_t bitmap_8[8]                 = { 0x3C, 0x42, 0x3C, 0x42, 0x42, 0x3C, 0x00, 0x00 }; // '8'
static uint8_t bitmap_9[8]                 = { 0x3C, 0x42, 0x42, 0x3E, 0x02, 0x3C, 0x00, 0x00 }; // '9'
static uint8_t bitmap_colon[8]             = { 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00 }; // ':'
static uint8_t bitmap_semicolon[8]         = { 0x00, 0x00, 0x00, 0x08, 0x00, 0x01, 0x00, 0x00 }; // ';'
static uint8_t bitmap_less[8]              = { 0x06, 0x18, 0x60, 0x18, 0x06, 0x00, 0x00, 0x00 }; // '<'
static uint8_t bitmap_equal[8]             = { 0x00, 0x7E, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00 }; // '='
static uint8_t bitmap_greater[8]           = { 0x60, 0x18, 0x06, 0x18, 0x60, 0x00, 0x00, 0x00 }; // '>'
static uint8_t bitmap_question[8]          = { 0x38, 0x44, 0x04, 0x18, 0x00, 0x10, 0x00, 0x00 }; // '?'
static uint8_t bitmap_at[8]                = { 0x3C, 0x44, 0x9C, 0x94, 0x5C, 0x20, 0x1C, 0x00 }; // '@'
static uint8_t bitmap_A[8]                 = { 0x18, 0x18, 0x24, 0x3C, 0x42, 0x42, 0x00, 0x00 }; // 'A'
static uint8_t bitmap_B[8]                 = { 0x78, 0x44, 0x78, 0x44, 0x44, 0x78, 0x00, 0x00 }; // 'B'
static uint8_t bitmap_C[8]                 = { 0x38, 0x44, 0x80, 0x80, 0x44, 0x38, 0x00, 0x00 }; // 'C'
static uint8_t bitmap_D[8]                 = { 0x78, 0x44, 0x44, 0x44, 0x44, 0x78, 0x00, 0x00 }; // 'D'
static uint8_t bitmap_E[8]                 = { 0x7C, 0x40, 0x78, 0x40, 0x40, 0x7C, 0x00, 0x00 }; // 'E'
static uint8_t bitmap_F[8]                 = { 0x7C, 0x40, 0x78, 0x40, 0x40, 0x40, 0x00, 0x00 }; // 'F'
static uint8_t bitmap_G[8]                 = { 0x38, 0x44, 0x80, 0x9C, 0x44, 0x38, 0x00, 0x00 }; // 'G'
static uint8_t bitmap_H[8]                 = { 0x42, 0x42, 0x7E, 0x42, 0x42, 0x42, 0x00, 0x00 }; // 'H'
static uint8_t bitmap_I[8]                 = { 0x3E, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00 }; // 'I'
static uint8_t bitmap_J[8]                 = { 0x1C, 0x04, 0x04, 0x04, 0x44, 0x38, 0x00, 0x00 }; // 'J'
static uint8_t bitmap_K[8]                 = { 0x44, 0x48, 0x50, 0x70, 0x48, 0x44, 0x00, 0x00 }; // 'K'
static uint8_t bitmap_L[8]                 = { 0x40, 0x40, 0x40, 0x40, 0x40, 0x7E, 0x00, 0x00 }; // 'L'
static uint8_t bitmap_M[8]                 = { 0x41, 0x63, 0x55, 0x49, 0x41, 0x41, 0x00, 0x00 }; // 'M'
static uint8_t bitmap_N[8]                 = { 0x42, 0x62, 0x52, 0x4A, 0x46, 0x42, 0x00, 0x00 }; // 'N'
static uint8_t bitmap_O[8]                 = { 0x1C, 0x22, 0x22, 0x22, 0x22, 0x1C, 0x00, 0x00 }; // 'O'
static uint8_t bitmap_P[8]                 = { 0x78, 0x44, 0x78, 0x40, 0x40, 0x40, 0x00, 0x00 }; // 'P'
static uint8_t bitmap_Q[8]                 = { 0x1C, 0x22, 0x22, 0x22, 0x22, 0x1C, 0x02, 0x00 }; // 'Q'
static uint8_t bitmap_R[8]                 = { 0x78, 0x44, 0x78, 0x50, 0x48, 0x44, 0x00, 0x00 }; // 'R'
static uint8_t bitmap_S[8]                 = { 0x1C, 0x22, 0x10, 0x0C, 0x22, 0x1C, 0x00, 0x00 }; // 'S'
static uint8_t bitmap_T[8]                 = { 0x7F, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00 }; // 'T'
static uint8_t bitmap_U[8]                 = { 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00 }; // 'U'
static uint8_t bitmap_V[8]                 = { 0x81, 0x42, 0x42, 0x24, 0x24, 0x18, 0x00, 0x00 }; // 'V'
static uint8_t bitmap_W[8]                 = { 0x41, 0x41, 0x49, 0x55, 0x63, 0x41, 0x00, 0x00 }; // 'W'
static uint8_t bitmap_X[8]                 = { 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x00, 0x00 }; // 'X'
static uint8_t bitmap_Y[8]                 = { 0x41, 0x22, 0x14, 0x08, 0x08, 0x08, 0x00, 0x00 }; // 'Y'
static uint8_t bitmap_Z[8]                 = { 0x7E, 0x04, 0x08, 0x10, 0x20, 0x7E, 0x00, 0x00 }; // 'Z'
static uint8_t bitmap_bracket_left[8]      = { 0x38, 0x20, 0x20, 0x20, 0x20, 0x38, 0x00, 0x00 }; // '['
static uint8_t bitmap_backslash[8]         = { 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00 }; // '\'
static uint8_t bitmap_bracket_right[8]     = { 0x38, 0x08, 0x08, 0x08, 0x08, 0x38, 0x00, 0x00 }; // ']'
static uint8_t bitmap_caret[8]             = { 0x10, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // '^'
static uint8_t bitmap_underscore[8]        = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00 }; // '_'
static uint8_t bitmap_grave[8]             = { 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // '`'
static uint8_t bitmap_a[8]                 = { 0x00, 0x3C, 0x02, 0x3E, 0x46, 0x3A, 0x00, 0x00 }; // 'a'
static uint8_t bitmap_b[8]                 = { 0x40, 0x40, 0x7C, 0x42, 0x62, 0x5C, 0x00, 0x00 }; // 'b'
static uint8_t bitmap_c[8]                 = { 0x00, 0x1C, 0x20, 0x20, 0x1C, 0x00, 0x00, 0x00 }; // 'c'
static uint8_t bitmap_d[8]                 = { 0x00, 0x08, 0x08, 0x08, 0x38, 0x48, 0x38, 0x00 }; // 'd'
static uint8_t bitmap_e[8]                 = { 0x00, 0x3C, 0x42, 0x7E, 0x40, 0x3C, 0x00, 0x00 }; // 'e'
static uint8_t bitmap_f[8]                 = { 0x00, 0x18, 0x10, 0x38, 0x10, 0x10, 0x00, 0x00 }; // 'f'
static uint8_t bitmap_g[8]                 = { 0x00, 0x34, 0x4C, 0x44, 0x34, 0x04, 0x38, 0x00 }; // 'g'
static uint8_t bitmap_h[8]                 = { 0x20, 0x20, 0x38, 0x24, 0x24, 0x24, 0x00, 0x00 }; // 'h'
static uint8_t bitmap_i[8]                 = { 0x00, 0x08, 0x00, 0x18, 0x08, 0x08, 0x08, 0x00 }; // 'i'
static uint8_t bitmap_j[8]                 = { 0x00, 0x08, 0x00, 0x18, 0x08, 0x28, 0x38, 0x00 }; // 'j'
static uint8_t bitmap_k[8]                 = { 0x20, 0x20, 0x24, 0x28, 0x30, 0x2C, 0x00, 0x00 }; // 'k'
static uint8_t bitmap_l[8]                 = { 0x10, 0x10, 0x10, 0x10, 0x10, 0x18, 0x00, 0x00 }; // 'l'
static uint8_t bitmap_m[8]                 = { 0x00, 0x66, 0x5A, 0x42, 0x42, 0x00, 0x00, 0x00 }; // 'm'
static uint8_t bitmap_n[8]                 = { 0x00, 0x2E, 0x32, 0x22, 0x22, 0x00, 0x00, 0x00 }; // 'n'
static uint8_t bitmap_o[8]                 = { 0x00, 0x3C, 0x42, 0x42, 0x3C, 0x00, 0x00, 0x00 }; // 'o'
static uint8_t bitmap_p[8]                 = { 0x00, 0x5C, 0x62, 0x42, 0x7C, 0x40, 0x40, 0x00 }; // 'p'
static uint8_t bitmap_q[8]                 = { 0x00, 0x3A, 0x46, 0x42, 0x3E, 0x02, 0x02, 0x00 }; // 'q'
static uint8_t bitmap_r[8]                 = { 0x00, 0x2C, 0x32, 0x20, 0x20, 0x00, 0x00, 0x00 }; // 'r'
static uint8_t bitmap_s[8]                 = { 0x00, 0x1C, 0x20, 0x18, 0x04, 0x38, 0x00, 0x00 }; // 's'
static uint8_t bitmap_t[8]                 = { 0x00, 0x10, 0x3C, 0x10, 0x10, 0x18, 0x00, 0x00 }; // 't'
static uint8_t bitmap_u[8]                 = { 0x00, 0x22, 0x22, 0x26, 0x1A, 0x00, 0x00, 0x00 }; // 'u'
static uint8_t bitmap_v[8]                 = { 0x00, 0x42, 0x42, 0x24, 0x18, 0x00, 0x00, 0x00 }; // 'v'
static uint8_t bitmap_w[8]                 = { 0x00, 0x81, 0x81, 0x5A, 0x66, 0x00, 0x00, 0x00 }; // 'w'
static uint8_t bitmap_x[8]                 = { 0x00, 0x42, 0x24, 0x18, 0x66, 0x00, 0x00, 0x00 }; // 'x'
static uint8_t bitmap_y[8]                 = { 0x00, 0x42, 0x21, 0x14, 0x08, 0x10, 0x60, 0x00 }; // 'y'
static uint8_t bitmap_z[8]                 = { 0x00, 0x3C, 0x08, 0x10, 0x3C, 0x00, 0x00, 0x00 }; // 'z'
static uint8_t bitmap_curly_brace_left[8]  = { 0x1C, 0x10, 0x30, 0x30, 0x10, 0x1C, 0x00, 0x00 }; // '{'
static uint8_t bitmap_pipe[8]              = { 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00 }; // '|'
static uint8_t bitmap_curly_brace_right[8] = { 0x38, 0x08, 0x0C, 0x0C, 0x08, 0x38, 0x00, 0x00 }; // '}'
static uint8_t bitmap_tilde[8]             = { 0x00, 0x00, 0x32, 0x4C, 0x00, 0x00, 0x00, 0x00 }; // '~'

glcd_char_def_t font[] = {
    { ' ',  bitmap_space },               // Element number 0
    { '!',  bitmap_exclamation },         // Element number 1
    { '"',  bitmap_quotedbl },            // Element number 2
    { '#',  bitmap_hash },                // Element number 3
    { '$',  bitmap_dollar },              // Element number 4
    { '%',  bitmap_percent },             // Element number 5
    { '&',  bitmap_ampersand },           // Element number 6
    { '\'', bitmap_apostrophe },          // Element number 7
    { '(',  bitmap_parenleft },           // Element number 8
    { ')',  bitmap_parenright },          // Element number 9
    { '*',  bitmap_asterisk },            // Element number 10
    { '+',  bitmap_plus },                // Element number 11
    { ',',  bitmap_comma },               // Element number 12
    { '-',  bitmap_minus },               // Element number 13
    { '.',  bitmap_period },              // Element number 14
    { '/',  bitmap_slash },               // Element number 15
    { '0',  bitmap_0 },                   // Element number 16
    { '1',  bitmap_1 },                   // Element number 17
    { '2',  bitmap_2 },                   // Element number 18
    { '3',  bitmap_3 },                   // Element number 19
    { '4',  bitmap_4 },                   // Element number 20
    { '5',  bitmap_5 },                   // Element number 21
    { '6',  bitmap_6 },                   // Element number 22
    { '7',  bitmap_7 },                   // Element number 23
    { '8',  bitmap_8 },                   // Element number 24
    { '9',  bitmap_9 },                   // Element number 25
    { ':',  bitmap_colon },               // Element number 26
    { ';',  bitmap_semicolon },           // Element number 27
    { '<',  bitmap_less },                // Element number 28
    { '=',  bitmap_equal },               // Element number 29
    { '>',  bitmap_greater },             // Element number 30
    { '?',  bitmap_question },            // Element number 31
    { '@',  bitmap_at },                  // Element number 32
    { 'A',  bitmap_A },                   // Element number 33
    { 'B',  bitmap_B },                   // Element number 34
    { 'C',  bitmap_C },                   // Element number 35
    { 'D',  bitmap_D },                   // Element number 36
    { 'E',  bitmap_E },                   // Element number 37
    { 'F',  bitmap_F },                   // Element number 38
    { 'G',  bitmap_G },                   // Element number 39
    { 'H',  bitmap_H },                   // Element number 40
    { 'I',  bitmap_I },                   // Element number 41
    { 'J',  bitmap_J },                   // Element number 42
    { 'K',  bitmap_K },                   // Element number 43
    { 'L',  bitmap_L },                   // Element number 44
    { 'M',  bitmap_M },                   // Element number 45
    { 'N',  bitmap_N },                   // Element number 46
    { 'O',  bitmap_O },                   // Element number 47
    { 'P',  bitmap_P },                   // Element number 48
    { 'Q',  bitmap_Q },                   // Element number 49
    { 'R',  bitmap_R },                   // Element number 50
    { 'S',  bitmap_S },                   // Element number 51
    { 'T',  bitmap_T },                   // Element number 52
    { 'U',  bitmap_U },                   // Element number 53
    { 'V',  bitmap_V },                   // Element number 54
    { 'W',  bitmap_W },                   // Element number 55
    { 'X',  bitmap_X },                   // Element number 56
    { 'Y',  bitmap_Y },                   // Element number 57
    { 'Z',  bitmap_Z },                   // Element number 58
    { '[',  bitmap_curly_brace_left },    // Element number 59
    { '\\', bitmap_backslash },           // Element number 60
    { ']',  bitmap_curly_brace_right },   // Element number 61
    { '^',  bitmap_caret },               // Element number 62
    { '_',  bitmap_underscore },          // Element number 63
    { '`',  bitmap_grave },               // Element number 64
    { 'a',  bitmap_a },                   // Element number 65
    { 'b',  bitmap_b },                   // Element number 66
    { 'c',  bitmap_c },                   // Element number 67
    { 'd',  bitmap_d },                   // Element number 68
    { 'e',  bitmap_e },                   // Element number 69
    { 'f',  bitmap_f },                   // Element number 70
    { 'g',  bitmap_g },                   // Element number 71
    { 'h',  bitmap_h },                   // Element number 72
    { 'i',  bitmap_i },                   // Element number 73
    { 'j',  bitmap_j },                   // Element number 74
    { 'k',  bitmap_k },                   // Element number 75
    { 'l',  bitmap_l },                   // Element number 76
    { 'm',  bitmap_m },                   // Element number 77
    { 'n',  bitmap_n },                   // Element number 78
    { 'o',  bitmap_o },                   // Element number 79
    { 'p',  bitmap_p },                   // Element number 80
    { 'q',  bitmap_q },                   // Element number 81
    { 'r',  bitmap_r },                   // Element number 82
    { 's',  bitmap_s },                   // Element number 83
    { 't',  bitmap_t },                   // Element number 84
    { 'u',  bitmap_u },                   // Element number 85
    { 'v',  bitmap_v },                   // Element number 86
    { 'w',  bitmap_w },                   // Element number 87
    { 'x',  bitmap_x },                   // Element number 88
    { 'y',  bitmap_y },                   // Element number 89
    { 'z',  bitmap_z },                   // Element number 90
    { '{',  bitmap_curly_brace_left },    // Element number 91
    { '|',  bitmap_pipe },                // Element number 92
    { '}',  bitmap_curly_brace_right },   // Element number 93
    { '~',  bitmap_tilde },               // Element number 94
};
