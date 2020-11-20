#ifndef Display_I2C_LCD_H
#define Display_I2C_LCD_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif

#include <avr/pgmspace.h>

#define IODIRA 0x00
#define IODIRB 0x01
#define IOPOLA 0x02
#define IOPOLB 0x03
#define GPINTENA 0x04
#define GPINTENB 0x05
#define DEFVALA 0x06
#define DEFVALB 0x07
#define INTCONA 0x08
#define INTCONB 0x09
#define IOCON 0x0A
#define GPPUA 0x0C
#define GPPUB 0x0D
#define INFTFA 0x0E
#define INFTFB 0x0F
#define INTCAPA 0x10
#define INTCAPB 0x11
#define GPIOA 0x12
#define GPIOB 0x13
#define OLLATA 0x14
#define OLLATB 0x15
#define LCD_CS1 0b00000100
#define LCD_CS2 0b00001000
#define LCD_RESET 0b00010000
#define LCD_DATA 0b00100000
#define LCD_READ 0b01000000
#define LCD_ENABLE 0b10000000

#define LCD_ON 0x3F
#define LCD_OFF 0x3E
#define LCD_SET_ADD 0x40
#define LCD_SET_PAGE 0xB8
#define LCD_DISP_START 0xC0

class Display_I2C_LCD : public Print {
private:
  byte _chipSelect;
  byte _lcdx;
  byte _lcdy;)
  
  byte _port;
  byte _ssPin;

  void WriteExpander(const byte reg, const byte data);
  byte readData();
  void startSend();
  void SendByte(const byte what);
  void EndSend();

  boolean _invmode;

#ifdef WRITETHROUGH_CACHE
  byte _cache[64 * 128 / 8];
  int _cacheOffset;
#endif

public:
  Display_I2C_LCD() : _port(0x20), _ssPin(10), _invmode(false){};

  void Begin(const byte port = 0x20, const byte i2cAddress = 0,
             const byte ssPin = 0);
  void cmd(const byte data);
  void gotoxy(byte x, byte y);
  void writeData(byte data, const boolean inv);
  void writeData(byte data) { writeData(data, _invmode); }
  void letter(byte c, const boolean inv);
  void letter(byte c) { letter(c, _invmode); }
  void string(const char *s, const boolean inv);
  void string(const char *s) { string(s, _invmode); }
  void blit(const byte *pic, const unsigned int size);
  void clear(const byte x1 = 0, const byte y1 = 0, const byte x2 = 127,
             const byte y2 = 63, const byte val = 0);
  void setPixel(const byte x, const byte y, const byte val = 1);
  void fillRect(const byte x1 = 0, const byte y1 = 0, const byte x2 = 127,
                const byte y2 = 63, const byte val = 1);
  void frameRect(const byte x1 = 0, const byte y1 = 0, const byte x2 = 127,
                 const byte y2 = 63, const byte val = 1, const byte width = 1);
  void Line(const byte x1 = 0, const byte y1 = 0, const byte x2 = 127,
            const byte y2 = 63, const byte val = 1);
  void Scroll(const byte y = 0);

#if defined(ARDUINO) && ARDUINO >= 100
  size_t write(uint8_t c) {
    letter(c, _invmode);
    return 1;
  }
#else
  void write(uint8_t c) { letter(c, _invmode); }
#endif

  void setInv(boolean inv) { _invmode = inv; }
};

#endif
