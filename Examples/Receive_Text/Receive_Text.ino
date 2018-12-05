//receives a text string over serial port, display  3 lines of text on sign
//push existing messages down the sign

//this implemenation uses 4 char arrays, but temp is not needed
//because the frame buffer stores the aformation of the text strings could write Serial to A
//this implementation is easier to follow

#include "Mega_Nodesign.h"

#define Text_Color	WHITE

//arrays to hold text strings
char A[9], B[9], C[9], temp[9];
int pos = 0;

Mega_Nodesign sign;

void setup() {
  Serial.begin(9600); //this could be faster, but it's only short infrequent datagrams

  sign.begin();
  sign.Send_Picture(); //to clear logo
}

void loop() {
  //nothing needed here for this test
}

void serialEvent() { //modified from the serialEvent Example
  while (Serial.available()) {
    //get the new byte
    char inChar = (char)Serial.read();
       
    if (inChar != '\n') {
      if (pos <= 8) { //add char to temp array
        temp[pos] = inChar;
        pos++;
      }
    }
    else { //put temp onto sign
      for(int i=0; i<=8; i++) { //shift text down sign
        C[i] = B[i]; B[i] = A[i]; A[i] = temp[i];
      }
      //display
      sign.Put_String(1, 1, A, 9, Text_Color); sign.Put_String(2, 1, B, 9, Text_Color); sign.Put_String(3, 1, C, 9, Text_Color);
      sign.Send_Picture();
      
      pos = 0; //back to start

      //Serial "Echo" for testing
      Serial.print("A: ");
      for(int j=0; j<=8; j++) { Serial.print(A[j]); }
      Serial.println(' ');
      Serial.print("B: ");
      for(int j=0; j<=8; j++) { Serial.print(B[j]); }
      Serial.println(' ');
      Serial.print("C: ");
      for(int j=0; j<=8; j++) { Serial.print(C[j]); }
      Serial.println(' '); Serial.println(' ');
    }    
  }
}
