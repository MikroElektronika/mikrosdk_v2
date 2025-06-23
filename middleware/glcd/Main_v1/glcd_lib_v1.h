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
typedef enum {
    CENTER_DIMENSIONS,
    CORNER_DIMENSIONS,
    THREE_POINTS
} parallelogram_mode_t;


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
typedef struct point {
    unsigned char x;
    unsigned char y;
} point;

typedef struct glcd {
    bool CS1;
    bool CS2;
    bool Enable;
    bool Reset;
    uint8_t READ_OR_WRITE;
    uint8_t DATA_OR_INSTRUCTION;
    uint8_t buffer[CS_SIZE][PAGE_SIZE][COL_PER_CHIP];
} glcd_t;

static uint64_t font[128] = {
	0x0,			    /* (space) */ // 0
	0x808080800080000,	/* ! */ // 1
	0x2828000000000000,	/* " */ // 2
	0x287C287C280000,	/* # */ // 3
	0x81E281C0A3C0800,	/* $ */ // 4
	0x6094681629060000,	/* % */ // 5
	0x1C20201926190000,	/* & */ // 6
	0x808000000000000,	/* ' */ // 7
	0x810202010080000,	/* ( */ // 8
	0x1008040408100000,	/* ) */ // 9
	0x2A1C3E1C2A000000,	/* * */ // 10
	0x8083E08080000,	/* + */ // 11
	0x81000,		    /* , */ // 12
	0x3C00000000,		/* - */ // 13
	0x80000,		    /* . */ // 14
	0x204081020400000,	/* / */ // 15
	0x1824424224180000,	/* 0 */ // 16
	0x8180808081C0000,	/* 1 */ // 17
	0x3C420418207E0000,	/* 2 */ // 18
	0x3C420418423C0000,	/* 3 */ // 19
	0x81828487C080000,	/* 4 */ // 20
	0x7E407C02423C0000,	/* 5 */ // 21
	0x3C407C42423C0000,	/* 6 */ // 22
	0x7E04081020400000,	/* 7 */ // 23
	0x3C423C42423C0000,	/* 8 */ // 24
	0x3C42423E023C0000,	/* 9 */ // 25
	0x80000080000,		/* : */ // 26
	0x80000081000,		/* ; */ // 27
	0x6186018060000,	/* < */ // 28
	0x7E007E000000,		/* = */ // 29
	0x60180618600000,	/* > */ // 30
	0x3844041800100000,	/* ? */ // 31
	0x3C449C945C201C,	/* @ */ // 32
	0x1818243C42420000,	/* A */ // 33
	0x7844784444780000,	/* B */ // 34
	0x3844808044380000,	/* C */ // 35
	0x7844444444780000,	/* D */ // 36
	0x7C407840407C0000,	/* E */ // 37
	0x7C40784040400000,	/* F */ // 38
	0x3844809C44380000,	/* G */ // 39
	0x42427E4242420000,	/* H */ // 40
	0x3E080808083E0000,	/* I */ // 41
	0x1C04040444380000,	/* J */ // 42
	0x4448507048440000,	/* K */ // 43
	0x40404040407E0000,	/* L */ // 44
	0x4163554941410000,	/* M */ // 45
	0x4262524A46420000,	/* N */ // 46
	0x1C222222221C0000,	/* O */ // 47
	0x7844784040400000,	/* P */ // 48
	0x1C222222221C0200,	/* Q */ // 49
	0x7844785048440000,	/* R */ // 50
	0x1C22100C221C0000,	/* S */ // 51
	0x7F08080808080000,	/* T */ // 52
	0x42424242423C0000,	/* U */ // 53
	0x8142422424180000,	/* V */ // 54
	0x4141495563410000,	/* W */ // 55
	0x4224181824420000,	/* X */ // 56
	0x4122140808080000,	/* Y */ // 57
	0x7E040810207E0000,	/* Z */ // 58
	0x3820202020380000,	/* [ */ // 59
	0x4020100804020000,	/* \ */ // 60
	0x3808080808380000,	/* ] */ // 61
	0x1028000000000000,	/* ^ */ // 62
	0x7E0000,		    /* _ */ // 63
	0x1008000000000000,	/* ` */ // 64
	0x3C023E463A0000,	/* a */ // 65
	0x40407C42625C0000,	/* b */ // 66
	0x1C20201C0000,		/* c */ // 67
	0x2023E42463A0000,	/* d */ // 68
	0x3C427E403C0000,	/* e */ // 69
	0x18103810100000,	/* f */ // 70
	0x344C44340438,		/* g */ // 71
	0x2020382424240000,	/* h */ // 72
	0x800080808080000,	/* i */ // 73
	0x800180808080870,	/* j */ // 74
	0x20202428302C0000,	/* k */ // 75
	0x1010101010180000,	/* l */ // 76
	0x665A42420000,		/* m */ // 77
	0x2E3222220000,		/* n */ // 78
	0x3C42423C0000,		/* o */ // 79
	0x5C62427C4040,		/* p */ // 80
	0x3A46423E0202,		/* q */ // 81
	0x2C3220200000,		/* r */ // 82
	0x1C201804380000,	/* s */ // 83
	0x103C1010180000,	/* t */ // 84
	0x2222261A0000,		/* u */ // 85
	0x424224180000,		/* v */ // 86
	0x81815A660000,		/* w */ // 87
	0x422418660000,		/* x */ // 88
	0x422214081060,		/* y */ // 89
	0x3C08103C0000,		/* z */ // 90
	0x1C103030101C0000,	/* { */ // 91
	0x808080808080800,	/* | */ // 92
	0x38080C0C08380000,	/* } */ // 93
	0x324C000000,		/* ~ */ // 94
	0x7E7E7E7E7E7E0000	/* DEL */ // 95
};


static port_t data_out, data_in, see_cmd, see;
static digital_out_t cs1d, cs2d, ed, resetd, rsd, rwd;

/* Functions Prototypes */

/* Initialize functions */
/*---------Function name----------//----------Arguments---------------*/
void GLCD_Port_Init                         ( void );
void Apply_changes                          ( void );
void Reset                                  ( void );
void GLCD_Init                              ( glcd_t* glcd );
void GLCD_Set_Page                          ( glcd_t* glcd, uint8_t page );
void GLCD_Display_Start_Line                ( glcd_t* glcd, uint8_t stline );
void GLCD_Set_Y                             ( glcd_t* glcd, uint8_t y_pos );
void GLCD_Clear                             ( glcd_t *glcd );                              //vide le buffer, (tilise la fonction write(0))
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

void GLCD_Draw_Rect(glcd_t* glcd, parallelogram_mode_t mode, point* input, uint8_t size, uint8_t dot_size, bool filled, bool rounded)
{
    if (!glcd || !input) return;
    switch(mode) {}
}

uint8_t filt = 0, page, line;
void GLCD_Write_Char( glcd_t* glcd, point* p, uint64_t c )
{
    page = p->y / 8, line = p->x % 128;

    filt = c & 0xFF;
    GLCD_Write(glcd, page, line, filt);

    filt = (c & 0xFF00)>>8;
    GLCD_Write(glcd, page, line+1, filt);

    filt = (c & 0xFF0000)>>16;
    GLCD_Write(glcd, page, line+2, filt);

    filt = (c & 0xFF000000)>>24;
    GLCD_Write(glcd, page, line+3, filt);

    filt = (c & 0xFF00000000)>>32;
    GLCD_Write(glcd, page, line+4, filt);

    filt = (c & 0xFF0000000000)>>40;
    GLCD_Write(glcd, page, line+5, filt);

    filt = (c & 0xFF000000000000)>>48;
    GLCD_Write(glcd, page, line+6, filt);

    filt = (c & 0xFF00000000000000)>>56;
    GLCD_Write(glcd, page, line+7, filt);
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

