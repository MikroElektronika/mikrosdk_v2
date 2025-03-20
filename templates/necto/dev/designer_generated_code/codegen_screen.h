#ifndef %2_H
#define %2_H


#include "vtft_types.h"

typedef struct {
%3
} %1_type;

extern void initialize_%1() ;
extern int get_%1_initialized() ;
extern %1_type %1; 
extern vtft_screen %1_data; 

#endif
