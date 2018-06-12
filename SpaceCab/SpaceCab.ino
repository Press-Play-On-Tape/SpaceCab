#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "Images.h"
#include "Levels.h"
#include "Utils.h"
 
ArduboyTones sound(arduboy.audio.enabled);
Sprites sprite;

struct Player {

  int16_t x;
  int16_t y;

  int16_t xDelta = 0;
  int16_t yDelta = 0;

  uint8_t getXDisplay() { return x / 8; }
  uint8_t getYDisplay() { return y / 8; }

};

Player player;

// Global Variables now --------------------------------------------------------

uint8_t playerFrame = 0;

uint8_t thrusterFrame = 0;

uint8_t customerx = 73;
uint8_t customery = 47;
uint8_t customerFrame = 0;
uint8_t customerNewPos = 5;

uint8_t gameTime = 60;

uint16_t currentScore = 0;

uint8_t state = 0;

int16_t backdropx = 0;
int16_t backdropy = 0;

//------------------------------------------------------------------------------

void incXDelta()
{

  switch (player.xDelta)
  {

    case -8 ... -2:
      player.xDelta = player.xDelta / 2;
      break;
    
    case -1:
      player.xDelta = 0;
      break;
    
    case 0:
      player.xDelta = 1;
      break;

    case 1 ... 4:
      player.xDelta = player.xDelta * 2;
      break;

  }

}

void decXDelta()
{

  switch (player.xDelta)
  {

    case -4 ... -1:
      player.xDelta = player.xDelta * 2;
      break;

    case 0:
      player.xDelta = -1;
      break;

    case 1:
      player.xDelta = 0;
      break;

    case 2 ... 8:
      player.xDelta = player.xDelta / 2;
      break;
    
  }

}

void incYDelta()
{

  switch (player.yDelta)
  {

    case -8 ... -2:
      player.yDelta = player.yDelta / 2;
      break;
    
    case -1:
      player.yDelta = 0;
      break;
    
    case 0:
      player.yDelta = 1;
      break;

    case 1 ... 4:
      player.yDelta = player.yDelta * 2;
      break;

  }

}

void decYDelta()
{

  switch (player.yDelta)
  {

    case -4 ... -1:
      player.yDelta = player.yDelta * 2;
      break;

    case 0:
      player.yDelta = -1;
      break;

    case 1:
      player.yDelta = 0;
      break;

    case 2 ... 8:
      player.yDelta = player.yDelta / 2;
      break;
    
  }

}

void handleInput()
{
  if (arduboy.everyXFrames(4)) {
    if(arduboy.pressed(LEFT_BUTTON))
    {
      decXDelta();
      playerFrame = 1;
    }
    if(arduboy.pressed(RIGHT_BUTTON))
    {
      incXDelta();
      playerFrame = 0;
    }
    if(arduboy.pressed(A_BUTTON))
    {
      if(playerFrame == 0)
      {
        Sprites::drawExternalMask(player.getXDisplay(), player.getYDisplay() + 8, thrusterRight, thrusterRightMask, thrusterFrame, thrusterFrame);
      }
      if(playerFrame == 1)
      {
        Sprites::drawExternalMask(player.getXDisplay(), player.getYDisplay() + 8, thrusterLeft, thrusterLeftMask, thrusterFrame, thrusterFrame);
      }
      if(arduboy.everyXFrames(5))
      {
        ++thrusterFrame;
        thrusterFrame %=2;
      }
      decYDelta(); // going up
      sound.tone(NOTE_C1, 50, NOTE_C2, 50, NOTE_C1, 50);
    }

    if (arduboy.everyXFrames(8))
    {
      if (arduboy.notPressed(A_BUTTON))
      {
        incYDelta(); // start falling.
      }

      if (arduboy.notPressed(LEFT_BUTTON) && arduboy.notPressed(RIGHT_BUTTON))
      { // slow down
        if (player.xDelta > 0)
        {
          decXDelta();
        }
        if (player.xDelta < 0)
        {
          incXDelta();
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
  Serial.print("x: ");
  Serial.print(player.x);
  Serial.print(", xDelta: ");
  Serial.print(player.xDelta);
  Serial.print(", y: ");
  Serial.print(player.y);
  Serial.print(", yDelta: ");
  Serial.println(player.yDelta);
  
  if (player.yDelta < 0) { 
    if (player.y > player.yDelta) {
      player.y = player.y + player.yDelta;
    }
    else {
      player.y = 0;
    }
  }
  if (player.yDelta > 0) { 
    if (player.y < (47 * 8) - player.yDelta) {
      player.y = player.y + player.yDelta;
    }
    else {
      player.y = 47 * 8;
    }
  }
  if (player.xDelta < 0) { 
    if (player.x > player.xDelta) {
      player.x = player.x + player.xDelta;
    }
    else {
      player.x = 0;
    }
  }
  if (player.xDelta > 0) { 
    if (player.x < (111 * 8) - player.xDelta) {
      player.x = player.x + player.xDelta;
    }
    else {
      player.x = (111 * 8);
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
    player.x = 17 * 8;
    player.y = 47 * 8;
    break;

  case 1:
    titleScreen();
    break;

  case 2:
    player.x = 17 * 8;
    player.y = 47 * 8;
    playerFrame = 1;
    thrusterFrame = 0;
    customerx = 73;
    customery = 47;
    customerFrame = 0;
    customerNewPos = 5;
    gameTime = 60;
    currentScore = 0;
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

