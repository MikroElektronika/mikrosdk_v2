#include <built_in.h>

// Externs
extern sfr unsigned long GLCD_DataPort_Input;
extern sfr unsigned long GLCD_DataPort_Output;

extern sfr sbit GLCD_CS1,
                GLCD_CS2,
                GLCD_RS,
                GLCD_RW,
                GLCD_RST,
                GLCD_EN;
// Externs end

// statics
static unsigned short fontW, fontH;
static unsigned int fontOffset;
static code const char *fontDef;
static unsigned short FontInitialized;
static unsigned int ExternalFontSet;
// Write_To_Pins
static void Write_To_Pins(char ddata) {
  unsigned int temp;
  temp = GLCD_DataPort_Output & 0xFF00;
  GLCD_DataPort_Output = temp | ddata;
}

//-------------- Simply strobes the enable line
static void Strobe() {
  Delay_10us();  // zbog 3.3V sistema (istraziti sta je)
  GLCD_EN = 1;
  Delay_10us();
  GLCD_EN = 0;
}

//-------------- Select which page of the display to address (0 to 7)
void Glcd_Set_Page(unsigned short page) {

  GLCD_RS = 0;
  GLCD_RW = 0;
  //Lo(GLCD_DataPort) = page | 0xB8;
  Write_To_Pins(page | 0xB8);
  Strobe();
}

//-------------- Selects side of the GLCD screen (0 or 1)
void Glcd_Set_Side(unsigned short x_pos) {
  x_pos &= 0x7F;
  if (x_pos & 0x40) {
    GLCD_CS1 = 1;
    GLCD_CS2 = 0;
  } else {
    GLCD_CS1 = 0;
    GLCD_CS2 = 1;
  }
}

// Glcd_Set_X
void Glcd_Set_X(unsigned short x_pos) {

  x_pos &= 0x7F;
  GLCD_RS = 0;  // set RS on 0v
  GLCD_RW = 0;  // set RW  on 0v

  x_pos &= 0xBF;
  x_pos |= 0x40;

//  Lo(GLCD_DataPort) = x_pos;
  Write_To_Pins(x_pos);

  Strobe();
}

//-------------- Reads data at selected page (0-7)  and y_pos (0-127)
unsigned short Glcd_Read_Data() {
  unsigned int local;
  //GLCD_DataPort_Direction = 0xFF; // set data port in input mode
  //PIC specific: izbaciti direction registar, za P18 je on na adresi PORT-a + 0x12
  // dsPIC specific : ovde ide -2 a ne -1 jer je GLCD_DataPort byte
  //  *(&GLCD_DataPort - 1) |= 0x00FF;  // set data port in input mode

  GPIO_Config(&GLCD_DataPort_Input, _GPIO_PINMASK_LOW, _GPIO_CFG_DIGITAL_INPUT);    // za  digitalni output


  Delay_1us();             // Ova kasnjenja su zbog kineskih GLCD-ova (anatema)
  Delay_1us();
  
  GLCD_RS = 1;  // set RS on 5v
  GLCD_EN = 0;
  GLCD_RW = 1;  // set RW on 5v

  GLCD_EN = 1;

  Delay_10us();            // Ova kasnjenja su zbog kineskih GLCD-ova (anatema)

  // AVR specific : Umesto obicnog citanja PORTx registra - cita se PINx registar, adresa je manja za 2
  //local =
  //        /* dereferenciranje */                       *
  //        /* castujemo u pointer na volatile */        (volatile char*)
  //        /* na desno je pointer na non-volatile */    ((&GLCD_DataPort) - 2);
  // eof AVR specific
  //  local = Lo(GLCD_DataPort);  // PIC specific
  local = GLCD_DataPort_Input;
  
  
  GLCD_EN = 0;
  GLCD_RW = 0; // set RW on 0v

  Delay_1us();             // Ova kasnjenja su zbog kineskih GLCD-ova (anatema)
  Delay_1us();

  //GLCD_DataPort_Direction = 0x00; // set data port back to output mode
  //PIC specific: izbaciti direction registar, za P18 je on na adresi PORT-a + 0x12
  // dsPIC specific : ovde ide -2 a ne -1 jer je GLCD_DataPort byte
  //  *(&GLCD_DataPort - 1) &= 0xFF00;  // set data port in output mode
  GPIO_Config(&GLCD_DataPort_Output, _GPIO_PINMASK_LOW, _GPIO_CFG_DIGITAL_OUTPUT);    // za  digitalni output

  return local;
}

//-------------- Writes data to data port
void Glcd_Write_Data(unsigned short ddata) {

  GLCD_EN = 0;  // set display ON
  GLCD_RS = 1;  // set RS on 5v
  GLCD_RW = 0;  // set RW on 0v

  //  Lo(GLCD_DataPort) = ddata;
  Write_To_Pins(ddata);
  
  Strobe();
}

//-------------- Clears the screen
void Glcd_Fill(unsigned short pattern) {
  unsigned int yy, page;

  GLCD_CS1 = 0;
  GLCD_CS2 = 1;  // set CS1 on 0v and CS2 on 5v

  for (page = 0; page <= 7u; page++) {
    Glcd_Set_Page(page);
//    Delay_10us();
    for (yy = 0; yy <= 63u; yy++) {
      Glcd_Write_Data(pattern);
//      Delay_10us();
    }
  }

  GLCD_CS2 = 0; GLCD_CS1 = 1;  // set CS1 on 5v and CS2 on 0v
  for (page = 0; page <= 7u; page++) {
    Glcd_Set_Page(page);
    for (yy = 0; yy <= 63u; yy++)
      Glcd_Write_Data(pattern);
  }
}

//-------------- Performs the initialization of the GLCD
void Glcd_Init() {
  FontInitialized = 0; // po default nije inicijalizovan
  ExternalFontSet = 0;
  // all control lines are output lines
    asm {
       MOVW  R0, #lo_addr(GLCD_RST)
       MOVT  R0, #hi_addr(GLCD_RST)    //data_bits
       MOV   R1, #1
       LSL   R1, R1, #bitPos(GLCD_RST)
    }
    GPIO_Config(R0, R1, _GPIO_CFG_DIGITAL_OUTPUT);    // za  digitalni output

    asm {
       MOVW  R0, #lo_addr(GLCD_EN)
       MOVT  R0, #hi_addr(GLCD_EN)    //data_bits
       MOV   R1, #1
       LSL   R1, R1, #bitPos(GLCD_EN)
    }
    GPIO_Config(R0, R1, _GPIO_CFG_DIGITAL_OUTPUT);    // za  digitalni output

    asm {
       MOVW  R0, #lo_addr(GLCD_RS)
       MOVT  R0, #hi_addr(GLCD_RS)    //data_bits
       MOV   R1, #1
       LSL   R1, R1, #bitPos(GLCD_RS)
    }
    GPIO_Config(R0, R1, _GPIO_CFG_DIGITAL_OUTPUT);    // za  digitalni output

    asm {
       MOVW  R0, #lo_addr(GLCD_RW)
       MOVT  R0, #hi_addr(GLCD_RW)    //data_bits
       MOV   R1, #1
       LSL   R1, R1, #bitPos(GLCD_RW)
    }
    GPIO_Config(R0, R1, _GPIO_CFG_DIGITAL_OUTPUT);    // za  digitalni output

    asm {
       MOVW  R0, #lo_addr(GLCD_CS1)
       MOVT  R0, #hi_addr(GLCD_CS1)    //data_bits
       MOV   R1, #1
       LSL   R1, R1, #bitPos(GLCD_CS1)
    }
    GPIO_Config(R0, R1, _GPIO_CFG_DIGITAL_OUTPUT);    // za  digitalni output

    asm {
       MOVW  R0, #lo_addr(GLCD_CS2)
       MOVT  R0, #hi_addr(GLCD_CS2)    //data_bits
       MOV   R1, #1
       LSL   R1, R1, #bitPos(GLCD_CS2)
    }
    GPIO_Config(R0, R1, _GPIO_CFG_DIGITAL_OUTPUT);    // za  digitalni output

// Dodatak da bi moglo da radi sa novijom verzijom vitaelko displejima  M� 20090630
  GLCD_RST = 0;

  //GLCD_DataPort = 0x00; // set data port as output
  //PIC specific: izbaciti direction registar, za P18 je on na adresi PORT-a + 0x12
  // dsPIC specific : ovde ide -2 a ne -1 jer je GLCD_DataPort byte
  //  *(&GLCD_DataPort - 1) &= 0xFF00;  // set data port in output mode
  GPIO_Config(&GLCD_DataPort_Output, 0xFF, _GPIO_CFG_DIGITAL_OUTPUT);    // za  digitalni output

// turn ON GLCD and set START line             // Ovo nam ne treba vise
  // GLCD_RST = 1; // set RST on 5v              // jer smo reset vec setovali gore u prvoj izmeni
  
  /* Delay_1us();  // Branin dodatak             //
  GLCD_RST := 0;   //   za vita-elko displeje    // Vise nisu potrebni ovi dilejevi
  Delay_1us();     //                            // reseno sa najnovijim pristupom M� 20090630
  GLCD_RST := 1;*/ //                            //
  
  GLCD_RS  = 0;  // set RS on 0v
  GLCD_RW  = 0;  // set RW  on 0v

  GLCD_CS1 = 0;  // set CS1 on 0v
  GLCD_CS2 = 1;  // set CS2 on 5v
  
  GLCD_RST = 1;  // Dodatak da bi moglo da radi sa novijom verzijom vitaelko
                 // displejima  M� 20090630
  
  Delay_1us();   // Dodat dilej jer je shvalerko(dsPIC) brz pa na nekim displejima
                 // potpuno odsece levu polovinu displeja        M� 20081118
                 // Prvobitno je bilo 10us, radi ok i sa 1us
                                                                              
// set display ON                                                               
//  Lo(GLCD_DataPort) = 0x3F;

  Write_To_Pins(0x3F);
  Strobe();
// set START line
//  Lo(GLCD_DataPort) = 0xC0;

  Write_To_Pins(0xC0);
  Strobe();

  GLCD_CS1 = 1; // set CS1 on 5v
  GLCD_CS2 = 0; // set CS2 on 0v
// set display ON
//  Lo(GLCD_DataPort) = 0x3F;

  Write_To_Pins(0x3F);
  Strobe();

// set START line
//  Lo(GLCD_DataPort) = 0xC0;

  Write_To_Pins(0xC0);
  Strobe();

}

//--------------- Changes font definition
void Glcd_Set_Font(const char *activeFont, unsigned short aFontWidth,
                   unsigned short aFontHeight, unsigned int aFontOffs) {
  fontDef = activeFont;
  fontOffset = aFontOffs;
  fontW = aFontWidth;
  fontH = aFontHeight;
  FontInitialized = 1;
}

//--------------- Writes sigle char on GLCD
void Glcd_Write_Char(unsigned short character,
                     unsigned short x_pos,
                     unsigned short page_num,
                     unsigned short color) {
  unsigned int ii;
  unsigned short data_read, font_ch, font_ch_inv;
  int pointer;

  if (page_num > 7)
    return;

  pointer = (character - fontOffset) * fontW;

  Glcd_Set_X(x_pos);
  Glcd_Set_Page(page_num);

  for (ii = 0; ii < fontW; ii++) {
    if (x_pos > 127)
      return;
  
    Glcd_Set_Side(x_pos);
    Glcd_Set_Page(page_num);
    Glcd_Set_X(x_pos);

    data_read = Glcd_Read_Data();
    data_read = Glcd_Read_Data();

    Glcd_Set_Side(x_pos);
    Glcd_Set_Page(page_num);
    Glcd_Set_X(x_pos);

// dodela u font_ch
    font_ch = fontDef[pointer++];
    font_ch_inv = ~font_ch;

// case po color
    switch (color) {
      case 0: data_read =  font_ch_inv; break;
      case 1: data_read =  font_ch; break;
      case 2: data_read ^= font_ch;
    }

    Glcd_Write_Data(data_read);
    x_pos++;
  }

  // last col (is empty)
  Glcd_Set_Side(x_pos);
  Glcd_Set_Page(page_num);
  Glcd_Set_X(x_pos);

  font_ch = 0xFF;
  font_ch_inv = 0;

  switch (color) {
    case 0:
      data_read = font_ch;
      Glcd_Write_Data(data_read);
      break;
    case 1:
      data_read = font_ch_inv;
      Glcd_Write_Data(data_read);
      break;
  }

}

//-------------- Writes string on GLCD
void Glcd_Write_Text(char *text, unsigned short x_pos,
                     unsigned short page_num, unsigned short color) {
                     
  unsigned int i;
  i = 0;

  if(FontInitialized == 0){    // ukoliko font nije inicijalizovan
  // Default font settings
    fontW = 5;
    fontH = 7;
    fontDef = font5x7;
    fontOffset = 32;
  }

// petlja za slanje
  while (text[i]) {
    Glcd_Write_Char(text[i], x_pos, page_num, color);
    x_pos += fontW + 1;
    i++;
  }
}

//-------------- Plots a dot on GLCD
void Glcd_Dot(unsigned short x_pos, unsigned short y_pos, unsigned short color) {
  unsigned short bit_mask1, bit_mask0;
  unsigned short ddata;
  
  if ( (x_pos < 0) || (x_pos > 127) || (y_pos < 0) || (y_pos > 63) )
    return;
    
// namestanje na poziciju
  Glcd_Set_Side(x_pos);
  Glcd_Set_Page(y_pos >> 3);  // 8 y pozicija idu u 1 page, delimo sa 8
  Glcd_Set_X(x_pos);
  Delay_10us();               // dsPIC specific

// cuveno duplo citanje iz GLCD datasheeta
  ddata = Glcd_Read_Data();
  Delay_10us();               // dsPIC specific
  ddata = Glcd_Read_Data();   // mora 2 puta, bila je neka frka sa GLCD datasheetom
  Delay_10us();               // dsPIC specific

  Glcd_Set_Page(y_pos >> 3);  // ovo nije visak
  Glcd_Set_X(x_pos);          //

  bit_mask1 = y_pos & 7;      // ostaviti donja 3 bita (info o poziciji unutar page)
  bit_mask1 = 1 << bit_mask1;
  bit_mask0 = ~bit_mask1;

// case po color
  switch (color) {
    case 0:
      ddata &= bit_mask0;
      break;
    case 1:
      ddata |= bit_mask1;
      break;
    case 2:
      ddata ^= bit_mask1;
  }

  Glcd_Write_Data(ddata);
}


//-------------- Draws a line on GLCD (Bersenham's algorithm)
void Glcd_Line(int x_start, int y_start,
               int x_end, int y_end,
               unsigned short color) {
  int dx, dy;
  int stepx, stepy;
  int fraction;

  if (x_start < 0)
    x_start = 0;
  if (x_start > 127)
    x_start = 127;
    
  if (x_end < 0)
    x_end = 0;
  if (x_end > 127)
    x_end = 127;

  if (y_start < 0)
    y_start = 0;
  if (y_start > 63)
    y_start = 63;
    
  if (y_end < 0)
    y_end = 0;
  if (y_end > 63)
    y_end = 63;

// razlike
  dx = x_end - x_start;
  dy = y_end - y_start;

// stepovi
  if (dx < 0) {
    dx = -dx;
    stepx = -1;
  } else {
    stepx = 1;
  }

  if (dy < 0) {
    dy = -dy;
    stepy = -1;
  }
  else {
    stepy = 1;
  }

  dx <<= 1;
  dy <<= 1;

  Glcd_Dot(x_start, y_start, color);

// dx > dy
  if (dx > dy) {
    fraction = dy - (dx >> 1);
    while (x_start != x_end) {
      if (fraction >= 0) {
        y_start += stepy;
        fraction -= dx;
      }
      x_start += stepx;
      fraction += dy;

      Glcd_Dot(x_start, y_start, color);
    }
  }
// dy > dx
  else {
    fraction = dx - (dy >> 1);
    while (y_start != y_end) {
      if (fraction >= 0) {
        x_start += stepx;
        fraction -= dy;
      }
      y_start += stepy;
      fraction += dx;
      Glcd_Dot(x_start, y_start, color);
    }
  }
}

//-------------- Draws a horizontal line
void Glcd_H_Line(unsigned short x_start, unsigned short x_end,
                 unsigned short y_pos, unsigned short color) {
  unsigned int loc;

  if ( (y_pos < 0) || (y_pos > 63) )
    return;

  if (x_start < 0)
    x_start = 0;
  if (x_start > 127)
    x_start = 127;

  if (x_end < 0)
    x_end = 0;
  if (x_end > 127)
    x_end = 127;

  if (x_start > x_end) {
    loc = x_start;
    x_start = x_end;
    x_end = loc;
  }

  while (x_start <= x_end) {
    Glcd_Dot(x_start, y_pos, color);
    x_start++;
  }
}

//-------------- Draws a vertical line
void Glcd_V_Line(unsigned short y_start, unsigned short y_end,
                 unsigned short x_pos, unsigned short color) {
  unsigned int loc;

  if ( (x_pos < 0) || (x_pos > 127) )
    return;

  if (y_start < 0)
    y_start = 0;
  if (y_start > 63)
    y_start = 63;

  if (y_end < 0)
    y_end = 0;
  if (y_end > 63)
    y_end = 63;

  if (y_start > y_end) {
    loc = y_start;
    y_start = y_end;
    y_end = loc;
  }

  while (y_start <= y_end) {
    Glcd_Dot(x_pos, y_start, color);
    y_start++;
  }
}

//-------------- Draws a circle
void Glcd_Circle(int x_center, int y_center, int radius,
                 unsigned short color) {
  int tswitch,
      y, x, d;

  if(radius == 0) {
    Glcd_Dot(x_center, y_center,color);
    return;
  }

  x = 0;
  d  = y_center - x_center;
  y  = radius;
  tswitch  = y << 1;
  tswitch = 3 - tswitch;
  while (x < (y+1)) {

    Glcd_Dot(x_center + x, y_center + y,color);       //
    Glcd_Dot(x_center + x, y_center - y,color);       ////
    if(x > 0) {                                       //////  <<-----------------//
      Glcd_Dot(x_center - x, y_center + y,color);     ////                       //
      Glcd_Dot(x_center - x, y_center - y,color);     //                         //
    }                                                                            //
                                                                                 //
    // Ako ovo nije ispunjeno onda su ove tacke vec iscrtane ovde ---------------//
    if(x != y)
    {
    Glcd_Dot(y_center + y - d, y_center + x,color);
      Glcd_Dot(y_center - y - d, y_center + x,color);
      if(x > 0)
      {
    Glcd_Dot(y_center + y - d, y_center - x,color);
    Glcd_Dot(y_center - y - d, y_center - x,color);
      }
    }

    if (tswitch < 0)
      tswitch += (x << 2) + 6;
    else
    {
      tswitch += ((x - y) << 2) + 10;
      y--;
    }
    x++;
  }
}

void Glcd_Circle_Fill(int x_center, int y_center, int radius,
                      unsigned short color) {
  int tswitch, y, x, d, xOld, yOld;

  if(radius == 0) {
    Glcd_Dot(x_center, y_center,color);
    return;
  }

  x = 0;
  xOld = 0;
  y  = radius;
  yOld = radius;
  d  = y_center - x_center;
  tswitch  = y << 1;
  tswitch = 3 - tswitch;

  while (x < (y+1)) {

    Glcd_Line(x_center + x,     y_center + y, x_center + x,     y_center - y,color);
    if (x > 0)
      Glcd_Line(x_center - x,     y_center + y, x_center - x,     y_center - y,color);
    
    if(yOld != y) {
      Glcd_Line(y_center + yOld - d, y_center + xOld, y_center + yOld - d, y_center - xOld,color);
      if (yOld > 0)
        Glcd_Line(y_center - yOld - d, y_center + xOld, y_center - yOld - d, y_center - xOld,color);
      yOld = y;
    }
      
    if (tswitch < 0)
      tswitch += (x << 2) + 6;
    else {
      tswitch += ((x - y) << 2) + 10;
      y--;
      xOld = x;
    }
    x++;
  }

  if((x-1) != yOld) {
    Glcd_Line(y_center + yOld - d, y_center + xOld, y_center + yOld - d, y_center - xOld,color);
    if (yOld > 0)
      Glcd_Line(y_center - yOld - d, y_center + xOld, y_center - yOld - d, y_center - xOld,color);
  }
}

//-------------- Plots an image on GLCD
void Glcd_Image(code const unsigned short * image) {
  unsigned int col, pg;
  unsigned int  clan_niza;

  pg = 0;
  clan_niza = 0;
// while
  while (pg <= 7) {
    Glcd_Set_Side(0);                         // sets up CS1 and CS2
    Glcd_Set_Page(pg);
    Glcd_Set_X(0);
    for (col = 0; col <= 63u; col++) {
      Glcd_Write_Data(image[clan_niza++]);
    }

    Glcd_Set_Side(64);                        // sets up CS1 and CS2
    Glcd_Set_Page(pg);
    Glcd_Set_X(64);
    for (col = 64; col <= 127u; col++) {
      Glcd_Write_Data(image[clan_niza++]);
    }

    pg++;
  }
}

//-------------- Draws a rectangle
void Glcd_Rectangle(unsigned short x_upper_left,unsigned short y_upper_left,
                    unsigned short x_bottom_right,unsigned short y_bottom_right,
                    unsigned short color) {

  Glcd_H_Line(x_upper_left  ,x_bottom_right  ,y_upper_left  ,color);
  Glcd_H_Line(x_upper_left  ,x_bottom_right  ,y_bottom_right,color);
  Glcd_V_Line(y_upper_left  ,y_bottom_right  ,x_upper_left  ,color);
  Glcd_V_Line(y_upper_left  ,y_bottom_right  ,x_bottom_right,color);
}

void Glcd_Rectangle_Round_Edges(unsigned short x_upper_left,   unsigned short y_upper_left,
                                unsigned short x_bottom_right, unsigned short y_bottom_right,
                                unsigned short round_radius,   unsigned short color) {
int tswitch, y, x, d1, d2, d3, d4, margina;

  // ako je rastojanje izmedju dve x kordinate manje od 2*radius krivine
  // znaci nije moguce iscrtati -> exit
  margina = x_upper_left-x_bottom_right;
  if (margina < 0) {
    if (-margina < 2*round_radius)
      return;
  }
  else {
    if (margina < 2*round_radius)
      return;
  }
  // isto vazi i za y kordinate
  margina = y_upper_left-y_bottom_right;
  if (margina < 0) {
    if (-margina < 2*round_radius)
      return;
  }
  else {
    if (margina < 2*round_radius)
      return;
  }

  Glcd_H_Line(x_upper_left+round_radius + 1, x_bottom_right-round_radius - 1, y_upper_left, color);
  Glcd_H_Line(x_upper_left+round_radius + 1, x_bottom_right-round_radius - 1, y_bottom_right, color);
  Glcd_V_Line(y_upper_left+round_radius + 1, y_bottom_right-round_radius - 1, x_upper_left, color);
  Glcd_V_Line(y_upper_left+round_radius + 1, y_bottom_right-round_radius - 1, x_bottom_right, color);

  x = 0;
  d1 = (y_upper_left + round_radius) - (x_bottom_right - round_radius);
  d2 = (y_upper_left + round_radius) - (x_upper_left + round_radius);
  d3 = (y_bottom_right - round_radius) - (x_upper_left + round_radius);
  d4 = (y_bottom_right - round_radius) - (x_bottom_right - round_radius);

  y  = round_radius;
  tswitch  = y << 1;
  tswitch = 3 - tswitch;
  while (x < (y+1)) {
    Glcd_Dot((x_upper_left + round_radius) - x,     (y_bottom_right - round_radius) + y,color);     // 31
    Glcd_Dot((x_bottom_right - round_radius) + x,     (y_bottom_right - round_radius) + y,color);   // 41
    Glcd_Dot((x_upper_left + round_radius) - x,     (y_upper_left + round_radius) - y,color);       // 21
    Glcd_Dot((x_bottom_right - round_radius) + x,     (y_upper_left + round_radius) - y,color);     // 11

    if(x != y) {
    Glcd_Dot((y_bottom_right - round_radius) + y - d4, (y_bottom_right - round_radius) + x,color);  // 42
    Glcd_Dot((y_bottom_right - round_radius) - y - d3, (y_bottom_right - round_radius) + x,color);  // 32
    Glcd_Dot((y_upper_left + round_radius) - y - d2, (y_upper_left + round_radius) - x,color);      // 22
    Glcd_Dot((y_upper_left + round_radius) + y - d1, (y_upper_left + round_radius) - x,color);      // 12
    }

    if (tswitch < 0) {
      tswitch += (x << 2) + 6;
    }
    else {
      tswitch += ((x - y) << 2) + 10;
      y--;
    }
    x++;
  }
}

//-------------- Draws a box
void Glcd_Box(unsigned short x_upper_left, unsigned short y_upper_left,
              unsigned short x_bottom_right, unsigned short y_bottom_right,
              unsigned short color) {
  unsigned int loc;

 for (loc = y_upper_left; loc <= y_bottom_right; loc++)
   Glcd_H_Line(x_upper_left,x_bottom_right,loc  ,color);
}

void Glcd_Rectangle_Round_Edges_Fill(unsigned short x_upper_left,   unsigned short y_upper_left,
                                     unsigned short x_bottom_right, unsigned short y_bottom_right,
                                     unsigned short round_radius,   unsigned short color) {
int tswitch, y, x, d1, d2, d3, d4, margina, xOld, yOld;

  // ako je rastojanje izmedju dve x kordinate manje od 2*radius krivine
  // znaci nije moguce iscrtati -> exit
  margina = x_upper_left-x_bottom_right;
  if (margina < 0) {
    if (-margina < 2*round_radius)
      return;
  }
  else {
    if (margina < 2*round_radius)
      return;
  }
  // isto vazi i za y kordinate
  margina = y_upper_left-y_bottom_right;
  if (margina < 0) {
    if (-margina < 2*round_radius)
      return;
  }
  else {
    if (margina < 2*round_radius)
      return;
  }
  
  Glcd_Box(x_upper_left, y_upper_left+round_radius + 1, x_bottom_right, y_bottom_right-round_radius - 1, color);

  x = 0;
  xOld = 0;
  d1 = (y_upper_left + round_radius) - (x_bottom_right - round_radius);
  d2 = (y_upper_left + round_radius) - (x_upper_left + round_radius);
  d3 = (y_bottom_right - round_radius) - (x_upper_left + round_radius);
  d4 = (y_bottom_right - round_radius) - (x_bottom_right - round_radius);

  y  = round_radius;
  yOld = y;
  tswitch  = y << 1;
  tswitch = 3 - tswitch;
  while (x < (y+1)) {

    if(yOld != y) {
      Glcd_Line((x_upper_left + round_radius) - xOld, (y_bottom_right - round_radius) + yOld,
                (x_bottom_right - round_radius) + xOld, (y_bottom_right - round_radius) + yOld, color);
      Glcd_Line((x_upper_left + round_radius) - xOld, (y_upper_left + round_radius) - yOld,
                (x_bottom_right - round_radius) + xOld, (y_upper_left + round_radius) - yOld,color);
      yOld = y;
    }

    Glcd_Line((y_bottom_right - round_radius) + y - d4, (y_bottom_right - round_radius) + x, 
              (y_bottom_right - round_radius) - y - d3, (y_bottom_right - round_radius) + x,color);
    Glcd_Line((y_upper_left + round_radius) - y - d2, (y_upper_left + round_radius) - x, 
              (y_upper_left + round_radius) + y - d1, (y_upper_left + round_radius) - x,color);

    if (tswitch < 0) {
      tswitch += (x << 2) + 6;
    }
    else {
      tswitch += ((x - y) << 2) + 10;
      y--;
      xOld = x;
    }
    x++;
  }
  if((x-1) != yOld) {
    Glcd_Line((x_upper_left + round_radius) - xOld, (y_bottom_right - round_radius) + yOld, (x_bottom_right - round_radius) + xOld, (y_bottom_right - round_radius) + yOld, color);
    Glcd_Line((x_upper_left + round_radius) - xOld, (y_upper_left + round_radius) - yOld, (x_bottom_right - round_radius) + xOld, (y_upper_left + round_radius) - yOld,color);
  }
}



// Miletina f-ja
void Glcd_PartialImage(unsigned int x_left, unsigned int y_top,
                       unsigned int width, unsigned int height,
                       unsigned int picture_width, unsigned int picture_height, code const unsigned short * image) {
  char start_page, end_page, wdata, rdata, top_pomeraj, end_pomeraj, tmp, picture_end_page;
  // prvo sirina pa visina, nizi pa visi bajt
  unsigned int i, j, row_ind, row_ind_prev;
  unsigned int cnt, max_index;
  char prev_data, curr_data;

  i = 0;
  j = 0;
  row_ind = 0;
  row_ind_prev = 0;

  if ((x_left + width - 1) > 127) width = 128 - x_left;
  if ((y_top + height - 1) > 63) height = 64 - y_top;

  start_page = y_top / 8;
  end_page = (y_top + height - 1) / 8;

  top_pomeraj = y_top % 8;
  end_pomeraj = (y_top + height) % 8;

  if (picture_height > height) picture_end_page = end_page;
  else picture_end_page = (y_top + picture_height - 1) / 8;

  if(picture_height % 8 == 0)
    max_index = (picture_height / 8) * picture_width;
  else
    max_index = ((picture_height / 8) + 1) * picture_width;

  for (i = start_page; i <= end_page; i++) {
    cnt = 0;
    for (j = 0; j < width; j++) {
      Glcd_Set_Side(x_left + j); // setuje se side, ovo bi moglo optimalnije, da se izbaci u gornu petlju, al' onda treba provera kada se menja side
      Glcd_Set_Page(i); // setuje se page

      if (j < picture_width && i <= picture_end_page) {
        if (i == start_page)prev_data = 0;
        else prev_data = image[cnt + row_ind_prev];

        if (row_ind >= max_index) curr_data = 0;
        else curr_data = image[cnt + row_ind];
      } else {
        curr_data = 0;
        prev_data = 0;
      }

      wdata = curr_data; // ako nema pomeraja

      if (top_pomeraj > 0) { // ako slika ne pocinje na pocetku page-a  sacuvamo donji deo prelomnjenog bajta i siftujemo ulevo + gornji deo prelomljenog bajta
        wdata = (prev_data >> (8 - top_pomeraj)) | (curr_data << top_pomeraj);
      }

      if (i == start_page && top_pomeraj > 0) { // gornji page i ako slika ne pocinje na pocetku page-a
        Glcd_Set_X(x_left + j);
        rdata = Glcd_Read_Data();
        rdata = Glcd_Read_Data();
        tmp = rdata & (0xFF >> (8 - top_pomeraj));
        wdata = wdata & (0xFF << top_pomeraj);
        wdata = wdata | tmp;
      }

      if (i == end_page && end_pomeraj > 0) { // poslednji page i pomeraj odozdo
        Glcd_Set_X(x_left + j);
        rdata = Glcd_Read_Data();
        rdata = Glcd_Read_Data();
        tmp = rdata & (0xFF << end_pomeraj);
        wdata = wdata & (0xFF >> (8 - end_pomeraj));
        wdata = wdata | tmp;
      }

      if (j < picture_width) cnt++; // inkrementiramo samo u granicama realne slike

      Glcd_Set_X(x_left + j);
      Glcd_Write_Data(wdata);

    } //end for j

    if (i < picture_end_page) { //
      row_ind_prev = row_ind;
      row_ind = row_ind + picture_width;
    }
  } // end for i
}

//////////////////////   TFT-oliki fontovi /////////////////////////////
static code const char *_font;
static unsigned int _fontFirstChar; // First character in the font table.
static unsigned int _fontLastChar;  // Last character in the font table.
static unsigned int _fontHeight;
static unsigned int FontColor;
static char FontOrientation;
const char _GLCD_HORIZONTAL = 0;     //font orientation
const char _GLCD_VERTICAL   = 1;
static unsigned int x_cord, y_cord;
static char FontInitialized_Adv = 0;
static unsigned long activeExtFont;
static char headerBuffer[8];
char* (*Glcd_Get_Ext_Data_Ptr)(unsigned long offset, unsigned long count, unsigned long* num);

void Glcd_Set_Ext_Buffer(char* (*getExtDataPtr)(unsigned long offset, unsigned long count, unsigned long* num)) {
  Glcd_Get_Ext_Data_Ptr = getExtDataPtr;
}

static void _Glcd_getHeader(unsigned long offset, unsigned int count){
  unsigned long i, num ;
  char *ptr, *ptrH;

  ptrH = headerBuffer;
  while(count > 0){
   ptr = Glcd_Get_Ext_Data_Ptr(offset,count,&num);
   for (i=0; i<num; i++){
     *ptrH = *ptr;
     ptrH++;
     ptr++;
   }
   count = count - num;
   offset = offset + num;
 }
}

void Glcd_Set_Font_Adv(const char *activeFont, unsigned char font_color, char font_orientation) {
  _font = activeFont;
  _fontFirstChar = activeFont[2] + (unsigned)(activeFont[3] << 8); // SWRELARM-665
  _fontLastChar  = activeFont[4] + (unsigned)(activeFont[5] << 8); // SWRELARM-665
  _fontHeight    = activeFont[6];

  FontColor = font_color;
  FontOrientation = font_orientation;
  FontInitialized_Adv = 1;
  ExternalFontSet = 0;
}

void Glcd_Set_Ext_Font_Adv(unsigned long activeFont, unsigned int font_color, char font_orientation) {
  unsigned int readed;
  char *ptr;

  activeExtFont = activeFont;
//  ptr = Glcd_Get_Ext_Data_Ptr(activeFont,8, &readed);
  _Glcd_getHeader(activeFont,8);
  ptr = &headerBuffer;

  _fontFirstChar = ptr[2] + (unsigned)(ptr[3] << 8); // SWRELARM-665
  _fontLastChar = ptr[4] + (unsigned)(ptr[5] << 8);  // SWRELARM-665
  _fontHeight = ptr[6];

  FontColor = font_color;
  FontOrientation = font_orientation;
  ExternalFontSet = 1;
}


static void _Glcd_Write_Char_AdvE(unsigned int ch) {//, unsigned int x, unsigned int y) {

  unsigned char chWidth = 0;
  unsigned char xCnt, yCnt;
  unsigned int x = 0, y;
  unsigned char temp = 0, mask;
  unsigned long offset;
  unsigned long pChTable;
  unsigned long pChBitMap;
  unsigned long readed, count, byteCount, countSaved;
  unsigned int tmp;
  char *ptr;

  if (ch < _fontFirstChar)
    return;
  if (ch > _fontLastChar)
    return;

  offset = 0;
  tmp = (ch - _fontFirstChar) << 2;
  pChTable = activeExtFont + 8 + tmp;

//  ptr = Glcd_Get_Ext_Data_Ptr(pChTable,4, &readed);
  _Glcd_getHeader(pChTable,4);
  ptr = &headerBuffer;

  chWidth = *ptr;

  offset = (unsigned long) ptr[1] + ((unsigned long)ptr[2] << 8) + ((unsigned long)ptr[3] << 16);

  pChBitMap = activeExtFont + offset;

  count = _fontHeight*(chWidth/8);
  if(chWidth%8)  //ako se sirina lomi, dodajemo _fontHeightE bajtova
    count += _fontHeight;
  countSaved = count;
  ptr = Glcd_Get_Ext_Data_Ptr(pChBitMap, count, &readed);
  pChBitMap += readed;
  count -= readed;

  byteCount = 0;
  if (FontOrientation == _GLCD_HORIZONTAL) {
    y = y_cord;
    for (yCnt = 0; yCnt < _fontHeight; yCnt++) {
      x = x_cord;
      mask = 0;
      for (xCnt = 0; xCnt < chWidth; xCnt++) {
        if (mask == 0) {
          byteCount++;
          if(readed<countSaved){
            if(byteCount>readed){
              byteCount = 1;
              ptr = Glcd_Get_Ext_Data_Ptr(pChBitMap, count, &readed);
              countSaved = count;
              pChBitMap += readed;
              count -= readed;
            }
          }
          temp = *ptr++;
          mask = 0x01;
        }

        if (temp & mask) {
          Glcd_Dot(x, y, FontColor);
        }

        x++;
        mask <<= 1;
      }
      y++;
    }
    // move cursor
    x_cord = x + 1;
  } else {
    y = x_cord;
    for (yCnt = 0; yCnt < _fontHeight; yCnt++) {
      x = y_cord;
      mask = 0;
      for (xCnt = 0; xCnt < chWidth; xCnt++) {
        if (mask == 0) {
          byteCount++;
          if(readed<countSaved){
            if(byteCount>readed){
              byteCount = 1;
              ptr = Glcd_Get_Ext_Data_Ptr(pChBitMap, count, &readed);
              countSaved = count;
              pChBitMap += readed;
              count -= readed;
            }
          }
          temp = *ptr++;
          mask = 0x01;
        }

        if (temp & mask) {
          Glcd_Dot(y, x, FontColor);
        }

        x--;
        mask <<= 1;
      }

      y++;
    }

    // move cursor
    y_cord = x - 1;
  }
}


static void _Glcd_Write_Char_Adv(unsigned char ch) {

  unsigned char chWidth = 0;
  unsigned char xCnt, yCnt;
  unsigned char x = 0, y;
  unsigned char temp = 0, mask;
  unsigned long offset;
  const char *pChTable;
  const char *pChBitMap;
  unsigned int tmp;

  if(FontInitialized_Adv == 0){
    Glcd_Set_Font_Adv(Glcd_defaultFont, 1, _GLCD_HORIZONTAL); //default font
    FontInitialized_Adv = 1;
  }

  if (ch < _fontFirstChar)
    return;
  if (ch > _fontLastChar)
    return;

  offset = 0;
  tmp = (ch - _fontFirstChar) << 2;
  pChTable = _font + 8 + tmp;
  chWidth = *pChTable;

  offset = (unsigned long) pChTable[1] + ((unsigned long)pChTable[2] << 8) + ((unsigned long)pChTable[3] << 16);

  pChBitMap = _font + offset;

  if (FontOrientation == _GLCD_HORIZONTAL) {
    y = y_cord;
    for (yCnt = 0; yCnt < _fontHeight; yCnt++) {
      x = x_cord;
      mask = 0;
      for (xCnt = 0; xCnt < chWidth; xCnt++) {
        if (mask == 0) {
          temp = *pChBitMap++;
          mask = 0x01;
        }

        if (temp & mask) {
          Glcd_Dot(x, y, FontColor);
        }

        x++;
        mask <<= 1;
      }
      y++;
    }
    // move cursor
    x_cord = x + 1;
  } else {
    y = x_cord;
    for (yCnt = 0; yCnt < _fontHeight; yCnt++) {
      x = y_cord;
      mask = 0;
      for (xCnt = 0; xCnt < chWidth; xCnt++) {
        if (mask == 0) {
          temp = *pChBitMap++;
          mask = 0x01;
        }

        if (temp & mask) {
          Glcd_Dot(y, x, FontColor);
        }

        x--;
        mask <<= 1;
      }

      y++;
    }

    // move cursor
    y_cord = x - 1;
  }
}

extern unsigned int Glcd_caption_length, Glcd_caption_height;
static unsigned int min_x_coord, min_y_coord;
static unsigned int max_x_coord, max_y_coord;

static unsigned char _Glcd_Write_Char_Return_Pos(unsigned int ch) {//, unsigned int x, unsigned int y) {

  unsigned char chWidth = 0;
  unsigned char xCnt, yCnt;
  unsigned int x = 0, y;
  const char *pChTable;
  unsigned int tmp;

  if (ch < _fontFirstChar)
    return;
  if (ch > _fontLastChar)
    return;
    
  if(FontInitialized_Adv == 0){
    Glcd_Set_Font_Adv(Glcd_defaultFont, 1, _GLCD_HORIZONTAL); //default font
    FontInitialized_Adv = 1;
  }

  tmp = (ch - _fontFirstChar) << 2;
  pChTable = _font + 8 + tmp;
  chWidth = *pChTable;

  return chWidth;
}


static unsigned char _Glcd_Write_Char_Return_PosE(unsigned int ch) {//, unsigned int x, unsigned int y) {

  unsigned char chWidth = 0;
  unsigned char xCnt, yCnt;
  unsigned int x = 0, y;
  unsigned long offset;
  unsigned long pChTable;
  unsigned int readed;
  unsigned int tmp;
  char *ptr;

  if (ch < _fontFirstChar)
    return;
  if (ch > _fontLastChar)
    return;

  offset = 0;
  tmp = (ch - _fontFirstChar) << 2;
  pChTable = activeExtFont + 8 + tmp;

//  ptr = TFT_Get_Ext_Data_Ptr(pChTable,4, &readed);
  _Glcd_getHeader(pChTable,4);
  ptr = headerBuffer;

  chWidth = *ptr;

  return chWidth;
}


static void Glcd_Move_Cursor(unsigned int _x, unsigned int _y) {
  x_cord = _x;
  y_cord = _y;
}

// dummy text write da bi dobili kordinate "ispisanog" texta
// text se ne ispisuje na displeju, vec setuje X, Y min i max vrednosti
// da bi mogli posle da centriramo text u Objektu (VTFT only) MZ
void Glcd_Write_Text_Return_Pos(unsigned char *text, unsigned int x, unsigned int y) {
  unsigned char ch;
  unsigned char txtWidth = 0;

  if(x >= 128)
    return;
  if(y >= 64)
    return;

  // na pocetku i min i max setujemo na pocetne vrednosti
  Glcd_caption_length = 0;
  Glcd_caption_height = 0;
//  min_x_coord = x;
//  max_x_coord = x;
//  min_y_coord = y;
//  max_y_coord = y;
//
//  i = 0;
//  Glcd_Move_Cursor(x,y);
  while (ch = *text++)
    if(ExternalFontSet)
      txtWidth += _Glcd_Write_Char_Return_PosE(ch) + 1;
    else
      txtWidth += _Glcd_Write_Char_Return_Pos(ch) + 1;

  Glcd_caption_length = txtWidth;
  Glcd_caption_height = _fontHeight;
}

void Glcd_Write_Char_Adv(unsigned char ch, unsigned int x, unsigned int y) {
  if (x >= 128)
    return;
  if (y >= 64)
    return;

  Glcd_Move_Cursor(x, y);
  if(ExternalFontSet)
    _Glcd_Write_Char_AdvE(ch);
  else
    _Glcd_Write_Char_Adv(ch);
}

void Glcd_Write_Text_Adv(unsigned char *text, unsigned int x, unsigned int y) {
  unsigned int i;

  if (x >= 128)
    return;
  if (y >= 64)
    return;

  i = 0;
  Glcd_Move_Cursor(x, y);
  while (text[i])
    if(ExternalFontSet)
      _Glcd_Write_Char_AdvE(text[i++]);
    else
      _Glcd_Write_Char_Adv(text[i++]);
}

void Glcd_Ext_Image(unsigned long image) {
  unsigned int col, pg;
  unsigned int  clan_niza;
  unsigned long cnt, readed, count, num;
  unsigned long offset;
  char *ptr;

  pg = 0;
  clan_niza = 0;
  offset = image;
  count = 1024;
  num = 0;
  readed = 0;
  cnt = 1;
  ptr = 0;
// while
  while (pg <= 7) {
    Glcd_Set_Side(0);                         // sets up CS1 and CS2
    Glcd_Set_Page(pg);
    Glcd_Set_X(0);
    for (col = 0; col <= 63u; col++) {
      if(cnt>readed){
        ptr = Glcd_Get_Ext_Data_Ptr(offset,count,&num);
        offset+=num;
        count-=num;
        readed+=num;
      }
      Glcd_Write_Data(*ptr);
      ptr++;
      cnt++;
    }

    Glcd_Set_Side(64);                        // sets up CS1 and CS2
    Glcd_Set_Page(pg);
    Glcd_Set_X(64);
    for (col = 64; col <= 127u; col++) {
      if(cnt>readed){
        ptr = Glcd_Get_Ext_Data_Ptr(offset,count,&num);
        offset+=num;
        count-=num;
        readed+=num;
      }
      Glcd_Write_Data(*ptr);
      ptr++;
      cnt++;
    }

    pg++;
  }
}

void Glcd_Ext_PartialImage(unsigned int x_left, unsigned int y_top,
                       unsigned int width, unsigned int height,
                       unsigned int picture_width, unsigned int picture_height, unsigned long image) {

  char start_page, end_page, wdata, rdata, top_pomeraj, end_pomeraj, tmp, picture_end_page;
  // prvo sirina pa visina, nizi pa visi bajt
  unsigned int i, j, row_ind, row_ind_prev;
  unsigned int cnt, max_index;
  char prev_data, curr_data;
  unsigned long offset;
  unsigned long readed, num, count, index_start, index_end, tmpW;
  char *ptr;

  i = 0;
  j = 0;
  row_ind = 0;
  row_ind_prev = 0;

  if ((x_left + width - 1) > 127) width = 128 - x_left;
  if ((y_top + height - 1) > 63) height = 64 - y_top;

  start_page = y_top / 8;
  end_page = (y_top + height - 1) / 8;

  top_pomeraj = y_top % 8;
  end_pomeraj = (y_top + height) % 8;

  if (picture_height > height) picture_end_page = end_page;
  else picture_end_page = (y_top + picture_height - 1) / 8;

  if(picture_height % 8 == 0)
    max_index = (picture_height / 8) * picture_width;
  else
    max_index = ((picture_height / 8) + 1) * picture_width;

  offset = image;
  count  = max_index;
  num = 0;
  ptr = Glcd_Get_Ext_Data_Ptr(offset, count, &num);
  index_start = 0;
  index_end = num - 1;
  for (i = start_page; i <= end_page; i++) {
    cnt = 0;
    for (j = 0; j < width; j++) {
      Glcd_Set_Side(x_left + j); // setuje se side, ovo bi moglo optimalnije, da se izbaci u gornu petlju, al' onda treba provera kada se menja side
      Glcd_Set_Page(i); // setuje se page

      if (j < picture_width && i <= picture_end_page) {
        if(top_pomeraj || end_pomeraj){
          if (i == start_page)
            prev_data = 0;
          else{
            tmpW = cnt + row_ind_prev ;
            if(tmpW<index_start || tmpW>index_end){
              index_start = tmpW;
              count = max_index-index_start;
              offset = image + index_start;
              ptr = Glcd_Get_Ext_Data_Ptr(offset,count,&num);
              index_end = index_start + num - 1;
            }
            tmpW = tmpW - index_start;
            prev_data = ptr[tmpW];
          }
        }

        if (row_ind >= max_index)
          curr_data = 0;
        else{
          tmpW = cnt + row_ind;
          if(tmpW<index_start || tmpW>index_end){
            index_start = tmpW;
            count = max_index-index_start;
            offset = image + index_start;
            ptr = Glcd_Get_Ext_Data_Ptr(offset,count,&num);
            index_end = index_start + num - 1;
          }
          tmpW = tmpW - index_start;
          curr_data = ptr[tmpW];
        }
      } else {
        curr_data = 0;
        prev_data = 0;
      }

      wdata = curr_data; // ako nema pomeraja

      if (top_pomeraj > 0) { // ako slika ne pocinje na pocetku page-a  sacuvamo donji deo prelomnjenog bajta i siftujemo ulevo + gornji deo prelomljenog bajta
        wdata = (prev_data >> (8 - top_pomeraj)) | (curr_data << top_pomeraj);
      }

      if (i == start_page && top_pomeraj > 0) { // gornji page i ako slika ne pocinje na pocetku page-a
        Glcd_Set_X(x_left + j);
        rdata = Glcd_Read_Data();
        rdata = Glcd_Read_Data();
        tmp = rdata & (0xFF >> (8 - top_pomeraj));
        wdata = wdata & (0xFF << top_pomeraj);
        wdata = wdata | tmp;
      }

      if (i == end_page && end_pomeraj > 0) { // poslednji page i pomeraj odozdo
        Glcd_Set_X(x_left + j);
        rdata = Glcd_Read_Data();
        rdata = Glcd_Read_Data();
        tmp = rdata & (0xFF << end_pomeraj);
        wdata = wdata & (0xFF >> (8 - end_pomeraj));
        wdata = wdata | tmp;
      }

      if (j < picture_width) cnt++; // inkrementiramo samo u granicama realne slike

      Glcd_Set_X(x_left + j);
      Glcd_Write_Data(wdata);

    } //end for j

    if (i < picture_end_page) { //
      row_ind_prev = row_ind;
      row_ind = row_ind + picture_width;
    }
  } // end for i
}