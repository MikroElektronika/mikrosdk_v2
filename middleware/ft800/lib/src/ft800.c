/****************************************************************************
**
** Copyright (C) ${COPYRIGHT_YEAR} MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is part of the mikroSDK package
**
** Commercial License Usage
**
** Licensees holding valid commercial NECTO compilers AI licenses may use this
** file in accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The MikroElektronika Company.
** For licensing terms and conditions see
** https://www.mikroe.com/legal/software-license-agreement.
** For further information use the contact form at
** https://www.mikroe.com/contact.
**
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used for
** non-commercial projects under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file  ft800.c
 * @brief FT800 controller source file.
 */

#include "ft800.h"
#include "ft800_cmd.h"
#include "ft800_reg.h"
#include <stdint.h>
#include <math.h>
//#include "drv_spi_master.h"


const ft800_controller_t FT800_CONTROLLER =
{
    {
        { 0x00, TP_EVENT_GEST_NONE },
        { 0x1C, TP_EVENT_GEST_LEFT },
        { 0x14, TP_EVENT_GEST_RIGHT },
        { 0x10, TP_EVENT_GEST_UP },
        { 0x18, TP_EVENT_GEST_DOWN },
        { 0x48, TP_EVENT_GEST_ZOOM_IN },
        { 0x49, TP_EVENT_GEST_ZOOM_OUT }
    }
};

void ft800_cfg_setup( ft800_cfg_t * cfg, const ft800_controller_t * controller )
{
    spi_master_select_device( cfg->cs_pin );
    cfg->in_pin    = HAL_PIN_NC;
    cfg->controller = controller;
}

void write_data( ft800_t *ctx,ft800_cfg_t *cfg, uint32_t addres, uint32_t value, uint8_t length ){
    uint8_t data[7];
    spi_master_select_device( cfg->cs_pin );
    if( length == 24 )
    {
        if( ( uint8_t )value == 0x00 )
        {
            uint8_t data[3];
            data[0] = 0x00; 
            data[1] = 0x00; 
            data[2] = 0x00; 
            spi_master_write( &ctx->spi_master, data, 3 );
        }
        else{
            uint8_t data[3];
            data[0] = ( ( uint8_t )value & 0x3F )|0x40; 
            data[1] = 0x00; 
            data[2] = 0x00; 
            spi_master_write( &ctx->spi_master, data, 3 );
        }
    }
    if( length == 8 )
    {
        data[0] = ( uint8_t )( ( ( addres >> 16) & 0x3F )|0x80 );  
        data[1] = ( uint8_t )( ( addres >> 8 ) & 0xFF );
        data[2] = ( uint8_t )( addres & 0xFF );
        data[3] = ( uint8_t )value;
        spi_master_write( &ctx->spi_master, data, 4 );
    }
    else if( length == 16 )
    {
        data[1] = ( uint8_t )( ( addres >> 8 ) & 0xFF );
        data[0] = ( uint8_t )( ( ( addres >> 16 ) & 0x3F ) | 0x80 );
        data[2] = ( uint8_t )( addres & 0xFF );
        data[3] = ( uint8_t )( value & 0xFF );
        data[4] = ( uint8_t )( ( value >> 8 ) & 0xFF );
        spi_master_write( &ctx->spi_master, data, 5 );
    }
    else if( length == 32 )
    {
        data[0] = ( uint8_t )( ( ( addres >> 16 ) & 0x3F ) | 0x80);
        data[1] = ( uint8_t )( ( addres >> 8 ) & 0xFF );
        data[2] = ( uint8_t )( addres & 0xFF );
        data[3] = ( uint8_t )( value & 0xFF );
        data[4] = ( uint8_t )( ( value >> 8 ) & 0xFF );
        data[5] = ( uint8_t )( ( value >> 16 ) & 0xFF );
        data[6] = ( uint8_t )( ( value >> 24 ) & 0xFF );
        spi_master_write( &ctx->spi_master, data, 7 );
    }

    spi_master_deselect_device( cfg->cs_pin );
}

uint32_t read_data(ft800_t *ctx, ft800_cfg_t *cfg, uint32_t addres, uint8_t length ){

    spi_master_select_device( cfg->cs_pin );
    if( length == 8 )
    {
        uint8_t tx_data[3];
        uint8_t rx_data_8[2];
        tx_data[0] = ( uint8_t )(( addres >> 16 ) & 0x3F); 
        tx_data[1] = ( uint8_t )(( addres >> 8 ) & 0xFF);
        tx_data[2] = ( uint8_t )( addres & 0xFF );
        spi_master_write_then_read( &ctx->spi_master, tx_data, 3, rx_data_8, 2 );
        spi_master_deselect_device( cfg->cs_pin );
        return rx_data_8[1];
    }

    else if( length == 16 )
    {
        uint8_t tx_data[3];
        uint8_t rx_data[3];
        uint16_t result_16;
        tx_data[0] = ( uint8_t )(( addres >> 16) & 0x3F );
        tx_data[1] = ( uint8_t )(( addres >> 8) & 0xFF );
        tx_data[2] = ( uint8_t )( addres & 0xFF ); 

        spi_master_write_then_read( &ctx->spi_master, tx_data, 3, rx_data, 3 );
        
        spi_master_deselect_device( cfg->cs_pin );
        result_16 = ( rx_data[2] << 8 ) | rx_data[1];
        return result_16;
    }

    else if( length == 32 ){

        uint8_t tx_data[3];
        uint8_t rx_data[5];
        uint32_t result_32;

        tx_data[0] = ( uint8_t )(( addres >> 16 ) & 0x3F );
        tx_data[1] = ( uint8_t )(( addres >> 8 ) & 0xFF );
        tx_data[2] = ( uint8_t )( addres & 0xFF );

        
        spi_master_write_then_read( &ctx->spi_master, tx_data, 3, rx_data, 5 );
        
        spi_master_deselect_device( cfg->cs_pin );
        result_32 = ( rx_data[4] << 24 )|( rx_data[3] << 16 )|( rx_data[2] << 8 ) | rx_data[1] ;
        return result_32;
    }
    
}

void ft800_default_cfg( ft800_t * ctx ){
    return;
}


void wait_coprocessor( ft800_t *ctx, ft800_cfg_t *cfg ){
    uint16_t read = read_data( ctx, cfg, FT800_REG_CMD_READ, 16 );
    uint16_t write = read_data( ctx, cfg, FT800_REG_CMD_WRITE, 16 );
    while( read != write ){
        read = read_data( ctx, cfg, FT800_REG_CMD_READ, 16);
        write = read_data(ctx, cfg, FT800_REG_CMD_WRITE, 16);
    }

}

void cmd( ft800_t *ctx, ft800_cfg_t *cfg, uint32_t command, uint16_t*cmdOffset ){
    write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, command, 32 );
    *cmdOffset += 4;
    write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, 16 );
}


void cmd_text( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t* cmdOffset, int16_t x, int16_t y, int16_t font, uint16_t options, const char* s ) {
    cmd(ctx, cfg, FT800_CMD_TEXT, cmdOffset );
    cmd(ctx, cfg, ( y << 16 ) | ( x & 0xFFFF ), cmdOffset );
    cmd(ctx, cfg, ( options << 16 ) | ( font & 0xFFFF ), cmdOffset);

    while ( *s ) {
        write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, *s++, 8);
        ( *cmdOffset )++;
    }
    write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, 0, 8);
    ( *cmdOffset )++;
    *cmdOffset = ( *cmdOffset + 3 ) & ~ 3;
    write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, 16);
}
uint16_t text_width( uint8_t size, char *text ){
    uint16_t cnt_width = 0;
    uint16_t width_t;
    if ( size <= 12 ){ 
        width_t = 8; 
    }
    else if ( size <= 24 ){ 
        width_t = 10;
    }
    else if ( size <= 36 ){ 
        width_t = 12;
    }
    else if ( size <= 48 ){ 
        width_t = 14;
    }
    else if (size <= 60){ 
        width_t = 17;
    }
    else{ 
        width_t = 24;
    }
    for (int i = 0; text[i] != '\0'; i++) {
        cnt_width += width_t;
    }
    return cnt_width;
}

uint16_t text_height( uint8_t size, char *text ){
    uint16_t cnt_height = 0;
    uint16_t height_t;
    if ( size <= 12 ){ 
        height_t = 13; 
    }
    else if ( size <= 24 ){ 
        height_t = 16;
    }
    else if ( size <= 36 ){ 
        height_t = 21;
    }
    else if ( size <= 48 ){ 
        height_t = 25;
    }
    else if ( size <= 60 ){ 
        height_t = 30;
    }
    else{ 
        height_t = 36;
    }
    for ( int i = 0; text[i] != '\0'; i++ ) {
        cnt_height += height_t;
    }
    return cnt_height;
}

void draw_aligned_text( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, uint16_t x, uint16_t y, uint16_t width, uint16_t height, ft800_text_alignment alignment, uint8_t size, uint8_t pen, char *text) {

    uint8_t font_size;
    uint8_t middle;
    uint16_t x_text;
    uint16_t y_text;
    uint16_t width_t;
    uint16_t cnt_width = text_width( size, text );

    if ( size <= 16 ){ 
        font_size = 26; 
        middle = 6;
    }
    else if ( size <= 32 ){ 
        font_size = 27; 
        middle =  8; 
    }
    else if ( size <= 48 ){ 
        font_size = 28; 
        middle = 10;
    }
    else if ( size <= 64 ){ 
        font_size = 29; 
        middle = 12; 
    }
    else if ( size <= 80 ){ 
        font_size = 30; 
        middle = 15; 
    }
    else{ 
        font_size = 31; 
        middle = 18; 
        width_t=24;
    }


    if( alignment == FT800_TEXT_ALIGNMENT_LEFT ){
        x_text = x + pen;
        y_text = ( uint16_t )( y + height / 2.0 - middle );
    }
    else if( alignment == FT800_TEXT_ALIGNMENT_RIGHT ){
        x_text = ( uint16_t )( x + width - cnt_width );
        y_text = ( uint16_t )( y + height / 2.0 - middle );
    }
    else if( alignment == FT800_TEXT_ALIGNMENT_CENTER ){
        x_text = ( uint16_t )( x + width / 2.0 - cnt_width / 2.0 );
        y_text = ( uint16_t )( y + height / 2.0 - middle );
    }
    else if( alignment == FT800_TEXT_ALIGNMENT_TOP ){
        x_text = ( uint16_t )( x + width / 2.0 - cnt_width / 2.0 );
        y_text = ( uint16_t )( y + pen );
    }
    else if( alignment == FT800_TEXT_ALIGNMENT_BOTTOM ){
        x_text = ( uint16_t )( x + width / 2.0 - cnt_width / 2.0 );
        y_text = y + height - 2 * middle - 2 * pen;
    }
    cmd_text( ctx, cfg, cmdOffset, x_text, y_text, font_size, 0, text );
}

void draw_vertical_text( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t* cmdOffset, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t text_s, uint16_t pen, ft800_text_alignment alignment, char *text ) {
    uint16_t x_text;
    uint16_t y_text;
    uint16_t font_size;
    uint8_t l_size = text_s / ( float )( sizeof( text ) );

    if ( l_size <= 16 ){ 
        font_size = 26; 
    }
    else if ( l_size <= 32 ){ 
        font_size = 27; 
    }
    else if ( l_size <= 48 ){ 
        font_size = 28; 
    }
    else if ( l_size <= 64 ){ 
        font_size = 29; 
    }
    else if ( l_size <= 80 ){ 
        font_size = 30; 
    }
    else{ 
        font_size = 31; 
    }

    uint16_t text_h = text_height( font_size, text );
    uint16_t text_w = text_width( font_size, text[0] );
    y_text = ( uint16_t )( y + height / 2.0 - text_h / 2.0);

    if( alignment == FT800_TEXT_ALIGNMENT_LEFT ){
        x_text = x + pen;
    }
    else if( alignment == FT800_TEXT_ALIGNMENT_CENTER ){
        x_text = ( uint16_t )( x + width / 2.0 - text_w / 2.0 );
    }
    else if( alignment == FT800_TEXT_ALIGNMENT_RIGHT ){
        x_text = x + width - text_w;
    }
    char ch[2];  

    
    for (int i = 0; text[i] != '\0'; i++) {
        ch[0] = text[i];
        ch[1] = '\0';
        cmd_text( ctx, cfg, cmdOffset, x_text, y_text, font_size, 0, ch );
        y_text += text_height( l_size, text[1] ); 
    }
}

void cmd_number( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t* cmdOffset, uint16_t left, uint16_t top, uint16_t font, uint16_t options, int32_t num ){
    cmd( ctx, cfg, FT800_CMD_NUMBER, cmdOffset );
    cmd( ctx, cfg, ( top << 16 ) | ( left & 0xFFFF ), cmdOffset );
    cmd( ctx, cfg, ( options << 16 ) | ( font & 0xFFFF ), cmdOffset );
    cmd( ctx, cfg, num, cmdOffset );
    write_data( ctx, cfg, FT800_RAM_CMD + *cmdOffset, 0, 8 );
    ( *cmdOffset )++;
    *cmdOffset = ( *cmdOffset + 3 ) & ~ 3;
    write_data( ctx, cfg, FT800_REG_CMD_WRITE, *cmdOffset, 16 );
}

void ft800_cfg( ft800_t *ctx, ft800_cfg_t *cfg ){

    write_data( ctx, cfg, FT800_CMD_ADDRES, FT800_ACTIVE, 24 );
    Delay_ms( 20 ); 
    write_data( ctx, cfg, FT800_CMD_ADDRES, FT800_CLKEXT, 24 );
    Delay_ms( 20 );

    write_data( ctx, cfg, FT800_CMD_ADDRES, FT800_CLK48M, 24 );
    Delay_ms( 20 );
    
    //spi_master_set_speed( &spi_master,18000000 );

    write_data( ctx, cfg, FT800_REG_GPIO, 0x00, 8 );
    write_data( ctx, cfg, FT800_REG_PCLK, 0x00, 8 );


    write_data( ctx, cfg, FT800_REG_HCYCLE, 548, 16 );
    write_data( ctx, cfg, FT800_REG_HOFFSET, 43, 16 );
    write_data( ctx, cfg, FT800_REG_HSYNC0, 0, 16 );
    write_data( ctx, cfg, FT800_REG_HSYNC1, 41, 16 );
    write_data( ctx, cfg, FT800_REG_VCYCLE, 292, 16 );
    write_data( ctx, cfg, FT800_REG_VOFFSET, 12, 16 );
    write_data( ctx, cfg, FT800_REG_VSYNC0, 0, 16 );
    write_data( ctx, cfg, FT800_REG_VSYNC1, 10, 16 );
    write_data( ctx, cfg, FT800_REG_PCLK_POL, 1 ,8 );
    // write_data(FT800_REG_HSIZE,TFT_WIDTH,16);
    write_data(ctx,cfg, FT800_REG_HSIZE, 480, 16 );
    // write_data(FT800_REG_VSIZE,TFT_HEIGHT,16);
    write_data(ctx,cfg, FT800_REG_VSIZE, 272, 16 );
    write_data(ctx,cfg, FT800_REG_CSPREAD, 0, 8 );

    write_data( ctx, cfg, RAM_DL + 0, FT800_CLEAR_COLOR_RGB( 0, 0, 255 ), 32 );
    write_data( ctx, cfg, RAM_DL + 4, FT800_CLEAR( 1, 1, 1 ), 32 );
    write_data( ctx, cfg, RAM_DL + 8, FT800_DISPLAY(), 32 );
    write_data( ctx, cfg, FT800_REG_DLSWAP, 2, 32 );

    write_data(ctx,cfg, FT800_REG_GPIO_DIR, 0x80, 8 );
    write_data(ctx,cfg, FT800_REG_GPIO, 0x80, 8 );
    write_data(ctx,cfg, FT800_REG_PWM_HZ, 0x00FA, 16 );
    write_data(ctx,cfg, FT800_REG_PWM_DUTY, 0x80, 8 );
    write_data(ctx,cfg, FT800_REG_PCLK, 0x05, 8 );

}

/**
 * @note @b FT800 hardware does not support gestures.
 */
void ft800_gesture( ft800_t* ctx, tp_event_t * event ) {
    *event = TP_EVENT_GEST_NONE;
}

tp_event_t ft800_press_detect( ft800_t* ctx ) {
    return ctx->press_det;
}

void ft800_press_coordinates( ft800_t* ctx, tp_touch_item_t * touch_item ) {
    touch_item->n_touches = 1;
    touch_item->point[0] = ctx->touch.point[0];
}

void ft800_init( ft800_t * ctx, ft800_cfg_t * cfg, tp_drv_t * drv ){

    spi_master_configure_default( &cfg->spi_master_cfg );

    digital_out_init( &ctx->cs_pin,cfg->cs_pin );
    digital_out_init( &ctx->pd_pin,cfg->pd_pin );
    cfg->spi_master_cfg.sck=cfg->sck_pin;
    cfg->spi_master_cfg.miso=cfg->miso_pin;
    cfg->spi_master_cfg.mosi=cfg->mosi_pin;
    cfg->spi_master_cfg.speed = 18000000; 
    cfg->spi_master_cfg.mode = SPI_MASTER_MODE_0; 
    cfg->spi_master_cfg.default_write_data = 0x00;

    if ( SPI_MASTER_SUCCESS == spi_master_open( &ctx->spi_master, &cfg->spi_master_cfg ) ) {

        spi_master_set_chip_select_polarity( SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW );

    }

    spi_master_set_speed( &ctx->spi_master,4500000 );

    digital_out_low( &ctx->pd_pin );
    Delay_ms(20);
    digital_out_high( &ctx->pd_pin );
    Delay_ms(20);
 
    ft800_cfg(ctx,cfg);

    init_touch_screen(ctx, cfg, true);

    drv->tp_press_detect_f      = ft800_press_detect;
    drv->tp_press_coordinates_f = ft800_press_coordinates;
    drv->tp_gesture_f           = ft800_gesture;
    drv->tp_process_f           = ft800_process;
}

tp_err_t ft800_process( ft800_t * ctx , ft800_cfg_t *cfg)
{
    tp_err_t status;

    status = ft800_read_press_coordinates( ctx,cfg );

    return status;
}

static tp_err_t ft800_read_press_coordinates( ft800_t *ctx, ft800_cfg_t *cfg )
{
    uint32_t position=read_data(ctx,cfg,FT800_REG_TOUCH_SCREEN_XY,32);
    if ( position!=2147516416 )
    {
        // TODO: Implement press coordinates obtaining from FT800
        
        ctx->touch.point[0].coord_x=position>>16;
        ctx->touch.point[0].coord_y=position&0xFFFF;

        ctx->press_det = TP_EVENT_PRESS_DET;
    }
    else
    {   ctx->touch.point[0].coord_x=0;
        ctx->touch.point[0].coord_y=0;
        ctx->press_det = TP_EVENT_PRESS_NOT_DET;
    }

    return TP_OK;
}

uint8_t rgb_convert(int16_t color,char *name){
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    if(strcmp(name,"red")==0){
        red=(uint8_t)(((color>>11)&0x1F)*(255.0/31.0));
        return red;
    }
    if(strcmp(name,"green")==0){
        green=(uint8_t)(((color>>5)&0x3F)*(255.0/63.0));
       return green;
    }
    if(strcmp(name,"blue")==0){
        blue=(uint8_t)((color&0x1F)*(255.0/31.0));
       return blue;
    }
    

}


void start_display_list(ft800_t *ctx, ft800_cfg_t *cfg,uint16_t *cmdOffset){
    
    //while(read_data((ctx,cfg,FT800_REG_DLSWAP,8)&0x03)!=0);/*Eksperimentalno.Obrisati ako se zaglavi*/

    cmd(ctx,cfg,FT800_CMD_DLSTART , cmdOffset);
    cmd(ctx,cfg,FT800_CLEAR_COLOR_RGB(255, 255, 255), cmdOffset);  
    cmd(ctx,cfg,FT800_CLEAR(1,1,1), cmdOffset);
    
}

void end_display_list(ft800_t *ctx, ft800_cfg_t *cfg,uint16_t *cmdOffset){
    cmd(ctx,cfg,FT800_CMD_DISPLAY,cmdOffset);
    cmd(ctx,cfg,FT800_CMD_SWAP,cmdOffset);
    //wait_coprocessor(ctx,cfg);
    *cmdOffset=0; /*Eksperimentalno.Ukoliko dodje do problema obrisati*/
}

void draw_button(ft800_t *ctx, ft800_cfg_t *cfg,uint16_t *cmdOffset,ft800_rounded_button *button){
    if(button->active){
        ft800_read_press_coordinates( ctx,cfg );
        uint16_t x_coordinate=ctx->touch.point[0].coord_x;
        uint16_t y_coordinate=ctx->touch.point[0].coord_y;
        gl_set_font(button->text.font.font_data);
        gl_size_t text_size = gl_get_text_dimensions(button->text.caption);
        uint8_t text_height=text_size.height;
        if(button->active==1){
            if(button->press_gradient.transparent==0){
                if(((x_coordinate<=(button->left+button->width))&&x_coordinate>=button->left)&&((y_coordinate<=(button->top+button->height))&&y_coordinate>=button->top)){
                    draw_gradient_rectangle(ctx,cfg, cmdOffset, button->left, button->top, button->width-button->pen.width, button->height-button->pen.width,2*button->corner_radius, button->press_gradient.press_start_color, button->press_gradient.press_end_color,button->press_gradient.gradient_style);
                }
                else{
                    draw_gradient_rectangle(ctx,cfg, cmdOffset, button->left, button->top, button->width-button->pen.width, button->height-button->pen.width,2*button->corner_radius, button->press_gradient.start_color, button->press_gradient.end_color,button->press_gradient.gradient_style);
                }
                
            }
            
            draw_edges_rectangle(ctx,cfg,cmdOffset,button->left,button->top,button->width, button->height,button->corner_radius, button->pen.color,button->pen.width);
            cmd(ctx, cfg, FT800_COLOR_RGB(rgb_convert(button->text.font.color, "red"),rgb_convert(button->text.font.color, "green"),rgb_convert(button->text.font.color, "blue")), cmdOffset);
            if(button->vertical_text){
               
                draw_vertical_text(ctx,cfg,cmdOffset,button->left, button->top,button->width,button->height,text_height,button->pen.width,button->text_align, button->text.caption);
            }
            else{
                draw_aligned_text(ctx,cfg,cmdOffset,button->left, button->top, button->width, button->height,button->text_align, text_height,button->pen.width, button->text.caption);
            }
            
            
        }

    }
    
}

void draw_circle(ft800_t *ctx, ft800_cfg_t *cfg,uint16_t *cmdOffset,ft800_circle *circle){
    if(circle->active==1){
        ft800_read_press_coordinates( ctx,cfg );
        uint16_t x_coordinate=ctx->touch.point[0].coord_x;
        uint16_t y_coordinate=ctx->touch.point[0].coord_y;

        if(circle->press_gradient.transparent==0){
            if(((x_coordinate<=(circle->left+2*circle->radius))&&x_coordinate>=(circle->left))&&((y_coordinate<=(circle->top+2*circle->radius))&&y_coordinate>=circle->top)){
                draw_gradient_circle(ctx, cfg,cmdOffset,circle->left+circle->radius,circle->top+circle->radius,2*circle->radius,circle->press_gradient.press_start_color,circle->press_gradient.press_end_color,circle->press_gradient.gradient_style);
                
            }
            else{
                draw_gradient_circle(ctx, cfg,cmdOffset,circle->left+circle->radius,circle->top+circle->radius,2*circle->radius,circle->press_gradient.start_color,circle->press_gradient.end_color,circle->press_gradient.gradient_style);
            }
        }
        draw_edges_circle(ctx,cfg,cmdOffset,circle->left+circle->radius,circle->top+circle->radius,2*circle->radius,circle->pen.color,circle->pen.width);
    }   
}


void draw_label(ft800_t *ctx,ft800_cfg_t *cfg,uint16_t *cmdOffset,ft800_label *label){
    if(label->active==1){
        gl_set_font(label->text.font.font_data);
        gl_size_t text_size = gl_get_text_dimensions(label->text.caption);
        uint16_t text_height=text_size.height;
        cmd(ctx,cfg,FT800_COLOR_RGB(rgb_convert(label->text.font.color,"red"),rgb_convert(label->text.font.color,"green"), rgb_convert(label->text.font.color,"blue")), cmdOffset);
        if(label->vertical_text){
            draw_vertical_text(ctx,cfg,cmdOffset,label->left,label->top,label->width,label->height,text_height,0,FT800_TEXT_ALIGNMENT_LEFT, label->text.caption);
        }
        else{
            draw_aligned_text(ctx,cfg,cmdOffset,label->left,label->top, label->width, label->height,FT800_TEXT_ALIGNMENT_LEFT, text_height,0, label->text.caption);

        }
        
        
    }
}

void draw_line(ft800_t *ctx,ft800_cfg_t *cfg,uint16_t *cmdOffset,ft800_line *line){
    
    cmd(ctx,cfg,FT800_BEGIN(FT800_LINES) , cmdOffset);
    cmd(ctx,cfg,FT800_LINE_WIDTH(line->pen.width*16) , cmdOffset);
    cmd(ctx,cfg,FT800_COLOR_RGB(rgb_convert(line->pen.color,"red"),rgb_convert(line->pen.color,"green"),rgb_convert(line->pen.color,"blue")) , cmdOffset);
    cmd(ctx,cfg,FT800_VERTEX2F(line->first_left*16,line->first_top*16) , cmdOffset);
    cmd(ctx,cfg,FT800_VERTEX2F(line->second_left*16,line->second_top*16) , cmdOffset);
    cmd(ctx,cfg,FT800_END() , cmdOffset);
}

void draw_box(ft800_t *ctx, ft800_cfg_t *cfg,uint16_t *cmdOffset,ft800_rounded_box *box){
    ft800_read_press_coordinates( ctx,cfg );
    uint16_t x_coordinate=ctx->touch.point[0].coord_x;
    uint16_t y_coordinate=ctx->touch.point[0].coord_y;

    
    if(box->active==1){
        if(box->press_gradient.transparent==0){

            if(((x_coordinate<=(box->left+box->width))&&x_coordinate>=box->left)&&((y_coordinate<=(box->top+box->height))&&y_coordinate>=box->top)){
                
                draw_gradient_rectangle(ctx,cfg, cmdOffset, box->left, box->top, box->width-box->pen.width, box->height-box->pen.width,2*box->corner_radius, box->press_gradient.press_start_color, box->press_gradient.press_end_color,box->press_gradient.gradient_style);
            }
            else{
                draw_gradient_rectangle(ctx,cfg, cmdOffset, box->left, box->top, box->width-box->pen.width, box->height-box->pen.width,2*box->corner_radius, box->press_gradient.start_color, box->press_gradient.end_color,box->press_gradient.gradient_style);
                
            }
            
        }
        draw_edges_rectangle(ctx,cfg,cmdOffset,box->left,box->top,box->width, box->height,box->corner_radius,box->pen.color,box->pen.width);
    }
}


void draw_progress_bar(ft800_t *ctx,ft800_cfg_t *cfg,uint16_t *cmdOffset,ft800_progress_bar *progress_bar){
    
        if(progress_bar->gradient.transparent==0){

            draw_gradient_rectangle(ctx,cfg,cmdOffset,progress_bar->left+26, progress_bar->top,(uint16_t)(((float)progress_bar->position/100)*(progress_bar->width-52)),progress_bar->height,0,progress_bar->gradient.end_color, progress_bar->gradient.start_color,progress_bar->gradient.gradient_style);
        }
        else{
            draw_gradient_rectangle(ctx,cfg,cmdOffset,progress_bar->left, progress_bar->top,progress_bar->width,progress_bar->height,progress_bar->corner_radius,progress_bar->back_color, progress_bar->back_color,progress_bar->gradient.gradient_style);
        }
        draw_edges_rectangle(ctx,cfg, cmdOffset,progress_bar->left, progress_bar->top,progress_bar->width,progress_bar->height,progress_bar->corner_radius,progress_bar->pen.color,progress_bar->pen.width);
        cmd(ctx,cfg,FT800_BEGIN(FT800_LINES), cmdOffset);
        cmd(ctx,cfg,FT800_LINE_WIDTH(progress_bar->pen.width*16) , cmdOffset);
        cmd(ctx,cfg,FT800_VERTEX2F(((progress_bar->left+26)*16),progress_bar->top*16), cmdOffset);
        cmd(ctx,cfg,FT800_VERTEX2F(((progress_bar->left+26)*16),(progress_bar->top+progress_bar->height)*16), cmdOffset);
        cmd(ctx,cfg,FT800_END(), cmdOffset);
        cmd(ctx,cfg,FT800_BEGIN(FT800_LINES), cmdOffset);
        cmd(ctx,cfg,FT800_VERTEX2F((uint16_t)(((float)progress_bar->position/100)*(progress_bar->width-52)+(progress_bar->left+26))*16,progress_bar->top*16), cmdOffset);
        cmd(ctx,cfg,FT800_VERTEX2F((uint16_t)(((float)progress_bar->position/100)*(progress_bar->width-52)+(progress_bar->left+26))*16,(progress_bar->top+progress_bar->height)*16), cmdOffset);
        cmd(ctx,cfg,FT800_END(), cmdOffset);
        if(progress_bar->show_position){
            cmd(ctx,cfg,FT800_COLOR_RGB(rgb_convert(progress_bar->font.color,"red"),rgb_convert(progress_bar->font.color,"green"),rgb_convert(progress_bar->font.color,"blue")) , cmdOffset);
            cmd_number(ctx,cfg,cmdOffset,(uint16_t)(progress_bar->left+26+(float)progress_bar->width/5),(uint16_t)(progress_bar->top+(float)progress_bar->height/2-13),30,0,progress_bar->position);
        }
    
}

void draw_check_box(ft800_t *ctx, ft800_cfg_t *cfg,uint16_t *cmdOffset,ft800_check_box *check_box){
    if(check_box->active==1){
        ft800_read_press_coordinates( ctx,cfg );
        uint16_t x_coordinate=ctx->touch.point[0].coord_x;
        uint16_t y_coordinate=ctx->touch.point[0].coord_y;
        uint16_t text_s=text_width(30,check_box->text.caption);
        gl_set_font(check_box->text.font.font_data);
        gl_size_t text_size = gl_get_text_dimensions(check_box->text.caption);
        uint8_t text_height=text_size.height;
        if(check_box->text_align==FT800_TEXT_ALIGNMENT_RIGHT){
            if(check_box->press_gradient.transparent==0){
                if(((x_coordinate<=(check_box->left+check_box->width))&&x_coordinate>=check_box->left)&&((y_coordinate<=(check_box->top+check_box->height))&&y_coordinate>=check_box->top)){
                    draw_gradient_rectangle(ctx,cfg,cmdOffset,check_box->left,check_box->top ,check_box->height,check_box->height,check_box->corner_radius,check_box->press_gradient.press_start_color, check_box->press_gradient.press_end_color,check_box->press_gradient.gradient_style);

                }
                else{
                    draw_gradient_rectangle(ctx,cfg,cmdOffset,check_box->left,check_box->top ,check_box->height,check_box->height,check_box->corner_radius,check_box->press_gradient.start_color,check_box->press_gradient.end_color,check_box->press_gradient.gradient_style);
                }

            }
            draw_edges_rectangle(ctx,cfg, cmdOffset,check_box->left, check_box->top, check_box->height, check_box->height,check_box->corner_radius, check_box->pen.color,check_box->pen.width);
            cmd(ctx,cfg,FT800_COLOR_RGB(rgb_convert(check_box->text.font.color,"red"),rgb_convert(check_box->text.font.color,"green"),rgb_convert(check_box->text.font.color,"blue")), cmdOffset);
            draw_aligned_text(ctx,cfg,cmdOffset,check_box->left+check_box->height, check_box->top, check_box->height, check_box->height,FT800_TEXT_ALIGNMENT_LEFT, text_height,check_box->pen.width, check_box->text.caption);
            cmd(ctx,cfg,FT800_COLOR_RGB(rgb_convert(check_box->pen.color,"red"),rgb_convert(check_box->pen.color,"green"),rgb_convert(check_box->pen.color,"blue")), cmdOffset);
            cmd(ctx,cfg,FT800_LINE_WIDTH(10*16) , cmdOffset);
            cmd(ctx,cfg,FT800_BEGIN(FT800_LINES), cmdOffset);
            cmd(ctx,cfg,FT800_VERTEX2F((check_box->left+5*check_box->pen.width)*16,(uint16_t)(check_box->top+(2.0/3.0)*check_box->height)*16), cmdOffset);
            cmd(ctx,cfg,FT800_VERTEX2F((uint16_t)(check_box->left+(1.0/3.0)*check_box->height+check_box->pen.width)*16,(check_box->top+check_box->height-5*check_box->pen.width)*16), cmdOffset);
            cmd(ctx,cfg,FT800_END(), cmdOffset);
            cmd(ctx,cfg,FT800_BEGIN(FT800_LINES), cmdOffset);
            cmd(ctx,cfg,FT800_VERTEX2F((uint16_t)(check_box->left+(1.0/3.0)*check_box->height+check_box->pen.width)*16,(check_box->top+check_box->height-5*check_box->pen.width)*16), cmdOffset);
            cmd(ctx,cfg,FT800_VERTEX2F((check_box->left+check_box->height-6*check_box->pen.width)*16,(check_box->top+6*check_box->pen.width)*16), cmdOffset);
            cmd(ctx,cfg,FT800_END(), cmdOffset);
           
        }
        else if(check_box->text_align==FT800_TEXT_ALIGNMENT_LEFT){
            if(check_box->press_gradient.transparent==0){
                if(((x_coordinate<=(check_box->left+check_box->width))&&x_coordinate>=check_box->left)&&((y_coordinate<=(check_box->top+check_box->height))&&y_coordinate>=check_box->top)){
                    draw_gradient_rectangle(ctx,cfg,cmdOffset,text_s+check_box->left,check_box->top ,check_box->height,check_box->height,check_box->corner_radius,check_box->press_gradient.press_start_color, check_box->press_gradient.press_end_color,check_box->press_gradient.gradient_style);

                }
                else{
                    draw_gradient_rectangle(ctx,cfg,cmdOffset,text_s+check_box->left,check_box->top ,check_box->height,check_box->height,check_box->corner_radius,check_box->press_gradient.start_color,check_box->press_gradient.end_color,check_box->press_gradient.gradient_style);
                }

            }
            draw_edges_rectangle(ctx,cfg, cmdOffset,text_s+check_box->left, check_box->top, check_box->height, check_box->height,check_box->corner_radius, check_box->pen.color,check_box->pen.width);
            cmd(ctx,cfg,FT800_COLOR_RGB(rgb_convert(check_box->text.font.color,"red"),rgb_convert(check_box->text.font.color,"green"),rgb_convert(check_box->text.font.color,"blue")), cmdOffset);
            draw_aligned_text(ctx,cfg,cmdOffset,check_box->left, check_box->top, check_box->height, check_box->height,FT800_TEXT_ALIGNMENT_LEFT, text_height,check_box->pen.width, check_box->text.caption);
            cmd(ctx,cfg,FT800_COLOR_RGB(rgb_convert(check_box->pen.color,"red"),rgb_convert(check_box->pen.color,"green"),rgb_convert(check_box->pen.color,"blue")), cmdOffset);
            cmd(ctx,cfg,FT800_LINE_WIDTH(10*16) , cmdOffset);
            cmd(ctx,cfg,FT800_BEGIN(FT800_LINES), cmdOffset);
            cmd(ctx,cfg,FT800_VERTEX2F((text_s+check_box->left+5*check_box->pen.width)*16,(uint16_t)(check_box->top+(2.0/3.0)*check_box->height)*16), cmdOffset);
            cmd(ctx,cfg,FT800_VERTEX2F((uint16_t)(text_s+check_box->left+(1.0/3.0)*check_box->height+check_box->pen.width)*16,(check_box->top+check_box->height-5*check_box->pen.width)*16), cmdOffset);
            cmd(ctx,cfg,FT800_END(), cmdOffset);
            cmd(ctx,cfg,FT800_BEGIN(FT800_LINES), cmdOffset);
            cmd(ctx,cfg,FT800_VERTEX2F((uint16_t)(text_s+check_box->left+(1.0/3.0)*check_box->height+check_box->pen.width)*16,(check_box->top+check_box->height-5*check_box->pen.width)*16), cmdOffset);
            cmd(ctx,cfg,FT800_VERTEX2F((text_s+check_box->left+check_box->height-6*check_box->pen.width)*16,(check_box->top+6*check_box->pen.width)*16), cmdOffset);
            cmd(ctx,cfg,FT800_END(), cmdOffset);
            
        }
    }
}


void draw_radio_button(ft800_t *ctx, ft800_cfg_t *cfg,uint16_t *cmdOffset,ft800_radio_button *radio_button){
    if(radio_button->active==1){
        ft800_read_press_coordinates( ctx,cfg );
        uint16_t x_coordinate=ctx->touch.point[0].coord_x;
        uint16_t y_coordinate=ctx->touch.point[0].coord_y;
        uint16_t text_s=text_width(30,radio_button->text.caption);
        gl_set_font(radio_button->text.font.font_data);
        gl_size_t text_size = gl_get_text_dimensions(radio_button->text.caption);
        uint8_t text_height=text_size.height;
        if(radio_button->text_align==FT800_TEXT_ALIGNMENT_RIGHT){
            if(radio_button->press_gradient.transparent==0){
                if(((x_coordinate<=(radio_button->left+radio_button->width))&&(x_coordinate>=radio_button->left))&&((y_coordinate<=(radio_button->top+radio_button->height))&&(y_coordinate>=radio_button->top))){
                
                    draw_gradient_circle(ctx,cfg,cmdOffset,(uint16_t)(radio_button->left+(float)radio_button->height/2.0), (uint16_t)(radio_button->top+(float)radio_button->height/2.0), radio_button->height/2.0,radio_button->press_gradient.press_end_color,radio_button->press_gradient.press_start_color,radio_button->press_gradient.gradient_style);

                }
                else{
                    draw_gradient_circle(ctx,cfg,cmdOffset,(uint16_t)(radio_button->left+(float)radio_button->height/2.0), (uint16_t)(radio_button->top+(float)radio_button->height/2.0), radio_button->height/2.0,radio_button->press_gradient.end_color,radio_button->press_gradient.start_color,radio_button->press_gradient.gradient_style);
                }

            }
    
            draw_edges_circle(ctx,cfg,cmdOffset,(uint16_t)(radio_button->left+(float)radio_button->height/2.0), (uint16_t)(radio_button->top+(float)radio_button->height/2.0),radio_button->height,radio_button->pen.color,radio_button->pen.width);
            draw_edges_circle(ctx,cfg,cmdOffset,(uint16_t)(radio_button->left+(float)radio_button->height/2.0), (uint16_t)(radio_button->top+(float)radio_button->height/2.0),radio_button->height/2.0,radio_button->pen.color,radio_button->pen.width);
            cmd(ctx,cfg,FT800_COLOR_RGB(rgb_convert(radio_button->text.font.color,"red"),rgb_convert(radio_button->text.font.color,"green"),rgb_convert(radio_button->text.font.color,"blue")), cmdOffset);
            draw_aligned_text(ctx,cfg,cmdOffset,radio_button->left+radio_button->height+radio_button->pen.width*2,radio_button->top, radio_button->height, radio_button->height,FT800_TEXT_ALIGNMENT_LEFT, text_height,radio_button->pen.width, radio_button->text.caption);
        }
        else if(radio_button->text_align==FT800_TEXT_ALIGNMENT_LEFT){
            if(radio_button->press_gradient.transparent==0){
                if(((x_coordinate<=(radio_button->left+radio_button->width))&&(x_coordinate>=radio_button->left))&&((y_coordinate<=(radio_button->top+radio_button->height))&&(y_coordinate>=radio_button->top))){
                
                    draw_gradient_circle(ctx,cfg,cmdOffset,(uint16_t)(text_s+radio_button->left+(float)radio_button->height/2.0), (uint16_t)(radio_button->top+(float)radio_button->height/2.0), radio_button->height/2.0,radio_button->press_gradient.press_end_color,radio_button->press_gradient.press_start_color,radio_button->press_gradient.gradient_style);

                }
                else{
                    draw_gradient_circle(ctx,cfg,cmdOffset,(uint16_t)(text_s+radio_button->left+(float)radio_button->height/2.0), (uint16_t)(radio_button->top+(float)radio_button->height/2.0), radio_button->height/2.0,radio_button->press_gradient.end_color,radio_button->press_gradient.start_color,radio_button->press_gradient.gradient_style);
                }

            }
    
            draw_edges_circle(ctx,cfg,cmdOffset,(uint16_t)(text_s+radio_button->left+(float)radio_button->height/2.0), (uint16_t)(radio_button->top+(float)radio_button->height/2.0),radio_button->height,radio_button->pen.color,radio_button->pen.width);
            draw_edges_circle(ctx,cfg,cmdOffset,(uint16_t)(text_s+radio_button->left+(float)radio_button->height/2.0), (uint16_t)(radio_button->top+(float)radio_button->height/2.0),radio_button->height/2.0,radio_button->pen.color,radio_button->pen.width);
            cmd(ctx,cfg,FT800_COLOR_RGB(rgb_convert(radio_button->text.font.color,"red"),rgb_convert(radio_button->text.font.color,"green"),rgb_convert(radio_button->text.font.color,"blue")), cmdOffset);
            draw_aligned_text(ctx,cfg,cmdOffset,radio_button->left,radio_button->top, radio_button->height, radio_button->height,FT800_TEXT_ALIGNMENT_LEFT, text_height,radio_button->pen.width, radio_button->text.caption);            
        }

        
    }
}

void draw_ellipse(ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset,ft800_ellipse *ellipse){
    if(ellipse->active==1){
        ft800_read_press_coordinates( ctx,cfg );
        uint16_t x_coordinate=ctx->touch.point[0].coord_x;
        uint16_t y_coordinate=ctx->touch.point[0].coord_y;

        if(ellipse->press_gradient.transparent==0){
            if(((x_coordinate<=(ellipse->left+ellipse->width))&&x_coordinate>=ellipse->left)&&((y_coordinate<=(ellipse->top+ellipse->height))&&y_coordinate>=ellipse->top)){
            
                
                draw_gradient_ellipse(ctx,cfg,cmdOffset,(uint16_t)(ellipse->left+(float)ellipse->width/2.0), (uint16_t)(ellipse->top+(float)ellipse->height/2.0), ellipse->width, ellipse->height, ellipse->press_gradient.press_end_color,ellipse->press_gradient.press_start_color,ellipse->press_gradient.gradient_style);
            }
            else{
                draw_gradient_ellipse(ctx,cfg,cmdOffset,(uint16_t)(ellipse->left+(float)ellipse->width/2.0), (uint16_t)(ellipse->top+(float)ellipse->height/2.0), ellipse->width, ellipse->height,ellipse->press_gradient.end_color,ellipse->press_gradient.start_color,ellipse->press_gradient.gradient_style);
            }
        }
        draw_edges_ellipse(ctx,cfg, cmdOffset,(uint16_t)(ellipse->left+(float)ellipse->width/2.0),(uint16_t)(ellipse->top+(float)ellipse->height/2.0),ellipse->width, ellipse->height,ellipse->pen.color,ellipse->pen.width);
    }   

}

void draw_edges_circle(ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset,uint16_t cx, uint16_t cy,uint16_t width,uint16_t pen_color, uint16_t pen_width){
    float a = width / 2.0f;

    cmd(ctx, cfg, FT800_COLOR_RGB(rgb_convert(pen_color, "red"),rgb_convert(pen_color, "green"),rgb_convert(pen_color, "blue")), cmdOffset);

    cmd(ctx, cfg, FT800_LINE_WIDTH(pen_width * 16), cmdOffset);

    cmd(ctx, cfg, FT800_BEGIN(FT800_LINE_STRIP), cmdOffset);

    uint16_t segments = 100;

    for (uint16_t i = 0; i <= segments; i++) {
        float theta = (2.0f * 3.14159f * i) / segments;
        float x = cx + a * cosf(theta);
        float y = cy + a * sinf(theta);

        cmd(ctx, cfg, FT800_VERTEX2F((uint16_t)(x * 16), (uint16_t)(y * 16)), cmdOffset);
    }

    cmd(ctx, cfg, FT800_END(), cmdOffset);
}

void draw_gradient_circle(ft800_t *ctx, ft800_cfg_t *cfg,uint16_t *cmdOffset,uint16_t cx, uint16_t cy, uint16_t width, uint16_t s_color,uint16_t e_color,ft800_gradient_style gradient) {

        uint8_t red,green,blue;
        uint16_t radius=(uint16_t)((float)width/2.0),steps = radius*2;
        int16_t x1,x2,y1,y2,y_top,y_bottom,i ;
        float dx,dy,x_offset,y_offset,normalized_x,normalized_y,sqrt_val,t;
        if(gradient==FT800_GRADIENT_BOTTOM_TOP){

            for (i = 0; i <= steps; i++) {
                t = (float)i / steps;

                red = rgb_convert(e_color,"red")+t*(rgb_convert(s_color,"red")-rgb_convert(e_color,"red"));
                green = rgb_convert(e_color,"green")+t*(rgb_convert(s_color,"green")-rgb_convert(e_color,"green"));
                blue = rgb_convert(e_color,"blue")+t*(rgb_convert(s_color,"blue")-rgb_convert(e_color,"blue"));

                y_offset = -radius + (2.0f * radius * t);
                y1 = cy + (int16_t)(y_offset);
                y2 = y1 + 1; 

                normalized_y = y_offset / radius;
                if (normalized_y < -1.0f){
                    normalized_y = -1.0f;
                } 
                if (normalized_y > 1.0f){
                    normalized_y = 1.0f;
                } 

                sqrt_val = 1.0f - (normalized_y * normalized_y);
                if (sqrt_val < 0.0f){
                    sqrt_val = 0.0f;
                } 

                dx = radius * sqrt(sqrt_val);
                x1 = cx - (int16_t)(dx);
                x2 = cx + (int16_t)(dx);

                if (x2 > x1) {
                    cmd(ctx,cfg,FT800_COLOR_RGB(red, green, blue),cmdOffset);
                    cmd(ctx,cfg,FT800_BEGIN(FT800_RECTS),cmdOffset);
                    cmd(ctx,cfg,FT800_VERTEX2F(x1 * 16, y1 * 16),cmdOffset);
                    cmd(ctx,cfg,FT800_VERTEX2F(x2 * 16, y2 * 16),cmdOffset);
                    cmd(ctx,cfg,FT800_END(),cmdOffset);
                }
            }
        }
        else if(gradient==FT800_GRADIENT_TOP_BOTTOM){

            for (i = 0; i <= steps; i++) {
                t = (float)i / steps;

          
                red = rgb_convert(s_color,"red")+t*(rgb_convert(e_color,"red")-rgb_convert(s_color,"red"));
                green = rgb_convert(s_color,"green")+t*(rgb_convert(e_color,"green")-rgb_convert(s_color,"green"));
                blue = rgb_convert(s_color,"blue")+t*(rgb_convert(e_color,"blue")-rgb_convert(s_color,"blue"));

                y_offset = -radius + (2.0f * radius * t);
                y1 = cy + (int16_t)(y_offset);
                y2 = y1 + 1; 

                normalized_y = y_offset / radius;
                if (normalized_y < -1.0f){
                    normalized_y = -1.0f;
                } 
                if (normalized_y > 1.0f){
                    normalized_y = 1.0f;
                } 

                sqrt_val = 1.0f - (normalized_y * normalized_y);
                if (sqrt_val < 0.0f){
                    sqrt_val = 0.0f;
                } 

                dx = radius * sqrt(sqrt_val);
                x1 = cx - (int16_t)(dx);
                x2 = cx + (int16_t)(dx);

                if (x2 > x1) {
                    cmd(ctx,cfg,FT800_COLOR_RGB(red, green, blue),cmdOffset);
                    cmd(ctx,cfg,FT800_BEGIN(FT800_RECTS),cmdOffset);
                    cmd(ctx,cfg,FT800_VERTEX2F(x1 * 16, y1 * 16),cmdOffset);
                    cmd(ctx,cfg,FT800_VERTEX2F(x2 * 16, y2 * 16),cmdOffset);
                    cmd(ctx,cfg,FT800_END(),cmdOffset);
                }
            }
        } 

        else if(gradient==FT800_GRADIENT_RIGHT_LEFT){


            for (i = 0; i <= steps; i++) {
                t = (float)i / steps;

                red = rgb_convert(e_color,"red")+t*(rgb_convert(s_color,"red")-rgb_convert(e_color,"red"));
                green = rgb_convert(e_color,"green")+t*(rgb_convert(s_color,"green")-rgb_convert(e_color,"green"));
                blue = rgb_convert(e_color,"blue")+t*(rgb_convert(s_color,"blue")-rgb_convert(e_color,"blue"));
    
                x_offset = -radius + (2.0f * radius * t);
                x1 = cx + (int16_t)(x_offset);
                x2 = x1 + 1;  

                normalized_x = x_offset / radius;
                if (normalized_x < -1.0f){
                    normalized_x = -1.0f;
                } 
                if (normalized_x > 1.0f){
                    normalized_x = 1.0f;
                } 

                sqrt_val = 1.0f - (normalized_x * normalized_x);
                if (sqrt_val < 0.0f){
                    sqrt_val = 0.0f;
                } 

                dy = radius * sqrt(sqrt_val);
                y_top = cy - (int16_t)(dy);
                y_bottom = cy + (int16_t)(dy);

                if (y_bottom > y_top) {
                    cmd(ctx,cfg,FT800_COLOR_RGB(red, green, blue),cmdOffset);
                    cmd(ctx,cfg,FT800_BEGIN(FT800_RECTS),cmdOffset);
                    cmd(ctx,cfg,FT800_VERTEX2F(x1 * 16, y_top * 16),cmdOffset);
                    cmd(ctx,cfg,FT800_VERTEX2F(x2 * 16, y_bottom * 16),cmdOffset);
                    cmd(ctx,cfg,FT800_END(),cmdOffset);
                }
            }
        }
        else if(gradient==FT800_GRADIENT_LEFT_RIGHT){

            for (i = 0; i <= steps; i++) {
                t = (float)i / steps;

                red = rgb_convert(s_color,"red")+t*(rgb_convert(e_color,"red")-rgb_convert(s_color,"red"));
                green = rgb_convert(s_color,"green")+t*(rgb_convert(e_color,"green")-rgb_convert(s_color,"green"));
                blue = rgb_convert(s_color,"blue")+t*(rgb_convert(e_color,"blue")-rgb_convert(s_color,"blue"));
    
                x_offset = -radius + (2.0f * radius * t);
                x1 = cx + (int16_t)(x_offset);
                x2 = x1 + 1;  

                normalized_x = x_offset / radius;
                if (normalized_x < -1.0f){
                    normalized_x = -1.0f;
                } 
                if (normalized_x > 1.0f){
                    normalized_x = 1.0f;
                } 

                sqrt_val = 1.0f - (normalized_x * normalized_x);
                if (sqrt_val < 0.0f){
                    sqrt_val = 0.0f;
                } 

                dy = radius * sqrt(sqrt_val);
                y_top = cy - (int16_t)(dy);
                y_bottom = cy + (int16_t)(dy);

                if (y_bottom > y_top) {
                    cmd(ctx,cfg,FT800_COLOR_RGB(red, green, blue),cmdOffset);
                    cmd(ctx,cfg,FT800_BEGIN(FT800_RECTS),cmdOffset);
                    cmd(ctx,cfg,FT800_VERTEX2F(x1 * 16, y_top * 16),cmdOffset);
                    cmd(ctx,cfg,FT800_VERTEX2F(x2 * 16, y_bottom * 16),cmdOffset);
                    cmd(ctx,cfg,FT800_END(),cmdOffset);
                }
            }
        }
        else if(gradient==FT800_GRADIENT_NONE){
            uint8_t red = rgb_convert(s_color, "red");
            uint8_t green = rgb_convert(s_color, "green");
            uint8_t blue = rgb_convert(s_color, "blue");
            cmd(ctx,cfg,FT800_COLOR_RGB(red, green, blue),cmdOffset);
            cmd(ctx,cfg,FT800_BEGIN(FT800_POINTS),cmdOffset);
            cmd(ctx,cfg,FT800_POINT_SIZE((uint16_t)((float)width/2.0)* 16),cmdOffset);
            cmd(ctx,cfg,FT800_VERTEX2F(cx * 16, cy * 16),cmdOffset);
            cmd(ctx,cfg,FT800_END(),cmdOffset);

        }

}


void draw_edges_ellipse(ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset,uint16_t cx, uint16_t cy,uint16_t width, uint16_t height,uint16_t pen_color, uint16_t pen_width) {

    float a = width / 2.0f;
    float b = height / 2.0f;

    cmd(ctx, cfg, FT800_COLOR_RGB(rgb_convert(pen_color, "red"),rgb_convert(pen_color, "green"),rgb_convert(pen_color, "blue")), cmdOffset);

    cmd(ctx, cfg, FT800_LINE_WIDTH(pen_width * 16), cmdOffset);

    cmd(ctx, cfg, FT800_BEGIN(FT800_LINE_STRIP), cmdOffset);

    uint16_t segments = 100;

    for (uint16_t i = 0; i <= segments; i++) {
        float theta = (2.0f * 3.14159f * i) / segments;
        float x = cx + a * cosf(theta);
        float y = cy + b * sinf(theta);

        cmd(ctx, cfg, FT800_VERTEX2F((uint16_t)(x * 16), (uint16_t)(y * 16)), cmdOffset);
    }

    cmd(ctx, cfg, FT800_END(), cmdOffset);
}



void draw_gradient_ellipse(ft800_t *ctx, ft800_cfg_t *cfg,uint16_t *cmdOffset,uint16_t x, uint16_t y, uint16_t width, uint16_t height,uint16_t s_color,uint16_t e_color,ft800_gradient_style gradient) {
    
    uint8_t red,green,blue,a = width / 2,b = height / 2,steps = 100,i;
    float t1,t2,x1_offset,x2_offset,y1_offset,y2_offset,normalized_x1,normalized_x2,normalized_y1,normalized_y2,dx1,dx2,dy1,dy2;
   
    if(gradient==FT800_GRADIENT_TOP_BOTTOM){
        for (i = 0; i < steps; i++) {
            t1 = (float)i / steps;
            t2 = (float)(i + 1) / steps;

            red = rgb_convert(e_color,"red")+t1*(rgb_convert(s_color,"red")-rgb_convert(e_color,"red"));
            green = rgb_convert(e_color,"green")+t1*(rgb_convert(s_color,"green")-rgb_convert(e_color,"green"));
            blue = rgb_convert(e_color,"blue")+t1*(rgb_convert(s_color,"blue")-rgb_convert(e_color,"blue"));
            
        
            y1_offset = (2.0f * b) * (t1 - 0.5f);  
            y2_offset = (2.0f * b) * (t2 - 0.5f);

            normalized_y1 = y1_offset / b;
            normalized_y2 = y2_offset / b;

            if (normalized_y1 < -1.0f){
                normalized_y1 = -1.0f;
            } 
            if (normalized_y1 > 1.0f){
                normalized_y1 = 1.0f;
            } 
            if (normalized_y2 < -1.0f){
                normalized_y2 = -1.0f;
            } 
            if (normalized_y2 > 1.0f){
                normalized_y2 = 1.0f;
            } 

            dx1 = a * sqrt(1.0f - normalized_y1 * normalized_y1);
            dx2 = a * sqrt(1.0f - normalized_y2 * normalized_y2);

            int16_t x_left1 = x - (int16_t)(dx1);
            int16_t x_right1 = x + (int16_t)(dx1);

            int16_t x_left2 = x - (int16_t)(dx2);
            int16_t x_right2 = x + (int16_t)(dx2);

            int16_t y1 = y + (int16_t)(y1_offset);
            int16_t y2 = y + (int16_t)(y2_offset);

            if (x_right1 > x_left1 && y2 != y1) {
                cmd(ctx,cfg,FT800_COLOR_RGB(red, green, blue),cmdOffset);
                cmd(ctx,cfg,FT800_BEGIN(FT800_RECTS),cmdOffset);
                cmd(ctx,cfg,FT800_VERTEX2F(x_left1 * 16, y1 * 16),cmdOffset);
                cmd(ctx,cfg,FT800_VERTEX2F(x_right1 * 16, y2 * 16),cmdOffset);
                cmd(ctx,cfg,FT800_END(),cmdOffset);
            }
        }
    }
    else if(gradient==FT800_GRADIENT_BOTTOM_TOP){
        for (i = 0; i < steps; i++) {
            t1 = (float)i / steps;
            t2 = (float)(i + 1) / steps;

            red = rgb_convert(s_color,"red")+t1*(rgb_convert(e_color,"red")-rgb_convert(s_color,"red"));
            green = rgb_convert(s_color,"green")+t1*(rgb_convert(e_color,"green")-rgb_convert(s_color,"green"));
            blue = rgb_convert(s_color,"blue")+t1*(rgb_convert(e_color,"blue")-rgb_convert(s_color,"blue"));
            
        
            y1_offset = (2.0f * b) * (t1 - 0.5f);  
            y2_offset = (2.0f * b) * (t2 - 0.5f);

            normalized_y1 = y1_offset / b;
            normalized_y2 = y2_offset / b;

            if (normalized_y1 < -1.0f){
                normalized_y1 = -1.0f;
            } 
            if (normalized_y1 > 1.0f){
                normalized_y1 = 1.0f;
            } 
            if (normalized_y2 < -1.0f){
                normalized_y2 = -1.0f;
            } 
            if (normalized_y2 > 1.0f){
                normalized_y2 = 1.0f;
            } 

            dx1 = a * sqrt(1.0f - normalized_y1 * normalized_y1);
            dx2 = a * sqrt(1.0f - normalized_y2 * normalized_y2);

            int16_t x_left1 = x - (int16_t)(dx1);
            int16_t x_right1 = x + (int16_t)(dx1);

            int16_t x_left2 = x - (int16_t)(dx2);
            int16_t x_right2 = x + (int16_t)(dx2);

            int16_t y1 = y + (int16_t)(y1_offset);
            int16_t y2 = y + (int16_t)(y2_offset);

            if (x_right1 > x_left1 && y2 != y1) {
                cmd(ctx,cfg,FT800_COLOR_RGB(red, green, blue),cmdOffset);
                cmd(ctx,cfg,FT800_BEGIN(FT800_RECTS),cmdOffset);
                cmd(ctx,cfg,FT800_VERTEX2F(x_left1 * 16, y1 * 16),cmdOffset);
                cmd(ctx,cfg,FT800_VERTEX2F(x_right1 * 16, y2 * 16),cmdOffset);
                cmd(ctx,cfg,FT800_END(),cmdOffset);
            }
        }
    }
    else if(gradient==FT800_GRADIENT_LEFT_RIGHT){
        for (i = 0; i < steps; i++) {
            t1 = (float)i / steps;
            t2 = (float)(i + 1) / steps;

            red = rgb_convert(e_color,"red")+t1*(rgb_convert(s_color,"red")-rgb_convert(e_color,"red"));
            green = rgb_convert(e_color,"green")+t1*(rgb_convert(s_color,"green")-rgb_convert(e_color,"green"));
            blue = rgb_convert(e_color,"blue")+t1*(rgb_convert(s_color,"blue")-rgb_convert(e_color,"blue"));

            x1_offset = (2.0f * a) * (t1 - 0.5f); 
            x2_offset = (2.0f * a) * (t2 - 0.5f);

            normalized_x1 = x1_offset / a;
            normalized_x2 = x2_offset / a;

            if (normalized_x1 < -1.0f){
                normalized_x1 = -1.0f;
            } 
            if (normalized_x1 > 1.0f){
                normalized_x1 = 1.0f;
            } 
            if (normalized_x2 < -1.0f){
                normalized_x2 = 1.0f;
            } 
            if (normalized_x2 > 1.0f){
                normalized_x2 = 1.0f;
            } 

            dy1 = b * sqrt(1.0f - normalized_x1 * normalized_x1);
            dy2 = b * sqrt(1.0f - normalized_x2 * normalized_x2);

            int16_t y_top1 = y - (int16_t)(dy1);
            int16_t y_bottom1 = y + (int16_t)(dy1);

            int16_t y_top2 = y - (int16_t)(dy2);
            int16_t y_bottom2 = y + (int16_t)(dy2);

            int16_t x1 = x + (int16_t)(x1_offset);
            int16_t x2 = x + (int16_t)(x2_offset);

            if (y_bottom1 > y_top1 && x2 != x1) {
                cmd(ctx,cfg,FT800_COLOR_RGB(red, green, blue),cmdOffset);
                cmd(ctx,cfg,FT800_BEGIN(FT800_RECTS),cmdOffset);
                cmd(ctx,cfg,FT800_VERTEX2F(x1 * 16, y_top1 * 16),cmdOffset);
                cmd(ctx,cfg,FT800_VERTEX2F(x2 * 16, y_bottom1 * 16),cmdOffset);
                cmd(ctx,cfg,FT800_END(),cmdOffset);
            }
        }
    }
    else if(gradient==FT800_GRADIENT_RIGHT_LEFT){
        for (i = 0; i < steps; i++) {
            t1 = (float)i / steps;
            t2 = (float)(i + 1) / steps;

            red = rgb_convert(s_color,"red")+t1*(rgb_convert(e_color,"red")-rgb_convert(s_color,"red"));
            green = rgb_convert(s_color,"green")+t1*(rgb_convert(e_color,"green")-rgb_convert(s_color,"green"));
            blue = rgb_convert(s_color,"blue")+t1*(rgb_convert(e_color,"blue")-rgb_convert(s_color,"blue"));

            x1_offset = (2.0f * a) * (t1 - 0.5f); 
            x2_offset = (2.0f * a) * (t2 - 0.5f);

            normalized_x1 = x1_offset / a;
            normalized_x2 = x2_offset / a;

            if (normalized_x1 < -1.0f){
                normalized_x1 = -1.0f;
            } 
            if (normalized_x1 > 1.0f){
                normalized_x1 = 1.0f;
            } 
            if (normalized_x2 < -1.0f){
                normalized_x2 = 1.0f;
            } 
            if (normalized_x2 > 1.0f){
                normalized_x2 = 1.0f;
            } 

            dy1 = b * sqrt(1.0f - normalized_x1 * normalized_x1);
            dy2 = b * sqrt(1.0f - normalized_x2 * normalized_x2);

            int16_t y_top1 = y - (int16_t)(dy1);
            int16_t y_bottom1 = y + (int16_t)(dy1);

            int16_t y_top2 = y - (int16_t)(dy2);
            int16_t y_bottom2 = y + (int16_t)(dy2);

            int16_t x1 = x + (int16_t)(x1_offset);
            int16_t x2 = x + (int16_t)(x2_offset);

            if (y_bottom1 > y_top1 && x2 != x1) {
                cmd(ctx,cfg,FT800_COLOR_RGB(red, green, blue),cmdOffset);
                cmd(ctx,cfg,FT800_BEGIN(FT800_RECTS),cmdOffset);
                cmd(ctx,cfg,FT800_VERTEX2F(x1 * 16, y_top1 * 16),cmdOffset);
                cmd(ctx,cfg,FT800_VERTEX2F(x2 * 16, y_bottom1 * 16),cmdOffset);
                cmd(ctx,cfg,FT800_END(),cmdOffset);
            }
        }
    }
    else if(gradient==FT800_GRADIENT_NONE){
        for (i = 0; i < steps; i++) {
            t1 = (float)i / steps;
            t2 = (float)(i + 1) / steps;

            red = rgb_convert(e_color, "red");
            green = rgb_convert(e_color, "green");
            blue = rgb_convert(e_color, "blue");
            
        
            y1_offset = (2.0f * b) * (t1 - 0.5f);  
            y2_offset = (2.0f * b) * (t2 - 0.5f);

            normalized_y1 = y1_offset / b;
            normalized_y2 = y2_offset / b;

            if (normalized_y1 < -1.0f){
                normalized_y1 = -1.0f;
            } 
            if (normalized_y1 > 1.0f){
                normalized_y1 = 1.0f;
            } 
            if (normalized_y2 < -1.0f){
                normalized_y2 = -1.0f;
            } 
            if (normalized_y2 > 1.0f){
                normalized_y2 = 1.0f;
            } 

            dx1 = a * sqrt(1.0f - normalized_y1 * normalized_y1);
            dx2 = a * sqrt(1.0f - normalized_y2 * normalized_y2);

            int16_t x_left1 = x - (int16_t)(dx1);
            int16_t x_right1 = x + (int16_t)(dx1);

            int16_t x_left2 = x - (int16_t)(dx2);
            int16_t x_right2 = x + (int16_t)(dx2);

            int16_t y1 = y + (int16_t)(y1_offset);
            int16_t y2 = y + (int16_t)(y2_offset);

            if (x_right1 > x_left1 && y2 != y1) {
                cmd(ctx,cfg,FT800_COLOR_RGB(red, green, blue),cmdOffset);
                cmd(ctx,cfg,FT800_BEGIN(FT800_RECTS),cmdOffset);
                cmd(ctx,cfg,FT800_VERTEX2F(x_left1 * 16, y1 * 16),cmdOffset);
                cmd(ctx,cfg,FT800_VERTEX2F(x_right1 * 16, y2 * 16),cmdOffset);
                cmd(ctx,cfg,FT800_END(),cmdOffset);
            }
        }

    }
    
}

void draw_edges_rectangle(ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset,uint16_t x1, uint16_t y1, uint16_t width, uint16_t height,uint16_t radius, uint16_t color, uint8_t pen_width) {
    
    uint8_t red = rgb_convert(color, "red");
    uint8_t green = rgb_convert(color, "green");
    uint8_t blue = rgb_convert(color, "blue");

    uint16_t x2 = x1 + width,y2 = y1 + height;
    uint8_t i, segments = 10;
    float theta;


    radius = radius * 2;

    if (radius > width / 2){
        radius = width / 2;
    } 
    if (radius > height / 2){
        radius = height / 2;
    } 

    cmd(ctx, cfg, FT800_COLOR_RGB(red, green, blue), cmdOffset);
    cmd(ctx, cfg, FT800_LINE_WIDTH(pen_width * 16), cmdOffset);

    cmd(ctx, cfg, FT800_BEGIN(FT800_LINES), cmdOffset);

    cmd(ctx, cfg, FT800_VERTEX2F((x1 + radius) * 16, y1 * 16), cmdOffset);
    cmd(ctx, cfg, FT800_VERTEX2F((x2 - radius) * 16, y1 * 16), cmdOffset);

    cmd(ctx, cfg, FT800_VERTEX2F((x1 + radius) * 16, y2 * 16), cmdOffset);
    cmd(ctx, cfg, FT800_VERTEX2F((x2 - radius) * 16, y2 * 16), cmdOffset);

    cmd(ctx, cfg, FT800_VERTEX2F(x1 * 16, (y1 + radius) * 16), cmdOffset);
    cmd(ctx, cfg, FT800_VERTEX2F(x1 * 16, (y2 - radius) * 16), cmdOffset);

    cmd(ctx, cfg, FT800_VERTEX2F(x2 * 16, (y1 + radius) * 16), cmdOffset);
    cmd(ctx, cfg, FT800_VERTEX2F(x2 * 16, (y2 - radius) * 16), cmdOffset);

    cmd(ctx, cfg, FT800_END(), cmdOffset);


    cmd(ctx, cfg, FT800_BEGIN(FT800_LINE_STRIP), cmdOffset);
    for (i = 0; i <= segments; i++) {
        theta = (M_PI / 2.0f) * (i / (float)segments);
        uint16_t x = (uint16_t)(x1 + radius - radius * cosf(theta));
        uint16_t y = (uint16_t)(y1 + radius - radius * sinf(theta));
        cmd(ctx, cfg, FT800_VERTEX2F(x * 16, y * 16), cmdOffset);
    }
    cmd(ctx, cfg, FT800_END(), cmdOffset);

    cmd(ctx, cfg, FT800_BEGIN(FT800_LINE_STRIP), cmdOffset);
    for (i = 0; i <= segments; i++) {
        theta = (M_PI / 2.0f) * (i / (float)segments);
        uint16_t x = (uint16_t)(x2 - radius + radius * sinf(theta));
        uint16_t y = (uint16_t)(y1 + radius - radius * cosf(theta));
        cmd(ctx, cfg, FT800_VERTEX2F(x * 16, y * 16), cmdOffset);
    }
    cmd(ctx, cfg, FT800_END(), cmdOffset);

    cmd(ctx, cfg, FT800_BEGIN(FT800_LINE_STRIP), cmdOffset);
    for (i = 0; i <= segments; i++) {
        theta = (M_PI / 2.0f) * (i / (float)segments);
        uint16_t x = (uint16_t)(x2 - radius + radius * cosf(theta));
        uint16_t y = (uint16_t)(y2 - radius + radius * sinf(theta));
        cmd(ctx, cfg, FT800_VERTEX2F(x * 16, y * 16), cmdOffset);
    }
    cmd(ctx, cfg, FT800_END(), cmdOffset);

    cmd(ctx, cfg, FT800_BEGIN(FT800_LINE_STRIP), cmdOffset);
    for (i = 0; i <= segments; i++) {
        theta = (M_PI / 2.0f) * (i / (float)segments);
        uint16_t x = (uint16_t)(x1 + radius - radius * sinf(theta));
        uint16_t y = (uint16_t)(y2 - radius + radius * cosf(theta));
        cmd(ctx, cfg, FT800_VERTEX2F(x * 16, y * 16), cmdOffset);
    }
    cmd(ctx, cfg, FT800_END(), cmdOffset);
}

void draw_gradient_rectangle(ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset,uint16_t x1, uint16_t y1, uint16_t width, uint16_t height,uint16_t radius, uint16_t s_color, uint16_t e_color,ft800_gradient_style gradient) {
    
    uint8_t red, green, blue;
    uint16_t x2 = x1 + width,y2 = y1 + height,i,y_start,y_end,shrink,x_left,x_right,x,x_end,y_top,y_bottom,steps;
    float dy,dx,t;

    if (radius > width / 2){
        radius = width / 2;
    } 
    if (radius > height / 2){
        radius = height / 2;
    } 

    if(gradient==FT800_GRADIENT_TOP_BOTTOM||gradient==FT800_GRADIENT_BOTTOM_TOP){
        steps=height;
    }
    else{
        steps=width;
    }

    if (gradient == FT800_GRADIENT_BOTTOM_TOP) { 
        for (i = 0; i <= steps; i++) {
            t = (float)i / steps;

            red = rgb_convert(e_color,"red")+t*(rgb_convert(s_color,"red")-rgb_convert(e_color,"red"));
            green = rgb_convert(e_color,"green")+t*(rgb_convert(s_color,"green")-rgb_convert(e_color,"green"));
            blue = rgb_convert(e_color,"blue")+t*(rgb_convert(s_color,"blue")-rgb_convert(e_color,"blue"));

            y_start = y1 + i;
            y_end = y_start + 1;

            shrink = 0;
            if (y_start < y1 + radius) {
                dy = (float)(radius - (y_start - y1));
                shrink = radius - (uint16_t)(sqrt(radius * radius - dy * dy));
            } else if (y_start > y2 - radius) {
                dy = (float)(y_start - (y2 - radius));
                shrink = radius - (uint16_t)(sqrt(radius * radius - dy * dy));
            }

            x_left = x1 + shrink;
            x_right = x2 - shrink;

            if (x_right > x_left) {
                cmd(ctx, cfg, FT800_COLOR_RGB(red, green, blue), cmdOffset);
                cmd(ctx, cfg, FT800_BEGIN(FT800_RECTS), cmdOffset);
                cmd(ctx, cfg, FT800_VERTEX2F(x_left * 16, y_start * 16), cmdOffset);
                cmd(ctx, cfg, FT800_VERTEX2F(x_right * 16, y_end * 16), cmdOffset);
                cmd(ctx, cfg, FT800_END(), cmdOffset);
            }
        }
    }

    else if (gradient == FT800_GRADIENT_TOP_BOTTOM) { 
        for (i = 0; i <= steps; i++) {
            t = (float)i / steps;

            red = rgb_convert(s_color,"red")+t*(rgb_convert(e_color,"red")-rgb_convert(s_color,"red"));
            green = rgb_convert(s_color,"green")+t*(rgb_convert(e_color,"green")-rgb_convert(s_color,"green"));
            blue = rgb_convert(s_color,"blue")+t*(rgb_convert(e_color,"blue")-rgb_convert(s_color,"blue"));

            y_start = y1 + i;
            y_end = y_start + 1;

            shrink = 0;
            if (y_start < y1 + radius) {
                dy = (float)(radius - (y_start - y1));
                shrink = radius - (uint16_t)(sqrt(radius * radius - dy * dy));
            } else if (y_start > y2 - radius) {
                dy = (float)(y_start - (y2 - radius));
                shrink = radius - (uint16_t)(sqrt(radius * radius - dy * dy));
            }

            x_left = x1 + shrink;
            x_right = x2 - shrink;

            if (x_right > x_left) {
                cmd(ctx, cfg, FT800_COLOR_RGB(red, green, blue), cmdOffset);
                cmd(ctx, cfg, FT800_BEGIN(FT800_RECTS), cmdOffset);
                cmd(ctx, cfg, FT800_VERTEX2F(x_left * 16, y_start * 16), cmdOffset);
                cmd(ctx, cfg, FT800_VERTEX2F(x_right * 16, y_end * 16), cmdOffset);
                cmd(ctx, cfg, FT800_END(), cmdOffset);
            }
        }
    }

    else if (gradient == FT800_GRADIENT_RIGHT_LEFT) {  
        for (i = 0; i <= steps; i++) {
            t = (float)i / steps;

            red = rgb_convert(e_color,"red")+t*(rgb_convert(s_color,"red")-rgb_convert(e_color,"red"));
            green = rgb_convert(e_color,"green")+t*(rgb_convert(s_color,"green")-rgb_convert(e_color,"green"));
            blue = rgb_convert(e_color,"blue")+t*(rgb_convert(s_color,"blue")-rgb_convert(e_color,"blue"));

            x = x1 + i;
            x_end = x + 1;

            shrink = 0;
            if (x < x1 + radius) {
                dx = (float)(radius - (x - x1));
                shrink = radius - (uint16_t)(sqrt(radius * radius - dx * dx));
            } else if (x > x2 - radius) {
                dx = (float)(x - (x2 - radius));
                shrink = radius - (uint16_t)(sqrt(radius * radius - dx * dx));
            }

            uint16_t y_top = y1 + shrink;
            uint16_t y_bottom = y2 - shrink;

            if (y_bottom > y_top) {
                cmd(ctx, cfg, FT800_COLOR_RGB(red, green, blue), cmdOffset);
                cmd(ctx, cfg, FT800_BEGIN(FT800_RECTS), cmdOffset);
                cmd(ctx, cfg, FT800_VERTEX2F(x * 16, y_top * 16), cmdOffset);
                cmd(ctx, cfg, FT800_VERTEX2F(x_end * 16, y_bottom * 16), cmdOffset);
                cmd(ctx, cfg, FT800_END(), cmdOffset);
            }
        }
    }

    else if (gradient == FT800_GRADIENT_LEFT_RIGHT) { 
        for (i = 0; i <= steps; i++) {
            t = (float)i / steps;

            red = rgb_convert(s_color,"red")+t*(rgb_convert(e_color,"red")-rgb_convert(s_color,"red"));
            green = rgb_convert(s_color,"green")+t*(rgb_convert(e_color,"green")-rgb_convert(s_color,"green"));
            blue = rgb_convert(s_color,"blue")+t*(rgb_convert(e_color,"blue")-rgb_convert(s_color,"blue"));

            x = x1 + i;
            x_end = x + 1;

            shrink = 0;
            if (x < x1 + radius) {
                dx = (float)(radius - (x - x1));
                shrink = radius - (uint16_t)(sqrtf(radius * radius - dx * dx));
            } else if (x > x2 - radius) {
                dx = (float)(x - (x2 - radius));
                shrink = radius - (uint16_t)(sqrtf(radius * radius - dx * dx));
            }

            y_top = y1 + shrink;
            y_bottom = y2 - shrink;

            if (y_bottom > y_top) {
                cmd(ctx, cfg, FT800_COLOR_RGB(red, green, blue), cmdOffset);
                cmd(ctx, cfg, FT800_BEGIN(FT800_RECTS), cmdOffset);
                cmd(ctx, cfg, FT800_VERTEX2F(x * 16, y_top * 16), cmdOffset);
                cmd(ctx, cfg, FT800_VERTEX2F(x_end * 16, y_bottom * 16), cmdOffset);
                cmd(ctx, cfg, FT800_END(), cmdOffset);
            }
        }
    }
    else if(gradient==FT800_GRADIENT_NONE){
        for (i = 0; i <= steps; i++) {
            t = (float)i / steps;

            red = rgb_convert(e_color, "red");
            green = rgb_convert(e_color, "green");
            blue = rgb_convert(e_color, "blue");

            y_start = y1 + i;
            y_end = y_start + 1;

            shrink = 0;
            if (y_start < y1 + radius) {
                dy = (float)(radius - (y_start - y1));
                shrink = radius - (uint16_t)(sqrt(radius * radius - dy * dy));
            } else if (y_start > y2 - radius) {
                dy = (float)(y_start - (y2 - radius));
                shrink = radius - (uint16_t)(sqrt(radius * radius - dy * dy));
            }

            x_left = x1 + shrink;
            x_right = x2 - shrink;

            if (x_right > x_left) {
                cmd(ctx, cfg, FT800_COLOR_RGB(red, green, blue), cmdOffset);
                cmd(ctx, cfg, FT800_BEGIN(FT800_RECTS), cmdOffset);
                cmd(ctx, cfg, FT800_VERTEX2F(x_left * 16, y_start * 16), cmdOffset);
                cmd(ctx, cfg, FT800_VERTEX2F(x_right * 16, y_end * 16), cmdOffset);
                cmd(ctx, cfg, FT800_END(), cmdOffset);
            }
        }
    }
    
}


void draw_image_image(ft800_t *ctx,ft800_cfg_t *cfg,uint16_t *cmdOffset,ft800_image *image) {
    uint32_t addr_in_ramg=0x000000;
    uint32_t image_size_bytes=image->width*image->height*2+6;
    if (!ctx || !cfg || !image->picture_data || image_size_bytes == 0)
        return;

    uint32_t padding = addr_in_ramg % 4;
    if (padding > 0) {
        uint8_t pad[4] = {0};
        uint32_t pad_len = 4 - padding;
        ft800_write_ram_g(ctx, cfg, cmdOffset, addr_in_ramg, pad, pad_len);
        addr_in_ramg += pad_len;
    }

    ft800_write_ram_g(ctx, cfg, cmdOffset, addr_in_ramg, image->picture_data, image_size_bytes);

    cmd(ctx, cfg, FT800_BITMAP_HANDLE(0), cmdOffset);
    cmd(ctx, cfg, FT800_BITMAP_SOURCE(addr_in_ramg), cmdOffset);
    cmd(ctx, cfg, FT800_BITMAP_LAYOUT(7, image->width * 2, image->height), cmdOffset);
    cmd(ctx, cfg, FT800_BITMAP_SIZE(0, 0, 0, image->width, image->height), cmdOffset);

    cmd(ctx, cfg, FT800_BEGIN(FT800_BITMAPS), cmdOffset);
    cmd(ctx, cfg, FT800_VERTEX2F(image->left * 16, image->top * 16), cmdOffset);
    cmd(ctx, cfg, FT800_END(), cmdOffset);
}

void init_touch_screen(ft800_t *ctx, ft800_cfg_t *cfg,bool run_calibration) {

    uint16_t cmdOffset = 0;

    write_data(ctx,cfg, FT800_REG_TOUCH_MODE,0x00,8);

    Delay_ms(10);

    
    if (run_calibration) {
        cmd(ctx,cfg,FT800_CMD_DLSTART, &cmdOffset);
        cmd(ctx,cfg,FT800_CLEAR_COLOR_RGB(0, 0, 0), &cmdOffset);
        cmd(ctx,cfg,FT800_CLEAR(1, 1, 1), &cmdOffset);
        cmd_text(ctx,cfg,&cmdOffset, 80, 120, 27, 0,"Touch the dots to calibrate");
        cmd(ctx,cfg,FT800_CMD_CALIBRATE, &cmdOffset);
        cmd(ctx,cfg,FT800_CMD_SWAP, &cmdOffset);
        write_data(ctx,cfg, FT800_REG_CMD_WRITE,cmdOffset,16); 
    
        wait_coprocessor(ctx,cfg);
        Delay_ms(100);
    }

    
    write_data(ctx,cfg, FT800_REG_TOUCH_MODE,0x03,8); 

    write_data(ctx,cfg, FT800_REG_TOUCH_TAG,0x00,8);
}




// // ------------------------------------------------------------------------- END
