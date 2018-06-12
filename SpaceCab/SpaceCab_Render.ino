#include <Arduboy2.h>

void drawLevel()
{
  for(int y = 0; y < LEVEL_HEIGHT; y++)
  {
    for(int x = 0; x < LEVEL_WIDTH; x++)
    {
      arduboy.drawBitmap(x * TILE_SIZE, y * TILE_SIZE, tiles[level1Map[y][x]], TILE_SIZE, TILE_SIZE, WHITE);
      
    }
  }
}

void drawHUD()
{
  uint8_t digits[5];
  uint8_t digitsTime[2];
  arduboy.drawLine(0, 53, 128, 53, WHITE);
  arduboy.fillRect(0, 55, 128, 64, WHITE);
  Sprites::drawExternalMask(0, 55, SpaceCabHUD, SpaceCabHUDMask, 0, 0);
  arduboy.setCursor(2, 57);
  arduboy.print(F("$"));
  extractDigits(digits, currentScore);
  for(uint8_t i = 5; i > 0; --i)
  arduboy.print(digits[i - 1]);
  arduboy.setCursor(50, 57);
  extractDigits(digitsTime, gameTime);
  for(uint8_t i = 2; i > 0; --i)
  arduboy.print(digitsTime[i - 1]);
  //Sprites::drawExternalMask(64, 57, livesLeft, livesLeftMask, 0, 0);
}

void scrollingBackground()
{

  arduboy.drawBitmap(backdropx, backdropy, checkeredBG, 128, 64, WHITE);
  arduboy.drawBitmap(backdropx + 128, backdropy, checkeredBG, 128, 64, WHITE);

  if(arduboy.everyXFrames(2))
  { // when running at 60fps

    --backdropx;
    if (backdropx < -128)
    {
      backdropx = 0;
    }
  
  }
}

void playerDisplay()
{
  Sprites::drawExternalMask(player.getXDisplay(), player.getYDisplay(), SpaceTaxi, SpaceTaxiMask, playerFrame, playerFrame);
}

void customerDisplay()
{
  Sprites::drawExternalMask(customerx, customery, Customer, CustomerMask, customerFrame, customerFrame);
  if(arduboy.everyXFrames(15))
  {
  ++customerFrame;
  customerFrame %=2;
  }
}
