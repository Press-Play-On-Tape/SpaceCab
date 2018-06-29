#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "Images.h"
#include "Levels.h"
#include "Level.h"
#include "Player.h"
#include "Customer.h"
#include "Utils.h"
#include "Constants.h"
#include "FixedPoints.h"
#include "FixedPointsCommon.h"

ArduboyTones sound(arduboy.audio.enabled);
Sprites sprite;

Player player;
Customer customer;
Level level;


// Global Variables now --------------------------------------------------------

GameState state = GameState::VSBoot;

uint8_t levelNumber = 0;
uint8_t thrusterFrame = 0;
uint8_t gameTime = 60;
uint16_t currentScore = 0;
int16_t backdropx = 0;
int16_t backdropy = 0;

//------------------------------------------------------------------------------


void handleInput()
{
  if (arduboy.everyXFrames(4)) {
    if (arduboy.pressed(LEFT_BUTTON))
    {

      player.decXDelta();
      player.frame = 1;
    }
    if (arduboy.pressed(RIGHT_BUTTON))
    {
      player.incXDelta();
      player.frame = 0;
    }
    if (arduboy.pressed(A_BUTTON))
    {
      if (player.frame == 0)
      {
        Sprites::drawExternalMask(player.getXDisplay(), player.getYDisplay() + 8, thrusterRight, thrusterRightMask, thrusterFrame, thrusterFrame);
      }
      if (player.frame == 1)
      {
        Sprites::drawExternalMask(player.getXDisplay(), player.getYDisplay() + 8, thrusterLeft, thrusterLeftMask, thrusterFrame, thrusterFrame);
      }
      if (arduboy.everyXFrames(5))
      {
        ++thrusterFrame;
        thrusterFrame %=2;
      }
      player.decYDelta(); // going up
      sound.tone(NOTE_C1, 50, NOTE_C2, 50, NOTE_C1, 50);
    }

    if (arduboy.everyXFrames(8))
    {
      if (arduboy.notPressed(A_BUTTON))
      {
        player.incYDelta(); // start falling.
      }

      if (arduboy.notPressed(LEFT_BUTTON) && arduboy.notPressed(RIGHT_BUTTON))
      { // slow down
        if (player.xDelta > 0)
        {
         player. decXDelta();
        }
        if (player.xDelta < 0)
        {
          player.incXDelta();
        }
      }
    }
  }
}

void updateTime() {

  if (arduboy.everyXFrames(60)) {
    if (gameTime >= 1)    --gameTime;
    if (gameTime == 0 )   state = GameState::GameOver;
  }

}

void launchCustomer() {

  uint8_t numberOfStartingPositions = levelStartingPositionsCount[level.getLevelNumber()];
  uint8_t customerNewPos = random(numberOfStartingPositions);

  const uint8_t *levelStartingPosition = levelStartingPositions[level.getLevelNumber()];
  customer.x = pgm_read_byte(&levelStartingPosition[customerNewPos * 2]) * TILE_SIZE;
  customer.y = pgm_read_byte(&levelStartingPosition[(customerNewPos * 2) + 1]) * TILE_SIZE;
  customer.frame = 0;

}

bool isTileSolid(uint8_t tileType) {

    switch (tileType) {
      case BRICK:
      case PLAT1:
      case ROOF2:
        return true;

      default:
        return false;
    }
}

bool canMoveLeft() {

  const uint8_t * levelMap = levelMaps[level.getLevelNumber()];
  uint16_t playerXPosition = player.getXDisplay() - level.getXOffsetDisplay();
  uint16_t playerYPosition = player.getYDisplay() - level.getYOffsetDisplay();
 
  // We are not yet at the left hand edge of tile so movement is possible
  if (playerXPosition % TILE_SIZE != 0) return true;
	
  // Only test if we can move if we are already at the left hand side of a tile 
  uint8_t tileX = (playerXPosition / 8) - 1;
  uint8_t tileY1 = (playerYPosition / 8);

  // Retrieve the tile from the level defintion for x, y1
  uint8_t tile1 = pgm_read_byte(&levelMap[(tileY1 * level.getWidthInTiles()) + tileX]);
  if (isTileSolid(tile1))
    return false;

  // Are we are actually straddling two tiles vertically
  if (player.getYDisplay() % TILE_SIZE != 0) {
    uint8_t tileY2 = (playerYPosition / 8) + 1;
    uint8_t tile2 = pgm_read_byte(&levelMap[(tileY2 * level.getWidthInTiles()) + tileX]);
    if (isTileSolid(tile2))
      return false;
  }

  return true;
}


bool canMoveRight() {

  const uint8_t * levelMap = levelMaps[level.getLevelNumber()];
  uint16_t playerXPosition = player.getXDisplay() - level.getXOffsetDisplay() + PLAYER_WIDTH;
  uint16_t playerYPosition = player.getYDisplay() - level.getYOffsetDisplay();

  // We are not yet at the right hand edge of tile so movement is possible
  if (playerXPosition % TILE_SIZE != TILE_SIZE - 1) 
	  return true;
  
  // Only test if we can move if we are already at the right hand side of a tile
  uint8_t tileX = (playerXPosition / 8) + 1;
  uint8_t tileY1 = (playerYPosition / 8);

  // Retrieve the tile from the level defintion for x, y1
  uint8_t tile1 = pgm_read_byte(&levelMap[(tileY1 * level.getWidthInTiles()) + tileX]);
  if (isTileSolid(tile1))
    return false;

  // Are we are actually straddling two tiles vertically
  if (player.getYDisplay() % TILE_SIZE != 0) {
    uint8_t tileY2 = (playerYPosition / 8) + 1;
    uint8_t tile2 = pgm_read_byte(&levelMap[(tileY2 * level.getWidthInTiles()) + tileX]);
    if (isTileSolid(tile2))
      return false;
  }

  return true;
}


bool canMoveUp() {

  const uint8_t * levelMap = levelMaps[level.getLevelNumber()];
  uint16_t playerXPosition = player.getXDisplay() - level.getXOffsetDisplay();
  uint16_t playerYPosition = player.getYDisplay() - level.getYOffsetDisplay();
 
  // We are not yet at the top edge of tile so movement is possible
  if (playerYPosition % TILE_SIZE != 0)
    return true;
	
  // Only test if we can move if we are already at the top side of a tile 
  uint8_t tileY = (playerYPosition / 8) - 1;
  uint8_t tileX1 = (playerXPosition / 8);
  uint8_t tileX2 = (playerXPosition / 8) + 1;
  uint8_t tileX3 = (playerXPosition / 8) + 2;

  // Retrieve the tile from the level defintion for x, y1
  uint8_t tile1 = pgm_read_byte(&levelMap[(tileY * level.getWidthInTiles()) + tileX1]);
  if (isTileSolid(tile1))
    return false;
	
  uint8_t tile2 = pgm_read_byte(&levelMap[(tileY * level.getWidthInTiles()) + tileX2]);
  if (isTileSolid(tile2))
    return false;
	
  uint8_t tile3 = pgm_read_byte(&levelMap[(tileY * level.getWidthInTiles()) + tileX3]);
  if (isTileSolid(tile3))
    return false;

  return true;
}


bool canMoveDown() {

  const uint8_t * levelMap = levelMaps[level.getLevelNumber()];
  uint16_t playerXPosition = player.getXDisplay() - level.getXOffsetDisplay();
  uint16_t playerYPosition = player.getYDisplay() - level.getYOffsetDisplay() + PLAYER_HEIGHT;
// Serial.print(player.getYDisplay());
// Serial.print(" ");
// Serial.print(level.getYOffsetDisplay());
// Serial.print(" ");
// Serial.println(playerYPosition);
  // We are not yet at the bottom edge of tile so movement is possible
  if (playerYPosition % TILE_SIZE != 0)
	  return true;
  
  // Only test if we can move if we are already at the right hand side of a tile
  uint8_t tileY = (playerYPosition / 8);
  uint8_t tileX1 = (playerXPosition / 8);
  uint8_t tileX2 = (playerXPosition / 8) + 1;
  uint8_t tileX3 = (playerXPosition / 8) + 2;

  // Retrieve the tile from the level defintion for x, y1
  uint8_t tile1 = pgm_read_byte(&levelMap[(tileY * level.getWidthInTiles()) + tileX1]);
  if (isTileSolid(tile1))
    return false;
	
  uint8_t tile2 = pgm_read_byte(&levelMap[(tileY * level.getWidthInTiles()) + tileX2]);
  if (isTileSolid(tile2))
    return false;
	
  uint8_t tile3 = pgm_read_byte(&levelMap[(tileY * level.getWidthInTiles()) + tileX3]);
  if (isTileSolid(tile3))
    return false;

  return true;
}


void checkCollision() {

  Rect playerRect = { player.getXDisplay(), player.getYDisplay(), PLAYER_WIDTH, PLAYER_HEIGHT };


  // Check customer collision only if they are on screen ..

  int16_t customerXVal = customer.x + level.xOffset.getInteger();
  int16_t customerYVal = customer.y + level.yOffset.getInteger();

  if (customerXVal >= -CUSTOMER_WIDTH && customerXVal < WIDTH && customerYVal >= -CUSTOMER_HEIGHT && customerYVal < HEIGHT) {
  
    Rect customerRect = { customerXVal, customerYVal, CUSTOMER_WIDTH, CUSTOMER_HEIGHT };

    if (arduboy.collide(playerRect, customerRect)) {
      currentScore = currentScore + 2;
      launchCustomer();
      sound.tone(NOTE_E6, 50, NOTE_E3, 50, NOTE_E2, 50);
    }

  }

}

void moveCab() {

  SQ15x16 playerYDeltaVal = player.getYDeltaVal();
  SQ15x16 playerXDeltaVal = player.getXDeltaVal();

  uint8_t playerYCentre = player.getYCentre();
  uint8_t playerXCentre = player.getXCentre();

// Serial.print("X: ");
// Serial.print(player.getXDisplay());
// Serial.print(",Y: ");
// Serial.println(player.getYDisplay());

  // --  Moving up --------------------------------------------------------------------------------------------

  if (player.yDelta < 0) { 

    if (canMoveUp()) {

      if (level.yOffset < 0) {

        if (player.y < playerYCentre) {
          if (level.yOffset < playerYDeltaVal) {
            level.yOffset = level.yOffset - playerYDeltaVal;
          }
          else {
            level.yOffset = 0;
          }
        }
        else if (player.y == playerYCentre) {
          if (level.yOffset < playerYDeltaVal) {
            level.yOffset = level.yOffset - playerYDeltaVal;
          }
          else {
            player.y = player.y + playerYDeltaVal - level.yOffset;
            level.yOffset = 0;
          }
        }
        else if (player.y > playerYCentre) {
          if (player.y + playerYDeltaVal > playerYCentre) {
            player.y = player.y + playerYDeltaVal;
          }
          else {
            level.yOffset = level.yOffset + playerYCentre - player.y - playerYDeltaVal;
            player.y = playerYCentre;
          }
        }

      }
      else {

        if (player.y > -playerYDeltaVal) {
          player.y = player.y + playerYDeltaVal;
        }
        else {
          player.y = 0;
        }

      }

    }
    
  }


  // --  Moving down --------------------------------------------------------------------------------------------

  if (player.yDelta > 0) { 
    
    if (canMoveDown()) {
      if (player.y < playerYCentre) {                         
        if (player.y + playerYDeltaVal < playerYCentre) {
          player.y = player.y + playerYDeltaVal;
        }
        else {
          level.yOffset = playerYCentre - player.y - playerYDeltaVal;
          player.y = playerYCentre;
        }
      }
      else if (player.y == playerYCentre) {                            
        if (level.yOffset - playerYDeltaVal > -level.getHeight() + HEIGHT) {
          level.yOffset = level.yOffset - playerYDeltaVal;
        }
        else {
          player.y = player.y + ((level.getHeight() - HEIGHT) + level.yOffset) + playerYDeltaVal;
          level.yOffset = -level.getHeight() + HEIGHT;
        }
      }
      else if (player.y > playerYCentre) {
        // Player is below the half way line ..     
//      if (level.yOffset == -level.getHeight() + HEIGHT) {
          // If the player can still move downwards on the screen then do it.      
          if (player.y + playerYDeltaVal + PLAYER_HEIGHT < HEIGHT) {
            player.y = player.y + playerYDeltaVal;
          }
          else {
            // Otherwise, cap the Y value at the maximum height ..
            player.y = HEIGHT - PLAYER_HEIGHT;
          }
//         }
//         else {
//           // If the player can still move downwards on the screen then do it.      
//           if (player.y + playerYDeltaVal - PLAYER_HEIGHT < HEIGHT) {
//             player.y = player.y + playerYDeltaVal;
//           }
//           else {
//             // Otherwise, cap the Y value at the maximum height ..
//             player.y = HEIGHT - PLAYER_HEIGHT;          
//           }
//         }
      }

    }

  }


  // --  Moving left --------------------------------------------------------------------------------------------

  if (player.xDelta < 0) { 

    if (canMoveLeft()) {

      if (level.xOffset < 0) {

        if (player.x < playerXCentre) {
          if (level.xOffset < playerXDeltaVal) {
            level.xOffset = level.xOffset - playerXDeltaVal;
          }
          else {
            level.xOffset = 0;
          }
        }
        else if (player.x == playerXCentre) {
          if (level.xOffset < playerXDeltaVal) {
            level.xOffset = level.xOffset - playerXDeltaVal;
          }
          else {
            player.x = player.x + playerXDeltaVal - level.xOffset;
            level.xOffset = 0;
          }
        }
        else if (player.x > playerXCentre) {
          if (player.x + playerXDeltaVal > playerXCentre) {
            player.x = player.x + playerXDeltaVal;
          }
          else {
            level.xOffset = level.xOffset + playerXCentre - player.x - playerXDeltaVal;
            player.x = playerXCentre;
          }
        }

      }
      else {

        if (player.x > -playerXDeltaVal) {
          player.x = player.x + playerXDeltaVal;
        }
        else {
          player.x = 0;
        }

      }

    }
    
  }


  // --  Moving Right -------------------------------------------------------------------------------------------

  if (player.xDelta > 0) {

    if (canMoveRight()) {

      if (player.x < playerXCentre) {
        if (player.x + playerXDeltaVal < playerXCentre) {
          player.x = player.x + playerXDeltaVal;
        }
        else {
          level.xOffset = playerXCentre - player.x - playerXDeltaVal;
          player.x = playerXCentre;
        }
      }
      else if (player.x == playerXCentre) {                            
        if (level.xOffset - playerXDeltaVal > -level.getWidth() + WIDTH) {
          level.xOffset = level.xOffset - playerXDeltaVal;
        }
        else {
          player.x = player.x + ((level.getWidth() - WIDTH) + level.xOffset) + playerXDeltaVal;
          level.xOffset = -level.getWidth() + WIDTH;
        }
      }
      else if (player.x > playerXCentre) {
//        if (level.xOffset == -level.getWidth() + WIDTH) {
          if (player.x + playerXDeltaVal + PLAYER_WIDTH < WIDTH) {
            player.x = player.x + playerXDeltaVal;
          }
          else {
            player.x = WIDTH - PLAYER_WIDTH;
          }
        // }
        // else {
        //   if (player.x + playerXDeltaVal - PLAYER_WIDTH < (WIDTH * TILE_SIZE)) {
        //     player.x = player.x + playerXDeltaVal;
        //   }
        //   else {
        //     player.x = (WIDTH * TILE_SIZE) - PLAYER_WIDTH;          
        //   }
        // }
      }

    }
  
  }

}

void inGame()
{
  updateTime();
  handleInput();
  checkCollision();
  drawLevel();
  drawHUD();
  playerDisplay();
  customerDisplay();
}

//------------------------------------------------------------------------------

void setup() {
  
  arduboy.boot();
  arduboy.display();
  arduboy.flashlight();
  arduboy.systemButtons();
  arduboy.audio.begin();
  arduboy.clear();
  arduboy.setFrameRate(60);

}

void loop() {
  if (!(arduboy.nextFrame()))
    return;

  arduboy.pollButtons();
  arduboy.clear();

  switch (state)
  {

  case GameState::VSBoot:
    vsBoot();
    break;

  case GameState::SplashScreen_Init:
    initLevel(0, &player, &level);
    state = GameState::SplashScreen;
    // break;  -- Fall through intentional.

  case GameState::SplashScreen:
    titleScreen();
    break;

  case GameState::PlayGame_Init:
    thrusterFrame = 0;
    gameTime = 60;
    currentScore = 0;
    levelNumber = 1;

    initLevel(levelNumber, &player, &level);
    launchCustomer();

    state = GameState::PlayGame;
    // break;  -- Fall through intentional.
      
  case GameState::PlayGame:
    inGame();
    break;

  case GameState::GameOver:
    gameoverScreen();
    break;

  }

  arduboy.display();
  moveCab();

}

