/*
 * Mega_NodeSign
 * use Arduino Mega to drive 48 (2 sets of 24) GE G35 light strings simultaniously
 * each row on board is cut in half, can drive both at once
 * so 2 24x24 arrays side by side, 18,720 uSeconds best case, 50 frames a second
 * 
 * created by Chris Lindsay for Baltimore Node
 * created using documentation from deepdarc.com
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
#define CYAN    0x0FF0U //it's full of cyan, I put it in myself!
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
  
  //Text: there are only 3 rows and 9 columns for text
  void Put_Char(int row, int col, char letter, unsigned int color);
  void Put_String(int row, int col, char text[], int len, unsigned int color);

  //Communications
  void Recv_Frame(); //recieve an entire screen via Serial
  void Recv_Pixel(); //puts sign into mode to receive pixel commands via Serial

  //Game Controller
  bool Get_Button_PlayerOne(byte mask);
  bool Get_Button_PlayerTwo(byte mask);

  byte Get_Raw_PlayerOne();
  byte Get_Raw_PlayerTwo();

private: 
  //Methods
  void Kill_Ten(); //uses up 10uSec
  void Enummerate(); //assigns ID values to lights in sign
  void Prepare_Masks(); //puts ID and default color values into masks
  void Get_Game_Input();

  //Frame Buffer Data
  byte Mask_Left_A[624], Mask_Left_B[624], Mask_Left_C[624], Mask_Right_F[624], Mask_Right_K[624], Mask_Right_L[624];
  
  bool use_Guard;
  bool working; //this is never set directly
  byte Player_One, Player_Two; //last input from game controllers
};

#endif //_Mega_Nodesign_
