#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "Images.h"
#include "Levels.h"
#include "Level.h"
#include "Player.h"
#include "Utils.h"
#include "Constants.h"
#include "FixedPoints.h"
#include "FixedPointsCommon.h"

ArduboyTones sound(arduboy.audio.enabled);
Sprites sprite;


Player player;
Level level;


// Global Variables now --------------------------------------------------------



uint8_t thrusterFrame = 0;

uint8_t customerx = 73;
uint8_t customery = 47;
uint8_t customerFrame = 0;
uint8_t customerNewPos = 5;

uint8_t gameTime = 60;

uint16_t currentScore = 0;

uint8_t state = 2;

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

void customerPosition()
{
  customerNewPos = random(5);
  if(customerNewPos == 0)
  {
    customerx = 1;
    customery = 32;
  }
  if(customerNewPos == 1)
  {
    customerx = 20;
    customery = 8;
  }
  if(customerNewPos == 2)
  {
    customerx = 49;
    customery = 24;
  }
  if(customerNewPos == 3)
  {
    customerx = 98;
    customery = 16;
  }
  if(customerNewPos == 4)
  {
    customerx = 73;
    customery = 47;
  }
}

void checkCollision()
{
  Rect playerRect = {player.getXDisplay(), player.getYDisplay(), 17, 8};
  Rect customerRect = {customerx, customery, 7, 8};
  Rect pad1Rect = {0, 39, 16, 8};
  Rect pad2Rect = {17, 16, 24, 8};
  Rect pad3Rect = {49, 32, 16, 8};
  Rect pad4Rect = {97, 24, 24, 8};
  if (arduboy.collide(playerRect, pad1Rect))
  {
    player.y = player.y - 8;
  }
  if (arduboy.collide(playerRect, pad2Rect))
  {
    player.y = player.y - 8;
  }
  if (arduboy.collide(playerRect, pad3Rect))
  {
    player.y = player.y - 8;
  }
  if (arduboy.collide(playerRect, pad4Rect))
  {
    player.y = player.y - 8;
  }
  if (arduboy.collide(playerRect, customerRect))
  {
    currentScore = currentScore + 2;
    customerPosition();
    sound.tone(NOTE_E6, 50, NOTE_E3, 50, NOTE_E2, 50);
  }
}

void moveCab()
{
  // Serial.print("x: ");
  // Serial.print(player.x);
  // Serial.print(", xDelta: ");
  // Serial.print(player.xDelta);
  // Serial.print(", y: ");
  // Serial.print(player.y);
  // Serial.print(", yDelta: ");
  // Serial.println(player.yDelta);
  

  // X range 0 to 111 or 0 to 127 - 16
  // y range 0 to 47 or 0 to 63 - 16

  if (player.yDelta < 0) { 
    if (player.y > player.yDelta) {
      player.y = player.y + player.yDelta;
    }
    else {
      player.y = 0;
    }
  }
  if (player.yDelta > 0) { 
    if (player.y < 47 - player.yDelta) {
      player.y = player.y + player.yDelta;
    }
    else {
      player.y = 47;
    }
  }

  // Serial.print("px: ");
  // Serial.print((float)player.x);
  // Serial.print(", pxd: ");
  // Serial.print((float)player.xDelta);
  // Serial.print(", py: ");
  // Serial.print((float)player.y);
  // Serial.print(", lv: ");
  // Serial.print((float)level.xOffset);

























  if (player.xDelta < 0) { 

    if (level.xOffset < 0) {

      if (level.xOffset < player.getXDeltaVal()) {
        level.xOffset = level.xOffset - player.getXDeltaVal();
      }
      else {
        level.xOffset = 0;
      }

    }
    else {

      if (level.xOffset == 0) {
        if (player.x > player.getXDeltaVal()) {
          player.x = player.x + player.getXDeltaVal();
        }
        else {
          player.x = 0;
        }

      }


      // if (player.x > player.xDelta) {
      //   player.x = player.x + player.xDelta;
      // }
      // else {
      //   player.x = 0;
      // }

    }
    
  }
  if (player.xDelta > 0) {

    if (player.x < player.getXCentre()) {
      if (player.x + player.getXDeltaVal() < player.getXCentre()) {
        player.x = player.x + player.getXDeltaVal();
      }
      else {
        level.xOffset = player.getXDeltaVal() - player.getXCentre() - player.x;
        player.x = player.getXCentre();
      }
    }
    else {
      if (player.x == player.getXCentre()) {
        if (level.xOffset < 240) {
          Serial.print((float) level.xOffset);
          Serial.print(" + ");
          Serial.print((float) player.getXDeltaVal());
          Serial.print(" = ");
          
          level.xOffset = level.xOffset + player.getXDeltaVal();
          Serial.print((float) level.xOffset);
        }
      }
    }




    // if (level.xOffset < 0) {
    //   if 




    //   if (-level.xOffset > player.xDelta) {
    //     level.xOffset = level.xOffset + player.xDelta;
    //   }
    //   else {
    //     pleyer.x
    //     level.xOffset = 0;
    //   }

    // } 
    // if (player.x < (111 * 8) - player.xDelta) {
    //   player.x = player.x + player.xDelta;
    // }
    // else {
    //   player.x = (111 * 8);
    // }
  }









Serial.println("");






























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
    break;

  case 1:
    titleScreen();
    break;

  case 2:
    player.x = player.getXCentre();
    player.y = 47;
    player.frame = 1;
    thrusterFrame = 0;
    customerx = 73;
    customery = 47;
    customerFrame = 0;
    customerNewPos = 5;
    gameTime = 60;
    currentScore = 0;

    level.number = 0;
    level.xOffset = -32;

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

