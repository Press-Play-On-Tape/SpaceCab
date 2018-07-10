#include "src/utils/Arduboy2Ext.h"


void handleInput(Player *player) {


  // You cannot move while loading a customer ..

  if (player->getPickingUpCustomer()) return;

  if (arduboy.justPressed(B_BUTTON) && player->getFuel() != 0) {

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

      if (arduboy.pressed(A_BUTTON) && player->getFuel() > 0) {

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

        if (arduboy.notPressed(A_BUTTON) || player->getFuel() == 0) {
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

void launchCustomer(Level *level, Customer *customer, uint8_t defaultStartPosition, uint8_t defaultEndingPosition) {

  const uint8_t numberOfPositions = levelPositionsCount[level->getLevelNumber()];
  uint8_t customerStartingPos = (defaultStartPosition == RANDOM_START_POSITION ? random(numberOfPositions) : defaultStartPosition);
  uint8_t customerDestination = (defaultEndingPosition == RANDOM_END_POSITION ? random(numberOfPositions) : defaultEndingPosition);


  // Ensure new customer is not placed in the location the last customer was dropped at ..

  while (defaultStartPosition == RANDOM_START_POSITION && (customerStartingPos == customer->getStartingPosition() || customerStartingPos == customer->getDestinationPosition())) {
      customerStartingPos = random(numberOfPositions);
  }


  // Make sure the staryting point and destination are different!

  while (defaultStartPosition == RANDOM_START_POSITION && customerStartingPos == customerDestination) {
    customerDestination = random(numberOfPositions);
  }

  const uint8_t *levelStartingPosition = levelStartingPositions[level->getLevelNumber()];
  customer->setXTile(pgm_read_byte(&levelStartingPosition[customerStartingPos * 2]));
  customer->setYTile(pgm_read_byte(&levelStartingPosition[(customerStartingPos * 2) + 1]));
  customer->setStartingPosition(customerStartingPos);
  customer->setDestinationPosition(customerDestination);

  if (customerDestination != GO_TO_GATE) {

    const uint8_t *levelEndingPosition = levelEndingPositions[level->getLevelNumber()];
    customer->setXDestinationTile(pgm_read_byte(&levelEndingPosition[customerDestination * 2]));
    customer->setYDestinationTile(pgm_read_byte(&levelEndingPosition[(customerDestination * 2) + 1]));

  }

  customer->setFrame(0);
  customer->setStatus(CustomerStatus::Alive);
  customer->setFare(random(FARE_MIN, FARE_MAX));

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

//void checkCollisionWithLevelElements(Level *level, Player *player, Customer *customer) {
void checkCollisionWithLevelElements(Level *level, Player *player) {

  player->setFuelling(false);

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
    checkCollisionWithLevelElements_TestElement(level, player, tileX1, tileY1, tile);
    tileAlreadyTested[tile] = 1;
  }

  tile = level->getLevelData(tileX2, tileY1);// pgm_read_byte(&levelMap[(tileY1 * level->getWidthInTiles()) + tileX2]);
  if (tileAlreadyTested[tile] == 0) {
    checkCollisionWithLevelElements_TestElement(level, player, tileX2, tileY1, tile);
    tileAlreadyTested[tile] = 1;
  }

  tile = level->getLevelData(tileX3, tileY1);// pgm_read_byte(&levelMap[(tileY1 * level->getWidthInTiles()) + tileX3]);
  if (tileAlreadyTested[tile] == 0) {
    checkCollisionWithLevelElements_TestElement(level, player, tileX3, tileY1, tile);
    tileAlreadyTested[tile] = 1;
  }

  if (playerYPosition / 8 != 0) {

    tile = level->getLevelData(tileX1, tileY2);// pgm_read_byte(&levelMap[(tileY2 * level->getWidthInTiles()) + tileX1]);
    if (tileAlreadyTested[tile] == 0) {
      checkCollisionWithLevelElements_TestElement(level, player, tileX1, tileY2, tile);
      tileAlreadyTested[tile] = 1;
    }

    tile = level->getLevelData(tileX2, tileY2);// pgm_read_byte(&levelMap[(tileY2 * level->getWidthInTiles()) + tileX2]);
    if (tileAlreadyTested[tile] == 0) {
      checkCollisionWithLevelElements_TestElement(level, player, tileX2, tileY2, tile);
      tileAlreadyTested[tile] = 1;
    }

    tile = level->getLevelData(tileX3, tileY2);// pgm_read_byte(&levelMap[(tileY2 * level->getWidthInTiles()) + tileX3]);
    if (tileAlreadyTested[tile] == 0) {
      checkCollisionWithLevelElements_TestElement(level, player, tileX3, tileY2, tile);
      tileAlreadyTested[tile] = 1;
    }

  } 

}

//void checkCollisionWithLevelElements_TestElement(Level *level, Player *player, Customer *customer, uint8_t x, uint8_t y, uint8_t element) {
void checkCollisionWithLevelElements_TestElement(Level *level, Player *player, uint8_t x, uint8_t y, uint8_t element) {

  switch (element) {

    case FUEL1:
      if (arduboy.getFrameCount(4) == 0) {
        Fuel *fuel = level->getFuel(x, y);
        if (fuel->getFuelLeft() > 0 && player->getFuel() < PLAYER_FUEL_MAX) {
          player->incFuel();
          player->setFuelling(true);
          fuel->decFuel();
        }
      }
      break;

    case SPIKU:
    case SPIKD:
      player->setStatus(PlayerStatus::OutOfFuel_Max);
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

  if (!player->isFuelling() && player->getStatus() == PlayerStatus::Active && arduboy.everyXFrames(15)) {

    player->decFuel();

    if (player->getFuel() == 0) {

//       player->setStatus(PlayerStatus::OutOfFuel_Max);
       player->setLandingGearDown(false);

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


  // // Update fare if carrying a passenger ..

  // if (player->isCarryingCustomer()) {


    // Decrease fare ..

    if (arduboy.everyXFrames(FARE_X_FRAMES)) {

      fareCount++;

      if (fareCount > FARE_COUNT) {
        fareCount = 0;
        customer->decFare();
      }

    }

  // }

}


//------------------------------------------------------------------------------
//  Play the game! 
//------------------------------------------------------------------------------

void inGame(Font4x6 *font4x6, Level *level, Player *player, Customer *customer) {

  updateTime();

  flashingCounter++;
  flashingCounter = flashingCounter % FLASH_MAX;

  if (gotoCounter != 0)   gotoCounter--;
  
  if (ouchCounter != 0) { 

    ouchCounter--;
    if (ouchCounter == 0) {
      launchCustomer(level, customer, RANDOM_START_POSITION, RANDOM_END_POSITION);
    }

  }

  drawLevel(level);

  if (player->getStatus() == PlayerStatus::Active) {
  
    handleInput(player);
    checkCollisionWithCustomer(level, player, customer);
//    checkCollisionWithLevelElements(level, player, customer);
    checkCollisionWithLevelElements(level, player);

  }

  playerDisplay(player);
  drawDollars(player);
  customerDisplay(level, player, customer);
  drawHUD(player, customer);
  drawGoto(level, player, customer);
  drawOuch(level, customer);

  if (state == GameState::EndOfLevel) {
    drawLevelStart(font4x6, level);
  }
  
  updateStatus(player, customer);

}
