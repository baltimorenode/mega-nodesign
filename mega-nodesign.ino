//choose what sign does before begin()

#include "Mega_Nodesign.h"

Mega_Nodesign sign;

byte global_mode = 0; //always check this value

void setup() {
  Serial.begin(115200); //lets start with fast
  
  while (Serial.available() == 0) { ; } //kill time
  char val = Serial.read();
  
  switch (val) {
    case 1:
      //first mode
      global_mode = 1;
      break;
  }
  //checking vs just set mode to val?
  
  sign.begin(); //sign starts

}

void loop() {
  //add your code here
}
