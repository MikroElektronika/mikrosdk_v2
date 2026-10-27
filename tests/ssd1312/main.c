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
#include "ssd1312.h"
#include "ssd1312_cmd.h"
#include "drv_i2c_master.h"

// -------------------------------------------------------------------- MACROS

// Display pins. SCL and SDA must belong to the same I2C module
#define TEST_SSD1312_PIN_RST  HAL_PIN_NC
#define TEST_SSD1312_PIN_SCL  HAL_PIN_NC // SCL
#define TEST_SSD1312_PIN_SDA  HAL_PIN_NC // SDA

#define TEST_SSD1312_I2C_ADDRESS    0x3C
#define TEST_SSD1312_I2C_SPEED      I2C_MASTER_SPEED_STANDARD // 100 kHz
#define TEST_SSD1312_DELAY_MS       3000
#define TEST_SSD1312_SQUARE_SIZE    16
#define TEST_SSD1312_INVERT_COLORS  0
#define TEST_SSD1312_INIT_SEQ       NULL
#define TEST_SSD1312_WIDTH          64
#define TEST_SSD1312_HEIGHT         128
#define TEST_SSD1312_COL_OFFSET     0
#define TEST_SSD1312_DISPLAY_OFFSET 0x20
#define TEST_SSD1312_CONTRAST       0x80

// ---------------------------------------------------------------- APPLICATION

static gl_driver_t gl_driver;   // Graphic library driver.
static ssd1312_cfg_t ssd1312_cfg; // SSD1312 configuration.

int main()
{
    // Configure the display.
    ssd1312_cfg.rst            = TEST_SSD1312_PIN_RST;
    ssd1312_cfg.scl            = TEST_SSD1312_PIN_SCL;
    ssd1312_cfg.sda            = TEST_SSD1312_PIN_SDA;
    ssd1312_cfg.address        = TEST_SSD1312_I2C_ADDRESS;
    ssd1312_cfg.speed          = TEST_SSD1312_I2C_SPEED;
    ssd1312_cfg.width          = TEST_SSD1312_WIDTH;
    ssd1312_cfg.height         = TEST_SSD1312_HEIGHT;
    ssd1312_cfg.col_offset     = TEST_SSD1312_COL_OFFSET;
    ssd1312_cfg.display_offset = TEST_SSD1312_DISPLAY_OFFSET;
    ssd1312_cfg.contrast       = TEST_SSD1312_CONTRAST;
    ssd1312_cfg.invert         = TEST_SSD1312_INVERT_COLORS;
    ssd1312_cfg.init_seq       = TEST_SSD1312_INIT_SEQ;
    // Initialize the display and link it with the graphic library.
    ssd1312_init(&ssd1312_cfg, &gl_driver);
    gl_set_driver(&gl_driver);

    // Fill the whole screen with white and black, one after another.
    gl_clear(GL_WHITE);
    Delay_ms(TEST_SSD1312_DELAY_MS);

    gl_clear(GL_BLACK);

    // Draw a square in each corner (checks addressing and orientation).
    gl_set_brush_style(GL_BRUSH_STYLE_FILL);
    gl_set_brush_color(GL_WHITE);

    gl_draw_rect(0, 0, TEST_SSD1312_SQUARE_SIZE, TEST_SSD1312_SQUARE_SIZE);
    gl_draw_rect(TEST_SSD1312_WIDTH - TEST_SSD1312_SQUARE_SIZE, 0, TEST_SSD1312_SQUARE_SIZE, TEST_SSD1312_SQUARE_SIZE);
    gl_draw_rect(0, TEST_SSD1312_HEIGHT - TEST_SSD1312_SQUARE_SIZE, TEST_SSD1312_SQUARE_SIZE, TEST_SSD1312_SQUARE_SIZE);
    gl_draw_rect(TEST_SSD1312_WIDTH - TEST_SSD1312_SQUARE_SIZE,
                 TEST_SSD1312_HEIGHT - TEST_SSD1312_SQUARE_SIZE,
                 TEST_SSD1312_SQUARE_SIZE, TEST_SSD1312_SQUARE_SIZE);

    Delay_ms(TEST_SSD1312_DELAY_MS);

    // Test display rotation. The square grows with every rotation, so the order is easy to follow.
    for (uint8_t rot = 0; rot < 4; rot++)
    {
        uint16_t size = TEST_SSD1312_SQUARE_SIZE + 8 * rot;

        ssd1312_rotate(rot);
        gl_clear(GL_BLACK);

        gl_set_brush_style(GL_BRUSH_STYLE_FILL);
        gl_set_brush_color(GL_WHITE);
        gl_draw_rect(0, 0, size, size);

        Delay_ms(2000);
    }

    // Test display power off/on control.
    ssd1312_display_power(0);
    Delay_ms(1500);
    ssd1312_display_power(1);
    Delay_ms(1500);

    ssd1312_rotate(0);
    gl_clear(GL_BLACK);

    return 0;
}
