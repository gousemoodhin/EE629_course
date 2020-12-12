# EE629_course

# Project: LCD displays using I2C protocol

## Progress: I2C code implementation is completed

## I2C
Introduction:

I2C (Inter-Integrated Circuit), pronounced I-squared-C. is a synchronous, multi-master, multi-slave, packet switched, single-ended, serial communication bus invented in 1982 by Philips Semiconductor (now NXP Semiconductors). It is two-wire interface is extremely useful for connecting multiple devices, all devices share the same two pins and each device is addressable. Each device needs to have a unique address in the range 8 to 119. The I2C bus is a simple two-wire bi-directional serial communication system that is intended for communication between microcontrollers and their peripherals over short distances.The Serial Clock Line (SCL) and the Serial Data line (SDA) are both bidirectional.

![alt text](https://www.analog.com/-/media/analog/en/landing-pages/technical-articles/i2c-primer-what-is-i2c-part-1-/36684.png?la=en&w=900)

- I2C is a serial communication protocol. It provides good support to the slow devices, such as EEPROM, ADC, I2C LCD, and RTC.
- The bus is initially idle where both SCL and SDA are both high. This means no device is pulling SCL or SDA low. The communication on the bus, which begins with a START and ends with a STOP, consists of five components
- START (S) is used by the master to initiate a transfer DATA is sent in 8-bit blocks and consists of 7-bit address and 1-bit direction from the master control code for master to slaves information from master to slave information from slave to master. 
- ACK (A) is used by slave to respond to the master after each 8-bit data transfer.
- RESTART (R) is used by the master to initiate additional transfers without releasing the bus. 
- STOP (P) is used by the master to signal the transfer is complete and the bus is free.
- A slow slave uses clock stretching to give it more time to react, and masters will use arbitration when two or more masters want the bus at the same time.

Text LCD displays are all very well, but they suffer from various limitations.

- Don't have a huge amount of screen to play with, 
- We can't do special effects (like inverse).
- We can't draw boxes and gauges.

## I/O Expander
Configure Port A to be all outputs:

Wire.beginTransmission (0x20);  // expander has I2C address 0x20
Wire.send (0x00);   // register 0 is the I/O direction register for Port A
Wire.send (0x00);   //  0x00 for all pins to output mode, 0xFF for all pins to input mode
Wire.endTransmission (); 

![alt text](https://www.electronicsforu.com/wp-contents/uploads/2016/11/lcd-and-arduino.-800x691.jpg)


## References
1) [CircuitBasics](https://www.circuitbasics.com/basics-of-the-i2c-communication-protocol/#:~:text=I2C%20is%20a%20serial%20communication,always%20controlled%20by%20the%20master.)

2) [Sparkfun](https://learn.sparkfun.com/tutorials/i2c/all)
