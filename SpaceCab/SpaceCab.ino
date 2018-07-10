#include "src/utils/Arduboy2Ext.h"

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

Arduboy2Ext arduboy;
ArduboyTones sound(arduboy.audio.enabled);
Sprites sprite;

Player player;
Customer customer;

Font4x6 font4x6 = Font4x6(0);

FadeOutEffect fadeOutEffect;
FadeInEffect fadeInEffect;
HighScore highScore;


// Global Variables now --------------------------------------------------------

GameState state = GameState::VSBoot;

uint8_t levelNumber = 0;
uint8_t thrusterFrame = 0;
uint8_t gameTime = GAME_TIME_MAX;
int16_t backdropx = 0;
uint8_t alternate = 0;
uint8_t fareCount = 0;
uint8_t dollarsCount = 0;
uint8_t flashingCounter = 0;
uint8_t bootCounter = 50;
uint8_t gotoCounter = 0;
uint8_t ouchCounter = 0;

Level level;


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
      levelNumber = 0;
      initLevel(level, player, customer, levelNumber);
      launchCustomer(level, customer, 1, GO_TO_GATE);
      player.setFrame(0);
      state = GameState::SplashScreen;
      fadeInEffect.reset(0, HEIGHT, 1);
      
      // break;  -- Fall through intentional.

    case GameState::SplashScreen:
      titleScreen(level, player, customer);
      break;

    case GameState::PlayGame_InitGame:
      levelNumber = 1;
      initGame(player);
      state = GameState::PlayGame_InitLevel;
      // break;  -- Fall through intentional.

    case GameState::PlayGame_InitLevel:
      thrusterFrame = 0;
      gameTime = GAME_TIME_MAX;
      initLevel(level, player, customer, levelNumber);
      launchCustomer(level, customer, RANDOM_START_POSITION, RANDOM_END_POSITION);
      state = GameState::PlayGame;
      // break;  -- Fall through intentional.
        
    case GameState::PlayGame:
    case GameState::EndOfLevel:
      inGame(font4x6, level, player, customer);
      break;

    case GameState::GameOver:
      gameoverScreen();
      levelNumber = 0;
      break;

    case GameState::SaveScore:
      highScore.reset();
      highScore.setSlotNumber(EEPROM_Utils::saveScore(player.getScore()));
      state = GameState::HighScore;
      fadeInEffect.reset(0, HEIGHT, 1);
      // break; Fall-through intentional.

    case GameState::HighScore:
      renderHighScore(highScore);
      break;

  }

  arduboy.display();
  moveCab(level, player, customer);

}

