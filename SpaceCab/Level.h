#pragma once

#include "Levels.h"
#include "Constants.h"

#include "FixedPoints.h"
#include "FixedPointsCommon.h"

struct Level
{
public:
  uint8_t number;
  
  uint16_t height = LEVEL_HEIGHT * 8;
  uint16_t width = LEVEL_WIDTH * 8;
  SQ15x16 xOffset = 0;
  SQ15x16 yOffset = 0;

 public:
  int16_t getXOffsetDisplay() const { return xOffset.getInteger(); }
  int16_t getYOffsetDisplay() const { return yOffset.getInteger(); }
};