"""
Author: Gousemoodhin Nadaf

IOT Project:
In this project we use I2C to read values from external sensor and diaply data on LCD display
- LCD 16x2 Display
"""

import DRIVER_LCD
import time
import Read_Weather_Info
Sensor = Read_Weather_Info.Read_Weather()
Handle_Lcd_Display = DRIVER_LCD.lcd()

def main():
    print("Sending Data to LCD Display...")
    #Read Distance Measurement and Weather Information
    weather_1, weather_2, the_distance = Sensor.main_1()
    
    #Send Sensor Info to LCD display 
    Handle_Lcd_Display.Display_Text_On_Lcd(weather_1, 5) # 5: Indicates display on consoles, (do not have hardware)
    Handle_Lcd_Display.Display_Text_On_Lcd(weather_2, 5)
    Handle_Lcd_Display.Display_Text_On_Lcd(the_distance, 5)
    time.sleep(1)
    # Clear the LCD display
    #Handle_Lcd_Display.Display_Lcd_Clear() # enable for real hardware
    #time.sleep(1)


if __name__ == "__main__":
    main()