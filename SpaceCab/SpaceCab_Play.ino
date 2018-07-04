#include <Arduboy2.h>

void handleInput() {

  if (arduboy.everyXFrames(4)) {

    if (arduboy.pressed(LEFT_BUTTON)) {
      player.decXDelta();
      player.frame = 1;
    }

    else if (arduboy.pressed(RIGHT_BUTTON)) {
      player.incXDelta();
      player.frame = 0;
    }

    if (arduboy.pressed(A_BUTTON)) {

      switch (player.frame) {

        case 0: 
          Sprites::drawExternalMask(player.getXDisplay(), player.getYDisplay() + 8, thrusterRight, thrusterRightMask, thrusterFrame, thrusterFrame);
          break;

        case 1:
          Sprites::drawExternalMask(player.getXDisplay(), player.getYDisplay() + 8, thrusterLeft, thrusterLeftMask, thrusterFrame, thrusterFrame);
          break;

      }


      // Alternate thruster frame every 5 frames ..

      if (arduboy.everyXFrames(5)) {
        ++thrusterFrame;
        thrusterFrame %=2;
      }

      player.decYDelta();
      sound.tone(NOTE_C1, 50, NOTE_C2, 50, NOTE_C1, 50);

    }

    if (arduboy.everyXFrames(8)) {

      // If the A Button is not being pressed, then we should start falling ..

      if (arduboy.notPressed(A_BUTTON)) {
        player.incYDelta(); 
      }


      // If the player is not pressing the left or right button then start slowing down ..

      if (arduboy.notPressed(LEFT_BUTTON) && arduboy.notPressed(RIGHT_BUTTON)) {

        if (player.xDelta > 0)  player.decXDelta();
        if (player.xDelta < 0)  player.incXDelta();

      }

    }

  }

}


void updateTime() {

  if (arduboy.everyXFrames(60)) {
//    if (gameTime >= 1)    --gameTime;
    if (gameTime == 0 )   state = GameState::GameOver;
  }

}


//------------------------------------------------------------------------------
//  Launch a new customer.
//
//  Valid launching positions are derived from the level design.
//------------------------------------------------------------------------------

void launchCustomer() {

  const uint8_t numberOfPositions = levelPositionsCount[level.getLevelNumber()];
  uint8_t customerStartingPos = random(numberOfPositions);
  uint8_t customerDestination = random(numberOfPositions);


  // Ensure new customer is not placed in the location the last customer was dropped at ..

  while (numberOfPositions != 1 && (customerStartingPos == customer.getStartingPosition() || customerStartingPos == customer.getDestinationPosition())) {
      customerStartingPos = random(numberOfPositions);
  }


  // Make sure the staryting point and destination are different!

  while (numberOfPositions != 1 && customerStartingPos == customerDestination) {
    customerDestination = random(numberOfPositions);
  }

  const uint8_t *levelStartingPosition = levelStartingPositions[level.getLevelNumber()];
  customer.setXTile(pgm_read_byte(&levelStartingPosition[customerStartingPos * 2]));
  customer.setYTile(pgm_read_byte(&levelStartingPosition[(customerStartingPos * 2) + 1]));
  customer.setStartingPosition(customerStartingPos);

  const uint8_t *levelEndingPosition = levelEndingPositions[level.getLevelNumber()];
  customer.setXDestinationTile(pgm_read_byte(&levelEndingPosition[customerDestination * 2]));
  customer.setYDestinationTile(pgm_read_byte(&levelEndingPosition[(customerDestination * 2) + 1]));
  customer.setDestinationPosition(customerDestination);

  customer.setFrame(0);
  customer.setFare(random(10, 20));

}


//------------------------------------------------------------------------------
//  Has the player collided with the customer ?
//------------------------------------------------------------------------------

void checkCollisionWithCustomer() {

  if (player.carryingCustomer) return;

  Rect playerRect = { static_cast<int16_t>(player.getXDisplay()), static_cast<int16_t>(player.getYDisplay()), PLAYER_WIDTH, PLAYER_HEIGHT };


  // Check customer collision only if they are on-screen ..

  int16_t customerXVal = customer.getX() + level.xOffset.getInteger();
  int16_t customerYVal = customer.getY() + level.yOffset.getInteger();

  if (customerXVal >= -CUSTOMER_WIDTH && customerXVal < WIDTH && customerYVal >= -CUSTOMER_HEIGHT && customerYVal < HEIGHT) {
  
    Rect customerRect = { customerXVal, customerYVal, CUSTOMER_WIDTH, CUSTOMER_HEIGHT };

    if (arduboy.collide(playerRect, customerRect)) {
      player.carryingCustomer = true;
      sound.tone(NOTE_E6, 50, NOTE_E3, 50, NOTE_E2, 50);
      gotoCounter = GOTO_COUNTER_MAX;
    }

  }

}



//------------------------------------------------------------------------------
//  Handle collisions with level elements ..
//------------------------------------------------------------------------------

void checkCollisionWithLevelElements() {

  uint8_t tileAlreadyTested[TILE_COUNT];

  for (uint8_t i = 0; i < TILE_COUNT; i++)  tileAlreadyTested[i] = 0;

  const uint8_t * levelMap = levelMaps[level.getLevelNumber()];
  uint16_t playerXPosition = player.getXDisplay() - level.getXOffsetDisplay();
  uint16_t playerYPosition = player.getYDisplay() - level.getYOffsetDisplay();

  uint8_t tileX1 = (playerXPosition / 8);
  uint8_t tileX2 = (playerXPosition / 8) + 1;
  uint8_t tileX3 = (playerXPosition / 8) + 2;
  uint8_t tileY1 = (playerYPosition / 8);
  uint8_t tileY2 = (playerYPosition / 8) + 1;

  uint8_t tile = pgm_read_byte(&levelMap[(tileY1 * level.getWidthInTiles()) + tileX1]);
  if (tileAlreadyTested[tile] == 0) {
    checkCollisionWithLevelElements_TestElement(tileX1, tileY1, tile);
    tileAlreadyTested[tile] = 1;
  }

  tile = pgm_read_byte(&levelMap[(tileY1 * level.getWidthInTiles()) + tileX2]);
  if (tileAlreadyTested[tile] == 0) {
    checkCollisionWithLevelElements_TestElement(tileX2, tileY1, tile);
    tileAlreadyTested[tile] = 1;
  }

  tile = pgm_read_byte(&levelMap[(tileY1 * level.getWidthInTiles()) + tileX3]);
  if (tileAlreadyTested[tile] == 0) {
    checkCollisionWithLevelElements_TestElement(tileX3, tileY1, tile);
    tileAlreadyTested[tile] = 1;
  }

  if (playerYPosition / 8 != 0) {

    tile = pgm_read_byte(&levelMap[(tileY2 * level.getWidthInTiles()) + tileX1]);
    if (tileAlreadyTested[tile] == 0) {
      checkCollisionWithLevelElements_TestElement(tileX1, tileY2, tile);
      tileAlreadyTested[tile] = 1;
    }

    tile = pgm_read_byte(&levelMap[(tileY2 * level.getWidthInTiles()) + tileX2]);
    if (tileAlreadyTested[tile] == 0) {
      checkCollisionWithLevelElements_TestElement(tileX2, tileY2, tile);
      tileAlreadyTested[tile] = 1;
    }

    tile = pgm_read_byte(&levelMap[(tileY2 * level.getWidthInTiles()) + tileX3]);
    if (tileAlreadyTested[tile] == 0) {
      checkCollisionWithLevelElements_TestElement(tileX3, tileY2, tile);
      tileAlreadyTested[tile] = 1;
    }

  } 

}

void checkCollisionWithLevelElements_TestElement(uint8_t x, uint8_t y, uint8_t element) {

  switch (element) {

    case FUEL1:
      if (player.fuel < PLAYER_FUEL_MAX) player.fuel++;
      break;

    case SPIKU:
      player.status = PlayerStatus::OutOfFuel_Max;
      break;

    case SPIKD:
      player.status = PlayerStatus::OutOfFuel_Max;
      break;

    case SIGN1:
      if (player.carryingCustomer && absT(customer.getXDestinationTile() - x) < 2 && customer.getYDestinationTile() == y) {
        player.carryingCustomer = false;
        player.currentScore = player.currentScore + customer.getFare();
        launchCustomer();
        dollarsCount = DOLLARS_COUNT_MAX;
      }
      break;
    

  }

}

void updateStatus() {


  // Burn fuel ..

  if (player.status == PlayerStatus::Active && arduboy.everyXFrames(15)) {

    --player.fuel;

    if (player.fuel == 0) {

      player.status = PlayerStatus::OutOfFuel_Max;

    }

  }




  // Update player status ..

  switch (player.status) {

    case PlayerStatus::OutOfFuel_Min ... PlayerStatus::OutOfFuel_Max:
      player.status--;
      break;

    case PlayerStatus::OutOfFuel_End:
      player.status = PlayerStatus::Inactive;
      player.numberOfLives--;

      if (player.numberOfLives > 0) {
        state = GameState::EndOfLevel;
      }
      else {
        state = GameState::GameOver;
      }
      
      break;

    default:  break;

  }


  // Update fare if carrying a passenger ..

  if (player.carryingCustomer) {

    if (arduboy.everyXFrames(FARE_X_FRAMES)) {

      fareCount++;

      if (fareCount > FARE_COUNT) {
        fareCount = 0;
        if (customer.getFare() > 0) customer.setFare(customer.getFare() - 1);
      }

    }

  }

}


//------------------------------------------------------------------------------
//  Play the game! 
//------------------------------------------------------------------------------

void inGame() {

  updateTime();
  flashingCounter++;
  flashingCounter = flashingCounter % FLASH_MAX;
  if (gotoCounter != 0) gotoCounter--;

  if (player.status == PlayerStatus::Active) {
  
    handleInput();
    checkCollisionWithCustomer();
    checkCollisionWithLevelElements();

  }

  drawLevel();
  playerDisplay();
  drawDollars();
  customerDisplay();
  drawHUD();
  drawGoto();

  if (state == GameState::EndOfLevel) {
    drawLevelStart();
  }
  
  updateStatus();

}
