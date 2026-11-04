// ------------------------------------------------------------------ INCLUDES

#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "board.h"
#include "delays.h"
#include "gl.h"
#include "gc9107_gl.h"

// -------------------------------------------------------------------- MACROS

// IPS Display 3 Click in mikroBUS 1. The backlight (BCK) is on the PWM pin.
#define TEST_GC9107_PIN_BCK  MIKROBUS( MIKROBUS_1, MIKROBUS_PWM )
#define TEST_GC9107_PIN_RST  MIKROBUS( MIKROBUS_1, MIKROBUS_RST )
#define TEST_GC9107_PIN_CS   MIKROBUS( MIKROBUS_1, MIKROBUS_CS )
#define TEST_GC9107_PIN_SCK  MIKROBUS( MIKROBUS_1, MIKROBUS_SCK )
#define TEST_GC9107_PIN_SDI  MIKROBUS( MIKROBUS_1, MIKROBUS_MOSI )
#define TEST_GC9107_PIN_SDO  MIKROBUS( MIKROBUS_1, MIKROBUS_MISO )
#define TEST_GC9107_PIN_RS   MIKROBUS( MIKROBUS_1, MIKROBUS_INT )

// Visible area of the display.
#define TEST_GC9107_WIDTH    128
#define TEST_GC9107_HEIGHT   115

#define TEST_GC9107_COLOR_DELAY_MS 2000
#define TEST_GC9107_SQUARE_SIZE    20
// The glass is round and clips the corners, so the squares are inset.
#define TEST_GC9107_MARGIN         24

// ---------------------------------------------------------------- APPLICATION

static gl_driver_t gl_driver;       // Graphic library driver.
static gc9107_cfg_t gc9107_cfg;     // GC9107 configuration.

// Draw a square near each corner of the current (rotated) display.
static void draw_marks()
{
    uint16_t width = gc9107_gl_get_display_width();
    uint16_t height = gc9107_gl_get_display_height();

    gl_set_brush_style( GL_BRUSH_STYLE_FILL );

    gl_set_brush_color( GL_RED );
    gl_draw_rect( TEST_GC9107_MARGIN, TEST_GC9107_MARGIN,
                  TEST_GC9107_SQUARE_SIZE, TEST_GC9107_SQUARE_SIZE );
    gl_set_brush_color( GL_GREEN );
    gl_draw_rect( width - TEST_GC9107_MARGIN - TEST_GC9107_SQUARE_SIZE, TEST_GC9107_MARGIN,
                  TEST_GC9107_SQUARE_SIZE, TEST_GC9107_SQUARE_SIZE );
    gl_set_brush_color( GL_BLUE );
    gl_draw_rect( TEST_GC9107_MARGIN, height - TEST_GC9107_MARGIN - TEST_GC9107_SQUARE_SIZE,
                  TEST_GC9107_SQUARE_SIZE, TEST_GC9107_SQUARE_SIZE );
    gl_set_brush_color( GL_WHITE );
    gl_draw_rect( width - TEST_GC9107_MARGIN - TEST_GC9107_SQUARE_SIZE,
                  height - TEST_GC9107_MARGIN - TEST_GC9107_SQUARE_SIZE,
                  TEST_GC9107_SQUARE_SIZE, TEST_GC9107_SQUARE_SIZE );
}

int main()
{
    // Configure the display.
    gc9107_cfg.bck    = TEST_GC9107_PIN_BCK;
    gc9107_cfg.rst    = TEST_GC9107_PIN_RST;
    gc9107_cfg.cs     = TEST_GC9107_PIN_CS;
    gc9107_cfg.sck    = TEST_GC9107_PIN_SCK;
    gc9107_cfg.sdi    = TEST_GC9107_PIN_SDI;
    gc9107_cfg.sdo    = TEST_GC9107_PIN_SDO;
    gc9107_cfg.rs     = TEST_GC9107_PIN_RS;
    gc9107_cfg.width  = TEST_GC9107_WIDTH;
    gc9107_cfg.height = TEST_GC9107_HEIGHT;

    // Initialize the display and link it with the graphic library.
    gc9107_gl_init( &gc9107_cfg, &gl_driver );
    gl_set_driver( &gl_driver );

    // Fill the whole screen with basic colors, one after another.
    gl_clear( GL_RED );
    Delay_ms( TEST_GC9107_COLOR_DELAY_MS );

    gl_clear( GL_GREEN );
    Delay_ms( TEST_GC9107_COLOR_DELAY_MS );

    gl_clear( GL_BLUE );
    Delay_ms( TEST_GC9107_COLOR_DELAY_MS );

    gl_clear( GL_WHITE );
    Delay_ms( TEST_GC9107_COLOR_DELAY_MS );

    gl_clear( GL_BLACK );

    // Squares near the corners (checks addressing and orientation).
    draw_marks();
    Delay_ms( TEST_GC9107_COLOR_DELAY_MS );

    // Test display rotation.
    for ( uint8_t rot = 0; rot < 4; rot++ )
    {
        gc9107_gl_rotate( rot );
        gl_clear( GL_BLACK );
        draw_marks();

        Delay_ms( TEST_GC9107_COLOR_DELAY_MS );
    }

    // Test display power off/on control.
    gc9107_gl_display_power( 0 );
    Delay_ms( 1500 );
    gc9107_gl_display_power( 1 );
    Delay_ms( 1500 );

    gc9107_gl_rotate( 0 );
    gl_clear( GL_BLACK );

    return 0;
}
