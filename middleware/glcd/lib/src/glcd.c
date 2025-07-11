#include "glcd.h"

void GLCD_Port_Init( void )
{
    port_init( &data_out, PORT_E, 0xFF, HAL_LL_GPIO_DIGITAL_OUTPUT );
    digital_out_init( &cs1d, CS1_PIN );
    digital_out_init( &cs2d, CS2_PIN );
    digital_out_init( &ed, E_PIN );
    digital_out_init( &resetd, RESET_PIN );
    digital_out_init( &rsd, RS_PIN );
    digital_out_init( &rwd, RW_PIN );
}

void GLCD_Init( glcd_t* glcd )
{
    GLCD_Port_Init();

    /* Definition of default GLCD configuration */
    glcd->CS1 = 1;
    glcd->CS2 = 1;
    glcd->Reset = 1;
    glcd->Enable = 1;
    glcd->DATA_OR_INSTRUCTION =  DATA;
    glcd->READ_OR_WRITE = READ;

    digital_out_write( &ed, glcd->Enable );
    digital_out_write( &cs1d, glcd->CS1 );
    digital_out_write( &cs2d, glcd->CS2 );
    digital_out_write( &resetd, glcd->Reset );
    digital_out_write( &rsd,  glcd->DATA_OR_INSTRUCTION );
    digital_out_write( &rwd, glcd->READ_OR_WRITE );
    Apply_changes();
}

void CS_Config(glcd_t* glcd, bool cs1, bool cs2)
{
    if (!glcd) return;
    digital_out_write(&cs1d, (cs1 == 1) ? 0 : 1);
    digital_out_write(&cs2d, (cs2 == 1) ? 0 : 1);
}

void GLCD_Set_Y( glcd_t* glcd, uint8_t y_pos )
{
    if ( !glcd || y_pos > 64 ) return;

    digital_out_low( &rsd );                    // RS = 0 (instruction)
    digital_out_low( &rwd );                    // RW = 0 (ecriture)
    port_write( &data_out, (0x40 | (y_pos & 0x3F)) );
    Apply_changes();
}

void GLCD_Set_Page( glcd_t* glcd, uint8_t page )
{
    if ( !glcd || page > 7 ) return;             

    digital_out_low( &rsd );                    // RS = 0 (instruction)
    digital_out_low( &rwd );                    // RW = 0 (ecriture)
    port_write( &data_out, (0xB8 | (page & 0x07)) );       // We only care about the lower 3 bits for page address
    Apply_changes();
}

//generalize this function to negative ligns (which means the second half of the GLCD and the 0 is 127, it's going backwards)
void GLCD_Write(glcd_t *glcd, uint8_t page, uint8_t line, uint8_t data_to_write)
{
    if (!glcd || page > PAGE_SIZE || line > ROW_SIZE) return;            // Set the Y position (line)
                                 
    if (line < 64) 
    {
        CS_Config(glcd, 1, 0);
        GLCD_Set_Y(glcd, line);
        GLCD_Set_Page(glcd, page);
    }
    else
    {
        CS_Config(glcd, 0, 1);
        GLCD_Set_Y(glcd, line-64);
        GLCD_Set_Page(glcd, page);
    }
    digital_out_low(&ed);
    digital_out_high(&rsd);
    digital_out_low(&rwd); 
    port_write(&data_out, data_to_write);
    Apply_changes();

    glcd->buffer[(line < 64) ? 0 : 1][page][line % 64] = data_to_write;
}

void GLCD_Clear(glcd_t *glcd)
{
    if (!glcd) return;
    
    for (uint8_t page = 0; page < PAGE_SIZE; page++)
        for (uint8_t col = 0; col <= ROW_SIZE; col++)
            GLCD_Write(glcd, page, col, 0x00);              // Write 0 to clear the screen
}

void GLCD_Fill_Screen( glcd_t* glcd, uint8_t pattern )
{
    if (!glcd) return;
    
    for (uint8_t page = 0; page < PAGE_SIZE; page++)
        for (uint8_t col = 0; col <= ROW_SIZE; col++)
            GLCD_Write(glcd, page, col, pattern);              // Write 0 to clear the screen
}

void GLCD_Draw_Dots(glcd_t* glcd, const point* pts, uint8_t size, uint8_t dot_size)
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

                uint8_t prev = GLCD_Read(glcd, current_page, x + dx);
                prev |= (1 << bit_in_page);
                GLCD_Write(glcd, current_page, x + dx, prev);
            }
        }
    }
}

void GLCD_Draw_Line( glcd_t* glcd, point pts[2], uint8_t dot_size, uint8_t direction )
{
    if (pts[0].x >= 128 || pts[1].x >= 128 || pts[0].y >= 64 || pts[1].y >= 64) return;


    uint8_t pattern = 0x00;
    uint8_t pt0_page = (pts[0].y / 8);
    uint8_t pt1_page = (pts[1].y / 8);
    uint8_t pt0_line = (pts[0].x % 128);
    uint8_t pt1_line = (pts[1].x % 128);
    switch(dot_size)
    {
        case 0: break; 
        case 1: pattern = 0x10; break;
        case 2: pattern = 0x18; break; 
        case 3: pattern = 0x19; break;
        case 4: pattern = 0x3C; break; 
        case 5: pattern = 0x3C; break; 
        case 6: pattern = 0x7E; break; 
        case 7: pattern = 0x7E; break; 
        case 8: pattern = 0xFF; break; 
    }

    switch(direction)
    {
        case VERTICAL_LINE:
        {
            if (pts[0].x != pts[1].x) return;

            int x = pts[0].x;
            int y0 = pts[0].y;
            int y1 = pts[1].y;

            if (y0 > y1) {
                int temp = y0;
                y0 = y1;
                y1 = temp;
            }

            for (int y = y0; y <= y1; y++) {
                for (uint8_t dx = 0; dx < dot_size; dx++) {
                    int current_x = x + dx;
                    if (current_x >= 128) continue;
                    if (y >= 64) continue;

                    uint8_t page = y / 8;
                    uint8_t bit_in_page = 1 << (y % 8);
                    uint8_t current = GLCD_Read(glcd, page, current_x);
                    current |= bit_in_page;
                    GLCD_Write(glcd, page, current_x, current);
                }
            }
            break;
        }

        case HORIZONTAL_LINE:
        {
            if (pts[0].y != pts[1].y) return;

            int y = pts[0].y;
            int x0 = pts[0].x;
            int x1 = pts[1].x;

            if (x0 > x1) { int temp = x0; x0 = x1; x1 = temp; }   
            for (int x = x0; x <= x1; x++) 
            {
                for (uint8_t dy = 0; dy < dot_size; dy++) 
                {
                    int current_y = y + dy;
                    if (x >= 128 || current_y >= 64) continue;

                    uint8_t page = current_y / 8;
                    uint8_t bit_in_page = 1 << (current_y % 8);
                    uint8_t current = GLCD_Read(glcd, page, x);
                    current |= bit_in_page;
                    GLCD_Write(glcd, page, x, current);
                }
            }
            break;
        }


        //Bresenham Algorithm for ploting a diagonal line
        case DIAGONAL:
        {
            int x0 = pts[0].x, y0 = pts[0].y;
            int x1 = pts[1].x, y1 = pts[1].y;

            int dx = abs(x1 - x0), dy = abs(y1 - y0);
            int sx = (x0 < x1) ? 1 : -1, sy = (y0 < y1) ? 1 : -1;
            int err = dx - dy;

            while (1)
            {
                for (uint8_t dy_dot = 0; dy_dot < dot_size; dy_dot++)
                {
                    for (uint8_t dx_dot = 0; dx_dot < dot_size; dx_dot++)
                    {
                        int x = x0 + dx_dot, y = y0 + dy_dot;
                        if (x < 0 || x >= 128 || y < 0 || y >= 64) continue;

                        uint8_t page = y / 8;
                        uint8_t bit_in_page = 1 << (y % 8);
                        uint8_t current = GLCD_Read(glcd, page, x);
                        current |= bit_in_page;
                        GLCD_Write(glcd, page, x, current);
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

void GLCD_Display( glcd_t* glcd, unsigned char turn_on_off )
{
    if ( !glcd ) return;
    if (!IS_ON( turn_on_off ) && !IS_OFF( turn_on_off ) ) return;

    for (uint8_t k = 0; k < 2; k++)
    {
        CS_Config( glcd, k%2, (k+1)%2 );
        digital_out_low( &rsd );                // RS = 0 (instruction)
        digital_out_low( &rwd );                // RW = 0 (ecriture)
        port_write( &data_out, turn_on_off );
        Apply_changes();
    }
}

uint8_t GLCD_Read(glcd_t* glcd, uint8_t page, uint8_t column)
{
    if (!glcd || page >= PAGE_SIZE || column >= ROW_SIZE) return 0;

    uint8_t chip = (column < 64) ? 0 : 1;
    uint8_t col_in_chip = column % 64;
    return glcd->buffer[chip][page][col_in_chip];
}

void Apply_changes( void )
{
    digital_out_high( &ed );
    Delay_us(10);
    digital_out_low( &ed );
    Delay_us(10);
}

float distance(point a, point b) 
{
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

void Sort_Points_Nearest_Neighbor(const point* input, point* output, uint8_t size) {
    if (!input || !output || size == 0) return;

    bool visited[64] = { false };
    uint8_t current = 0;

    float min_dist = 1e9;
    for (uint8_t i = 0; i < size; i++) 
    {
        float d = distance((point){0, 0}, input[i]);
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
                float d = distance(output[i - 1], input[j]);
                if (d < best_dist) {best_dist = d; next = j; }
            }
        }
        output[i] = input[next];
        visited[next] = true;
    }
}

void Fill_Polygon(glcd_t* glcd, const point* input, uint8_t size, uint8_t dot_size)
{
    if (!glcd || !input || size < 3 || dot_size == 0) return;

    // Étape 1 : calcul des bornes verticales
    uint8_t min_y = 255, max_y = 0;
    for (uint8_t i = 0; i < size; i++) {
        if (input[i].y < min_y) min_y = input[i].y;
        if (input[i].y > max_y) max_y = input[i].y;
    }

    // Étape 2 : trier les points dans l'ordre du contour
    point sorted[64];
    Sort_Points_Nearest_Neighbor(input, sorted, size);

    // Étape 3 : balayage horizontal
    for (uint8_t y = min_y; y <= max_y; y++)
    {
        uint8_t x_intersections[64];
        uint8_t nb_x = 0;

        for (uint8_t i = 0; i < size; i++)
        {
            point p1 = sorted[i];
            point p2 = sorted[(i + 1) % size];

            if (p1.y == p2.y) continue; // segment horizontal → ignorer

            // S'assurer que p1 est en haut
            if (p1.y > p2.y) {
                point temp = p1;
                p1 = p2;
                p2 = temp;
            }

            // Y traverse l'arête
            if (y >= p1.y && y < p2.y)
            {
                int16_t dx = p2.x - p1.x;
                int16_t dy = p2.y - p1.y;
                uint8_t x = p1.x + (dx * (y - p1.y)) / dy;
                if (nb_x < 64) x_intersections[nb_x++] = x;
            }
        }

        // Trier les x (tri à bulles simple)
        for (uint8_t i = 0; i < nb_x - 1; i++) {
            for (uint8_t j = 0; j < nb_x - i - 1; j++) {
                if (x_intersections[j] > x_intersections[j + 1]) {
                    uint8_t tmp = x_intersections[j];
                    x_intersections[j] = x_intersections[j + 1];
                    x_intersections[j + 1] = tmp;
                }
            }
        }

        // Tracer les segments horizontaux entre les paires d'intersections
        for (uint8_t i = 0; i + 1 < nb_x; i += 2)
        {
            point p[2] = {
                { x_intersections[i], y },
                { x_intersections[i + 1], y }
            };
            GLCD_Draw_Line(glcd, p, dot_size, HORIZONTAL_LINE);
        }
    }
}

uint8_t get_direction(point a, point b) {
    if (a.x == b.x) return VERTICAL_LINE;
    if (a.y == b.y) return HORIZONTAL_LINE;
    return DIAGONAL;
}

void GLCD_Draw_Polygon(glcd_t* glcd, const point* limit, uint8_t size, uint8_t dot_size, bool is_filled, bool round_edges)
{
    if (!glcd || !limit || size < 3) return;

    point output[64];
    Sort_Points_Nearest_Neighbor(limit, output, size);
    for (uint8_t i = 0; i < size; i++) 
    {
        point temp[2] = { {output[i].x, output[i].y}, {output[(i + 1) % size].x, output[(i + 1) % size].y} };
        GLCD_Draw_Line(glcd, temp, dot_size, DIAGONAL);
    }

    if (is_filled) { Fill_Polygon(glcd, limit, size, dot_size); }
    if (round_edges) {}
}

void GLCD_Draw_Rect_Giving_Size(glcd_t* glcd, const point* top_left_origin, uint8_t width, uint8_t height, uint8_t dot_size, bool is_filled, bool round_edges)
{
    if (!glcd || !top_left_origin || width == 0 || height == 0 || width > ROW_SIZE) return;

    // Empêcher le dépassement d’écran
    if (top_left_origin->x + width > 128) width = 128 - top_left_origin->x;
    if (top_left_origin->y + height > 64) height = 64 - top_left_origin->y;

    point corners[4] = {
        { top_left_origin->x,             top_left_origin->y },                             // top-left
        { top_left_origin->x + width - 1, top_left_origin->y },                             // top-right
        { top_left_origin->x + width - 1, top_left_origin->y + height - 1 },                // bottom-right
        { top_left_origin->x,             top_left_origin->y + height - 1 }                 // bottom-left
    };

    point top[2]    = { { corners[0].x, corners[0].y }, { corners[1].x, corners[1].y } };
    point right[2]  = { { corners[1].x, corners[1].y }, { corners[2].x, corners[2].y } };
    point bottom[2] = { { corners[2].x, corners[2].y }, { corners[3].x, corners[3].y } };
    point left[2]   = { { corners[3].x, corners[3].y }, { corners[0].x, corners[0].y } };

    GLCD_Draw_Line(glcd, top, dot_size, get_direction(top[0], top[1]));
    GLCD_Draw_Line(glcd, right, dot_size, get_direction(right[0], right[1]));
    GLCD_Draw_Line(glcd, bottom, dot_size, get_direction(bottom[0], bottom[1]));
    GLCD_Draw_Line(glcd, left, dot_size, get_direction(left[0], left[1]));


    if (is_filled) { Fill_Polygon(glcd, corners, 4, dot_size); }
    if (round_edges) {}
}

//TODO
void GLCD_Draw_Rect_Giving_Points(glcd_t* glcd, const point* p, uint8_t dot_size, bool is_filled, bool round_edges)
{
    if (!glcd || !p) return;


    if (is_filled) { }
    if (round_edges) { }
}

void GLCD_Draw_Circle( glcd_t* glcd, const point* origin, uint8_t dot_size, uint8_t radius, uint16_t precision, bool is_filled)
{
    if (!glcd || !origin) return;

    point circle_approx[5000];
    for (uint16_t i=0; i<precision; i++)
    {
        circle_approx[i].x = origin->x + radius*cos((2*PI*i)/precision);
        circle_approx[i].y = origin->y + radius*sin((2*PI*i)/precision);
    }

    for (uint16_t i=0; i<precision; i++)
    {
        point temp[2] = { 
            { circle_approx[i].x, circle_approx[i].y }, 
            { circle_approx[(i+1)%precision].x, circle_approx[(i+1)%precision].y } 
        };
        GLCD_Draw_Line(glcd, temp, dot_size, DIAGONAL);
    }
    if (is_filled) { Fill_Polygon(glcd, circle_approx, precision, dot_size); }
}

void GLCD_Draw_Ellipse(glcd_t* glcd, const point focuses[2], float c, uint8_t dot_size, uint16_t precision, bool is_filled)
{
    if (!glcd || !focuses || precision < 3 || precision > 5000) return;

    float ax = focuses[0].x, ay = focuses[0].y;
    float bx = focuses[1].x, by = focuses[1].y;

    float fx = (ax + bx) / 2.0f;
    float fy = (ay + by) / 2.0f;
    float d = sqrt((bx - ax)*(bx - ax) + (by - ay)*(by - ay));
    if (d >= c) return;

    float a = c / 2.0f;
    float b = sqrt(a * a - (d / 2.0f) * (d / 2.0f));
    float theta = atan2(by - ay, bx - ax);

    point ellipse_approx[5000];

    for (uint16_t i = 0; i < precision; i++)
    {
        float t = 2.0f * PI * i / precision;
        float cos_t = cos(t);
        float sin_t = sin(t);

        float x = fx + a * cos_t * cos(theta) - b * sin_t * sin(theta);
        float y = fy + a * cos_t * sin(theta) + b * sin_t * cos(theta);

        // Clamp dans l'écran
        if (x >= 0 && x < 128 && y >= 0 && y < 64)
        {
            ellipse_approx[i].x = (uint8_t)(x + 0.5f);
            ellipse_approx[i].y = (uint8_t)(y + 0.5f);
        }
        else
        {
            ellipse_approx[i].x = 255;
            ellipse_approx[i].y = 255;
        }
    }

    for (uint16_t i = 0; i < precision; i++)
    {
        point temp[2] = {
            {ellipse_approx[i].x, ellipse_approx[i].y},
            {ellipse_approx[(i + 1) % precision].x, ellipse_approx[(i + 1) % precision].y}
        };
        GLCD_Draw_Line(glcd, temp, dot_size, DIAGONAL);
    }
    if (is_filled){}
}

float Module(point a, point b) { return sqrt((b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y)); }

uint64_t Transpose_Word(uint64_t word)
{
    uint64_t result = 0;

    for (uint8_t row = 0; row < 8; row++)
        for (uint8_t col = 0; col < 8; col++)
            if (word & (1ULL << (col * 8 + row)))
                result |= (1ULL << (row * 8 + col));

    return result;
}

uint64_t Find_Matching_Char_From_Bitmap(char c)
{
    uint8_t size = sizeof(font) / sizeof(font[0]);
    for (uint8_t i=0; i<size; i++)
    {
        if (c == font[i].c) return font[i].bitmap_code;
        else continue;
    }
}

uint8_t Reverse_Byte(uint8_t b)
{
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

void GLCD_Write_Char(glcd_t* glcd, point* p, char c)
{
    uint8_t page = p->y / 8;
    uint8_t line = p->x % 128;
    uint64_t res = Transpose_Word(Find_Matching_Char_From_Bitmap(c));

    for (uint8_t i = 0; i < 8; i++) 
    {
        uint8_t byte = (res >> (8 * (7 - i))) & 0xFF;
        byte = Reverse_Byte(byte);
        GLCD_Write(glcd, page, line + i, byte);
    }
}

void GLCD_Write_Text(glcd_t* glcd, point* p, const char* c)
{
    if (!glcd || !p || !c) return;

    point pos = *p;

    size_t len = strlen(c);
    for (size_t i = 0; i < len; i++)
    {
        GLCD_Write_Char(glcd, &pos, c[i]);
        pos.x += 8;

        if (pos.x >= 128) {
            pos.x = 0;
            pos.y += 8;
            if (pos.y >= 64) break;
        }
    }
}