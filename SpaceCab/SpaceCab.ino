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

uint8_t thrusterFrame = 0;
uint8_t gameTime = 60;
uint16_t currentScore = 0;
uint8_t state = 0;
int16_t backdropx = 0;
int16_t backdropy = 0;

//------------------------------------------------------------------------------


void handleInput()
{
  if (arduboy.everyXFrames(4)) {
    if(arduboy.pressed(LEFT_BUTTON))
    {

      player.decXDelta();
      player.frame = 1;
    }
    if(arduboy.pressed(RIGHT_BUTTON))
    {
      player.incXDelta();
      player.frame = 0;
    }
    if(arduboy.pressed(A_BUTTON))
    {
      if(player.frame == 0)
      {
        Sprites::drawExternalMask(player.getXDisplay(), player.getYDisplay() + 8, thrusterRight, thrusterRightMask, thrusterFrame, thrusterFrame);
      }
      if(player.frame == 1)
      {
        Sprites::drawExternalMask(player.getXDisplay(), player.getYDisplay() + 8, thrusterLeft, thrusterLeftMask, thrusterFrame, thrusterFrame);
      }
      if(arduboy.everyXFrames(5))
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
    gameTime = (gameTime > 1) ? gameTime - 1 : state = 4;
  }

}

void customerPosition() {

  uint8_t numberOfStartingPositions = levelStartingPositionsCount[level.number];
  uint8_t customerNewPos = random(numberOfStartingPositions);

  const uint8_t *levelStartingPosition = levelStartingPositions[level.number];
  customer.x = pgm_read_byte(&levelStartingPosition[customerNewPos * 2]) * TILE_SIZE;
  customer.y = pgm_read_byte(&levelStartingPosition[(customerNewPos * 2) + 1]) * TILE_SIZE;

}

bool isTileSolid(uint8_t tileType)
{
    switch (tileType)
    {
      case BRICK:
      case PLAT1:
      case ROOF2:
        /*Serial.print(tileX);
        Serial.print(" ");
        Serial.print(tileY1);
        Serial.println(", brick or edge to left of Y1.");*/
        return true;
      default:
        return false;
    }
}

bool canMoveLeft()
{
  const uint8_t * levelMap = levelMaps[level.number];
  uint16_t playerXPosition = player.getXDisplay() - level.getXOffsetDisplay();
  uint16_t playerYPosition = player.getYDisplay() - level.getYOffsetDisplay();
 
  // We are not yet at the left hand edge of tile so movement is possible
  if (playerXPosition % TILE_SIZE != 0)
    return true;
	
  // Only test if we can move if we are already at the left hand side of a tile 
  uint8_t tileX = (playerXPosition / 8) - 1;
  uint8_t tileY1 = (playerYPosition / 8);

  // Retrieve the tile from the level defintion for x, y1
  uint8_t tile1 = pgm_read_byte(&levelMap[(tileY1 * LEVEL_WIDTH) + tileX]);
  if(isTileSolid(tile1))
    return false;

  // Are we are actually straddling two tiles vertically
  if (player.getYDisplay() % TILE_SIZE != 0)
  {
    uint8_t tileY2 = (playerYPosition / 8) + 1;
    uint8_t tile2 = pgm_read_byte(&levelMap[(tileY2 * LEVEL_WIDTH) + tileX]);
    if(isTileSolid(tile2))
      return false;
  }

  return true;
}


bool canMoveRight()
{
  const uint8_t * levelMap = levelMaps[level.number];
  uint16_t playerXPosition = player.getXDisplay() - level.getXOffsetDisplay() + PLAYER_WIDTH;
  uint16_t playerYPosition = player.getYDisplay() - level.getYOffsetDisplay();

  // We are not yet at the right hand edge of tile so movement is possible
  if (playerXPosition % TILE_SIZE != TILE_SIZE - 1)
	return true;
  
  // Only test if we can move if we are already at the right hand side of a tile
  uint8_t tileX = (playerXPosition / 8) + 1;
  uint8_t tileY1 = (playerYPosition / 8);

  // Retrieve the tile from the level defintion for x, y1
  uint8_t tile1 = pgm_read_byte(&levelMap[(tileY1 * LEVEL_WIDTH) + tileX]);
  if(isTileSolid(tile1))
    return false;

  // Are we are actually straddling two tiles vertically
  if (player.getYDisplay() % TILE_SIZE != 0)
   {
    uint8_t tileY2 = (playerYPosition / 8) + 1;
    uint8_t tile2 = pgm_read_byte(&levelMap[(tileY2 * LEVEL_WIDTH) + tileX]);
    if(isTileSolid(tile2))
      return false;
  }

  return true;
}


bool canMoveUp()
{
  const uint8_t * levelMap = levelMaps[level.number];
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
  uint8_t tile1 = pgm_read_byte(&levelMap[(tileY * LEVEL_WIDTH) + tileX1]);
  if(isTileSolid(tile1))
    return false;
	
  uint8_t tile2 = pgm_read_byte(&levelMap[(tileY * LEVEL_WIDTH) + tileX2]);
  if(isTileSolid(tile2))
    return false;
	
  uint8_t tile3 = pgm_read_byte(&levelMap[(tileY * LEVEL_WIDTH) + tileX3]);
  if(isTileSolid(tile3))
    return false;

  return true;
}


bool canMoveDown()
{
  const uint8_t * levelMap = levelMaps[level.number];
  uint16_t playerXPosition = player.getXDisplay() - level.getXOffsetDisplay();
  uint16_t playerYPosition = player.getYDisplay() - level.getYOffsetDisplay() + PLAYER_HEIGHT;

  // We are not yet at the bottom edge of tile so movement is possible
  if (playerYPosition % TILE_SIZE != 0)
	return true;
  
  // Only test if we can move if we are already at the right hand side of a tile
  uint8_t tileY = (playerYPosition / 8);
  uint8_t tileX1 = (playerXPosition / 8);
  uint8_t tileX2 = (playerXPosition / 8) + 1;
  uint8_t tileX3 = (playerXPosition / 8) + 2;

  // Retrieve the tile from the level defintion for x, y1
  uint8_t tile1 = pgm_read_byte(&levelMap[(tileY * LEVEL_WIDTH) + tileX1]);
  if(isTileSolid(tile1))
    return false;
	
  uint8_t tile2 = pgm_read_byte(&levelMap[(tileY * LEVEL_WIDTH) + tileX2]);
  if(isTileSolid(tile2))
    return false;
	
  uint8_t tile3 = pgm_read_byte(&levelMap[(tileY * LEVEL_WIDTH) + tileX3]);
  if(isTileSolid(tile3))
    return false;

  return true;
}


void checkCollision() {

  Rect playerRect = { player.getXDisplay(), player.getYDisplay(), 17, 8 };


  // Check customer collision only if they are on screen ..

  int16_t customerXVal = customer.x + level.xOffset.getInteger();

  if (customerXVal >= -CUSTOMER_WIDTH && customerXVal < 128) {
  
    Rect customerRect = { customerXVal, customer.y, CUSTOMER_WIDTH, CUSTOMER_HEIGHT };

    if (arduboy.collide(playerRect, customerRect)) {
      currentScore = currentScore + 2;
      customerPosition();
      sound.tone(NOTE_E6, 50, NOTE_E3, 50, NOTE_E2, 50);
    }

  }

}

void moveCab() {

  SQ15x16 playerYDeltaVal = player.getYDeltaVal();


Serial.print("X: ");
Serial.print(player.getXDisplay());
Serial.print(",Y: ");
Serial.println(player.getYDisplay());

  // --  Moving up --------------------------------------------------------------------------------------------

  if (player.yDelta < 0) { 

    if (canMoveUp()) {

      if (player.y > playerYDeltaVal) {
        player.y = player.y + playerYDeltaVal;
      }
      else {
        player.y = 0;
      }

    }

  }


  // --  Moving down --------------------------------------------------------------------------------------------

  if (player.yDelta > 0) { 

    if (canMoveDown()) {

      if (player.y + PLAYER_HEIGHT < 55 - playerYDeltaVal) {
        player.y = player.y + playerYDeltaVal;
      }
      else {
        player.y = 55 - PLAYER_HEIGHT;
      }

    }

  }


  // --  Moving left --------------------------------------------------------------------------------------------

  uint8_t playerXCentre = player.getXCentre();
  SQ15x16 playerXDeltaVal = player.getXDeltaVal();

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
        if (level.xOffset - playerXDeltaVal > -level.width + WIDTH) {
          level.xOffset = level.xOffset - playerXDeltaVal;
        }
        else {
          player.x = player.x + ((level.width - WIDTH) + level.xOffset) + playerXDeltaVal;
          level.xOffset = -level.width + WIDTH;
        }
      }
      else if (player.x > playerXCentre) {
        if (level.xOffset == -level.width + WIDTH) {
          if (player.x + playerXDeltaVal + PLAYER_WIDTH < WIDTH) {
            player.x = player.x + playerXDeltaVal;
          }
          else {
            player.x = WIDTH - PLAYER_WIDTH;
          }
        }
        else {
          if (player.x + playerXDeltaVal - PLAYER_WIDTH < (WIDTH * TILE_SIZE)) {
            player.x = player.x + playerXDeltaVal;
          }
          else {
            player.x = (WIDTH * TILE_SIZE) - PLAYER_WIDTH;          
          }
        }
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

  // initialize things here

}

void loop() {
  if (!(arduboy.nextFrame()))
    return;

  arduboy.pollButtons();
  arduboy.clear();

  switch (state)
  {

  case 0:
    vsBoot();
    player.x = 17;
    player.y = 47;
    level.number = 0;
    level.xOffset = 0;
    level.width = 16 * TILE_SIZE;
    break;

  case 1:
    level.width = 16 * TILE_SIZE;
    level.number = 0;
    titleScreen();
    break;

  case 2:
    player.x = player.getXCentre();
    player.y = 47;
    player.frame = 1;
    thrusterFrame = 0;
    customer.x = 73;
    customer.y = 47;
    customer.frame = 0;
    gameTime = 60;
    currentScore = 0;

    level.number = 1;
    level.xOffset = -32;
    level.width = LEVEL_WIDTH * TILE_SIZE;

    state = 3;
      
  case 3:
    inGame();
    break;

  case 4:
    gameoverScreen();
    break;

  }


  arduboy.display();
  moveCab();
}

