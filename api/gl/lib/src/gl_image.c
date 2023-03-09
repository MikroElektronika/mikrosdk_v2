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

#include "gl_image.h"
#include "gl_image_format_handlers.h"
#include "gl_jpeg_types.h"
#include "gl_utils.h"

#include <stdbool.h>
#include <string.h>
#include <stddef.h>


#define _JPEG_UNUSED 0

extern gl_t instance;

typedef struct
{
    gl_color_t color[2];
} gl_1bpp_pallete_t;

uint16_t gl_image_width(const uint8_t * image)
{
    const gl_image_header_t * header = (const gl_image_header_t *)image;

    if (image == NULL)
        return 0;

    return header->width;
}

uint16_t gl_image_height(const uint8_t * image)
{
    const gl_image_header_t * header = (const gl_image_header_t  *)image;

    if (image == NULL)
        return 0;

    return header->height;
}

gl_image_format_t gl_image_format(const uint8_t *image)
{
    const gl_image_header_t * header = (const gl_image_header_t *)image;

    if (image == NULL)
        return 0;

    return (gl_image_format_t)header->format;
}

/**
 * @brief The function initializes \p out rectangle with default values, to
 * draw whole picture, if \p in rectangle iz NULL. Otherwise it cpoies in to
 * out.
 */
void _init_source_rect(gl_rectangle_t *out, const gl_rectangle_t * __generic_ptr in, const uint8_t * image)
{
    uint32_t tmp_ptr = (uint32_t)in & 0x7FFFFF;

    if (!tmp_ptr)
    {
        out->top_left.x = 0;
        out->top_left.y = 0;
        out->width  = gl_image_width(image);
        out->height = gl_image_height(image);
    }
    else
    {
        memcpy(out, in, sizeof(gl_rectangle_t));
    }
}

/**
 * @brief The function draws 16bpp bitmap image, using Nearest-neighbor
 * interpolation.
 */
void gl_draw_bitmap_16bpp(gl_rectangle_t *dest, gl_rectangle_t *src, const uint8_t * image)
{
    const gl_int_t w = gl_image_width(image);

    gl_int_t x_cnt;
    gl_int_t y_cnt;

    const uint16_t * pixel_data = (const uint16_t *)(image + sizeof(gl_image_header_t));

    // Nearest-neighbor interpolation.
    instance.driver.begin_frame_f(dest);
    for (y_cnt = 0; y_cnt < dest->height; y_cnt++)
    {
        for (x_cnt = 0; x_cnt < dest->width; x_cnt++)
            instance.driver.frame_data_f(pixel_data[((((y_cnt * src->height) / dest->height) + src->top_left.y) * w) + (((x_cnt * src->width) / dest->width) + src->top_left.x)]);
    }
    instance.driver.end_frame_f();
}

/**
 * @brief The function draws 4bpp bitmap image, using Nearest-neighbor
 * interpolation.
 */
void gl_draw_bitmap_4bpp(gl_rectangle_t *dest, gl_rectangle_t *src, const uint8_t * image)
{
    const gl_int_t w = gl_image_width(image);

    gl_int_t x_cnt;
    gl_int_t y_cnt;
    gl_color_t color;

    uint32_t x_index;
    uint32_t y_index;

    size_t pixel_index;
    size_t pallete_index;
    size_t data_index;

    const gl_color_t * pallete = (const uint8_t *)(image + sizeof(gl_image_header_t));
    const uint8_t * pixel_data = (const uint8_t *)(image + sizeof(gl_image_header_t) + sizeof(gl_color_t) * 16);
    // Nearest-neighbor interpolation.
    instance.driver.begin_frame_f(dest);
    for (y_cnt = 0; y_cnt < dest->height; y_cnt++)
    {
        y_index = (((y_cnt * src->height) / dest->height) + src->top_left.y);
        for (x_cnt = 0; x_cnt < dest->width; x_cnt++)
        {
            x_index = (((x_cnt * src->width) / dest->width) + src->top_left.x);
            pixel_index = ((y_index * w) + x_index);
            data_index = pixel_index / 2;
            if (pixel_index % 2)
            {
                pallete_index = (size_t)pixel_data[data_index];
            }
            else
            {
                pallete_index = (size_t)pixel_data[data_index];
                pallete_index >>= 4;
            }
            pallete_index &= (size_t)0x0F;

            color = pallete[pallete_index];
            instance.driver.frame_data_f(color);
        }
    }
    instance.driver.end_frame_f();
}
/**
 * @brief The function draws 8bpp bitmap image, using Nearest-neighbor
 * interpolation.
 */
void gl_draw_bitmap_8bpp(gl_rectangle_t *dest, gl_rectangle_t *src, const uint8_t * image)
{
    const gl_int_t w = gl_image_width(image);

    gl_int_t x_cnt;
    gl_int_t y_cnt;

    uint32_t pixel_index;
    uint32_t x_index;
    uint32_t y_index;

    const gl_color_t * pallete = (const uint8_t *)(image + sizeof(gl_image_header_t));
    const uint8_t * pixel_data = (const uint8_t *)(image + sizeof(gl_image_header_t) + sizeof(gl_color_t) * 256);

    // Nearest-neighbor interpolation.
    instance.driver.begin_frame_f(dest);
    for (y_cnt = 0; y_cnt < dest->height; y_cnt++)
    {
        y_index = (((y_cnt * src->height) / dest->height) + src->top_left.y);
        for (x_cnt = 0; x_cnt < dest->width; x_cnt++)
        {
            x_index = (((x_cnt * src->width) / dest->width) + src->top_left.x);
            pixel_index = (y_index * w) + x_index;
            instance.driver.frame_data_f(pallete[pixel_data[pixel_index]]);
        }
    }
    instance.driver.end_frame_f();
}

/**
 * @brief The function draws 1bpp bitmap image, using Nearest-neighbor
 * interpolation.
 */
void gl_draw_bitmap_1bpp(gl_rectangle_t *dest, gl_rectangle_t *src, const uint8_t * image)
{
    const gl_int_t w = gl_image_width(image) / 8 + 1;

    gl_int_t x_cnt;
    gl_int_t y_cnt;

    uint32_t pixel_index;
    uint32_t x_index;
    uint32_t y_index;

    const gl_1bpp_pallete_t * pallete = (const gl_1bpp_pallete_t *)(image + sizeof(gl_image_header_t));
    const uint8_t * pixel_data = (const uint8_t *)(image + sizeof(gl_image_header_t) + sizeof(gl_1bpp_pallete_t));

    // Nearest-neighbor interpolation.
    instance.driver.begin_frame_f(dest);
    for (y_cnt = 0; y_cnt < dest->height; y_cnt++)
    {
        y_index = (((y_cnt * src->height) / dest->height) + src->top_left.y);
        for (x_cnt = 0; x_cnt < dest->width; x_cnt++)
        {
            x_index = (((x_cnt * src->width) / dest->width) + src->top_left.x);
            pixel_index = (y_index * w) + x_index / 8;
            if (pixel_data[pixel_index] & (0x80 >> (x_index % 8)))
               instance.driver.frame_data_f(pallete->color[1]);
            else
               instance.driver.frame_data_f(pallete->color[0]);
        }
    }
    instance.driver.end_frame_f();
}

// TODO: Change return value to enum which contains error message.
int gl_draw_image(gl_rectangle_t *dest, gl_rectangle_t *src1, const uint8_t * image)
{
    gl_int_t cut_len_dest;
    gl_int_t cut_len_src;
    gl_rectangle_t src;
    const gl_image_header_t * header = (const gl_image_header_t *)image;

    if (image == NULL || instance.driver.fill_f == NULL)
        return GL_DRAW_IMAGE_ERROR;

    if (!dest || dest->width == 0 || dest->height == 0 ||
        dest->top_left.x >= instance.driver.display_width ||
        dest->top_left.y >= instance.driver.display_height ||
        dest->top_left.x + dest->width < 0 ||
        dest->top_left.y + dest->height < 0)
        return GL_DRAW_IMAGE_DEST_ERROR;

    _init_source_rect(&src, src1, image);

    if (header->format != GL_IMAGE_FORMAT_JPEG)
    {
        if (dest->top_left.x < 0)
        {
            cut_len_dest = 0 - dest->top_left.x;
            cut_len_src =  (src.width * cut_len_dest) / dest->width;
            dest->top_left.x = 0;
            src.top_left.x += cut_len_src;
            dest->width -= cut_len_dest;
            src.width -= cut_len_src;
        }

        if (dest->top_left.x + dest->width > instance.driver.display_width)
        {
            cut_len_dest = dest->top_left.x + dest->width - instance.driver.display_width;
            cut_len_src = (src.width * cut_len_dest) / dest->width;
            dest->width -= cut_len_dest;
            src.width -= cut_len_src;
        }

        if (dest->top_left.y < 0)
        {
            cut_len_dest = - dest->top_left.y;
            cut_len_src = (src.height * cut_len_dest) / dest->height;
            dest->top_left.y = 0;
            dest->height -= cut_len_dest;
            src.top_left.y += cut_len_src;
            src.height -= cut_len_src;
        }

        if (dest->top_left.y + dest->height > instance.driver.display_height)
        {
            cut_len_dest = dest->top_left.y + dest->height - instance.driver.display_height;
            cut_len_src = (src.height * cut_len_dest) / dest->height ;
            dest->height -= cut_len_dest;
            src.height -= cut_len_src;
        }
    }

    switch(header->format)
    {
    case GL_IMAGE_FORMAT_BITMAP_16BPP:
        gl_draw_bitmap_16bpp(dest, &src, image);
        break;
    case GL_IMAGE_FORMAT_BITMAP_4BPP:
        gl_draw_bitmap_4bpp(dest, &src, image);
        break;
    case GL_IMAGE_FORMAT_BITMAP_8BPP:
        gl_draw_bitmap_8bpp(dest, &src, image);
        break;
    case GL_IMAGE_FORMAT_BITMAP_1BPP:
        gl_draw_bitmap_1bpp(dest, &src, image);
        break;
    case GL_IMAGE_FORMAT_JPEG:
        gl_draw_jpeg_image(dest, &src, image);
    default:
        return GL_DRAW_IMAGE_UNSUPPORTED_FORMAT;
    }

    return GL_DRAW_IMAGE_SUCCESS;
}

static const uint8_t * _jpeg_image_read_ptr;
static jpeg_decoder_t _jpeg_decoder;
static jpeg_color_space_pointers_t _jpeg_color_space_ptr;

static uint8_t _jpeg_file_read_bytes(uint8_t *buffer, uint32_t cnt)
{
    memcpy(buffer, _jpeg_image_read_ptr, cnt);
    _jpeg_image_read_ptr += cnt;
    return cnt;
}

static void _jpeg_file_read(uint8_t *buffer, uint8_t read_size, uint32_t cnt)
{
    int8_t i;

    while (cnt > 0)
    {
        for (i = read_size - 1; i >= 0; i--)
        {
            *(buffer + i) = *_jpeg_image_read_ptr;
            _jpeg_image_read_ptr++;
        }
        buffer = buffer + read_size;
        cnt--;
    }
}

static void _jpeg_set_decoder()
{
    if (_jpeg_decoder.sof0.channels == 1)
    {
        _jpeg_decoder.work_memory.blocks_in_one_pass = 1;
        _jpeg_decoder.work_memory.sub_sample_type = _JPEG_SAMPLE_1x1;
    }
    else if (_jpeg_decoder.sof0.channels == 3)
    {
        if ((_jpeg_decoder.sof0.channel_h_samp_factor[0] == 1 && _jpeg_decoder.sof0.channel_v_samp_factor[0] == 1) &&
            (_jpeg_decoder.sof0.channel_h_samp_factor[1] == 1 && _jpeg_decoder.sof0.channel_v_samp_factor[1] == 1) &&
            (_jpeg_decoder.sof0.channel_h_samp_factor[2] == 1 && _jpeg_decoder.sof0.channel_v_samp_factor[2] == 1))
        {
            _jpeg_decoder.work_memory.blocks_in_one_pass = 3;
            _jpeg_decoder.work_memory.channel_map[0] = 0;
            _jpeg_decoder.work_memory.channel_map[1] = 1;
            _jpeg_decoder.work_memory.channel_map[2] = 2;
            _jpeg_decoder.work_memory.sub_sample_type = _JPEG_SAMPLE_1x1;
        }
        else if ((_jpeg_decoder.sof0.channel_h_samp_factor[0] == 1 && _jpeg_decoder.sof0.channel_v_samp_factor[0] == 2) &&
                ( _jpeg_decoder.sof0.channel_h_samp_factor[1] == 1 && _jpeg_decoder.sof0.channel_v_samp_factor[1] == 1) &&
                ( _jpeg_decoder.sof0.channel_h_samp_factor[2] == 1 && _jpeg_decoder.sof0.channel_v_samp_factor[2] == 1))
        {
            _jpeg_decoder.work_memory.blocks_in_one_pass = 4;
            _jpeg_decoder.work_memory.channel_map[0] = 0;
            _jpeg_decoder.work_memory.channel_map[1] = 0;
            _jpeg_decoder.work_memory.channel_map[2] = 1;
            _jpeg_decoder.work_memory.channel_map[3] = 2;
            _jpeg_decoder.work_memory.sub_sample_type = _JPEG_SAMPLE_1x2;
        }
        else if ((_jpeg_decoder.sof0.channel_h_samp_factor[0] == 2 && _jpeg_decoder.sof0.channel_v_samp_factor[0] == 1) &&
                ( _jpeg_decoder.sof0.channel_h_samp_factor[1] == 1 && _jpeg_decoder.sof0.channel_v_samp_factor[1] == 1) &&
                ( _jpeg_decoder.sof0.channel_h_samp_factor[2] == 1 && _jpeg_decoder.sof0.channel_v_samp_factor[2] == 1))
        {
            _jpeg_decoder.work_memory.blocks_in_one_pass = 4;
            _jpeg_decoder.work_memory.channel_map[0] = 0;
            _jpeg_decoder.work_memory.channel_map[1] = 0;
            _jpeg_decoder.work_memory.channel_map[2] = 1;
            _jpeg_decoder.work_memory.channel_map[3] = 2;
            _jpeg_decoder.work_memory.sub_sample_type = _JPEG_SAMPLE_2x1;
        }
        else if ((_jpeg_decoder.sof0.channel_h_samp_factor[0] == 2 && _jpeg_decoder.sof0.channel_v_samp_factor[0] == 2) &&
                ( _jpeg_decoder.sof0.channel_h_samp_factor[1] == 1 && _jpeg_decoder.sof0.channel_v_samp_factor[1] == 1) &&
                ( _jpeg_decoder.sof0.channel_h_samp_factor[2] == 1 && _jpeg_decoder.sof0.channel_v_samp_factor[2] == 1))
        {
            _jpeg_decoder.work_memory.blocks_in_one_pass = 6;
            _jpeg_decoder.work_memory.channel_map[0] = 0;
            _jpeg_decoder.work_memory.channel_map[1] = 0;
            _jpeg_decoder.work_memory.channel_map[2] = 0;
            _jpeg_decoder.work_memory.channel_map[3] = 0;
            _jpeg_decoder.work_memory.channel_map[4] = 1;
            _jpeg_decoder.work_memory.channel_map[5] = 2;
            _jpeg_decoder.work_memory.sub_sample_type = _JPEG_SAMPLE_2x2;
        }
        else
        {
            _jpeg_decoder.error = GL_DRAW_IMAGE_JPEG_ERROR_1;
        }
    }
    return;
}

static void _jpeg_read_header()
{
    uint8_t sos_over = 0;
    uint8_t eof_detected = 0;
    uint8_t temp;
    uint8_t i;
    uint8_t section;
    uint16_t seg_len;
    uint16_t offset;
    uint8_t q_table_index;
    uint8_t counter;
    uint8_t data_1;
    uint8_t data_2;
    uint8_t h_table_index;
    uint16_t num_of_symbols;
    uint8_t is_ac;
    uint8_t *len_table;
    uint8_t *sym_table;
    uint8_t channel_id;

    while (eof_detected == 0)
    {
        if (sos_over == 1)
        {
            _jpeg_set_decoder();
            return;
        }

        _jpeg_file_read(&temp, sizeof(temp), 1);
        if (temp != 0xFF)
            continue;

        _jpeg_file_read(&section, sizeof(section), 1);
        switch (section)
        {
            case _JPEG_SOI:
            case _JPEG_TEM:
            case _JPEG_RST0:
            case _JPEG_RST1:
            case _JPEG_RST2:
            case _JPEG_RST3:
            case _JPEG_RST4:
            case _JPEG_RST5:
            case _JPEG_RST6:
            case _JPEG_RST7:
                break;

            case _JPEG_EOI:
                eof_detected = 1;
                break;

            case _JPEG_SOF0:
                _jpeg_file_read(&seg_len, sizeof(seg_len), 1);
                if (seg_len <= 8)
                {
                    _jpeg_decoder.error = GL_DRAW_IMAGE_JPEG_ERROR_2;
                    break;
                }
                _jpeg_file_read(&_jpeg_decoder.sof0.data_bits, sizeof(_jpeg_decoder.sof0.data_bits), 1);
                _jpeg_file_read(&_jpeg_decoder.sof0.height, sizeof(_jpeg_decoder.sof0.height), 1);
                _jpeg_file_read(&_jpeg_decoder.sof0.width, sizeof(_jpeg_decoder.sof0.width), 1);
                _jpeg_file_read(&_jpeg_decoder.sof0.channels, sizeof(_jpeg_decoder.sof0.channels), 1);
                if (seg_len < 8 + (_jpeg_decoder.sof0.channels * 3))
                {
                    _jpeg_decoder.error = GL_DRAW_IMAGE_JPEG_ERROR_3;
                    break;
                }
                for (i = 0; i < _jpeg_decoder.sof0.channels; i++)
                {
                    _jpeg_file_read(&_jpeg_decoder.sof0.channel_type[i], sizeof(uint8_t), 1);
                    _jpeg_file_read(&temp, sizeof(temp), 1);
                    _jpeg_decoder.sof0.channel_h_samp_factor[i] = temp >> 4;
                    _jpeg_decoder.sof0.channel_v_samp_factor[i] = temp & 0x0F;
                    _jpeg_file_read(&_jpeg_decoder.sof0.channel_quant_table_map[i], sizeof(uint8_t), 1);
                }
                break;

            case _JPEG_APP0:
                _jpeg_file_read(&seg_len, sizeof(seg_len), 1);
                if (seg_len < 16)
                {
                    _jpeg_decoder.error = GL_DRAW_IMAGE_JPEG_ERROR_4;
                    break;
                }
                else
                {
                    uint8_t buf[5];
                    _jpeg_file_read(buf, sizeof(uint8_t), 5);
                    if (buf[0] == 'J' && buf[1] == 'F' && buf[2] == 'I' && buf[3] == 'F' && buf[4] == '\0')
                        _jpeg_decoder.app0.jfif = 1;
                }
                _jpeg_file_read(&_jpeg_decoder.app0.major_rev, sizeof(_jpeg_decoder.app0.major_rev), 1);
                _jpeg_file_read(&_jpeg_decoder.app0.minor_rev, sizeof(_jpeg_decoder.app0.minor_rev), 1);
                if (_jpeg_decoder.app0.major_rev != 1)
                {
                    _jpeg_decoder.error = GL_DRAW_IMAGE_JPEG_ERROR_5;
                    break;
                }

                break;

            case _JPEG_DRI:
                _jpeg_file_read(&seg_len, sizeof(seg_len), 1);
                if (seg_len == 4)
                    _jpeg_file_read(&_jpeg_decoder.dri.restart_interval, sizeof(_jpeg_decoder.dri.restart_interval), 1);
                break;

            case _JPEG_DQT:
                _jpeg_file_read(&seg_len, sizeof(seg_len), 1);
                if (seg_len < 67)
                {
                    _jpeg_decoder.error = GL_DRAW_IMAGE_JPEG_ERROR_6;
                    break;
                }

                do
                {
                    _jpeg_file_read(&temp, sizeof(temp), 1);
                    q_table_index = temp & 0x0F;
                    _jpeg_decoder.dqt.quant_uses_16_bits = _jpeg_decoder.dqt.quant_uses_16_bits | (temp >> 4);

                    for (i = 0; i < 64; i++)
                    {
                        data_1 = 0;
                        data_2 = 0;
                        if (_jpeg_decoder.dqt.quant_uses_16_bits == 0)
                        {
                            _jpeg_file_read(&data_1, sizeof(data_1), 1);
                            _jpeg_decoder.dqt.quant_table[q_table_index][_JPEG_ZIG_ZAG_8x8[i]] = data_1;
                        }
                        else
                        {
                            _jpeg_file_read(&data_1, sizeof(data_1), 1);
                            _jpeg_file_read(&data_2, sizeof(data_1), 1);
                            _jpeg_decoder.dqt.quant_table[q_table_index][_JPEG_ZIG_ZAG_8x8[i]] = (((uint16_t) data_1) << 8) + data_2;
                        }
                    }
                    seg_len -= (_jpeg_decoder.dqt.quant_uses_16_bits == 0) ? 65 : 129;
                } while (seg_len >= 67);
                break;

            case _JPEG_DHT:
                _jpeg_file_read(&seg_len, sizeof(seg_len), 1);
                if (seg_len < 19)
                {
                    _jpeg_decoder.error = GL_DRAW_IMAGE_JPEG_ERROR_7;
                    break;
                }

                do
                {
                    _jpeg_file_read(&temp, sizeof(temp), 1);
                    h_table_index = temp & 0x0F;
                    is_ac = (temp >> 4) & 0x01;

                    if (is_ac == 0)
                    {
                        len_table = (uint8_t*) &_jpeg_decoder.dht.huff_dc_symbol_len[h_table_index][0];
                        sym_table = (uint8_t*) &_jpeg_decoder.dht.huff_dc_symbol[h_table_index][0];
                    }
                    else
                    {
                        len_table = (uint8_t*) &_jpeg_decoder.dht.huff_ac_symbol_len[h_table_index][0];
                        sym_table = (uint8_t*) &_jpeg_decoder.dht.huff_ac_symbol[h_table_index][0];
                    }

                    _jpeg_file_read(len_table, sizeof(uint8_t), 16);

                    for (i = 0, num_of_symbols = 0; i < 16; i++)
                        num_of_symbols += len_table[i];

                    seg_len -= 17;

                    if (seg_len < num_of_symbols || (is_ac == 1 && num_of_symbols > 256) || (is_ac == 0 && num_of_symbols > 16))
                    {
                        _jpeg_decoder.error = GL_DRAW_IMAGE_JPEG_ERROR_8;
                        break;
                    }

                    _jpeg_file_read(sym_table, sizeof(uint8_t), num_of_symbols);
                    seg_len -= num_of_symbols;
                    _jpeg_decoder.dht.huff_tables++;
                } while (seg_len >= 19);
                break;

            case _JPEG_SOS:
                _jpeg_file_read(&seg_len, sizeof(seg_len), 1);
                if (seg_len < 3)
                {
                    _jpeg_decoder.error = GL_DRAW_IMAGE_JPEG_ERROR_9;
                    break;
                }

                _jpeg_file_read(&temp, sizeof(temp), 1);
                offset = seg_len - (3 + (temp * 2));

                if (_jpeg_decoder.sof0.channels != temp || seg_len < 3 + (temp * 2))
                {
                    _jpeg_decoder.error = GL_DRAW_IMAGE_JPEG_ERROR_10;
                    break;
                }
                else
                {
                    channel_id = 0xFF;

                    for (counter = 0; counter < _jpeg_decoder.sof0.channels; counter++)
                    {
                        _jpeg_file_read(&temp, sizeof(temp), 1);
                        for (i = 0; i < _JPEG_MAX_CHANNELS; i++)
                        {
                            if (_jpeg_decoder.sof0.channel_type[i] == temp)
                            {
                                channel_id = i;
                                break;
                            }
                        }

                        if (channel_id < _JPEG_MAX_CHANNELS)
                        {
                            _jpeg_file_read(&temp, sizeof(temp), 1);
                            _jpeg_decoder.sos.channel_huff_ac_table_map[channel_id] = temp & 0x0F;
                            _jpeg_decoder.sos.channel_huff_dc_table_map[channel_id] = temp >> 4;
                        }
                    }
                    _jpeg_image_read_ptr = _jpeg_image_read_ptr + offset;
                }
                sos_over = 1;
                break;

            default:
                _jpeg_file_read(&seg_len, sizeof(seg_len), 1);
                if (seg_len < 2)
                {
                    _jpeg_decoder.error = GL_DRAW_IMAGE_JPEG_ERROR_11;
                    break;
                }
                _jpeg_image_read_ptr = _jpeg_image_read_ptr + seg_len - 2;
        }
    }
}

static void _jpeg_generate_huffman_tables()
{
    uint8_t length;
    uint8_t table;
    uint8_t tmp = _jpeg_decoder.dht.huff_tables / 2;

    for (table = 0; table < tmp; table++)
    {
        _jpeg_decoder.huff.huff_ac_sym_start[table][0] = 0;
        _jpeg_decoder.huff.huff_dc_sym_start[table][0] = 0;

        for (length = 1; length < 16; length++)
        {
            _jpeg_decoder.huff.huff_ac_sym_start[table][length] = (_jpeg_decoder.huff.huff_ac_sym_start[table][length - 1] + _jpeg_decoder.dht.huff_ac_symbol_len[table][length - 1]) << 1;
            _jpeg_decoder.huff.huff_dc_sym_start[table][length] = (_jpeg_decoder.huff.huff_dc_sym_start[table][length - 1] + _jpeg_decoder.dht.huff_dc_symbol_len[table][length - 1]) << 1;
        }
    }
}

static uint8_t _jpeg_get_bit()
{
    uint8_t result = 0;

    if (_jpeg_decoder.work_memory.buffer_index >= _jpeg_decoder.work_memory.buffer_len)
    {
        _jpeg_decoder.work_memory.buffer_len = _jpeg_file_read_bytes(&(_jpeg_decoder.work_memory.data_buffer[0]), _JPEG_MAX_DATA_BUF_LEN);
        while (_jpeg_decoder.work_memory.data_buffer[_jpeg_decoder.work_memory.buffer_len - 1] == 0xFF)
        {
            _jpeg_decoder.work_memory.buffer_len--;
            _jpeg_image_read_ptr = _jpeg_image_read_ptr - 1;
        }
        _jpeg_decoder.work_memory.buffer_index = 0;
    }

    while (_jpeg_decoder.work_memory.bits_available == 0)
    {
        _jpeg_decoder.work_memory.bits_available = 16;
        _jpeg_decoder.work_memory.work_bits = _jpeg_decoder.work_memory.data_buffer[_jpeg_decoder.work_memory.buffer_index++];
        _jpeg_decoder.work_memory.work_bits = (_jpeg_decoder.work_memory.work_bits << 8) + _jpeg_decoder.work_memory.data_buffer[_jpeg_decoder.work_memory.buffer_index++];

        if (_jpeg_decoder.work_memory.buffer_index > _jpeg_decoder.work_memory.buffer_len)
        {
            _jpeg_decoder.work_memory.bits_available = 8;
        }
        else if ((_jpeg_decoder.work_memory.work_bits & 0x00FF) == 0x00FF)
        {
            _jpeg_decoder.work_memory.bits_available = 8;
            _jpeg_decoder.work_memory.buffer_index--;
        }
        else if (_jpeg_decoder.work_memory.work_bits >= 0xFF00)
        {
            if (_jpeg_decoder.work_memory.work_bits == 0xFF00)
                _jpeg_decoder.work_memory.bits_available = 8;
        }
    }

    result = (_jpeg_decoder.work_memory.work_bits & 0x8000) ? 0x01 : 0;

    _jpeg_decoder.work_memory.work_bits <<= 1;
    _jpeg_decoder.work_memory.bits_available--;

    return result;
}

static uint16_t _jpeg_get_n_bits(uint8_t cnt)
{
    uint16_t result = 0;

    _jpeg_decoder.work_memory.first_bit = _jpeg_get_bit();

    result = _jpeg_decoder.work_memory.first_bit;
    cnt--;

    while (cnt--)
        result = (result << 1) + _jpeg_get_bit();

    return result;
}

static uint16_t _jpeg_get_restart_word()
{
    while (_jpeg_decoder.work_memory.bits_available & 0x07)
        _jpeg_get_bit();

    return _jpeg_get_n_bits(16);
}

static uint8_t _jpeg_get_next_huffman_byte()
{
    uint8_t  bits          = 0;
    uint8_t  symbol        = 0;
    uint8_t  symbols       = 0;
    uint16_t bit_pattern   = 0;
    uint16_t symbol_offset = 0;
    uint16_t diff          = 0;

    for (bits = 0; bits < 16; bits++)
    {
        bit_pattern = (bit_pattern << 1) + _jpeg_get_bit();
        symbols = _jpeg_decoder.work_memory.current_huff_symbol_len_table[bits];
        if (symbols == 0)
            continue;

        diff = bit_pattern - _jpeg_decoder.work_memory.current_huff_symbol_start_table[bits];
        if (diff < symbols)
        {
            symbol = _jpeg_decoder.work_memory.current_huff_symbol_table[symbol_offset + diff];
            break;
        }
        symbol_offset += symbols;
    }

    return symbol;
}

static int16_t _jpeg_get_n_bits_value(uint8_t cnt)
{
    uint16_t result = 0;

    if (cnt)
    {
        result = _jpeg_get_n_bits(cnt);
        if (_jpeg_decoder.work_memory.first_bit == 0)
        {
            result = ~(result | (0xFFFF << cnt));
            return ((int16_t) result * -1);
        }
    }

    return result;
}

static int32_t _jpeg_unscale_value(int32_t x, int32_t n)
{
    return ((x) + ((int32_t) 0x01 << ((n) - 1))) >> (n);
}

static int8_t _jpeg_to_signed_char_range(int16_t x)
{
    if (x < -128)
        return -128;
    else if (x > 127)
        return 127;
    else
        return x;
}

static uint8_t _jpeg_to_char_range(int16_t x)
{
    if (x < 0)
        return 0;
    else if (x > 255)
        return 255;
    else
        return x;
}

static void _jpeg_inverse_dct(int16_t *in_buf, uint16_t *quant_ptr)
{
    const uint8_t DCT_SIZE       = 8;
    const uint8_t DCT_BLOCK_SIZE = 64;
    const uint8_t PASS1_BITS     = 2;
    const uint8_t CONST_BITS     = 13;
    const int32_t C_0_298631336  = 2446;
    const int32_t C_0_390180644  = 3196;
    const int32_t C_0_541196100  = 4433;
    const int32_t C_0_765366865  = 6270;
    const int32_t C_0_899976223  = 7373;
    const int32_t C_1_175875602  = 9633;
    const int32_t C_1_501321110  = 12299;
    const int32_t C_1_847759065  = 15137;
    const int32_t C_1_961570560  = 16069;
    const int32_t C_2_053119869  = 16819;
    const int32_t C_2_562915447  = 20995;
    const int32_t C_3_072711026  = 25172;

    int32_t tmp0;
    int32_t tmp1;
    int32_t tmp2;
    int32_t tmp3;
    int32_t tmp10;
    int32_t tmp11;
    int32_t tmp12;
    int32_t tmp13;
    int32_t z1;
    int32_t z2;
    int32_t z3;
    int32_t z4;
    int32_t z5;

    uint8_t i;
    int16_t *in_ptr;
    int16_t *out_ptr;
    int32_t *ws_ptr;
    int32_t workspace[DCT_BLOCK_SIZE];

    int32_t dc_val;

    in_ptr = in_buf;
    ws_ptr = workspace;

    for (i = 0; i < DCT_SIZE; i++)
    {
        if (in_ptr[DCT_SIZE * 1] == 0 && in_ptr[DCT_SIZE * 2] == 0 &&
            in_ptr[DCT_SIZE * 3] == 0 && in_ptr[DCT_SIZE * 4] == 0 &&
            in_ptr[DCT_SIZE * 5] == 0 && in_ptr[DCT_SIZE * 6] == 0 &&
            in_ptr[DCT_SIZE * 7] == 0)
        {
            dc_val = ((uint32_t) in_ptr[DCT_SIZE * 0] * quant_ptr[DCT_SIZE * 0]) << PASS1_BITS;

            ws_ptr[DCT_SIZE * 0] = dc_val;
            ws_ptr[DCT_SIZE * 1] = dc_val;
            ws_ptr[DCT_SIZE * 2] = dc_val;
            ws_ptr[DCT_SIZE * 3] = dc_val;
            ws_ptr[DCT_SIZE * 4] = dc_val;
            ws_ptr[DCT_SIZE * 5] = dc_val;
            ws_ptr[DCT_SIZE * 6] = dc_val;
            ws_ptr[DCT_SIZE * 7] = dc_val;

            in_ptr++;
            quant_ptr++;
            ws_ptr++;
            continue;
        }

        z2 = (uint32_t) in_ptr[DCT_SIZE * 2] * quant_ptr[DCT_SIZE * 2];
        z3 = (uint32_t) in_ptr[DCT_SIZE * 6] * quant_ptr[DCT_SIZE * 6];

        z1 = (int32_t) (z2 + z3) * C_0_541196100;
        tmp2 = z1 + (int32_t) (z3) * (-C_1_847759065);
        tmp3 = z1 + (int32_t) (z2) * C_0_765366865;

        z2 = (uint32_t) in_ptr[DCT_SIZE * 0] * quant_ptr[DCT_SIZE * 0];
        z3 = (uint32_t) in_ptr[DCT_SIZE * 4] * quant_ptr[DCT_SIZE * 4];

        tmp0 = (z2 + z3) << CONST_BITS;
        tmp1 = (z2 - z3) << CONST_BITS;

        tmp10 = tmp0 + tmp3;
        tmp13 = tmp0 - tmp3;
        tmp11 = tmp1 + tmp2;
        tmp12 = tmp1 - tmp2;

        tmp0 = (uint32_t) in_ptr[DCT_SIZE * 7] * quant_ptr[DCT_SIZE * 7];
        tmp1 = (uint32_t) in_ptr[DCT_SIZE * 5] * quant_ptr[DCT_SIZE * 5];
        tmp2 = (uint32_t) in_ptr[DCT_SIZE * 3] * quant_ptr[DCT_SIZE * 3];
        tmp3 = (uint32_t) in_ptr[DCT_SIZE * 1] * quant_ptr[DCT_SIZE * 1];

        z1 = tmp0 + tmp3;
        z2 = tmp1 + tmp2;
        z3 = tmp0 + tmp2;
        z4 = tmp1 + tmp3;
        z5 = (int32_t) (z3 + z4) * C_1_175875602;

        tmp0 = (int32_t) (tmp0) * C_0_298631336;
        tmp1 = (int32_t) (tmp1) * C_2_053119869;
        tmp2 = (int32_t) (tmp2) * C_3_072711026;
        tmp3 = (int32_t) (tmp3) * C_1_501321110;
        z1 = (int32_t) (z1) * (-C_0_899976223);
        z2 = (int32_t) (z2) * (-C_2_562915447);
        z3 = (int32_t) (z3) * (-C_1_961570560);
        z4 = (int32_t) (z4) * (-C_0_390180644);

        z3 += z5;
        z4 += z5;

        tmp0 += z1 + z3;
        tmp1 += z2 + z4;
        tmp2 += z2 + z3;
        tmp3 += z1 + z4;

        ws_ptr[DCT_SIZE * 0] = (int32_t) _jpeg_unscale_value((tmp10 + tmp3), (CONST_BITS - PASS1_BITS));
        ws_ptr[DCT_SIZE * 7] = (int32_t) _jpeg_unscale_value((tmp10 - tmp3), (CONST_BITS - PASS1_BITS));
        ws_ptr[DCT_SIZE * 1] = (int32_t) _jpeg_unscale_value((tmp11 + tmp2), (CONST_BITS - PASS1_BITS));
        ws_ptr[DCT_SIZE * 6] = (int32_t) _jpeg_unscale_value((tmp11 - tmp2), (CONST_BITS - PASS1_BITS));
        ws_ptr[DCT_SIZE * 2] = (int32_t) _jpeg_unscale_value((tmp12 + tmp1), (CONST_BITS - PASS1_BITS));
        ws_ptr[DCT_SIZE * 5] = (int32_t) _jpeg_unscale_value((tmp12 - tmp1), (CONST_BITS - PASS1_BITS));
        ws_ptr[DCT_SIZE * 3] = (int32_t) _jpeg_unscale_value((tmp13 + tmp0), (CONST_BITS - PASS1_BITS));
        ws_ptr[DCT_SIZE * 4] = (int32_t) _jpeg_unscale_value((tmp13 - tmp0), (CONST_BITS - PASS1_BITS));

        in_ptr++;
        quant_ptr++;
        ws_ptr++;
    }

    ws_ptr = workspace;
    out_ptr = &in_buf[0];
    for (i = 0; i < DCT_SIZE; i++)
    {
        z2 = (int32_t) ws_ptr[2];
        z3 = (int32_t) ws_ptr[6];

        z1 = (int32_t) (z2 + z3) * C_0_541196100;
        tmp2 = z1 + (int32_t) (z3) * (-C_1_847759065);
        tmp3 = z1 + (int32_t) (z2) * C_0_765366865;

        tmp0 = ((int32_t) ws_ptr[0] + (int32_t) ws_ptr[4]) << CONST_BITS;
        tmp1 = ((int32_t) ws_ptr[0] - (int32_t) ws_ptr[4]) << CONST_BITS;

        tmp10 = tmp0 + tmp3;
        tmp13 = tmp0 - tmp3;
        tmp11 = tmp1 + tmp2;
        tmp12 = tmp1 - tmp2;

        tmp0 = (int32_t) ws_ptr[7];
        tmp1 = (int32_t) ws_ptr[5];
        tmp2 = (int32_t) ws_ptr[3];
        tmp3 = (int32_t) ws_ptr[1];

        z1 = tmp0 + tmp3;
        z2 = tmp1 + tmp2;
        z3 = tmp0 + tmp2;
        z4 = tmp1 + tmp3;
        z5 = (int32_t) (z3 + z4) * C_1_175875602;

        tmp0 = (int32_t) (tmp0) * C_0_298631336;
        tmp1 = (int32_t) (tmp1) * C_2_053119869;
        tmp2 = (int32_t) (tmp2) * C_3_072711026;
        tmp3 = (int32_t) (tmp3) * C_1_501321110;
        z1 = (int32_t) (z1) * (-C_0_899976223);
        z2 = (int32_t) (z2) * (-C_2_562915447);
        z3 = (int32_t) (z3) * (-C_1_961570560);
        z4 = (int32_t) (z4) * (-C_0_390180644);

        z3 += z5;
        z4 += z5;

        tmp0 += z1 + z3;
        tmp1 += z2 + z4;
        tmp2 += z2 + z3;
        tmp3 += z1 + z4;

        out_ptr[0] = (int16_t) _jpeg_to_signed_char_range((int32_t) _jpeg_unscale_value(tmp10 + tmp3, CONST_BITS + PASS1_BITS + 3));
        out_ptr[7] = (int16_t) _jpeg_to_signed_char_range((int32_t) _jpeg_unscale_value(tmp10 - tmp3, CONST_BITS + PASS1_BITS + 3));
        out_ptr[1] = (int16_t) _jpeg_to_signed_char_range((int32_t) _jpeg_unscale_value(tmp11 + tmp2, CONST_BITS + PASS1_BITS + 3));
        out_ptr[6] = (int16_t) _jpeg_to_signed_char_range((int32_t) _jpeg_unscale_value(tmp11 - tmp2, CONST_BITS + PASS1_BITS + 3));
        out_ptr[2] = (int16_t) _jpeg_to_signed_char_range((int32_t) _jpeg_unscale_value(tmp12 + tmp1, CONST_BITS + PASS1_BITS + 3));
        out_ptr[5] = (int16_t) _jpeg_to_signed_char_range((int32_t) _jpeg_unscale_value(tmp12 - tmp1, CONST_BITS + PASS1_BITS + 3));
        out_ptr[3] = (int16_t) _jpeg_to_signed_char_range((int32_t) _jpeg_unscale_value(tmp13 + tmp0, CONST_BITS + PASS1_BITS + 3));
        out_ptr[4] = (int16_t) _jpeg_to_signed_char_range((int32_t) _jpeg_unscale_value(tmp13 - tmp0, CONST_BITS + PASS1_BITS + 3));

        out_ptr += DCT_SIZE;
        ws_ptr  += DCT_SIZE;
    }
}

static void _jpeg_set_next_decoding_block_point()
{
    switch(_jpeg_decoder.work_memory.sub_sample_type)
    {
        case _JPEG_SAMPLE_1x1:
            _jpeg_decoder.drawing.image_offset_x += 8;

            if (_jpeg_decoder.drawing.image_offset_x >= _jpeg_decoder.sof0.width)
            {
                _jpeg_decoder.drawing.image_offset_x = 0;
                _jpeg_decoder.drawing.image_offset_y += 8;
            }
            break;
        case _JPEG_SAMPLE_1x2:
            _jpeg_decoder.drawing.image_offset_x += 8;

            if (_jpeg_decoder.drawing.image_offset_x >= _jpeg_decoder.sof0.width)
            {
                _jpeg_decoder.drawing.image_offset_x = 0;
                _jpeg_decoder.drawing.image_offset_y += 16;
            }
            break;
        case _JPEG_SAMPLE_2x1:
            _jpeg_decoder.drawing.image_offset_x += 16;

            if (_jpeg_decoder.drawing.image_offset_x >= _jpeg_decoder.sof0.width)
            {
                _jpeg_decoder.drawing.image_offset_x = 0;
                _jpeg_decoder.drawing.image_offset_y += 8;
            }
            break;
        case _JPEG_SAMPLE_2x2:
            _jpeg_decoder.drawing.image_offset_x += 16;

            if (_jpeg_decoder.drawing.image_offset_x >= _jpeg_decoder.sof0.width)
            {
                _jpeg_decoder.drawing.image_offset_x = 0;
                _jpeg_decoder.drawing.image_offset_y += 16;
            }
            break;
        default :
            _jpeg_decoder.error = GL_DRAW_IMAGE_JPEG_ERROR_16;
    }
}

static void _jpeg_decode_block()
{
    uint8_t block;
    uint8_t i;
    uint8_t byte_count;
    uint8_t huff_byte;
    uint16_t restart_word;
    uint8_t index;

    for (block = 0; block < _jpeg_decoder.work_memory.blocks_in_one_pass; block++)
    {
        if ((_jpeg_decoder.dri.restart_interval > 0) && (_jpeg_decoder.work_memory.block_number == _jpeg_decoder.dri.restart_interval * _jpeg_decoder.work_memory.blocks_in_one_pass))
        {
            restart_word = _jpeg_get_restart_word();

            if (restart_word < 0xFFD0 || restart_word > 0xFFD7)
                _jpeg_decoder.error = GL_DRAW_IMAGE_JPEG_ERROR_12;

            for (i = 0; i < _JPEG_MAX_CHANNELS; i++)
                _jpeg_decoder.work_memory.prev_dc_value[i] = 0;

            _jpeg_decoder.work_memory.block_number = 0;
        }

        for (i = 0; i < 64; i++)
            _jpeg_decoder.work_memory.one_block[block][i] = 0;

        _jpeg_decoder.work_memory.current_quant_table = &(_jpeg_decoder.dqt.quant_table[_jpeg_decoder.sof0.channel_quant_table_map[_jpeg_decoder.work_memory.channel_map[block]]][0]);

        byte_count = 0;
        index = _jpeg_decoder.sos.channel_huff_dc_table_map[_jpeg_decoder.work_memory.channel_map[block]];
        _jpeg_decoder.work_memory.current_huff_symbol_len_table   = &(_jpeg_decoder.dht.huff_dc_symbol_len[index][0]);
        _jpeg_decoder.work_memory.current_huff_symbol_table       = &(_jpeg_decoder.dht.huff_dc_symbol[index][0]);
        _jpeg_decoder.work_memory.current_huff_symbol_start_table = &(_jpeg_decoder.huff.huff_dc_sym_start[index][0]);
        huff_byte = _jpeg_get_next_huffman_byte();

        _jpeg_decoder.work_memory.one_block[block][0] = _jpeg_get_n_bits_value(huff_byte & 0x0F) + _jpeg_decoder.work_memory.prev_dc_value[_jpeg_decoder.work_memory.channel_map[block]];
        _jpeg_decoder.work_memory.prev_dc_value[_jpeg_decoder.work_memory.channel_map[block]] = _jpeg_decoder.work_memory.one_block[block][0];

        byte_count = 1;
        index = _jpeg_decoder.sos.channel_huff_ac_table_map[_jpeg_decoder.work_memory.channel_map[block]];
        _jpeg_decoder.work_memory.current_huff_symbol_len_table   = &(_jpeg_decoder.dht.huff_ac_symbol_len[index][0]);
        _jpeg_decoder.work_memory.current_huff_symbol_table       = &(_jpeg_decoder.dht.huff_ac_symbol[index][0]);
        _jpeg_decoder.work_memory.current_huff_symbol_start_table = &(_jpeg_decoder.huff.huff_ac_sym_start[index][0]);

        while (byte_count < 64)
        {
            huff_byte = _jpeg_get_next_huffman_byte();
            byte_count += (huff_byte >> 4);
            if (huff_byte == 0)
                break;

            if (byte_count > 63)
                _jpeg_decoder.error = GL_DRAW_IMAGE_JPEG_ERROR_13;

            _jpeg_decoder.work_memory.one_block[block][_JPEG_ZIG_ZAG_8x8[byte_count++]] = _jpeg_get_n_bits_value(huff_byte & 0x0F);
        }
        _jpeg_decoder.work_memory.block_number++;
        _jpeg_inverse_dct(&(_jpeg_decoder.work_memory.one_block[block][0]), _jpeg_decoder.work_memory.current_quant_table);
    }

    return;
}

static bool _jpeg_is_offset_x_in_range(uint16_t image_offset_x)
{
    return ((image_offset_x < _jpeg_decoder.sof0.width) &&
            (image_offset_x >= _jpeg_decoder.drawing.src->top_left.x) &&
            (image_offset_x < _jpeg_decoder.drawing.src->top_left.x + _jpeg_decoder.drawing.src->width));
}

static bool _jpeg_is_offset_y_in_range(uint16_t image_offset_y)
{
    return ((image_offset_y < _jpeg_decoder.sof0.height) &&
            (image_offset_y >= _jpeg_decoder.drawing.src->top_left.y) &&
            (image_offset_y < _jpeg_decoder.drawing.src->top_left.y + _jpeg_decoder.drawing.src->height));
}

static uint32_t _jpeg_calculate_dest_x_offset(uint16_t src_offset_x)
{
    return (uint32_t)src_offset_x * ((uint32_t)_jpeg_decoder.drawing.dest->width / (uint32_t)_jpeg_decoder.drawing.src->width);
}

static uint32_t _jpeg_calculate_dest_y_offset(uint16_t src_offset_y)
{
    return (uint32_t)src_offset_y * ((uint32_t)_jpeg_decoder.drawing.dest->height / (uint32_t)_jpeg_decoder.drawing.src->height);
}

static uint32_t _jpeg_calculate_x_drawing_count(uint16_t image_offset_x)
{
    uint16_t src_offset_x;
    uint16_t count;

    src_offset_x = image_offset_x - _jpeg_decoder.drawing.src->top_left.x;

    if (_jpeg_decoder.drawing.dest->width == _jpeg_decoder.drawing.src->width)
        return 1;

    if (_jpeg_decoder.drawing.dest->width > _jpeg_decoder.drawing.src->width)
    {
        count = _jpeg_calculate_dest_x_offset(src_offset_x + 1) - _jpeg_calculate_dest_x_offset(src_offset_x);
    }
    else // _jpeg_decoder.drawing.dest->width < _jpeg_decoder.drawing.src->width
    {
        if (src_offset_x == 0)
            count = 1;
        else
            count = _jpeg_calculate_dest_x_offset(src_offset_x) - _jpeg_calculate_dest_x_offset(src_offset_x - 1);
    }

    return count;
}

static uint16_t _jpeg_calculate_y_drawing_count(uint16_t image_offset_y)
{
    uint16_t src_offset_y;
    uint16_t count;

        src_offset_y = image_offset_y - _jpeg_decoder.drawing.src->top_left.y;

    if (_jpeg_decoder.drawing.dest->height == _jpeg_decoder.drawing.src->height)
        return 1;

    if (_jpeg_decoder.drawing.dest->height > _jpeg_decoder.drawing.src->height)
    {
        count = _jpeg_calculate_dest_y_offset(src_offset_y + 1) - _jpeg_calculate_dest_y_offset(src_offset_y);
    }
    else // _jpeg_decoder.drawing.dest->height < _jpeg_decoder.drawing.src->height
    {
        if (src_offset_y == 0)
            count = 1;
        else
            count = _jpeg_calculate_dest_y_offset(src_offset_y) - _jpeg_calculate_dest_y_offset(src_offset_y - 1);
    }

    return count;
}

static void _jpeg_sample_draw_point(uint16_t _x, uint16_t _y, uint16_t cb_cr_index)
{
    int32_t s1;
    int32_t s2;
    int32_t s3;
    gl_color_t temp;

    s1 = ((*_jpeg_color_space_ptr.y_ptr) + 128) * 128;
    s2 = _jpeg_color_space_ptr.cb_ptr[cb_cr_index];
    s3 = _jpeg_color_space_ptr.cr_ptr[cb_cr_index];

    temp = instance.pen.color;
    instance.pen.color = ((_jpeg_to_char_range((s1 + (128 * s3 + 64 * s3 - 8 * s3 - 4 * s3)) >> 7) >> 3) << 11) |
                          ((_jpeg_to_char_range((s1 - (32 * s2 + 8 * s2 + 4 * s2) - (64 * s3 + 32 * s3 - 4 * s3 - s3)) >> 7) >> 2) << 5) |
                          ((_jpeg_to_char_range((s1 + (256 * s2 - 32 * s2 + 2 * s2 + s2)) >> 7) >> 3));

    gl_draw_point(_x, _y);
    instance.pen.color = temp;
}

static void _jpeg_set_color(uint16_t width, int32_t s1, int32_t s2, int32_t s3, uint16_t drawing_count)
{
    uint16_t i;
    jpeg_color_t color;
    gl_color_t   gl_color;

    color.r = _jpeg_to_char_range((s1 + 180 * s3) >> 7);
    color.g = _jpeg_to_char_range((s1 - 44 * s2 - 91 * s3) >> 7);
    color.b = _jpeg_to_char_range((s1 + 227 * s2) >> 7);

    gl_color = ((color.r >> 3) << 11) | ((color.g >> 2) << 5) | (color.b >> 3);

    for (i = 0; i < drawing_count; i++)
    {
        if (width < instance.driver.display_width)
            instance.driver.frame_data_f(gl_color);
        else
            return;
    }
}

static void _jpeg_sample_1x1_set_color(int16_t image_offset_x, uint16_t drawing_count)
{
    int32_t s1;
    int32_t s2;
    int32_t s3;

    s1 = ((*_jpeg_color_space_ptr.y_ptr) + 128) * 128;
    s2 = (*_jpeg_color_space_ptr.cb_ptr);
    s3 = (*_jpeg_color_space_ptr.cr_ptr);
    _jpeg_set_color(_jpeg_decoder.drawing.dest->top_left.x + image_offset_x, s1, s2, s3, drawing_count);
}

static void _jpeg_sample_2x2_set_color(int16_t image_offset_x, uint8_t _x, uint8_t _y, uint16_t drawing_count)
{
    int32_t s1;
    int32_t s2;
    int32_t s3;

    s1 = ((*_jpeg_color_space_ptr.y_ptr) + 128) * 128;
    s2 = _jpeg_color_space_ptr.cb_ptr[(_y >> 1) * 8 + (_x >> 1)];
    s3 = _jpeg_color_space_ptr.cr_ptr[(_y >> 1) * 8 + (_x >> 1)];
    _jpeg_set_color(_jpeg_decoder.drawing.dest->top_left.x + image_offset_x, s1, s2, s3, drawing_count);
}

static void _jpeg_sample_init_pointers(uint8_t block)
{
    uint8_t cb_cr_offset[4];

    cb_cr_offset[0] = 0;
    cb_cr_offset[1] = 4;
    cb_cr_offset[2] = 32;
    cb_cr_offset[3] = 36;

    switch(_jpeg_decoder.work_memory.sub_sample_type)
    {
        case _JPEG_SAMPLE_1x1:
            _jpeg_color_space_ptr.y_ptr  = &(_jpeg_decoder.work_memory.one_block[0][0]);
            _jpeg_color_space_ptr.cb_ptr = &(_jpeg_decoder.work_memory.one_block[1][0]);
            _jpeg_color_space_ptr.cr_ptr = &(_jpeg_decoder.work_memory.one_block[2][0]);
            break;
        case _JPEG_SAMPLE_1x2:
            _jpeg_color_space_ptr.y_ptr  = &(_jpeg_decoder.work_memory.one_block[block][0]);
            _jpeg_color_space_ptr.cb_ptr = &(_jpeg_decoder.work_memory.one_block[2][block * 32]);
            _jpeg_color_space_ptr.cr_ptr = &(_jpeg_decoder.work_memory.one_block[3][block * 32]);
            break;
        case _JPEG_SAMPLE_2x1:
            _jpeg_color_space_ptr.y_ptr  = &(_jpeg_decoder.work_memory.one_block[block][0]);
            _jpeg_color_space_ptr.cb_ptr = &(_jpeg_decoder.work_memory.one_block[2][block * 4]);
            _jpeg_color_space_ptr.cr_ptr = &(_jpeg_decoder.work_memory.one_block[3][block * 4]);
            break;
        case _JPEG_SAMPLE_2x2:
            _jpeg_color_space_ptr.y_ptr  = &(_jpeg_decoder.work_memory.one_block[block][0]);
            _jpeg_color_space_ptr.cb_ptr = &(_jpeg_decoder.work_memory.one_block[4][cb_cr_offset[block]]);
            _jpeg_color_space_ptr.cr_ptr = &(_jpeg_decoder.work_memory.one_block[5][cb_cr_offset[block]]);
            break;
        default :
            _jpeg_decoder.error = GL_DRAW_IMAGE_JPEG_ERROR_16;
    }
}

static void _jpeg_sample_update_pointers(int16_t value)
{
    switch(_jpeg_decoder.work_memory.sub_sample_type)
    {
        case _JPEG_SAMPLE_1x1:
            _jpeg_color_space_ptr.cb_ptr += value;
            _jpeg_color_space_ptr.cr_ptr += value;
        case _JPEG_SAMPLE_1x2:
        case _JPEG_SAMPLE_2x1:
        case _JPEG_SAMPLE_2x2:
            _jpeg_color_space_ptr.y_ptr  += value;
            break;
        default :
            _jpeg_decoder.error = GL_DRAW_IMAGE_JPEG_ERROR_16;
    }
}

static void _jpeg_sample_1x1()
{
    uint8_t _x;
    uint8_t _y;
    uint16_t image_offset_y;
    uint16_t image_offset_x;
    uint16_t src_offset_x;
    uint16_t src_offset_y;
    uint16_t display_offset_y;
    uint16_t x_drawing_count;
    uint16_t y_drawing_count;
    uint16_t count;
    bool first_x_drawing;
    gl_rectangle_t rect;

    _jpeg_sample_init_pointers(_JPEG_UNUSED);

    src_offset_x = _jpeg_decoder.drawing.image_offset_x - _jpeg_decoder.drawing.src->top_left.x;

    rect.width   = instance.driver.display_width;
    rect.height  = 1;

    for (_y = 0; _y < 8; _y++)
    {
        image_offset_y   = _jpeg_decoder.drawing.image_offset_y + _y;

        if (_jpeg_is_offset_y_in_range(image_offset_y))
        {
            y_drawing_count = _jpeg_calculate_y_drawing_count(image_offset_y);
            for (count = 0; count < y_drawing_count; count++)
            {
                if (count > 0)
                    _jpeg_sample_update_pointers(-8);

                src_offset_y     = image_offset_y - _jpeg_decoder.drawing.src->top_left.y;
                display_offset_y = _jpeg_decoder.drawing.dest->top_left.y + _jpeg_calculate_dest_y_offset(src_offset_y) + count;

                if (display_offset_y < instance.driver.display_height)
                {

                    first_x_drawing = true;
                    for (_x = 0; _x < 8; _x++)
                    {
                        image_offset_x = _jpeg_decoder.drawing.image_offset_x + _x;
                        if (_jpeg_is_offset_x_in_range(image_offset_x))
                        {
                            x_drawing_count = _jpeg_calculate_x_drawing_count(image_offset_x);

                            if (x_drawing_count && first_x_drawing)
                            {
                                rect.top_left.x = _jpeg_decoder.drawing.dest->top_left.x + _jpeg_calculate_dest_x_offset(src_offset_x + _x);
                                rect.top_left.y = display_offset_y;
                                instance.driver.begin_frame_f(&rect);
                                first_x_drawing = false;
                            }

                            _jpeg_sample_1x1_set_color(image_offset_x, x_drawing_count);
                        }

                        _jpeg_sample_update_pointers(1);
                    }
                }
                else
                {
                    _jpeg_sample_update_pointers(8);
                }
            }
        }
        else
        {
            _jpeg_sample_update_pointers(8);
        }
    }
}

static void _jpeg_sample_1x2_or_2x1()
{
    uint8_t _x;
    uint8_t _y;
    uint8_t block;
    uint8_t block_offset[2];
    uint16_t cb_cr_index;
    uint16_t image_offset_x;
    uint16_t image_offset_y;
    uint16_t src_offset_x;
    uint16_t src_offset_y;
    uint16_t x_drawing_count;
    uint16_t y_drawing_count;
    uint16_t x_count;
    uint16_t y_count;

    block_offset[0] = 0;
    block_offset[1] = 8;

    for (block = 0; block < 2; block++)
    {
        _jpeg_sample_init_pointers(block);

        for (_y = 0; _y < 8; _y++)
        {
            for (_x = 0; _x < 8; _x++)
            {
                image_offset_x = _jpeg_decoder.drawing.image_offset_x + _x;
                image_offset_y = _jpeg_decoder.drawing.image_offset_y + _y;

                switch(_jpeg_decoder.work_memory.sub_sample_type)
                {
                    case _JPEG_SAMPLE_1x2:
                        image_offset_y += block_offset[block];
                        cb_cr_index = (_y >> 1) * 8 + _x;
                        break;
                    case _JPEG_SAMPLE_2x1:
                        image_offset_x += block_offset[block];
                        cb_cr_index = _y * 8 + (_x >> 1);
                        break;
                    default :
                        _jpeg_decoder.error = GL_DRAW_IMAGE_JPEG_ERROR_16;
                        return;
                }

                if (_jpeg_is_offset_x_in_range(image_offset_x) &&
                    _jpeg_is_offset_y_in_range(image_offset_y))
                {
                    x_drawing_count = _jpeg_calculate_x_drawing_count(image_offset_x);
                    y_drawing_count = _jpeg_calculate_y_drawing_count(image_offset_y);

                    src_offset_x = image_offset_x - _jpeg_decoder.drawing.src->top_left.x;
                    src_offset_y = image_offset_y - _jpeg_decoder.drawing.src->top_left.y;

                    for(y_count = 0; y_count < y_drawing_count; y_count++)
                        for(x_count = 0; x_count < x_drawing_count; x_count++)
                            _jpeg_sample_draw_point(_jpeg_decoder.drawing.dest->top_left.x + _jpeg_calculate_dest_x_offset(src_offset_x) + x_count,
                                                    _jpeg_decoder.drawing.dest->top_left.y + _jpeg_calculate_dest_y_offset(src_offset_y) + y_count,
                                                    cb_cr_index);
                }
                _jpeg_sample_update_pointers(1);
            }
        }
    }
}

static void _jpeg_sample_2x2()
{
    uint8_t _x;
    uint8_t _y;
    uint8_t block;
    uint8_t offset_x4[4];
    uint8_t offset_y4[4];
    uint16_t image_offset_x;
    uint16_t image_offset_y;
    uint16_t src_offset_x;
    uint16_t src_offset_y;
    uint16_t display_offset_y;
    uint16_t x_drawing_count;
    uint16_t y_drawing_count;
    uint16_t count;
    bool first_x_drawing;
    gl_rectangle_t rect;

    offset_x4[0] = 0;
    offset_x4[1] = 8;
    offset_x4[2] = 0;
    offset_x4[3] = 8;
    offset_y4[0] = 0;
    offset_y4[1] = 0;
    offset_y4[2] = 8;
    offset_y4[3] = 8;

    rect.width  = 1;
    rect.height = 1;

    for (block = 0; block < 4; block++)
    {
        _jpeg_sample_init_pointers(block);

        image_offset_x = _jpeg_decoder.drawing.image_offset_x + offset_x4[block];
        src_offset_x   = image_offset_x - _jpeg_decoder.drawing.src->top_left.x;

        for (_y = 0; _y < 8; _y++)
        {
            image_offset_y   = _jpeg_decoder.drawing.image_offset_y + offset_y4[block] + _y;

            if (_jpeg_is_offset_y_in_range(image_offset_y))
            {
                y_drawing_count = _jpeg_calculate_y_drawing_count(image_offset_y);
                for (count = 0; count < y_drawing_count; count++)
                {
                    if (count > 0)
                        _jpeg_sample_update_pointers(-8);

                    src_offset_y     = image_offset_y - _jpeg_decoder.drawing.src->top_left.y;
                    display_offset_y = _jpeg_decoder.drawing.dest->top_left.y + _jpeg_calculate_dest_y_offset(src_offset_y) + count;

                    if ((display_offset_y < instance.driver.display_height))
                    {
                        first_x_drawing = true;
                        for (_x = 0; _x < 8; _x++)
                        {
                            if (_jpeg_is_offset_x_in_range(image_offset_x + _x))
                            {
                                x_drawing_count = _jpeg_calculate_x_drawing_count(image_offset_x + _x);

                                if (x_drawing_count && first_x_drawing)
                                {
                                    rect.top_left.x = _jpeg_decoder.drawing.dest->top_left.x + _jpeg_calculate_dest_x_offset(src_offset_x + _x);
                                    rect.top_left.y = display_offset_y;
                                    instance.driver.begin_frame_f(&rect);
                                    first_x_drawing = true;
                                }

                                _jpeg_sample_2x2_set_color(image_offset_x + _x, _x, _y, x_drawing_count);
                            }

                            _jpeg_sample_update_pointers(1);
                        }
                    }
                    else
                    {
                        _jpeg_sample_update_pointers(8);
                    }
                }
            }
            else
            {
                _jpeg_sample_update_pointers(8);
            }
        }
    }
}

static void _jpeg_draw_block()
{
    switch(_jpeg_decoder.work_memory.sub_sample_type)
    {
        case _JPEG_SAMPLE_1x1:
            _jpeg_sample_1x1();
            break;
        case _JPEG_SAMPLE_1x2:
        case _JPEG_SAMPLE_2x1:
            _jpeg_sample_1x2_or_2x1();
            break;
        case _JPEG_SAMPLE_2x2:
            _jpeg_sample_2x2();
            break;
        default :
            _jpeg_decoder.error = GL_DRAW_IMAGE_JPEG_ERROR_16;
    }
}

static void _jpeg_calculate_blocks(uint16_t *widht_blocks, uint16_t *height_blocks, uint16_t width, uint16_t height)
{
    uint16_t w_blocks;
    uint16_t h_blocks;

    w_blocks = width  / 8;
    h_blocks = height / 8;

    if (width % 8)
        w_blocks++;

    if (height % 8)
        h_blocks++;

    if (_jpeg_decoder.work_memory.sub_sample_type == _JPEG_SAMPLE_1x2)
    {
        h_blocks = (h_blocks >> 1) + (h_blocks & 1);
    }
    else if (_jpeg_decoder.work_memory.sub_sample_type == _JPEG_SAMPLE_2x1)
    {
        w_blocks = (w_blocks >> 1) + (w_blocks & 1);
    }
    else if (_jpeg_decoder.work_memory.sub_sample_type == _JPEG_SAMPLE_2x2)
    {
        h_blocks = (h_blocks >> 1) + (h_blocks & 1);
        w_blocks = (w_blocks >> 1) + (w_blocks & 1);
    }

    *widht_blocks  = w_blocks;
    *height_blocks = h_blocks;
}

static void _jpeg_draw_blocks()
{
    uint16_t image_widht_blocks;
    uint16_t image_height_blocks;

    uint16_t src_w_start;
    uint16_t src_h_start;

    uint16_t src_w_end;
    uint16_t src_h_end;

    uint16_t w_block;
    uint16_t h_block;

    uint8_t block_width;
    uint8_t block_height;

    switch(_jpeg_decoder.work_memory.sub_sample_type)
    {
        case _JPEG_SAMPLE_1x1:
            block_width  = 8;
            block_height = 8;
            break;
        case _JPEG_SAMPLE_1x2:
            block_width  = 8;
            block_height = 16;
            break;
        case _JPEG_SAMPLE_2x1:
            block_width  = 16;
            block_height = 8;
            break;
        case _JPEG_SAMPLE_2x2:
            block_width  = 16;
            block_height = 16;
            break;
        default :
            _jpeg_decoder.error = GL_DRAW_IMAGE_JPEG_ERROR_16;
            return;
    }

    _jpeg_calculate_blocks(&image_widht_blocks,
                           &image_height_blocks,
                           _jpeg_decoder.sof0.width,
                           _jpeg_decoder.sof0.height);

    _jpeg_calculate_blocks(&src_w_start,
                           &src_h_start,
                           _jpeg_decoder.drawing.src->top_left.x,
                           _jpeg_decoder.drawing.src->top_left.y);

    _jpeg_calculate_blocks(&src_w_end,
                           &src_h_end,
                           _jpeg_decoder.drawing.src->top_left.x + _jpeg_decoder.drawing.src->width,
                           _jpeg_decoder.drawing.src->top_left.y + _jpeg_decoder.drawing.src->height);

    if (_jpeg_decoder.drawing.src->top_left.x % block_width)
        src_w_start--;
    if (_jpeg_decoder.drawing.src->top_left.y % block_height)
        src_h_start--;

    if ((_jpeg_decoder.drawing.src->top_left.x + _jpeg_decoder.drawing.src->width) % block_width)
        src_w_end--;
    if ((_jpeg_decoder.drawing.src->top_left.y + _jpeg_decoder.drawing.src->height) % block_height)
        src_h_end--;

    for (h_block = 0; h_block < image_height_blocks; h_block++)
    {
        for (w_block = 0; w_block < image_widht_blocks; w_block++)
        {
            _jpeg_decode_block();

            if ((src_h_start <= h_block) && (h_block <= src_h_end) &&
                (src_w_start <= w_block) && (w_block <= src_w_end))
            {
                _jpeg_draw_block();
            }

            _jpeg_set_next_decoding_block_point();

            if (_jpeg_decoder.error)
                break;
        }

        if (_jpeg_decoder.error)
            break;
    }

    instance.driver.end_frame_f();
}


int gl_draw_jpeg_image(gl_rectangle_t *dest, gl_rectangle_t *src, const uint8_t * image)
{
    _jpeg_decoder.error = GL_DRAW_IMAGE_SUCCESS;

    memset(&_jpeg_decoder, 0x00, sizeof(jpeg_decoder_t));

    _jpeg_decoder.drawing.src  = src;
    _jpeg_decoder.drawing.dest = dest;

    _jpeg_decoder.image_file_as_array = (const uint8_t *)(image + sizeof(gl_image_header_t));
    _jpeg_image_read_ptr = _jpeg_decoder.image_file_as_array;
    _jpeg_read_header();

    if (_jpeg_decoder.error)
        return _jpeg_decoder.error;

    _jpeg_generate_huffman_tables();

    _jpeg_draw_blocks();

    return _jpeg_decoder.error;
}
