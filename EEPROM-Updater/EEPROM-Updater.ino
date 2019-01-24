/*************************************************************************
 / This sketch saves a matrix of color values into the Arduino Mega's EEPROM
 / Then the bitmask for the font is saved
 / Then it prints the contents of the EEPROM over the Serial console
 / This is a support sketch for the mega_modesign project
 /
 / Created by Chris Lindsay for BaltimoreNode
 / 
 / *******************************************************************************
*/
#include <EEPROM.h>

#include "Font.h"
#include "Logo.h"

//size of logo
int rows = 24; int cols = 26;

//starting address in EEPROM
int addr = 0;

void setup() {
  //write logo data to EEPROM
  for (int i=0; i <= rows-1; i++) {
    for (int j=0; j <= cols-1; j++) {
      //split unsigned int and write bytes to EEPROM
      EEPROM.write(addr, highByte(logo[i][j]));
      addr++;
      EEPROM.write(addr, lowByte(logo[i][j]));
      addr++;
    }
  }
  //write font data to EEPROM
  for (int i=0; i<= 639; i++) {
    EEPROM.write(addr, f8x5[i]);
    addr++;
  }
  Serial.begin(9600);
}

void loop() {
  unsigned int val;
  addr = 0;

  //validate contents of EEPROM
  for (int i=0; i <= rows-1; i++) {
    for (int j=0; j <= cols-1; j++) {
      val = EEPROM.read(addr);
      addr++;
      val = val << 8;
      val += EEPROM.read(addr);
      addr++;
      Serial.print(val);
      Serial.print(" ");
    }
    Serial.println("");
  }
  Serial.println("----------------------------------------");
  for (int i=0; i <= 128; i++) { //all the letters
    for (int j=0; j <= 5; j++) { //single letter
      val = EEPROM.read(addr);
      Serial.print(val);
      Serial.print(" ");
      addr++;
    }
    Serial.println("");
  }
  Serial.println("----------------------------------------");
  delay(5000);
}
