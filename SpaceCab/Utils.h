#pragma once
#include <Arduboy2.h>
Arduboy2Base arduboy;

uint8_t fadeWidth;

// Extract individual digits of a uint8_t -------------------------------------

template< size_t size > void extractDigits(uint8_t (&buffer)[size], uint8_t value)
{
  for(uint8_t i = 0; i < size; ++i)
  {
    buffer[i] = value % 10;
    value /= 10;
  }
}

// Extract individual digits of a uint16_t
template< size_t size > void extractDigits(uint8_t (&buffer)[size], uint16_t value)
{
  for(uint8_t i = 0; i < size; ++i)
  {
    buffer[i] = value % 10;
    value /= 10;
  }
}

//------------------------------------------------------------------------------

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

  if (fadeWidth > 0)
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
  if (fadeWidth < WIDTH)
  {
    ++fadeWidth;
    return false;
  }
  else
    return true;
  }
  
// -----------------------------------------------------------------------------


void initLevel(uint8_t levelNumber, Player *player, Level *level) {

  uint8_t width = levelInit[levelNumber * 6];
  uint8_t height = levelInit[(levelNumber * 6) + 1];

  level->xOffset = static_cast<SQ15x16>(levelInit[(levelNumber * 6) + 2]);
  level->yOffset = static_cast<SQ15x16>(levelInit[(levelNumber * 6) + 3]);

  player->x = static_cast<SQ15x16>(levelInit[(levelNumber * 6) + 4]);
  player->y = static_cast<SQ15x16>(levelInit[(levelNumber * 6) + 5]);

  player->frame = 1;
  
  level->setLevelNumber(levelNumber);
  level->setHeight(height * TILE_SIZE);
  level->setWidth(width * TILE_SIZE);
  level->setHeightInTiles(height);
  level->setWidthInTiles(width);

}


// ----------------------------------------------------------------------------
//  A better absolute as it uses less memory than the standard one .. 
//
template<typename T> T absT(const T & v) {
  
  return (v < 0) ? -v : v;

}