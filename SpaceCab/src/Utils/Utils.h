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

void initGame(Level *level, Player *player, Customer *customer) {

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
  
  level->setLevelNumber(levelNumber);
  level->setHeight(height * TILE_SIZE);
  level->setWidth(width * TILE_SIZE);
  level->setHeightInTiles(height);
  level->setWidthInTiles(width);

  customer->setStartingPosition(CUSTOMER_NO_STARTING_POS);



  // Parse level for fuel tiles ..

  for (uint8_t y = 0; y < FUEL_TILES_MAX; y++) {

    Fuel *fuel = level->getFuel(y);
    fuel->setXTile(0);
    fuel->setYTile(0);
    fuel->setFuelLeft(0);

  }

  {
    const uint8_t *levelMap = levelMaps[level->getLevelNumber()];
    uint8_t fuelIdx = 0;
    
    for (uint8_t y = 0; y < level->getHeightInTiles(); y++) {

      for (uint8_t x = 0; x < level->getWidthInTiles(); x++) {

        uint8_t tile = pgm_read_byte(&levelMap[(y * level->getWidthInTiles()) + x]);

        if (tile == FUEL1) {
          
          Fuel *fuel = level->getFuel(fuelIdx);
          fuel->setXTile(x);
          fuel->setYTile(y);
          fuel->setFuelLeft(random(FUEL_MIN, FUEL_MAX));
          fuelIdx++;

        }

      }

    }

  }




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