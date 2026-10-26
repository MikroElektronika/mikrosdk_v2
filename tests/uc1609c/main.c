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
#include "uc1609c.h"

// -------------------------------------------------------------------- MACROS

// Display pins. SCK, MISO and MOSI must belong to the same SPI module
#define TEST_UC1609C_PIN_RST  HAL_PIN_NC
#define TEST_UC1609C_PIN_CS   HAL_PIN_NC
#define TEST_UC1609C_PIN_DC   HAL_PIN_NC // CD
#define TEST_UC1609C_PIN_SCK  HAL_PIN_NC // SCK
#define TEST_UC1609C_PIN_MISO HAL_PIN_NC // Not wired, but required by the SPI driver.
#define TEST_UC1609C_PIN_MOSI HAL_PIN_NC // SDA

#define TEST_UC1609C_SPI_SPEED      1000000 // In Hz (the datasheet gives no maximum, start low).
#define TEST_UC1609C_DELAY_MS       3000
#define TEST_UC1609C_SQUARE_SIZE    12
#define TEST_UC1609C_INVERT_COLORS  0
#define TEST_UC1609C_INIT_SEQ       NULL
#define TEST_UC1609C_WIDTH          192
#define TEST_UC1609C_HEIGHT         64
#define TEST_UC1609C_CONTRAST       0xB0

// ---------------------------------------------------------------- APPLICATION

static gl_driver_t gl_driver;     // Graphic library driver.
static uc1609c_cfg_t uc1609c_cfg; // UC1609C configuration.

int main()
{
    // Configure the display.
    uc1609c_cfg.rst      = TEST_UC1609C_PIN_RST;
    uc1609c_cfg.cs       = TEST_UC1609C_PIN_CS;
    uc1609c_cfg.d_c      = TEST_UC1609C_PIN_DC;
    uc1609c_cfg.sck      = TEST_UC1609C_PIN_SCK;
    uc1609c_cfg.miso     = TEST_UC1609C_PIN_MISO;
    uc1609c_cfg.mosi     = TEST_UC1609C_PIN_MOSI;
    uc1609c_cfg.speed    = TEST_UC1609C_SPI_SPEED;
    uc1609c_cfg.width    = TEST_UC1609C_WIDTH;
    uc1609c_cfg.height   = TEST_UC1609C_HEIGHT;
    uc1609c_cfg.contrast = TEST_UC1609C_CONTRAST;
    uc1609c_cfg.invert   = TEST_UC1609C_INVERT_COLORS;
    uc1609c_cfg.init_seq = TEST_UC1609C_INIT_SEQ;
    // Initialize the display and link it with the graphic library.
    uc1609c_init(&uc1609c_cfg, &gl_driver);
    gl_set_driver(&gl_driver);

    // Fill the whole screen with white and black, one after another.
    gl_clear(GL_WHITE);
    Delay_ms(TEST_UC1609C_DELAY_MS);

    gl_clear(GL_BLACK);
    Delay_ms(TEST_UC1609C_DELAY_MS);

    gl_clear(GL_WHITE);

    // Draw a square in each corner (checks addressing and orientation).
    gl_set_brush_style(GL_BRUSH_STYLE_FILL);
    gl_set_brush_color(GL_BLACK);

    gl_draw_rect(0, 0, TEST_UC1609C_SQUARE_SIZE, TEST_UC1609C_SQUARE_SIZE);
    gl_draw_rect(TEST_UC1609C_WIDTH - TEST_UC1609C_SQUARE_SIZE, 0, TEST_UC1609C_SQUARE_SIZE, TEST_UC1609C_SQUARE_SIZE);
    gl_draw_rect(0, TEST_UC1609C_HEIGHT - TEST_UC1609C_SQUARE_SIZE, TEST_UC1609C_SQUARE_SIZE, TEST_UC1609C_SQUARE_SIZE);
    gl_draw_rect(TEST_UC1609C_WIDTH - TEST_UC1609C_SQUARE_SIZE,
                 TEST_UC1609C_HEIGHT - TEST_UC1609C_SQUARE_SIZE,
                 TEST_UC1609C_SQUARE_SIZE, TEST_UC1609C_SQUARE_SIZE);

    Delay_ms(TEST_UC1609C_DELAY_MS);

    // Test display rotation. The square grows with every rotation, so the order is easy to follow.
    for (uint8_t rot = 0; rot < 4; rot++)
    {
        uint16_t size = TEST_UC1609C_SQUARE_SIZE * (rot + 1);

        uc1609c_rotate(rot);
        // The Graphics Library keeps its own copy of the display size, so refresh it after a rotation.
        gl_set_driver(&gl_driver);
        gl_clear(GL_WHITE);

        gl_set_brush_style(GL_BRUSH_STYLE_FILL);
        gl_set_brush_color(GL_BLACK);
        gl_draw_rect(0, 0, size, size);

        Delay_ms(2000);
    }

    // Test display power off/on control.
    uc1609c_display_power(0);
    Delay_ms(1500);
    uc1609c_display_power(1);
    Delay_ms(1500);

    uc1609c_rotate(0);
    gl_set_driver(&gl_driver);
    gl_clear(GL_WHITE);

    return 0;
}
