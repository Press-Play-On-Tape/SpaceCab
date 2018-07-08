#pragma once

#include "../Utils/Arduboy2Ext.h"
#include "../Utils/Constants.h"
#include "Levels.h"
#include "Fuel.h"

#include "FixedPoints.h"
#include "FixedPointsCommon.h"

struct Level {

  public:
 
    SQ15x16 xOffset = 0;
    SQ15x16 yOffset = 0;

  private:
 
    uint8_t _number;
    uint16_t _height = 0;
    uint16_t _width = 0;
    uint16_t _heightInTiles = 0;
    uint16_t _widthInTiles = 0;
    Fuel *_fuels[FUEL_TILES_MAX];
    uint8_t _levelData[256];

  public:

    Level(Fuel* fuels[]) {
      
      for (uint8_t x = 0 ; x < FUEL_TILES_MAX; x++) {
        _fuels[x] = fuels[x];
      }

    };

    int16_t getXOffsetDisplay()               const { return xOffset.getInteger(); }
    int16_t getYOffsetDisplay()               const { return yOffset.getInteger(); }

    uint16_t getLevelNumber()                 const { return _number; }
    uint16_t getHeight()                      const { return _height; }
    uint16_t getWidth()                       const { return _width; }
    uint16_t getHeightInTiles()               const { return _heightInTiles; }
    uint16_t getWidthInTiles()                const { return _widthInTiles; }

    Fuel * getFuel(uint8_t idx)               const { return _fuels[idx]; }

    void setHeight(uint16_t val)              { _height = val; }
    void setWidth(uint16_t val)               { _width = val; }
    void setHeightInTiles(uint16_t val)       { _heightInTiles = val; }
    void setWidthInTiles(uint16_t val)        { _widthInTiles = val; }

    void setFuel(uint8_t idx, Fuel * fuel)    { _fuels[idx] = fuel; }

    Fuel * getFuel(uint8_t xTile, uint8_t yTile) {

      for (uint8_t i = 0; i < FUEL_TILES_MAX; i++) {

        Fuel *fuel = _fuels[i];

        if (fuel->getXTile() == xTile && fuel->getYTile() == yTile) {
          return fuel;
        }

      }

      return nullptr;

    }


    uint8_t getLevelData(uint8_t x, uint8_t y) {

      if ((x % 2) == 0) {
        return (_levelData[((y * _widthInTiles) / 2) + (x / 2)] >> 4);
      }
      else {
        return (_levelData[((y * _widthInTiles) / 2) + (x / 2)] & 0x0f);
      }

    }

    void setLevelNumber(uint8_t val) { 
      
      _number = val; 


    // Parse level for fuel tiles ..

    for (uint8_t y = 0; y < FUEL_TILES_MAX; y++) {

      Fuel *fuel = _fuels[y];
      fuel->setXTile(0);
      fuel->setYTile(0);
      fuel->setFuelLeft(0);

    }

    {
 
      const uint8_t *levelMap = levelMaps[_number];
      uint8_t fuelIdx = 0;
      
      for (uint8_t y = 0; y < _heightInTiles; y++) {

        for (uint8_t x = 0; x < _widthInTiles; x = x + 2) {

          uint8_t tileIndex = ((y * _widthInTiles) / 2) + (x / 2);
          uint8_t tile = pgm_read_byte(&levelMap[tileIndex]);

          _levelData[tileIndex] = tile;

          {
            uint8_t isFuel = (tile & 0xf0) >> 4;

            if (isFuel == FUEL1) {
              
              Fuel *fuel = _fuels[fuelIdx];
              fuel->setXTile(x);
              fuel->setYTile(y);
              fuel->setFuelLeft(random(FUEL_MIN, FUEL_MAX));
              fuelIdx++;

            }

            isFuel = (tile & 0x0f);

            if (isFuel == FUEL1) {
              
              Fuel *fuel = _fuels[fuelIdx];
              fuel->setXTile(x);
              fuel->setYTile(y);
              fuel->setFuelLeft(random(FUEL_MIN, FUEL_MAX));
              fuelIdx++;

            }

          }

        }

      }

    }

  }

};