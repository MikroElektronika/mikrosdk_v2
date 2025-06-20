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
#define GLCD_BUFFER_SIZE        ( COL_SIZE * ROW_SIZE / 8 )

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

void GLCD_Draw_Line( glcd_t* glcd, point* pts, uint8_t dot_size, uint8_t direction )
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

        //Bresenham Algorithm for ploting a line
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

void Sort_Points(point* pts, uint8_t size)
{
    if (!pts || size < 3) return;

    // Calcul du centroïde
    int cx = 0, cy = 0;
    for (uint8_t i = 0; i < size; i++) {
        cx += pts[i].x;
        cy += pts[i].y;
    }
    cx /= size;
    cy /= size;

    // Tri par orientation autour du centroïde
    for (uint8_t i = 0; i < size - 1; i++) {
        for (uint8_t j = i + 1; j < size; j++) {
            int dx1 = pts[i].x - cx;
            int dy1 = pts[i].y - cy;
            int dx2 = pts[j].x - cx;
            int dy2 = pts[j].y - cy;

            // Produit vectoriel : dx1*dy2 - dx2*dy1
            int cross = dx1 * dy2 - dx2 * dy1;

            // Si le point j est "avant" le point i dans l'ordre angulaire
            if (cross < 0) {
                point temp = pts[i];
                pts[i] = pts[j];
                pts[j] = temp;
            }
        }
    }
}

void GLCD_Draw_Parallelogram(glcd_t* glcd, point* limit, uint8_t size, uint8_t dot_size, bool is_filled, bool round_edges)
{
    if (!glcd || !limit || size != 4) return;
    
    Sort_Points(limit, size);
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

    point corners[4];
    switch (mode)
    {
        case CENTER_DIMENSIONS:
        {
            point center = input[0];
            uint8_t width = input[1].x;
            uint8_t height = input[1].y;

            corners[0] = (point){ center.x - width / 2, center.y - height / 2 };
            corners[1] = (point){ center.x + width / 2, center.y - height / 2 };
            corners[2] = (point){ center.x + width / 2, center.y + height / 2 };
            corners[3] = (point){ center.x - width / 2, center.y + height / 2 };
            break;
        }

        case CORNER_DIMENSIONS:
        {
            point corner = input[0];
            uint8_t width = input[1].x;
            uint8_t height = input[1].y;

            corners[0] = corner;
            corners[1] = (point){ corner.x + width, corner.y };
            corners[2] = (point){ corner.x + width, corner.y + height };
            corners[3] = (point){ corner.x, corner.y + height };
            break;
        }

        case THREE_POINTS:
        {
            point p1 = input[0];
            point p2 = input[1];
            point p3 = input[2];
            point p4 = { p1.x + (p3.x - p2.x), p1.y + (p3.y - p2.y) };

            corners[0] = p1;
            corners[1] = p2;
            corners[2] = p3;
            corners[3] = p4;
            break;
        }
    }
    GLCD_Draw_Parallelogram(glcd, corners, 4, dot_size, filled, rounded);
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

