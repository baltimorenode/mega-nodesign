#ifndef _Mega_NodeGame_
#define _Mega_NodeGame_

//bitmasks for controller buttons
#define   BUTTON_A        0x01U
#define   BUTTON_B        0x02U
#define   BUTTON_Start    0x04U
#define   BUTTON_Select   0x08U
#define   BUTTON_UP       0x10U
#define   BUTTON_DOWN     0x20U
#define   BUTTON_LEFT     0x40U
#define   BUTTON_RIGHT    0x80U

class Game_Input { //support 2 NES controllers for input
public:
  //constructor
  Game_Input (int ctrl1_data, int ctrl1_clk, int ctrl2_data, int ctrl2_clk, int latch);

  //technically a setter
  void Update_Controllers();

  //Getters
  bool Get_Button_One(byte mask);
  bool Get_Button_Two(byte mask);

  byte Get_Raw_One();
  byte Get_Raw_Two();

private:
  byte one, two; //state of last request from controllers
  int c_1_d, c_1_c, c_2_d, c_2_c; //IO pins
  int c_21_latch; //only need 1 latch, shared by both controllers
};

#endif //_Mega_NodeGame_

