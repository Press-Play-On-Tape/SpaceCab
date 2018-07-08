#include "src/utils/Arduboy2Ext.h"


void handleInput(Player *player) {


  // You cannot move while loading a customer ..

  if (player->getPickingUpCustomer()) return;

  if (arduboy.justPressed(B_BUTTON)) {

      player->setLandingGearDown(!player->isLandingGearDown());

  }
  else {
      
    if (arduboy.everyXFrames(4)) {

      if (!player->hasJustLanded()) {

        if (arduboy.pressed(LEFT_BUTTON)) {
          player->decXDelta();
          player->setFrame(1);
        }

        else if (arduboy.pressed(RIGHT_BUTTON)) {
          player->incXDelta();
          player->setFrame(0);
        }

      }

      if (arduboy.pressed(A_BUTTON)) {

        switch (player->getFrame()) {

          case 0: 
            Sprites::drawExternalMask(player->getXDisplay(), player->getYDisplay() + 8, thrusterRight, thrusterRightMask, thrusterFrame, thrusterFrame);
            break;

          case 1:
            Sprites::drawExternalMask(player->getXDisplay(), player->getYDisplay() + 8, thrusterLeft, thrusterLeftMask, thrusterFrame, thrusterFrame);
            break;

        }


        // Alternate thruster frame every 5 frames ..

        if (arduboy.everyXFrames(5)) {
          ++thrusterFrame;
          thrusterFrame %=2;
        }

        player->decYDelta();
        sound.tone(NOTE_C1, 50, NOTE_C2, 50, NOTE_C1, 50);

      }

      if (arduboy.everyXFrames(8)) {

        // If the A Button is not being pressed, then we should start falling ..

        if (arduboy.notPressed(A_BUTTON)) {
          player->incYDelta(); 
        }


        // If the player is not pressing the left or right button then start slowing down ..

        if (arduboy.notPressed(LEFT_BUTTON) && arduboy.notPressed(RIGHT_BUTTON)) {

          if (player->getXDelta() > 0)  player->decXDelta();
          if (player->getXDelta() < 0)  player->incXDelta();

        }

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

void launchCustomer(Level *level, Customer *customer) {

  const uint8_t numberOfPositions = levelPositionsCount[level->getLevelNumber()];
  uint8_t customerStartingPos = random(numberOfPositions);
  uint8_t customerDestination = random(numberOfPositions);


  // Ensure new customer is not placed in the location the last customer was dropped at ..

  while (numberOfPositions != 1 && (customerStartingPos == customer->getStartingPosition() || customerStartingPos == customer->getDestinationPosition())) {
      customerStartingPos = random(numberOfPositions);
  }


  // Make sure the staryting point and destination are different!

  while (numberOfPositions != 1 && customerStartingPos == customerDestination) {
    customerDestination = random(numberOfPositions);
  }

  const uint8_t *levelStartingPosition = levelStartingPositions[level->getLevelNumber()];
  customer->setXTile(pgm_read_byte(&levelStartingPosition[customerStartingPos * 2]));
  customer->setYTile(pgm_read_byte(&levelStartingPosition[(customerStartingPos * 2) + 1]));
  customer->setStartingPosition(customerStartingPos);

  const uint8_t *levelEndingPosition = levelEndingPositions[level->getLevelNumber()];
  customer->setXDestinationTile(pgm_read_byte(&levelEndingPosition[customerDestination * 2]));
  customer->setYDestinationTile(pgm_read_byte(&levelEndingPosition[(customerDestination * 2) + 1]));
  customer->setDestinationPosition(customerDestination);

  customer->setFrame(0);
  customer->setStatus(CustomerStatus::Alive);
  customer->setFare(random(10, 20));

}


//------------------------------------------------------------------------------
//  Has the player collided with the customer ?
//------------------------------------------------------------------------------

void checkCollisionWithCustomer(Level *level, Player *player, Customer *customer) {

  if (player->isCarryingCustomer() || customer->getStatus() == CustomerStatus::Dead) return;

  Rect playerRect = { static_cast<int16_t>(player->getXDisplay()), static_cast<int16_t>(player->getYDisplay()), PLAYER_WIDTH, player->getHeight() };


  // Check customer collision only if they are on-screen ..

  int16_t customerXVal = customer->getX() + level->xOffset.getInteger();
  int16_t customerYVal = customer->getY() + level->yOffset.getInteger();

  if (customerXVal >= -CUSTOMER_WIDTH && customerXVal < WIDTH && customerYVal >= -CUSTOMER_HEIGHT && customerYVal < HEIGHT) {
  
    Rect customerRect = { customerXVal, customerYVal, CUSTOMER_WIDTH, CUSTOMER_HEIGHT };

    if (arduboy.collide(playerRect, customerRect)) {

      ouchCounter = OUCH_COUNTER_MAX;
      customer->setStatus(CustomerStatus::Dead);
      player->setPickingUpCustomer(false);

    }

  }

}



//------------------------------------------------------------------------------
//  Handle collisions with level elements ..
//------------------------------------------------------------------------------

void checkCollisionWithLevelElements(Level *level, Player *player, Customer *customer) {

  uint8_t tileAlreadyTested[TILE_COUNT];

  for (uint8_t i = 0; i < TILE_COUNT; i++)  tileAlreadyTested[i] = 0;

//  const uint8_t * levelMap = levelMaps[level->getLevelNumber()];
  uint16_t playerXPosition = player->getXDisplay() - level->getXOffsetDisplay();
  uint16_t playerYPosition = player->getYDisplay() - level->getYOffsetDisplay();

  uint8_t tileX1 = (playerXPosition / 8);
  uint8_t tileX2 = (playerXPosition / 8) + 1;
  uint8_t tileX3 = (playerXPosition / 8) + 2;
  uint8_t tileY1 = (playerYPosition / 8);
  uint8_t tileY2 = (playerYPosition / 8) + 1;

  uint8_t tile = level->getLevelData(tileX1, tileY1);// pgm_read_byte(&levelMap[(tileY1 * level->getWidthInTiles()) + tileX1]);
  if (tileAlreadyTested[tile] == 0) {
    checkCollisionWithLevelElements_TestElement(level, player, customer, tileX1, tileY1, tile);
    tileAlreadyTested[tile] = 1;
  }

  tile = level->getLevelData(tileX2, tileY1);// pgm_read_byte(&levelMap[(tileY1 * level->getWidthInTiles()) + tileX2]);
  if (tileAlreadyTested[tile] == 0) {
    checkCollisionWithLevelElements_TestElement(level, player, customer, tileX2, tileY1, tile);
    tileAlreadyTested[tile] = 1;
  }

  tile = level->getLevelData(tileX3, tileY1);// pgm_read_byte(&levelMap[(tileY1 * level->getWidthInTiles()) + tileX3]);
  if (tileAlreadyTested[tile] == 0) {
    checkCollisionWithLevelElements_TestElement(level, player, customer, tileX3, tileY1, tile);
    tileAlreadyTested[tile] = 1;
  }

  if (playerYPosition / 8 != 0) {

    tile = level->getLevelData(tileX1, tileY2);// pgm_read_byte(&levelMap[(tileY2 * level->getWidthInTiles()) + tileX1]);
    if (tileAlreadyTested[tile] == 0) {
      checkCollisionWithLevelElements_TestElement(level, player, customer, tileX1, tileY2, tile);
      tileAlreadyTested[tile] = 1;
    }

    tile = level->getLevelData(tileX2, tileY2);// pgm_read_byte(&levelMap[(tileY2 * level->getWidthInTiles()) + tileX2]);
    if (tileAlreadyTested[tile] == 0) {
      checkCollisionWithLevelElements_TestElement(level, player, customer, tileX2, tileY2, tile);
      tileAlreadyTested[tile] = 1;
    }

    tile = level->getLevelData(tileX3, tileY2);// pgm_read_byte(&levelMap[(tileY2 * level->getWidthInTiles()) + tileX3]);
    if (tileAlreadyTested[tile] == 0) {
      checkCollisionWithLevelElements_TestElement(level, player, customer, tileX3, tileY2, tile);
      tileAlreadyTested[tile] = 1;
    }

  } 

}

void checkCollisionWithLevelElements_TestElement(Level *level, Player *player, Customer *customer, uint8_t x, uint8_t y, uint8_t element) {

  switch (element) {

    case FUEL1:
      if (arduboy.getFrameCount(4) == 0) {
        Fuel *fuel = level->getFuel(x, y);
        if (fuel->getFuelLeft() > 0 && player->getFuel() < PLAYER_FUEL_MAX) {
          player->incFuel();
          fuel->decFuel();
        }
      }
      break;

    case SPIKU:
    case SPIKD:
      player->setStatus(PlayerStatus::OutOfFuel_Max);
      break;

    case SIGN1:
      if (player->isCarryingCustomer() && absT(customer->getXDestinationTile() - x) < 2 && customer->getYDestinationTile() == y) {
        player->setCarryingCustomer(false);
        player->setScore(player->getScore() + customer->getFare());
        launchCustomer(level, customer);
        dollarsCount = DOLLARS_COUNT_MAX;
      }
      break;
    
  }

  // Going down?

  if (!player->isLandingGearDown() && player->getYDelta() > 0) {

    if (isTileSolid(element)) {

      player->setStatus(PlayerStatus::OutOfFuel_Max);

    }

  }

}

void updateStatus(Player *player, Customer *customer) {


  // Burn fuel ..

  if (player->getStatus() == PlayerStatus::Active && arduboy.everyXFrames(15)) {

    player->decFuel();

    if (player->getFuel() == 0) {

      player->setStatus(PlayerStatus::OutOfFuel_Max);

    }

  }


  // Update player status ..

  switch (player->getStatus()) {

    case PlayerStatus::OutOfFuel_Min ... PlayerStatus::OutOfFuel_Max:
      player->decStatus();
      break;

    case PlayerStatus::OutOfFuel_End:
      player->setStatus(PlayerStatus::Inactive);
      player->decNumberOfLives();

      if (player->getNumberOfLives() > 0) {
        state = GameState::EndOfLevel;
      }
      else {
        state = GameState::GameOver;
      }
      
      break;

    default:  break;

  }


  // Update fare if carrying a passenger ..

  if (player->isCarryingCustomer()) {

    if (arduboy.everyXFrames(FARE_X_FRAMES)) {

      fareCount++;

      if (fareCount > FARE_COUNT) {
        fareCount = 0;
        customer->decFare();
      }

    }

  }

}


//------------------------------------------------------------------------------
//  Play the game! 
//------------------------------------------------------------------------------

void inGame(Level *level, Player *player, Customer *customer) {

  updateTime();

  flashingCounter++;
  flashingCounter = flashingCounter % FLASH_MAX;

  if (gotoCounter != 0)   gotoCounter--;
  
  if (ouchCounter != 0) { 

    ouchCounter--;
    if (ouchCounter == 0) {
      launchCustomer(level, customer);
    }

  }

  drawLevel(level);

  if (player->getStatus() == PlayerStatus::Active) {
  
    handleInput(player);
    checkCollisionWithCustomer(level, player, customer);
    checkCollisionWithLevelElements(level, player, customer);

  }

  playerDisplay(player);
  drawDollars(player);
  customerDisplay(level, player, customer);
  drawHUD(player, customer);
  drawGoto(level, customer);
  drawOuch(level, customer);

  if (state == GameState::EndOfLevel) {
    drawLevelStart();
  }
  
  updateStatus(player, customer);

}
