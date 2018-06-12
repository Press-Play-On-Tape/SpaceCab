#pragma once

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
#define SHADE 8
#define BRICK 9
#define TILE_SIZE 8

const unsigned char PROGMEM tiles[10][8] =
{
  {0x0d, 0x9f, 0x2d, 0x97, 0x0d, 0x9f, 0x2d, 0x97 },
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  {0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40 },
  {0x16, 0x05, 0x12, 0x04, 0x14, 0x02, 0x15, 0x06 },
  {0x40, 0x40, 0x4f, 0x09, 0xed, 0x09, 0x4f, 0x40 },
  {0x05, 0x02, 0x05, 0x02, 0x05, 0x02, 0x05, 0x02 },
  {0x07, 0x09, 0x07, 0x0f, 0x07, 0x09, 0x07, 0x0f },
  {0x00, 0x38, 0x44, 0x82, 0x9a, 0xa2, 0x44, 0x38 },
  {0x09, 0x22, 0x09, 0x22, 0x09, 0x22, 0x09, 0x22 },
  {0x82, 0x5a, 0x9a, 0x42, 0x98, 0x5a, 0x9a, 0x58 }
};

// Level 1 layout --------------------------------------------------------------

int level1Map[LEVEL_HEIGHT][LEVEL_WIDTH] = {
  { ROCK2, ROCK2, ROCK2, ROCK2, ROCK2, ROCK2, ROCK2, ROCK2, ROCK2, GATE1, GATE1, GATE1, ROCK2, ROCK2, ROCK2, ROCK2 },
  { EMPTY, EMPTY, EDGE1, EDGE1, EDGE1, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
  { EMPTY, EMPTY, BRICK, BRICK, BRICK, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EDGE1, EDGE1, SIGN1, EMPTY },
  { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EDGE1, EDGE1, EMPTY, EMPTY, EMPTY, EMPTY, BRICK, BRICK, BRICK, EMPTY },
  { EDGE1, SIGN1, EMPTY, EMPTY, EMPTY, EMPTY, BRICK, BRICK, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
  { BRICK, BRICK, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
  { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
  { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, CLOCK, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
};

//-------------------------------------------------------------------------------------
