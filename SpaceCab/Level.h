#pragma once

#include "Levels.h"
#include "Constants.h"

#include "FixedPoints.h"
#include "FixedPointsCommon.h"

struct Level {

  uint8_t number;
  
  uint16_t width = LEVEL_WIDTH * 8;
  SQ15x16 xOffset;

  int16_t getXOffsetDisplay() { return xOffset.getInteger(); }

};