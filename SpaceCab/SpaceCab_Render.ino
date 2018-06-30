#include <Arduboy2.h>

void drawLevel() {

  const uint8_t *levelMap = levelMaps[level.getLevelNumber()];
  
  for (uint8_t y = 0; y < level.getHeightInTiles(); y++) {

    for (uint8_t x = 0; x < level.getWidthInTiles(); x++) {

      const int16_t tileX = (x * TILE_SIZE);
      const int16_t tileY = (y * TILE_SIZE);
      const int16_t bitmapX = tileX + level.getXOffsetDisplay();
      const int16_t bitmapY = tileY + level.getYOffsetDisplay();
      
      // Do we really need to render the tile?
      if (bitmapX < -8 || bitmapX >= WIDTH || bitmapY < -8 || bitmapY >= HEIGHT)
        continue;

      uint8_t tile = pgm_read_byte(&levelMap[(y * level.getWidthInTiles()) + x]);
      arduboy.drawBitmap(bitmapX, bitmapY, tiles[tile], TILE_SIZE, TILE_SIZE, WHITE);

    }

  }

}

#define HUD_OFFSET 10
#define HUD_WIDTH 66

void drawHUD() {


  uint8_t digits[5];
  uint8_t digitsTime[2];

  Sprites::drawExternalMask(10, 55, SpaceCabHUD, SpaceCabHUDMask, 0, 0);
  font4x6.setCursor(23, 57);
  extractDigits(digits, currentScore);
  for(uint8_t i = 5; i > 0; --i) 
    font4x6.print(digits[i - 1]);


  Sprites::drawExternalMask(92, 55, SpaceCabHUD_Time, SpaceCabHUD_Time_Mask, 0, 0);
  font4x6.setCursor(105, 57);
  extractDigits(digitsTime, gameTime);
  for(uint8_t i = 2; i > 0; --i)
    font4x6.print(digitsTime[i - 1]);
  //Sprites::drawExternalMask(64, 57, livesLeft, livesLeftMask, 0, 0);
}

void scrollingBackground()
{

  arduboy.drawBitmap(backdropx, backdropy, checkeredBG, 128, 64, WHITE);
  arduboy.drawBitmap(backdropx + 128, backdropy, checkeredBG, 128, 64, WHITE);

  if (arduboy.everyXFrames(2))
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


uint8_t arrowCount = 0;
void customerDisplay() {

  int16_t customerXVal = customer.x + level.xOffset.getInteger();
  int16_t customerYVal = customer.y + level.yOffset.getInteger();

  if (customerXVal >= -CUSTOMER_WIDTH && customerXVal < WIDTH && customerYVal >= -CUSTOMER_HEIGHT && customerYVal < HEIGHT) {

    Sprites::drawExternalMask(customerXVal, customerYVal, Customer_Img, Customer_Img_Mask, customer.frame, customer.frame);

    if (arduboy.everyXFrames(15)) {
      customer.incFrame();
    }

    arrowCount = 0;

  }
  else { 
    

    // Render arrows.

    arrowCount++;
    arrowCount = arrowCount % ARROW_FLASH;
    if (arrowCount < (ARROW_FLASH / 2)) { 

      SQ15x16 dX = static_cast<SQ15x16>(customer.x) - (player.x - level.xOffset);
      SQ15x16 dY = static_cast<SQ15x16>(customer.y) - (player.y - level.yOffset);
      SQ15x16 grad = dY / dX;

      if (customer.x < (player.x - level.xOffset)) {
    
        if (absT(dX) <= 0.02) {

          if (dY > 0)             { Sprites::drawExternalMask(59, 56, ArrowD, ArrowD_Mask, 0, 0); }
          if (dY < 0)             { Sprites::drawExternalMask(59, 0, ArrowU, ArrowU_Mask, 0, 0); }

        }
        else {

          if (grad > 2.0)         { Sprites::drawExternalMask(59, 0, ArrowU, ArrowU_Mask, 0, 0); }
          else if (grad > 0.14)   { Sprites::drawExternalMask(0, 0, ArrowUL, ArrowUL_Mask, 0, 0); }
          else if (grad > -0.14)  { Sprites::drawExternalMask(0, 28, ArrowL, ArrowL_Mask, 0, 0); }
          else if (grad > -2.0)   { Sprites::drawExternalMask(0, 56, ArrowDL, ArrowDL_Mask, 0, 0); }
          else                    { Sprites::drawExternalMask(59, 56, ArrowD, ArrowD_Mask, 0, 0); }

        }

      } 
      else {

        if (absT(dX) <= 0.02) {

          if (dY > 0)             { Sprites::drawExternalMask(59, 56, ArrowD, ArrowD_Mask, 0, 0); }
          if (dY < 0)             { Sprites::drawExternalMask(59, 0, ArrowU, ArrowU_Mask, 0, 0); }

        }
        else {

          if (grad > 2.0)         { Sprites::drawExternalMask(59, 56, ArrowD, ArrowD_Mask, 0, 0); }
          else if (grad > 0.14)   { Sprites::drawExternalMask(120, 56, ArrowDR, ArrowDR_Mask, 0, 0); }
          else if (grad > -0.14)  { Sprites::drawExternalMask(120, 28, ArrowR, ArrowR_Mask, 0, 0); }
          else if (grad > -2.0)   { Sprites::drawExternalMask(120, 0, ArrowUR, ArrowUR_Mask, 0, 0); }
          else                    { Sprites::drawExternalMask(59, 0, ArrowU, ArrowU_Mask, 0, 0); }

        }

      }

    }

  }

}
