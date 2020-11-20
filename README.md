# EE629_course
Work related EE 629 IOT course 

# Project: LCD displays using I2C protocol

Progress: Implementing code and understanding Architecture

## I2C
Introduction:

I2C (Inter-Integrated Circuit), pronounced I-squared-C. is a synchronous, multi-master, multi-slave, packet switched, single-ended, serial communication bus invented in 1982 by Philips Semiconductor (now NXP Semiconductors). It is two-wire interface is extremely useful for connecting multiple devices, all devices share the same two pins and each device is addressable. Each device needs to have a unique address in the range 8 to 119. The I2C bus is a simple two-wire bi-directional serial communication system that is intended for communication between microcontrollers and their peripherals over short distances.The Serial Clock Line (SCL) and the Serial Data line (SDA) are both bidirectional.
- I2C is a serial communication protocol. It provides good support to the slow devices, such as EEPROM, ADC, I2C LCD, and RTC.
- The bus is initially idle where both SCL and SDA are both high. This means no device is pulling SCL or SDA low. The communication on the bus, which begins with a START and ends with a STOP, consists of five components
- START (S) is used by the master to initiate a transfer DATA is sent in 8-bit blocks and consists of 7-bit address and 1-bit direction from the master control code for master to slaves information from master to slave information from slave to master. 
- ACK (A) is used by slave to respond to the master after each 8-bit data transfer.
- RESTART (R) is used by the master to initiate additional transfers without releasing the bus. 
- STOP (P) is used by the master to signal the transfer is complete and the bus is free.
- A slow slave uses clock stretching to give it more time to react, and masters will use arbitration when two or more masters want the bus at the same time.
