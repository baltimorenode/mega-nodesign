#ifndef _Font_
#define _Font_

//this is a lot of oddly formatted code so I put it into it's own header

//8x5 font, in ASCII order, unimplemented characters will print as an empty space
byte f8x5[640] = {
0, 0, 0, 0, 0,            //NULL
0, 0, 0, 0, 0,            //SOH  these are non printable characters
0, 0, 0, 0, 0,            //STX
0, 0, 0, 0, 0,            //ETX
0, 0, 0, 0, 0,            //EOT
0, 0, 0, 0, 0,            //ENQ
0, 0, 0, 0, 0,            //ACK
0, 0, 0, 0, 0,            //BEL
0, 0, 0, 0, 0,            //BS
0, 0, 0, 0, 0,            //TAB
0, 0, 0, 0, 0,            //LF
0, 0, 0, 0, 0,            //VT
0, 0, 0, 0, 0,            //FF
0, 0, 0, 0, 0,            //CR
0, 0, 0, 0, 0,            //SO
0, 0, 0, 0, 0,            //SI
0, 0, 0, 0, 0,            //DLE
0, 0, 0, 0, 0,            //DC1
0, 0, 0, 0, 0,            //DC2
0, 0, 0, 0, 0,            //DC3
0, 0, 0, 0, 0,            //DC4
0, 0, 0, 0, 0,            //NAK
0, 0, 0, 0, 0,            //SYN
0, 0, 0, 0, 0,            //ETB
0, 0, 0, 0, 0,            //CAN
0, 0, 0, 0, 0,            //EM
0, 0, 0, 0, 0,            //SUB
0, 0, 0, 0, 0,            //ESC
0, 0, 0, 0, 0,            //FS
0, 0, 0, 0, 0,            //GS
0, 0, 0, 0, 0,            //RS
0, 0, 0, 0, 0,            //US  **** the idea is to replace these with graphics
0, 0, 0, 0, 0,            //Space
0, 0, 191, 0, 0,          // !
0, 0, 3, 0, 3,            // "
36, 255, 36, 255, 36,     // #
158, 146, 255, 146, 242,  // $
195, 35, 24, 98, 195,     // %
118, 137, 81, 33, 70,     // &
3, 7, 0, 0, 0,            // ' single quote
0, 0, 60, 66, 129,        // (
129, 66, 60, 0, 0,        // )
0, 72, 60, 72, 0,         // *
0, 8, 56, 8, 0,           // +
224, 96, 0, 0, 0,         // , comma
0, 8, 8, 8, 0,            // -
192, 192, 0, 0, 0,        // . period
255, 96, 24, 6, 1,        // /
0, 254, 130, 130, 254,    // 0
0, 130, 255, 128, 128,    // 1
194, 161, 145, 146, 140,  // 2
66, 65, 145, 145, 110,    // 3
48, 40, 36, 254, 32,      // 4
79, 137, 133, 69, 57,     // 5
124, 162, 145, 145, 114,  // 6
0, 193, 17, 13, 3,        // 7
112, 143, 137, 143, 112,  // 8
126, 69, 137, 137, 78,    // 9
0, 0, 195, 195, 0,        // :
0, 0, 99, 227, 0,         // ;
0, 16, 40, 68, 130,       // <
0, 36, 36, 36, 0,         // =
130, 68, 40, 16, 0,       // >
0, 2, 177, 10, 4,         // ?
62, 65, 153, 153, 6,      // @
224, 28, 18, 28, 224,     // A
255, 137, 137, 137, 118,  // B
126, 129, 129, 129, 66,   // C
255, 129, 129, 66, 60,    // D
255, 145, 145, 129, 0,    // E
255, 17, 17, 1, 0,        // F
126, 129, 145, 145, 114,  // G
255, 16, 16, 255, 0,      // H
96, 128, 128, 127, 0,     // J
255, 48, 40, 68, 130,     // K
255, 128, 128, 128, 0,    // L
255, 12, 112, 12, 255,    // M
255, 8, 24, 32, 255,      // N
255, 129, 129, 129, 255,  // O
255, 9, 9, 6, 0,          // P
62, 65, 97, 65, 190,      // Q
255, 17, 49, 202, 4,      // R
143, 137, 137, 137, 241,  // S
1, 1, 255, 1, 1,          // T
127, 128, 128, 128, 127,  // U
7, 56, 96, 56, 7,         // V
63, 96, 56, 96, 63,       // W
195, 36, 24, 36, 195,     // X
3, 20, 240, 20, 3,        // Y
193, 161, 153, 133, 131,  // Z
0, 0, 255, 129, 129,      // [
1, 6, 24, 96, 128,        // \
129, 129, 255, 0, 0,      // ]
0, 2, 1, 2, 0,            // ^
128, 128, 128, 128, 128,  // _
0, 0, 0, 1, 2,            // ` backtick
0, 0, 0, 0, 0,            // a: lower case letters not implemented
0, 0, 0, 0, 0,            // b
0, 0, 0, 0, 0,            // c
0, 0, 0, 0, 0,            // d 
0, 0, 0, 0, 0,            // e
0, 0, 0, 0, 0,            // f
0, 0, 0, 0, 0,            // g
0, 0, 0, 0, 0,            // h
0, 0, 0, 0, 0,            // i
0, 0, 0, 0, 0,            // j
0, 0, 0, 0, 0,            // k
0, 0, 0, 0, 0,            // l
0, 0, 0, 0, 0,            // m
0, 0, 0, 0, 0,            // n
0, 0, 0, 0, 0,            // o
0, 0, 0, 0, 0,            // p
0, 0, 0, 0, 0,            // q
0, 0, 0, 0, 0,            // r
0, 0, 0, 0, 0,            // s
0, 0, 0, 0, 0,            // t
0, 0, 0, 0, 0,            // u
0, 0, 0, 0, 0,            // v
0, 0, 0, 0, 0,            // w
0, 0, 0, 0, 0,            // x
0, 0, 0, 0, 0,            // y
0, 0, 0, 0, 0,            // z: lower case letters not implemented
0, 0, 24, 102, 129,       // {
0, 0, 255, 0, 0,          // | vertial line
0, 0, 129, 102, 240,      // }
8, 8, 16, 8, 16,          // ~
0, 0, 0, 0, 0             //DEL this is a non-printable control character
}; //only the first 128 standard ASCII characters are here

#endif //_Font_
