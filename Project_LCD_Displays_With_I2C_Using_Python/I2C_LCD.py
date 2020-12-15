"""
Author: Gousemoodhin Nadaf

IOT Project:
In this project we use I2C to read values from external sensor and diaply data on LCD display
- LCD 16x2 Display
"""

import DRIVER_LCD
import time
Handle_Lcd_Display = DRIVER_LCD.lcd()

while True:
    print("Sending Data to LCD Display...")
    Handle_Lcd_Display.Display_Text_On_Lcd("Hello Stevens", 5) # 5 indicates display on consoles, (do not have hardware)
    Handle_Lcd_Display.Display_Text_On_Lcd("IOT Project", 5)
    time.sleep(1)
    #Handle_Lcd_Display.Display_Lcd_Clear() # enable for real hardware
    time.sleep(1)
