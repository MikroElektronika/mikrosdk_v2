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
#define ROW_SIZE                64
#define COL_SIZE                128
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
void GLCD_Init                              ( glcd_t* glcd );
void GLCD_Set_Page                          ( glcd_t* glcd, uint8_t page );
void GLCD_Display_Start_Line                ( glcd_t* glcd, uint8_t stline );
void GLCD_Set_Y                             ( glcd_t* glcd, uint8_t y_pos );
void GLCD_Restore_Default_Configuration     ( glcd_t* glcd );
void GLCD_Clear                             ( glcd_t *glcd );                           //vide le buffer
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
    //port_init( &data_in, PORT_C, 0xFF, HAL_LL_GPIO_DIGITAL_INPUT );
    digital_out_init( &cs1d, CS1_PIN );
    digital_out_init( &cs2d, CS2_PIN );
    digital_out_init( &ed, E_PIN );
    digital_out_init( &resetd, RESET_PIN );
    digital_out_init( &rsd, RS_PIN );
    digital_out_init( &rwd, RW_PIN );

    /* This is for debugging, it is not useful for the rest of the code */
    port_init( &see_cmd, PORT_D, 0xFF, HAL_LL_GPIO_DIGITAL_OUTPUT );
    port_init( &see, PORT_C, 0xFF, HAL_LL_GPIO_DIGITAL_OUTPUT );
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

    //GLCD_Set_Page( glcd, 0 );                // Set the first page
    //GLCD_Set_Y( glcd, 0 );                   // Set the first Y position
}

void GLCD_Display( glcd_t* glcd, unsigned char turn_on_off )
{
    if ( !glcd ) return;
    if (!IS_ON( turn_on_off ) && !IS_OFF( turn_on_off ) ) return;

    digital_out_low( &cs1d );                // CS1 = 0
    digital_out_low( &cs2d );                // CS2 = 0
    digital_out_low( &rsd );                // RS = 0 (instruction)
    digital_out_low( &rwd );                // RW = 0 (ecriture)
    port_write( &data_out, turn_on_off );
    port_write( &see_cmd, turn_on_off ); // For debugging purposes
    Apply_changes();
    
}

void GLCD_Set_Y( glcd_t* glcd, uint8_t y_pos )
{
    if ( !glcd ) return;
    if ( y_pos > 63 ) y_pos = 63;            // Ensure y_pos is within 0-63 range
    if ( y_pos < 0 ) y_pos = 0;              // Ensure y_pos is within 0-63 range

    digital_out_low( &cs1d );                // CS1 = 0
    digital_out_low( &cs2d );                // CS2 = 0
    digital_out_low( &rsd );                 // RS = 0 (instruction)
    digital_out_low( &rwd );                 // RW = 0 (ecriture)

    port_write( &data_out, y_pos | 0x40 );
    //port_write( &see_cmd, y_pos | 0x3F );             // For debugging purposes
    Apply_changes();
}

void GLCD_Set_Page( glcd_t* glcd, uint8_t page )
{
    if ( !glcd ) return;
    if ( page > 7 ) page = 7;                // Ensure page is within 0-7 range
    if ( page < 0 ) page = 0;                // Ensure page is within 0-7 range

    digital_out_low( &cs1d );                // CS1 = 0
    digital_out_low( &cs2d );                // CS2 = 0
    digital_out_low( &rsd );                 // RS = 0 (instruction)
    digital_out_low( &rwd );                 // RW = 0 (ecriture)

    port_write( &data_out, page | 0xB8 );
    //port_write( &see_cmd, page | 0xB8 );     // For debugging purposes
    Apply_changes();
}

void GLCD_Write( glcd_t *glcd, uint8_t page, uint8_t lign, uint8_t data_to_write )
{
    if ( !glcd ) return;
    if ( page > 7 || lign > 127 ) return;               // Ensure page and column are within valid ranges
    if ( page < 0 || lign < 0 ) return;                 // Ensure page and column are within valid ranges
    if ( data_to_write > 0xFF ) data_to_write = 0xFF;   // Ensure data_to_write is within 0-255 range
    if ( data_to_write < 0 ) data_to_write = 0;         // Ensure data_to_write is within 0-255 range

    /*
    GLCD_Set_Page( glcd, page );                        // Set the page
    GLCD_Set_Y( glcd, lign );                           // Set the Y position
    */

    digital_out_low( &ed );                             // E = 0
    digital_out_high( &rsd );                           // RS = 1 (data)
    digital_out_low( &rwd );                            // RW = 0 (ecriture)

    port_write( &data_out, data_to_write );
    Apply_changes();                                    // Apply changes to the GLCD
    //port_write( &see_cmd, data_to_write );            // For debugging purposes
}

GLCD_Clear( glcd_t *glcd )
{
    unsigned char i, j;
    unsigned char pattern = 0x00; // Clear pattern

    for (i = 0; i < PAGE_SIZE; i++) 
    { 
        for (j = 0; j < ROW_SIZE; j++) 
        {
            GLCD_Write( glcd, i, j, pattern ); // Write clear pattern to each page and row
        }
    }
}


void Apply_changes( void )
{
    digital_out_high( &ed );
    Delay_us(1);
    digital_out_low( &ed );
    Delay_us(1);
}