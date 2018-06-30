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
#include "Font4x6.h"

ArduboyTones sound(arduboy.audio.enabled);
Sprites sprite;

Player player;
Customer customer;
Level level;
Font4x6 font4x6 = Font4x6(0);


// Global Variables now --------------------------------------------------------

GameState state = GameState::VSBoot;

uint8_t levelNumber = 0;
uint8_t thrusterFrame = 0;
uint8_t gameTime = 60;
uint16_t currentScore = 0;
int16_t backdropx = 0;
int16_t backdropy = 0;

//------------------------------------------------------------------------------


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

    else if (arduboy.pressed(DOWN_BUTTON)) {
      player.incYDelta(); 
    }

    else if (arduboy.pressed(A_BUTTON)) {

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

    else if (arduboy.everyXFrames(8)) {

      // If the A Button is not being pressed, then we should start falling ..

      if (arduboy.notPressed(A_BUTTON)) {
        player.incYDelta(); 
      }


      // If the player is not pressing the elft or right button then start slowing down ..

      if (arduboy.notPressed(LEFT_BUTTON) && arduboy.notPressed(RIGHT_BUTTON)) {

        if (player.xDelta > 0)  player.decXDelta();
        if (player.xDelta < 0)  player.incXDelta();

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


//------------------------------------------------------------------------------
//  Launch a new customer.
//
//  Valid launching positions are derived from the level design.
//------------------------------------------------------------------------------

void launchCustomer() {

  uint8_t numberOfStartingPositions = levelStartingPositionsCount[level.getLevelNumber()];
  uint8_t customerNewPos = random(numberOfStartingPositions);

  const uint8_t *levelStartingPosition = levelStartingPositions[level.getLevelNumber()];
  customer.x = pgm_read_byte(&levelStartingPosition[customerNewPos * 2]) * TILE_SIZE;
  customer.y = pgm_read_byte(&levelStartingPosition[(customerNewPos * 2) + 1]) * TILE_SIZE;
  customer.frame = 0;

}


//------------------------------------------------------------------------------
//  Has the player collided with the customer ?
//------------------------------------------------------------------------------

void checkCollision() {

  Rect playerRect = { static_cast<int16_t>(player.getXDisplay()), static_cast<int16_t>(player.getYDisplay()), PLAYER_WIDTH, PLAYER_HEIGHT };


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


//------------------------------------------------------------------------------
//  Play the game! 
//------------------------------------------------------------------------------

void inGame() {

  updateTime();
  handleInput();
  checkCollision();
  drawLevel();
  playerDisplay();
  customerDisplay();
  drawHUD();

}


//------------------------------------------------------------------------------
//  Setup 
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
  
  if (!(arduboy.nextFrame())) return;

  arduboy.pollButtons();
  arduboy.clear();

  switch (state) {

    case GameState::VSBoot:
      vsBoot();
      break;

    case GameState::SplashScreen_Init:
      initLevel(0, &player, &level);
      launchCustomer();
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

