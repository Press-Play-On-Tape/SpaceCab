#pragma once

#include "../Utils/Constants.h"

#include "FixedPoints.h"
#include "FixedPointsCommon.h"

#define PLAYER_X_CENTRE 56
#define PLAYER_Y_CENTRE 28

struct Player {

  private:

    SQ15x16 _x;
    SQ15x16 _y;
    int8_t _xDelta = 0;
    int8_t _yDelta = 0;
    uint8_t _frame = 0;
    uint8_t _retractLandgingGear = 0; // Counter when moving up.
    uint16_t _fuel = 0;
    uint16_t _score = 0;
    bool _carryingCustomer = false;
    bool _landingGearDown = false;
    bool _justLanded = true;
    uint8_t _numberOfLives = 0;
    PlayerStatus _status;

  public:

    const SQ15x16 getX()                        { return _x; }
    const SQ15x16 getY()                        { return _y; }
    int8_t getXDelta()                          { return _xDelta; }
    int8_t getYDelta()                          { return _yDelta; }
    uint8_t getFrame()                          { return _frame; }
    uint8_t getNumberOfLives()                  { return _numberOfLives; }
    uint16_t getFuel()                          { return _fuel; }
    uint16_t getScore()                         { return _score; }
    bool isCarryingCustomer()                   { return _carryingCustomer; }
    bool isLandingGearDown()                    { return _landingGearDown; }
    bool hasJustLanded()                        { return _justLanded; }
    PlayerStatus getStatus()                    { return _status; }
    uint8_t getRetractLandingGear()             { return _retractLandgingGear; }

    void setX(SQ15x16 val)                      { _x = val; }
    void setY(SQ15x16 val)                      { _y = val; }
    void setXDelta(int8_t val)                  { _xDelta = val; }
    void setYDelta(int8_t val)                  { _yDelta = val; }
    void setFrame(uint8_t val)                  { _frame = val; }
    void setNumberOfLives(uint8_t val)          { _numberOfLives = val; }
    void setFuel(uint16_t val)                  { _fuel = val; }
    void setScore(uint16_t val)                 { _score = val; }
    void setCarryingCustomer(bool val)          { _carryingCustomer = val; }
    void setLandingGearDown(bool val)           { _landingGearDown = val; }
    void setJustLanded(bool val)                { _justLanded = val; }
    void setStatus(PlayerStatus val)            { _status = val; }
    void setRetractLandingGear(int8_t val)      { _retractLandgingGear = val; }

    uint16_t getXDisplay()                      { return _x.getInteger(); }
    uint16_t getYDisplay()                      { return _y.getInteger(); }
    SQ15x16 getXDeltaVal()                      { return (static_cast<SQ15x16>(_xDelta) / 8.00); }
    SQ15x16 getYDeltaVal()                      { return (static_cast<SQ15x16>(_yDelta) / 8.00); }

    void incFuel()                              { _fuel++;}
    void decFuel()                              { _fuel--;}
    void decNumberOfLives()                     { _numberOfLives--;}
    void decStatus()                            { _status--;}

    void decRetractLandingGear() { 

      if (_retractLandgingGear > 0) {

        _retractLandgingGear--;

        if (_retractLandgingGear == 0) {

          _landingGearDown = false;

        }

      }

    }

    void incXDelta() {

      switch (_xDelta) {

        case -8 ... -2:
          _xDelta = _xDelta / 2;
          break;
          
        case -1:
          _xDelta = 0;
          break;
          
        case 0:
          _xDelta = 1;
          break;

        case 1 ... 4:
          _xDelta = _xDelta * 2;
          break;

      }

    }

    void decXDelta() {

      switch (_xDelta) {

        case -4 ... -1:
          _xDelta = _xDelta * 2;
          break;

        case 0:
          _xDelta = -1;
          break;

        case 1:
          _xDelta = 0;
          break;

        case 2 ... 8:
          _xDelta = _xDelta / 2;
          break;
          
      }

    }

    void incYDelta() {
      
      switch (_yDelta) {

        case -8 ... -2:
          _yDelta = _yDelta / 2;
          break;
          
        case -1:
          _yDelta = 0;
          break;
          
        case 0:
          _yDelta = 1;
          break;

        case 1 ... 4:
          _yDelta = _yDelta * 2;
          break;

      }

    }

    void decYDelta() {

      switch (_yDelta) {

        case -4 ... -1:
          _yDelta = _yDelta * 2;
          break;

        case 0:
          _yDelta = -1;
          break;

        case 1:
          _yDelta = 0;
          break;

        case 2 ... 8:
          _yDelta = _yDelta / 2;
          break;
          
      }

    }

};