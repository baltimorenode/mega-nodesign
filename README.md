# mega-nodesign

Baltimore Node G35 Sign User Guide

::The Grand Design::

We have a low resolution 4’ high 8’ long RGB sign made from repurposed GE G35 Christmas light strings and an Arduino Mega. The original controllers have been removed from the strings of lights and the data lines have been connected to 6 of the 8bit ports on the Mega.

::System Hardware Overview::

Power Supply:
The large blue power supply provides 5v to the light board and the Arduino Mega.

Display Board:
G35 Light strings are formed into a 24 row by 48 column display board. The lights are zip tied to a white beg board with aluminum L-bracket supports.

Lights:
There are 48 lines of 24 G35 Christmas lights connected to an Arduino Mega. Physically there are only 24 lines of lights. The data line was cut separting each string into 2 sets of 24 lights. This cuts the time to update all the lights in half.

Ports:
The following AVR ports are completely used for the display - A B C F K L
Please note that this percludes the use of the SPI bus, but does not interfere with the I2C or UARTS.

::System Software Overview::

Memory:
The frame buffer uses up 4K of the available 8K of ram. Leaving the remaining 8K available for additional code.
The first 1248 bytes of the EEPROM are filled with the Baltimore Node logo. Remember that the EEPROM addressing is zero indexed.

Startup:
The template sketch automatically creates the frame buffer. Then fills the frame buffer with addressing data. Ports A B C F K and L are all set to OUTPUT and have their value set to LOW. The enumeration is performed on the strings of G35 lights. The Serial port is started at SER_BAUD rate. The logo is loaded from the EEPROM into the frame buffer and displayed for 5 seconds. The screen is cleared, but the lights are NOT updated. Then the user’s setup code is performed.

Color Constants:
All colors are represented by the LS12B of an unsigned int value. Format: – 4 Brightness, 4b Blue, 4b Green, 4b Red.
RED  BLUE  GREEN  PURP  YELLOW  CYAN  ORANGE  WHITE  BLACK

::User Functions::
located in Node_Header.h

Setup_Node_Sign():
This function is used by the setup function to perform all nessesary initialization of the G35 light strings. There is no need for the user to ever call this function.

Send_Picture():
This function must be called whenever the user desires to update the display. Please note this function disables all interrupts while performing the light update. So micros() and millis() will not be updated.

Send_Picture_Guard():
This functions sends ‘s’ over the serial port before updating the display. Then sends ‘d’ after completion. Please note this function disables all interrupts while performing the update.

Set_Pixel(row, col, high_bright, color):
This function changes a color value in the frame buffer. Row is 1<>24. Col is 1<>48. Bright is not currently implemented so any byte value will do. Color is any unsigned int value like a Color Constant. Only the lower 12 bits are used to set the color value in the frame buffer. Please note that it’s not currently possible to change the brightness.

Clear_Screen():
This function changes the color value in the frame buffer for all the pixels to BLACK.

Load_Logo():
This function updates the frame buffer with a copy of the Baltimore Node logo. Please note that the right most 22 columns are not changed by this function.
