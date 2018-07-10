#include "src/utils/Arduboy2Ext.h"

uint8_t starfieldy = 0;

void drawStarfield()
{
  arduboy.drawBitmap(0, starfieldy, starBackground, 128, 64, WHITE);
  arduboy.drawBitmap(0, starfieldy - 64, starBackground, 128, 64, WHITE);
  ++starfieldy;
  if( starfieldy > 64 )
  {
    starfieldy = 0;
  }
}

void blackScanlines()
{
  for(uint8_t i = 0; i < (HEIGHT);)
  {
    i+=8;
    arduboy.drawFastHLine(0, i, WIDTH, BLACK);
  }
}
