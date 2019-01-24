//SN74HC165N test sketch

//wait for shift register to read and latch
#define LATCH   5

//!!!these need to be moved!!!
int latchPin        = 8;  //Connects to Parallel load pin the 165
int clockEnablePin  = 9;  //Connects to Clock Enable pin the 165
int dataPin         = 11; //Connects to the Q7 pin the 165
int clockPin        = 12; //Connects to the Clock pin the 165

unsigned int pinValues;
unsigned int oldPinValues;

void setup()
{
  Serial.begin(9600);

  //Initialize
  pinMode(latchPin, OUTPUT);
  pinMode(clockEnablePin, OUTPUT); //there is an OR gate from these 2 pins
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, INPUT);

  digitalWrite(clockPin, LOW);
  digitalWrite(ploadPin, HIGH);
}

void loop()
{
  //Read the state of all zones
  pinValues = read_shift_reg();

  //If there was a chage in state, display which ones changed
  if(pinValues != oldPinValues)
  {
    Serial.println("Change detected");
    Serial.println("Pin States:");

    //Print each bit
    for(int i = 1; i <= 128; i = i << 1)
    {
      Serial.print("  Pin-");
  
      if(pinValues & i)
        Serial.println("HIGH");
      else
        Serial.println("LOW");
    }
  
    Serial.println("");
    oldPinValues = pinValues;
  }

  delay(100); //10 chechs per second
}

unsigned int read_shift_reg()
{
  //Trigger latch
  digitalWrite(clockEnablePin, HIGH);
  digitalWrite(latchPin, LOW);
  delayMicroseconds(LATCH); //not sure if needed
  digitalWrite(latchPin, HIGH);
  digitalWrite(clockEnablePin, LOW);

  //Read data
  return(shiftIn(dataPin, clockPin, MSBFIRST));
}
