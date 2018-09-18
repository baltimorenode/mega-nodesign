/*
 * Mega_Node_Sign
 * use Arduino Mega to drive 48 (2 sets of 24) GE G35 light strings simultaniously
 * each row on board is cut in half, can drive both at once
 * so 2 24x24 arrays side by side, 18,720 uSeconds best case, 50 frames a second
 * 
 * created by Chris Lindsay for Baltimore Node
 * created using documentation from deepdarc.com
*/

/*
//desc: use 6 ports on Mega to send string data A, B (pins 10-13, 50-53), C, F, K, and L
//24x26 unsigned int Logo is stored at start of EEPROM
//******************DATAGRAM*****************************
//Idle bus state: Low
//Start Bit: High for 10uSeconds
//Zero Low for 10uSeconds, High for 20uSeconds
//One Low for 20uSeconds, High for 10uSeconds
//30uSeconds between frames
//
//all bits are the same length after Start
//so do a state check every 10uSeconds
//
//Each frame is 26 bits long and has the following format:
//Start bit
//6-Bit Bulb Address, MSB first
//8-Bit Brightness, MSB first    12-15 (only the low 4 bits fill out unsigned int)
//4-Bit Blue, MSB first     8-11
//4-Bit Green, MSB first      4-7
//4-Bit Red, MSB first      0-3
//pack into unsigned int, this uses only 4 bits for brightness
// 4b bright, 4b, blue, 4b green, 4b red
//max brightness is 0xCC
//********************************************************
*/

#ifndef _Node_Header_
#define _Node_Header_

#include <EEPROM.h>

//colors 0BGR
#define RED     0x000FU
#define BLUE    0x0F00U
#define GREEN   0x00F0U
#define PURP    0x0D3AU
#define YELLOW  0x00FFU
#define CYAN    0x0FF0U
#define ORANGE  0x001FU
#define WHITE   0x0FFFU
#define BLACK   0x0000U

//used to store bit patterns for output ports
byte Mask_Left_A[624], Mask_Left_B[624], Mask_Left_C[624], Mask_Right_F[624], Mask_Right_K[624], Mask_Right_L[624];

void Prepare_Masks () { //called by setup to fill address in virtual frame_buffer, these will never change
  //please note 0x00 and 0xFF are switched to make the mask |= faster
  int pos = 0;
  for (int col = 1; col <= 24; col++) { //24 columns
    for (int val = 32; val >= 1; val = val >> 1) { //6 bits of address, 32 == b100000
      if ((col & val) == 0) {
        Mask_Left_A[pos] = 0xFF; Mask_Left_B[pos] = 0xFF; Mask_Left_C[pos] = 0xFF; Mask_Right_F[pos] = 0xFF; Mask_Right_K[pos] = 0xFF; Mask_Right_L[pos] = 0xFF;
      }
      else {
        Mask_Left_A[pos] = 0x00; Mask_Left_B[pos] = 0x00; Mask_Left_C[pos] = 0x00; Mask_Right_F[pos] = 0x00; Mask_Right_K[pos] = 0x00; Mask_Right_L[pos] = 0x00;
      }
      pos++;
    }

    //fill out Brightness becomes 0xCC

    Mask_Left_A[pos] = 0x00; Mask_Left_B[pos] = 0x00; Mask_Left_C[pos] = 0x00; Mask_Right_F[pos] = 0x00; Mask_Right_K[pos] = 0x00; Mask_Right_L[pos] = 0x00;
    pos++; //next bit
    Mask_Left_A[pos] = 0x00; Mask_Left_B[pos] = 0x00; Mask_Left_C[pos] = 0x00; Mask_Right_F[pos] = 0x00; Mask_Right_K[pos] = 0x00; Mask_Right_L[pos] = 0x00;
    pos++; //next bit
    Mask_Left_A[pos] = 0xFF; Mask_Left_B[pos] = 0xFF; Mask_Left_C[pos] = 0xFF; Mask_Right_F[pos] = 0xFF; Mask_Right_K[pos] = 0xFF; Mask_Right_L[pos] = 0xFF;
    pos++; //next bit
    Mask_Left_A[pos] = 0xFF; Mask_Left_B[pos] = 0xFF; Mask_Left_C[pos] = 0xFF; Mask_Right_F[pos] = 0xFF; Mask_Right_K[pos] = 0xFF; Mask_Right_L[pos] = 0xFF;
    pos++; //next bit 
    Mask_Left_A[pos] = 0x00; Mask_Left_B[pos] = 0x00; Mask_Left_C[pos] = 0x00; Mask_Right_F[pos] = 0x00; Mask_Right_K[pos] = 0x00; Mask_Right_L[pos] = 0x00;
    pos++; //next bit
    Mask_Left_A[pos] = 0x00; Mask_Left_B[pos] = 0x00; Mask_Left_C[pos] = 0x00; Mask_Right_F[pos] = 0x00; Mask_Right_K[pos] = 0x00; Mask_Right_L[pos] = 0x00;
    pos++; //next bit   
    Mask_Left_A[pos] = 0xFF; Mask_Left_B[pos] = 0xFF; Mask_Left_C[pos] = 0xFF; Mask_Right_F[pos] = 0xFF; Mask_Right_K[pos] = 0xFF; Mask_Right_L[pos] = 0xFF;
    pos++; //next bit
    Mask_Left_A[pos] = 0xFF; Mask_Left_B[pos] = 0xFF; Mask_Left_C[pos] = 0xFF; Mask_Right_F[pos] = 0xFF; Mask_Right_K[pos] = 0xFF; Mask_Right_L[pos] = 0xFF;
    pos++; //next bit


    for (int i = 0; i <= 11; i++) { //zero out remaining color "data" bits
      Mask_Left_A[pos] = 0xFF; Mask_Left_B[pos] = 0xFF; Mask_Left_C[pos] = 0xFF; Mask_Right_F[pos] = 0xFF; Mask_Right_K[pos] = 0xFF; Mask_Right_L[pos] = 0xFF;
      pos++;
    }
  }
}

void Kill_Ten() { //uses up ~10uSec with NOPs
  //assembly NOPs
  __asm__ volatile (
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
  );
    __asm__ volatile (
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
  );
    __asm__ volatile (
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
  );
    __asm__ volatile (
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
  );
    __asm__ volatile (
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
  );
    __asm__ volatile (
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
  );
  //last, -4 call/ret
}

void Send_Picture() { //Output to ports to strings
  //please note the masks are bit flipped so that |= with mask does not require ~
  uint8_t oldSREG = SREG; //Save interupt status
  cli(); //Disable interupts, this prevents micros() and millis() from working :(

  //PORTA = 0x00; PORTB = 0x00; PORTC = 0x00; PORTF = 0x00; PORTK = 0x00; PORTL = 0x00; //set all ports LOW
  
  int out_pos = 0; //mask array index
  for (byte col = 0; col <= 23; col++) { //24 lights per row    
    //start bit
    PORTA = 0xFF; PORTB = 0xFF; PORTC = 0xFF; PORTF = 0xFF; PORTK = 0xFF; PORTL = 0xFF; //set all ports HIGH
    Kill_Ten(); //wait
    PORTA = 0x00; PORTB = 0x00; PORTC = 0x00; PORTF = 0x00; PORTK = 0x00; PORTL = 0x00; //set all ports LOW

    for (byte i = 0; i <= 25; i++) { //26 bits datagram per light
      Kill_Ten(); //wait 
      PORTA |= Mask_Left_A[out_pos]; PORTB |= Mask_Left_B[out_pos]; PORTC |= Mask_Left_C[out_pos]; //OR with mask
      PORTF |= Mask_Right_F[out_pos]; PORTK |= Mask_Right_K[out_pos]; PORTL |= Mask_Right_L[out_pos]; //this sets ZEROs
      Kill_Ten(); //wait
      PORTA = 0xFF; PORTB = 0xFF; PORTC = 0xFF; PORTF = 0xFF; PORTK = 0xFF; PORTL = 0xFF; //set all ports HIGH, for ONEs
      Kill_Ten(); //wait
      PORTA = 0x00; PORTB = 0x00; PORTC = 0x00; PORTF = 0x00; PORTK = 0x00; PORTL = 0x00; //set all ports LOW
      out_pos++; //next bit
    }
    Kill_Ten(); Kill_Ten(); Kill_Ten(); //fill out 30uSec end of Frame
    Kill_Ten(); Kill_Ten(); Kill_Ten(); //fill out 30uSec end of Frame
  }
  
  SREG = oldSREG; // Re-enable interupts if they were enabled

  //PORTA = 0x00; PORTB = 0x00; PORTC = 0x00; PORTF = 0x00; PORTK = 0x00; PORTL = 0x00; //set all ports LOW
}

void Send_Picture_Guard() {
  Serial.write('s');
  Send_Picture();
  Serial.write('d');
}

void Set_Pixel (int row, int col, byte high_bright, unsigned int color) { //use this to set values in "frame_buffer"
  //please note this needs work, use high_bight, high_bright should come in as 0xX0, validate <=CC
  int start = (24 - col) * 26 + 25; //this goes to correct column position then skips to the LSB of the colore value
  int line = row - 1; //push this so row 1 is accutally the zero bit of the Mask
  while (line >= 8) { line -= 8; } //push so line is correct for "PORT"
  byte over = 0x01 << line; //set overwrite mask to desired bit
  byte *mask_ptr; //used inside the for loop
  unsigned int color_mask = 0x0001U;

  //set pointer to desired array to itterate through
  if (col >= 25) { //right
    if (row >= 17) { mask_ptr = Mask_Right_L; }
    else if (row >= 9) { mask_ptr = Mask_Right_K; }
    else { mask_ptr = Mask_Right_F; }
  }
  else { //left
    if (row >= 17) { mask_ptr = Mask_Left_C; }
    else if (row >= 9) { mask_ptr = Mask_Left_B; }
    else { mask_ptr = Mask_Left_A; }
  }
  
  //remember that puting a 1 in the mask will write a 0 to the light
  for (int b = 11; b >= 0; b--) { //only trying to change color value right now
    if (color & color_mask) { mask_ptr[start - b] &= (byte)~over; } //AND with a 0 in the desired bit, will set selected bit to 0
    else { mask_ptr[start - b] |= (byte)over; } //OR with a 1 in the desired bit, will set selected bit to 1
    color_mask << 1;
  }
}

unsigned int Get_Pixel (int row, int col) { //needs work
  unsigned int temp = 0;
  for (int i = 0; i <= 0; i++) {
    if (col >=24) { //right
      if (row >= 16) {
        //asdf
      }
      else if (row >= 8) {
        //asdf
      }
      else {
        //asdf
      }
    }
    else { //left
      if (row >= 16) {
        //asdf
      }
      else if (row >= 8) {
        //asdf
      }
      else {
        //asdf
      }
    }
  }
  return (temp);
}

void Load_Logo () { //puts logo from EEPROM int Masks via Set_Pixel
  unsigned int val, addr = 0;
  for (int i = 1; i <= 24; i++) { //24 rows
    for (int j = 1; j <= 26; j++) { //26 cols
      //get int means 2 bytes
      val = EEPROM.read(addr);
      addr++;
      val = val << 8; //shift high byte over
      val += EEPROM.read(addr);
      addr++;
      Set_Pixel(i, j, 6, val);
    }
  }
}

void Clear_Screen () { //sets all Masks to BLACK
  for (int i = 1; i <= 24; i++) {
    for (int j = 1; j <= 48; j++) {
      Set_Pixel(i, j, 6, BLACK);
    }
  }
}

void Setup_Node_Sign() {
  //set port bits to OUTPUT
  DDRA |= B11111111; DDRB |= B11111111; DDRC |= B11111111; DDRF |= B11111111; DDRK |= B11111111; DDRL |= B11111111;
  PORTA = 0x00; PORTB = 0x00; PORTC = 0x00; PORTF = 0x00; PORTK = 0x00; PORTL = 0x00; //all low

  Prepare_Masks();

  Send_Picture(); //enumerate
  
  Load_Logo();

  Send_Picture();

  delay(5000);
  Clear_Screen(); //the logo will remain up untill the user calls Send_Picture()
}

#endif //_Node_Header_
