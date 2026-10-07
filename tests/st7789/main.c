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
#include "st7789.h"

// -------------------------------------------------------------------- MACROS

// Display pins. SCK, MISO and MOSI must belong to the same SPI module.
#define TEST_ST7789_PIN_RST   GPIO_PG8
#define TEST_ST7789_PIN_DC    GPIO_PG10
#define TEST_ST7789_PIN_SCK   GPIO_PG13   // SCL
#define TEST_ST7789_PIN_MISO  GPIO_PG12   // Not wired, but required by the SPI driver.
#define TEST_ST7789_PIN_MOSI  GPIO_PG14   // SDA

#define TEST_ST7789_SPI_SPEED 20000000    // In Hz.
#define TEST_ST7789_SPI_MODE  0           // SPI mode (0 to 3). Not used when soft_spi is 1.
#define TEST_ST7789_COLOR_DELAY_MS 3000
#define TEST_ST7789_SQUARE_SIZE    40

// Uncomment for the 1.3" GMT130 module (no CS, 240x240, soft SPI, own init sequence).
// Leave commented for GMT020-02, GMT024-10 and GMT028-05.
// #define TEST_GMT130

#ifdef TEST_GMT130
    #define TEST_ST7789_PIN_CS        HAL_PIN_NC
    #define TEST_ST7789_WIDTH         240
    #define TEST_ST7789_HEIGHT        240
    #define TEST_ST7789_INVERT_COLORS 1
    #define TEST_ST7789_SOFT_SPI      1
    #define TEST_ST7789_INIT_SEQ      gmt130_init
#else
    #define TEST_ST7789_PIN_CS        GPIO_PG9
    #define TEST_ST7789_WIDTH         240
    #define TEST_ST7789_HEIGHT        320
    #define TEST_ST7789_INVERT_COLORS 0     // 1 for GMT020-02.
    #define TEST_ST7789_SOFT_SPI      0
    #define TEST_ST7789_INIT_SEQ      NULL
#endif

// ---------------------------------------------------------------- APPLICATION

static gl_driver_t gl_driver;   // Graphic library driver.
static st7789_cfg_t st7789_cfg; // ST7789 configuration.

// GMT130 manufacturer power, voltage and gamma settings: command, number of parameters, parameters. Ends with 0.
static const uint8_t gmt130_init[] =
{
    0xB2, 5, 0x0C, 0x0C, 0x00, 0x33, 0x33,
    0xB7, 1, 0x35,
    0xBB, 1, 0x19,
    0xC0, 1, 0x2C,
    0xC2, 1, 0x01,
    0xC3, 1, 0x12,
    0xC4, 1, 0x20,
    0xC6, 1, 0x0F,
    0xD0, 2, 0xA4, 0xA1,
    0xE0, 14, 0xD0, 0x04, 0x0D, 0x11, 0x13, 0x2B, 0x3F, 0x54, 0x4C, 0x18, 0x0D, 0x0B, 0x1F, 0x23,
    0xE1, 14, 0xD0, 0x04, 0x0C, 0x11, 0x13, 0x2C, 0x3F, 0x44, 0x51, 0x2F, 0x1F, 0x1F, 0x20, 0x23,
    0
};

int main()
{
    // Configure the display.
    st7789_cfg.rst      = TEST_ST7789_PIN_RST;
    st7789_cfg.cs       = TEST_ST7789_PIN_CS;
    st7789_cfg.d_c      = TEST_ST7789_PIN_DC;
    st7789_cfg.sck      = TEST_ST7789_PIN_SCK;
    st7789_cfg.miso     = TEST_ST7789_PIN_MISO;
    st7789_cfg.mosi     = TEST_ST7789_PIN_MOSI;
    st7789_cfg.speed    = TEST_ST7789_SPI_SPEED;
    st7789_cfg.width    = TEST_ST7789_WIDTH;
    st7789_cfg.height   = TEST_ST7789_HEIGHT;
    st7789_cfg.invert   = TEST_ST7789_INVERT_COLORS;
    st7789_cfg.spi_mode = TEST_ST7789_SPI_MODE;
    st7789_cfg.soft_spi = TEST_ST7789_SOFT_SPI;
    st7789_cfg.init_seq = TEST_ST7789_INIT_SEQ;

    // Initialize the display and link it with the graphic library.
    st7789_init(&st7789_cfg, &gl_driver);
    gl_set_driver(&gl_driver);

    // Fill the whole screen with basic colors, one after another.
    gl_clear(GL_RED);
    Delay_ms(TEST_ST7789_COLOR_DELAY_MS);

    gl_clear(GL_GREEN);
    Delay_ms(TEST_ST7789_COLOR_DELAY_MS);

    gl_clear(GL_BLUE);
    Delay_ms(TEST_ST7789_COLOR_DELAY_MS);

    gl_clear(GL_WHITE);
    Delay_ms(TEST_ST7789_COLOR_DELAY_MS);

    gl_clear(GL_BLACK);

    // Draw a square in each corner (checks addressing and orientation).
    gl_set_brush_style(GL_BRUSH_STYLE_FILL);

    gl_set_brush_color(GL_RED);
    gl_draw_rect(0, 0, TEST_ST7789_SQUARE_SIZE, TEST_ST7789_SQUARE_SIZE);
    gl_set_brush_color(GL_GREEN);
    gl_draw_rect(TEST_ST7789_WIDTH - TEST_ST7789_SQUARE_SIZE, 0, TEST_ST7789_SQUARE_SIZE, TEST_ST7789_SQUARE_SIZE);
    gl_set_brush_color(GL_BLUE);
    gl_draw_rect(0, TEST_ST7789_HEIGHT - TEST_ST7789_SQUARE_SIZE, TEST_ST7789_SQUARE_SIZE, TEST_ST7789_SQUARE_SIZE);
    gl_set_brush_color(GL_WHITE);
    gl_draw_rect(TEST_ST7789_WIDTH - TEST_ST7789_SQUARE_SIZE, TEST_ST7789_HEIGHT - TEST_ST7789_SQUARE_SIZE, TEST_ST7789_SQUARE_SIZE, TEST_ST7789_SQUARE_SIZE);

    Delay_ms(TEST_ST7789_COLOR_DELAY_MS);

    // Test display rotation.
    for (uint8_t rot = 0; rot < 4; rot++)
    {
        st7789_rotate(rot);
        gl_clear(GL_BLACK);

        gl_set_brush_style(GL_BRUSH_STYLE_FILL);
        gl_set_brush_color(GL_RED);
        gl_draw_rect(0, 0, 60, 60);

        Delay_ms(2000);
    }

    // Test display power off/on control.
    st7789_display_power(0);
    Delay_ms(1500);
    st7789_display_power(1);
    Delay_ms(1500);

    st7789_rotate(0);
    gl_clear(GL_BLACK);

    return 0;
}