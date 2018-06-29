#pragma once

#include "Constants.h"

#include "FixedPoints.h"
#include "FixedPointsCommon.h"

struct Player {

  SQ15x16 x;
  SQ15x16 y;
  uint8_t frame = 0;

  int8_t xDelta = 0;
  int8_t yDelta = 0;

  uint16_t getXDisplay() { return x.getInteger(); }
  uint16_t getYDisplay() { return y.getInteger(); }

  uint8_t getXCentre() { return (64 - PLAYER_WIDTH_HALF); }
  uint8_t getYCentre() { return (32 - PLAYER_HEIGHT_HALF); }

  SQ15x16 getXDeltaVal() { return (static_cast<SQ15x16>(xDelta) / 8.00); }
  SQ15x16 getYDeltaVal() { return (static_cast<SQ15x16>(yDelta) / 8.00); }

  void incXDelta() {

    switch (xDelta) {

        case -8 ... -2:
        xDelta = xDelta / 2;
        break;
        
        case -1:
        xDelta = 0;
        break;
        
        case 0:
        xDelta = 1;
        break;

        case 1 ... 4:
        xDelta = xDelta * 2;
        break;

    }

  }

  void decXDelta() {

    switch (xDelta) {

        case -4 ... -1:
        xDelta = xDelta * 2;
        break;

        case 0:
        xDelta = -1;
        break;

        case 1:
        xDelta = 0;
        break;

        case 2 ... 8:
        xDelta = xDelta / 2;
        break;
        
    }

  }

  void incYDelta() {

    switch (yDelta) {

        case -8 ... -2:
        yDelta = yDelta / 2;
        break;
        
        case -1:
        yDelta = 0;
        break;
        
        case 0:
        yDelta = 1;
        break;

        case 1 ... 4:
        yDelta = yDelta * 2;
        break;

    }

  }

  void decYDelta() {

    switch (yDelta) {

        case -4 ... -1:
        yDelta = yDelta * 2;
        break;

        case 0:
        yDelta = -1;
        break;

        case 1:
        yDelta = 0;
        break;

        case 2 ... 8:
        yDelta = yDelta / 2;
        break;
        
    }

  }

};