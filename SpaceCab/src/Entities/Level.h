#pragma once

#include "../Utils/Arduboy2Ext.h"
#include "../Utils/Constants.h"
#include "Levels.h"
#include "Fuel.h"
#include "Gate.h"

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
    bool _openGates;
    uint8_t _levelScore;

    Gate _gate0;
    Gate _gate1;
    Gate _gate2;
    Gate _gate3;
    Gate _gate4;

    Gate *_gates[GATE_TILES_MAX] = { &_gate0, &_gate1, &_gate2, &_gate3, &_gate4 };


  public:

    Level(Fuel* fuels[]) {
      
      for (uint8_t x = 0 ; x < FUEL_TILES_MAX; x++) {
        _fuels[x] = fuels[x];
      }
      
      for (uint8_t x = 0 ; x < GATE_TILES_MAX; x++) {
        _gates[x]->setActive(false);
      }

    };

    int16_t getXOffsetDisplay()               const { return xOffset.getInteger(); }
    int16_t getYOffsetDisplay()               const { return yOffset.getInteger(); }

    uint16_t getLevelNumber()                 const { return _number; }
    uint16_t getHeight()                      const { return _height; }
    uint16_t getWidth()                       const { return _width; }
    uint16_t getHeightInTiles()               const { return _heightInTiles; }
    uint16_t getWidthInTiles()                const { return _widthInTiles; }
    uint16_t getLevelScore()                  const { return _levelScore; }

    Fuel * getFuel(uint8_t idx)               const { return _fuels[idx]; }

    void setHeight(uint16_t val)              { _height = val; }
    void setWidth(uint16_t val)               { _width = val; }
    void setHeightInTiles(uint16_t val)       { _heightInTiles = val; _height = val * TILE_SIZE; }
    void setWidthInTiles(uint16_t val)        { _widthInTiles = val; _width = val * TILE_SIZE; }

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

      uint8_t tile = EMPTY;

      if ((x % 2) == 0) {
        tile = (_levelData[((y * _widthInTiles) / 2) + (x / 2)] >> 4);
      }
      else {
        tile = (_levelData[((y * _widthInTiles) / 2) + (x / 2)] & 0x0f);
      }

      switch (tile) {

        case GATE1:

          if (_openGates) return EMPTY;
          return GATE1;

        default:  
          return tile;

      }

    }

    void openGates() {
      _openGates = true;
    }

    void reset(uint8_t levelNumber/*, uint8_t width, uint8_t height*/) { 
      
      _number = levelNumber; 
      _openGates = false;

      _widthInTiles = levelInit[levelNumber * 7];
      _heightInTiles = levelInit[(levelNumber * 7) + 1];
      _width = _widthInTiles * TILE_SIZE;
      _height = _heightInTiles * TILE_SIZE;

      xOffset = static_cast<SQ15x16>(levelInit[(levelNumber * 7) + 2]);
      yOffset = static_cast<SQ15x16>(levelInit[(levelNumber * 7) + 3]);
      _levelScore = levelInit[(levelNumber * 7) + 6];


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
        uint8_t gateIdx = 0;
        
        for (uint8_t y = 0; y < _heightInTiles; y++) {

          for (uint8_t x = 0; x < _widthInTiles; x = x + 2) {

            uint8_t tileIndex = ((y * _widthInTiles) / 2) + (x / 2);
            uint8_t tiles = pgm_read_byte(&levelMap[tileIndex]);

            _levelData[tileIndex] = tiles;

            {

              // Left hand side tile ..

              uint8_t tile = (tiles & 0xf0) >> 4;

              switch (tile) {

                case FUEL1:
                  updateFuelDetails(x, y, fuelIdx);
                  fuelIdx++;
                  break;

                case GATE1:
                  updateGateDetails(x, y, gateIdx);
                  gateIdx++;
                  break;

              }


              // Right hand side tile ..

              tile = (tiles & 0x0f);

              switch (tile) {

                case FUEL1:
                  updateFuelDetails(x, y, fuelIdx);
                  fuelIdx++;
                  break;

                case GATE1:
                  updateGateDetails(x, y, gateIdx);
                  gateIdx++;
                  break;

              }

            }

          }

        }

      }

    }

    void updateFuelDetails(uint8_t x, uint8_t y, uint8_t index) {

      Fuel *fuel = _fuels[index];
      fuel->setXTile(x);
      fuel->setYTile(y);
      fuel->setFuelLeft(random(FUEL_MIN, FUEL_MAX));
 
    }

    void updateGateDetails(uint8_t x, uint8_t y, uint8_t index) {

      Gate *gate = _gates[index];
      gate->setXTile(x);
      gate->setYTile(y);
      gate->setActive(true);
 
    }

};