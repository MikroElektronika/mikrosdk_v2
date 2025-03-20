#include "main_screen.h"
#include "scr_main_screen.h"

static vtft_t *_vtft;

void main_screen_show( vtft_t *vtft )
{
    _vtft = vtft;
    initialize_main_screen();
    
    vtft_set_current_screen( _vtft, main_screen.screen_data );
}
