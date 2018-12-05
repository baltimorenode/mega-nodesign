
//create sign object
//begin
//testing methods

#include "Mega_Nodesign.h"

Mega_Nodesign sign;

void setup() {
  Serial.begin(115200);
  //Serial.println("Baltimore Node Mega Nodesign");

  sign.begin(); //sign starts
}

void loop() {
  sign.Recv_Screen();

  sign.Send_Picture();
}
