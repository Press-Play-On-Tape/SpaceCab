#pragma once

#include <Arduboy2.h>
#include "Constants.h"

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

void initGame(Player *player, Level *level, Customer *customer) {

  player->numberOfLives = 1; //SJHPLAYER_NUMBER_OF_LIVES_MAX;
  player->currentScore = 0;

}

void initLevel(uint8_t levelNumber, Player *player, Level *level, Customer *customer) {

  uint8_t width = levelInit[levelNumber * 6];
  uint8_t height = levelInit[(levelNumber * 6) + 1];

  level->xOffset = static_cast<SQ15x16>(levelInit[(levelNumber * 6) + 2]);
  level->yOffset = static_cast<SQ15x16>(levelInit[(levelNumber * 6) + 3]);

  player->x = static_cast<SQ15x16>(levelInit[(levelNumber * 6) + 4]);
  player->y = static_cast<SQ15x16>(levelInit[(levelNumber * 6) + 5]);
  player->xDelta = 0;
  player->yDelta = 0;
  player->frame = 1;
  player->fuel = PLAYER_FUEL_MAX;
  player->carryingCustomer = false;
  player->status = PlayerStatus::Active;
  
  level->setLevelNumber(levelNumber);
  level->setHeight(height * TILE_SIZE);
  level->setWidth(width * TILE_SIZE);
  level->setHeightInTiles(height);
  level->setWidthInTiles(width);

  customer->setStartingPosition(CUSTOMER_NO_STARTING_POS);

}


// ----------------------------------------------------------------------------
//  A better absolute as it uses less memory than the standard one .. 
//
template<typename T> T absT(const T & v) {
  
  return (v < 0) ? -v : v;

}