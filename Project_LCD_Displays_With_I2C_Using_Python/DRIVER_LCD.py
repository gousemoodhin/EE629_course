"""
- DRIVER_LCD
"""

import I2C
from time import *

En = 0b00000100
Rw = 0b00000010
Rs = 0b00000001

# Common LCD address
ADDRESS = 0x27

LCD_CLEARDISPLAY    = 0x01
LCD_RETURNHOME      = 0x02
LCD_ENTRYMODESET    = 0x04
LCD_DISPLAYCONTROL  = 0x08
LCD_CURSORSHIFT     = 0x10
LCD_FUNCTIONSET     = 0x20
LCD_SETCGRAMADDR    = 0x40
LCD_SETDDRAMADDR    = 0x80
LCD_ENTRYRIGHT      = 0x00
LCD_ENTRYLEFT       = 0x02
LCD_DISPLAYON       = 0x04
LCD_DISPLAYOFF      = 0x00
LCD_CURSORON        = 0x02
LCD_CURSOROFF       = 0x00
LCD_BLINKON         = 0x01
LCD_BLINKOFF        = 0x00
LCD_DISPLAYMOVE     = 0x08
LCD_CURSORMOVE      = 0x00
LCD_MOVERIGHT       = 0x04
LCD_MOVELEFT        = 0x00
LCD_8BITMODE        = 0x10
LCD_4BITMODE        = 0x00
LCD_2LINE           = 0x08
LCD_1LINE           = 0x00
LCD_5x10DOTS        = 0x04
LCD_5x8DOTS         = 0x00
LCD_BACKLIGHT       = 0x08
LCD_NOBACKLIGHT     = 0x00
LCD_ENTRYSHIFTINCREMENT = 0x01
LCD_ENTRYSHIFTDECREMENT = 0x00

# This Class initializes LCD object.
class lcd:
   def __init__(self):
      self.lcd_device = I2C.I2C_Hardware(ADDRESS)
      #self.lcd_device = 0x3f
      self.Write_LCD_Display(0x03)
      self.Write_LCD_Display(0x03)
      self.Write_LCD_Display(0x03)
      self.Write_LCD_Display(0x02)

      self.Write_LCD_Display(LCD_FUNCTIONSET | LCD_2LINE | LCD_5x8DOTS | LCD_4BITMODE)
      self.Write_LCD_Display(LCD_DISPLAYCONTROL | LCD_DISPLAYON)
      self.Write_LCD_Display(LCD_CLEARDISPLAY)
      self.Write_LCD_Display(LCD_ENTRYMODESET | LCD_ENTRYLEFT)


   def LCD_SEND(self, data):
      self.lcd_device.Write_I2C(data | En | LCD_BACKLIGHT)
      sleep(.0005)
      self.lcd_device.Write_I2C(((data & ~En) | LCD_BACKLIGHT))
      sleep(.0001)

   def Write_LCD_Display_4_Bits(self, data):
      self.lcd_device.Write_I2C(data | LCD_BACKLIGHT)
      self.LCD_SEND(data)

   def Write_LCD_Display(self, cmd, mode=0):
      self.Write_LCD_Display_4_Bits(mode | (cmd & 0xF0))
      self.Write_LCD_Display_4_Bits(mode | ((cmd << 4) & 0xF0))

   def Display_On_Console(self, string):
      print("Displaying on Virtual LCD (console) ")
      print('-' * 60)
      print(string)
      print('-' * 60)
    
   def Display_Text_On_Lcd(self, string, line):
      if line == 1:
         self.Write_LCD_Display(0x80)
      if line == 2:
         self.Write_LCD_Display(0xC0)
      if line == 3:
         self.Write_LCD_Display(0x94)
      if line == 4:
         self.Write_LCD_Display(0xD4)
      if line == 5:
         self.Display_On_Console(string) #If we do not have LCD hardware, display data on console
         return
      
      #for char in string:
       #  self.Write_LCD_Display(ord(char), Rs) # Enable for real Hardware

   
   #Flush the LCD display
   def Display_Lcd_Clear(self):
      self.Write_LCD_Display(LCD_CLEARDISPLAY)
      self.Write_LCD_Display(LCD_RETURNHOME)

