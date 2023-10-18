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

/// @cond

#ifndef JPEG_CONSTANTS_H
#define JPEG_CONSTANTS_H

#include <stdint.h>

const uint8_t _JPEG_MAX_CHANNELS     = 3;   /* This supports only Grayscale and YCbCr images - DONT CHANGE THIS */
const uint8_t _JPEG_MAX_BLOCKS       = 6;   /* To decode one logical block, we have to decode 1 to 6 blocks depending on channels and subsampling - DONT REDUCE THIS */
const uint8_t _JPEG_MAX_HUFF_TABLES  = 2;   /* Each causes 2 tables -> One for AC and another for DC - DONT REDUCE THIS */
const uint8_t _JPEG_MAX_DATA_BUF_LEN = 128; /* Increase if you have more data memory */

/// JPEG Header constants
const uint8_t _JPEG_SOF0 = 0xC0;
const uint8_t _JPEG_DHT  = 0xC4;
const uint8_t _JPEG_SOI  = 0xD8;
const uint8_t _JPEG_EOI  = 0xD9;
const uint8_t _JPEG_SOS  = 0xDA;
const uint8_t _JPEG_DQT  = 0xDB;
const uint8_t _JPEG_DRI  = 0xDD;
const uint8_t _JPEG_APP0 = 0xE0;
const uint8_t _JPEG_COM  = 0xFE;

/* The below markers doesn't have parameters */
const uint8_t _JPEG_TEM  = 0x01;
const uint8_t _JPEG_RST0 = 0xD0;
const uint8_t _JPEG_RST1 = 0xD1;
const uint8_t _JPEG_RST2 = 0xD2;
const uint8_t _JPEG_RST3 = 0xD3;
const uint8_t _JPEG_RST4 = 0xD4;
const uint8_t _JPEG_RST5 = 0xD5;
const uint8_t _JPEG_RST6 = 0xD6;
const uint8_t _JPEG_RST7 = 0xD7;

const uint8_t _JPEG_SAMPLE_1x1 = 0;
const uint8_t _JPEG_SAMPLE_1x2 = 1;
const uint8_t _JPEG_SAMPLE_2x1 = 2;
const uint8_t _JPEG_SAMPLE_2x2 = 3;

#ifndef __MIKROC__
#define _JPEG_MAX_CHANNELS      3   /* This supports only Grayscale and YCbCr images - DONT CHANGE THIS */
#define _JPEG_MAX_BLOCKS        6   /* To decode one logical block, we have to decode 1 to 6 blocks depending on channels and subsampling - DONT REDUCE THIS */
#define _JPEG_MAX_HUFF_TABLES   2   /* Each causes 2 tables -> One for AC and another for DC - DONT REDUCE THIS */
#define _JPEG_MAX_DATA_BUF_LEN  128 /* Increase if you have more data memory */

/// JPEG Header constants
#define _JPEG_SOF0 0xC0
#define _JPEG_DHT  0xC4
#define _JPEG_SOI  0xD8
#define _JPEG_EOI  0xD9
#define _JPEG_SOS  0xDA
#define _JPEG_DQT  0xDB
#define _JPEG_DRI  0xDD
#define _JPEG_APP0 0xE0
#define _JPEG_COM  0xFE

/* The below markers doesn't have parameters */
#define _JPEG_TEM  0x01
#define _JPEG_RST0 0xD0
#define _JPEG_RST1 0xD1
#define _JPEG_RST2 0xD2
#define _JPEG_RST3 0xD3
#define _JPEG_RST4 0xD4
#define _JPEG_RST5 0xD5
#define _JPEG_RST6 0xD6
#define _JPEG_RST7 0xD7

#define _JPEG_SAMPLE_1x1 0
#define _JPEG_SAMPLE_1x2 1
#define _JPEG_SAMPLE_2x1 2
#define _JPEG_SAMPLE_2x2 3
#endif

const uint8_t _JPEG_ZIG_ZAG_8x8[64] =
{
   0,  1,  8, 16,  9,  2,  3, 10,
  17, 24, 32, 25, 18, 11,  4,  5,
  12, 19, 26, 33, 40, 48, 41, 34,
  27, 20, 13,  6,  7, 14, 21, 28,
  35, 42, 49, 56, 57, 50, 43, 36,
  29, 22, 15, 23, 30, 37, 44, 51,
  58, 59, 52, 45, 38, 31, 39, 46,
  53, 60, 61, 54, 47, 55, 62, 63
};

#endif // JPEG_CONSTANTS_H

/// @endcond
