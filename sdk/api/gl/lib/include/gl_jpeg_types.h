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

#ifndef JPEG_TYPES_H
#define JPEG_TYPES_H

#include "gl_jpeg_constants.h"
#include "gl_types.h"

typedef struct
{
    uint8_t jfif;           /* JFIF marker found flag */
    uint8_t major_rev; /* Should be 1 */
    uint8_t minor_rev; /* Should be 0-2 but is not a show stopper */
} jpeg_decoder_app0_t;

typedef struct
{
    uint8_t  data_bits; /* Data precision, can be 8(, 12 or 16) */
    uint16_t width;     /* Width in pixels */
    uint16_t height;    /* Height in pixels */
    uint8_t  channels;  /* Number of channels e.g. YCbCr = 3 */
    uint8_t  channel_type[_JPEG_MAX_CHANNELS];
    uint8_t  channel_h_samp_factor[_JPEG_MAX_CHANNELS];
    uint8_t  channel_v_samp_factor[_JPEG_MAX_CHANNELS];
    uint8_t  channel_quant_table_map[_JPEG_MAX_CHANNELS];
} jpeg_decoder_sof0_t;

typedef struct
{
    uint8_t  quant_uses_16_bits;                               /* If flag is set, it is an error as 16 bit is not supported */
    uint16_t quant_table[_JPEG_MAX_CHANNELS][64]; /* Supports only 8 & 16 bit resolutions */
} jpeg_decoder_dqt_t;

typedef struct
{
    uint16_t restart_interval; /* The restart interval in blocks */
} jpeg_decoder_dri_t;

typedef struct
{
    uint8_t huff_tables;
    uint8_t huff_ac_symbol_len[_JPEG_MAX_HUFF_TABLES][16]; /* Supports only 8 bit resolution */
    uint8_t huff_ac_symbol[_JPEG_MAX_HUFF_TABLES][256];     /* Maximum possible symbols are 256 */
    uint8_t huff_dc_symbol_len[_JPEG_MAX_HUFF_TABLES][16]; /* Supports only 8 bit resolution */
    uint8_t huff_dc_symbol[_JPEG_MAX_HUFF_TABLES][16];      /* Maximum possible symbols are 16 for DC :-) */
} jpeg_decoder_dht_t;

typedef struct
{
    uint8_t channel_huff_ac_table_map[_JPEG_MAX_CHANNELS];
    uint8_t channel_huff_dc_table_map[_JPEG_MAX_CHANNELS];
} jpeg_decoder_sos_t;

typedef struct
{
    uint16_t huff_ac_sym_start[_JPEG_MAX_HUFF_TABLES][16]; /* Starting symbol for each length */
    uint16_t huff_dc_sym_start[_JPEG_MAX_HUFF_TABLES][16]; /* Starting symbol for each length */
} jpeg_decoder_huff_t;

typedef struct
{
    uint16_t  work_bits;
    uint8_t   bits_available;
    uint8_t   blocks_in_one_pass;
    int16_t   one_block[_JPEG_MAX_BLOCKS][64]; /* Temporary storage for a 8x8 block */
    uint16_t  block_number;
    uint8_t   channel_map[_JPEG_MAX_BLOCKS];
    uint8_t   sub_sample_type;
    int16_t   prev_dc_value[_JPEG_MAX_CHANNELS];
    uint8_t  *current_huff_symbol_len_table;
    uint8_t  *current_huff_symbol_table;
    uint16_t *current_huff_symbol_start_table;
    uint16_t *current_quant_table;
    uint8_t   data_buffer[_JPEG_MAX_DATA_BUF_LEN];
    uint16_t  buffer_len;
    uint16_t  buffer_index;
    uint8_t   first_bit;
} jpeg_work_memory_t;

typedef struct gl_jpeg_types
{
    gl_rectangle_t *dest;
    gl_rectangle_t *src;
    uint16_t drawn_x;
    uint16_t drawn_y;
    uint16_t image_offset_x;
    uint16_t image_offset_y;
} jpeg_drawing_t;


typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} jpeg_color_t;

typedef struct
{
    int16_t *y_ptr;
    int16_t *cb_ptr;
    int16_t *cr_ptr;
} jpeg_color_space_pointers_t;

// ToDo : rename jpeg errors
typedef enum
{
    GL_DRAW_IMAGE_SUCCESS = 0,
    GL_DRAW_IMAGE_UNSUPPORTED_FORMAT,
    GL_DRAW_IMAGE_ERROR,
    GL_DRAW_IMAGE_DEST_ERROR,
    GL_DRAW_IMAGE_JPEG_ERROR_1,
    GL_DRAW_IMAGE_JPEG_ERROR_2,
    GL_DRAW_IMAGE_JPEG_ERROR_3,
    GL_DRAW_IMAGE_JPEG_ERROR_4,
    GL_DRAW_IMAGE_JPEG_ERROR_5,
    GL_DRAW_IMAGE_JPEG_ERROR_6,
    GL_DRAW_IMAGE_JPEG_ERROR_7,
    GL_DRAW_IMAGE_JPEG_ERROR_8,
    GL_DRAW_IMAGE_JPEG_ERROR_9,
    GL_DRAW_IMAGE_JPEG_ERROR_10,
    GL_DRAW_IMAGE_JPEG_ERROR_11,
    GL_DRAW_IMAGE_JPEG_ERROR_12,
    GL_DRAW_IMAGE_JPEG_ERROR_13,
    GL_DRAW_IMAGE_JPEG_ERROR_14,
    GL_DRAW_IMAGE_JPEG_ERROR_15,
    GL_DRAW_IMAGE_JPEG_ERROR_16
} gl_draw_image_result_t;

typedef struct
{
    const code uint8_t * image_file_as_array;
    jpeg_decoder_app0_t    app0;
    jpeg_decoder_sof0_t    sof0;
    jpeg_decoder_dqt_t     dqt;
    jpeg_decoder_dri_t     dri;
    jpeg_decoder_dht_t     dht;
    jpeg_decoder_sos_t     sos;
    jpeg_decoder_huff_t    huff;
    jpeg_work_memory_t     work_memory;
    jpeg_drawing_t         drawing;
    gl_draw_image_result_t error;
} jpeg_decoder_t;

#endif // JPEG_TYPES_H

/// @endcond
