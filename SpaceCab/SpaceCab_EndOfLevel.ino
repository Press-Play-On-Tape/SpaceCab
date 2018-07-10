#include "src/utils/Arduboy2Ext.h"

uint8_t starfieldy = 0;

void drawStarfield()
{
  Sprites::drawOverwrite(0, starfieldy, starBackground, WHITE);
  Sprites::drawOverwrite(0, starfieldy - 64, starBackground, WHITE);
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
