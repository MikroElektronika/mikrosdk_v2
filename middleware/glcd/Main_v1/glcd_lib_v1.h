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
    READ = 1, WRITE = 0, DEFAULT_CONFIG = 0
} config;

typedef enum { VERTICAL_LINE, HORIZONTAL_LINE, ELSE } line_direction;
typedef enum { CENTER_DIMENSIONS, CORNER_DIMENSIONS, THREE_POINTS } rect_mode_t;


#define IS_ON( x )              ( (x == ON) || (x == oN) || (x == on) || (x == oN) )
#define IS_OFF( x )             ( (x == OFF) || (x == Off) || (x == oFf) || (x == ofF) || (x == OFf) || (x == oFF) || (x == ofF) || (x == off) )

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

/* GLCD Structure context/config creation and basic geometry (point) structure*/
typedef struct point { unsigned char x; unsigned char y; } point;
typedef struct CHAR { char c; uint64_t bitmap_code; } CHAR;

typedef struct glcd {
    bool CS1;
    bool CS2;
    bool Enable;
    bool Reset;
    uint8_t READ_OR_WRITE;
    uint8_t DATA_OR_INSTRUCTION;
    uint8_t buffer[CS_SIZE][PAGE_SIZE][COL_PER_CHIP];
} glcd_t;

const CHAR font[] = {
    { ' ',  0x0000000000000000 },     // 0
    { '1',  0x0808080800080000 },     // 1
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
    { 'd',  0x20203E42463A0000 },     // 68
    { 'e',  0x003C427E403C0000 },     // 69
    { 'f',  0x0018103810100000 },     // 70
    { 'g',  0x00344C4434043800 },     // 71
    { 'h',  0x2020382424240000 },     // 72
    { 'i',  0x0000080080808000 },     // 73
    { 'j',  0x0008018080808070 },     // 74
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



static port_t data_out, data_in, see_cmd, see;
static digital_out_t cs1d, cs2d, ed, resetd, rsd, rwd;

/* Functions Prototypes */

/* Initialize functions */
/*---------Function name----------//----------Arguments---------------*/
void GLCD_Port_Init                         ( void );
void Apply_changes                          ( void );
void GLCD_Init                              ( glcd_t* glcd );
void GLCD_Set_Page                          ( glcd_t* glcd, uint8_t page );
void GLCD_Display_Start_Line                ( glcd_t* glcd, uint8_t stline );
void GLCD_Set_Y                             ( glcd_t* glcd, uint8_t y_pos );
void GLCD_Clear                             ( glcd_t *glcd );                              //vide le buffer, (utilise la fonction write(0))
void GLCD_Display                           ( glcd_t* glcd, uint8_t turn_on_off );         //cache le buffer, sans le supprimer

/* Read and Write functions */
uint8_t GLCD_Read                           ( glcd_t* glcd, uint8_t page, uint8_t lign );
void GLCD_Write                             ( glcd_t *glcd, uint8_t page, uint8_t column, uint8_t data_to_write );

/* Drawing functions */
void GLCD_Fill_Screen                       ( glcd_t* glcd, uint8_t pattern );
void GLCD_Draw_Dots                         ( glcd_t* glcd, point* pts, uint8_t size, uint8_t dot_size );
void GLCD_Draw_Line                         ( glcd_t* glcd, const point* pts, bool is_vertical );
void GLCD_Draw_Rect                         ( glcd_t* glcd, const point* limit, bool is_filled , bool round_edges ); 
void GLCD_Draw_Shape                        ( glcd_t* glcd, const point* limit, bool is_filled ); 
void GLCD_Draw_Circle                       ( glcd_t* glcd, const point* origin, bool is_filled );

void GLCD_Write_Char                        ( glcd_t* glcd, point* p, uint64_t c );
void GLCD_Write_String                      ( glcd_t* glcd, point* p, const char* c );


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

void GLCD_Draw_Dots(glcd_t* glcd, point* pts, uint8_t size, uint8_t dot_size)
{
    if (!glcd || !pts || dot_size > 8) return;

    uint8_t pattern = 0x00;
    switch(dot_size)
    {
        case 0: return;
        case 2:
        case 3: pattern = 0x18; break;
        case 4:
        case 5: pattern = 0x3C; break;
        case 6:
        case 7: pattern = 0x7E; break;
        case 8: pattern = 0xFF; break;
    }

    for (uint8_t i = 0; i < size; i++)
    {
        if (pts[i].x > 127 || pts[i].y > 63) continue;

        uint8_t page = pts[i].y / 8;
        uint8_t lign = pts[i].x;

        for (uint8_t j = 0; j < dot_size + 1; j++)
            GLCD_Write(glcd, page, lign + j, pattern);

        // Ajout pour éviter traînée (facultatif)
        GLCD_Write(glcd, page, lign + dot_size + 1, 0x00);
    }
}

void GLCD_Draw_Line( glcd_t* glcd, point pts[2], uint8_t dot_size, uint8_t direction )
{
    if (!glcd || !pts || pts[0].x > 128 || pts[1].x > 128 || pts[0].y > 64 || pts[1].y > 64 ) return;

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

            for (uint8_t i=pt0_page; i<pt1_page; i++)
                for (uint8_t j=0; j<dot_size+1; j++)
                    GLCD_Write(glcd, i, pts[0].x+j, 0xFF);
            break;
        }
        
        case HORIZONTAL_LINE:
        {
            if (pts[0].y != pts[1].y) return;
        
            for (uint8_t i=pt0_line; i<pt1_line; i++)
                GLCD_Write(glcd, pt0_page, pts[0].x+i, pattern);
            break;
        }

        //Bresenham Algorithm for ploting a "diagonal" line
        case ELSE:
        {
            int x0 = pts[0].x;
            int y0 = pts[0].y;
            int x1 = pts[1].x;
            int y1 = pts[1].y;

            int dx = abs(x1 - x0);
            int dy = abs(y1 - y0);
            int sx = (x0 < x1) ? 1 : -1;
            int sy = (y0 < y1) ? 1 : -1;
            int err = dx - dy;

            while (1)
            {
                for (uint8_t dy_dot = 0; dy_dot < dot_size; dy_dot++)
                {
                    for (uint8_t dx_dot = 0; dx_dot < dot_size; dx_dot++)
                    {
                        int x = x0 + dx_dot;
                        int y = y0 + dy_dot;

                        if (x < 0 || x >= 128 || y < 0 || y >= 64)
                            continue;

                        uint8_t page = y / 8;
                        uint8_t bit_in_page = 1 << (y % 8);

                        // Lire l’état actuel du pixel
                        uint8_t current = GLCD_Read(glcd, page, x);
                        // Fusionner avec le bit à écrire
                        current |= bit_in_page;
                        // Écrire le nouveau pixel
                        GLCD_Write(glcd, page, x, current);
                    }
                }

                if (x0 == x1 && y0 == y1)
                    break;

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

void Sort_Points_Convex_Hull(point* pts, uint8_t size)
{
    if (!pts || size < 3) return;

    // 1. Trouver le point le plus en bas à gauche (référence)
    uint8_t ref_idx = 0;
    for (uint8_t i = 1; i < size; i++) {
        if (pts[i].y < pts[ref_idx].y || (pts[i].y == pts[ref_idx].y && pts[i].x < pts[ref_idx].x)) {
            ref_idx = i;
        }
    }

    // Échanger avec l'élément en tête
    if (ref_idx != 0) {
        point temp = pts[0];
        pts[0] = pts[ref_idx];
        pts[ref_idx] = temp;
    }
    point ref = pts[0];

    // 2. Trier les autres points selon l'angle polaire avec ref
    for (uint8_t i = 1; i < size - 1; i++) {
        for (uint8_t j = i + 1; j < size; j++) {
            int dx1 = pts[i].x - ref.x;
            int dy1 = pts[i].y - ref.y;
            int dx2 = pts[j].x - ref.x;
            int dy2 = pts[j].y - ref.y;
            int cross = dx1 * dy2 - dy1 * dx2;

            if (cross < 0 || (cross == 0 &&
                (dx2 * dx2 + dy2 * dy2) < (dx1 * dx1 + dy1 * dy1))) {
                point temp = pts[i];
                pts[i] = pts[j];
                pts[j] = temp;
            }
        }
    }

    // 3. Construction de l’enveloppe convexe (pile)
    point stack[64]; // max 64 points, adapter si nécessaire
    uint8_t m = 0;

    stack[m++] = pts[0];
    stack[m++] = pts[1];

    for (uint8_t i = 2; i < size; i++) {
        while (m >= 2) {
            point a = stack[m - 2];
            point b = stack[m - 1];
            point c = pts[i];

            int orient = (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
            if (orient > 0) break; // virage à gauche
            m--; // sinon on retire
        }
        stack[m++] = pts[i];
    }

    // 4. Réécriture du tableau d’origine avec les points de l’enveloppe
    for (uint8_t i = 0; i < m; i++) {
        pts[i] = stack[i];
    }
}

void GLCD_Draw_Polygon(glcd_t* glcd, point* limit, uint8_t size, uint8_t dot_size, bool is_filled, bool round_edges)
{
    if (!glcd || !limit ) return;

    Sort_Points_Convex_Hull(limit, size);
    for (uint8_t i = 0; i < size; i++)
    {
        point temp[2] = {
            { limit[i].x, limit[i].y },
            { limit[(i + 1) % size].x, limit[(i + 1) % size].y }
        };
        GLCD_Draw_Line(glcd, temp, dot_size, ELSE);
    }

    if (is_filled) {}
    if (round_edges) {}
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


void GLCD_Write_Char(glcd_t* glcd, point* p, char c)
{
    uint8_t page = p->y / 8;
    uint8_t line = p->x % 128;
    uint64_t res = Find_Matching_Char_From_Bitmap(c);
    
    for (uint8_t i = sizeof(uint64_t); i > 0; i--) 
    {
        uint8_t filt = (res >> (8 * i)) & 0xFF;  // extraire chaque octet
        GLCD_Write(glcd, page, line + (7 - i), filt);
    }
}




/**
 * @brief TODO
 *  - Add Doxygen description of the functions.
 *  - Change the glcd structure to avoid defining pins directly, but 
 *    instead exclusively via stucture members.
 *  - Change the variable names to be more descriptive and consistent.
 *  - Finish and test the GLCD functions. 
 *  - Make the behaviour universal (about MCUs)
 *  - Optimize the code for better performance and readability.
 *  - Add error handling and validation where necessary.
 */

