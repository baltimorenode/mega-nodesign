#include "Mega_Nodesign.h"

Mega_Nodesign sign;
unsigned int Next_Color = 0x0000;

void setup() {
  Serial.begin(9600);
  sign.begin();
}

void loop() {
  //run a random pattern for a while
  for (int temp = 0; temp <= 150; temp++) {
    for (int i=1; i<=24; i++) {
      for (int j=1; j<=48; j++) {
        sign.Set_Pixel(i, j, DEFAULT_BRIGHT, Next_Color);
        Next_Color += random(255) - 128;
        if (Next_Color >= 0x0FFF) {
          Next_Color = random(4095);
        }
      }
    }
    //changes the entire frame buffer then display new image
    sign.Send_Picture();
  }

  //show the logo for 5 seconds
  sign.Clear_Screen();
  delay(500);
  sign.Load_Logo();
  sign.Send_Picture();
  delay(5000);
}
