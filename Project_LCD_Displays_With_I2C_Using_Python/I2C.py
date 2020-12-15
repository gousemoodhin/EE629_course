import smbus
from time import *

class I2C_Hardware:
   def __init__(self, addr, port=1):
      self.addr = addr
      #self.bus = smbus.SMBus(port) # Enable for real Hardware
      return

   def Write_I2C(self, cmd):
      #self.bus.write_byte(self.addr, cmd) # Enable for real Hardware
      sleep(0.0001)
      return

   def Write_I2C_Arg(self, cmd, data): 
      #self.bus.write_byte_data(self.addr, cmd, data) # Enable for real Hardware
      sleep(0.0001)
      return

   def Write_I2C_Block_Data(self, cmd, data):
      #self.bus.Write_I2C_Block_Data(self.addr, cmd, data) # Enable for real Hardware
      sleep(0.0001)
      return

   def Read(self):
      #return self.bus.Read_Byte(self.addr) # Enable for real Hardware
      return

   def Read_Data(self, cmd):
      #return self.bus.Read_Byte_Data(self.addr, cmd) # Enable for real Hardware
      return

   def Read_I2C_Block_Data(self, cmd):
      #return self.bus.Read_Block_Data(self.addr, cmd) # Enable for real Hardware
      return
