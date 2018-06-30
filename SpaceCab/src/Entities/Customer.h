#pragma once

struct Customer {

  uint16_t x;
  uint16_t y;
  uint8_t frame;
  
  void incFrame() {
    frame = (frame == 0 ? 1 : 0);
  }

};