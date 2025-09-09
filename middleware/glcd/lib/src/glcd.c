#include "glcd.h"

static const uint8_t bitmap_space[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // ' '
static const uint8_t bitmap_exclamation[8] = { 0x08, 0x08, 0x08, 0x08, 0x00, 0x08, 0x00, 0x00 }; // '!'
static const uint8_t bitmap_quotedbl[8] = { 0x28, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // '"'
static const uint8_t bitmap_hash[8] = { 0x28, 0x7C, 0x28, 0x7C, 0x28, 0x00, 0x00, 0x00 }; // '#'
static const uint8_t bitmap_dollar[8] = { 0x08, 0x1E, 0x28, 0x1C, 0x0A, 0x3C, 0x08, 0x00 }; // '$'
static const uint8_t bitmap_percent[8] = { 0x60, 0x94, 0x68, 0x16, 0x29, 0x06, 0x00, 0x00 }; // '%'
static const uint8_t bitmap_ampersand[8] = { 0x1C, 0x20, 0x20, 0x19, 0x26, 0x19, 0x00, 0x00 }; // '&'
static const uint8_t bitmap_apostrophe[8] = { 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // '\'
static const uint8_t bitmap_parenleft[8] = { 0x08, 0x10, 0x20, 0x20, 0x10, 0x08, 0x00, 0x00 }; // '('
static const uint8_t bitmap_parenright[8] = { 0x10, 0x08, 0x04, 0x04, 0x08, 0x10, 0x00, 0x00 }; // ')'
static const uint8_t bitmap_asterisk[8] = { 0x2A, 0x1C, 0x3E, 0x1C, 0x2A, 0x00, 0x00, 0x00 }; // '*'
static const uint8_t bitmap_plus[8] = { 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00, 0x00, 0x00 }; // '+'
static const uint8_t bitmap_comma[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x00, 0x00 }; // ','
static const uint8_t bitmap_minus[8] = { 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // '-'
static const uint8_t bitmap_period[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00 }; // '.'
static const uint8_t bitmap_slash[8] = { 0x20, 0x40, 0x81, 0x02, 0x04, 0x00, 0x00, 0x00 }; // '/'
static const uint8_t bitmap_0[8] = { 0x18, 0x24, 0x42, 0x42, 0x24, 0x18, 0x00, 0x00 }; // '0'
static const uint8_t bitmap_1[8] = { 0x08, 0x18, 0x08, 0x08, 0x08, 0x1C, 0x00, 0x00 }; // '1'
static const uint8_t bitmap_2[8] = { 0x3C, 0x42, 0x04, 0x18, 0x20, 0x7E, 0x00, 0x00 }; // '2'
static const uint8_t bitmap_3[8] = { 0x3C, 0x42, 0x04, 0x18, 0x42, 0x3C, 0x00, 0x00 }; // '3'
static const uint8_t bitmap_4[8] = { 0x08, 0x18, 0x28, 0x48, 0x7C, 0x08, 0x00, 0x00 }; // '4'
static const uint8_t bitmap_5[8] = { 0x7E, 0x40, 0x7C, 0x02, 0x42, 0x3C, 0x00, 0x00 }; // '5'
static const uint8_t bitmap_6[8] = { 0x3C, 0x40, 0x7C, 0x42, 0x42, 0x3C, 0x00, 0x00 }; // '6'
static const uint8_t bitmap_7[8] = { 0x7E, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00, 0x00 }; // '7'
static const uint8_t bitmap_8[8] = { 0x3C, 0x42, 0x3C, 0x42, 0x42, 0x3C, 0x00, 0x00 }; // '8'
static const uint8_t bitmap_9[8] = { 0x3C, 0x42, 0x42, 0x3E, 0x02, 0x3C, 0x00, 0x00 }; // '9'
static const uint8_t bitmap_colon[8] = { 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00 }; // ':'
static const uint8_t bitmap_semicolon[8] = { 0x00, 0x00, 0x00, 0x08, 0x00, 0x01, 0x00, 0x00 }; // ';'
static const uint8_t bitmap_less[8] = { 0x06, 0x18, 0x60, 0x18, 0x06, 0x00, 0x00, 0x00 }; // '<'
static const uint8_t bitmap_equal[8] = { 0x00, 0x7E, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00 }; // '='
static const uint8_t bitmap_greater[8] = { 0x60, 0x18, 0x06, 0x18, 0x60, 0x00, 0x00, 0x00 }; // '>'
static const uint8_t bitmap_question[8] = { 0x38, 0x44, 0x04, 0x18, 0x00, 0x10, 0x00, 0x00 }; // '?'
static const uint8_t bitmap_at[8] = { 0x3C, 0x44, 0x9C, 0x94, 0x5C, 0x20, 0x1C, 0x00 }; // '@'
static const uint8_t bitmap_A[8] = { 0x18, 0x18, 0x24, 0x3C, 0x42, 0x42, 0x00, 0x00 }; // 'A'
static const uint8_t bitmap_B[8] = { 0x78, 0x44, 0x78, 0x44, 0x44, 0x78, 0x00, 0x00 }; // 'B'
static const uint8_t bitmap_C[8] = { 0x38, 0x44, 0x80, 0x80, 0x44, 0x38, 0x00, 0x00 }; // 'C'
static const uint8_t bitmap_D[8] = { 0x78, 0x44, 0x44, 0x44, 0x44, 0x78, 0x00, 0x00 }; // 'D'
static const uint8_t bitmap_E[8] = { 0x7C, 0x40, 0x78, 0x40, 0x40, 0x7C, 0x00, 0x00 }; // 'E'
static const uint8_t bitmap_F[8] = { 0x7C, 0x40, 0x78, 0x40, 0x40, 0x40, 0x00, 0x00 }; // 'F'
static const uint8_t bitmap_G[8] = { 0x38, 0x44, 0x80, 0x9C, 0x44, 0x38, 0x00, 0x00 }; // 'G'
static const uint8_t bitmap_H[8] = { 0x42, 0x42, 0x7E, 0x42, 0x42, 0x42, 0x00, 0x00 }; // 'H'
static const uint8_t bitmap_I[8] = { 0x3E, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00 }; // 'I'
static const uint8_t bitmap_J[8] = { 0x1C, 0x04, 0x04, 0x04, 0x44, 0x38, 0x00, 0x00 }; // 'J'
static const uint8_t bitmap_K[8] = { 0x44, 0x48, 0x50, 0x70, 0x48, 0x44, 0x00, 0x00 }; // 'K'
static const uint8_t bitmap_L[8] = { 0x40, 0x40, 0x40, 0x40, 0x40, 0x7E, 0x00, 0x00 }; // 'L'
static const uint8_t bitmap_M[8] = { 0x41, 0x63, 0x55, 0x49, 0x41, 0x41, 0x00, 0x00 }; // 'M'
static const uint8_t bitmap_N[8] = { 0x42, 0x62, 0x52, 0x4A, 0x46, 0x42, 0x00, 0x00 }; // 'N'
static const uint8_t bitmap_O[8] = { 0x1C, 0x22, 0x22, 0x22, 0x22, 0x1C, 0x00, 0x00 }; // 'O'
static const uint8_t bitmap_P[8] = { 0x78, 0x44, 0x78, 0x40, 0x40, 0x40, 0x00, 0x00 }; // 'P'
static const uint8_t bitmap_Q[8] = { 0x1C, 0x22, 0x22, 0x22, 0x22, 0x1C, 0x02, 0x00 }; // 'Q'
static const uint8_t bitmap_R[8] = { 0x78, 0x44, 0x78, 0x50, 0x48, 0x44, 0x00, 0x00 }; // 'R'
static const uint8_t bitmap_S[8] = { 0x1C, 0x22, 0x10, 0x0C, 0x22, 0x1C, 0x00, 0x00 }; // 'S'
static const uint8_t bitmap_T[8] = { 0x7F, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00 }; // 'T'
static const uint8_t bitmap_U[8] = { 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00 }; // 'U'
static const uint8_t bitmap_V[8] = { 0x81, 0x42, 0x42, 0x24, 0x24, 0x18, 0x00, 0x00 }; // 'V'
static const uint8_t bitmap_W[8] = { 0x41, 0x41, 0x49, 0x55, 0x63, 0x41, 0x00, 0x00 }; // 'W'
static const uint8_t bitmap_X[8] = { 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x00, 0x00 }; // 'X'
static const uint8_t bitmap_Y[8] = { 0x41, 0x22, 0x14, 0x08, 0x08, 0x08, 0x00, 0x00 }; // 'Y'
static const uint8_t bitmap_Z[8] = { 0x7E, 0x04, 0x08, 0x10, 0x20, 0x7E, 0x00, 0x00 }; // 'Z'
static const uint8_t bitmap_bracket_left[8] = { 0x38, 0x20, 0x20, 0x20, 0x20, 0x38, 0x00, 0x00 }; // '['
static const uint8_t bitmap_backslash[8] = { 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00 }; // '\'
static const uint8_t bitmap_bracket_right[8] = { 0x38, 0x08, 0x08, 0x08, 0x08, 0x38, 0x00, 0x00 }; // ']'
static const uint8_t bitmap_caret[8] = { 0x10, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // '^'
static const uint8_t bitmap_underscore[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00 }; // '_'
static const uint8_t bitmap_grave[8] = { 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // '`'
static const uint8_t bitmap_a[8] = { 0x00, 0x3C, 0x02, 0x3E, 0x46, 0x3A, 0x00, 0x00 }; // 'a'
static const uint8_t bitmap_b[8] = { 0x40, 0x40, 0x7C, 0x42, 0x62, 0x5C, 0x00, 0x00 }; // 'b'
static const uint8_t bitmap_c[8] = { 0x00, 0x1C, 0x20, 0x20, 0x1C, 0x00, 0x00, 0x00 }; // 'c'
static const uint8_t bitmap_d[8] = { 0x00, 0x08, 0x08, 0x08, 0x38, 0x48, 0x38, 0x00 }; // 'd'
static const uint8_t bitmap_e[8] = { 0x00, 0x3C, 0x42, 0x7E, 0x40, 0x3C, 0x00, 0x00 }; // 'e'
static const uint8_t bitmap_f[8] = { 0x00, 0x18, 0x10, 0x38, 0x10, 0x10, 0x00, 0x00 }; // 'f'
static const uint8_t bitmap_g[8] = { 0x00, 0x34, 0x4C, 0x44, 0x34, 0x04, 0x38, 0x00 }; // 'g'
static const uint8_t bitmap_h[8] = { 0x20, 0x20, 0x38, 0x24, 0x24, 0x24, 0x00, 0x00 }; // 'h'
static const uint8_t bitmap_i[8] = { 0x00, 0x08, 0x00, 0x18, 0x08, 0x08, 0x08, 0x00 }; // 'i'
static const uint8_t bitmap_j[8] = { 0x00, 0x08, 0x00, 0x18, 0x08, 0x28, 0x38, 0x00 }; // 'j'
static const uint8_t bitmap_k[8] = { 0x20, 0x20, 0x24, 0x28, 0x30, 0x2C, 0x00, 0x00 }; // 'k'
static const uint8_t bitmap_l[8] = { 0x10, 0x10, 0x10, 0x10, 0x10, 0x18, 0x00, 0x00 }; // 'l'
static const uint8_t bitmap_m[8] = { 0x00, 0x66, 0x5A, 0x42, 0x42, 0x00, 0x00, 0x00 }; // 'm'
static const uint8_t bitmap_n[8] = { 0x00, 0x2E, 0x32, 0x22, 0x22, 0x00, 0x00, 0x00 }; // 'n'
static const uint8_t bitmap_o[8] = { 0x00, 0x3C, 0x42, 0x42, 0x3C, 0x00, 0x00, 0x00 }; // 'o'
static const uint8_t bitmap_p[8] = { 0x00, 0x5C, 0x62, 0x42, 0x7C, 0x40, 0x40, 0x00 }; // 'p'
static const uint8_t bitmap_q[8] = { 0x00, 0x3A, 0x46, 0x42, 0x3E, 0x02, 0x02, 0x00 }; // 'q'
static const uint8_t bitmap_r[8] = { 0x00, 0x2C, 0x32, 0x20, 0x20, 0x00, 0x00, 0x00 }; // 'r'
static const uint8_t bitmap_s[8] = { 0x00, 0x1C, 0x20, 0x18, 0x04, 0x38, 0x00, 0x00 }; // 's'
static const uint8_t bitmap_t[8] = { 0x00, 0x10, 0x3C, 0x10, 0x10, 0x18, 0x00, 0x00 }; // 't'
static const uint8_t bitmap_u[8] = { 0x00, 0x22, 0x22, 0x26, 0x1A, 0x00, 0x00, 0x00 }; // 'u'
static const uint8_t bitmap_v[8] = { 0x00, 0x42, 0x42, 0x24, 0x18, 0x00, 0x00, 0x00 }; // 'v'
static const uint8_t bitmap_w[8] = { 0x00, 0x81, 0x81, 0x5A, 0x66, 0x00, 0x00, 0x00 }; // 'w'
static const uint8_t bitmap_x[8] = { 0x00, 0x42, 0x24, 0x18, 0x66, 0x00, 0x00, 0x00 }; // 'x'
static const uint8_t bitmap_y[8] = { 0x00, 0x42, 0x21, 0x14, 0x08, 0x10, 0x60, 0x00 }; // 'y'
static const uint8_t bitmap_z[8] = { 0x00, 0x3C, 0x08, 0x10, 0x3C, 0x00, 0x00, 0x00 }; // 'z'
static const uint8_t bitmap_curly_brace_left[8] = { 0x1C, 0x10, 0x30, 0x30, 0x10, 0x1C, 0x00, 0x00 }; // '{'
static const uint8_t bitmap_pipe[8] = { 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00 }; // '|'
static const uint8_t bitmap_curly_brace_right[8] = { 0x38, 0x08, 0x0C, 0x0C, 0x08, 0x38, 0x00, 0x00 }; // '}'
static const uint8_t bitmap_tilde[8] = { 0x00, 0x00, 0x32, 0x4C, 0x00, 0x00, 0x00, 0x00 }; // '~'

const glcd_char_def_t font[] = {
    { ' ',  bitmap_space },                 // 0
    { '!',  bitmap_exclamation },     // 1
    { '"',  bitmap_quotedbl },     // 2
    { '#',  bitmap_hash },     // 3
    { '$',  bitmap_dollar },     // 4
    { '%',  bitmap_percent },     // 5
    { '&',  bitmap_ampersand },     // 6
    { '\'', bitmap_apostrophe },     // 7
    { '(',  bitmap_parenleft },     // 8
    { ')',  bitmap_parenright },     // 9
    { '*',  bitmap_asterisk },     // 10
    { '+',  bitmap_plus },     // 11
    { ',',  bitmap_comma },     // 12
    { '-',  bitmap_minus },     // 13
    { '.',  bitmap_period },     // 14
    { '/',  bitmap_slash },     // 15
    { '0',  bitmap_0 },     // 16
    { '1',  bitmap_1 },     // 17
    { '2',  bitmap_2 },     // 18
    { '3',  bitmap_3 },     // 19
    { '4',  bitmap_4 },     // 20
    { '5',  bitmap_5 },     // 21
    { '6',  bitmap_6 },     // 22
    { '7',  bitmap_7 },     // 23
    { '8',  bitmap_8 },     // 24
    { '9',  bitmap_9 },     // 25
    { ':',  bitmap_colon },     // 26
    { ';',  bitmap_semicolon },     // 27
    { '<',  bitmap_less },     // 28
    { '=',  bitmap_equal },     // 29
    { '>',  bitmap_greater },     // 30
    { '?',  bitmap_question },     // 31
    { '@',  bitmap_at },     // 32
    { 'A',  bitmap_A },     // 33
    { 'B',  bitmap_B },     // 34
    { 'C',  bitmap_C },     // 35
    { 'D',  bitmap_D },     // 36
    { 'E',  bitmap_E },     // 37
    { 'F',  bitmap_F },     // 38
    { 'G',  bitmap_G },     // 39
    { 'H',  bitmap_H },     // 40
    { 'I',  bitmap_I },     // 41
    { 'J',  bitmap_J },     // 42
    { 'K',  bitmap_K },     // 43
    { 'L',  bitmap_L },     // 44
    { 'M',  bitmap_M },     // 45
    { 'N',  bitmap_N },     // 46
    { 'O',  bitmap_O },     // 47
    { 'P',  bitmap_P },     // 48
    { 'Q',  bitmap_Q },     // 49
    { 'R',  bitmap_R },     // 50
    { 'S',  bitmap_S },     // 51
    { 'T',  bitmap_T },     // 52
    { 'U',  bitmap_U },     // 53
    { 'V',  bitmap_V },     // 54
    { 'W',  bitmap_W },     // 55
    { 'X',  bitmap_X },     // 56
    { 'Y',  bitmap_Y },     // 57
    { 'Z',  bitmap_Z },     // 58
    { '[',  bitmap_curly_brace_left },     // 59
    { '\\', bitmap_backslash },     // 60
    { ']',  bitmap_curly_brace_right },     // 61
    { '^',  bitmap_caret },     // 62
    { '_',  bitmap_underscore },     // 63
    { '`',  bitmap_grave },     // 64
    { 'a',  bitmap_a },     // 65
    { 'b',  bitmap_b },     // 66
    { 'c',  bitmap_c },     // 67
    { 'd',  bitmap_d },     // 68
    { 'e',  bitmap_e },     // 69
    { 'f',  bitmap_f },     // 70
    { 'g',  bitmap_g },     // 71
    { 'h',  bitmap_h },     // 72
    { 'i',  bitmap_i },     // 73
    { 'j',  bitmap_j },     // 74
    { 'k',  bitmap_k },     // 75
    { 'l',  bitmap_l },     // 76
    { 'm',  bitmap_m },     // 77
    { 'n',  bitmap_n },     // 78
    { 'o',  bitmap_o },     // 79
    { 'p',  bitmap_p },     // 80
    { 'q',  bitmap_q },     // 81
    { 'r',  bitmap_r },     // 82
    { 's',  bitmap_s },     // 83
    { 't',  bitmap_t },     // 84
    { 'u',  bitmap_u },     // 85
    { 'v',  bitmap_v },     // 86
    { 'w',  bitmap_w },     // 87
    { 'x',  bitmap_x },     // 88
    { 'y',  bitmap_y },     // 89
    { 'z',  bitmap_z },     // 90
    { '{',  bitmap_curly_brace_left },     // 91
    { '|',  bitmap_pipe },     // 92
    { '}',  bitmap_curly_brace_right },     // 93
    { '~',  bitmap_tilde },     // 94
};

void glcd_port_init( glcd_t* glcd )
{
    port_init( &glcd->data_out, glcd->config.data_out,
               glcd->config.data_out_mask, HAL_LL_GPIO_DIGITAL_OUTPUT );
    digital_out_init( &glcd->cs1d, glcd->config.GLCD_CS1_PIN );
    digital_out_init( &glcd->cs2d, glcd->config.GLCD_CS2_PIN );
    digital_out_init( &glcd->ed, glcd->config.GLCD_E_PIN );
    digital_out_init( &glcd->resetd, glcd->config.GLCD_RESET_PIN );
    digital_out_init( &glcd->rsd, glcd->config.GLCD_RS_PIN );
    digital_out_init( &glcd->rwd, glcd->config.GLCD_RW_PIN );
}

void glcd_init( glcd_t* glcd )
{
    glcd_port_init( glcd );

    digital_out_high( &glcd->ed );
    digital_out_high( &glcd->cs1d );
    digital_out_high( &glcd->cs2d );
    digital_out_high( &glcd->resetd );
    digital_out_low( &glcd->rsd );
    digital_out_high( &glcd->rwd );
    glcd_apply_changes( glcd );
}

void glcd_set_page( glcd_t* glcd, uint8_t page )
{
    if ( !glcd || page > 7 ) return;

    digital_out_low( &glcd->rsd ); // RS = 0 ( instruction )
    digital_out_low( &glcd->rwd ); // RW = 0 ( write )

    // We only care about the lower 3 bits for page address
    if ( 0xFF00 == glcd->config.data_out_mask ) {
        port_write( &glcd->data_out, ( 0xB8 | ( page & 0x07 )) << 8 );
    } else if ( 0xFF == glcd->config.data_out_mask ) {
        port_write( &glcd->data_out, ( 0xB8 | ( page & 0x07 )) );
    }

    glcd_apply_changes( glcd );
}

void glcd_set_y( glcd_t* glcd, uint8_t y_pos )
{
    if ( !glcd || y_pos > 64 ) return;

    digital_out_low( &glcd->rsd ); // RS = 0 ( instruction )
    digital_out_low( &glcd->rwd ); // RW = 0 ( write )

    port_write( &glcd->data_out, ( 0x40 | ( y_pos & 0x3F )) );

    glcd_apply_changes( glcd );
}

void glcd_clear( glcd_t *glcd )
{
    if ( !glcd ) return;

    for ( uint8_t page = 0; page < PAGE_SIZE; page++ )
        for ( uint8_t col = 0; col <= ROW_SIZE; col++ )
            glcd_write( glcd, page, col, 0x00 );
}

void glcd_display( glcd_t* glcd, glcd_display_cfg_t turn_on_off )
{
    if ( !glcd || ( turn_on_off != GLCD_DISPLAY_ON && turn_on_off != GLCD_DISPLAY_OFF ) ) {
        return;
    }

    for ( uint8_t k = 0; k < 2; k++ )
    {
        glcd_cs_config( glcd, k%2, ( k+1 )%2 );

        digital_out_low( &glcd->rsd ); // RS = 0 ( instruction )
        digital_out_low( &glcd->rwd ); // RW = 0 ( write )

        port_write( &glcd->data_out, turn_on_off );
        glcd_apply_changes( glcd );
    }
}

void glcd_apply_changes( glcd_t* glcd )
{
    digital_out_high( &glcd->ed );
    Delay_us( 10 );
    digital_out_low( &glcd->ed );
    Delay_us( 10 );
}

void glcd_cs_config( glcd_t* glcd, bool cs1, bool cs2 )
{
    if ( !glcd ) return;
    digital_out_write( &glcd->cs1d, ( cs1 == 1 ) ? 0 : 1 );
    digital_out_write( &glcd->cs2d, ( cs2 == 1 ) ? 0 : 1 );
}

/* -------------------------- Read and Write functions -------------------------- */
uint8_t glcd_read( glcd_t* glcd, uint8_t page, uint8_t column )
{
    if ( !glcd || page >= PAGE_SIZE || column >= ROW_SIZE ) return 0;

    uint8_t chip = ( column < 64 ) ? 0 : 1;
    uint8_t col_in_chip = column % 64;
    return glcd->buffer[chip][page][col_in_chip];
}

void glcd_write( glcd_t *glcd, uint8_t page, uint8_t line, uint8_t data_to_write )
{
    if ( !glcd || page > PAGE_SIZE || line > ROW_SIZE ) return;

    if ( line < 64 )
    {
        glcd_cs_config( glcd, 1, 0 );
        glcd_set_y( glcd, line );
        glcd_set_page( glcd, page );
    }
    else
    {
        glcd_cs_config( glcd, 0, 1 );
        glcd_set_y( glcd, line-64 );
        glcd_set_page( glcd, page );
    }
    digital_out_low( &glcd->ed );
    digital_out_high( &glcd->rsd );
    digital_out_low( &glcd->rwd );
    port_write( &glcd->data_out, data_to_write );
    glcd_apply_changes( glcd );

    glcd->buffer[( line < 64 ) ? 0 : 1][page][line % 64] = data_to_write;
}

void glcd_write_char( glcd_t* glcd, glcd_point_t* p, char c )
{
    uint8_t page = p->y / 8;
    uint8_t line = p->x % 128;
    uint64_t res = glcd_transpose_word( glcd_find_matching_char_from_bitmap( c ));

    for ( uint8_t i = 0; i < 8; i++ )
    {
        uint8_t byte = ( res >> ( 8 * ( 7 - i )) ) & 0xFF;
        byte = glcd_reverse_byte( byte );
        glcd_write( glcd, page, line + i, byte );
    }
}

void glcd_write_text( glcd_t* glcd, glcd_point_t* p, const char* c )
{
    if ( !glcd || !p || !c ) return;

    glcd_point_t pos = *p;
    size_t len = strlen( c );
    for ( size_t i = 0; i < len; i++ )
    {
        glcd_write_char( glcd, &pos, c[i] );
        pos.x += 8;

        if ( pos.x >= 128 ) {
            pos.x = 0;
            pos.y += 8;
            if ( pos.y >= 64 ) break;
        }
    }
}

/* ----------------------------- Drawing functions ----------------------------- */
void glcd_fill_screen( glcd_t* glcd, uint8_t pattern )
{
    if ( !glcd ) return;

    for ( uint8_t page = 0; page < PAGE_SIZE; page++ )
        for ( uint8_t col = 0; col <= ROW_SIZE; col++ )
            glcd_write( glcd, page, col, pattern );
}

void glcd_draw_dots( glcd_t* glcd, const glcd_point_t* pts,
                     uint8_t size, uint8_t dot_size )
{
    if ( !glcd || !pts || dot_size == 0 || dot_size > 8 ) {
        return;
    }

    for ( uint8_t i = 0; i < size; i++ )
    {
        uint8_t x = pts[i].x;
        uint8_t y = pts[i].y;

        if ( x >= 128 || y >= 64 ) continue;

        uint8_t page = y / 8;
        uint8_t y_offset = y % 8;

        for ( uint8_t dx = 0; dx < dot_size; dx++ )
        {
            if ( x + dx >= 128 ) continue;
            for ( uint8_t dy = 0; dy < dot_size; dy++ )
            {
                uint8_t current_y = y + dy;
                if ( current_y >= 64 ) continue;

                uint8_t current_page = current_y / 8;
                uint8_t bit_in_page = current_y % 8;

                uint8_t prev = glcd_read( glcd, current_page, x + dx );
                prev |= ( 1 << bit_in_page );
                glcd_write( glcd, current_page, x + dx, prev );
            }
        }
    }
}

void glcd_draw_line( glcd_t* glcd, const glcd_segment_t* s, uint8_t s_size,
                     glcd_line_dir_t direction )
{
    if ( !glcd || !s ) return;

    for ( uint8_t i = 0; i < s_size; i++ )
    {
        glcd_point_t p0 = s[i].pts[0], p1 = s[i].pts[1];
        uint8_t thickness = s[i].line_size;

        if ( p0.x >= 128 || p1.x >= 128 || p0.y >= 64 || p1.y >= 64 ||
            p0.x < 0 || p1.x < 0 || p0.y < 0 || p1.y < 0 )
            continue;

        switch ( direction )
        {
            case GLCD_VERTICAL_LINE:
            {
                if ( p0.x != p1.x ) break;
                int x = p0.x;
                int y0 = ( p0.y < p1.y ) ? p0.y : p1.y;
                int y1 = ( p0.y > p1.y ) ? p0.y : p1.y;

                for ( int y = y0; y <= y1 && y < 64; y++ )
                {
                    for ( uint8_t dx = 0; dx < thickness; dx++ )
                    {
                        int cx = x + dx;
                        if ( cx >= 128 ) continue;

                        uint8_t page = y / 8;
                        uint8_t bit_in_page = 1 << ( y % 8 );
                        uint8_t val = glcd_read( glcd, page, cx );
                        glcd_write( glcd, page, cx, val | bit_in_page );
                    }
                }
                break;
            }

            case GLCD_HORIZONTAL_LINE:
            {
                if ( p0.y != p1.y ) break;
                int y = p0.y;
                int x0 = ( p0.x < p1.x ) ? p0.x : p1.x;
                int x1 = ( p0.x > p1.x ) ? p0.x : p1.x;

                for ( int x = x0; x <= x1 && x < 128; x++ )
                {
                    for ( uint8_t dy = 0; dy < thickness; dy++ )
                    {
                        int cy = y + dy;
                        if ( cy >= 64 ) continue;

                        uint8_t page = cy / 8;
                        uint8_t bit_in_page = 1 << ( cy % 8 );
                        uint8_t val = glcd_read( glcd, page, x );
                        glcd_write( glcd, page, x, val | bit_in_page );
                    }
                }
                break;
            }

            case GLCD_DIAGONAL:
            {
                int x0 = p0.x, y0 = p0.y;
                int x1 = p1.x, y1 = p1.y;
                int dx = abs( x1 - x0 ), dy = abs( y1 - y0 );
                int sx = ( x0 < x1 ) ? 1 : -1;
                int sy = ( y0 < y1 ) ? 1 : -1;
                int err = dx - dy;

                while ( 1 )
                {
                    for ( uint8_t dy_dot = 0; dy_dot < thickness; dy_dot++ )
                    {
                        for ( uint8_t dx_dot = 0; dx_dot < thickness; dx_dot++ )
                        {
                            int x = x0 + dx_dot;
                            int y = y0 + dy_dot;
                            if ( x < 0 || x >= 128 || y < 0 || y >= 64 ) continue;

                            uint8_t page = y / 8;
                            uint8_t bit_in_page = 1 << ( y % 8 );
                            uint8_t val = glcd_read( glcd, page, x );
                            glcd_write( glcd, page, x, val | bit_in_page );
                        }
                    }

                    if ( x0 == x1 && y0 == y1 ) break;

                    int e2 = 2 * err;
                    if ( e2 > -dy ) { err -= dy; x0 += sx; }
                    if ( e2 < dx )  { err += dx; y0 += sy; }
                }
                break;
            }
        }
    }
}

void glcd_draw_rect( glcd_t* glcd, const glcd_point_t* p, uint16_t psize,
                     const glcd_rect_t* r, uint16_t rsize )
{
    if ( !glcd || !r || !p || psize != rsize ) return;

    for ( uint16_t i=0; i<psize; i++ )
    {
        uint8_t x0 = p[i].x, y0 = p[i].y;
        uint8_t x1 = ( x0 + r[i].w ) % ROW_SIZE, y1 = ( y0 + r[i].h ) % COL_PER_CHIP;
        uint8_t line_sz = r[i].line_size;

        glcd_segment_t rect[4] = {
            {{{x0, y0},{x1, y0}}, line_sz},
            {{{x0, y0},{x0, y1}}, line_sz},
            {{{x1, y0},{x1, y1}}, line_sz},
            {{{x0, y1},{x1, y1}}, line_sz}
        };

        glcd_draw_line( glcd, rect, 4, GLCD_DIAGONAL );
        if ( r[i].filled ) {
            glcd_fill_polygon( glcd, rect, 4 );
        }
        if ( r[i].rounded ) {
            /*
             * TODO - This feature will be added in a future release.
             */
        }
    }
}

void glcd_draw_shape( glcd_t* glcd, const glcd_segment_t* edges, uint8_t size,
                      bool is_filled, bool round_edges )
{
    if ( !glcd || !edges ) return;

    glcd_segment_t output[64];
    glcd_sort_points_nearest_neighbor( edges, output, size );
    glcd_draw_line( glcd, output, size, GLCD_DIAGONAL );

    if ( is_filled ) {
        glcd_fill_polygon( glcd, output, output[0].line_size );
    }
    if ( round_edges ) {
        /*
         * TODO - This feature will be added in a future release.
         */
    }
}

void glcd_draw_regular_polygon( glcd_t* glcd, const glcd_point_t* ori,
                                uint8_t num_of_ori, const glcd_polygon_mode_t* pol,
                                uint8_t num_of_pol, bool is_filled )
{
    if ( !glcd || !ori || !pol || num_of_pol == 0 || num_of_ori == 0 ) {
        return;
    }

    uint8_t count = ( num_of_ori < num_of_pol ) ? num_of_ori : num_of_pol;
    for ( uint8_t p = 0; p < count; p++ )
    {
        uint8_t sides = pol[p];
        if ( sides < 3 || sides > 10 ) continue;

        glcd_point_t polygon_points[10];
        glcd_segment_t edges[10];

        for ( uint8_t i = 0; i < sides; i++ )
        {
            float angle = ( 2 * PI * i ) / sides;
            int16_t x = ori[p].x + ( int16_t )( 20 * cos( angle ));
            int16_t y = ori[p].y + ( int16_t )( 20 * sin( angle ));

            polygon_points[i].x = x;
            polygon_points[i].y = y ;
        }

        for ( uint8_t i = 0; i < sides; i++ )
        {
            edges[i].pts[0] = polygon_points[i];
            edges[i].pts[1] = polygon_points[( i + 1 ) % sides];
            edges[i].line_size = 2;
        }

        glcd_draw_line( glcd, edges, sides, GLCD_DIAGONAL );
        if ( is_filled ) glcd_fill_polygon( glcd, edges, sides );
    }
}

void glcd_draw_circle( glcd_t* glcd, const glcd_circle_t* c, uint16_t csize,
                       glcd_circle_mode_t precision )
{
    if ( !glcd || !c ) return;

    glcd_point_t circle_approx[5000];
    for ( uint16_t i = 0; i < csize; i++ )
    {
        uint8_t radius = c[i].radius, dot_size = c[i].line_thickness;
        glcd_point_t origin = c[i].center;

        for ( uint16_t j = 0; j < precision; j++ )
        {
            circle_approx[j].x = origin.x +
                                 ( int16_t )( radius * cos( ( 2 * PI * j ) / precision ));
            circle_approx[j].y = origin.y +
                                 ( int16_t )( radius * sin( (2 * PI * j ) / precision ));
        }

        for ( uint16_t j = 0; j < precision; j++ )
        {
            glcd_segment_t s = {
                {
                    {circle_approx[j].x, circle_approx[j].y},
                    {circle_approx[( j + 1 ) % precision].x,
                                   circle_approx[( j + 1 ) % precision].y}
                },
                dot_size
            };
            glcd_draw_line( glcd, &s, 1, GLCD_DIAGONAL );
        }
        if ( c[i].filled ) {
            glcd_fill_circle( glcd, circle_approx, precision, dot_size );
        }
    }
}

void glcd_draw_ellipse( glcd_t* glcd, const glcd_ellipse_t* e, uint16_t esize,
                        glcd_circle_mode_t precision )
{
    if ( !glcd || !e || esize == 0 || precision < 3 || precision > 5000 ) {
        return;
    }

    for ( uint16_t i = 0; i < esize; i++ )
    {
        float cx = e[i].mid_foci[0].x, cy = e[i].mid_foci[0].y;
        float fx = e[i].mid_foci[1].x, fy = e[i].mid_foci[1].y;
        float dx = fx - cx, dy = fy - cy;
        float c_val = sqrt( dx * dx + dy * dy );
        float a = e[i].a;
        if ( a <= c_val ) a = c_val + 5; // Ensure valid ellipse
        float b = sqrt( a * a - c_val * c_val );

        float theta_axis = atan2( dy, dx );
        uint8_t dot_size = e[i].line_size;
        bool is_filled = e[i].filled;

        glcd_point_t ellipse_points[5000];
        for ( uint16_t j = 0; j < precision; j++ )
        {
            float theta = ( 2.0f * PI * j ) / precision;
            float x_local = a * cos( theta );
            float y_local = b * sin( theta );
            float x_rot = x_local * cos( theta_axis ) - y_local * sin( theta_axis );
            float y_rot = x_local * sin( theta_axis ) + y_local * cos( theta_axis );
            float x = cx + x_rot;
            float y = cy + y_rot;

            ellipse_points[j].x = ( uint8_t )( x + 0.5f );
            ellipse_points[j].y = ( uint8_t )( y + 0.5f );
        }

        for ( uint16_t k = 0; k < precision; k++ )
        {
            glcd_segment_t s = {
                {
                    { ellipse_points[k].x, ellipse_points[k].y },
                    { ellipse_points[( k + 1 ) % precision].x,
                                     ellipse_points[( k + 1 ) % precision].y }
                },
                dot_size
            };
            glcd_draw_line( glcd, &s, 1, GLCD_DIAGONAL );
        }
        if ( is_filled ) {
            glcd_fill_circle( glcd, ellipse_points, precision, dot_size );
        }
    }
}
/*
void dvd_animation( glcd_t* glcd ) {}
*/

/* ----------------------------------- Utils ----------------------------------- */
float distance( glcd_point_t a, glcd_point_t b )
{
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return sqrt( dx * dx + dy * dy );
}

void glcd_sort_points_nearest_neighbor( const glcd_segment_t* input,
                                        glcd_segment_t* output, uint8_t size )
{
    if ( !input || !output || size == 0 ) return;

    bool visited[64] = { false };
    uint8_t current = 0;

    float min_dist = 1e9;
    for ( uint8_t i = 0; i < size; i++ )
    {
        float d = distance( (glcd_point_t ){0, 0}, input[i].pts[0] );
        if ( d < min_dist ) { min_dist = d; current = i; }
    }

    output[0] = input[current];
    visited[current] = true;

    for ( uint8_t i = 1; i < size; i++ )
    {
        float best_dist = 1e9;
        uint8_t next = 0;
        for ( uint8_t j = 0; j < size; j++ )
        {
            if ( !visited[j] )
            {
                float d = distance( output[i - 1].pts[1], input[j].pts[0] );
                if ( d < best_dist ) { best_dist = d; next = j; }
            }
        }
        output[i] = input[next];
        visited[next] = true;
    }
}

void glcd_fill_polygon( glcd_t* glcd, const glcd_segment_t* edges,
                        uint8_t size )
{
    if ( !glcd || !edges || size < 3 ) return;

    for ( uint8_t i = 0; i < size; i++ ) {
        if ( edges[i].line_size != edges[( i + 1 ) % size].line_size ) {
            return;
        }
    }
    uint8_t min_y = 255, max_y = 0, dot_size = edges[0].line_size;
    for ( uint8_t i = 0; i < size; i++ )
    {
        if ( edges[i].pts[0].y < min_y ) min_y = edges[i].pts[0].y;
        if ( edges[i].pts[0].y > max_y ) max_y = edges[i].pts[0].y;
        if ( edges[i].pts[1].y < min_y ) min_y = edges[i].pts[1].y;
        if ( edges[i].pts[1].y > max_y ) max_y = edges[i].pts[1].y;
    }

    glcd_segment_t sorted[64];
    glcd_sort_points_nearest_neighbor( edges, sorted, size );

    for ( uint8_t y = min_y; y <= max_y; y++ )
    {
        uint8_t x_intersections[64];
        uint8_t nb_x = 0;

        for ( uint8_t i = 0; i < size; i++ )
        {
            glcd_point_t p1 = sorted[i].pts[0], p2 = sorted[i].pts[1];
            if ( p1.y == p2.y ) continue;
            if ( p1.y > p2.y ) {
                glcd_point_t temp = p1;
                p1 = p2;
                p2 = temp;
            }

            if ( y >= p1.y && y < p2.y )
            {
                int16_t dx = p2.x - p1.x;
                int16_t dy = p2.y - p1.y;
                uint8_t x = p1.x + ( dx * ( y - p1.y )) / dy;
                if ( nb_x < 64 ) x_intersections[nb_x++] = x;
            }
        }

        // Bubble sorting
        for ( uint8_t i = 0; i < nb_x - 1; i++ )
        {
            for ( uint8_t j = 0; j < nb_x - i - 1; j++ )
            {
                if ( x_intersections[j] > x_intersections[j + 1] )
                {
                    uint8_t tmp = x_intersections[j];
                    x_intersections[j] = x_intersections[j + 1];
                    x_intersections[j + 1] = tmp;
                }
            }
        }

        for ( uint8_t i = 0; i + 1 < nb_x; i += 2 )
        {
            glcd_segment_t s = { { { x_intersections[i], y },
                                 { x_intersections[i + 1], y } }, dot_size };
            glcd_draw_line( glcd, &s, 1, GLCD_HORIZONTAL_LINE );
        }
    }
}

void glcd_fill_circle( glcd_t* glcd, const glcd_point_t* contour,
                       uint16_t precision, uint8_t dot_size )
{
    if ( !glcd || !contour || dot_size == 0 ) return;

    uint8_t min_y = 255, max_y = 0;
    for ( uint16_t i = 0; i < precision; i++ )
    {
        if ( contour[i].y < min_y ) min_y = contour[i].y;
        if ( contour[i].y > max_y ) max_y = contour[i].y;
    }

    for ( uint8_t y = min_y; y <= max_y; y++ )
    {
        uint8_t x_intersections[128];
        uint8_t count_x = 0;

        for ( uint16_t i = 0; i < precision; i++ )
        {
            glcd_point_t p1 = contour[i];
            glcd_point_t p2 = contour[( i + 1 ) % precision];

            if ( p1.y == p2.y ) continue;
            if ( p1.y > p2.y )
            {
                glcd_point_t tmp = p1;
                p1 = p2;
                p2 = tmp;
            }

            if ( y >= p1.y && y < p2.y )
            {
                float dx = p2.x - p1.x;
                float dy = p2.y - p1.y;
                float x = p1.x + dx * ( float )( y - p1.y ) / dy;
                if ( count_x < 128 )
                    x_intersections[count_x++] = ( uint8_t )( x + 0.5f );
            }
        }

        for ( uint8_t j = 0; j < count_x - 1; j++ )
        {
            for ( uint8_t k = 0; k < count_x - j - 1; k++ )
            {
                if ( x_intersections[k] > x_intersections[k + 1] )
                {
                    uint8_t temp = x_intersections[k];
                    x_intersections[k] = x_intersections[k + 1];
                    x_intersections[k + 1] = temp;
                }
            }
        }

        for ( uint8_t j = 0; j + 1 < count_x; j += 2 )
        {
            glcd_segment_t s = { {{ x_intersections[j], y },
                                  { x_intersections[j + 1], y }}, dot_size };
            glcd_draw_line( glcd, &s, 1, GLCD_DIAGONAL );
        }
    }
}

static int glcd_dot_product( glcd_point_t a, glcd_point_t b, glcd_point_t c )
{
    int ux = b.x - a.x;
    int uy = b.y - a.y;
    int vx = c.x - a.x;
    int vy = c.y - a.y;
    return ux * vx + uy * vy;
}

uint64_t glcd_transpose_word( uint64_t word )
{
    uint64_t result = 0;

    for ( uint8_t row = 0; row < 8; row++ )
        for ( uint8_t col = 0; col < 8; col++ )
            if ( word & ( 1ULL << ( col * 8 + row )) )
                result |= ( 1ULL << ( row * 8 + col ));

    return result;
}

uint64_t glcd_find_matching_char_from_bitmap( char c )
{
    uint8_t size = sizeof( font ) / sizeof( font[0] );
    for ( uint8_t i=0; i<size; i++ )
    {
        if ( c == font[i].c ) return font[i].bitmap_code;
        else continue;
    }
    return 0;
}

uint8_t glcd_reverse_byte( uint8_t b )
{
    b = ( b & 0xF0 ) >> 4 | ( b & 0x0F ) << 4;
    b = ( b & 0xCC ) >> 2 | ( b & 0x33 ) << 2;
    b = ( b & 0xAA ) >> 1 | ( b & 0x55 ) << 1;
    return b;
}