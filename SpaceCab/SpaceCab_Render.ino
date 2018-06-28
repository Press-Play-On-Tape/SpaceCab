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

void customerDisplay() {

  int16_t customerXVal = customer.x + level.xOffset.getInteger();
  int16_t customerYVal = customer.y + level.yOffset.getInteger();

  if (customerXVal >= -CUSTOMER_WIDTH && customerXVal < WIDTH && customerYVal >= -CUSTOMER_HEIGHT && customerYVal < 55) {

    Sprites::drawExternalMask(customerXVal, customerYVal, Customer_Img, Customer_Img_Mask, customer.frame, customer.frame);

    if (arduboy.everyXFrames(15)) {
      customer.incFrame();
    }

  }
  else { // Render arrows.

    if (customerXVal < -CUSTOMER_WIDTH && customerXVal) {

      SQ15x16 grad = static_cast<SQ15x16>(customerYVal) - static_cast<SQ15x16>(player.getYDisplay()) / static_cast<SQ15x16>(customerXVal) - static_cast<SQ15x16>(player.getXDisplay());
Serial.print((float)(static_cast<SQ15x16>(customerYVal) - static_cast<SQ15x16>(player.getYDisplay())));
Serial.print(" - ");
Serial.print((float)(static_cast<SQ15x16>(customerXVal) - static_cast<SQ15x16>(player.getXDisplay())));
Serial.print(" - ");
Serial.print((float)grad);
Serial.print(" - ");
      if (grad > 50) {
        Serial.println("UP");
      }
      else if (grad > 32) {
        Serial.println("UP LEFT");
      }
      else if (grad > 32) {
        Serial.println("LEFT");
      }
      else if (grad > -32) {
        Serial.println("DOWN LEFT");
      }
      else {
        Serial.println("DOWN");
      }

    } 
    else {

      SQ15x16 grad = static_cast<SQ15x16>(customerYVal) - static_cast<SQ15x16>(player.getYDisplay()) / static_cast<SQ15x16>(customerXVal) - static_cast<SQ15x16>(player.getXDisplay());
Serial.print((float)(static_cast<SQ15x16>(customerYVal) - static_cast<SQ15x16>(player.getYDisplay())));
Serial.print(" = ");
Serial.print((float)(static_cast<SQ15x16>(customerXVal) - static_cast<SQ15x16>(player.getXDisplay())));
Serial.print(" = ");
Serial.print((float)grad);
Serial.print(" = ");
      if (grad > 50) {
        Serial.println("UP");
      }
      else if (grad > 32) {
        Serial.println("UP RIGHT");
      }
      else if (grad > 32) {
        Serial.println("RIGHT");
      }
      else if (grad > -32) {
        Serial.println("DOWN RIGHT");
      }
      else {
        Serial.println("DOWN");
      }

    }

  }

}
