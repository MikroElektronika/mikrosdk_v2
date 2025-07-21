// ------------------------------------------------------------------ INCLUDES

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "glcd.h"

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

int main(void)
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    while (1)
    {
        // Run the first test to initialize GLCD and display some patterns.
        test1();

        // Run the second test to draw circles and ellipses.
        test2();

        // Run the third test to write characters and text on GLCD.
        test3();

        // Add a delay or break condition if needed.
        Delay_ms(1000);
    }
    return 0;
}

static void test1( void )
{
    glcd_t glcd;
    GLCD_Init(&glcd);
    GLCD_Display(&glcd, ON);
    GLCD_Clear(&glcd);

    point pts[] = { {10, 10}, {20, 20}, {30, 30} };
    GLCD_Draw_Dots(&glcd, pts, sizeof(pts) / sizeof(pts[0]), 2);
    Delay_ms(1000);
    GLCD_Clear(&glcd);

    segment s = { {{10, 10}, {50, 50}}, 2 };
    GLCD_Draw_Line(&glcd, &s, 1, DIAGONAL);
    Delay_ms(1000);
    GLCD_Clear(&glcd);
}

static void test2( void )
{
    glcd_t glcd;
    GLCD_Init(&glcd);
    GLCD_Display(&glcd, ON);
    GLCD_Clear(&glcd);

    circle c = { {64, 32}, 20, 2, true };
    GLCD_Draw_Circle(&glcd, &c, 1, DEFAULT);
    Delay_ms(1000);
    GLCD_Clear(&glcd);

    ellipse e = { {{64, 32}, {80, 32}}, 30.0f, 2, true };
    GLCD_Draw_Ellipse(&glcd, &e, 1, DEFAULT);
    Delay_ms(1000);
    GLCD_Clear(&glcd);

    circle c2[10] = {
        { {64, 32}, 10, 2, true },
        { {64, 32}, 15, 2, false },
        { {64, 32}, 20, 2, true },
        { {64, 32}, 25, 2, false },
        { {64, 32}, 30, 2, true },
        { {64, 32}, 35, 2, false },
        { {64, 32}, 40, 2, true },
        { {64, 32}, 45, 2, false },
        { {64, 32}, 50, 2, true },
        { {64, 32}, 55, 2, false }
    };
    for (uint8_t i = 0; i < 10; i++) {
        GLCD_Draw_Circle(&glcd, &c2[i], 1, DEFAULT);
        Delay_ms(500);
        GLCD_Clear(&glcd);
    }

    ellipse e2[10] = {
        { {{64, 32}, {100, 32}}, 20.0f, 2, true },
        { {{64, 32}, {100, 32}}, 25.0f, 2, false },
        { {{64, 32}, {100, 32}}, 30.0f, 2, true },
        { {{64, 32}, {100, 32}}, 35.0f, 2, false },
        { {{64, 32}, {100, 32}}, 40.0f, 2, true },
        { {{64, 32}, {100, 32}}, 45.0f, 2, false },
        { {{64, 32}, {100, 32}}, 50.0f, 2, true },
        { {{64, 32}, {100, 32}}, 55.0f, 2, false },
        { {{64, 32}, {100, 32}}, 60.0f, 2, true },
        { {{64, 32}, {100, 32}}, 65.0f, 2, false }
    };
    for (uint8_t i = 0; i < 10; i++) {
        GLCD_Draw_Ellipse(&glcd, &e2[i], 1, DEFAULT);
        Delay_ms(500);
        GLCD_Clear(&glcd);
    }
}

static void test3( void )
{
    glcd_t glcd;
    GLCD_Init(&glcd);
    GLCD_Display(&glcd, ON);
    GLCD_Clear(&glcd);

    point p = { 10, 10 };
    GLCD_Write_Char(&glcd, &p, 'A');
    p.x += 8; // Move to next character position
    GLCD_Write_Char(&glcd, &p, 'B');
    p.x += 8; // Move to next character position
    GLCD_Write_Char(&glcd, &p, 'C');

    const char* text = "Hello GLCD!";
    p.x = 10; // Reset x position
    p.y += 16; // Move to next line
    GLCD_Write_Text(&glcd, &p, text);
}

// ----------------------------------------------------------------------- END
