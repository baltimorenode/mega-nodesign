//create sign object
//begin
//testing methods

#include "Mega_Nodesign.h"

Mega_Nodesign sign;

void setup() {
  Serial.begin(9600);
  Serial.println("Baltimore Node Mega Nodesign");

  sign.begin(); //sign starts

  // put your setup code here, to run once:
}

void loop() {
  for (int i=1; i<=24; i++) {
    for (int j=1; j<=48; j++) {
      sign.Set_Pixel(i, j, DEFAULT_BRIGHT, RED);
      sign.Send_Picture();
    }
  }
  delay (500);
  for (int i=1; i<=24; i++) {
    for (int j=1; j<=48; j++) {
      sign.Set_Pixel(i, j, DEFAULT_BRIGHT, YELLOW);
      sign.Send_Picture();
    }
  }
  delay(500);
  for (int i=1; i<=24; i++) {
    for (int j=1; j<=48; j++) {
      sign.Set_Pixel(i, j, DEFAULT_BRIGHT, BLUE);
      sign.Send_Picture();
    }
  }

  delay(3000);

  Serial.println("OK!");
  sign.Clear_Screen();
  sign.Send_Picture();
  delay(500);

//  sign.stop();
//  while (true) { ; } //infinite do nothing loop

}
