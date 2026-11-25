/* Compares the STM32 driver's register map with ST's (see stm32_regmap.h). */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

extern const uint32_t regmap_ours[];
extern const uint32_t regmap_st[];
extern const char *const regmap_names[];
extern const size_t regmap_count;

int main( void )
{
    int failures = 0;
    for ( size_t i = 0; i < regmap_count; i++ )
    {
        if ( regmap_ours[ i ] != regmap_st[ i ] )
        {
            failures++;
            printf( "FAIL %s: driver 0x%08X, ST 0x%08X\n", regmap_names[ i ], ( unsigned )regmap_ours[ i ],
                    ( unsigned )regmap_st[ i ] );
        }
    }
    printf( "RESULT %s (%zu values compared with ST's header, %d differ)\n", failures ? "FAIL" : "PASS",
            regmap_count, failures );
    return failures ? 1 : 0;
}
