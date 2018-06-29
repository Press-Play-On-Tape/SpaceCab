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

void drawHUD()
{
  uint8_t digits[5];
  uint8_t digitsTime[2];
  //arduboy.drawLine(0, 53, 128, 53, WHITE);
  Sprites::drawExternalMask(0, 54, SpaceCabHUD, SpaceCabHUDMask, 0, 0);
  arduboy.setCursor(8, 57);
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
    
    // // Render arrows.

    // arrowCount++;
    // arrowCount = arrowCount % ARROW_FLASH;
    // if (arrowCount < (ARROW_FLASH / 2)) { 

    //   if (customer.x < player.x) {

    //     SQ15x16 dY = static_cast<SQ15x16>(customerYVal) - static_cast<SQ15x16>(player.getYDisplay());
    //     SQ15x16 dX = static_cast<SQ15x16>(customerXVal) - static_cast<SQ15x16>(player.getXDisplay());
        
    //     SQ15x16 grad = dY / dX;
    
    //     if (dX == 0.00) {

    //       if (dY > 0)             { Sprites::drawExternalMask(59, 47, ArrowD, ArrowD_Mask, 0, 0); }
    //       if (dY < 0)             { Sprites::drawExternalMask(59, 0, ArrowU, ArrowU_Mask, 0, 0); }

    //     }
    //     else {

    //       if (grad > 2.0)         { Sprites::drawExternalMask(59, 0, ArrowU, ArrowU_Mask, 0, 0); }
    //       else if (grad > 0.12)   { Sprites::drawExternalMask(0, 0, ArrowUL, ArrowUL_Mask, 0, 0); }
    //       else if (grad > -0.12)  { Sprites::drawExternalMask(0, 28, ArrowL, ArrowL_Mask, 0, 0); }
    //       else if (grad > -2.0)   { Sprites::drawExternalMask(0, 47, ArrowDL, ArrowDL_Mask, 0, 0); }
    //       else                    { Sprites::drawExternalMask(59, 47, ArrowD, ArrowD_Mask, 0, 0); }

    //     }

    //   } 
    //   else {

    //     SQ15x16 dY = static_cast<SQ15x16>(customerYVal) - static_cast<SQ15x16>(player.getYDisplay());
    //     SQ15x16 dX = static_cast<SQ15x16>(customerXVal) - static_cast<SQ15x16>(player.getXDisplay());
    //     SQ15x16 grad = dY / dX;

    //     if (dX == 0.00) {

    //       if (dY > 0)             { Sprites::drawExternalMask(59, 47, ArrowD, ArrowD_Mask, 0, 0); }
    //       if (dY < 0)             { Sprites::drawExternalMask(59, 0, ArrowU, ArrowU_Mask, 0, 0); }

    //     }
    //     else {

    //       if (grad > 2.0)         { Sprites::drawExternalMask(59, 47, ArrowD, ArrowD_Mask, 0, 0); }
    //       else if (grad > 0.12)   { Sprites::drawExternalMask(120, 47, ArrowDR, ArrowDR_Mask, 0, 0); }
    //       else if (grad > -0.12)  { Sprites::drawExternalMask(120, 28, ArrowR, ArrowR_Mask, 0, 0); }
    //       else if (grad > -2.0)   { Sprites::drawExternalMask(120, 0, ArrowUR, ArrowUR_Mask, 0, 0); }
    //       else                    { Sprites::drawExternalMask(59, 0, ArrowU, ArrowU_Mask, 0, 0); }

    //     }

    //   }

    // }


    // Render arrows.

    arrowCount++;
    arrowCount = arrowCount % ARROW_FLASH;
    if (arrowCount < (ARROW_FLASH / 2)) { 
Serial.print("Cust: ");
Serial.print((float)customer.x);
Serial.print(", Player: ");
Serial.print((float)player.x);
      SQ15x16 dY = static_cast<SQ15x16>(customerYVal) - static_cast<SQ15x16>(player.getYDisplay());
      SQ15x16 dX = static_cast<SQ15x16>(customerXVal) - static_cast<SQ15x16>(player.getXDisplay());
      SQ15x16 grad = dY / dX;
Serial.print(", dX: ");
Serial.print((float)dX);
Serial.print(", dY: ");
Serial.print((float)dY);
Serial.print(", Grad: ");
Serial.print((float)grad);

      if (customer.x < player.x) {
    
        if (absT(dX) <= 0.02) {

          if (dY > 0)             { Serial.println("1.1"); Sprites::drawExternalMask(59, 47, ArrowD, ArrowD_Mask, 0, 0); }
          if (dY < 0)             { Serial.println("1.2"); Sprites::drawExternalMask(59, 0, ArrowU, ArrowU_Mask, 0, 0); }

        }
        else {

          if (grad > 2.0)         { Serial.println("1.3"); Sprites::drawExternalMask(59, 0, ArrowU, ArrowU_Mask, 0, 0); }
          else if (grad > 0.12)   { Serial.println("1.4"); Sprites::drawExternalMask(0, 0, ArrowUL, ArrowUL_Mask, 0, 0); }
          else if (grad > -0.12)  { Serial.println("1.5"); Sprites::drawExternalMask(0, 28, ArrowL, ArrowL_Mask, 0, 0); }
          else if (grad > -2.0)   { Serial.println("1.6"); Sprites::drawExternalMask(0, 47, ArrowDL, ArrowDL_Mask, 0, 0); }
          else                    { Serial.println("1.7"); Sprites::drawExternalMask(59, 47, ArrowD, ArrowD_Mask, 0, 0); }

        }

      } 
      else {

        if (absT(dX) <= 0.02) {

          if (dY > 0)             { Serial.println("2.1"); Sprites::drawExternalMask(59, 47, ArrowD, ArrowD_Mask, 0, 0); }
          if (dY < 0)             { Serial.println("2.2"); Sprites::drawExternalMask(59, 0, ArrowU, ArrowU_Mask, 0, 0); }

        }
        else {

          if (grad > 2.0)         { Serial.println("2.3"); Sprites::drawExternalMask(59, 47, ArrowD, ArrowD_Mask, 0, 0); }
          else if (grad > 0.12)   { Serial.println("2.4"); Sprites::drawExternalMask(120, 47, ArrowDR, ArrowDR_Mask, 0, 0); }
          else if (grad > -0.12)  { Serial.println("2.5"); Sprites::drawExternalMask(120, 28, ArrowR, ArrowR_Mask, 0, 0); }
          else if (grad > -2.0)   { Serial.println("2.6"); Sprites::drawExternalMask(120, 0, ArrowUR, ArrowUR_Mask, 0, 0); }
          else                    { Serial.println("2.7"); Sprites::drawExternalMask(59, 0, ArrowU, ArrowU_Mask, 0, 0); }

        }

      }

    }

  }

}
