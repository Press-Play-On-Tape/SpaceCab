#pragma once

#include <Arduboy2.h>

class Slot {

  public: 

    Slot() {};
  

    // Properties ..

    uint8_t getChar0();
    uint8_t getChar1();
    uint8_t getChar2();
    uint16_t getScore();

    void setChar0(uint8_t val);
    void setChar1(uint8_t val);
    void setChar2(uint8_t val);
    void setScore(uint16_t val);


  private:
   
    uint8_t _char0;
    uint8_t _char1;
    uint8_t _char2;
    uint16_t _score;

};


//--------------------------------------------------------------------------------------------------------------------------
// Properties ..

uint8_t Slot::getChar0() {
  return _char0;
}

uint8_t Slot::getChar1() {
  return _char1;
}

uint8_t Slot::getChar2() {
  return _char2;
}

uint16_t Slot::getScore() {
  return _score;
}

void Slot::setChar0(uint8_t val) {
  _char0 = val;
}

void Slot::setChar1(uint8_t val) {
  _char1 = val;
}

void Slot::setChar2(uint8_t val) {
  _char2 = val;
}

void Slot::setScore(uint16_t val) {
  _score = val;
}