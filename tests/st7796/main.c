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
#include "st7796.h"

// -------------------------------------------------------------------- MACROS

// Display pins. SCK, MISO and MOSI must belong to the same SPI module.
#define TEST_ST7796_PIN_RST   GPIO_PG8
#define TEST_ST7796_PIN_CS    GPIO_PG9
#define TEST_ST7796_PIN_DC    GPIO_PG10
#define TEST_ST7796_PIN_SCK   GPIO_PG13   // SCL
#define TEST_ST7796_PIN_MISO  GPIO_PG12   // Not wired, but required by the SPI driver.
#define TEST_ST7796_PIN_MOSI  GPIO_PG14   // SDA

#define TEST_ST7796_SPI_SPEED 10000000    // In Hz.
#define TEST_ST7796_COLOR_DELAY_MS 3000
#define TEST_ST7796_SQUARE_SIZE    40
#define TEST_ST7796_INVERT_COLORS 0
#define TEST_ST7796_INIT_SEQ      NULL
#define TEST_ST7796_WIDTH         320
#define TEST_ST7796_HEIGHT        480
#define TEST_ST7796_BGR           1

// ---------------------------------------------------------------- APPLICATION

static gl_driver_t gl_driver;   // Graphic library driver.
static st7796_cfg_t st7796_cfg; // ST7796 configuration.

int main()
{
    // Configure the display.
    st7796_cfg.rst      = TEST_ST7796_PIN_RST;
    st7796_cfg.cs       = TEST_ST7796_PIN_CS;
    st7796_cfg.d_c      = TEST_ST7796_PIN_DC;
    st7796_cfg.sck      = TEST_ST7796_PIN_SCK;
    st7796_cfg.miso     = TEST_ST7796_PIN_MISO;
    st7796_cfg.mosi     = TEST_ST7796_PIN_MOSI;
    st7796_cfg.speed    = TEST_ST7796_SPI_SPEED;
    st7796_cfg.width    = TEST_ST7796_WIDTH;
    st7796_cfg.height   = TEST_ST7796_HEIGHT;
    st7796_cfg.bgr        = TEST_ST7796_BGR;
    st7796_cfg.invert   = TEST_ST7796_INVERT_COLORS;
    st7796_cfg.init_seq = TEST_ST7796_INIT_SEQ;

    // Initialize the display and link it with the graphic library.
    st7796_init(&st7796_cfg, &gl_driver);
    gl_set_driver(&gl_driver);

    // Fill the whole screen with basic colors, one after another.
    gl_clear(GL_RED);
    Delay_ms(TEST_ST7796_COLOR_DELAY_MS);

    gl_clear(GL_GREEN);
    Delay_ms(TEST_ST7796_COLOR_DELAY_MS);

    gl_clear(GL_BLUE);
    Delay_ms(TEST_ST7796_COLOR_DELAY_MS);

    gl_clear(GL_WHITE);
    Delay_ms(TEST_ST7796_COLOR_DELAY_MS);

    gl_clear(GL_BLACK);

    // Draw a square in each corner (checks addressing and orientation).
    gl_set_brush_style(GL_BRUSH_STYLE_FILL);

    gl_set_brush_color(GL_RED);
    gl_draw_rect(0, 0, TEST_ST7796_SQUARE_SIZE, TEST_ST7796_SQUARE_SIZE);
    gl_set_brush_color(GL_GREEN);
    gl_draw_rect(TEST_ST7796_WIDTH - TEST_ST7796_SQUARE_SIZE, 0, TEST_ST7796_SQUARE_SIZE, TEST_ST7796_SQUARE_SIZE);
    gl_set_brush_color(GL_BLUE);
    gl_draw_rect(0, TEST_ST7796_HEIGHT - TEST_ST7796_SQUARE_SIZE, TEST_ST7796_SQUARE_SIZE, TEST_ST7796_SQUARE_SIZE);
    gl_set_brush_color(GL_WHITE);
    gl_draw_rect(TEST_ST7796_WIDTH - TEST_ST7796_SQUARE_SIZE, TEST_ST7796_HEIGHT - TEST_ST7796_SQUARE_SIZE, TEST_ST7796_SQUARE_SIZE, TEST_ST7796_SQUARE_SIZE);

    Delay_ms(TEST_ST7796_COLOR_DELAY_MS);

    // Test display rotation.
    for (uint8_t rot = 0; rot < 4; rot++)
    {
        st7796_rotate(rot);
        gl_clear(GL_BLACK);

        gl_set_brush_style(GL_BRUSH_STYLE_FILL);
        gl_set_brush_color(GL_RED);
        gl_draw_rect(0, 0, 60, 60);

        Delay_ms(2000);
    }

    // Test display power off/on control.
    st7796_display_power(0);
    Delay_ms(1500);
    st7796_display_power(1);
    Delay_ms(1500);

    st7796_rotate(0);
    gl_clear(GL_BLACK);

    return 0;
}