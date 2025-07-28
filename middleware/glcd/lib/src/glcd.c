#include "glcd.h"

const char_def font[] = {
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

void glcd_config_default( glcd_cfg_t* glcd_cfg )
{
    if (!glcd_cfg) return;
    glcd_cfg->GLCD_E_PIN = TFT_E;
    glcd_cfg->GLCD_RW_PIN = TFT_R_W;
    glcd_cfg->GLCD_RS_PIN = TFT_RS;
    glcd_cfg->GLCD_CS2_PIN = TFT_CS2;
    glcd_cfg->GLCD_CS1_PIN = TFT_CS1;
    glcd_cfg->GLCD_RESET_PIN = TFT_RST;

    glcd_cfg->data_out = TFT_8BIT_DATA_PORT_CH0;            // Default port for data output

}

void glcd_port_init( glcd_t* glcd )
{
    glcd_config_default( &glcd->config );

    port_init( &glcd->data_out, glcd->config.data_out, 0xFF, HAL_LL_GPIO_DIGITAL_OUTPUT );
    digital_out_init( &glcd->cs1d, glcd->config.GLCD_CS1_PIN );
    digital_out_init( &glcd->cs2d, glcd->config.GLCD_CS2_PIN );
    digital_out_init( &glcd->ed, glcd->config.GLCD_E_PIN );
    digital_out_init( &glcd->resetd, glcd->config.GLCD_RESET_PIN );
    digital_out_init( &glcd->rsd, glcd->config.GLCD_RS_PIN );
    digital_out_init( &glcd->rwd, glcd->config.GLCD_RW_PIN );
}

void glcd_init( glcd_t* glcd )
{
    glcd_port_init(glcd);

    digital_out_high( &glcd->ed );
    digital_out_high( &glcd->cs1d );
    digital_out_high( &glcd->cs2d );
    digital_out_high( &glcd->resetd );
    digital_out_low( &glcd->rsd );
    digital_out_high( &glcd->rwd );
    apply_changes(glcd);
}

void glcd_set_page( glcd_t* glcd, uint8_t page )
{
    if ( !glcd || page > 7 ) return;

    digital_out_low( &glcd->rsd );                               // RS = 0 (instruction)
    digital_out_low( &glcd->rwd );                               // RW = 0 (ecriture)
    port_write( &glcd->data_out, (0xB8 | (page & 0x07)) );       // We only care about the lower 3 bits for page address
    apply_changes(glcd);
}

void glcd_set_y( glcd_t* glcd, uint8_t y_pos )
{
    if ( !glcd || y_pos > 64 ) return;

    digital_out_low( &glcd->rsd );                    // RS = 0 (instruction)
    digital_out_low( &glcd->rwd );                    // RW = 0 (ecriture)
    port_write( &glcd->data_out, (0x40 | (y_pos & 0x3F)) );
    apply_changes(glcd);
}

void glcd_clear(glcd_t *glcd)
{
    if (!glcd) return;

    for (uint8_t page = 0; page < PAGE_SIZE; page++)
        for (uint8_t col = 0; col <= ROW_SIZE; col++)
            glcd_write(glcd, page, col, 0x00);
}

void glcd_display( glcd_t* glcd, display_cfg_t turn_on_off )
{
    if ( !glcd || turn_on_off != ON || turn_on_off != OFF ) return;

    for (uint8_t k = 0; k < 2; k++)
    {
        cs_config( glcd, k%2, (k+1)%2 );
        digital_out_low( &glcd->rsd );                // RS = 0 (instruction)
        digital_out_low( &glcd->rwd );                // RW = 0 (ecriture)
        port_write( &glcd->data_out, turn_on_off );
        apply_changes(glcd);
    }
}

void apply_changes( glcd_t* glcd )
{
    digital_out_high( &glcd->ed );
    Delay_us(10);
    digital_out_low( &glcd->ed );
    Delay_us(10);
}

void cs_config(glcd_t* glcd, bool cs1, bool cs2)
{
    if (!glcd) return;
    digital_out_write(&glcd->cs1d, (cs1 == 1) ? 0 : 1);
    digital_out_write(&glcd->cs2d, (cs2 == 1) ? 0 : 1);
}

/* -------------------------------------------------- Read and Write functions -------------------------------------------------- */
uint8_t glcd_read(glcd_t* glcd, uint8_t page, uint8_t column)
{
    if (!glcd || page >= PAGE_SIZE || column >= ROW_SIZE) return 0;

    uint8_t chip = (column < 64) ? 0 : 1;
    uint8_t col_in_chip = column % 64;
    return glcd->buffer[chip][page][col_in_chip];
}

uint8_t glcd_reqd_ll(glcd_t* glcd, uint8_t page, uint8_t column)
{
    if (!glcd || page >= PAGE_SIZE || column >= ROW_SIZE) return 0;

    port_init( &glcd->data_out, PORT_E, 0xFF, HAL_LL_GPIO_DIGITAL_INPUT );
    uint8_t chip = (column < 64) ? 0 : 1;
    uint8_t col_in_chip = column % 64;

    cs_config(glcd, chip == 0, chip == 1);
    glcd_set_y(glcd, col_in_chip);
    glcd_set_page(glcd, page);

    digital_out_high(&glcd->rsd);
    digital_out_high(&glcd->rwd);

    // Dummy read (necessary for the GLCD to prepare for reading)
    digital_out_high(&glcd->ed);    // E = 1
    Delay_us(1);                    // tWH ≥ 450 ns (from datasheet)
    digital_out_low(&glcd->ed);     // E = 0
    Delay_us(1);

    uint8_t data_readed = port_read(&glcd->data_out);
    port_init( &glcd->data_out, PORT_E, 0xFF, HAL_LL_GPIO_DIGITAL_OUTPUT );
    apply_changes(glcd);

    return data_readed;
}

void glcd_write(glcd_t *glcd, uint8_t page, uint8_t line, uint8_t data_to_write)
{
    if (!glcd || page > PAGE_SIZE || line > ROW_SIZE) return;

    if (line < 64)
    {
        cs_config(glcd, 1, 0);
        glcd_set_y(glcd, line);
        glcd_set_page(glcd, page);
    }
    else
    {
        cs_config(glcd, 0, 1);
        glcd_set_y(glcd, line-64);
        glcd_set_page(glcd, page);
    }
    digital_out_low(&glcd->ed);
    digital_out_high(&glcd->rsd);
    digital_out_low(&glcd->rwd);
    port_write(&glcd->data_out, data_to_write);
    apply_changes(glcd);

    glcd->buffer[(line < 64) ? 0 : 1][page][line % 64] = data_to_write;
}

void glcd_write_char(glcd_t* glcd, point* p, char c)
{
    uint8_t page = p->y / 8;
    uint8_t line = p->x % 128;
    uint64_t res = transpose_word(find_matching_char_from_bitmap(c));

    for (uint8_t i = 0; i < 8; i++)
    {
        uint8_t byte = (res >> (8 * (7 - i))) & 0xFF;
        byte = reverse_byte(byte);
        glcd_write(glcd, page, line + i, byte);
    }
}

void glcd_write_text(glcd_t* glcd, point* p, const char* c)
{
    if (!glcd || !p || !c) return;

    point pos = *p;
    size_t len = strlen(c);
    for (size_t i = 0; i < len; i++)
    {
        glcd_write_char(glcd, &pos, c[i]);
        pos.x += 8;

        if (pos.x >= 128) {
            pos.x = 0;
            pos.y += 8;
            if (pos.y >= 64) break;
        }
    }
}

/* -------------------------------------------------- Drawing functions -------------------------------------------------- */
void glcd_fill_screen( glcd_t* glcd, uint8_t pattern )
{
    if (!glcd) return;

    for (uint8_t page = 0; page < PAGE_SIZE; page++)
        for (uint8_t col = 0; col <= ROW_SIZE; col++)
            glcd_write(glcd, page, col, pattern);
}

void glcd_draw_dots(glcd_t* glcd, const point* pts, uint8_t size, uint8_t dot_size)
{
    if (!glcd || !pts || dot_size == 0 || dot_size > 8) return;

    for (uint8_t i = 0; i < size; i++)
    {
        uint8_t x = pts[i].x;
        uint8_t y = pts[i].y;

        if (x >= 128 || y >= 64) continue;

        uint8_t page = y / 8;
        uint8_t y_offset = y % 8;

        for (uint8_t dx = 0; dx < dot_size; dx++)
        {
            if (x + dx >= 128) continue;
            for (uint8_t dy = 0; dy < dot_size; dy++)
            {
                uint8_t current_y = y + dy;
                if (current_y >= 64) continue;

                uint8_t current_page = current_y / 8;
                uint8_t bit_in_page = current_y % 8;

                uint8_t prev = glcd_read(glcd, current_page, x + dx);
                prev |= (1 << bit_in_page);
                glcd_write(glcd, current_page, x + dx, prev);
            }
        }
    }
}

void glcd_draw_line(glcd_t* glcd, const segment* s, uint8_t s_size, line_dir_t direction)
{
    if (!glcd || !s) return;

    for (uint8_t i = 0; i < s_size; i++)
    {
        point p0 = s[i].pts[0];
        point p1 = s[i].pts[1];
        uint8_t thickness = s[i].line_size;

        if (p0.x >= 128 || p1.x >= 128 || p0.y >= 64 || p1.y >= 64 ||
            p0.x < 0 || p1.x < 0 || p0.y < 0 || p1.y < 0)
            continue;

        switch (direction)
        {
            case VERTICAL_LINE:
            {
                if (p0.x != p1.x) break;
                int x = p0.x;
                int y0 = (p0.y < p1.y) ? p0.y : p1.y;
                int y1 = (p0.y > p1.y) ? p0.y : p1.y;

                for (int y = y0; y <= y1 && y < 64; y++)
                {
                    for (uint8_t dx = 0; dx < thickness; dx++)
                    {
                        int cx = x + dx;
                        if (cx >= 128) continue;

                        uint8_t page = y / 8;
                        uint8_t bit_in_page = 1 << (y % 8);
                        uint8_t val = glcd_read(glcd, page, cx);
                        glcd_write(glcd, page, cx, val | bit_in_page);
                    }
                }
                break;
            }

            case HORIZONTAL_LINE:
            {
                if (p0.y != p1.y) break;
                int y = p0.y;
                int x0 = (p0.x < p1.x) ? p0.x : p1.x;
                int x1 = (p0.x > p1.x) ? p0.x : p1.x;

                for (int x = x0; x <= x1 && x < 128; x++)
                {
                    for (uint8_t dy = 0; dy < thickness; dy++)
                    {
                        int cy = y + dy;
                        if (cy >= 64) continue;

                        uint8_t page = cy / 8;
                        uint8_t bit_in_page = 1 << (cy % 8);
                        uint8_t val = glcd_read(glcd, page, x);
                        glcd_write(glcd, page, x, val | bit_in_page);
                    }
                }
                break;
            }

            case DIAGONAL:
            {
                int x0 = p0.x, y0 = p0.y;
                int x1 = p1.x, y1 = p1.y;
                int dx = abs(x1 - x0), dy = abs(y1 - y0);
                int sx = (x0 < x1) ? 1 : -1;
                int sy = (y0 < y1) ? 1 : -1;
                int err = dx - dy;

                while (1)
                {
                    for (uint8_t dy_dot = 0; dy_dot < thickness; dy_dot++)
                    {
                        for (uint8_t dx_dot = 0; dx_dot < thickness; dx_dot++)
                        {
                            int x = x0 + dx_dot;
                            int y = y0 + dy_dot;
                            if (x < 0 || x >= 128 || y < 0 || y >= 64) continue;

                            uint8_t page = y / 8;
                            uint8_t bit_in_page = 1 << (y % 8);
                            uint8_t val = glcd_read(glcd, page, x);
                            glcd_write(glcd, page, x, val | bit_in_page);
                        }
                    }

                    if (x0 == x1 && y0 == y1) break;

                    int e2 = 2 * err;
                    if (e2 > -dy) { err -= dy; x0 += sx; }
                    if (e2 < dx)  { err += dx; y0 += sy; }
                }
                break;
            }
        }
    }
}

void glcd_draw_rect(glcd_t* glcd, const point* p, uint16_t psize, const rect* r, uint16_t rsize)
{
    if (!glcd || !r || !p || psize != rsize ) return;

    for (uint16_t i=0; i<psize; i++)
    {
        uint8_t x0 = p[i].x, y0 = p[i].y;
        uint8_t x1 = (x0 + r[i].w)%ROW_SIZE, y1 = (y0 + r[i].h)%COL_PER_CHIP;
        uint8_t line_sz = r[i].line_size;

        segment rect[4] = {
            {{{x0, y0},{x1, y0}}, line_sz},
            {{{x0, y0},{x0, y1}}, line_sz},
            {{{x1, y0},{x1, y1}}, line_sz},
            {{{x0, y1},{x1, y1}}, line_sz}
        };

        glcd_draw_line(glcd, rect, 4, DIAGONAL);
        if (r[i].filled) { fill_polygon(glcd, rect, 4); }
        if (r[i].rounded) { /*TODO*/ }
    }
}

void glcd_draw_shape(glcd_t* glcd, const segment* edges, uint8_t size, bool is_filled, bool round_edges)
{
    if (!glcd || !edges) return;

    segment output[64];
    sort_points_nearest_neighbor(edges, output, size);
    glcd_draw_line(glcd, output, size, DIAGONAL);

    if (is_filled) { fill_polygon(glcd, output, output[0].line_size); }
    if (round_edges) { /*TODO*/ }
}

void glcd_draw_regular_polygon(glcd_t* glcd, const point* ori, uint8_t num_of_ori, const polygon_mode_t* pol, uint8_t num_of_pol, bool is_filled)
{
    if (!glcd || !ori || !pol || num_of_pol == 0 || num_of_ori == 0) return;

    uint8_t count = (num_of_ori < num_of_pol) ? num_of_ori : num_of_pol;
    for (uint8_t p = 0; p < count; p++)
    {
        uint8_t sides = pol[p];
        if (sides < 3 || sides > 10) continue;

        point polygon_points[10];
        segment edges[10];

        for (uint8_t i = 0; i < sides; i++)
        {
            float angle = (2 * PI * i) / sides;
            int16_t x = ori[p].x + (int16_t)(20 * cos(angle));
            int16_t y = ori[p].y + (int16_t)(20 * sin(angle));

            polygon_points[i].x = x;
            polygon_points[i].y = y ;
        }

        for (uint8_t i = 0; i < sides; i++)
        {
            edges[i].pts[0] = polygon_points[i];
            edges[i].pts[1] = polygon_points[(i + 1) % sides];
            edges[i].line_size = 2;
        }

        glcd_draw_line(glcd, edges, sides, DIAGONAL);
        if (is_filled) fill_polygon(glcd, edges, sides);
    }
}

void glcd_draw_circle( glcd_t* glcd, const circle* c, uint16_t csize, circle_mode_t precision )
{
    if ( !glcd || !c ) return;

    point circle_approx[5000];
    for (uint16_t i = 0; i < csize; i++)
    {
        uint8_t radius = c[i].r, dot_size = c[i].line_size;
        point origin = c[i].o;

        for (uint16_t j = 0; j < precision; j++)
        {
            circle_approx[j].x = origin.x + (int16_t)(radius * cos((2 * PI * j) / precision));
            circle_approx[j].y = origin.y + (int16_t)(radius * sin((2 * PI * j) / precision));
        }

        for (uint16_t j = 0; j < precision; j++)
        {
            segment s = { {{circle_approx[j].x, circle_approx[j].y}, {circle_approx[(j + 1) % precision].x, circle_approx[(j + 1) % precision].y}}, dot_size };
            glcd_draw_line(glcd, &s, 1, DIAGONAL);
        }
        if (c[i].filled) { fill_circle(glcd, circle_approx, precision, dot_size); }
    }
}

void glcd_draw_ellipse(glcd_t* glcd, const ellipse* e, uint16_t esize, circle_mode_t precision)
{
    if (!glcd || !e || esize == 0 || precision < 3 || precision > 5000) return;

    for (uint16_t i = 0; i < esize; i++)
    {
        float cx = e[i].mid_foci[0].x, cy = e[i].mid_foci[0].y;
        float fx = e[i].mid_foci[1].x, fy = e[i].mid_foci[1].y;
        float dx = fx - cx, dy = fy - cy;
        float c_val = sqrt(dx * dx + dy * dy);
        float a = e[i].a;
        if (a <= c_val) a = c_val + 5; // Ensure valid ellipse
        float b = sqrt(a * a - c_val * c_val);

        float theta_axis = atan2(dy, dx);
        uint8_t dot_size = e[i].line_size;
        bool is_filled = e[i].filled;

        point ellipse_points[5000];
        for (uint16_t j = 0; j < precision; j++)
        {
            float theta = (2.0f * PI * j) / precision;
            float x_local = a * cos(theta);
            float y_local = b * sin(theta);
            float x_rot = x_local * cos(theta_axis) - y_local * sin(theta_axis);
            float y_rot = x_local * sin(theta_axis) + y_local * cos(theta_axis);
            float x = cx + x_rot;
            float y = cy + y_rot;

            ellipse_points[j].x = (uint8_t)(x + 0.5f);
            ellipse_points[j].y = (uint8_t)(y + 0.5f);
        }

        for (uint16_t k = 0; k < precision; k++)
        {
            segment s = {
                {
                    { ellipse_points[k].x, ellipse_points[k].y },
                    { ellipse_points[(k + 1) % precision].x, ellipse_points[(k + 1) % precision].y }
                },
                dot_size
            };
            glcd_draw_line(glcd, &s, 1, DIAGONAL);
        }
        if (is_filled) { fill_circle(glcd, ellipse_points, precision, dot_size); }
    }
}



/* -------------------------------------------------- Utils -------------------------------------------------- */
float distance(point a, point b)
{
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

void sort_points_nearest_neighbor(const segment* input, segment* output, uint8_t size)
{
    if (!input || !output || size == 0) return;

    bool visited[64] = { false };
    uint8_t current = 0;

    float min_dist = 1e9;
    for (uint8_t i = 0; i < size; i++)
    {
        float d = distance((point){0, 0}, input[i].pts[0]);
        if (d < min_dist) { min_dist = d; current = i; }
    }

    output[0] = input[current];
    visited[current] = true;

    for (uint8_t i = 1; i < size; i++)
    {
        float best_dist = 1e9;
        uint8_t next = 0;
        for (uint8_t j = 0; j < size; j++)
        {
            if (!visited[j])
            {
                float d = distance(output[i - 1].pts[1], input[j].pts[0]);
                if (d < best_dist) { best_dist = d; next = j; }
            }
        }
        output[i] = input[next];
        visited[next] = true;
    }
}

void fill_polygon(glcd_t* glcd, const segment* edges, uint8_t size)
{
    if (!glcd || !edges || size < 3) return;

    for (uint8_t i = 0; i < size; i++) { if (edges[i].line_size != edges[(i+1)%size].line_size) return; }
    uint8_t min_y = 255, max_y = 0, dot_size = edges[0].line_size;
    for (uint8_t i = 0; i < size; i++)
    {
        if (edges[i].pts[0].y < min_y) min_y = edges[i].pts[0].y;
        if (edges[i].pts[0].y > max_y) max_y = edges[i].pts[0].y;
        if (edges[i].pts[1].y < min_y) min_y = edges[i].pts[1].y;
        if (edges[i].pts[1].y > max_y) max_y = edges[i].pts[1].y;
    }

    segment sorted[64];
    sort_points_nearest_neighbor(edges, sorted, size);

    for (uint8_t y = min_y; y <= max_y; y++)
    {
        uint8_t x_intersections[64];
        uint8_t nb_x = 0;

        for (uint8_t i = 0; i < size; i++)
        {
            point p1 = sorted[i].pts[0], p2 = sorted[i].pts[1];
            if (p1.y == p2.y) continue;
            if (p1.y > p2.y) { point temp = p1; p1 = p2; p2 = temp; }

            if (y >= p1.y && y < p2.y)
            {
                int16_t dx = p2.x - p1.x;
                int16_t dy = p2.y - p1.y;
                uint8_t x = p1.x + (dx * (y - p1.y)) / dy;
                if (nb_x < 64) x_intersections[nb_x++] = x;
            }
        }

        // Tri à bulles
        for (uint8_t i = 0; i < nb_x - 1; i++)
        {
            for (uint8_t j = 0; j < nb_x - i - 1; j++)
            {
                if (x_intersections[j] > x_intersections[j + 1])
                {
                    uint8_t tmp = x_intersections[j];
                    x_intersections[j] = x_intersections[j + 1];
                    x_intersections[j + 1] = tmp;
                }
            }
        }

        for (uint8_t i = 0; i + 1 < nb_x; i += 2)
        {
            segment s = { { { x_intersections[i], y }, { x_intersections[i + 1], y } }, dot_size };
            glcd_draw_line(glcd, &s, 1, HORIZONTAL_LINE);
        }
    }
}

void fill_circle( glcd_t* glcd, const point* contour, uint16_t precision, uint8_t dot_size )
{
    if (!glcd || !contour || dot_size == 0) return;

    uint8_t min_y = 255, max_y = 0;
    for (uint16_t i = 0; i < precision; i++)
    {
        if (contour[i].y < min_y) min_y = contour[i].y;
        if (contour[i].y > max_y) max_y = contour[i].y;
    }

    for (uint8_t y = min_y; y <= max_y; y++)
    {
        uint8_t x_intersections[128];
        uint8_t count_x = 0;

        for (uint16_t i = 0; i < precision; i++)
        {
            point p1 = contour[i];
            point p2 = contour[(i + 1) % precision];

            if (p1.y == p2.y) continue;
            if (p1.y > p2.y)
            {
                point tmp = p1;
                p1 = p2;
                p2 = tmp;
            }

            if (y >= p1.y && y < p2.y)
            {
                float dx = p2.x - p1.x;
                float dy = p2.y - p1.y;
                float x = p1.x + dx * (float)(y - p1.y) / dy;
                if (count_x < 128)
                    x_intersections[count_x++] = (uint8_t)(x + 0.5f);
            }
        }

        for (uint8_t j = 0; j < count_x - 1; j++)
        {
            for (uint8_t k = 0; k < count_x - j - 1; k++)
            {
                if (x_intersections[k] > x_intersections[k + 1])
                {
                    uint8_t temp = x_intersections[k];
                    x_intersections[k] = x_intersections[k + 1];
                    x_intersections[k + 1] = temp;
                }
            }
        }

        for (uint8_t j = 0; j + 1 < count_x; j += 2)
        {
            segment s = { {{ x_intersections[j], y }, { x_intersections[j + 1], y }}, dot_size };
            glcd_draw_line(glcd, &s, 1, DIAGONAL);
        }
    }
}

static int dot_product(point a, point b, point c)
{
    int ux = b.x - a.x;
    int uy = b.y - a.y;
    int vx = c.x - a.x;
    int vy = c.y - a.y;
    return ux * vx + uy * vy;
}

uint64_t transpose_word(uint64_t word)
{
    uint64_t result = 0;

    for (uint8_t row = 0; row < 8; row++)
        for (uint8_t col = 0; col < 8; col++)
            if (word & (1ULL << (col * 8 + row)))
                result |= (1ULL << (row * 8 + col));

    return result;
}


uint64_t find_matching_char_from_bitmap(char c)
{
    uint8_t size = sizeof(font) / sizeof(font[0]);
    for (uint8_t i=0; i<size; i++)
    {
        if (c == font[i].c) return font[i].bitmap_code;
        else continue;
    }
    return 0;
}

uint8_t reverse_byte(uint8_t b)
{
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}