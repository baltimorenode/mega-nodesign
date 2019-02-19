//choose what sign does before begin()

#include "Mega_Nodesign.h"

Mega_Nodesign sign;

byte global_mode = 0; //always check this value

void setup() {
  Serial.begin(115200); //lets start with fast
  
  while (Serial.available() == 0) { ; } //kill time
  char val = Serial.read();
  
  switch (val) {
    case 1: //Random
      //first mode
      global_mode = 1;
      break;
    case 2: //Receive Text
      //second mode
      global_mode = 2;
      break;
   case 3: //Pixelflut
      sign.Set_Guard(true);
      global_mode = 3;
      break;
  case 4: //Receive Pictures
      //fourth mode
      global_mode = 4;
      break;
  case 5:
      //fifth mode
      global_mode = 5;
      break;
  }
  //checking vs just set mode to val?
  
  sign.begin(); //sign starts

}

void loop() {
  //add your code here
    switch (global_mode) {
    case 1:
      static int Next_Color = 0;
      for (int temp = 0; temp <= 150; temp++) { //run a random pattern for a while
        for (int i=1; i<=24; i++) {
          for (int j=1; j<=48; j++) {
            sign.Set_Pixel(i, j, DEFAULT_BRIGHT, Next_Color);
            Next_Color += random(255) - 128;
            if (Next_Color >= 0x0FFF) { Next_Color = random(4095); }
          }
        }
        sign.Send_Picture(); //changes the entire frame buffer then display new image
      }
      sign.Clear_Screen(); delay(500); sign.Load_Logo(); sign.Send_Picture(); delay(5000); //show the logo for 5 seconds
      break;
    case 2:
        //nothing needed in loop
      break;
   case 3: //Pixelflut
      sign.Recv_Pixel();
      sign.Send_Picture();
      break;
  case 4:

      break;
  case 5:

      break;
  }
  
  //need to use correct "Send_Picture()"
  //waiting on game branch
}
