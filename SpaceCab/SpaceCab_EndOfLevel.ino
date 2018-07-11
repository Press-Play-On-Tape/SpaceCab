#include "src/utils/Arduboy2Ext.h"
#include "src/utils/Vector2.h"

Vector2 stars[16];

constexpr Vector2 centreScreen = Vector2(WIDTH / 2, HEIGHT / 2);

const Vector2 offsets[16] PROGMEM = {
	Vector2(1.0000, 0.0000),
	Vector2(0.9239, 0.3827),
	Vector2(0.7071, 0.7071),
	Vector2(0.3827, 0.9239),
	Vector2(0.0000, 1.0000),
	Vector2(-0.3827, 0.9239),
	Vector2(-0.7071, 0.7071),
	Vector2(-0.9239, 0.3827),
	Vector2(-1.0000, 0.0000),
	Vector2(-0.9239, -0.3827),
	Vector2(-0.7071, -0.7071),
	Vector2(-0.3827, -0.9239),
	Vector2(0.0000, -1.0000),
	Vector2(0.3827, -0.9239),
	Vector2(0.7071, -0.7071),
	Vector2(0.9239, -0.3827),
};

bool starsInitialised = false;

void initialiseStars(void) {

	for(uint8_t i = 0; i < 16; ++i) stars[i] = centreScreen;
	starsInitialised = true;

}

void resetStars(void) {
	starsInitialised = false;
}

void updateStarfield(void) {

	for(uint8_t i = 0; i < 16; ++i) {

		stars[i].x += SQ7x8::fromInternal(pgm_read_word(&offsets[i].x));
		stars[i].y += SQ7x8::fromInternal(pgm_read_word(&offsets[i].y));
		
		if (stars[i].x < 0 || stars[i].y < 0) stars[i] = centreScreen;

	}

}

void drawStarfield() {

	for(uint8_t i = 0; i < 16; ++i) {
		arduboy.drawPixel(static_cast<int8_t>(stars[i].x), static_cast<int8_t>(stars[i].y));
  }
  
}

void blackScanlines() {

  for(uint8_t i = 0; i < (HEIGHT); i+=8) {
    
    arduboy.drawFastHLine(0, i, WIDTH, BLACK);

  }

}
