#include "mega_game.h"

//default constructor
Game_Input::Game_Input (int ctrl1_data, int ctrl1_clk, int ctrl2_data, int ctrl2_clk, int latch) {
  c_1_d = ctrl1_data; c_1_c = ctrl1_clk;
  c_2_d = ctrl2_data; c_2_c = ctrl2_clk;
  c_21_latch = latch; //one pin for both controllers
  //could replace this with Update_Controllers() if you wanted non-standard normally closed buttons
  one = 0; two = 0; 
}

void Game_Input::Update_Controllers() {
  //Strobe latch pin
  digitalWrite(c_21_latch, HIGH);
  digitalWrite(c_21_latch, LOW);
  //button state is now saved to shift register inside the controller

  //shiftIn data from controllers
  one = shiftIn(c_1_d, c_1_c, MSBFIRST);
  two = shiftIn(c_2_d, c_2_c, MSBFIRST);
}

//Getters
bool Game_Input::Get_Button_One(byte mask) { return (one & mask); }
bool Game_Input::Get_Button_Two(byte mask) { return (two & mask); }
//the idea here is to call a-la if(myObject.Get_Button_Two(BUTTON_Start)){/*pause*/}

byte Game_Input::Get_Raw_One() { return (one); }
byte Game_Input::Get_Raw_Two() { return (two); }
