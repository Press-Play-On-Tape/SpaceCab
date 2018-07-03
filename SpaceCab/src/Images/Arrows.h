#pragma once

#include "Arduboy2.h"
#include "../Utils/Constants.h"

#ifdef ARROWS_FP
const unsigned char PROGMEM ArrowDL[] = {
8, 8,
0x00, 0x7c, 0x78, 0x70, 0x60, 0x40, 0x00, 0x00, 
};

const unsigned char PROGMEM ArrowDL_Mask[] = {
//8, 8,
0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 
};

const unsigned char PROGMEM ArrowDR[] = {
8, 8,
0x00, 0x00, 0x40, 0x60, 0x70, 0x78, 0x7c, 0x00, 
};

const unsigned char PROGMEM ArrowDR_Mask[] = {
//8, 8,
0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 
};

const unsigned char PROGMEM ArrowD[] = {
9, 8,
0x00, 0x08, 0x18, 0x38, 0x78, 0x38, 0x18, 0x08, 0x00, 
};

const unsigned char PROGMEM ArrowD_Mask[] = {
//9, 8,
0x0c, 0x1c, 0x3c, 0x7c, 0xfc, 0x7c, 0x3c, 0x1c, 0x0c, 
};

const unsigned char PROGMEM ArrowL[] = {
8, 9,
0x00, 0x10, 0x38, 0x7c, 0xfe, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const unsigned char PROGMEM ArrowL_Mask[] = {
//8, 9,
0x10, 0x38, 0x7c, 0xfe, 0xff, 0xff, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 
};

const unsigned char PROGMEM ArrowR[] = {
8, 9,
0x00, 0x00, 0x00, 0xfe, 0x7c, 0x38, 0x10, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const unsigned char PROGMEM ArrowR_Mask[] = {
//8, 9,
0x00, 0x00, 0xff, 0xff, 0xfe, 0x7c, 0x38, 0x10, 
0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 
};

const unsigned char PROGMEM ArrowU[] = {
9, 8,
0x00, 0x10, 0x18, 0x1c, 0x1e, 0x1c, 0x18, 0x10, 0x00, 
};

const unsigned char PROGMEM ArrowU_Mask[] = {
//9, 8,
0x30, 0x38, 0x3c, 0x3e, 0x3f, 0x3e, 0x3c, 0x38, 0x30, 
};

const unsigned char PROGMEM ArrowUL[] = {
8, 8,
0x00, 0x3e, 0x1e, 0x0e, 0x06, 0x02, 0x00, 0x00, 
};

const unsigned char PROGMEM ArrowUL_Mask[] = {
//8, 8,
0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 
};

const unsigned char PROGMEM ArrowUR[] = {
8, 8,
0x00, 0x00, 0x02, 0x06, 0x0e, 0x1e, 0x3e, 0x00, 
};

const unsigned char PROGMEM ArrowUR_Mask[] = {
//8, 8,
0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff, 
};

#endif
#ifndef ARROWS_FP

const unsigned char PROGMEM ArrowImgs[] = {
// width, height,
8, 8,
0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 
0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x1f, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 
0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0xf8,
0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 
0xf8, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 
0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x1f, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
};

const unsigned char PROGMEM ArrowMasks[] = {
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x3f, 0x3f,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xfc,
0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 
0xfc, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00,
0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
0x3f, 0x3f, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 
};

#endif
