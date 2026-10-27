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
#include "st7525i.h"

// -------------------------------------------------------------------- MACROS

// Display pins. SCK, MISO and MOSI must belong to the same SPI module
#define TEST_ST7525I_PIN_RST  HAL_PIN_NC
#define TEST_ST7525I_PIN_CS   HAL_PIN_NC
#define TEST_ST7525I_PIN_DC   HAL_PIN_NC // RS (A0)
#define TEST_ST7525I_PIN_SCK  HAL_PIN_NC // D0 (SCL)
#define TEST_ST7525I_PIN_MISO HAL_PIN_NC // Not wired, but required by the SPI driver.
#define TEST_ST7525I_PIN_MOSI HAL_PIN_NC // D1 (SDA)

#define TEST_ST7525I_SPI_SPEED      4000000 // In Hz (the datasheet gives no maximum, start low).
#define TEST_ST7525I_DELAY_MS       3000
#define TEST_ST7525I_SQUARE_SIZE    12
#define TEST_ST7525I_INVERT_COLORS  1
#define TEST_ST7525I_INIT_SEQ       NULL
#define TEST_ST7525I_WIDTH          192
#define TEST_ST7525I_HEIGHT         64
#define TEST_ST7525I_CONTRAST       0x70

// ---------------------------------------------------------------- APPLICATION

static gl_driver_t gl_driver;      // Graphic library driver.
static st7525i_cfg_t st7525i_cfg; // ST7525I configuration.

int main()
{
    // Configure the display.
    st7525i_cfg.rst      = TEST_ST7525I_PIN_RST;
    st7525i_cfg.cs       = TEST_ST7525I_PIN_CS;
    st7525i_cfg.d_c      = TEST_ST7525I_PIN_DC;
    st7525i_cfg.sck      = TEST_ST7525I_PIN_SCK;
    st7525i_cfg.miso     = TEST_ST7525I_PIN_MISO;
    st7525i_cfg.mosi     = TEST_ST7525I_PIN_MOSI;
    st7525i_cfg.speed    = TEST_ST7525I_SPI_SPEED;
    st7525i_cfg.width    = TEST_ST7525I_WIDTH;
    st7525i_cfg.height   = TEST_ST7525I_HEIGHT;
    st7525i_cfg.contrast = TEST_ST7525I_CONTRAST;
    st7525i_cfg.invert   = TEST_ST7525I_INVERT_COLORS;
    st7525i_cfg.init_seq = TEST_ST7525I_INIT_SEQ;
    // Initialize the display and link it with the graphic library.
    st7525i_init(&st7525i_cfg, &gl_driver);
    gl_set_driver(&gl_driver);

    // Fill the whole screen with white and black, one after another.
    gl_clear(GL_WHITE);
    Delay_ms(TEST_ST7525I_DELAY_MS);

    gl_clear(GL_BLACK);
    Delay_ms(TEST_ST7525I_DELAY_MS);

    gl_clear(GL_WHITE);

    // Draw a square in each corner (checks addressing and orientation).
    gl_set_brush_style(GL_BRUSH_STYLE_FILL);
    gl_set_brush_color(GL_BLACK);

    gl_draw_rect(0, 0, TEST_ST7525I_SQUARE_SIZE, TEST_ST7525I_SQUARE_SIZE);
    gl_draw_rect(TEST_ST7525I_WIDTH - TEST_ST7525I_SQUARE_SIZE, 0, TEST_ST7525I_SQUARE_SIZE, TEST_ST7525I_SQUARE_SIZE);
    gl_draw_rect(0, TEST_ST7525I_HEIGHT - TEST_ST7525I_SQUARE_SIZE, TEST_ST7525I_SQUARE_SIZE, TEST_ST7525I_SQUARE_SIZE);
    gl_draw_rect(TEST_ST7525I_WIDTH - TEST_ST7525I_SQUARE_SIZE,
                 TEST_ST7525I_HEIGHT - TEST_ST7525I_SQUARE_SIZE,
                 TEST_ST7525I_SQUARE_SIZE, TEST_ST7525I_SQUARE_SIZE);

    Delay_ms(TEST_ST7525I_DELAY_MS);

    // Test display rotation. The square grows with every rotation, so the order is easy to follow.
    for (uint8_t rot = 0; rot < 4; rot++)
    {
        uint16_t size = TEST_ST7525I_SQUARE_SIZE * (rot + 1);

        st7525i_rotate(rot);
        // The Graphics Library keeps its own copy of the display size, so refresh it after a rotation.
        gl_set_driver(&gl_driver);
        gl_clear(GL_WHITE);

        gl_set_brush_style(GL_BRUSH_STYLE_FILL);
        gl_set_brush_color(GL_BLACK);
        gl_draw_rect(0, 0, size, size);

        Delay_ms(2000);
    }

    // Test display power off/on control.
    st7525i_display_power(0);
    Delay_ms(1500);
    st7525i_display_power(1);
    Delay_ms(1500);

    st7525i_rotate(0);
    gl_set_driver(&gl_driver);
    gl_clear(GL_WHITE);

    return 0;
}
