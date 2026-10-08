// ------------------------------------------------------------------ INCLUDES

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "board.h"
#include "delays.h"
#include "gl.h"
#include "st7735s.h"

// -------------------------------------------------------------------- MACROS

// Display pins. SCK, MISO and MOSI must belong to the same SPI module.
#define TEST_ST7735S_PIN_RST   GPIO_PG8
#define TEST_ST7735S_PIN_CS        GPIO_PG9
#define TEST_ST7735S_PIN_DC    GPIO_PG10
#define TEST_ST7735S_PIN_SCK   GPIO_PG13   // SCL
#define TEST_ST7735S_PIN_MISO  GPIO_PG12   // Not wired, but required by the SPI driver.
#define TEST_ST7735S_PIN_MOSI  GPIO_PG14   // SDA

#define TEST_ST7735S_SPI_SPEED 10000000    // In Hz.
#define TEST_ST7735S_COLOR_DELAY_MS 3000
#define TEST_ST7735S_SQUARE_SIZE    40
#define TEST_ST7735S_INVERT_COLORS 0
#define TEST_ST7735S_INIT_SEQ      NULL

// Select the module to test. Define exactly one of them.
//#define TEST_GMT177   // 1.77", 128x160.
#define TEST_GMT144   // 1.44", 128x128.

#if defined(TEST_GMT144)
    #define TEST_ST7735S_WIDTH         128
    #define TEST_ST7735S_HEIGHT        128
    #define TEST_ST7735S_RAM_WIDTH     132
    #define TEST_ST7735S_RAM_HEIGHT    132
    #define TEST_ST7735S_COL_OFFSET    2
    #define TEST_ST7735S_ROW_OFFSET    1
    #define TEST_ST7735S_BGR           1
#elif defined(TEST_GMT177)
    #define TEST_ST7735S_WIDTH         128
    #define TEST_ST7735S_HEIGHT        160
    #define TEST_ST7735S_RAM_WIDTH     128
    #define TEST_ST7735S_RAM_HEIGHT    160
    #define TEST_ST7735S_COL_OFFSET    0
    #define TEST_ST7735S_ROW_OFFSET    0
    #define TEST_ST7735S_BGR           0
#else
    #error "Select a module: define TEST_GMT177 or TEST_GMT144."
#endif
// ---------------------------------------------------------------- APPLICATION

static gl_driver_t gl_driver;   // Graphic library driver.
static st7735s_cfg_t st7735s_cfg; // ST7735S configuration.

int main()
{
    // Configure the display.
    st7735s_cfg.rst      = TEST_ST7735S_PIN_RST;
    st7735s_cfg.cs       = TEST_ST7735S_PIN_CS;
    st7735s_cfg.d_c      = TEST_ST7735S_PIN_DC;
    st7735s_cfg.sck      = TEST_ST7735S_PIN_SCK;
    st7735s_cfg.miso     = TEST_ST7735S_PIN_MISO;
    st7735s_cfg.mosi     = TEST_ST7735S_PIN_MOSI;
    st7735s_cfg.speed    = TEST_ST7735S_SPI_SPEED;
    st7735s_cfg.width    = TEST_ST7735S_WIDTH;
    st7735s_cfg.height   = TEST_ST7735S_HEIGHT;
    st7735s_cfg.ram_width  = TEST_ST7735S_RAM_WIDTH;
    st7735s_cfg.ram_height = TEST_ST7735S_RAM_HEIGHT;
    st7735s_cfg.col_offset = TEST_ST7735S_COL_OFFSET;
    st7735s_cfg.row_offset = TEST_ST7735S_ROW_OFFSET;
    st7735s_cfg.bgr        = TEST_ST7735S_BGR;
    st7735s_cfg.invert   = TEST_ST7735S_INVERT_COLORS;
    st7735s_cfg.init_seq = TEST_ST7735S_INIT_SEQ;

    // Initialize the display and link it with the graphic library.
    st7735s_init(&st7735s_cfg, &gl_driver);
    gl_set_driver(&gl_driver);

    // Fill the whole screen with basic colors, one after another.
    gl_clear(GL_RED);
    Delay_ms(TEST_ST7735S_COLOR_DELAY_MS);

    gl_clear(GL_GREEN);
    Delay_ms(TEST_ST7735S_COLOR_DELAY_MS);

    gl_clear(GL_BLUE);
    Delay_ms(TEST_ST7735S_COLOR_DELAY_MS);

    gl_clear(GL_WHITE);
    Delay_ms(TEST_ST7735S_COLOR_DELAY_MS);

    gl_clear(GL_BLACK);

    // Draw a square in each corner (checks addressing and orientation).
    gl_set_brush_style(GL_BRUSH_STYLE_FILL);

    gl_set_brush_color(GL_RED);
    gl_draw_rect(0, 0, TEST_ST7735S_SQUARE_SIZE, TEST_ST7735S_SQUARE_SIZE);
    gl_set_brush_color(GL_GREEN);
    gl_draw_rect(TEST_ST7735S_WIDTH - TEST_ST7735S_SQUARE_SIZE, 0, TEST_ST7735S_SQUARE_SIZE, TEST_ST7735S_SQUARE_SIZE);
    gl_set_brush_color(GL_BLUE);
    gl_draw_rect(0, TEST_ST7735S_HEIGHT - TEST_ST7735S_SQUARE_SIZE, TEST_ST7735S_SQUARE_SIZE, TEST_ST7735S_SQUARE_SIZE);
    gl_set_brush_color(GL_WHITE);
    gl_draw_rect(TEST_ST7735S_WIDTH - TEST_ST7735S_SQUARE_SIZE, TEST_ST7735S_HEIGHT - TEST_ST7735S_SQUARE_SIZE, TEST_ST7735S_SQUARE_SIZE, TEST_ST7735S_SQUARE_SIZE);

    Delay_ms(TEST_ST7735S_COLOR_DELAY_MS);

    // Test display rotation.
    for (uint8_t rot = 0; rot < 4; rot++)
    {
        st7735s_rotate(rot);
        gl_clear(GL_BLACK);

        gl_set_brush_style(GL_BRUSH_STYLE_FILL);
        gl_set_brush_color(GL_RED);
        gl_draw_rect(0, 0, 60, 60);

        Delay_ms(2000);
    }

    // Test display power off/on control.
    st7735s_display_power(0);
    Delay_ms(1500);
    st7735s_display_power(1);
    Delay_ms(1500);

    st7735s_rotate(0);
    gl_clear(GL_BLACK);

    return 0;
}