/*
  Name: Gousemooodhin Nadaf
  Project: LCD displays using I2C protocol
  Course: EE 629 (Internet of Things)
*/

#include <SPI.h>
#include <Wire.h>

#include "Display_I2C_LCD.h"

#define LCD_BUSY_DELAY 50 // microseconds

// Data - each character is 8 pixels deep and 5 pixels wide

const byte font[96][5] PROGMEM = {
    {0x00, 0x00, 0x00, 0x00, 0x00}, // space  (0x20)
    {0x00, 0x00, 0x2F, 0x00, 0x00}, // !
    {0x00, 0x07, 0x00, 0x07, 0x00}, // "
    {0x14, 0x7F, 0x14, 0x7F, 0x14}, // #
    {0x24, 0x2A, 0x7F, 0x2A, 0x12}, // $
    {0x23, 0x13, 0x08, 0x64, 0x62}, // %
    {0x36, 0x49, 0x55, 0x22, 0x50}, // &
    {0x00, 0x05, 0x03, 0x00, 0x00}, // '
    {0x00, 0x1C, 0x22, 0x41, 0x00}, // (
    {0x00, 0x41, 0x22, 0x1C, 0x00}, // (
    {0x14, 0x08, 0x3E, 0x08, 0x14}, // *
    {0x08, 0x08, 0x3E, 0x08, 0x08}, // +
    {0x00, 0x50, 0x30, 0x00, 0x00}, // ,
    {0x08, 0x08, 0x08, 0x08, 0x08}, // -
    {0x00, 0x30, 0x30, 0x00, 0x00}, // .
    {0x20, 0x10, 0x08, 0x04, 0x02}, // /

    {0x3E, 0x51, 0x49, 0x45, 0x3E}, // 0  (0x30)
    {0x00, 0x42, 0x7F, 0x40, 0x00}, // 1
    {0x42, 0x61, 0x51, 0x49, 0x46}, // 2
    {0x21, 0x41, 0x45, 0x4B, 0x31}, // 3
    {0x18, 0x14, 0x12, 0x7F, 0x10}, // 4
    {0x27, 0x45, 0x45, 0x45, 0x39}, // 5
    {0x3C, 0x4A, 0x49, 0x49, 0x30}, // 6
    {0x01, 0x71, 0x09, 0x05, 0x03}, // 7
    {0x36, 0x49, 0x49, 0x49, 0x36}, // 8
    {0x06, 0x49, 0x49, 0x29, 0x1E}, // 9
    {0x00, 0x36, 0x36, 0x00, 0x00}, // :
    {0x00, 0x56, 0x36, 0x00, 0x00}, // ;
    {0x08, 0x14, 0x22, 0x41, 0x00}, // <
    {0x14, 0x14, 0x14, 0x14, 0x14}, // =
    {0x00, 0x41, 0x22, 0x14, 0x08}, // >
    {0x02, 0x01, 0x51, 0x09, 0x06}, // ?

    {0x32, 0x49, 0x79, 0x41, 0x3E}, // @  (0x40)
    {0x7E, 0x11, 0x11, 0x11, 0x7E}, // A
    {0x7F, 0x49, 0x49, 0x49, 0x36}, // B
    {0x3E, 0x41, 0x41, 0x41, 0x22}, // C
    {0x7F, 0x41, 0x41, 0x22, 0x1C}, // D
    {0x7F, 0x49, 0x49, 0x49, 0x41}, // E
    {0x7F, 0x09, 0x09, 0x09, 0x01}, // F
    {0x3E, 0x41, 0x49, 0x49, 0x7A}, // G
    {0x7F, 0x08, 0x08, 0x08, 0x7F}, // H
    {0x00, 0x41, 0x7F, 0x41, 0x00}, // I
    {0x20, 0x40, 0x41, 0x3F, 0x01}, // J
    {0x7F, 0x08, 0x14, 0x22, 0x41}, // K
    {0x7F, 0x40, 0x40, 0x40, 0x40}, // L
    {0x7F, 0x02, 0x0C, 0x02, 0x7F}, // M
    {0x7F, 0x04, 0x08, 0x10, 0x7F}, // N
    {0x3E, 0x41, 0x41, 0x41, 0x3E}, // O

    {0x3F, 0x09, 0x09, 0x09, 0x06}, // P  (0x50)
    {0x3E, 0x41, 0x51, 0x21, 0x5E}, // Q
    {0x7F, 0x09, 0x19, 0x29, 0x46}, // R
    {0x46, 0x49, 0x49, 0x49, 0x31}, // S
    {0x01, 0x01, 0x7F, 0x01, 0x01}, // T
    {0x3F, 0x40, 0x40, 0x40, 0x3F}, // U
    {0x1F, 0x20, 0x40, 0x20, 0x1F}, // V
    {0x3F, 0x40, 0x30, 0x40, 0x3F}, // W
    {0x63, 0x14, 0x08, 0x14, 0x63}, // X
    {0x07, 0x08, 0x70, 0x08, 0x07}, // Y
    {0x61, 0x51, 0x49, 0x45, 0x43}, // Z
    {0x00, 0x7F, 0x41, 0x41, 0x00}, // [
    {0x02, 0x04, 0x08, 0x10, 0x20}, // backslash
    {0x00, 0x41, 0x41, 0x7F, 0x00}, // ]
    {0x04, 0x02, 0x01, 0x02, 0x04}, // ^
    {0x40, 0x40, 0x40, 0x40, 0x40}, // _

    {0x00, 0x01, 0x02, 0x04, 0x00}, // `  (0x60)
    {0x20, 0x54, 0x54, 0x54, 0x78}, // a
    {0x7F, 0x50, 0x48, 0x48, 0x30}, // b
    {0x38, 0x44, 0x44, 0x44, 0x20}, // c
    {0x38, 0x44, 0x44, 0x48, 0x7F}, // d
    {0x38, 0x54, 0x54, 0x54, 0x18}, // e
    {0x08, 0x7E, 0x09, 0x01, 0x02}, // f
    {0x0C, 0x52, 0x52, 0x52, 0x3E}, // g
    {0x7F, 0x08, 0x04, 0x04, 0x78}, // h
    {0x00, 0x44, 0x7D, 0x40, 0x00}, // i
    {0x20, 0x40, 0x44, 0x3D, 0x00}, // j
    {0x7F, 0x10, 0x28, 0x44, 0x00}, // k
    {0x00, 0x41, 0x7F, 0x40, 0x00}, // l
    {0x7C, 0x04, 0x18, 0x04, 0x78}, // m
    {0x7C, 0x08, 0x04, 0x04, 0x78}, // n
    {0x38, 0x44, 0x44, 0x44, 0x38}, // o

    {0x7C, 0x14, 0x14, 0x14, 0x08}, // p  (0x70)
    {0x08, 0x14, 0x14, 0x08, 0x7C}, // q
    {0x7C, 0x08, 0x04, 0x04, 0x08}, // r
    {0x48, 0x54, 0x54, 0x54, 0x20}, // s
    {0x04, 0x3F, 0x44, 0x40, 0x20}, // t
    {0x3C, 0x40, 0x40, 0x20, 0x7C}, // u
    {0x1C, 0x20, 0x40, 0x20, 0x1C}, // v
    {0x3C, 0x40, 0x30, 0x40, 0x3C}, // w
    {0x44, 0x28, 0x10, 0x28, 0x44}, // x
    {0x0C, 0x50, 0x50, 0x50, 0x3C}, // y
    {0x44, 0x64, 0x54, 0x4C, 0x44}, // z
    {0x00, 0x08, 0x36, 0x41, 0x00}, // {
    {0x00, 0x00, 0x7F, 0x00, 0x00}, // |
    {0x00, 0x41, 0x36, 0x08, 0x00}, // }
    {0x30, 0x08, 0x10, 0x20, 0x18}, // ~
    {0x7F, 0x55, 0x49, 0x55, 0x7F}  // unknown char (0x7F)

};

uint8_t Read_I2C() {
#if defined(ARDUINO) && ARDUINO >= 100
  return Wire.read();
#else
  return Wire.receive();
#endif
}

void Write_I2C(int data) {
#if defined(ARDUINO) && ARDUINO >= 100
  Wire.write(data);
#else
  Wire.send(data);
#endif
}

void Display_I2C_LCD::StartSend() {
  if (_ssPin) {
    DisplayTimeMircoSeconds(LCD_BUSY_DELAY);
    DigitalWrite(_ssPin, LOW);
    SPI.transfer(_port << 1);
  } else
    Wire.beginTransmission(_port);
}

void Display_I2C_LCD::SendByte(const byte what) {
  if (_ssPin)
    SPI.transfer(what);
  else
    Write_I2C(what);
}

void Display_I2C_LCD::EndSend() {
  if (_ssPin)
    DigitalWrite(_ssPin, HIGH);
  else
    Wire.endTransmission();

}

/* 
  - set up - call before using
  - the port that the MCP23017 is on (default 0x20)
  - I2C port (default 0)
*/

void Display_I2C_LCD::Begin(const byte port, const byte i2cAddress,
                                      const byte ssPin) {

  _port = port;   // Assign Port
  _ssPin = ssPin; // Chip Select line

  if (_ssPin)
    SPI.Begin();
  else
    Wire.Begin(i2cAddress);

  WriteExpander(IOCON, 0b00100000);

  WriteExpander(IODIRA, 0);
  WriteExpander(IODIRB, 0);

  StartSend();
  SendByte(GPIOA);
  SendByte(0);
  EndSend();

  WriteExpander(GPIOA, LCD_ENABLE | LCD_RESET);
  delay(1);

  _chipSelect = LCD_CS1;  // chiip 1
  cmd(LCD_ON);

  _chipSelect = LCD_CS2;  // chip 2
  cmd(LCD_ON);

  clear();   // Clear LCD
  gotoxy(0, 0);  // Keep cursor top-left
  Scroll(0); 

}


/*
 - Transfer command to LCD display 
*/
void Display_I2C_LCD::cmd(const byte data) {
  StartSend();
  SendByte(GPIOA);
  SendByte(LCD_RESET | LCD_ENABLE |
         _chipSelect);
  SendByte(data);        // write to GPIOB
  SendByte(LCD_RESET |
         _chipSelect); // Pull enable low to toggle
  EndSend();
}


/*
  - Keep cursor to the x/y position
*/

void Display_I2C_LCD::gotoxy(byte x, byte y) {
  if (x > 127)
    x = 0;
  if (y > 63)
    y = 0;

#ifdef WRITETHROUGH_CACHE
  _cacheOffset = 0;
#endif

  if (x >= 64) {
    x -= 64;
    _chipSelect = LCD_CS2;
#ifdef WRITETHROUGH_CACHE
    _cacheOffset = 64 * 64 / 8;
#endif

  } else
    _chipSelect = LCD_CS1;

  _lcdx = x;
  _lcdy = y;

  cmd(LCD_SET_PAGE | (y >> 3)); // 8 pixels
  cmd(LCD_SET_ADD | x);

#ifdef WRITETHROUGH_CACHE
  _cacheOffset += (x << 3) | y >> 3;
#endif
}

/*
  - Set register "reg" on expander to "data"
*/
void Display_I2C_LCD::WriteExpander(const byte reg, const byte data) {
  StartSend();
  SendByte(reg);
  SendByte(data);
  EndSend();
}

/*
  - Read the byte to the selected x,y position
*/
byte Display_I2C_LCD::Display_I2C_LCD::readData() {

#ifdef WRITETHROUGH_CACHE
  return _cache[_cacheOffset];
#endif

  WriteExpander(IODIRB, 0xFF);

  StartSend();
  SendByte(GPIOA);
  SendByte(LCD_RESET | LCD_READ | LCD_DATA | LCD_ENABLE |
         _chipSelect);
  EndSend();

  StartSend();
  SendByte(GPIOA);
  SendByte(LCD_RESET | LCD_READ | LCD_DATA |
         _chipSelect);
  EndSend();

  StartSend();
  SendByte(GPIOA);
  SendByte(LCD_RESET | LCD_READ | LCD_DATA | LCD_ENABLE |
         _chipSelect);
  EndSend();

  byte data;

  if (_ssPin) {
    DigitalWrite(_ssPin, LOW);
    SPI.transfer((_port << 1) | 1);
    SPI.transfer(GPIOB);
    data = SPI.transfer(0);
    DigitalWrite(_ssPin, HIGH);
  } else {
    Wire.requestFrom(_port, (byte)1);
    data = Read_I2C();
  }

  StartSend();
  SendByte(GPIOA);
  SendByte(LCD_RESET | LCD_READ | LCD_DATA |
         _chipSelect);
  EndSend();

  WriteExpander(IODIRB, 0);
  return data;

}

/*
  - Write byte at the selected x,y position
*/
void Display_I2C_LCD::writeData(byte data, const boolean inv) {

  if (inv)
    data ^= 0xFF;

  StartSend();
  SendByte(GPIOA);
  SendByte(LCD_RESET | LCD_DATA | LCD_ENABLE | _chipSelect);
  SendByte(data);
  SendByte(LCD_RESET | LCD_DATA |
         _chipSelect);
  EndSend();

#ifdef WRITETHROUGH_CACHE
  _cache[_cacheOffset] = data;
#endif

  _lcdx++;

  if (_lcdx >= 64) {
    if (_chipSelect == LCD_CS1)
      gotoxy(64, _lcdy);
    else
      gotoxy(0, _lcdy + 8);
  }
  else {
#ifdef WRITETHROUGH_CACHE
    _cacheOffset += 8;
#endif
  }

}

void Display_I2C_LCD::letter(byte c, const boolean inv) {
  if (c < 0x20 || c > 0x7F)
    c = 0x7F;

  c -= 0x20;

  if (_lcdx >= 60 && _chipSelect == LCD_CS2)
    gotoxy(0, _lcdy + 8);

  for (byte x = 0; x < 5; x++)
    writeData(pgm_read_byte(&font[c][x]), inv);
  writeData(0, inv);

}

void Display_I2C_LCD::string(const char *s, const boolean inv) {
  char c;
  while (c = *s++)
    letter(c, inv);
}

/*
  - copies aseries of bytes to the LCD display
*/
void Display_I2C_LCD::blit(const byte *pic, const unsigned int size) {
  for (unsigned int x = 0; x < size; x++, pic++)
    writeData(pgm_read_byte(pic));
}


/*
  - clear rectangle x1,y1,x2,y2
*/
void Display_I2C_LCD::clear(const byte x1,
                                      const byte y1,
                                      const byte x2,
                                      const byte y2,
                                      const byte val)
{
  for (byte y = y1; y <= y2; y += 8) {
    gotoxy(x1, y);
    for (byte x = x1; x <= x2; x++)
      writeData(val);
  }

  gotoxy(x1, y1);
}

/*
  - Write or clear a pixel at x,y
*/
void Display_I2C_LCD::setPixel(const byte x, const byte y,
                                         const byte val) {
  gotoxy(x, y);
  byte c = readData();
  if (val)
    c |= 1 << (y & 7);
  else
    c &= ~(1 << (y & 7));

  gotoxy(x, y);

  writeData(c);

}

/*
  - Fill the rectangle x1,y1,x2,y2
*/
void Display_I2C_LCD::fillRect(
    const byte x1,
    const byte y1,
    const byte x2,
    const byte y2,
    const byte val)
{
  for (byte y = y1; y <= y2; y++)
    for (byte x = x1; x <= x2; x++)
      setPixel(x, y, val);
}


/*
  - Frame the rectangle x1,y1,x2,y2 
*/
void Display_I2C_LCD::frameRect(
    const byte x1,
    const byte y1,
    const byte x2,
    const byte y2,
    const byte val,
    const byte width) {
  byte x, y, i;

  for (x = x1; x <= x2; x++)
    for (i = 0; i < width; i++)
      setPixel(x, y1 + i, val);

  for (x = x1; x <= x2; x++)
    for (i = 0; i < width; i++)
      setPixel(x, y2 - i, val);

  for (y = y1; y <= y2; y++)
    for (i = 0; i < width; i++)
      setPixel(x1 + i, y, val);

  for (y = y1; y <= y2; y++)
    for (i = 0; i < width; i++)
      setPixel(x2 - i, y, val);

}

/*
  - Draw a line from x1,y1 to x2,y2
*/
void Display_I2C_LCD::Line(
    const byte x1,
    const byte y1,
    const byte x2,
    const byte y2,
    const byte val)
{
  byte x, y;

  if (x1 == x2) {
    for (y = y1; y <= y2; y++)
      setPixel(x1, y, val);
    return;
  }

  if (y1 == y2) {
    for (x = x1; x <= x2; x++)
      setPixel(x, y1, val);
    return;
  }

  int x_diff = x2 - x1, y_diff = y2 - y1;

  if (abs(x_diff) > abs(y_diff)) {
    int x_inc = 1;
    int y_inc = (y_diff << 8) / x_diff;
    int y_temp = y1 << 8;
    if (x_diff < 0)
      x_inc = -1;

    for (x = x1; x != x2; x += x_inc) {
      setPixel(x, y_temp >> 8, val);
      y_temp += y_inc;
    }

    return;
  }

  int x_inc = (x_diff << 8) / y_diff;
  int y_inc = 1;
  if (y_diff < 0)
    y_inc = -1;

  int x_temp = x1 << 8;
  for (y = y1; y != y2; y += y_inc) {
    setPixel(x_temp >> 8, y, val);
    x_temp += x_inc;
  }

}

void Display_I2C_LCD::Scroll(const byte y)
{
  byte old_cs = _chipSelect;
  _chipSelect = LCD_CS1;
  cmd(LCD_DISP_START | (y & 0x3F));
  _chipSelect = LCD_CS2;
  cmd(LCD_DISP_START | (y & 0x3F));
  _chipSelect = old_cs;
}
