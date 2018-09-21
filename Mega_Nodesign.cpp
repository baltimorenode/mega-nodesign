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

void Mega_Nodesign::Enummerate() { //set light IDs from 1 to 24
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
  
  uint8_t oldSREG = SREG; //Save interupt status
  cli(); //Disable interupts, this prevents micros() and millis() from working :(

  //PORTA = 0x00; PORTB = 0x00; PORTC = 0x00; PORTF = 0x00; PORTK = 0x00; PORTL = 0x00; //set all ports LOW
  
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
    Kill_Ten(); Kill_Ten(); Kill_Ten(); //fill out 30uSec end of Frame
    Kill_Ten(); Kill_Ten(); Kill_Ten(); //fill out 30uSec end of Frame, this should not be needed but seems to reduce color glitching
  }
  
  SREG = oldSREG; // Re-enable interupts if they were enabled

  //PORTA = 0x00; PORTB = 0x00; PORTC = 0x00; PORTF = 0x00; PORTK = 0x00; PORTL = 0x00; //set all ports LOW

  if (use_Guard) { Serial.write('d'); }
}

void Mega_Nodesign::Set_Pixel (int row, int col, byte high_bright, unsigned int color) { //use this to set values in "frame_buffer"
  //please note this needs work, use high_bight, high_bright should come in as 0xX0, validate <=CC

  //the highest block of the mask is the leftmost light, this goes to correct column position then skips to the LSB of the color value
  int start = (24 - col) * 26 + 25; //so go backward
  int line = row - 1; //push this so row 1 is accutally the zero bit of the Mask
  while (line >= 8) { line -= 8; } //push so line is correct for "PORT"
  byte over = 0x01 << line; //set overwrite mask to desired bit
  byte *mask_ptr; //used inside the for loop
  
  //set pointer to desired array to itterate through
  if (col >= 25) { //right side
    if (row >= 17) { mask_ptr = Mask_Right_L; }
    else if (row >= 9) { mask_ptr = Mask_Right_K; }
    else { mask_ptr = Mask_Right_F; }
  }
  else { //left side
    if (row >= 17) { mask_ptr = Mask_Left_C; }
    else if (row >= 9) { mask_ptr = Mask_Left_B; }
    else { mask_ptr = Mask_Left_A; }
  }
  
  //remember that puting a 1 in the mask will write a 0 to the light
  for (int b = 11; b >= 0; b--) { //only trying to change color value right now
    if (color & (0x0001U << b)) { mask_ptr[start - b] &= (byte)~over; } //AND with a 0 in the desired bit, will set selected bit to 0
    else { mask_ptr[start - b] |= (byte)over; } //OR with a 1 in the desired bit, will set selected bit to 1
  }
}

void Mega_Nodesign::Kill_Ten() { //uses up ~10uSec with assembly NOPs
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

void Mega_Nodesign::Clear_Screen () { //sets all Masks to BLACK
  for (int i = 1; i <= 24; i++) {
    for (int j = 1; j <= 48; j++) {
      Set_Pixel(i, j, DEFAULT_BRIGHT, BLACK);
    }
  }
}

void Mega_Nodesign::Load_Logo () { //puts logo from EEPROM int Masks via Set_Pixel
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

void Mega_Nodesign::Set_Guard(bool val) { //Setter
  use_Guard = val;
}

bool Mega_Nodesign::Get_Guard() { //Getter
  return (use_Guard);
}

bool Mega_Nodesign::Get_Working () { //Getter
  return (working);
}

Mega_Nodesign::Mega_Nodesign () { //the only constructor
  //set port bits to OUTPUT
  DDRA |= B11111111; DDRB |= B11111111; DDRC |= B11111111; DDRF |= B11111111; DDRK |= B11111111; DDRL |= B11111111;
  PORTA = 0x00; PORTB = 0x00; PORTC = 0x00; PORTF = 0x00; PORTK = 0x00; PORTL = 0x00; //all low to start

  use_Guard = false;
  working = false;
}

void Mega_Nodesign::begin () {
  //set PSU pin to High
  //code here

  working = true;
  
  Enummerate();
  Prepare_Masks();
  Load_Logo();
  Send_Picture();
  delay(5000); //the logo is displayed for at least 5 seconds
  Clear_Screen(); //the user has to call Send_Picture to remove the logo from the sign
}

void Mega_Nodesign::stop () {
  //set PSU pin to Low
  //code here

  working = false;
}

