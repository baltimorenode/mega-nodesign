//use pins 16-19 in setup to set functional mode for the sign
//combines all examples and ideas into one sketch

#include "Mega_Nodesign.h"

byte Global_Mode = 0;

Mega_Nodesign sign;

void setup() {
  //16 - 19  LSB - MSB
  //0 - Random
  //1 - Receive Text
  //2 - Receive Pictures
  //3 - Pixelflut
  //4 - Game of Life
  //5 - Snake
  //6 - 
  if (digitalRead(16) == HIGH) { Global_Mode += 1; }
  if (digitalRead(17) == HIGH) { Global_Mode += 2; }
  if (digitalRead(18) == HIGH) { Global_Mode += 4; }
  if (digitalRead(19) == HIGH) { Global_Mode += 8; }

  sign.begin(); //sign starts

  switch (Global_Mode) {
    case 0:
      //nothing
      break;
    case 2:
    case 3:
      sign.Set_Guard(true);
    case 1:
      Serial.begin(115200);
      break;
    case 4:
      //nothing
      break;
    case 5:
      //nothing
      break;
  }
}

void loop() {
  switch (Global_Mode) {
    case 0: //Random
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
    case 1: //Receive Text
      //nothing needed in loop
      break;
    case 2: //Receive Pictures
      sign.Recv_Frame();
      sign.Send_Picture();
      break;
    case 3: //Pixelflut
      sign.Recv_Pixel();
      sign.Send_Picture();
      break;
    case 4: //Game of Life
      while (true) {
        //adsf
      }
      break;
    case 5: //Snake
      while (true) {
        //adsf
      }
      break;
  }
}

void serialEvent() { //modified from the serialEvent Example
  switch(Global_Mode) {
    case 0:
      //nothing needed
      break;
    case 1:
      static char A[9], B[9], C[9], temp[9]; static int pos = 0;
      while (Serial.available()) {
        char inChar = (char)Serial.read(); //get the new byte           
        if (inChar != '\n') { //add char to temp array
          if (pos <= 8) { temp[pos] = inChar; pos++; }
        } else { //put temp onto sign and shift text down sign
          for(int i=0; i<=8; i++) { C[i] = B[i]; B[i] = A[i]; A[i] = temp[i]; }
          //display
          sign.Put_String(1, 1, A, 9, WHITE); sign.Put_String(2, 1, B, 9, WHITE); sign.Put_String(3, 1, C, 9, WHITE); sign.Send_Picture();
          pos = 0; //back to start
          //Serial "Echo" for testing
          Serial.print("A: "); for(int j=0; j<=8; j++) { Serial.print(A[j]); } Serial.println(' ');
          Serial.print("B: "); for(int j=0; j<=8; j++) { Serial.print(B[j]); } Serial.println(' ');
          Serial.print("C: "); for(int j=0; j<=8; j++) { Serial.print(C[j]); } Serial.println(' '); Serial.println(' ');
        }    
      }
      break;
    case 2:
      //nothing needed
      break;
    case 3:
      //nothing needed
      break;
  }
}
