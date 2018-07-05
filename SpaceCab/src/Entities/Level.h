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

    void setLevelNumber(uint8_t val)          { _number = val; }
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



};