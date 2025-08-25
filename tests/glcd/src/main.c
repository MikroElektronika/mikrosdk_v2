// ------------------------------------------------------------------ INCLUDES

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "glcd.h"

glcd_t glcd;

/**
 * @brief Main function for GLCD test.
 * @details Initializes the GLCD and displays a simple pattern (dots, segements).
 * @return Nothing.
 */
static void test1( void );

/**
 * @brief Secondary test function.
 * @details This function can be used to test additional GLCD functionalities (circle, rectangles, ellipses).
 * @return Nothing.
 */
static void test2( void );

/**
 * @brief Third test function.
 * @details This function can be used to test additional GLCD functionalities (character and text writing).
 * @return Nothing.
 */
static void test3( void );

int main( void )
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    GLCD_MAP_PINS( &glcd );
    glcd_init( &glcd );
    glcd_display( &glcd, GLCD_DISPLAY_ON );
    glcd_clear( &glcd );

    while ( 1)
    {
        // Run the first test to initialize GLCD and display some patterns.
        test1();

        // Run the second test to draw circles and ellipses.
        test2();

        // Run the third test to write characters and text on GLCD.
        test3();

    }

    return 0;
}

static void test1( void )
{
    glcd_point_t pts[] = { { 10, 10 }, { 20, 20 }, { 30, 30 } };
    glcd_draw_dots( &glcd, pts, sizeof( pts ) / sizeof( pts[ 0 ] ), 2 );

    Delay_ms( 1000 );
    glcd_clear( &glcd );

    glcd_segment_t s = { { { 10, 10 }, { 50, 50 } }, 2 };
    glcd_draw_line( &glcd, &s, 1, GLCD_DIAGONAL );
    Delay_ms( 1000 );
    glcd_clear( &glcd );
}

static void test2( void )
{
    glcd_point_t d = { 32, 32 };
    glcd_rect_t r = { 80, 30, 2, false, false };
    glcd_draw_rect( &glcd, &d, 1, &r, 1 );
    Delay_ms( 1000 );
    glcd_clear( &glcd );

    glcd_circle_t c = { { 64, 32 }, 20, 2, true };
    glcd_draw_circle( &glcd, &c, 1, GLCD_DEFAULT );
    Delay_ms( 1000 );
    glcd_clear( &glcd );

    glcd_ellipse_t e = { { { 64, 32 }, { 80, 32 } }, 30.0f, 2, true };
    glcd_draw_ellipse( &glcd, &e, 1, GLCD_DEFAULT );
    Delay_ms( 1000 );
    glcd_clear( &glcd );

    glcd_point_t p[ 10 ] = {
        { 10, 10 }, { 20, 20 }, { 30, 30 }, { 40, 40 },
        { 50, 50 }, { 60, 60 }, { 70, 70 }, { 80, 80 },
        { 90, 90 }, { 100,100 }
    };
    glcd_rect_t r2[ 10 ] = {
        { 10, 20, 2, false, false },
        { 20, 30, 2, false, false },
        { 30, 40, 2, false, false },
        { 40, 50, 2, false, false },
        { 50, 60, 2, false, false },
        { 60, 70, 2, false, false },
        { 70, 80, 2, false, false },
        { 80, 90, 2, false, false },
        { 90, 100, 2, false, false },
        { 100, 110, 2, false, false }
    };
    for ( uint8_t i = 0; i < 10; i++ ) {
        glcd_draw_rect( &glcd, &p[ i ], 1, &r2[ i ], 1 );
        Delay_ms( 1000 );
        glcd_clear( &glcd );
    }

    glcd_circle_t c2[ 10 ] = {
        { { 64, 32 }, 10, 2, true },
        { { 64, 32 }, 15, 2, false },
        { { 64, 32 }, 20, 2, true },
        { { 64, 32 }, 25, 2, false },
        { { 64, 32 }, 30, 2, true },
        { { 64, 32 }, 35, 2, false },
        { { 64, 32 }, 40, 2, false },
        { { 64, 32 }, 45, 2, false },
        { { 64, 32 }, 50, 2, false },
        { { 64, 32 }, 55, 2, false }
    };
    for ( uint8_t i = 0; i < 10; i++ ) {
        glcd_draw_circle( &glcd, &c2[ i ], 1, GLCD_DEFAULT );
        Delay_ms( 500 );
        glcd_clear( &glcd );
    }

    glcd_ellipse_t e2[ 10 ] = {
        { { { 64, 32 }, { 100, 32 } }, 20.0f, 2, true },
        { { { 64, 32 }, { 100, 32 } }, 25.0f, 2, false },
        { { { 64, 32 }, { 100, 32 } }, 30.0f, 2, true },
        { { { 64, 32 }, { 100, 32 } }, 35.0f, 2, false },
        { { { 64, 32 }, { 100, 32 } }, 40.0f, 2, false },
        { { { 64, 32 }, { 100, 32 } }, 45.0f, 2, false },
        { { { 64, 32 }, { 100, 32 } }, 50.0f, 2, false },
        { { { 64, 32 }, { 100, 32 } }, 55.0f, 2, false },
        { { { 64, 32 }, { 100, 32 } }, 60.0f, 2, false },
        { { { 64, 32 }, { 100, 32 } }, 65.0f, 2, false }
    };
    for ( uint8_t i = 0; i < 10; i++ ) {
        glcd_draw_ellipse( &glcd, &e2[ i ], 1, GLCD_DEFAULT );
        Delay_ms( 500 );
        glcd_clear( &glcd );
    }
}

static void test3( void )
{
    glcd_point_t p = { 10, 10 };
    glcd_write_char( &glcd, &p, 'M' );
    Delay_ms( 500 );
    p.x += 8; // Move to next character position
    glcd_write_char( &glcd, &p, 'I' );
    Delay_ms( 500 );
    p.x += 8; // Move to next character position
    glcd_write_char( &glcd, &p, 'K' );
    Delay_ms( 500 );
    p.x += 8; // Move to next character position
    glcd_write_char( &glcd, &p, 'R' );
    Delay_ms( 500 );
    p.x += 8; // Move to next character position
    glcd_write_char( &glcd, &p, 'O' );
    Delay_ms( 500 );
    p.x += 8; // Move to next character position
    glcd_write_char( &glcd, &p, 'E' );
    Delay_ms( 500 );

    const char* text = "Hello GLCD!";
    p.x = 10; // Reset x position
    p.y += 16; // Move to next line
    glcd_write_text( &glcd, &p, text );
    Delay_ms( 2500 );
    glcd_clear( &glcd );
}

// ----------------------------------------------------------------------- END
