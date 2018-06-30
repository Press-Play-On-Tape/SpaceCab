#pragma once

#include "Levels.h"
#include "../Utils/Constants.h"

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

  public:
    int16_t getXOffsetDisplay()           const { return xOffset.getInteger(); }
    int16_t getYOffsetDisplay()           const { return yOffset.getInteger(); }

    uint16_t getLevelNumber()             const { return _number; }
    uint16_t getHeight()                  const { return _height; }
    uint16_t getWidth()                   const { return _width; }
    uint16_t getHeightInTiles()           const { return _heightInTiles; }
    uint16_t getWidthInTiles()            const { return _widthInTiles; }

    void setLevelNumber(uint8_t val)      { _number = val; }
    void setHeight(uint16_t val)          { _height = val; }
    void setWidth(uint16_t val)           { _width = val; }
    void setHeightInTiles(uint16_t val)   { _heightInTiles = val; }
    void setWidthInTiles(uint16_t val)    { _widthInTiles = val; }


};