#include "${SCREEN_NAME}.h"
#include "scr_${SCREEN_NAME}.h"

static vtft_t *_vtft;

void ${SCREEN_NAME}_show(vtft_t *vtft)
{
    _vtft = vtft;
    if( !get_${SCREEN_NAME}_initialized() )
        initialize_${SCREEN_NAME}();

    vtft_set_current_screen(_vtft, ${SCREEN_NAME}.screen_data);
}
