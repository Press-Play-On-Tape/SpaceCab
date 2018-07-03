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
  uint8_t digitsFare[2];
  uint8_t digitsFuel[3];
  uint8_t digitsLives[1];

  Sprites::drawOverwrite(0, 56, SpaceCabHUD, 0);
  font4x6.setCursor(13, 57);
  extractDigits(digits, player.currentScore);
  for(uint8_t i = 5; i > 0; --i) 
  font4x6.print(digits[i - 1]);

  font4x6.setCursor(56, 57);
  extractDigits(digitsFuel, player.fuel);
  for(uint8_t i = 3; i > 0; --i) 
  font4x6.print(digitsFuel[i - 1]);

  font4x6.setCursor(92, 57);
  extractDigits(digitsLives, player.numberOfLives);
  for(uint8_t i = 1; i > 0; --i) 
  font4x6.print(digitsLives[i - 1]);

  font4x6.setCursor(112, 57);
  extractDigits(digitsFare, customer.getFare());
  for(uint8_t i = 2; i > 0; --i)
  font4x6.print(digitsFare[i - 1]);

Serial.print(customer.getStartingPosition());
Serial.print(", Dest : ");
Serial.print(customer.getDestinationPosition());
Serial.print(", Carrying : ");
Serial.println( (player.carryingCustomer ? "Y" : "N") );
}

void scrollingBackground(bool scrollLeft) {

  uint8_t xCount = 0;

  arduboy.drawFastHLine(0, 0, WIDTH, WHITE);

  for (int16_t x = backdropx; x < 128; x = x + 8) {

    for (uint8_t y = 0; y < 7; ++y) {

      if ((xCount % 2 == 0 && y % 2 == 0) || (xCount % 2 == 1 && y % 2 == 1)) {
        Sprites::drawOverwrite(x, 4 + (y * 8), checkeredBG_White, 0);
      }

    }

    ++xCount;

  }

  arduboy.drawFastHLine(0, HEIGHT - 1, WIDTH, WHITE);

  if (arduboy.everyXFrames(2)) { // when running at 60fps

    if (scrollLeft) {
      --backdropx;
      if (backdropx <= -WIDTH) {
        backdropx = 0;
      }
    }
    else {
      ++backdropx;
      if (backdropx >= 0) {
        backdropx = -WIDTH;
      }
    }
  
  }

}

void playerDisplay() {

  uint8_t const *imageName = nullptr;
  uint8_t const *maskName = nullptr;
  int8_t xOffset = 0;
  int8_t yOffset = 0;

  switch (player.status) {

    case PlayerStatus::OutOfFuel_Img1_Start ... PlayerStatus::OutOfFuel_Img1_End:
      imageName = SpaceTaxi_OutOfFuel_1;
      maskName = SpaceTaxi_OutOfFuel_1_Mask;
      xOffset = -5;
      yOffset = -5;
      break;

    case PlayerStatus::OutOfFuel_Img2_Start ... PlayerStatus::OutOfFuel_Img2_End:
      imageName = SpaceTaxi_OutOfFuel_2;
      maskName = SpaceTaxi_OutOfFuel_2_Mask;
      xOffset = -5;
      yOffset = -5;
      break;

    case PlayerStatus::OutOfFuel_Img3_Start ... PlayerStatus::OutOfFuel_Img3_End:
      imageName = SpaceTaxi_OutOfFuel_3;
      maskName = SpaceTaxi_OutOfFuel_3_Mask;
      xOffset = -5;
      yOffset = -5;
      break;

    case PlayerStatus::OutOfFuel_Img4_Start ... PlayerStatus::OutOfFuel_Img4_End:
      imageName = SpaceTaxi_OutOfFuel_4;
      maskName = SpaceTaxi_OutOfFuel_4_Mask;
      xOffset = -5;
      yOffset = -5;
      break;

    case PlayerStatus::Active:
      imageName = SpaceTaxi;
      maskName = SpaceTaxiMask;
      break;

    default: break;

  }

  if (imageName != nullptr) {
    Sprites::drawExternalMask(player.getXDisplay() + xOffset, player.getYDisplay() + yOffset, imageName, maskName, player.frame, player.frame);
  }

}


uint8_t arrowCount = 0;
void customerDisplay() {

  int16_t customerXVal = customer.getX() + level.xOffset.getInteger();
  int16_t customerYVal = customer.getY() + level.yOffset.getInteger();

  if (!player.carryingCustomer && customerXVal >= -CUSTOMER_WIDTH && customerXVal < WIDTH && customerYVal >= -CUSTOMER_HEIGHT && customerYVal < HEIGHT) {

    Sprites::drawExternalMask(customerXVal, customerYVal, Customer_Img, Customer_Img_Mask, customer.getFrame(), customer.getFrame());

    if (arduboy.everyXFrames(15)) {
      customer.incFrame();
    }

    arrowCount = 0;

  }
  else if (state == GameState::PlayGame)  { 

#ifdef ARROWS_FP

    uint8_t const *imageName = nullptr;
    uint8_t const *maskName = nullptr;
    uint8_t xPos = 0;
    uint8_t yPos = 0;

    uint16_t customerX = 0;
    uint16_t customerY = 0;

    //uint8_t const *images[] = { ArrowU, ArrowUR, ArrowR, ArrowDR, ArrowD, ArrowDL, ArrowL, ArrowUL };
    //uint8_t const *masks[] = { ArrowU_Mask, ArrowUR_Mask, ArrowR_Mask, ArrowDR_Mask, ArrowD_Mask, ArrowDL_Mask, ArrowL_Mask, ArrowUL_Mask };

    // Render arrows.

    arrowCount++;
    arrowCount = arrowCount % ARROW_FLASH;
    if (arrowCount < (ARROW_FLASH / 2)) { 

      if (!player.carryingCustomer) {

        customerX = customer.getX();
        customerY = customer.getY();

      }
      else {

        customerX = customer.getXDestinationTile() * TILE_SIZE;
        customerY = customer.getYDestinationTile() * TILE_SIZE;

      }

      SQ15x16 dX = static_cast<SQ15x16>(customerX) - (player.x - level.xOffset);
      SQ15x16 dY = static_cast<SQ15x16>(customerY) - (player.y - level.yOffset);
      SQ15x16 grad = dY / dX;

      if (customerX < (player.x - level.xOffset)) {
    
        if (absT(dX) <= 0.02) {

          if (dY > 0)             { imageName = ArrowD;   maskName = ArrowD_Mask;   xPos = 59;  yPos = 56; }
          if (dY < 0)             { imageName = ArrowU;   maskName = ArrowU_Mask;   xPos = 59;  yPos = 0; }

        }
        else {

          if (grad > 2.0)         { imageName = ArrowU;   maskName = ArrowU_Mask;   xPos = 59;  yPos = 0; }
          else if (grad > 0.14)   { imageName = ArrowUL;  maskName = ArrowUL_Mask;  xPos = 0;   yPos = 0; }
          else if (grad > -0.14)  { imageName = ArrowL;   maskName = ArrowL_Mask;   xPos = 0;   yPos = 28; }
          else if (grad > -2.0)   { imageName = ArrowDL;  maskName = ArrowDL_Mask;  xPos = 0;   yPos = 56; }
          else                    { imageName = ArrowD;   maskName = ArrowD_Mask;   xPos = 59;  yPos = 56; }

        }

      } 
      else {

        if (absT(dX) <= 0.02) {

          if (dY > 0)             { imageName = ArrowD;   maskName = ArrowD_Mask;   xPos = 59;  yPos = 56; }
          if (dY < 0)             { imageName = ArrowU;   maskName = ArrowU_Mask;   xPos = 59;  yPos = 0; }

        }
        else {

          if (grad > 2.0)         { imageName = ArrowD;   maskName = ArrowD_Mask;   xPos = 59;  yPos = 56; }
          else if (grad > 0.14)   { imageName = ArrowDR;  maskName = ArrowDR_Mask;  xPos = 120; yPos = 56; }
          else if (grad > -0.14)  { imageName = ArrowR;   maskName = ArrowR_Mask;   xPos = 120; yPos = 28; }
          else if (grad > -2.0)   { imageName = ArrowUR;  maskName = ArrowUR_Mask;  xPos = 120; yPos = 0; }
          else                    { imageName = ArrowU;   maskName = ArrowU_Mask;   xPos = 59;  yPos = 0; }

        }

      }

      if (imageName != nullptr) {

        Sprites::drawExternalMask(xPos, yPos, imageName, maskName, 0, 0);

      }

/* Adds 98 bytes..

    uint8_t idx = 0;

    uint16_t customerX = 0;
    uint16_t customerY = 0;

    uint8_t const *images[] = { ArrowU, ArrowUR, ArrowR, ArrowDR, ArrowD, ArrowDL, ArrowL, ArrowUL };
    uint8_t const *masks[] = { ArrowU_Mask, ArrowUR_Mask, ArrowR_Mask, ArrowDR_Mask, ArrowD_Mask, ArrowDL_Mask, ArrowL_Mask, ArrowUL_Mask };
    uint8_t const xPos[] = { 59, 120, 120, 120, 59, 0, 0, 0 };
    uint8_t const yPos[] = { 0, 0, 28, 56, 56, 56, 28, 0 };
    
    // Render arrows.

    arrowCount++;
    arrowCount = arrowCount % ARROW_FLASH;
    if (arrowCount < (ARROW_FLASH / 2)) { 

      if (!player.carryingCustomer) {

        customerX = customer.getX();
        customerY = customer.getY();

      }
      else {

        customerX = customer.getXDestinationTile() * TILE_SIZE;
        customerY = customer.getYDestinationTile() * TILE_SIZE;

      }

      SQ15x16 dX = static_cast<SQ15x16>(customerX) - (player.x - level.xOffset);
      SQ15x16 dY = static_cast<SQ15x16>(customerY) - (player.y - level.yOffset);
      SQ15x16 grad = dY / dX;

      if (customerX < (player.x - level.xOffset)) {
    
        if (absT(dX) <= 0.02) {

          if (dY > 0)             { idx = 4; }
          if (dY < 0)             { idx = 0; }

        }
        else {

          if (grad > 2.0)         { idx = 0; }
          else if (grad > 0.14)   { idx = 7; }
          else if (grad > -0.14)  { idx = 6; }
          else if (grad > -2.0)   { idx = 5; }
          else                    { idx = 4; }

        }

      } 
      else {

        if (absT(dX) <= 0.02) {

          if (dY > 0)             { idx = 4; }
          if (dY < 0)             { idx = 0; }

        }
        else {

          if (grad > 2.0)         { idx = 4; }
          else if (grad > 0.14)   { idx = 3; }
          else if (grad > -0.14)  { idx = 2; }
          else if (grad > -2.0)   { idx = 1; }
          else                    { idx = 0; }

        }

      }

      Sprites::drawExternalMask(xPos[idx], yPos[idx], images[idx], masks[idx], 0, 0);
      */

    }
#endif
#ifndef ARROWS_FP

    uint16_t customerX = 0;
    uint16_t customerY = 0;
    uint8_t arrowX = 0;
    uint8_t arrowY = 0;
    uint8_t playerX = player.getXDisplay();
    uint8_t playerY = player.getYDisplay();

    Direction direction = Direction::Up;

    // Render arrows.

    arrowCount++;
    arrowCount = arrowCount % ARROW_FLASH;

    if (arrowCount < (ARROW_FLASH / 2)) { 

      if (!player.carryingCustomer) {

        customerX = customer.getX();
        customerY = customer.getY();

      }
      else {

        customerX = customer.getXDestinationTile() * TILE_SIZE;
        customerY = customer.getYDestinationTile() * TILE_SIZE;

      }


      // If the customer location is on screen then do not render ..
      {
        int16_t customerXDisplay = customerX + level.getXOffsetDisplay();
        int16_t customerYDisplay = customerY + level.getYOffsetDisplay();

        if (customerXDisplay >= -CUSTOMER_WIDTH && customerXDisplay < WIDTH && customerYDisplay >= -CUSTOMER_HEIGHT && customerYDisplay < HEIGHT) {
          return;
        } 

      }

      int16_t dX = customerX - (player.x - level.xOffset).getInteger();
      int16_t dY = customerY - (player.y - level.yOffset).getInteger();

      if (dX < -playerX) {

        if (dY < -playerY)                            { direction = Direction::UpLeft; arrowX = 0; arrowY = 0; }
        if (dY >= -playerY && dY < -playerY + 64)     { direction = Direction::Left; arrowX = 0; arrowY = playerY + dY - 4; }
        if (dY >= -playerY + 64)                      { direction = Direction::DownLeft; arrowX = 0; arrowY = 56; }

      }

      if (dX >= -playerX && dX < -playerX + WIDTH) {

        if (dY < 0)                                   { direction = Direction::Up; arrowX = playerX + dX; arrowY = 0; }
        if (dY > 0)                                   { direction = Direction::Down; arrowX = playerX + dX; arrowY = 56; }

      }

      if (dX >= -playerX + WIDTH) {

        if (dY < -playerY)                            { direction = Direction::UpRight; arrowX = 120; arrowY = 0; }
        if (dY >= -playerY && dY < -playerY + 64)     { direction = Direction::Right; arrowX = 120; arrowY = playerY + dY - 4; }
        if (dY >= -playerY + 64)                      { direction = Direction::DownRight; arrowX = 120; arrowY = 56; }

      }

      Sprites::drawExternalMask(arrowX, arrowY, ArrowImgs, ArrowMasks, static_cast<uint8_t>(direction), static_cast<uint8_t>(direction));

    }
#endif

  }

}

void drawLevelStart() {

  arduboy.fillRect(18, 24, 67, 20, BLACK);
  arduboy.drawFastHLine(19, 25, 92, WHITE);
  arduboy.drawFastHLine(19, 38, 92, WHITE);
  arduboy.drawFastHLine(19, 39, 92, BLACK);


  font4x6.setCursor(22, 28);
  font4x6.print(F("Level "));
  font4x6.print(levelNumber);
  font4x6.print(F(" GOOD LUCK! "));

  if (arduboy.justPressed(A_BUTTON)) { 
    
    state = GameState::PlayGame_InitLevel; 
    
  }

}

void drawDollars() {

  if (dollarsCount > 0) {

    uint8_t idx = (DOLLARS_COUNT_MAX - dollarsCount) / DOLLARS_COUNT_MULT;

    Sprites::drawExternalMask(player.getXDisplay() - 5, player.getYDisplay() - 10, dollars, dollars_Mask, idx, idx);
    dollarsCount--;
  
  }

}
