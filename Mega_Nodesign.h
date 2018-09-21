
#ifndef _Mega_Nodesign_
#define _Mega_Nodesign_

//needed libraries
#include <EEPROM.h>
#include <Arduino.h>

//colors, U = unsigned
#define RED     0x000FU
#define BLUE    0x0F00U
#define GREEN   0x00F0U
#define PURPLE  0x0D3AU
#define YELLOW  0x00FFU
#define CYAN    0x0FF0U
#define ORANGE  0x001FU
#define WHITE   0x0FFFU
#define BLACK   0x0000U

#define DEFAULT_BRIGHT  0xCCU

class Mega_Nodesign {
public:
  //Constructor
  Mega_Nodesign();

  //Basic Control
  void begin();
  void stop(); //disable power to lightstrings

  //Flow Control
  void Set_Guard(bool val);
  bool Get_Guard();
  bool Get_Working();
  
  //Basic Manipulators
  void Set_Pixel(int row, int col, byte high_bright, unsigned int color);
  void Send_Picture(); //draws the current state of the masks to the sign
  
  //Drawing
  void Load_Logo(); //loads BaltimoreNode logo into masks
  void Clear_Screen(); //sets masks to black

private: 
  //Methods
  void Kill_Ten(); //uses up 10uSec
  void Enummerate(); //assigns ID values to lights in sign
  void Prepare_Masks(); //puts ID and default color values into masks

  //Frame Buffer Data
  byte Mask_Left_A[624], Mask_Left_B[624], Mask_Left_C[624], Mask_Right_F[624], Mask_Right_K[624], Mask_Right_L[624];
  
  bool use_Guard;
  bool working; //this is never set directly
};

#endif //_Mega_Nodesign_
