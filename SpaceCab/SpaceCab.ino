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

void updateTime()
{
  if(arduboy.everyXFrames(60))
    {
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

void checkCollision()
{
  // Rect playerRect = {player.getXDisplay(), player.getYDisplay(), 17, 8};
  // Rect customerRect = {customerx, customery, 7, 8};
  // Rect pad1Rect = {0, 39, 16, 8};
  // Rect pad2Rect = {17, 16, 24, 8};
  // Rect pad3Rect = {49, 32, 16, 8};
  // Rect pad4Rect = {97, 24, 24, 8};
  // if (arduboy.collide(playerRect, pad1Rect))
  // {
  //   player.y = player.y - 8;
  // }
  // if (arduboy.collide(playerRect, pad2Rect))
  // {
  //   player.y = player.y - 8;
  // }
  // if (arduboy.collide(playerRect, pad3Rect))
  // {
  //   player.y = player.y - 8;
  // }
  // if (arduboy.collide(playerRect, pad4Rect))
  // {
  //   player.y = player.y - 8;
  // }
  // if (arduboy.collide(playerRect, customerRect))
  // {
  //   currentScore = currentScore + 2;
  //   customerPosition();
  //   sound.tone(NOTE_E6, 50, NOTE_E3, 50, NOTE_E2, 50);
  // }

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


  // --  Moving up --------------------------------------------------------------------------------------------

  if (player.yDelta < 0) { 
    if (player.y > playerYDeltaVal) {
      player.y = player.y + playerYDeltaVal;
    }
    else {
      player.y = 0;
    }
  }


  // --  Moving down --------------------------------------------------------------------------------------------

  if (player.yDelta > 0) { 
    if (player.y < 47 - playerYDeltaVal) {
      player.y = player.y + playerYDeltaVal;
    }
    else {
      player.y = 47;
    }
  }


  // --  Moving left --------------------------------------------------------------------------------------------

  uint8_t playerXCentre = player.getXCentre();
  SQ15x16 playerXDeltaVal = player.getXDeltaVal();

  if (player.xDelta < 0) { 

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

  // --  Moving Right -------------------------------------------------------------------------------------------

  if (player.xDelta > 0) {

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

void inGame()
{
  drawHUD();
  drawLevel();
  playerDisplay();
  customerDisplay();
  checkCollision();
  updateTime();
  handleInput();
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

    level.number = 0;
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

