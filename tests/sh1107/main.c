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
#include "sh1107.h"

// -------------------------------------------------------------------- MACROS

// Display pins. SCK, MISO and MOSI must belong to the same SPI module
#define TEST_SH1107_PIN_RST  HAL_PIN_NC
#define TEST_SH1107_PIN_CS   HAL_PIN_NC
#define TEST_SH1107_PIN_DC   HAL_PIN_NC
#define TEST_SH1107_PIN_SCK  HAL_PIN_NC // SCL
#define TEST_SH1107_PIN_MISO HAL_PIN_NC // Not wired, but required by the SPI driver.
#define TEST_SH1107_PIN_MOSI HAL_PIN_NC // SDA

#define TEST_SH1107_SPI_SPEED      4000000 // In Hz (the controller supports up to 4 MHz at 3.3 V).
#define TEST_SH1107_DELAY_MS       3000
#define TEST_SH1107_SQUARE_SIZE    16
#define TEST_SH1107_INVERT_COLORS  0
#define TEST_SH1107_INIT_SEQ       NULL
#define TEST_SH1107_WIDTH          128
#define TEST_SH1107_HEIGHT         128
#define TEST_SH1107_COL_OFFSET     0
#define TEST_SH1107_DISPLAY_OFFSET 0
#define TEST_SH1107_CONTRAST       0x80

// ---------------------------------------------------------------- APPLICATION

static gl_driver_t gl_driver;   // Graphic library driver.
static sh1107_cfg_t sh1107_cfg; // SH1107 configuration.

int main()
{
    // Configure the display.
    sh1107_cfg.rst            = TEST_SH1107_PIN_RST;
    sh1107_cfg.cs             = TEST_SH1107_PIN_CS;
    sh1107_cfg.d_c            = TEST_SH1107_PIN_DC;
    sh1107_cfg.sck            = TEST_SH1107_PIN_SCK;
    sh1107_cfg.miso           = TEST_SH1107_PIN_MISO;
    sh1107_cfg.mosi           = TEST_SH1107_PIN_MOSI;
    sh1107_cfg.speed          = TEST_SH1107_SPI_SPEED;
    sh1107_cfg.width          = TEST_SH1107_WIDTH;
    sh1107_cfg.height         = TEST_SH1107_HEIGHT;
    sh1107_cfg.col_offset     = TEST_SH1107_COL_OFFSET;
    sh1107_cfg.display_offset = TEST_SH1107_DISPLAY_OFFSET;
    sh1107_cfg.contrast       = TEST_SH1107_CONTRAST;
    sh1107_cfg.invert         = TEST_SH1107_INVERT_COLORS;
    sh1107_cfg.init_seq       = TEST_SH1107_INIT_SEQ;
    // Initialize the display and link it with the graphic library.
    sh1107_init(&sh1107_cfg, &gl_driver);
    gl_set_driver(&gl_driver);

    // Fill the whole screen with white and black, one after another.
    gl_clear(GL_WHITE);
    Delay_ms(TEST_SH1107_DELAY_MS);

    gl_clear(GL_BLACK);

    // Draw a square in each corner (checks addressing and orientation).
    gl_set_brush_style(GL_BRUSH_STYLE_FILL);
    gl_set_brush_color(GL_WHITE);

    gl_draw_rect(0, 0, TEST_SH1107_SQUARE_SIZE, TEST_SH1107_SQUARE_SIZE);
    gl_draw_rect(TEST_SH1107_WIDTH - TEST_SH1107_SQUARE_SIZE, 0, TEST_SH1107_SQUARE_SIZE, TEST_SH1107_SQUARE_SIZE);
    gl_draw_rect(0, TEST_SH1107_HEIGHT - TEST_SH1107_SQUARE_SIZE, TEST_SH1107_SQUARE_SIZE, TEST_SH1107_SQUARE_SIZE);
    gl_draw_rect(TEST_SH1107_WIDTH - TEST_SH1107_SQUARE_SIZE,
                 TEST_SH1107_HEIGHT - TEST_SH1107_SQUARE_SIZE,
                 TEST_SH1107_SQUARE_SIZE, TEST_SH1107_SQUARE_SIZE);

    Delay_ms(TEST_SH1107_DELAY_MS);

    // Test display rotation. The square grows with every rotation, so the order is easy to follow.
    for (uint8_t rot = 0; rot < 4; rot++)
    {
        uint16_t size = TEST_SH1107_SQUARE_SIZE * (rot + 1);

        sh1107_rotate(rot);
        gl_clear(GL_BLACK);

        gl_set_brush_style(GL_BRUSH_STYLE_FILL);
        gl_set_brush_color(GL_WHITE);
        gl_draw_rect(0, 0, size, size);

        Delay_ms(2000);
    }

    // Test display power off/on control.
    sh1107_display_power(0);
    Delay_ms(1500);
    sh1107_display_power(1);
    Delay_ms(1500);

    sh1107_rotate(0);
    gl_clear(GL_BLACK);

    return 0;
}
