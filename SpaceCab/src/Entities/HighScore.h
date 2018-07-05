#pragma once

#include "../Utils/Arduboy2Ext.h"
#include "../Utils/Constants.h"

struct HighScore {

  private:
   
    uint8_t _slotNumber;
    uint8_t _charIndex;
    uint8_t _chars[3];

  public: 

    HighScore() {

      _slotNumber = DO_NOT_EDIT_SLOT;
      _charIndex = 0;
      _chars[0] = 0;
      _chars[1] = 0;
      _chars[2] = 0;

    };

    uint8_t getSlotNumber()                    { return _slotNumber; }
    uint8_t getCharIndex()                     { return _charIndex; }
    uint8_t getChar(uint8_t idx)               { return _chars[idx]; }

    void setSlotNumber(uint8_t val)            { _slotNumber = val; }
    void setCharIndex(uint8_t val)             { _charIndex = val; }
    void setChar(uint8_t idx, uint8_t val)     { _chars[idx] = val; }


    void incCharIndex() {
      if (_charIndex < 2) _charIndex++;
    }

    void decCharIndex() {
      if (_charIndex > 0) _charIndex--;
    }

    void incChar(uint8_t idx) {
      
      if (_chars[idx] == 26) {
        _chars[idx] = 0; 
      } 
      else { 
        _chars[idx]++;
      } 

    }

    void decChar(uint8_t idx) {
      
      if (_chars[idx] == 0) {
        _chars[idx] = 25; 
      } 
      else { 
        _chars[idx]--;
      } 

    }

    void disableEditting() {
      _slotNumber = 255;
    }

    void reset() {

      _slotNumber = 255;
      _charIndex = 0;
      _chars[0] = 0;
      _chars[1] = 0;
      _chars[2] = 0;

    }

};
