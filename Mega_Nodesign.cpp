#include "Mega_Nodesign.h"

void Mega_Nodesign::Prepare_Masks () { //called by setup to fill address in virtual frame_buffer, these will never change
  //please note 0x00 and 0xFF are switched to make the mask |= faster
  int pos = 0;
  for (int col = 24; col >= 1; col--) { //24 columns, in reverse enumeration order
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

void Mega_Nodesign::Enumerate() { //set light IDs from 1 to 24
  //this code looks very similar to Send_Picture and Prepar_Masks, but is only for initializing the light strings
  //temporarily using Left_Mask_A to keep memory usage static, it will be correctly configured by Prepare_Masks()  
  int pos = 0;
  for (int id = 1; id <= 24; id++) { //enummerate lights in reverse of send order
    for (int val = 32; val >= 1; val = val >> 1) { //6 bits of address, 32 == b100000
      if ((id & val) == 0) { Mask_Left_A[pos] = 0xFF; }
      else { Mask_Left_A[pos] = 0x00; }
      pos++;
    }
    //fill out Brightness becomes 0xCC
    Mask_Left_A[pos] = 0x00; pos++; //next bit
    Mask_Left_A[pos] = 0x00; pos++; //next bit
    Mask_Left_A[pos] = 0xFF; pos++; //next bit
    Mask_Left_A[pos] = 0xFF; pos++; //next bit 
    Mask_Left_A[pos] = 0x00; pos++; //next bit
    Mask_Left_A[pos] = 0x00; pos++; //next bit   
    Mask_Left_A[pos] = 0xFF; pos++; //next bit
    Mask_Left_A[pos] = 0xFF; pos++; //next bit
    for (int i = 0; i <= 11; i++) { //zero out remaining color "data" bits
      Mask_Left_A[pos] = 0xFF;
      pos++;
    }
  }
  //send enumeration data to light strings
  pos = 0;
  uint8_t oldSREG = SREG; //Save interupt status
  cli(); //Disable interupts, this prevents micros() and millis() from working :(
  for (byte light = 0; light <= 23; light++) {
    //start bit
    PORTA = 0xFF; PORTB = 0xFF; PORTC = 0xFF; PORTF = 0xFF; PORTK = 0xFF; PORTL = 0xFF; //set all ports HIGH
    Kill_Ten(); //wait
    PORTA = 0x00; PORTB = 0x00; PORTC = 0x00; PORTF = 0x00; PORTK = 0x00; PORTL = 0x00; //set all ports LOW    
    for (byte i = 0; i <= 25; i++) {
	    Kill_Ten(); //wait 
      PORTA |= Mask_Left_A[pos]; PORTB |= Mask_Left_A[pos]; PORTC |= Mask_Left_A[pos]; //OR with mask
      PORTF |= Mask_Left_A[pos]; PORTK |= Mask_Left_A[pos]; PORTL |= Mask_Left_A[pos]; //this sets ZEROs
      Kill_Ten(); //wait
      PORTA = 0xFF; PORTB = 0xFF; PORTC = 0xFF; PORTF = 0xFF; PORTK = 0xFF; PORTL = 0xFF; //set all ports HIGH, for ONEs
      Kill_Ten(); //wait
      PORTA = 0x00; PORTB = 0x00; PORTC = 0x00; PORTF = 0x00; PORTK = 0x00; PORTL = 0x00; //set all ports LOW
      pos++; //next bit
	  }
    Kill_Ten(); Kill_Ten(); Kill_Ten(); //fill out 30uSec end of Frame
    Kill_Ten(); Kill_Ten(); Kill_Ten(); //fill out 30uSec end of Frame
  }
  SREG = oldSREG; // Re-enable interupts if they were enabled
}

void Mega_Nodesign::Send_Picture() { //Output to ports to light strings
  //please note the masks are bit flipped so that |= with mask does not require ~

  if (use_Guard) { Serial.write('s'); }
  
  //uint8_t oldSREG = SREG; //Save interupt status
  //cli(); //Disable interupts, this prevents micros() and millis() from working :(
  
  int out_pos = 0; //mask array index
  for (byte col = 0; col <= 23; col++) { //24 lights per row, arbitrary variable   
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
    //fill out 30uSec end of Frame
    Kill_Ten(); Kill_Ten(); Kill_Ten();
    Kill_Ten(); Kill_Ten(); Kill_Ten(); //this is more than 30uSec but seems to reduce color glitching 
  }
  
  //SREG = oldSREG; // Re-enable interupts if they were enabled

  if (use_Guard) { Serial.write('d'); }
} //~16300uSec or 16ms which is less than 20ms so ~50fps with just under 4ms per frame for other logic

void Mega_Nodesign::Set_Pixel (int row, int col, byte high_bright, unsigned int color) { //use this to set values in "frame_buffer"
  //please note this needs work, use high_bight, high_bright should come in as 0xX0, validate <=CC

  byte *mask_ptr; //used inside the for loop
  int line = row - 1; //push this so row 1 is accutally the zero bit of the Mask
    
  //set pointer to desired array to itterate through
  if (col >= 25) { //right side
    if (row >= 17) { mask_ptr = Mask_Right_L; line -= 17; }
    else if (row >= 9) { mask_ptr = Mask_Right_K; line -= 9; }
    else { mask_ptr = Mask_Right_F; }
    row -= 24;
  }
  else { //left side
    if (row >= 17) { mask_ptr = Mask_Left_C; line -= 17; }
    else if (row >= 9) { mask_ptr = Mask_Left_B; line -= 9; }
    else { mask_ptr = Mask_Left_A; }
  }

  mask_ptr += (24 - col) * 26 + 14;

  //the highest block of the mask is the leftmost light, this goes to correct column position then skips to the LSB of the color value

  byte over = 0x01 << line; //set overwrite mask to desired bit
  unsigned int color_bit_mask = 0x0800U;
  
  //remember that puting a 1 in the mask will write a 0 to the light
  //unrolled loop to save 2uSec
  if (color & color_bit_mask) { *mask_ptr = *mask_ptr & (byte)~over; } //AND with a 0 in the desired bit, will set selected bit to 0
  else { *mask_ptr = *mask_ptr | (byte)over; } //OR with a 1 in the desired bit, will set selected bit to 1
  mask_ptr = mask_ptr + 1;
  color_bit_mask = color_bit_mask >> 1;

    if (color & color_bit_mask) { *mask_ptr = *mask_ptr & (byte)~over; } //AND with a 0 in the desired bit, will set selected bit to 0
  else { *mask_ptr = *mask_ptr | (byte)over; } //OR with a 1 in the desired bit, will set selected bit to 1
  mask_ptr = mask_ptr + 1;
  color_bit_mask = color_bit_mask >> 1;
    if (color & color_bit_mask) { *mask_ptr = *mask_ptr & (byte)~over; } //AND with a 0 in the desired bit, will set selected bit to 0
  else { *mask_ptr = *mask_ptr | (byte)over; } //OR with a 1 in the desired bit, will set selected bit to 1
  mask_ptr = mask_ptr + 1;
  color_bit_mask = color_bit_mask >> 1;
    if (color & color_bit_mask) { *mask_ptr = *mask_ptr & (byte)~over; } //AND with a 0 in the desired bit, will set selected bit to 0
  else { *mask_ptr = *mask_ptr | (byte)over; } //OR with a 1 in the desired bit, will set selected bit to 1
  mask_ptr = mask_ptr + 1;
  color_bit_mask = color_bit_mask >> 1;
    if (color & color_bit_mask) { *mask_ptr = *mask_ptr & (byte)~over; } //AND with a 0 in the desired bit, will set selected bit to 0
  else { *mask_ptr = *mask_ptr | (byte)over; } //OR with a 1 in the desired bit, will set selected bit to 1
  mask_ptr = mask_ptr + 1;
  color_bit_mask = color_bit_mask >> 1;
    if (color & color_bit_mask) { *mask_ptr = *mask_ptr & (byte)~over; } //AND with a 0 in the desired bit, will set selected bit to 0
  else { *mask_ptr = *mask_ptr | (byte)over; } //OR with a 1 in the desired bit, will set selected bit to 1
  mask_ptr = mask_ptr + 1;
  color_bit_mask = color_bit_mask >> 1;
    if (color & color_bit_mask) { *mask_ptr = *mask_ptr & (byte)~over; } //AND with a 0 in the desired bit, will set selected bit to 0
  else { *mask_ptr = *mask_ptr | (byte)over; } //OR with a 1 in the desired bit, will set selected bit to 1
  mask_ptr = mask_ptr + 1;
  color_bit_mask = color_bit_mask >> 1;
    if (color & color_bit_mask) { *mask_ptr = *mask_ptr & (byte)~over; } //AND with a 0 in the desired bit, will set selected bit to 0
  else { *mask_ptr = *mask_ptr | (byte)over; } //OR with a 1 in the desired bit, will set selected bit to 1
  mask_ptr = mask_ptr + 1;
  color_bit_mask = color_bit_mask >> 1;
    if (color & color_bit_mask) { *mask_ptr = *mask_ptr & (byte)~over; } //AND with a 0 in the desired bit, will set selected bit to 0
  else { *mask_ptr = *mask_ptr | (byte)over; } //OR with a 1 in the desired bit, will set selected bit to 1
  mask_ptr = mask_ptr + 1;
  color_bit_mask = color_bit_mask >> 1;
    if (color & color_bit_mask) { *mask_ptr = *mask_ptr & (byte)~over; } //AND with a 0 in the desired bit, will set selected bit to 0
  else { *mask_ptr = *mask_ptr | (byte)over; } //OR with a 1 in the desired bit, will set selected bit to 1
  mask_ptr = mask_ptr + 1;
  color_bit_mask = color_bit_mask >> 1;
    if (color & color_bit_mask) { *mask_ptr = *mask_ptr & (byte)~over; } //AND with a 0 in the desired bit, will set selected bit to 0
  else { *mask_ptr = *mask_ptr | (byte)over; } //OR with a 1 in the desired bit, will set selected bit to 1
  mask_ptr = mask_ptr + 1;
  color_bit_mask = color_bit_mask >> 1;
    if (color & color_bit_mask) { *mask_ptr = *mask_ptr & (byte)~over; } //AND with a 0 in the desired bit, will set selected bit to 0
  else { *mask_ptr = *mask_ptr | (byte)over; } //OR with a 1 in the desired bit, will set selected bit to 1
} //~12uSec

void Mega_Nodesign::Kill_Ten() { //uses up ~10uSec with assembly NOPs
  __asm__ volatile (
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
  ); //1
    __asm__ volatile (
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
  ); //2
    __asm__ volatile (
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
  ); //3
    __asm__ volatile (
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
  ); //4
    __asm__ volatile (
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
  ); //5
  __asm__ volatile (
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
    "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t" "   nop      "   "\n\t"
  ); //6
  //last, -4 call/ret
} //this is just over 6uSec, which is less than required by spec

void Mega_Nodesign::Clear_Screen() { //sets all pixel Masks to BLACK
  int pos = 14; //start of color for first pixel

  for (int j = 0; j <= 24; j++) { //24 lights per string
    Mask_Left_A[pos] = 0xFF; Mask_Left_B[pos] = 0xFF; Mask_Left_C[pos] = 0xFF; Mask_Right_F[pos] = 0xFF; Mask_Right_K[pos] = 0xFF; Mask_Right_L[pos] = 0xFF;
    pos++;
    Mask_Left_A[pos] = 0xFF; Mask_Left_B[pos] = 0xFF; Mask_Left_C[pos] = 0xFF; Mask_Right_F[pos] = 0xFF; Mask_Right_K[pos] = 0xFF; Mask_Right_L[pos] = 0xFF;
    pos++;
    Mask_Left_A[pos] = 0xFF; Mask_Left_B[pos] = 0xFF; Mask_Left_C[pos] = 0xFF; Mask_Right_F[pos] = 0xFF; Mask_Right_K[pos] = 0xFF; Mask_Right_L[pos] = 0xFF;
    pos++;
    Mask_Left_A[pos] = 0xFF; Mask_Left_B[pos] = 0xFF; Mask_Left_C[pos] = 0xFF; Mask_Right_F[pos] = 0xFF; Mask_Right_K[pos] = 0xFF; Mask_Right_L[pos] = 0xFF;
    pos++;
    Mask_Left_A[pos] = 0xFF; Mask_Left_B[pos] = 0xFF; Mask_Left_C[pos] = 0xFF; Mask_Right_F[pos] = 0xFF; Mask_Right_K[pos] = 0xFF; Mask_Right_L[pos] = 0xFF;
    pos++;
    Mask_Left_A[pos] = 0xFF; Mask_Left_B[pos] = 0xFF; Mask_Left_C[pos] = 0xFF; Mask_Right_F[pos] = 0xFF; Mask_Right_K[pos] = 0xFF; Mask_Right_L[pos] = 0xFF;
    pos++;
    Mask_Left_A[pos] = 0xFF; Mask_Left_B[pos] = 0xFF; Mask_Left_C[pos] = 0xFF; Mask_Right_F[pos] = 0xFF; Mask_Right_K[pos] = 0xFF; Mask_Right_L[pos] = 0xFF;
    pos++;
    Mask_Left_A[pos] = 0xFF; Mask_Left_B[pos] = 0xFF; Mask_Left_C[pos] = 0xFF; Mask_Right_F[pos] = 0xFF; Mask_Right_K[pos] = 0xFF; Mask_Right_L[pos] = 0xFF;
    pos++;
    Mask_Left_A[pos] = 0xFF; Mask_Left_B[pos] = 0xFF; Mask_Left_C[pos] = 0xFF; Mask_Right_F[pos] = 0xFF; Mask_Right_K[pos] = 0xFF; Mask_Right_L[pos] = 0xFF;
    pos++;
    Mask_Left_A[pos] = 0xFF; Mask_Left_B[pos] = 0xFF; Mask_Left_C[pos] = 0xFF; Mask_Right_F[pos] = 0xFF; Mask_Right_K[pos] = 0xFF; Mask_Right_L[pos] = 0xFF;
    pos++;
    Mask_Left_A[pos] = 0xFF; Mask_Left_B[pos] = 0xFF; Mask_Left_C[pos] = 0xFF; Mask_Right_F[pos] = 0xFF; Mask_Right_K[pos] = 0xFF; Mask_Right_L[pos] = 0xFF;
    pos++;
    Mask_Left_A[pos] = 0xFF; Mask_Left_B[pos] = 0xFF; Mask_Left_C[pos] = 0xFF; Mask_Right_F[pos] = 0xFF; Mask_Right_K[pos] = 0xFF; Mask_Right_L[pos] = 0xFF;
    pos += 15; //goto color of next pixel
  }
/*
  for (int i = 1; i <= 24; i++) {
    for (int j = 1; j <= 48; j++) {
      Set_Pixel(i, j, DEFAULT_BRIGHT, BLACK);
    }
  }
*/
} //445uSec

void Mega_Nodesign::Load_Logo() { //puts logo from EEPROM int Masks via Set_Pixel
  unsigned int val, addr = 0;
  for (int i = 1; i <= 24; i++) { //24 rows
    for (int j = 1; j <= 26; j++) { //26 cols
      //get int means 2 bytes
      val = EEPROM.read(addr);
      addr++;
      val = val << 8; //shift high byte over
      val += EEPROM.read(addr);
      addr++;
      Set_Pixel(i, j, DEFAULT_BRIGHT , val);
    }
  }
}

void Mega_Nodesign::Set_Guard(bool val) { //Setter
  use_Guard = val;
}

bool Mega_Nodesign::Get_Guard() { //Getter
  return (use_Guard);
}

bool Mega_Nodesign::Get_Working () { //Getter
  return (working);
}

void Mega_Nodesign::Put_Char(int row, int col, char letter, unsigned int color) {
  //the row converts directly to a Mask which works to 8 rows on sign
  byte display_col = 6 * col - 5;
  byte *mask_ptr;
  if (display_col >= 25) { //left
    if (row == 1) { mask_ptr = Mask_Right_F; }
    else if (row == 2) { mask_ptr = Mask_Right_K; }
    else { mask_ptr = Mask_Right_L; }
    display_col -= 24;
  } else { //right
    if (row == 1) { mask_ptr = Mask_Left_A; }
    else if (row == 2) { mask_ptr = Mask_Left_B; }
    else { mask_ptr = Mask_Left_C; }
  }
  mask_ptr += (24 - display_col) * 26 + 14; //MSB of color for starting column
  int ee_addr = 5 * letter + 1248; //1248 this is where the logo ends in EEPROM
  for (int font = 0; font <= 5; font++) { //5 columns of the character font
    byte val = EEPROM.read(ee_addr);
    val = ~val; //1->0 0->1 for faster write to strings
    unsigned int color_mask = 0x0800U;
    //for(int b = 0; b <= 11; b++) { //unroll this after proof to improve performance
      if (color & color_mask) { *mask_ptr = (byte)val; }
      else { *mask_ptr = (byte)0xFF; }
      color_mask = color_mask >> 1;
      mask_ptr = mask_ptr + 1;
      if (color & color_mask) { *mask_ptr = (byte)val; }
      else { *mask_ptr = (byte)0xFF; }
      color_mask = color_mask >> 1;
      mask_ptr = mask_ptr + 1;
      if (color & color_mask) { *mask_ptr = (byte)val; }
      else { *mask_ptr = (byte)0xFF; }
      color_mask = color_mask >> 1;
      mask_ptr = mask_ptr + 1;
      if (color & color_mask) { *mask_ptr = (byte)val; }
      else { *mask_ptr = (byte)0xFF; }
      color_mask = color_mask >> 1;
      mask_ptr = mask_ptr + 1;
      if (color & color_mask) { *mask_ptr = (byte)val; }
      else { *mask_ptr = (byte)0xFF; }
      color_mask = color_mask >> 1;
      mask_ptr = mask_ptr + 1;
      if (color & color_mask) { *mask_ptr = (byte)val; }
      else { *mask_ptr = (byte)0xFF; }
      color_mask = color_mask >> 1;
      mask_ptr = mask_ptr + 1;
      if (color & color_mask) { *mask_ptr = (byte)val; }
      else { *mask_ptr = (byte)0xFF; }
      color_mask = color_mask >> 1;
      mask_ptr = mask_ptr + 1;
      if (color & color_mask) { *mask_ptr = (byte)val; }
      else { *mask_ptr = (byte)0xFF; }
      color_mask = color_mask >> 1;
      mask_ptr = mask_ptr + 1;
      if (color & color_mask) { *mask_ptr = (byte)val; }
      else { *mask_ptr = (byte)0xFF; }
      color_mask = color_mask >> 1;
      mask_ptr = mask_ptr + 1;
      if (color & color_mask) { *mask_ptr = (byte)val; }
      else { *mask_ptr = (byte)0xFF; }
      color_mask = color_mask >> 1;
      mask_ptr = mask_ptr + 1;
      if (color & color_mask) { *mask_ptr = (byte)val; }
      else { *mask_ptr = (byte)0xFF; }
      mask_ptr = mask_ptr + 1;
      color_mask = color_mask >> 1;
      if (color & color_mask) { *mask_ptr = (byte)val; }
      else { *mask_ptr = (byte)0xFF; }
      mask_ptr = mask_ptr + 1;
    //}
    mask_ptr = mask_ptr - 38; //skip to color portion of frame for next column
    ee_addr = ee_addr + 1;
  }
  //perhaps force 6th column of black to ensure clean spaces between letters?
  //removing the space would facilitate storing and dispalying graphic sprites in the font
} //32uSec

void Mega_Nodesign::Put_String(int row, int col, char text[], int len, unsigned int color) {
  //there is no text wrapping
  for (int i = 0; i < len; i++) {
    Put_Char(row, col + i, text[i], color);
  }
}

void Mega_Nodesign::Recv_Screen() { //requires 2304 bytes recieved
  byte temp_in;
  unsigned int temp_color;

  Serial.write('g'); //send "start"
  for (int x = 1; x <= 48; x++) { //repeat for 24 lines
    for (int y = 1; y <= 24; y++) {
      while(Serial.available() < 1) { }
      temp_in = Serial.read(); //MSB
      temp_color = temp_in << 8;

      while(Serial.available() < 1) { }
      temp_in = Serial.read(); //LSB
      temp_color += temp_in;

      Set_Pixel(y, x, DEFAULT_BRIGHT, temp_color); //this will be slow
    }
  }
  Serial.write('d'); //send "done"
} //how to make this event driven?

Mega_Nodesign::Mega_Nodesign () { //the only constructor
  //set port bits to OUTPUT
  DDRA |= B11111111; DDRB |= B11111111; DDRC |= B11111111; DDRF |= B11111111; DDRK |= B11111111; DDRL |= B11111111;
  PORTA = 0x00; PORTB = 0x00; PORTC = 0x00; PORTF = 0x00; PORTK = 0x00; PORTL = 0x00; //all low to start

  //setup power supply relays
  DDRJ |= B00000011; //PORTJ 0, 1 = pin 15 and 14
  PORTJ = 0x03; //14 and 15 HIGH, none of the other pins of PORTJ are exposed but just to be nice only set used pins

  DDRH |= B00000011; //PORTH 0, 1 = pin 17 and 16
  PORTH = 0x03; 

  DDRD |= B00001100; //PORTD 3, 2, 1, 0 = pin 18, 19, 20, and 21
  PORTD = 0x0B; //only using pins 18 and 19

  use_Guard = false;
  working = false;
}

void Mega_Nodesign::begin () {
  //set PSU pin to LOW
  PORTJ = 0x000; //14 and 15 LOW
  PORTH = 0x00;
  PORTD = 0x00;

  working = true;
  
  Enumerate();
  Prepare_Masks();
  Load_Logo();
  Send_Picture();
  delay(5000); //the logo is displayed for at least 5 seconds
  Clear_Screen(); //the user has to call Send_Picture to remove the logo from the sign
}

void Mega_Nodesign::stop () {
  //set PSU pin to Low
  PORTJ = 0x03; //14 and 15 HIGH
  PORTH = 0x03;
  PORTD = 0x0B;

  working = false;
}

void Mega_Nodesign::Print_Mask(int mask, int col) { //do ont keep this in production
  byte *mask_ptr;
  switch (mask) { //which mask
    case 1:
      mask_ptr = Mask_Left_A;
      break;
    case 2:
      mask_ptr = Mask_Left_B;
      break;
    case 3:
      mask_ptr = Mask_Left_C;
      break;
    case 4:
      mask_ptr = Mask_Right_F;
      break;
    case 5:
      mask_ptr = Mask_Right_K;
      break;
    case 6:
      mask_ptr = Mask_Right_L;
      break;
  }
  
  mask_ptr += (24 - col) * 26; //goto bit position

  for (int i=0; i<=26; i++) { //loop through bits
    Serial.print(*mask_ptr);
    Serial.print(" ");
    mask_ptr = mask_ptr + 1;
  }
  Serial.println("");
}

