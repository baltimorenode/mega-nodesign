Baltimore Node G35 Sign User Guide
By: Chris Lindsay

::System Hardware Overview::

Power Supply:
The large blue power supply provides 5v to the light board and the Arduino Mega.

Display Board:
G35 Light strings are formed into a 24 row by 48 column display board.

Lights:
There are 48 lines of 24 G35 Christmas lights connected to an Arduino Mega. 

Ports:
The following AVR ports are completely used for the display - A B C F K L

Pins:
string : pin
power relay: 
1: 22		PORTA
2: 23
3: 24
4: 25
5: 26
6: 27
7: 28
8: 29
9: 53		PORTB
10: 52
11: 51
12: 50
13: 10
14: 11
15: 12
16: 13
17: 37		PORTC
18: 36
19: 35
20: 34
21: 33
22: 32
23: 31
24: 30
25: A0		PORTF
26: A1
27: A2
28: A3
29: A4
30: A5
31: A6
32: A7
33: A8		PORTK
34: A9
35: A10
36: A11
37: A12
38: A13
39: A14
40: A15
41: 49		PORTL
42: 48
43: 47
44: 46
45: 45
46: 44
47: 43
48: 42

::System Software Overview::

Memory:
The frame buffer uses up 4K of the available 8K of RAM. Leaving YK available for additional code. The first 1248 bytes of the EEPROM are filled with the Baltimore Node logo. The next 640 bytes of the EEPROM are filled with the 5x8 font.

Startup:
The template sketch automatically creates the frame buffer. Then fills the frame buffer with addressing data. Ports A B C F K and L are all set to OUTPUT and have their value set to LOW. The enumeration is performed on the strings of G35 lights. The logo is loaded and displayed for 5 seconds. Then the user’s setup code is performed.

Color Constants:
All colors are represented by the LS12B of an unsigned int. Format – 4 Brightness, 4b Blue, 4b Green, 4b Red.

RED  BLUE  GREEN  PURPLE  YELLOW  CYAN  ORANGE  WHITE  BLACK

User Functions:
Mega_Nodesign(): constructor
This function enummerates the light strings, prepares the masks and displays the logo onto the light strings. The masks are cleared but the user must call Send_Picture() to update the light strings.

begin():
Enables power to the lightstrings. Enummerates the Ids for the lights on all the strings. Masks are filled with ID values. The logo is loaded and sent to the sign. After a delay of 5 seconds the masks are cleared. It is up to the user code to update the sign, this keeps the logo displayed until real content is ready.

stop();
Disables power to the lightstrings. After this is called nothing will be displayed on the sign.

Send_Picture():
This function must be called whenever the user desires to update the display. Please note this function disables all interrupts while performing the update. So micros() and millis() will not be updated.

Set_Guard(): Get_Guard():
The guard sends an ‘s’ before updating the light strings with Send_Picture and an ‘d’ once complete.

Get_Working():
Returns true if stop() has not been called.

Set_Pixel(row, col, high_bright, color):
This function changes a color value in the frame buffer. Row is 1<>24. Col is 1<>48. Bright is not currently implemented so any byte value will do. Color is any value like a Color Constant.

Clear_Screen():
This function changes all the color values in the masks to BLACK

Load_Logo():
This function updates the frame buffer with a copy of the Baltimore Node logo. Please note that the right most 22 columns are not changed by this function.

Put_Char(row, col, letter, color):
Puts a 5x8 pixel font image of color into the frame buffer based on the 3 row by 8 column font of letter. 

Put_String(row, col, text, len, color):
Puts a series of 5x8 pixel font images of color into the frame buffer. There is a 1 column space between each letter in the string. Supports C’ish style string, there is no NULL character termination, so len is only the number of characters.
