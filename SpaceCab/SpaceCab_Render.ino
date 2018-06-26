#include <Arduboy2.h>

void drawLevel() {

  const uint8_t *levelMap = levelMaps[level.number];

  for (int y = 0; y < LEVEL_HEIGHT; y++) {

    for (int x = 0; x < LEVEL_WIDTH; x++) {

      // Do we really need to render the tile?

      if (((x * TILE_SIZE) + level.getXOffsetDisplay()) > -8 && ((x * TILE_SIZE) + level.getXOffsetDisplay()) < 128) {

        uint8_t tile = pgm_read_byte(&levelMap[(y * LEVEL_WIDTH) + x]);
        arduboy.drawBitmap(((x * TILE_SIZE) + level.getXOffsetDisplay()), y * TILE_SIZE, tiles[tile], TILE_SIZE, TILE_SIZE, WHITE);

      }      

    }

  }

}

void drawHUD()
{
  uint8_t digits[5];
  uint8_t digitsTime[2];
  arduboy.drawLine(0, 53, 128, 53, WHITE);
  arduboy.drawLine(0, 54, 128, 54, BLACK);
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

void playerDisplay() {
  Sprites::drawExternalMask(player.getXDisplay(), player.getYDisplay(), SpaceTaxi, SpaceTaxiMask, player.frame, player.frame);
}

void customerDisplay() {

  int16_t customerXVal = customer.x + level.xOffset.getInteger();

  if (customerXVal >= -CUSTOMER_WIDTH && customerXVal < 128) {

    Sprites::drawExternalMask(customerXVal, customer.y, Customer_Img, Customer_Img_Mask, customer.frame, customer.frame);

    if(arduboy.everyXFrames(15)) {
      customer.incFrame();
    }

  }

}
