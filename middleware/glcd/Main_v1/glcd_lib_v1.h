#include "MikroSDK.Board"
#include "MikroSDK.Driver"
#include "MikroSDK.Driver.GPIO.In"
#include "MikroSDK.Driver.GPIO.Out"
#include "MikroSDK.Driver.GPIO.Port"

typedef enum {
    ON = 0x3F, on = 0x3F, On = 0x3F, oN = 0x3F, 
    
    OFF = 0x3E, Off = 0x3E, oFf = 0x3E, ofF = 0x3E,
    OFf = 0x3E, oFF = 0x3E, OfF = 0x3E, off = 0x3E,
    
    DATA = 0, INSTRUCTION = 1,
    READ = 1, WRITE = 0
} config;

typedef enum { VERTICAL_LINE, HORIZONTAL_LINE, DIAGONAL } line_direction;
typedef enum { CENTER_DIMENSIONS, CORNER_DIMENSIONS, THREE_POINTS } rect_mode_t;
typedef enum { FAST_MODE = 15, DEFAULT_MODE = 100, PRECISION_MODE = 3000 } circle_mode_t;


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
typedef struct point { uint8_t x; uint8_t y; } point;
typedef struct segment { point pts[2]; uint8_t line_size; } segment;
typedef struct rect { uint8_t w; uint8_t h; uint8_t line_size; bool filled; bool rounded; } rect;
typedef struct circle { uint8_t o; uint8_t r; uint8_t line_size; bool filled; } circle;
typedef struct ellipse { point focuses[2]; float a; uint8_t line_size; bool filled; } ellipse;
typedef struct CHAR { char c; uint64_t bitmap_code; } CHAR;

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

/* Functions Prototypes */
/* Initialize functions */
/*---------Function name----------//----------Arguments---------------*/
void GLCD_Port_Init                         ( glcd_t* glcd );
void GLCD_Init                              ( glcd_t* glcd );
void GLCD_Set_Page                          ( glcd_t* glcd, uint8_t page );
void GLCD_Display_Start_Line                ( glcd_t* glcd, uint8_t stline );
void GLCD_Set_Y                             ( glcd_t* glcd, uint8_t y_pos );
void GLCD_Clear                             ( glcd_t *glcd );                              //vide le buffer, (utilise la fonction write(0))
void GLCD_Display                           ( glcd_t* glcd, uint8_t turn_on_off );         //cache le buffer, sans le supprimer
void Apply_changes                          ( glcd_t* glcd );
void CS_Config                              ( glcd_t* glcd, bool cs1, bool cs2 );

/* Read and Write functions */
uint8_t GLCD_Read                           ( glcd_t* glcd, uint8_t page, uint8_t lign );
void GLCD_Write                             ( glcd_t *glcd, uint8_t page, uint8_t column, uint8_t data_to_write );
void GLCD_Write_Char                        ( glcd_t* glcd, point* p, char c );
void GLCD_Write_Text                        ( glcd_t* glcd, point* p, const char* c );

/* Drawing functions */
void GLCD_Fill_Screen                       ( glcd_t* glcd, uint8_t pattern );
void GLCD_Draw_Dots                         ( glcd_t* glcd, const point* pts, uint8_t size, uint8_t dot_size );
void GLCD_Draw_Line                         ( glcd_t* glcd, segment s, uint8_t direction );
void GLCD_Draw_Rect                         ( glcd_t* glcd, const point* p, uint16_t psize, const rect* r, uint16_t rsize, uint8_t line_sz );
void GLCD_Draw_Rect_Giving_Points           ( glcd_t* glcd, const point* p, uint8_t size, uint8_t dot_size, bool is_filled, bool round_edges);
void GLCD_Draw_Polygon                      ( glcd_t* glcd, const segment* edges, uint8_t size, bool is_filled, bool round_edges );
void GLCD_Draw_Circle                       ( glcd_t* glcd, const point* origin, uint8_t dot_size, uint8_t radius, uint16_t precision, bool is_filled);


/* Utils */
float distance                              ( point a, point b );
void Sort_Points_Nearest_Neighbor           ( const segment* input, segment* output, uint8_t size );
void Fill_Polygon                           ( glcd_t* glcd, const segment* edges, uint8_t size );
uint64_t Transpose_Word                     ( uint64_t word );
uint64_t Find_Matching_Char_From_Bitmap     ( char c );
uint8_t Reverse_Byte                        ( uint8_t b );

void GLCD_Port_Init( glcd_t* glcd )
{
    port_init( &glcd->data_out, PORT_E, 0xFF, HAL_LL_GPIO_DIGITAL_OUTPUT );
    digital_out_init( &glcd->cs1d, CS1_PIN );
    digital_out_init( &glcd->cs2d, CS2_PIN );
    digital_out_init( &glcd->ed, E_PIN );
    digital_out_init( &glcd->resetd, RESET_PIN );
    digital_out_init( &glcd->rsd, RS_PIN );
    digital_out_init( &glcd->rwd, RW_PIN );
}

void GLCD_Init( glcd_t* glcd )
{
    GLCD_Port_Init(glcd);

    digital_out_high( &glcd->ed );
    digital_out_high( &glcd->cs1d );
    digital_out_high( &glcd->cs2d );
    digital_out_high( &glcd->resetd );
    digital_out_low( &glcd->rsd );
    digital_out_high( &glcd->rwd );
    Apply_changes(glcd);
}

void Apply_changes( glcd_t* glcd )
{
    digital_out_high( &glcd->ed );
    Delay_us(10);
    digital_out_low( &glcd->ed );
    Delay_us(10);
}

void CS_Config(glcd_t* glcd, bool cs1, bool cs2)
{
    if (!glcd) return;
    digital_out_write(&glcd->cs1d, (cs1 == 1) ? 0 : 1);
    digital_out_write(&glcd->cs2d, (cs2 == 1) ? 0 : 1);
}

void GLCD_Set_Y( glcd_t* glcd, uint8_t y_pos )
{
    if ( !glcd || y_pos > 64 ) return;

    digital_out_low( &glcd->rsd );                    // RS = 0 (instruction)
    digital_out_low( &glcd->rwd );                    // RW = 0 (ecriture)
    port_write( &glcd->data_out, (0x40 | (y_pos & 0x3F)) );
    Apply_changes(glcd);
}

void GLCD_Set_Page( glcd_t* glcd, uint8_t page )
{
    if ( !glcd || page > 7 ) return;             

    digital_out_low( &glcd->rsd );                    // RS = 0 (instruction)
    digital_out_low( &glcd->rwd );                    // RW = 0 (ecriture)
    port_write( &glcd->data_out, (0xB8 | (page & 0x07)) );       // We only care about the lower 3 bits for page address
    Apply_changes(glcd);
}

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
    digital_out_low(&glcd->ed);
    digital_out_high(&glcd->rsd);
    digital_out_low(&glcd->rwd); 
    port_write(&glcd->data_out, data_to_write);
    Apply_changes(glcd);

    glcd->buffer[(line < 64) ? 0 : 1][page][line % 64] = data_to_write;
}

void GLCD_Display( glcd_t* glcd, uint8_t turn_on_off )
{
    if ( !glcd ) return;
    if (!IS_ON( turn_on_off ) && !IS_OFF( turn_on_off ) ) return;

    for (uint8_t k = 0; k < 2; k++)
    {
        CS_Config( glcd, k%2, (k+1)%2 );
        digital_out_low( &glcd->rsd );                // RS = 0 (instruction)
        digital_out_low( &glcd->rwd );                // RW = 0 (ecriture)
        port_write( &glcd->data_out, turn_on_off );
        Apply_changes(glcd);
    }
}

uint8_t GLCD_Read(glcd_t* glcd, uint8_t page, uint8_t column)
{
    if (!glcd || page >= PAGE_SIZE || column >= ROW_SIZE) return 0;

    uint8_t chip = (column < 64) ? 0 : 1;
    uint8_t col_in_chip = column % 64;
    return glcd->buffer[chip][page][col_in_chip];
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

void GLCD_Draw_Line( glcd_t* glcd, segment s, uint8_t direction )
{
    if (s.pts[0].x >= 128 || s.pts[1].x >= 128 || s.pts[0].y >= 64 || s.pts[1].y >= 64) return;

    uint8_t pt0_page = (s.pts[0].y / 8);
    uint8_t pt1_page = (s.pts[1].y / 8);
    uint8_t pt0_line = (s.pts[0].x % 128);
    uint8_t pt1_line = (s.pts[1].x % 128);
    switch(direction)
    {
        case VERTICAL_LINE:
        {
            if (s.pts[0].x != s.pts[1].x) return;
            int x = s.pts[0].x, y0 = s.pts[0].y, y1 = s.pts[1].y;
            if (y0 > y1) { int temp = y0; y0 = y1; y1 = temp; }

            for (int y = y0; y <= y1; y++) 
            {
                for (uint8_t dx = 0; dx < s.line_size; dx++) 
                {
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
            if (s.pts[0].y != s.pts[1].y) return;
            int y = s.pts[0].y, x0 = s.pts[0].x, x1 = s.pts[1].x;
            if (x0 > x1) { int temp = x0; x0 = x1; x1 = temp; }

            for (int x = x0; x <= x1; x++) 
            {
                for (uint8_t dy = 0; dy < s.line_size; dy++) 
                {
                    int current_y = y + dy;
                    if (x < 0 || x >= 128 || current_y < 0 || current_y >= 64) continue;

                    uint8_t page = current_y / 8;
                    uint8_t bit_in_page = 1 << (current_y % 8);
                    uint8_t current = GLCD_Read(glcd, page, x);
                    current |= bit_in_page;
                    GLCD_Write(glcd, page, x, current);
                }
            }
            break;
        }

        //Bresenham Algorithm
        case DIAGONAL:
        {
            int x0 = s.pts[0].x, y0 = s.pts[0].y;
            int x1 = s.pts[1].x, y1 = s.pts[1].y;

            int dx = abs(x1 - x0), dy = abs(y1 - y0);
            int sx = (x0 < x1) ? 1 : -1, sy = (y0 < y1) ? 1 : -1;
            int err = dx - dy;

            while (1)
            {
                for (uint8_t dy_dot = 0; dy_dot < s.line_size; dy_dot++)
                {
                    for (uint8_t dx_dot = 0; dx_dot < s.line_size; dx_dot++)
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

uint8_t GLCD_Read_LL(glcd_t* glcd, uint8_t page, uint8_t column) 
{
    if (!glcd || page >= PAGE_SIZE || column >= ROW_SIZE) return 0;

    port_init( &glcd->data_out, PORT_E, 0xFF, HAL_LL_GPIO_DIGITAL_INPUT );
    uint8_t chip = (column < 64) ? 0 : 1;
    uint8_t col_in_chip = column % 64;

    CS_Config(glcd, chip == 0, chip == 1);
    GLCD_Set_Y(glcd, col_in_chip);
    GLCD_Set_Page(glcd, page);

    // Configuration pour lecture de données
    digital_out_high(&glcd->rsd);  // RS = 1 (data)
    digital_out_high(&glcd->rwd);  // RW = 1 (read)

    // Dummy read (nécessaire pour charger le registre de sortie)
    digital_out_high(&glcd->ed);   // E = 1
    Delay_us(1);             // tWH ≥ 450 ns
    digital_out_low(&glcd->ed);    // E = 0
    Delay_us(1);

    uint8_t data_readed = port_read(&glcd->data_out);  // Lecture du bus de données
    port_init( &glcd->data_out, PORT_E, 0xFF, HAL_LL_GPIO_DIGITAL_OUTPUT );
    Apply_changes(glcd);

    return data_readed;
}

float distance(point a, point b) 
{
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

void Sort_Points_Nearest_Neighbor(const segment* input, segment* output, uint8_t size) 
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

void Fill_Polygon(glcd_t* glcd, const segment* edges, uint8_t size)
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
    Sort_Points_Nearest_Neighbor(edges, sorted, size);

    for (uint8_t y = min_y; y <= max_y; y++) 
    {
        uint8_t x_intersections[64];
        uint8_t nb_x = 0;

        for (uint8_t i = 0; i < size; i++) 
        {
            point p1 = sorted[i].pts[0];
            point p2 = sorted[i].pts[1];

            if (p1.y == p2.y) continue;
            if (p1.y > p2.y) 
            {
                point temp = p1;
                p1 = p2;
                p2 = temp;
            }

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
            GLCD_Draw_Line(glcd, s, HORIZONTAL_LINE);
        }
    }
}

void Fill_Circle(glcd_t* glcd, const point* contour, uint16_t precision, uint8_t dot_size)
{
    if (!glcd || !contour || dot_size == 0) return;

    uint8_t min_y = 255, max_y = 0, size = sizeof(contour)/sizeof(contour[0]);
    uint16_t i;

    for (i = 0; i < size; i++)
    {
        if (contour[i].y < min_y) min_y = contour[i].y;
        if (contour[i].y > max_y) max_y = contour[i].y;
    }

    for (uint8_t y = min_y; y <= max_y; y++)
    {
        uint8_t x_intersections[128];
        uint8_t count_x = 0;

        for (i = 0; i < size; i++)
        {
            point p1 = contour[i];
            point p2 = contour[(i + 1) % size];

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
            GLCD_Draw_Line(glcd, s, HORIZONTAL_LINE);
        }
    }
}

void GLCD_Draw_Polygon(glcd_t* glcd, const segment* edges, uint8_t size, bool is_filled, bool round_edges)
{
    if (!glcd || !edges) return;

    segment output[64];
    Sort_Points_Nearest_Neighbor(edges, output, size);
    for (uint8_t i = 0; i < size; i++) { GLCD_Draw_Line(glcd, output[i], DIAGONAL); }

    if (is_filled) { Fill_Polygon(glcd, output, output[0].line_size); }
    if (round_edges) {}
}

void GLCD_Draw_Rect(glcd_t* glcd, const point* p, uint16_t psize, const rect* r, uint16_t rsize)
{
    if (!glcd || !r || !p || psize != rsize ) return;

    for (uint16_t i=0; i<psize; i++) 
    {
        uint8_t x0 = p[i].x, y0 = p[i].y;
        uint8_t x1 = x0 + r[i].w, y1 = y0 + r[i].h;
        uint8_t line_sz = r[i].line_size;

        segment rect[4] = {
            {{{x0, y0},{x1, y0}}, line_sz},
            {{{x0, y0},{x0, y1}}, line_sz},
            {{{x1, y0},{x1, y1}}, line_sz},
            {{{x0, y1},{x1, y1}}, line_sz}
        };

        for (uint16_t k=0; k<4; k++) { GLCD_Draw_Line(glcd, rect[k], DIAGONAL); }
        if (r[j].filled) { Fill_Polygon(glcd, rect, 4); }
        if (r[j].rounded) {}
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

void GLCD_Draw_Rect_Giving_Points(glcd_t* glcd, const point* p, uint8_t size, uint8_t dot_size, bool is_filled, bool round_edges)
{
    if (!glcd || !p || size == 0) return;

    switch (size)
    {
        case 1: { GLCD_Draw_Dots(glcd, p, size, dot_size); break; }
        case 2: { segment s = { {{p[0].x, p[0].y}, {p[1].x, p[1].y} }, dot_size }; GLCD_Draw_Line(glcd, s, DIAGONAL); break; }
        case 3: 
        {
            if (dot_product(p[0], p[1], p[2]) == 0) 
            {
                point p3 = { p[1].x + (p[2].x - p[0].x), p[1].y + (p[2].y - p[0].y) };
                segment rect[4] = {
                    { {{ p[0].x, p[0].y }, { p[1].x, p[1].y }}, dot_size },
                    { {{ p[1].x, p[1].y }, { p3.x, p3.y }}, dot_size },
                    { {{ p3.x, p3.y }, { p[2].x, p[2].y }}, dot_size },
                    { {{ p[2].x, p[2].y }, { p[0].x, p[0].y }}, dot_size }
                };
                GLCD_Draw_Polygon(glcd, rect, 4, is_filled, round_edges);
            } else {
                segment tri[3] = {
                    { {{ p[0].x, p[0].y }, { p[1].x, p[1].y }}, dot_size },
                    { {{ p[1].x, p[1].y }, { p[2].x, p[2].y }}, dot_size },
                    { {{ p[2].x, p[2].y }, { p[0].x, p[0].y }}, dot_size }
                };
                GLCD_Draw_Polygon(glcd, tri, 3, is_filled, round_edges);
            }
            break;
        }

        case 4: 
        {
            bool right_angles =
                dot_product(p[0], p[1], p[3]) == 0 &&
                dot_product(p[1], p[2], p[0]) == 0 &&
                dot_product(p[2], p[3], p[1]) == 0 &&
                dot_product(p[3], p[0], p[2]) == 0;

            segment rect[4] = {
                { { { p[0].x, p[0].y }, { p[1].x, p[1].y } }, dot_size },
                { { { p[1].x, p[1].y }, { p[2].x, p[2].y } }, dot_size },
                { { { p[2].x, p[2].y }, { p[3].x, p[3].y } }, dot_size },
                { { { p[3].x, p[3].y }, { p[0].x, p[0].y } }, dot_size }
            };
            GLCD_Draw_Polygon(glcd, rect, 4, is_filled, round_edges);
            break;
        }
        default: break;
    }
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
        segment s = { {{circle_approx[i].x, circle_approx[i].y}, {circle_approx[(i+1)%precision].x, circle_approx[(i+1)%precision].y}}, dot_size };
        GLCD_Draw_Line(glcd, s, DIAGONAL);
    }
    if (is_filled) { Fill_Circle(glcd, circle_approx, precision, dot_size); }
}

void GLCD_Draw_Ellipse(glcd_t* glcd, const point params[2], uint8_t dot_size, uint16_t precision, bool is_filled)
{
    if (!glcd || !params || precision < 3 || precision > 5000) return;

    float a = params[2].x;
    float b = params[2].y;
    if (a <= 0 || b <= 0) return;

    float c = sqrt(a*a - b*b);
    float e = c / a;
    float p = (b*b) / a;

    // Centre de l’ellipse
    float cx = (params[0].x + params[1].x) / 2.0f;
    float cy = (params[0].y + params[1].y) / 2.0f;

    // Angle de l'axe principal
    float theta_axis = atan2(params[1].y - params[0].y, params[1].x - params[0].x);

    point ellipse[5000];

    for (uint16_t i = 0; i < precision; i++)
    {
        float theta = (2.0f * PI * i) / precision;
        float r = p / (1.0f - e * cos(theta));

        // Position locale par rapport au foyer
        float x_local = r * cos(theta);
        float y_local = r * sin(theta);

        // Tourner selon l'angle de l’ellipse
        float x_rot = x_local * cos(theta_axis) - y_local * sin(theta_axis);
        float y_rot = x_local * sin(theta_axis) + y_local * cos(theta_axis);

        // Décaler vers le bon foyer (focus[0])
        float x = cx + x_rot;
        float y = cy + y_rot;

        if (x >= 0 && x < 128 && y >= 0 && y < 64) { ellipse[i].x = x; ellipse[i].y = y; }
        else { ellipse[i].x = 255; ellipse[i].y = 255; }
    }

    for (uint16_t i=0; i<precision; i++)
    {
        segment s = { {{ellipse[i].x, ellipse[i].y}, {ellipse[(i+1)%precision].x, ellipse[(i+1)%precision].y}}, dot_size };
        GLCD_Draw_Line(glcd, s, DIAGONAL);
    }

    if (is_filled) { Fill_Circle(glcd, ellipse, precision, dot_size); }
}

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
    return 0;
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

/**
 * @brief TODO
 *  - Add Doxygen description of the functions. 
 *  - Make the behaviour universal (about MCUs)
 *  - Optimize the code for better performance and readability.
 *  - Add error handling and validation where necessary.
 */

