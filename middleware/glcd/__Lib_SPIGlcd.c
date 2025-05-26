// u ovoj verziji biblioteke zakucana je adresa spi_lcd modula
// to je zato shto sve nase plocice imaju zakucanu ovu adresu hardwerski
// pa ce korisnicima biti lakse ako ovu adresu daju samo jednom u initu
// Kad bude imalo smisla tj. kad se na nasem hardweru otkuca ova adresa,
// vrlo lako ce se izmeniti da ovaj parametar daje user poziva svake spi_lcd rutine

#define Expand_Read_DataPort() Expander_Read_PortB(DefDeviceAddress)
#define Expand_Read_CtrlPort() Expander_Read_PortA(DefDeviceAddress)
#define Expand_Write_DataPort(qqq) Expander_Write_PortB(DefDeviceAddress, qqq)
#define Expand_Write_CtrlPort(qqq) Expander_Write_PortA(DefDeviceAddress, qqq)
#define Expand_Write_DataTris(qqq) Expander_Set_DirectionPortB(DefDeviceAddress, qqq)
#define Expand_Write_CtrlTris(qqq) Expander_Set_DirectionPortA(DefDeviceAddress, qqq)

// static globals
static int DefDeviceAddress;
static int spifontW, spifontH;
static unsigned int spifontOffset;
static const code unsigned short * spifontDef;
static unsigned int ExternalFontSet;

//-------------- Simply strobes the enable line
static void SPI_Strobe() {
unsigned int xxx;

  xxx = Expand_Read_CtrlPort();
// set EN
  xxx |= 0x10;                            
  Expand_Write_CtrlPort(xxx);
  Delay_10us();

// clear EN
  xxx &= 0xEF;                           
  Expand_Write_CtrlPort(xxx);
}

//-------------- Select which page of the display to address (0 to 7)
void SPI_Glcd_Set_Page(char page) {
unsigned int xxx;

  xxx = Expand_Read_CtrlPort();
// set RS on 0v
  xxx &= 0xF3;
// set RW on 0v
  Expand_Write_CtrlPort(xxx);

  xxx = page | 0xB8;
  Expand_Write_DataPort(xxx);
  SPI_Strobe();
}

//-------------- Selects side of the GLCD screen (0 or 1)
void SPI_Glcd_Set_Side(char x_pos) {
unsigned int xxx;

  x_pos &= 0x7F;
  if((x_pos & 0x40) != 0) {
      xxx = Expand_Read_CtrlPort();
// set   CS1 on 5v
      xxx = xxx & 0xFD | 0x01;            
// clear CS2
      Expand_Write_CtrlPort(xxx);  
    }
  else {
      xxx = Expand_Read_CtrlPort();
// set   CS2
      xxx = xxx & 0xFE | 0x02;            
// clear CS1
      Expand_Write_CtrlPort(xxx);  
  }
}

// SPI_Glcd_Set_X
void SPI_Glcd_Set_X(char x_pos) {
unsigned int xxx;

  x_pos &= 0x7F;
  
  xxx = Expand_Read_CtrlPort();
// set RS on 0v
  xxx &= 0xF3;             
// set RW on 0v
  Expand_Write_CtrlPort(xxx);      

  x_pos |= 0x40;
  Expand_Write_DataPort(x_pos);
  SPI_Strobe();
}

//-------------- Reads data at selected page (0-7)  and y_pos (0-127)
char SPI_Glcd_Read_Data() {
unsigned int xxx;
char result;

// set RS on 5v
  xxx = Expand_Read_CtrlPort();   
// clear ENABLE bit
  xxx = xxx & 0xEF | 0x0C;          
// set RW on 5v   
  Expand_Write_CtrlPort(xxx);   

// set tris registers
  Expand_Write_DataTris(0xFF);

// set RS on 5v
  xxx = Expand_Read_CtrlPort(); 
// clear ENABLE bit  
  xxx |= 0x10;                         
// set RW on 5v
  Expand_Write_CtrlPort(xxx);   

  result = Expand_Read_DataPort();
  
  xxx = Expand_Read_CtrlPort();
// clear ENABLE bit
  xxx &= 0xE7;                    
// clear RW on 5v     
  Expand_Write_CtrlPort(xxx);   

  Expand_Write_DataTris(0x00);
  return result;
}

//-------------- Writes data to data port
void SPI_Glcd_Write_Data(char data_) {
volatile unsigned int xxx;

  xxx = Expand_Read_CtrlPort();
// set RS on 5v and set RW on 0v
  xxx = xxx & 0xE7 | 0x04;             
  Expand_Write_CtrlPort(xxx);
  
  Expand_Write_DataPort(data_);
  SPI_Strobe();
}

//-------------- Clears the screen
void SPI_Glcd_Fill(char pattern) {
unsigned int xxx, page, yy;

  xxx = Expand_Read_CtrlPort();
// set CS1 on 0v and CS2 on 5v
  xxx = xxx & 0xFE | 0x02;             
  Expand_Write_CtrlPort(xxx);

  for(page = 0; page < 8; page++) {
    SPI_Glcd_Set_Page(page);
    for(yy = 0; yy < 64; yy++)
      SPI_Glcd_Write_Data(pattern);
  }

  xxx = Expand_Read_CtrlPort();
// set CS1 on 5v and CS2 on 0v
  xxx = xxx & 0xFD | 0x01;             
  Expand_Write_CtrlPort(xxx);
  
  for(page = 0; page < 8; page++) {
    SPI_Glcd_Set_Page(page);
    for(yy = 0; yy < 64; yy++)
      SPI_Glcd_Write_Data(pattern);
  }
}

//-------------- Performs the initialization of the GLCD
void SPI_Glcd_Init(char DeviceAddress) {
  ExternalFontSet = 0;
  //  initialization
  DefDeviceAddress = DeviceAddress;
  Expander_Init(DeviceAddress);

  // set tris registers
  Expand_Write_DataTris(0x00);
  Expand_Write_CtrlTris(0x00);

  // turn ON GLCD and set START line
  Expand_Write_CtrlPort(0x22);
// set display ON
  Expand_Write_DataPort(0x3F); 
  SPI_Strobe();
// set START line
  Expand_Write_DataPort(0xC0); 
  SPI_Strobe();
// set CS1 on 5v and set CS2 on 0v
  Expand_Write_CtrlPort(0x21); 
// set display ON
  Expand_Write_DataPort(0x3F); 
  SPI_Strobe();
// set START line
  Expand_Write_DataPort(0xC0); 
  SPI_Strobe();

  // Default font settings
  spifontW = 5;
  spifontH = 7;
  spifontDef = font5x7;
  spifontOffset = 32;
}

//--------------- Changes font definition
void SPI_Glcd_Set_Font(const code char * activeFont, char aFontWidth,
                       char aFontHeight, unsigned int aFontOffs) {

  spifontDef = activeFont;
  spifontOffset = aFontOffs;
  spifontW = aFontWidth;
  spifontH = aFontHeight;

}

//--------------- Writes sigle char on GLCD
void SPI_Glcd_Write_Char(char chr1, char x_pos, char page_num, char color) {
char ii, data_read, font_ch, font_ch_inv;
int  ptr;
const code char * NewFont;

  if (page_num > 7)
  return;

  ptr = (chr1 - spifontOffset) * spifontW;

  SPI_Glcd_Set_X(x_pos);
  SPI_Glcd_Set_Page(page_num);

  for(ii = 0; ii <= spifontW-1; ii++) {
    if (x_pos > 127)
      return;

    SPI_Glcd_Set_Side(x_pos);
    SPI_Glcd_Set_Page(page_num);
    SPI_Glcd_Set_X(x_pos);

    data_read = SPI_Glcd_Read_Data();
    data_read = SPI_Glcd_Read_Data();

    SPI_Glcd_Set_Side(x_pos);
    SPI_Glcd_Set_Page(page_num);
    SPI_Glcd_Set_X(x_pos);

    NewFont = spifontDef + ptr;
    font_ch = *NewFont;
    ptr++;
    font_ch_inv = ~font_ch;

// case po color
    switch(color) {
      case 0: data_read = font_ch_inv;
              break;
      case 1: data_read = font_ch;
              break;
      case 2: data_read ^= font_ch;
              break;
    }
    SPI_Glcd_Write_Data(data_read);
    x_pos++;
  }

  // last col (is empty)
  SPI_Glcd_Set_Side(x_pos);
  SPI_Glcd_Set_Page(page_num);
  SPI_Glcd_Set_X(x_pos);

  font_ch = 0xFF;
  font_ch_inv = 0;

// case po color
  switch(color) {
    case 0: {
             data_read = font_ch;
             SPI_Glcd_Write_Data(data_read);
             break;
            }
    case 1: {
             data_read = font_ch_inv;
             SPI_Glcd_Write_Data(data_read);
             break;
            }
  }
}

//-------------- Writes string on GLCD
void SPI_Glcd_Write_Text(char text[], char x_pos, char page_num, char color) {
unsigned int i;
char a;

  i = 0;
  a = text[0];
// while za slanje texta
  while(a != 0) {
    SPI_Glcd_Write_Char(text[i], x_pos, page_num, color);
    x_pos += spifontW + 1;

    i++;
    a = text[i];
  }
}

//-------------- Plots a dot on GLCD
void SPI_Glcd_Dot(char x_pos, char y_pos, char color) {
unsigned int bit_line, data_, bit0;

  if ( (x_pos < 0) || (x_pos > 127) || (y_pos < 0) || (y_pos > 63) )
    return;

  SPI_Glcd_Set_Side(x_pos);
  SPI_Glcd_Set_Page(y_pos >> 3);
  SPI_Glcd_Set_X(x_pos);

  data_ = SPI_Glcd_Read_Data();
  data_ = SPI_Glcd_Read_Data();

  SPI_Glcd_Set_Page(y_pos >> 3);
  SPI_Glcd_Set_X(x_pos);

  bit_line = y_pos & 7;
  bit_line = 1 << bit_line;
  bit0 = ~bit_line;

// case po color
  switch(color) {
    case 0: data_ &= bit0;
            break;
    case 1: data_ |= bit_line;
            break;
    case 2: data_ ^= bit_line;
            break;
  }

  SPI_Glcd_Write_Data(data_);
}


//-------------- Draws a line on GLCD (Bersenham's algorithm)
void SPI_Glcd_Line(int x_start, int y_start, int x_end, int y_end, char color) {
int dy, dx, stepx, stepy, fraction;

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
  dy = y_end - y_start;
  dx = x_end - x_start;
// stepovi
  if(dy < 0) {
    dy = -dy;
    stepy = -1;
  }
  else
    stepy = 1;

  if(dx < 0) {
    dx = -dx;
    stepx = -1;
  }
  else
    stepx = 1;

  dy <<= 1;
  dx <<= 1;

  SPI_Glcd_Dot(x_start, y_start, color);
// dx > dy
  if(dx > dy) {
    fraction = dy - (dx >> 1);
    while(x_start != x_end) {
      if(fraction >= 0) {
        y_start += stepy;
        fraction -= dx;
      }
      x_start += stepx;
      fraction += dy;

      SPI_Glcd_Dot(x_start, y_start, color);
    }
  }
// dy > dx
  else {
    fraction = dx - (dy >> 1);
    while(y_start != y_end) {
      if(fraction >= 0) {
        x_start += stepx;
        fraction -= dy;
      }
      y_start += stepy;
      fraction += dx;
      SPI_Glcd_Dot(x_start, y_start, color);
    }
  }
}

//-------------- Draws a horizontal line
void SPI_Glcd_H_Line(char x_start, char x_end, char y_pos, char color) {
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

  if(x_start > x_end) {
    loc = x_start;
    x_start = x_end;
    x_end = loc;
  }

  while(x_start <= x_end) {
    SPI_Glcd_Dot(x_start, y_pos, color);
    x_start++;
  }
}

//-------------- Draws a vertical line
void SPI_Glcd_V_Line(char y_start, char y_end, char x_pos, char color) {
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

  if(y_start > y_end) {
    loc = y_start;
    y_start = y_end;
    y_end = loc;
  }

  while(y_start <= y_end) {
    SPI_Glcd_Dot(x_pos, y_start, color);
    y_start++;
  }
}

//-------------- Draws a circle
void SPI_Glcd_Circle(int x_center, int y_center, int radius, char color) {
int tswitch, y, x, d;

  if(radius == 0) {
    SPI_Glcd_Dot(x_center, y_center,color);
    return;
  }

  x = 0;
  d = y_center - x_center;
  y = radius;
  tswitch = y << 1;
  tswitch = 3 - tswitch;

  while(x < (y + 1)) {

    SPI_Glcd_Dot(x_center + x,     y_center + y,color);
    SPI_Glcd_Dot(x_center + x,     y_center - y,color);
    if(x > 0) {
    SPI_Glcd_Dot(x_center - x,     y_center + y,color);
    SPI_Glcd_Dot(x_center - x,     y_center - y,color);
    }

    // Ako ovo nije ispunjeno onda su ove tacke vec iscrtane
    if(x != y)
    {
    SPI_Glcd_Dot(y_center + y - d, y_center + x,color);
      SPI_Glcd_Dot(y_center - y - d, y_center + x,color);
      if(x > 0)
      {
    SPI_Glcd_Dot(y_center + y - d, y_center - x,color);
    SPI_Glcd_Dot(y_center - y - d, y_center - x,color);
      }
    }

    if(tswitch < 0)
      tswitch += (x << 2) + 6;
    else {
      tswitch += ((x - y) << 2) + 10;
      y--;
    }
    x++;
  }
}

void SPI_Glcd_Circle_Fill(int x_center, int y_center, int radius,
                 unsigned short color) {
  int tswitch,
      y, x, d, xOld, yOld;

  if(radius == 0) {
    SPI_Glcd_Dot(x_center, y_center,color);
    return;
  }

  x = 0;
  xOld = 0;
  d  = y_center - x_center;
  y  = radius;
  yOld = y;
  tswitch  = y << 1;
  tswitch = 3 - tswitch;
  while (x < (y+1)) {

    SPI_Glcd_Line(x_center + x,     y_center + y, x_center + x,     y_center - y,color);
    if (x > 0)
      SPI_Glcd_Line(x_center - x,     y_center + y, x_center - x,     y_center - y,color);

    if(yOld != y) {
      SPI_Glcd_Line(y_center + yOld - d, y_center + xOld, y_center + yOld - d, y_center - xOld,color);
      if (yOld > 0)
        SPI_Glcd_Line(y_center - yOld - d, y_center + xOld, y_center - yOld - d, y_center - xOld,color);
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
    SPI_Glcd_Line(y_center + yOld - d, y_center + xOld, y_center + yOld - d, y_center - xOld,color);
    if (yOld > 0)
      SPI_Glcd_Line(y_center - yOld - d, y_center + xOld, y_center - yOld - d, y_center - xOld,color);
  }
}

//-------------- Plots an image on GLCD
void SPI_Glcd_Image(const code char * image) {
unsigned int col, pg;

  pg = 0;

// while
  while(pg <= 7) {
    SPI_Glcd_Set_Side(0);
    SPI_Glcd_Set_Page(pg);
    SPI_Glcd_Set_X(0);

    for(col = 0; col <= 63; col++) {
      SPI_Glcd_Write_Data(*image++);
    }

    SPI_Glcd_Set_Side(64);
    SPI_Glcd_Set_Page(pg);
    SPI_Glcd_Set_X(64);

    for(col = 64; col <= 127; col++) {
      SPI_Glcd_Write_Data(*image++);
    }
    pg++;
  }
}

//-------------- Draws a rectangle
void SPI_Glcd_Rectangle(char x_upper_left, char y_upper_left, char x_bottom_right, char y_bottom_right, char color) {

  SPI_Glcd_H_Line(x_upper_left  ,x_bottom_right  ,y_upper_left  ,color);
  SPI_Glcd_H_Line(x_upper_left  ,x_bottom_right  ,y_bottom_right,color);
  SPI_Glcd_V_Line(y_upper_left  ,y_bottom_right  ,x_upper_left  ,color);
  SPI_Glcd_V_Line(y_upper_left  ,y_bottom_right  ,x_bottom_right,color);
}

void SPI_Glcd_Rectangle_Round_Edges(unsigned short x_upper_left,unsigned short y_upper_left,
                          unsigned short x_bottom_right,unsigned short y_bottom_right,
                          unsigned short round_radius, unsigned short color) {
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

  SPI_Glcd_H_Line(x_upper_left+round_radius + 1, x_bottom_right-round_radius - 1, y_upper_left, color);
  SPI_Glcd_H_Line(x_upper_left+round_radius + 1, x_bottom_right-round_radius - 1, y_bottom_right, color);
  SPI_Glcd_V_Line(y_upper_left+round_radius + 1, y_bottom_right-round_radius - 1, x_upper_left, color);
  SPI_Glcd_V_Line(y_upper_left+round_radius + 1, y_bottom_right-round_radius - 1, x_bottom_right, color);

  x = 0;
  d1 = (y_upper_left + round_radius) - (x_bottom_right - round_radius);
  d2 = (y_upper_left + round_radius) - (x_upper_left + round_radius);
  d3 = (y_bottom_right - round_radius) - (x_upper_left + round_radius);
  d4 = (y_bottom_right - round_radius) - (x_bottom_right - round_radius);

  y  = round_radius;
  tswitch  = y << 1;
  tswitch = 3 - tswitch;
  while (x < (y+1)) {
    SPI_Glcd_Dot((x_upper_left + round_radius) - x,     (y_bottom_right - round_radius) + y,color);     // 31
    SPI_Glcd_Dot((x_bottom_right - round_radius) + x,     (y_bottom_right - round_radius) + y,color);   // 41
    SPI_Glcd_Dot((x_upper_left + round_radius) - x,     (y_upper_left + round_radius) - y,color);       // 21
    SPI_Glcd_Dot((x_bottom_right - round_radius) + x,     (y_upper_left + round_radius) - y,color);     // 11

    if(x != y) {
    SPI_Glcd_Dot((y_bottom_right - round_radius) + y - d4, (y_bottom_right - round_radius) + x,color);  // 42
    SPI_Glcd_Dot((y_bottom_right - round_radius) - y - d3, (y_bottom_right - round_radius) + x,color);  // 32
    SPI_Glcd_Dot((y_upper_left + round_radius) - y - d2, (y_upper_left + round_radius) - x,color);      // 22
    SPI_Glcd_Dot((y_upper_left + round_radius) + y - d1, (y_upper_left + round_radius) - x,color);      // 12
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
void SPI_Glcd_Box(char x_upper_left, char y_upper_left, char x_bottom_right, char y_bottom_right, char color) {
unsigned int loc;

  for(loc = y_upper_left; loc <= y_bottom_right; loc++)
    SPI_Glcd_H_Line(x_upper_left, x_bottom_right, loc, color);
}

void SPI_Glcd_Rectangle_Round_Edges_Fill(unsigned short x_upper_left,unsigned short y_upper_left,
                          unsigned short x_bottom_right,unsigned short y_bottom_right,
                          unsigned short round_radius, unsigned short color) {
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

  SPI_Glcd_Box(x_upper_left, y_upper_left+round_radius + 1, x_bottom_right, y_bottom_right-round_radius - 1, color);

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
      SPI_Glcd_Line((x_upper_left + round_radius) - xOld, (y_bottom_right - round_radius) + yOld,
                (x_bottom_right - round_radius) + xOld, (y_bottom_right - round_radius) + yOld, color);
      SPI_Glcd_Line((x_upper_left + round_radius) - xOld, (y_upper_left + round_radius) - yOld,
                (x_bottom_right - round_radius) + xOld, (y_upper_left + round_radius) - yOld,color);
      yOld = y;
    }

    SPI_Glcd_Line((y_bottom_right - round_radius) + y - d4, (y_bottom_right - round_radius) + x,
              (y_bottom_right - round_radius) - y - d3, (y_bottom_right - round_radius) + x,color);
    SPI_Glcd_Line((y_upper_left + round_radius) - y - d2, (y_upper_left + round_radius) - x,
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
    SPI_Glcd_Line((x_upper_left + round_radius) - xOld, (y_bottom_right - round_radius) + yOld, (x_bottom_right - round_radius) + xOld, (y_bottom_right - round_radius) + yOld, color);
    SPI_Glcd_Line((x_upper_left + round_radius) - xOld, (y_upper_left + round_radius) - yOld, (x_bottom_right - round_radius) + xOld, (y_upper_left + round_radius) - yOld,color);
  }
}

// Draw Partial Image
void SPI_Glcd_PartialImage(unsigned int x_left, unsigned int y_top,
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
      SPI_Glcd_Set_Side(x_left + j); // setuje se side, ovo bi moglo optimalnije, da se izbaci u gornu petlju, al' onda treba provera kada se menja side
      SPI_Glcd_Set_Page(i); // setuje se page

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
        SPI_Glcd_Set_X(x_left + j);
        rdata = SPI_Glcd_Read_Data();
        rdata = SPI_Glcd_Read_Data();
        tmp = rdata & (0xFF >> (8 - top_pomeraj));
        wdata = wdata & (0xFF << top_pomeraj);
        wdata = wdata | tmp;
      }

      if (i == end_page && end_pomeraj > 0) { // poslednji page i pomeraj odozdo
        SPI_Glcd_Set_X(x_left + j);
        rdata = SPI_Glcd_Read_Data();
        rdata = SPI_Glcd_Read_Data();
        tmp = rdata & (0xFF << end_pomeraj);
        wdata = wdata & (0xFF >> (8 - end_pomeraj));
        wdata = wdata | tmp;
      }

      if (j < picture_width) cnt++; // inkrementiramo samo u granicama realne slike

      SPI_Glcd_Set_X(x_left + j);
      SPI_Glcd_Write_Data(wdata);

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
const char _SPI_GLCD_HORIZONTAL = 0;     //font orientation
const char _SPI_GLCD_VERTICAL   = 1;
static unsigned int x_cord, y_cord;
static char FontInitialized_Adv = 0;
static unsigned long activeExtFont;
static char headerBuffer[8];
char* (*SPI_Glcd_Get_Ext_Data_Ptr)(unsigned long offset, unsigned long count, unsigned long* num);

void SPI_Glcd_Set_Ext_Buffer(char* (*getExtDataPtr)(unsigned long offset, unsigned long count, unsigned long* num)) {
  SPI_Glcd_Get_Ext_Data_Ptr = getExtDataPtr;
}

static void _SPI_Glcd_getHeader(unsigned long offset, unsigned int count){
  unsigned long i, num ;
  char *ptr, *ptrH;

  ptrH = headerBuffer;
  while(count > 0){
   ptr = SPI_Glcd_Get_Ext_Data_Ptr(offset,count,&num);
   for (i=0; i<num; i++){
     *ptrH = *ptr;
     ptrH++;
     ptr++;
   }
   count = count - num;
   offset = offset + num;
 }
}


void SPI_Glcd_Set_Font_Adv(const char *activeFont, unsigned char font_color, char font_orientation) {
  _font = activeFont;
  _fontFirstChar = activeFont[2] + (unsigned)(activeFont[3] << 8); // SWRELARM-665
  _fontLastChar  = activeFont[4] + (unsigned)(activeFont[5] << 8); // SWRELARM-665
  _fontHeight    = activeFont[6];

  FontColor = font_color;
  FontOrientation = font_orientation;
  FontInitialized_Adv = 1;
  ExternalFontSet = 0;
}

void SPI_Glcd_Set_Ext_Font_Adv(unsigned long activeFont, unsigned int font_color, char font_orientation) {
  unsigned int readed;
  char *ptr;

  activeExtFont = activeFont;
//  ptr = SPI_Glcd_Get_Ext_Data_Ptr(activeFont,8, &readed);
  _SPI_Glcd_getHeader(activeFont,8);
  ptr = &headerBuffer;

  _fontFirstChar = ptr[2] + (unsigned)(ptr[3] << 8); // SWRELARM-665
  _fontLastChar = ptr[4] + (unsigned)(ptr[5] << 8); // SWRELARM-665
  _fontHeight = ptr[6];

  FontColor = font_color;
  FontOrientation = font_orientation;
  ExternalFontSet = 1;
}


static void _SPI_Glcd_Write_Char_Adv(unsigned char ch) {

  unsigned char chWidth = 0;
  unsigned char xCnt, yCnt;
  unsigned char x = 0, y;
  unsigned char temp = 0, mask;
  unsigned long offset;
  const char *pChTable;
  const char *pChBitMap;
  unsigned int tmp;

  if(FontInitialized_Adv == 0){
    SPI_Glcd_Set_Font_Adv(Glcd_defaultFont, 1, _SPI_GLCD_HORIZONTAL); //default font
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

  if (FontOrientation == _SPI_GLCD_HORIZONTAL) {
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
          SPI_Glcd_Dot(x, y, FontColor);
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
          SPI_Glcd_Dot(y, x, FontColor);
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

static void _SPI_Glcd_Write_Char_AdvE(unsigned int ch) {//, unsigned int x, unsigned int y) {

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

//  ptr = SPI_Glcd_Get_Ext_Data_Ptr(pChTable,4, &readed);
  _SPI_Glcd_getHeader(pChTable,4);
  ptr = &headerBuffer;

  chWidth = *ptr;

  offset = (unsigned long) ptr[1] + ((unsigned long)ptr[2] << 8) + ((unsigned long)ptr[3] << 16);

  pChBitMap = activeExtFont + offset;

  count = _fontHeight*(chWidth/8);
  if(chWidth%8)  //ako se sirina lomi, dodajemo _fontHeightE bajtova
    count += _fontHeight;
  countSaved = count;
  ptr = SPI_Glcd_Get_Ext_Data_Ptr(pChBitMap, count, &readed);
  pChBitMap += readed;
  count -= readed;

  byteCount = 0;
  if (FontOrientation == _SPI_GLCD_HORIZONTAL) {
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
              ptr = SPI_Glcd_Get_Ext_Data_Ptr(pChBitMap, count, &readed);
              countSaved = count;
              pChBitMap += readed;
              count -= readed;
            }
          }
          temp = *ptr++;
          mask = 0x01;
        }

        if (temp & mask) {
          SPI_Glcd_Dot(x, y, FontColor);
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
              ptr = SPI_Glcd_Get_Ext_Data_Ptr(pChBitMap, count, &readed);
              countSaved = count;
              pChBitMap += readed;
              count -= readed;
            }
          }
          temp = *ptr++;
          mask = 0x01;
        }

        if (temp & mask) {
          SPI_Glcd_Dot(y, x, FontColor);
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

extern unsigned int SPI_Glcd_caption_length, SPI_Glcd_caption_height;
static unsigned int min_x_coord, min_y_coord;
static unsigned int max_x_coord, max_y_coord;

static unsigned char _SPI_Glcd_Write_Char_Return_Pos(unsigned int ch) {//, unsigned int x, unsigned int y) {

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
    SPI_Glcd_Set_Font_Adv(Glcd_defaultFont, 1, _SPI_GLCD_HORIZONTAL); //default font
    FontInitialized_Adv = 1;
  }

  tmp = (ch - _fontFirstChar) << 2;
  pChTable = _font + 8 + tmp;
  chWidth = *pChTable;

  return chWidth;
}

static unsigned char _SPI_Glcd_Write_Char_Return_PosE(unsigned int ch) {//, unsigned int x, unsigned int y) {

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
  _SPI_Glcd_getHeader(pChTable,4);
  ptr = headerBuffer;

  chWidth = *ptr;

  return chWidth;
}

static void SPI_Glcd_Move_Cursor(unsigned int _x, unsigned int _y) {
  x_cord = _x;
  y_cord = _y;
}

// dummy text write da bi dobili kordinate "ispisanog" texta
// text se ne ispisuje na displeju, vec setuje X, Y min i max vrednosti
// da bi mogli posle da centriramo text u Objektu (VTFT only) MZ
void SPI_Glcd_Write_Text_Return_Pos(unsigned char *text, unsigned int x, unsigned int y) {
  unsigned char ch;
  unsigned char txtWidth = 0;

  if(x >= 128)
    return;
  if(y >= 64)
    return;

  // na pocetku i min i max setujemo na pocetne vrednosti
  SPI_Glcd_caption_length = 0;
  SPI_Glcd_caption_height = 0;
//  min_x_coord = x;
//  max_x_coord = x;
//  min_y_coord = y;
//  max_y_coord = y;
//
//  i = 0;
//  SPI_Glcd_Move_Cursor(x,y);
  while (ch = *text++)
    if(ExternalFontSet)
      txtWidth += _SPI_Glcd_Write_Char_Return_PosE(ch) + 1;
    else
      txtWidth += _SPI_Glcd_Write_Char_Return_Pos(ch) + 1;

  SPI_Glcd_caption_length = txtWidth;
  SPI_Glcd_caption_height = _fontHeight;
}

void SPI_Glcd_Write_Char_Adv(unsigned char ch, unsigned int x, unsigned int y) {
  if (x >= 128)
    return;
  if (y >= 64)
    return;

  SPI_Glcd_Move_Cursor(x, y);
  if(ExternalFontSet)
    _SPI_Glcd_Write_Char_AdvE(ch);
  else
    _SPI_Glcd_Write_Char_Adv(ch);
}

void SPI_Glcd_Write_Text_Adv(unsigned char *text, unsigned int x, unsigned int y) {
  unsigned int i;

  if (x >= 128)
    return;
  if (y >= 64)
    return;

  i = 0;
  SPI_Glcd_Move_Cursor(x, y);
  while (text[i])
    if(ExternalFontSet)
      _SPI_Glcd_Write_Char_AdvE(text[i++]);
    else
      _SPI_Glcd_Write_Char_Adv(text[i++]);
}

void SPI_Glcd_Ext_Image(unsigned long image) {
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
// while
  while (pg <= 7) {
    SPI_Glcd_Set_Side(0);                         // sets up CS1 and CS2
    SPI_Glcd_Set_Page(pg);
    SPI_Glcd_Set_X(0);
    for (col = 0; col <= 63u; col++) {
      if(cnt>readed){
        ptr = SPI_Glcd_Get_Ext_Data_Ptr(offset,count,&num);
        offset+=num;
        count-=num;
        readed+=num;
      }
      SPI_Glcd_Write_Data(*ptr);
      ptr++;
      cnt++;
    }

    SPI_Glcd_Set_Side(64);                        // sets up CS1 and CS2
    SPI_Glcd_Set_Page(pg);
    SPI_Glcd_Set_X(64);
    for (col = 64; col <= 127u; col++) {
      if(cnt>readed){
        ptr = SPI_Glcd_Get_Ext_Data_Ptr(offset,count,&num);
        offset+=num;
        count-=num;
        readed+=num;
      }
      SPI_Glcd_Write_Data(*ptr);
      ptr++;
      cnt++;
    }

    pg++;
  }
}


void SPI_Glcd_Ext_PartialImage(unsigned int x_left, unsigned int y_top,
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
  ptr = SPI_Glcd_Get_Ext_Data_Ptr(offset, count, &num);
  index_start = 0;
  index_end = num - 1;
  for (i = start_page; i <= end_page; i++) {
    cnt = 0;
    for (j = 0; j < width; j++) {
      SPI_Glcd_Set_Side(x_left + j); // setuje se side, ovo bi moglo optimalnije, da se izbaci u gornu petlju, al' onda treba provera kada se menja side
      SPI_Glcd_Set_Page(i); // setuje se page

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
              ptr = SPI_Glcd_Get_Ext_Data_Ptr(offset,count,&num);
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
            ptr = SPI_Glcd_Get_Ext_Data_Ptr(offset,count,&num);
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
        SPI_Glcd_Set_X(x_left + j);
        rdata = SPI_Glcd_Read_Data();
        rdata = SPI_Glcd_Read_Data();
        tmp = rdata & (0xFF >> (8 - top_pomeraj));
        wdata = wdata & (0xFF << top_pomeraj);
        wdata = wdata | tmp;
      }

      if (i == end_page && end_pomeraj > 0) { // poslednji page i pomeraj odozdo
        SPI_Glcd_Set_X(x_left + j);
        rdata = SPI_Glcd_Read_Data();
        rdata = SPI_Glcd_Read_Data();
        tmp = rdata & (0xFF << end_pomeraj);
        wdata = wdata & (0xFF >> (8 - end_pomeraj));
        wdata = wdata | tmp;
      }

      if (j < picture_width) cnt++; // inkrementiramo samo u granicama realne slike

      SPI_Glcd_Set_X(x_left + j);
      SPI_Glcd_Write_Data(wdata);

    } //end for j

    if (i < picture_end_page) { //
      row_ind_prev = row_ind;
      row_ind = row_ind + picture_width;
    }
  } // end for i
}