#include "MikroSDK.Board"
#include "MikroSDK.Driver"
#include "MikroSDK.Driver.GPIO.In"
#include "MikroSDK.Driver.GPIO.Out"
#include "MikroSDK.Driver.GPIO.Port"

typedef enum {
    ON = 0x3F, on = 0x3F, On = 0x3F, oN = 0x3F, 
    
    OFF = 0x3E, Off = 0x3E, oFf = 0x3E, ofF = 0x3E,
    OFf = 0x3E, oFF = 0x3E, OfF = 0x3E, off = 0x3E,
    
    DATA, INSTRUCTION,
    READ, WRITE, DEFAULT_CONFIG = 0
} config;

#define IS_ON( x )              ( (x == ON) || (x == oN) || (x == on) || (x == oN) )
#define IS_OFF( x )             ( (x == OFF) || (x == Off) || (x == oFf) || (x == ofF) || (x == OFf) || (x == oFF) || (x == ofF) || (x == off) )

#define PAGE_SIZE               8
#define COL_SIZE                64
#define ROW_SIZE                128
#define GLCD_BUFFER_SIZE        ( COL_SIZE * ROW_SIZE / 8 )

/* Pins defintion for GLCD usage */
#define E_PIN                   PE15
#define RW_PIN                  PE13
#define RS_PIN                  PE12
#define CS2_PIN                 PE11
#define CS1_PIN                 PE10
#define RESET_PIN               PE8

#define Data_PIN_7              PE7
#define Data_PIN_6              PE6
#define Data_PIN_5              PE5
#define Data_PIN_4              PE4
#define Data_PIN_3              PE3
#define Data_PIN_2              PE2
#define Data_PIN_1              PE1
#define Data_PIN_0              PE0

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
    unsigned char buffer[GLCD_BUFFER_SIZE];
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
uint8_t GLCD_Read                           ( glcd_t* glcd );
void GLCD_Write                             ( glcd_t *glcd, uint8_t page, uint8_t column, uint8_t data_to_write );

/* Drawing functions */
void GLCD_Fill_Screen                       ( glcd_t* glcd, uint8_t pattern );
void GLCD_Draw_Dot                          ( glcd_t* glcd, point* p );
void GLCD_Draw_Line                         ( glcd_t* glcd, const point* pts, bool is_vertical );
void GLCD_Draw_Rect                         ( glcd_t* glcd, const point* limit, bool is_filled , bool round_edges ); 
void GLCD_Draw_Circle                       ( glcd_t* glcd, const point* origin, bool is_filled );


void GLCD_Port_Init( void )
{
    port_init( &data_out, PORT_E, 0xFF, HAL_LL_GPIO_DIGITAL_OUTPUT );
    port_init( &data_in, PORT_C, 0xFF, HAL_LL_GPIO_DIGITAL_INPUT );
    digital_out_init( &cs1d, CS1_PIN );
    digital_out_init( &cs2d, CS2_PIN );
    digital_out_init( &ed, E_PIN );
    digital_out_init( &resetd, RESET_PIN );
    digital_out_init( &rsd, RS_PIN );
    digital_out_init( &rwd, RW_PIN );

    /* This is for debugging, it is not useful for the rest of the code */
    port_init( &see_cmd, PORT_D, 0xFF, HAL_LL_GPIO_DIGITAL_OUTPUT );
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
    digital_out_write( &rsd, (glcd->DATA_OR_INSTRUCTION ==  DATA) ? 0 : 1 );
    digital_out_write( &rwd, (glcd->READ_OR_WRITE == READ) ? 1 : 0 );

    GLCD_Set_Page(glcd, 0);                              // Set the page (0-7)
    GLCD_Set_Y(glcd, 0);                                 // Set the Y position (lign)
    GLCD_Display_Start_Line(glcd, 0);                       // Set the start line to 0
}

void CS_Config( glcd_t* glcd, uint8_t cs1, uint8_t cs2 )
{
    if ( !glcd ) return;

    if (cs1 == 1 && cs2 == 0) 
    {
        digital_out_high(&cs1d);  // CS1 = 1
        digital_out_low(&cs2d);   // CS2 = 0
    } 
    else if (cs1 == 0 && cs2 == 1) 
    {
        digital_out_low(&cs1d);   // CS1 = 0
        digital_out_high(&cs2d);  // CS2 = 1
    }  
}

void GLCD_Set_Y( glcd_t* glcd, uint8_t y_pos )
{
    if ( !glcd ) return;
    if ( y_pos > 63 ) y_pos = 63;            // Ensure y_pos is within 0-63 range

    digital_out_low( &rsd );                 // RS = 0 (instruction)
    digital_out_low( &rwd );                 // RW = 0 (ecriture)

    y_pos |= 0x40;   
    port_write( &data_out, y_pos );
    Apply_changes();
}

void GLCD_Display_Start_Line( glcd_t* glcd, uint8_t stline )
{
    if ( !glcd ) return;
    if ( stline > 63 ) stline = 63;            // Ensure y_pos is within 0-63 range

    digital_out_low( &rsd );                 // RS = 0 (instruction)
    digital_out_low( &rwd );                 // RW = 0 (ecriture)

    stline |= 0xC0;   
    port_write( &data_out, stline );
    Apply_changes();
}


void GLCD_Set_Page( glcd_t* glcd, uint8_t page )
{
    if ( !glcd ) return;
    if ( page > 7 ||  page < 0 ) return;   // Ensure page is within 0-7 range               

    digital_out_low( &rsd );                 // RS = 0 (instruction)
    digital_out_low( &rwd );                 // RW = 0 (ecriture)

    page |= 0xB8;                            // Set the 6th bit to indicate page address
    port_write( &data_out, page );
    Apply_changes();
}

void GLCD_Write(glcd_t *glcd, uint8_t page, uint8_t lign, uint8_t data_to_write)
{
    if (!glcd || page > 7 || lign > 127) return;            // Set the Y position (lign)

    for (uint8_t k = 0; k < 2; k++)
    {
        CS_Config( glcd, k%2, (k+1)%2 );
        digital_out_low(&ed);                               // E = 0
        digital_out_high(&rsd);                             // RS = 1 (data)
        digital_out_low(&rwd);                              // RW = 0 (write)
        port_write(&data_out, data_to_write);
        Apply_changes();                                    // E = 1 puis E = 0
    }
}

uint8_t GLCD_Read(glcd_t* glcd)
{
    if (!glcd) return 0;

    digital_out_low(&ed);                               // E = 0
    digital_out_low(&rsd);                              // RS = 0 (instruction)
    digital_out_high(&rwd);                             // RW = 1 (read)
    Apply_changes();                                    // E = 1 puis E = 0
                                            
    uint8_t data_read = port_read_input(&data_in);      // Read data from the input port
    return data_read;
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


void Apply_changes( void )
{
    digital_out_high( &ed );
    Delay_us(1);
    digital_out_low( &ed );
    Delay_us(1);
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

