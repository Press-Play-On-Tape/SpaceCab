#include <Arduboy2.h>
#include <ArduboyTones.h>
 
Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);
Sprites sprite;

#define LEVEL_WIDTH 16
#define LEVEL_HEIGHT 8
#define PLAT1 0
#define EMPTY 1
#define EDGE1 2
#define ROCK1 3
#define SIGN1 4
#define GATE1 5
#define ROCK2 6
#define CLOCK 7
#define TILE_SIZE 8

// Level 1 layout --------------------------------------------------------------

int level1Map[LEVEL_HEIGHT][LEVEL_WIDTH] = {
  { ROCK2, ROCK2, ROCK2, ROCK2, ROCK2, ROCK2, ROCK2, ROCK2, ROCK2, GATE1, GATE1, GATE1, ROCK2, ROCK2, ROCK2, ROCK2 },
  { EMPTY, EMPTY, EDGE1, EDGE1, EDGE1, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
  { EMPTY, EMPTY, PLAT1, PLAT1, PLAT1, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EDGE1, EDGE1, SIGN1, EMPTY },
  { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EDGE1, EDGE1, EMPTY, EMPTY, EMPTY, EMPTY, PLAT1, PLAT1, PLAT1, EMPTY },
  { EDGE1, SIGN1, EMPTY, EMPTY, EMPTY, EMPTY, PLAT1, PLAT1, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
  { PLAT1, PLAT1, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
  { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
  { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, CLOCK, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
};


// Lets Load images in PROGMEM -------------------------------------------------

const unsigned char PROGMEM SpaceTaxi[] =
{
// width, height,
17, 8,

//facing right frame0
0x00, 0x70, 0x18, 0x6e, 0x1e, 0x5e, 0x12, 0x72, 0x76, 0x7c, 0x18, 0x6a, 0x1e, 0x5a, 0x10, 0x60, 0x00, 

//facing left frame1
0x00, 0x60, 0x10, 0x5a, 0x1e, 0x6a, 0x18, 0x7c, 0x76, 0x72, 0x12, 0x5e, 0x1e, 0x6e, 0x18, 0x70, 0x00, 
};

const unsigned char PROGMEM SpaceTaxiMask[] =
{

//facing right frame0
0x70, 0xf8, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xfa, 0xf0, 0x60,  

//facing left frame1
0x60, 0xf0, 0xfa, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf8, 0x70,
};

const unsigned char PROGMEM livesLeft[] =
{
// width, height,
25, 6,
0x0e, 0x11, 0x29, 0x11, 0x11, 0x12, 0x2a, 0x12, 0x0e, 0x11, 0x29, 0x11, 0x11, 0x12, 0x2a, 0x12, 0x0e, 0x11, 0x29, 0x11, 0x11, 0x12, 0x2a, 0x12, 0x0c, 
};

const unsigned char PROGMEM livesLeftMask[] =
{
0x0e, 0x1f, 0x3f, 0x1f, 0x1f, 0x1e, 0x3e, 0x1e, 0x0e, 0x1f, 0x3f, 0x1f, 0x1f, 0x1e, 0x3e, 0x1e, 0x0e, 0x1f, 0x3f, 0x1f, 0x1f, 0x1e, 0x3e, 0x1e, 0x0c, 
};

const unsigned char PROGMEM Customer[] =
{
// width, height,
7, 8,

//frame0
0x00, 0x08, 0x64, 0x1e, 0x64, 0x02, 0x00, 

//frame1
0x00, 0x08, 0x64, 0x1e, 0x64, 0x04, 0x00, 
};

const unsigned char PROGMEM CustomerMask[] =
{

//frame0
0x08, 0x7c, 0xfe, 0x7f, 0xfe, 0x67, 0x02, 

//frame1
0x08, 0x7c, 0xfe, 0x7f, 0xfe, 0x6e, 0x04, 
};

const unsigned char PROGMEM thrusterRight[] =
{
// width, height,
17, 4,

//Frame0
0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x02, 0x00, 0x00, 

//Frame1
0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 
};

const unsigned char PROGMEM thrusterRightMask[] =
{

//Frame0
0x00, 0x00, 0x00, 0x02, 0x07, 0x0e, 0x07, 0x02, 0x00, 0x00, 0x00, 0x02, 0x07, 0x0e, 0x07, 0x02, 0x00, 

//Frame1
0x00, 0x00, 0x00, 0x00, 0x02, 0x07, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x07, 0x02, 0x00, 0x00, 
};

const unsigned char PROGMEM thrusterLeft[] =
{
// width, height,
17, 4,

//Frame0
0x00, 0x00, 0x02, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 

//Frame1
0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char PROGMEM thrusterLeftMask[] =
{

//Frame0
0x00, 0x02, 0x07, 0x0e, 0x07, 0x02, 0x00, 0x00, 0x00, 0x02, 0x07, 0x0e, 0x07, 0x02, 0x00, 0x00, 0x00, 

//Frame1
0x00, 0x00, 0x02, 0x07, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x07, 0x02, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char PROGMEM SpaceCabSplash[] =
{
// width, height,
//128, 64,
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
0x3e, 0x3e, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x00, 0x00, 0x00, 0x38, 0x7e, 0xfe, 0xff, 0xe7, 0x87, 0x87, 0x07, 0x0e, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x87, 0x87, 0xc7, 0xff, 0xff, 0xfe, 0x7c, 0x00, 0x00, 0xf0, 0xff, 0xff, 0x1f, 0xff, 0xff, 0xf0, 0x80, 0x00, 0x00, 0xe0, 0xf8, 0xfc, 0xfe, 0x1e, 0x0f, 0x07, 0x07, 0x07, 0x0f, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x00, 0x00, 0x00, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x3e, 0x3e, 0x3e, 
0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xc0, 0xc1, 0xc3, 0xe7, 0xff, 0xff, 0x7e, 0x3c, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x80, 0xf8, 0xff, 0xff, 0x7f, 0x3b, 0x38, 0x3b, 0x7f, 0xff, 0xff, 0xf8, 0x80, 0x0f, 0x3f, 0x7f, 0xff, 0xf0, 0xe0, 0xc0, 0xc0, 0xc0, 0xe0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x00, 0x00, 0x00, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 
0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x82, 0x42, 0x80, 0x50, 0x08, 0x50, 0x09, 0x51, 0x29, 0x11, 0x29, 0x11, 0x28, 0x90, 0x40, 0xa0, 0x50, 0xa9, 0x51, 0xa9, 0x81, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x09, 0x11, 0xa9, 0x11, 0xc0, 0xd0, 0xc0, 0xd0, 0xc0, 0x11, 0xa9, 0x11, 0x09, 0x00, 0xc0, 0xd0, 0xc8, 0xd1, 0xc9, 0xd1, 0xc9, 0xd1, 0x89, 0x10, 0x00, 0x01, 0x09, 0x11, 0x29, 0x51, 0xa9, 0x51, 0x89, 0x51, 0x09, 0x50, 0x00, 0x40, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x01, 0x02, 0xf9, 0x7e, 0x7f, 0xff, 0x07, 0x03, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0xc0, 0x7c, 0xff, 0xff, 0x07, 0xff, 0xff, 0x7c, 0xe0, 0x00, 0x00, 0x00, 0xff, 0x7f, 0x7f, 0xff, 0xe1, 0xf1, 0x7f, 0xff, 0x9f, 0x8f, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0d, 0x19, 0x37, 0x6c, 0x58, 0x50, 0x50, 0x50, 0x78, 0x00, 0x60, 0x5e, 0x43, 0x61, 0x13, 0x0a, 0x0a, 0x0a, 0x13, 0x61, 0x43, 0x5e, 0x60, 0x00, 0x7f, 0x41, 0x41, 0x5f, 0x50, 0x50, 0x59, 0x47, 0x21, 0x39, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x27, 0x04, 0x76, 0x04, 0x27, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 
};

const unsigned char PROGMEM bootlogo[] =
{
// width, height,
//128, 64,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0a, 0x2a, 0xa8, 0xa3, 0x8f, 0x3f, 0xff, 0xff, 0xfe, 0xf0, 0x80, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0xc0, 0xc0, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0a, 0x0a, 0x28, 0xa3, 0x87, 0x1f, 0x7f, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x01, 0xf0, 0xf8, 0xfc, 0xfe, 0x06, 0xa3, 0x0b, 0x07, 0x07, 0x3f, 0x0f, 0x23, 0x08, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0a, 0x28, 0xa1, 0x87, 0x1f, 0x7f, 0xff, 0x1f, 0x00, 0x80, 0xf1, 0xf3, 0xf3, 0x63, 0x63, 0x22, 0xb2, 0x1e, 0x20, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0xc8, 0x08, 0x88, 0x4a, 0x8a, 0x48, 0x48, 0x08, 0x88, 0x49, 0x89, 0x08, 0xca, 0x48, 0x09, 0x48, 0xc8, 0x48, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x02, 0x03, 0x03, 0x00, 0x01, 0x02, 0x01, 0x00, 0x03, 0x01, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const unsigned char PROGMEM checkeredBG[] =
{
// width, height,
//128, 64,
0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 
0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 
0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 
0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 
0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 
0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 
0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 
};

const unsigned char PROGMEM SpaceCabHUD[] =
{
// width, height,
128, 9,
0xfe, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xfe, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xfe, 0x00, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 
0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
};

const unsigned char PROGMEM SpaceCabHUDMask[] =
{
// width, height,
//128, 9,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
};

const unsigned char PROGMEM tiles[8][8] =
{
  {0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97 },
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  {0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40 },
  {0x16, 0x05, 0x12, 0x04, 0x14, 0x02, 0x15, 0x06 },
  {0x40, 0x40, 0x4f, 0x09, 0xed, 0x09, 0x4f, 0x40 },
  {0x05, 0x02, 0x05, 0x02, 0x05, 0x02, 0x05, 0x02 },
  {0x07, 0x09, 0x07, 0x0f, 0x07, 0x09, 0x07, 0x0f },
  {0x00, 0x38, 0x44, 0x82, 0x9a, 0xa2, 0x44, 0x38 }
};

//------------------------------------------------------------------------------

// Global Variables now --------------------------------------------------------

uint8_t playerx = 17;
uint8_t playery = 47;
uint8_t playerFrame = 0;

uint8_t thrusterFrame = 0;

uint8_t customerx = 73;
uint8_t customery = 47;
uint8_t customerFrame = 0;
uint8_t customerNewPos = 5;

uint8_t gameTime = 60;

uint16_t currentScore = 0;

uint8_t state = 0;

uint8_t fadeWidth;

int16_t backdropx = 0;
int16_t backdropy = 0;

//------------------------------------------------------------------------------

// Functions -------------------------------------------------------------------

void resetGame()
{
  playerx = 17;
  playery = 47;
  playerFrame = 1;
  thrusterFrame = 0;
  customerx = 73;
  customery = 47;
  customerFrame = 0;
  customerNewPos = 5;
  gameTime = 60;
  currentScore = 0;
}

void playerDisplay()
{
  Sprites::drawExternalMask(playerx, playery, SpaceTaxi, SpaceTaxiMask, playerFrame, playerFrame);
  if(arduboy.everyXFrames(3))
  {
    ++playery;
  }
  if(playery>47)
  {
    playery = 47;
  }
}

void customerDisplay()
{
  Sprites::drawExternalMask(customerx, customery, Customer, CustomerMask, customerFrame, customerFrame);
  if(arduboy.everyXFrames(15))
  {
  ++customerFrame;
  customerFrame %=2;
  }
}

void handleInput()
{
  if(arduboy.pressed(LEFT_BUTTON) && playerx > 0)
  {
    --playerx;
    playerFrame = 1;
  }
  if(arduboy.pressed(RIGHT_BUTTON) && playerx < 111)
  {
    ++playerx;
    playerFrame = 0;
  }
  if(arduboy.pressed(A_BUTTON) && playery > 0)
  {
    if(playerFrame == 0)
    {
      Sprites::drawExternalMask(playerx, playery + 8, thrusterRight, thrusterRightMask, thrusterFrame, thrusterFrame);
    }
    if(playerFrame == 1)
    {
      Sprites::drawExternalMask(playerx, playery + 8, thrusterLeft, thrusterLeftMask, thrusterFrame, thrusterFrame);
    }
    if(arduboy.everyXFrames(5))
    {
      ++thrusterFrame;
      thrusterFrame %=2;
    }
    --playery;
    sound.tone(NOTE_C1, 50, NOTE_C2, 50, NOTE_C1, 50);
  }
}

void scrollingBackground()
{

  arduboy.drawBitmap(backdropx, backdropy, checkeredBG, 128, 64, WHITE);
  arduboy.drawBitmap(backdropx + 128, backdropy, checkeredBG, 128, 64, WHITE);

  if(arduboy.everyXFrames(2))
  { // when running at 60fps

    --backdropx;
    if (backdropx < -128)
    {
      backdropx = 0;
    }
  
  }
}

// Fade effect functions -------------------------------------------------------

void resetFade()
{
  fadeWidth = 0;
}

void resetFadeIn()
{
  fadeWidth = WIDTH;
}

bool fadeIn()
{
  for(uint8_t i = 0; i < (HEIGHT / 2); ++i)
  {
    arduboy.drawFastHLine(0, (i * 2), fadeWidth, BLACK);
    arduboy.drawFastHLine((WIDTH - fadeWidth), (i * 2) + 1, fadeWidth, BLACK);
  }

  if(fadeWidth > 0)
  {
    fadeWidth = fadeWidth - 4;
    return false;
  }
  else
    return true;
}

bool fadeOut()
{
  for(uint8_t i = 0; i < (HEIGHT / 2); ++i)
  {
    arduboy.drawFastHLine(0, (i * 2), fadeWidth, BLACK);
    arduboy.drawFastHLine((WIDTH - fadeWidth), (i * 2) + 1, fadeWidth, BLACK);
  }
  if(fadeWidth < WIDTH)
  {
    ++fadeWidth;
    return false;
  }
  else
    return true;
  }
  
// -----------------------------------------------------------------------------

void drawHUD()
{
  arduboy.drawLine(0, 53, 128, 53, WHITE);
  arduboy.fillRect(0, 55, 128, 64, WHITE);
  Sprites::drawExternalMask(0, 55, SpaceCabHUD, SpaceCabHUDMask, 0, 0);
  arduboy.setCursor(2, 57);
  arduboy.print(F("$"));
  arduboy.print(currentScore);
  arduboy.setCursor(50, 57);
  arduboy.print(gameTime);
  //Sprites::drawExternalMask(64, 57, livesLeft, livesLeftMask, 0, 0);
}

void updateTime()
{
  if(arduboy.everyXFrames(60))
    {
      gameTime = (gameTime > 1) ? gameTime - 1 : state = 3;
    }
}

void customerPosition()
{
  customerNewPos = random(5);
  if(customerNewPos == 1)
  {
    customerx = 1;
    customery = 32;
  }
  if(customerNewPos == 2)
  {
    customerx = 20;
    customery = 8;
  }
  if(customerNewPos == 3)
  {
    customerx = 49;
    customery = 24;
  }
  if(customerNewPos == 4)
  {
    customerx = 98;
    customery = 16;
  }
  if(customerNewPos == 5)
  {
    customerx = 73;
    customery = 47;
  }
}

void checkCollision()
{
  Rect playerRect = {playerx, playery, 17, 8};
  Rect customerRect = {customerx, customery, 7, 8};
  Rect pad1Rect = {0, 39, 16, 8};
  Rect pad2Rect = {17, 16, 24, 8};
  Rect pad3Rect = {49, 32, 16, 8};
  Rect pad4Rect = {97, 24, 24, 8};
  if (arduboy.collide(playerRect, pad1Rect))
  {
    playery = playery - 1;
  }
  if (arduboy.collide(playerRect, pad2Rect))
  {
    playery = playery - 1;
  }
  if (arduboy.collide(playerRect, pad3Rect))
  {
    playery = playery - 1;
  }
  if (arduboy.collide(playerRect, pad4Rect))
  {
    playery = playery - 1;
  }
  if (arduboy.collide(playerRect, customerRect))
  {
    currentScore = currentScore + 2;
    customerPosition();
    sound.tone(NOTE_E6, 50, NOTE_E3, 50, NOTE_E2, 50);
  }
}

void drawLevel()
{
  for(int y = 0; y < LEVEL_HEIGHT; y++)
  {
    for(int x = 0; x < LEVEL_WIDTH; x++)
    {
      arduboy.drawBitmap(x * TILE_SIZE, y * TILE_SIZE, tiles[level1Map[y][x]], TILE_SIZE, TILE_SIZE, WHITE);
      
    }
  }
}

void inGame()
{
  drawHUD();
  drawLevel();
  playerDisplay();
  customerDisplay();
  checkCollision();
  updateTime();
  handleInput();
}

void titleScreen()
{
  Rect playerRect = {playerx, playery, 17, 8};
  Rect customerRect = {97, 48, 7, 8};
  arduboy.drawBitmap(0, 0, SpaceCabSplash, 128, 64, WHITE);
  Sprites::drawExternalMask(97, 48, Customer, CustomerMask, customerFrame, customerFrame);
  if(arduboy.everyXFrames(15))
  {
  ++customerFrame;
  customerFrame %=2;
  }
  Sprites::drawExternalMask(playerx, playery, SpaceTaxi, SpaceTaxiMask, playerFrame, playerFrame);
  if(arduboy.everyXFrames(3))
  {
    ++playery;
  }
  if(playery>47)
  {
    playery = 47;
  }
  if(arduboy.pressed(LEFT_BUTTON) && playerx > 0)
  {
    --playerx;
    playerFrame = 1;
  }
  if(arduboy.pressed(RIGHT_BUTTON) && playerx < 111)
  {
    ++playerx;
    playerFrame = 0;
  }
  if(arduboy.pressed(A_BUTTON) && playery > 0)
  {
    if(playerFrame == 0)
    {
      Sprites::drawExternalMask(playerx, playery + 8, thrusterRight, thrusterRightMask, thrusterFrame, thrusterFrame);
    }
    if(playerFrame == 1)
    {
      Sprites::drawExternalMask(playerx, playery + 8, thrusterLeft, thrusterLeftMask, thrusterFrame, thrusterFrame);
    }
    if(arduboy.everyXFrames(5))
    {
      ++thrusterFrame;
      thrusterFrame %=2;
    }
    --playery;
    sound.tone(NOTE_C1, 50, NOTE_C2, 50, NOTE_C1, 50);
  }

  if (arduboy.collide(playerRect, customerRect))
  {
    arduboy.initRandomSeed();
    resetGame();
    sound.tone(NOTE_C5,50, NOTE_D4,50, NOTE_E3,50);
    state = 2;
  }
}

void vsBoot()
{
  // Vsoft logo display
    arduboy.drawBitmap(0, 0, bootlogo, 128, 64, WHITE);
    if(fadeOut())
    {
      resetFade();
      resetFadeIn();
      state = 1;
    }
}

void gameoverScreen()
{
  scrollingBackground();
  arduboy.fillRect(0, 16, 128, 31, BLACK);
  arduboy.drawLine(0, 17, 128, 17, WHITE);
  arduboy.drawLine(0, 45, 128, 45, WHITE);
  arduboy.drawLine(0, 48, 128, 48, BLACK);
  arduboy.drawLine(0, 50, 128, 50, BLACK);

  arduboy.setCursor(37, 22);
  arduboy.print(F("GAME OVER"));

  arduboy.setCursor(40, 34);
  arduboy.print(F("SCORE:"));
  arduboy.print(currentScore);
  
  if (arduboy.justPressed(B_BUTTON))
  {
    state = 1;
  }
}


//------------------------------------------------------------------------------

void setup() {
  arduboy.boot();
  arduboy.display();
  arduboy.flashlight();
  arduboy.systemButtons();
  arduboy.audio.begin();
  arduboy.clear();
  arduboy.setFrameRate(60);

  // initialize things here

}

void loop() {
  if (!(arduboy.nextFrame()))
    return;

  arduboy.pollButtons();
  arduboy.clear();

  // Here we go!
  
  if (state == 0)  { vsBoot(); }
  else if (state == 1)  { titleScreen(); }
  else if (state == 2)  { inGame(); }
  else if (state == 3)  { gameoverScreen(); }


  arduboy.display();
}

