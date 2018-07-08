#pragma once

#include "Arduboy2Ext.h"
#include "Constants.h"

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

void initGame(Player *player) {

  player->setNumberOfLives(PLAYER_NUMBER_OF_LIVES_MAX);
  player->setScore(0);

}

void initLevel(Level *level, Player *player, Customer *customer, uint8_t levelNumber) {

  uint8_t width = levelInit[levelNumber * 6];
  uint8_t height = levelInit[(levelNumber * 6) + 1];

  level->xOffset = static_cast<SQ15x16>(levelInit[(levelNumber * 6) + 2]);
  level->yOffset = static_cast<SQ15x16>(levelInit[(levelNumber * 6) + 3]);

  player->setX(static_cast<SQ15x16>(levelInit[(levelNumber * 6) + 4]));
  player->setY(static_cast<SQ15x16>(levelInit[(levelNumber * 6) + 5]));
  player->setXDelta(0);
  player->setYDelta(0);
  player->setFrame(1);
  player->setFuel(PLAYER_FUEL_MAX);
  player->setCarryingCustomer(false);
  player->setStatus(PlayerStatus::Active);
  player->setLandingGearDown(true);
  player->setJustLanded(true);
  player->setPickingUpCustomer(false);
  
  level->setHeight(height * TILE_SIZE);
  level->setWidth(width * TILE_SIZE);
  level->setHeightInTiles(height);
  level->setWidthInTiles(width);
  level->setLevelNumber(levelNumber);

  customer->setStartingPosition(CUSTOMER_NO_STARTING_POS);


}


// ----------------------------------------------------------------------------
//  A better absolute as it uses less memory than the standard one .. 
//
template<typename T> T absT(const T & v) {
  
  return (v < 0) ? -v : v;

}


// ----------------------------------------------------------------------------------------------------------
//  Is the nominated tile solid?
// ----------------------------------------------------------------------------------------------------------

bool isTileSolid(uint8_t tileType) {

  switch (tileType) {
    
    case BRICK:
    case PLAT1:
    case ROCKS:
    case METAL:
    case SAND1:
      return true;

    default:
      return false;

  }
  
}