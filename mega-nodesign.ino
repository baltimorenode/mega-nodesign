//Main sketch file
//Created by: Chris Lindsay for BaltimoreNode

/* *****************************************
 * This sketch template creates a virtual frame buffer abstraction
 * It allows the user to create any desired graphic
 * Using the 24x48 G35 board for display
 *
 * *****************************************
 * Please note you must call Send_Picture() every time you want the display to change
 * The update takes about 4ms during which time Micros() and Millis() will not be updated
 *   The timers for these functions has to be disabled during Send_Picture()
 * The user has 4K of RAM and 2K of EEPROM to use in there code
 * 
 * *****************************************
*/

#include "Node_Header.h"

#define SER_BAUD 9600

//add your globals here

void setup() {
  Serial.begin(SER_BAUD);

  Setup_Node_Sign(); 

  //start your setup code here:

}

void loop() {
  //add you loop code here
  
  //some test code
  unsigned int v = 0x0003;
  for (int i = 1; i <= 24; i++) {
    for (int j = 1; j <= 48; j++) {
      Set_Pixel(i, j, 0x06, v);
      Send_Picture();
      v += 17;
    }
  }
  Clear_Screen();

}

