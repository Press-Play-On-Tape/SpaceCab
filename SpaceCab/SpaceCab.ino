#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "src/Images/Images.h"
#include "src/Entities/Entities.h"
#include "src/Utils/Utils.h"
#include "src/Utils/Constants.h"
#include "src/Utils/EEPROM_Utils.h"
#include "src/Utils/FadeEffects.h"
#include <FixedPoints.h>
#include <FixedPointsCommon.h>
#include "src/Fonts/Font4x6.h"

ArduboyTones sound(arduboy.audio.enabled);
Sprites sprite;

Player player;
Customer customer;
Level level;
Font4x6 font4x6 = Font4x6(0);

FadeOutEffect fadeOutEffect;
FadeInEffect fadeInEffect;
HighScore highScore;


// Global Variables now --------------------------------------------------------

GameState state = GameState::VSBoot;

uint8_t levelNumber = 0;
uint8_t thrusterFrame = 0;
uint8_t gameTime = GAME_TIME_MAX;
uint16_t currentScore = 0;
int16_t backdropx = 0;
int16_t backdropy = 0;
uint8_t alternate = 0;
uint8_t fareCount = 0;

//------------------------------------------------------------------------------



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

  EEPROM_Utils::initEEPROM(false);
  
  fadeOutEffect.reset(0, HEIGHT, 1);
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
      fadeInEffect.reset(0, HEIGHT, 1);
      // break;  -- Fall through intentional.

    case GameState::SplashScreen:
      titleScreen();
      break;

    case GameState::PlayGame_Init:
      thrusterFrame = 0;
      gameTime = GAME_TIME_MAX;
      currentScore = 0;
      levelNumber = 1;

      initLevel(levelNumber, &player, &level);
      launchCustomer();

      state = GameState::PlayGame;
      // break;  -- Fall through intentional.
        
    case GameState::PlayGame:
      inGame();
      break;

    case GameState::EndOfLevel:
//      gameoverScreen();
      break;

    case GameState::GameOver:
      gameoverScreen();
      break;

    case GameState::SaveScore:
      highScore.reset();
      highScore.setSlotNumber(EEPROM_Utils::saveScore(currentScore));
      state = GameState::HighScore;
      fadeInEffect.reset(0, HEIGHT, 1);
      // break; Fall-through intentional.

    case GameState::HighScore:
      HighScore();
      break;

  }

  arduboy.display();
  moveCab();

}

