#include "glcd.h"

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

/* -------------------------------------------------- Initialize functions -------------------------------------------------- */
/**
 * @name GLCD_Port_Init
 * @brief Initializes the GLCD port and control pins.
 *
 * @details This function sets up the data output port and initializes all required
 * digital output pins for controlling the GLCD, including chip select,
 * enable, reset, register select, and read/write pins.
 *
 * @param ( glcd_t* ) Pointer to the GLCD structure containing pin configurations.
 * @return Nothing
 * 
 * @note This function is called automatically by GLCD_Init() to prepare the GLCD for operation.
 * It should not be called directly unless you need to reinitialize the port.
 */
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

/**
 * @name GLCD_Init
 * @brief Initializes the GLCD hardware and sets the initial pin states.
 *
 * @details This function configures the GLCD port and sets the control pins to their
 * initial states required for proper operation. It performs the following steps:
 * - Initializes the GLCD port.
 * - Sets the enable, chip select 1, chip select 2, and reset pins to high.
 * - Sets the register select pin to low.
 * - Sets the read/write pin to high.
 * - Applies the changes to the hardware.
 *
 * @param ( glcd_t* ) glcd : to the glcd_t structure containing GLCD configuration and pin mappings.
 * @return Nothing
 * 
 * @note This function must be called before any other GLCD operations to ensure the hardware is ready.
 * It initializes the GLCD and prepares it for further commands and data transmission.
 */
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

/**
 * @name GLCD_Set_Page
 * @brief Sets the current page for GLCD operations.
 *
 * @details This function sets the page address for the GLCD, which determines
 * the vertical position on the screen where subsequent data will be written.
 * The page value must be between 0 and 7 (inclusive).
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( uint8_t ) page : The page number to set (0-7).
 * @return Nothing
 * 
 * @note This function should be called before writing data to a specific page. But the user isn't supposed
 * to use this function directly, instead it should use GLCD_Write() which will handle the page setting automatically.
 * If the page number is out of range (greater than 7), the function will return immediately without making any changes.
 */
void GLCD_Set_Page( glcd_t* glcd, uint8_t page )
{
    if ( !glcd || page > 7 ) return;             

    digital_out_low( &glcd->rsd );                    // RS = 0 (instruction)
    digital_out_low( &glcd->rwd );                    // RW = 0 (ecriture)
    port_write( &glcd->data_out, (0xB8 | (page & 0x07)) );       // We only care about the lower 3 bits for page address
    Apply_changes(glcd);
}

/**
 * @name GLCD_Set_Y
 * @brief Sets the Y position (line) for GLCD operations.
 *
 * @details This function sets the Y position on the GLCD, which determines the
 * horizontal line where subsequent data will be written. The Y position
 * must be between 0 and 64 (inclusive).
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( uint8_t ) y_pos : The Y position to set (0-64).
 * @return Nothing
 * 
 * @note This function should be called before writing data to a specific line, and is done automatically by GLCD_Write().
 * If the Y position is out of range (greater than 64), the function will return immediately without making any changes.
 */
void GLCD_Set_Y( glcd_t* glcd, uint8_t y_pos )
{
    if ( !glcd || y_pos > 64 ) return;

    digital_out_low( &glcd->rsd );                    // RS = 0 (instruction)
    digital_out_low( &glcd->rwd );                    // RW = 0 (ecriture)
    port_write( &glcd->data_out, (0x40 | (y_pos & 0x3F)) );
    Apply_changes(glcd);
}

/**
 * @name GLCD_Clear
 * @brief Clears the GLCD buffer by writing zeros to all pages and columns.
 *
 * @details This function iterates through all pages and columns of the GLCD
 * and writes zero to each position, effectively clearing the display.
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @return Nothing
 * 
 * @note This function writes zeros to the GLCD register for each page and column,
 * which will result in a blank display when the buffer is displayed. The data (because of the GLCD_Write function) 
 * is written to the buffer as well.
 */
void GLCD_Clear(glcd_t *glcd)
{
    if (!glcd) return;
    
    for (uint8_t page = 0; page < PAGE_SIZE; page++)
        for (uint8_t col = 0; col <= ROW_SIZE; col++)
            GLCD_Write(glcd, page, col, 0x00);
}

/**
 * @name GLCD_Display
 * @brief Turns the GLCD display on or off.
 *
 * @details This function controls the display state of the GLCD by setting the
 * appropriate control signals. It can turn the display on or off based on the
 * provided parameter.
 *
 * @param ( glcd_t* )        glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( uint8_t ) turn_on_off : The state to set (ON or OFF).
 * @return Nothing
 * 
 * @note This function should be called to toggle the display state. It uses the CS_Config function to select the chip,
 * and applies changes to the control signals.
 */
void GLCD_Display( glcd_t* glcd, display_cfg_t turn_on_off )
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


/**
 * @name Apply_changes
 * @brief Applies changes to the GLCD by toggling the enable pin.
 *
 * @details This function toggles the enable pin of the GLCD to apply any changes made
 * to the data or control signals. It ensures that the GLCD registers are updated with
 * the latest values. This chip uses a pulse on the enable pin to latch the data (according to the datasheet).
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @return Nothing
 * 
 * @note This function should be called after writing data or control signals to the GLCD
 * to ensure that the changes take effect.
 */
void Apply_changes( glcd_t* glcd )
{
    digital_out_high( &glcd->ed );
    Delay_us(10);
    digital_out_low( &glcd->ed );
    Delay_us(10);
}

/**
 * @name CS_Config
 * @brief Configures the chip select pins for the GLCD.
 *
 * @details This function sets the chip select pins (CS1 and CS2) to either high or low
 * based on the provided parameters. It is used to select which chip (if multiple chips are used)
 * will respond to the GLCD commands.
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( bool )     cs1 : State for chip select 1 (true for low, false for high).
 * @param ( bool )     cs2 : State for chip select 2 (true for low, false for high).
 * @return Nothing
 * 
 * @note This function should be called before writing data to the GLCD to ensure that the correct chip is selected
 * and is of course, called in GLCD_Write() function. The CS logic is inverted, so a value of 1 means the chip 
 * is selected (active low).
 */
void CS_Config(glcd_t* glcd, bool cs1, bool cs2)
{
    if (!glcd) return;
    digital_out_write(&glcd->cs1d, (cs1 == 1) ? 0 : 1);
    digital_out_write(&glcd->cs2d, (cs2 == 1) ? 0 : 1);
}



/* -------------------------------------------------- Read and Write functions -------------------------------------------------- */
/**
 * @name GLCD_Read
 * @brief Reads a byte from the GLCD buffer at the specified page and column.
 *
 * @details This function retrieves a byte from the GLCD buffer based on the specified
 * page and column indices. It checks if the indices are within valid ranges before accessing
 * the buffer.
 *
 * @param  ( glcd_t* )   glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param  ( uint8_t )   page : The page number (0-7).
 * @param  ( uint8_t ) column : The column number (0-127).
 * @return ( uint8_t ) The byte read from the GLCD buffer, or 0 if indices are out of range.
 * 
 * @note This function is used to read data from the GLCD buffer without affecting the display. Although it is a software read,
 * it is mainly used to access the framebuffer buffer for further processing or display updates (because the Read_LL a.k.a Low Level Read)
 * is imprecise and slower than this function. This should be a improvment for the next version of this library.
 */
uint8_t GLCD_Read(glcd_t* glcd, uint8_t page, uint8_t column)
{
    if (!glcd || page >= PAGE_SIZE || column >= ROW_SIZE) return 0;

    uint8_t chip = (column < 64) ? 0 : 1;
    uint8_t col_in_chip = column % 64;
    return glcd->buffer[chip][page][col_in_chip];
}

/**
 * @name GLCD_Read_LL
 * @brief Reads a byte from the GLCD at the specified page and column using low-level access.
 *
 * @details This function performs a low-level read operation on the GLCD by configuring
 * the necessary control signals and reading the data from the specified page and column.
 * It is used for direct hardware access to retrieve data from the GLCD.
 *
 * @param ( glcd_t* )   glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( uint8_t )   page : The page number (0-7).
 * @param ( uint8_t ) column : The column number (0-127).
 * @return ( uint8_t ) The byte read from the GLCD, or 0 if indices are out of range.
 * 
 * @note This function is used for low-level access to read data directly from the GLCD hardware.
 * It should be used with caution as it bypasses the buffer and directly interacts with the GLCD.
 */
uint8_t GLCD_Read_LL(glcd_t* glcd, uint8_t page, uint8_t column) 
{
    if (!glcd || page >= PAGE_SIZE || column >= ROW_SIZE) return 0;

    port_init( &glcd->data_out, PORT_E, 0xFF, HAL_LL_GPIO_DIGITAL_INPUT );
    uint8_t chip = (column < 64) ? 0 : 1;
    uint8_t col_in_chip = column % 64;

    CS_Config(glcd, chip == 0, chip == 1);
    GLCD_Set_Y(glcd, col_in_chip);
    GLCD_Set_Page(glcd, page);

    digital_out_high(&glcd->rsd);
    digital_out_high(&glcd->rwd);

    // Dummy read (necessary for the GLCD to prepare for reading)
    digital_out_high(&glcd->ed);    // E = 1
    Delay_us(1);                    // tWH ≥ 450 ns (from datasheet)
    digital_out_low(&glcd->ed);     // E = 0
    Delay_us(1);

    uint8_t data_readed = port_read(&glcd->data_out);
    port_init( &glcd->data_out, PORT_E, 0xFF, HAL_LL_GPIO_DIGITAL_OUTPUT );
    Apply_changes(glcd);

    return data_readed;
}

/**
 * @name GLCD_Write
 * @brief Writes a byte to the GLCD at the specified page and line.
 *
 * @details This function writes a byte of data to the GLCD at the specified page and line.
 * It handles the chip selection based on the line number (0-63 for CS1, 64-127 for CS2).
 * The data is also stored in the GLCD buffer for later retrieval.
 *
 * @param ( glcd_t* )          glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( uint8_t )          page : The page number (0-7).
 * @param ( uint8_t )          line : The line number (0-127).
 * @param ( uint8_t ) data_to_write : The byte of data to write to the GLCD.
 * @return Nothing
 * 
 * @note This function should be called to write data to the GLCD. It automatically selects the appropriate chip
 * based on the line number and updates both the GLCD display and the internal buffer.
 */
void GLCD_Write(glcd_t *glcd, uint8_t page, uint8_t line, uint8_t data_to_write)
{
    if (!glcd || page > PAGE_SIZE || line > ROW_SIZE) return;
                             
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

/**
 * @name GLCD_Write_Char
 * @brief Writes a character to the GLCD at the specified position.
 *
 * @details This function writes a single character to the GLCD at the specified position
 * (x, y). It retrieves the character's bitmap from a predefined font array and writes it
 * to the GLCD in a column-wise manner.
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( point* )     p : Pointer to a point structure defining the position (x, y) on the GLCD.
 * @param ( char )       c : The character to write to the GLCD.
 * @return Nothing
 * 
 * @note This function is used to display individual characters on the GLCD. It calculates
 * the page and line based on the provided point and writes each byte of the character's bitmap
 * to the GLCD buffer.
 */
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

/**
 * @name GLCD_Write_Text
 * @brief Writes a string of text to the GLCD at the specified position.
 *
 * @details This function writes a null-terminated string to the GLCD starting from
 * the specified point (x, y). It iterates through each character in the string and
 * calls GLCD_Write_Char to write each character to the GLCD.
 *
 * @param ( glcd_t* )  glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( point* )      p : Pointer to a point structure defining the starting position (x, y) on the GLCD.
 * @param ( const char* ) c : Pointer to a null-terminated string to write to the GLCD.
 * @return Nothing
 * 
 * @note This function is used to display text on the GLCD. It automatically handles line wrapping
 * by moving to the next line when the end of a page is reached. If the text exceeds the available space,
 * it stops writing further characters.
 */
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

/* -------------------------------------------------- Drawing functions -------------------------------------------------- */
/**
 * @name GLCD_Fill_Screen
 * @brief Fills the entire GLCD screen with a specified pattern.
 *
 * @details This function fills the entire GLCD screen by writing a specified pattern
 * to each page and column. The pattern is repeated across the entire display.
 *
 * @param ( glcd_t* )    glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( uint8_t ) pattern : The byte pattern to fill the screen with.
 * @return Nothing
 * 
 * @note This function is used to quickly fill the entire GLCD screen with a specific pattern,
 * which can be useful for clearing the display or creating background effects.
 */
void GLCD_Fill_Screen( glcd_t* glcd, uint8_t pattern )
{
    if (!glcd) return;
    
    for (uint8_t page = 0; page < PAGE_SIZE; page++)
        for (uint8_t col = 0; col <= ROW_SIZE; col++)
            GLCD_Write(glcd, page, col, pattern);
}

/**
 * @name GLCD_Draw_Dots
 * @brief Draws multiple dots on the GLCD at specified points.
 *
 * @details This function draws dots on the GLCD at the specified points with a given size.
 * Each point is represented by a structure containing x and y coordinates. The dot size
 * determines how many pixels will be filled around each point.
 *
 * @param ( glcd_t* )     glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( const point* ) pts : Pointer to an array of points where dots will be drawn.
 * @param ( uint8_t )     size : The number of points in the array.
 * @param ( uint8_t ) dot_size : The size of each dot (1-8).
 * @return Nothing
 * 
 * @note This function is used to draw multiple dots on the GLCD. It iterates through each point
 * and fills the corresponding pixels based on the specified dot size. If the dot size is out of range,
 * it returns without making any changes.
 */
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

/**
 * @name GLCD_Draw_Line
 * @brief Draws a line on the GLCD based on the specified segment and direction.
 *
 * @details This function draws a line on the GLCD using Bresenham's algorithm for diagonal lines,
 * and simple loops for horizontal and vertical lines. The segment is defined by two points, and the
 * direction determines how the line is drawn (vertical, horizontal, or diagonal).
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( const segment* ) s : An array of segment(s) to plot.
 * @param ( line_dir_t ) direction : The direction of the line (VERTICAL_LINE, HORIZONTAL_LINE, DIAGONAL).
 * @return Nothing
 * 
 * @note This function handles drawing lines of varying sizes and directions. It checks if the points are within
 * valid ranges before attempting to draw. If the points are out of bounds, it returns without making any changes.
 */
void GLCD_Draw_Line(glcd_t* glcd, const segment* s, uint8_t s_size, line_dir_t direction)
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
                        uint8_t val = GLCD_Read(glcd, page, cx);
                        GLCD_Write(glcd, page, cx, val | bit_in_page);
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
                        uint8_t val = GLCD_Read(glcd, page, x);
                        GLCD_Write(glcd, page, x, val | bit_in_page);
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
                            uint8_t val = GLCD_Read(glcd, page, x);
                            GLCD_Write(glcd, page, x, val | bit_in_page);
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

/**
 * @name GLCD_Draw_Rect
 * @brief Draws rectangles on the GLCD based on specified points and rectangle sizes.
 *
 * @details This function draws rectangles on the GLCD at specified points with given sizes.
 * Each rectangle is defined by a point (top-left corner) and a size (width, height).
 * It can also fill the rectangle if specified.
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( const point* ) p : Pointer to an array of points defining the top-left corners of rectangles.
 * @param ( uint16_t ) psize : The number of points in the array.
 * @param ( const rect* ) r : Pointer to an array of rectangles defining their sizes and properties.
 * @param ( uint16_t ) rsize : The number of rectangles in the array.
 * @return Nothing
 * 
 * @note This function is used to draw multiple rectangles on the GLCD. It iterates through each point and rectangle,
 * drawing lines for each side of the rectangle and filling it if specified. If the sizes do not match or if any input
 * is invalid, it returns without making any changes.
 */
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

        GLCD_Draw_Line(glcd, rect, 4, DIAGONAL); 
        if (r[i].filled) { Fill_Polygon(glcd, rect, 4); }
        if (r[i].rounded) {  }
    }
}

/**
 * @name GLCD_Draw_Rect_Giving_Points
 * @brief Draws rectangles or triangles based on given points and size.
 *
 * @details This function draws rectangles or triangles on the GLCD based on the provided points.
 * It can handle different sizes of shapes (1-4 points) and can fill them if specified.
 * It also supports rounded edges for rectangles.
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( const point* ) p : Pointer to an array of points defining the corners of the shape.
 * @param ( uint8_t ) size : The number of points in the array (1-4).
 * @param ( uint8_t ) dot_size : The size of each dot in the shape.
 * @param ( bool ) is_filled : Whether to fill the shape or not.
 * @param ( bool ) round_edges : Whether to round the edges of the rectangle or not.
 * @return Nothing
 * 
 * @note This function is used to draw shapes based on a variable number of points. It handles
 * different cases for 1, 2, 3, and 4 points, drawing lines or polygons as appropriate. If the input
 * is invalid, it returns without making any changes.
 */
void GLCD_Draw_Rect_Giving_Points(glcd_t* glcd, const point* p, uint8_t size, uint8_t dot_size, bool is_filled, bool round_edges)
{
    if (!glcd || !p || size == 0) return;

    switch (size)
    {
        case 1: { GLCD_Draw_Dots(glcd, p, size, dot_size); break; }
        case 2: { segment s = { {{p[0].x, p[0].y}, {p[1].x, p[1].y} }, dot_size }; GLCD_Draw_Line(glcd, &s, 1, DIAGONAL); break; }
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
                GLCD_Draw_Shape(glcd, rect, 4, is_filled, round_edges);
            } else {
                segment tri[3] = {
                    { {{ p[0].x, p[0].y }, { p[1].x, p[1].y }}, dot_size },
                    { {{ p[1].x, p[1].y }, { p[2].x, p[2].y }}, dot_size },
                    { {{ p[2].x, p[2].y }, { p[0].x, p[0].y }}, dot_size }
                };
                GLCD_Draw_Shape(glcd, tri, 3, is_filled, round_edges);
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
            GLCD_Draw_Shape(glcd, rect, 4, is_filled, round_edges);
            break;
        }
        default: break;
    }
}


/**
 * @name GLCD_Draw_Shape
 * @brief Draws a polygon on the GLCD based on the specified edges and size.
 *
 * @details This function draws a polygon on the GLCD by connecting the edges defined in the input array.
 * It can fill the polygon if specified and can also round the edges if required.
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( const segment* ) edges : Pointer to an array of segments defining the edges of the polygon.
 * @param ( uint8_t ) size : The number of edges in the polygon.
 * @param ( bool ) is_filled : Whether to fill the polygon or not.
 * @param ( bool ) round_edges : Whether to round the edges of the polygon or not.
 * @return Nothing
 * 
 * @note This function is used to draw polygons with varying numbers of edges. It sorts the points using a nearest neighbor algorithm
 * and draws lines between them. If filling is enabled, it calls Fill_Polygon to fill the area inside the polygon.
 */
void GLCD_Draw_Shape(glcd_t* glcd, const segment* edges, uint8_t size, bool is_filled, bool round_edges)
{
    if (!glcd || !edges) return;

    segment output[64];
    Sort_Points_Nearest_Neighbor(edges, output, size);
    GLCD_Draw_Line(glcd, output, size, DIAGONAL);

    if (is_filled) { Fill_Polygon(glcd, output, output[0].line_size); }
    if (round_edges) { }
}

/**
 * @name GLCD_Draw_Regular_Polygon
 * @brief Draws regular polygons on the GLCD based on specified parameters.
 *
 * @details This function draws regular polygons on the GLCD using a specified number of sides and properties.
 * It can also fill the polygon if specified. The polygons are defined by their origin point and properties.
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( const point* ) ori : Pointer to an array of points defining the origin of each polygon.
 * @param ( uint8_t ) num_of_ori : The number of origins in the array.
 * @param ( const polygon_mode_t* ) pol : Pointer to an array of polygon modes defining properties like number of sides, size, and filling.
 * @param ( uint8_t ) num_of_pol : The number of polygons in the array.
 * @param ( bool ) is_filled : Whether to fill the polygon or not.
 * @return Nothing
 * 
 * @note This function is used to draw multiple regular polygons on the GLCD. It calculates the vertices of each polygon
 * based on the origin and properties, and draws lines between them. If filling is enabled, it calls Fill_Polygon to fill
 * the area inside the polygon.
 */
void GLCD_Draw_Regular_Polygon(glcd_t* glcd, const point* ori, uint8_t num_of_ori, const polygon_mode_t* pol, uint8_t num_of_pol, bool is_filled)
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

        GLCD_Draw_Line(glcd, edges, sides, DIAGONAL);
        if (is_filled) Fill_Polygon(glcd, edges, sides);
    }
}



/**
 * @name GLCD_Draw_Circle
 * @brief Draws circles on the GLCD based on specified circle parameters.
 *
 * @details This function draws circles on the GLCD using a specified precision for the circle approximation.
 * It can also fill the circle if specified. The circles are defined by their center point and radius.
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( const circle* ) c : Pointer to an array of circles defining their center points, radii, and properties.
 * @param ( uint16_t ) csize : The number of circles in the array.
 * @param ( circle_mode_t ) precision : The precision for circle approximation (15-3000 numbers of points).
 * @return Nothing
 * 
 * @note This function is used to draw multiple circles on the GLCD. It approximates each circle using trigonometric functions
 * and draws lines between points on the circle's circumference. If filling is enabled, it calls Fill_Circle to fill the area inside the circle.
 */
void GLCD_Draw_Circle( glcd_t* glcd, const circle* c, uint16_t csize, circle_mode_t precision )
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
            GLCD_Draw_Line(glcd, &s, 1, DIAGONAL);
        }
        if (c[i].filled) { Fill_Circle(glcd, circle_approx, precision, dot_size); }
    }
}

/**
 * @name GLCD_Draw_Ellipse
 * @brief Draws ellipses on the GLCD based on specified ellipse parameters.
 * 
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( const ellipse* ) e : Pointer to an array of ellipses defining their mid-foci, semi-major axis, and properties.
 * @param ( uint16_t ) esize : The number of ellipses in the array.
 * @param ( circle_mode_t ) precision : The precision for ellipse approximation (15-3000).
 * @return Nothing
 * 
 * @details This function draws ellipses on the GLCD using a specified precision for the ellipse approximation.
 */
void GLCD_Draw_Ellipse(glcd_t* glcd, const ellipse* e, uint16_t esize, circle_mode_t precision)
{
    if (!glcd || !e || esize == 0 || precision < 3 || precision > 5000) return;

    for (uint16_t i = 0; i < esize; i++)
    {
        float cx = e[i].mid_foci[0].x, cy = e[i].mid_foci[0].y;
        float fx = e[i].mid_foci[1].x, fy = e[i].mid_foci[1].y;
        float dx = fx - cx, dy = fy - cy;
        float c_val = sqrt(dx * dx + dy * dy);
        float a = e[i].a;
        if (a <= c_val) a = c_val + 1; // Ensure valid ellipse
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
            GLCD_Draw_Line(glcd, &s, 1, DIAGONAL);
        }
        if (is_filled) { Fill_Circle(glcd, ellipse_points, precision, dot_size); }
    }
}



/* -------------------------------------------------- Utils -------------------------------------------------- */
/**
 * @name distance
 * @brief Calculates the Euclidean distance between two points.
 *
 * This function computes the straight-line distance between point 'a' and point 'b'
 * using the Pythagorean theorem.
 *
 * @param ( point ) a : The first point with x and y coordinates.
 * @param ( point ) b : The second point with x and y coordinates.
 * @return ( float ) The Euclidean distance as a float.
 * 
 * @note This function is used to calculate the distance between two points in a 2D space.
 * It is commonly used in algorithms that require distance calculations, such as nearest neighbor searches.
 */
float distance(point a, point b) 
{
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

/**
 * @name Sort_Points_Nearest_Neighbor
 * @brief Sorts points using the nearest neighbor algorithm.
 *
 * This function sorts an array of segments based on the distance from the origin (0, 0)
 * and then arranges them in a sequence that connects each segment to the next closest one.
 *
 * @param ( const segment* ) input : Pointer to the input array of segments.
 * @param ( segment* ) output : Pointer to the output array where sorted segments will be stored.
 * @param ( uint8_t ) size : The number of segments in the input array.
 * @return Nothing
 * 
 * @note This function is used to sort segments based on their proximity to each other, which can be useful in graphical applications
 * where segments need to be drawn in a specific order. It uses a nearest neighbor approach to find the optimal order of segments.
 * It assumes that the input segments are valid and that the output array has enough space to hold the sorted segments.
 */
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

/**
 * @name Fill_Polygon
 * @brief Fills a polygon on the GLCD based on the specified edges and size.
 *
 * @details This function fills a polygon on the GLCD by determining the intersections of the edges
 * at each horizontal line and drawing filled segments between these intersections.
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( const segment* ) edges : Pointer to an array of segments defining the edges of the polygon.
 * @param ( uint8_t ) size : The number of edges in the polygon.
 * @return Nothing
 * 
 * @note This function is used to fill polygons with a specified size. It sorts the points using a nearest neighbor algorithm,
 * determines the intersections for each horizontal line, and fills the area between these intersections. If the input is invalid,
 * it returns without making any changes.
 */
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
            GLCD_Draw_Line(glcd, &s, 1, HORIZONTAL_LINE);
        }
    }
}

/**
 * @name Fill_Circle
 * @brief Fills a circle on the GLCD based on the specified contour and precision.
 *
 * @details This function fills a circle on the GLCD by determining the intersections of the contour
 * at each horizontal line and drawing filled segments between these intersections.
 *
 * @param ( glcd_t* ) glcd : Pointer to the glcd_t structure containing GLCD configuration and pin mappings.
 * @param ( const point* ) contour : Pointer to an array of points defining the contour of the circle.
 * @param ( uint16_t ) precision : The precision for circle approximation (15-3000).
 * @param ( uint8_t ) dot_size : The size of each dot in the filled circle.
 * @return Nothing
 * 
 * @note This function is used to fill circles with a specified precision. It calculates intersections for each horizontal line,
 * sorts them, and fills the area between these intersections. If the input is invalid, it returns without making any changes.
 */
void Fill_Circle( glcd_t* glcd, const point* contour, uint16_t precision, uint8_t dot_size )
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
            GLCD_Draw_Line(glcd, &s, 1, HORIZONTAL_LINE);
        }
    }
}

/**
 * @name dot_product
 * @brief Calculates the dot product of two vectors defined by three points.
 * 
 * @param ( point ) a : The first point, which serves as the origin for the vectors.
 * @param ( point ) b : The second point, which defines the first vector from point 'a'.
 * @param ( point ) c : The third point, which defines the second vector from point 'a'.
 * @return ( static int ) The dot product of the two vectors as an integer.
 * 
 * @details This function computes the dot product of two vectors defined by the points 'b' and 'c' relative to the origin 'a'.
 * The dot product is calculated as the sum of the products of the corresponding components of the vectors.
 * It is commonly used in geometry and physics to determine the angle between two vectors or to check if they are orthogonal.
 */
static int dot_product(point a, point b, point c) 
{
    int ux = b.x - a.x;
    int uy = b.y - a.y;
    int vx = c.x - a.x;
    int vy = c.y - a.y;
    return ux * vx + uy * vy;
}

/**
 * @name Transpose_Word
 * @brief Transposes a 64-bit word by swapping its rows and columns.
 * 
 * @param ( uint64_t ) word : The 64-bit word to be transposed.
 * @return ( uint64_t ) The transposed 64-bit word.
 * 
 * @details This function takes a 64-bit word and transposes it by swapping its rows and columns.
 * It iterates through each bit of the word and rearranges them to create a new word.
 */
uint64_t Transpose_Word(uint64_t word)
{
    uint64_t result = 0;

    for (uint8_t row = 0; row < 8; row++)
        for (uint8_t col = 0; col < 8; col++)
            if (word & (1ULL << (col * 8 + row)))
                result |= (1ULL << (row * 8 + col));

    return result;
}

/**
 * @name Find_Matching_Char_From_Bitmap
 * @brief Finds the bitmap code for a given character in the font array.
 *
 * @param ( char ) c : The character to find in the font array.
 * @return ( uint64_t ) The bitmap code corresponding to the character, or 0 if not found.
 * 
 * @details This function searches through the font array for a character and returns its associated bitmap code.
 * If the character is not found, it returns 0. The font array is assumed to be defined elsewhere in the code.
 */
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

/**
 * @name Reverse_Byte
 * @brief Reverses the bits in a byte.
 * 
 * @param ( uint8_t ) b : The byte to be reversed.
 * @return ( uint8_t ) The byte with its bits reversed.
 * 
 * @details This function takes a byte and reverses its bits by performing bitwise operations.
 * It shifts the bits to their opposite positions, effectively reversing the order of the bits.
 */
uint8_t Reverse_Byte(uint8_t b)
{
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}