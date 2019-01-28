//this is test code that will be included into mega-game.h/cpp

byte last;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("ASM TEST");
  last = get_in();
  Serial.println(last);

  digitalWrite(12, LOW);
  digitalWrite(9, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  byte g = get_in();

  if (g != last) {
    Serial.println(g);
    last = g;
  }
  delay(200);
}

byte get_in() {
  //set pins
  DDRB |= B11110111;
  
  //pin masks
  byte latch_mask = B00000001; //8
  byte clk_e_mask = B00000010; //9
  byte data_mask  = B00001000; //11
  byte clock_mask = B00010000; //12

  byte value = 0;

  //clock and latch - parallel read in
  PORTB |= clk_e_mask; //clk_e HIGH
  PORTB &= ~latch_mask;//latch LOW
  __asm__ volatile ( "   nop      "   "\n\t" ); //only needs to be 20ns
  PORTB |= latch_mask; //latch HIGH
  PORTB &= ~clk_e_mask; //clk_e LOW

  //1 bit serial output
  PORTB |= clock_mask; //clock HIGH
  __asm__ volatile ( "   nop      "   "\n\t" );
  value = ((PINB & data_mask) >> 3); //push to 0 or 1, mask to LSB
  PORTB &= ~clock_mask; //clock LOW
  
  __asm__ volatile ( "   nop      "   "\n\t" );

  PORTB |= clock_mask; //clock HIGH
  __asm__ volatile ( "   nop      "   "\n\t" );
  value = value << 1;
  value |= ((PINB & data_mask) >> 3);
  PORTB &= ~clock_mask; //clock LOW
  
  __asm__ volatile ( "   nop      "   "\n\t" );

  PORTB |= clock_mask; //clock HIGH
  __asm__ volatile ( "   nop      "   "\n\t" );
  value = value << 1;
  value |= ((PINB & data_mask) >> 3);
  PORTB &= ~clock_mask; //clock LOW
  
  w__asm__ volatile ( "   nop      "   "\n\t" );

  PORTB |= clock_mask; //clock HIGH
  __asm__ volatile ( "   nop      "   "\n\t" );
  value = value << 1;
  value |= ((PINB & data_mask) >> 3);
  PORTB &= ~clock_mask; //clock LOW
  
  __asm__ volatile ( "   nop      "   "\n\t" );

  PORTB |= clock_mask; //clock HIGH
  __asm__ volatile ( "   nop      "   "\n\t" );
  value = value << 1;
  value |= ((PINB & data_mask) >> 3);
  PORTB &= ~clock_mask; //clock LOW
  
  __asm__ volatile ( "   nop      "   "\n\t" );

  PORTB |= clock_mask; //clock HIGH
  __asm__ volatile ( "   nop      "   "\n\t" );
  value = value << 1;
  value |= ((PINB & data_mask) >> 3);
  PORTB &= ~clock_mask; //clock LOW
  
  __asm__ volatile ( "   nop      "   "\n\t" );

  PORTB |= clock_mask; //clock HIGH
  __asm__ volatile ( "   nop      "   "\n\t" );
  value = value << 1;
  value |= ((PINB & data_mask) >> 3);
  PORTB &= ~clock_mask; //clock LOW
  
  __asm__ volatile ( "   nop      "   "\n\t" );

  PORTB |= clock_mask; //clock HIGH
  __asm__ volatile ( "   nop      "   "\n\t" );
  value = value << 1;
  value |= ((PINB & data_mask) >> 3);
  PORTB &= ~clock_mask; //clock LOW
  
  return (value);
}

void wait_1usec () {
  __asm__ volatile ( "   nop      "   "\n\t" );__asm__ volatile ( "   nop      "   "\n\t" );__asm__ volatile ( "   nop      "   "\n\t" );__asm__ volatile ( "   nop      "   "\n\t" );
  __asm__ volatile ( "   nop      "   "\n\t" );__asm__ volatile ( "   nop      "   "\n\t" );__asm__ volatile ( "   nop      "   "\n\t" );__asm__ volatile ( "   nop      "   "\n\t" );
  __asm__ volatile ( "   nop      "   "\n\t" );__asm__ volatile ( "   nop      "   "\n\t" );__asm__ volatile ( "   nop      "   "\n\t" );__asm__ volatile ( "   nop      "   "\n\t" );
  __asm__ volatile ( "   nop      "   "\n\t" );__asm__ volatile ( "   nop      "   "\n\t" );__asm__ volatile ( "   nop      "   "\n\t" );__asm__ volatile ( "   nop      "   "\n\t" );
 
}
