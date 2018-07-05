#include "src/utils/Arduboy2Ext.h"


void vsBoot() {
  
  Sprites::drawOverwrite(29, 17, bootlogo, 0);

  switch (counter) {

    case 0:
      
      if (!fadeOutEffect.isComplete()) {

        fadeOutEffect.draw(arduboy);
        fadeOutEffect.update();

      }

      if (fadeOutEffect.isComplete())   state = GameState::SplashScreen_Init;

      break;

    case 1:

      fadeOutEffect.reset(0, HEIGHT, 1);
      --counter;
      break;

    default:
  
      --counter;
      break;
      
  }

}

void titleScreen() {

  int16_t customerXVal = customer.getX() + level.xOffset.getInteger();
  int16_t customerYVal = customer.getY() + level.yOffset.getInteger();
  int16_t logoXVal = 0 + level.xOffset.getInteger();
  int16_t logoYVal = 6 + level.yOffset.getInteger();  
  
  Rect playerRect = {static_cast<int16_t>(player.getXDisplay()), static_cast<int16_t>(player.getYDisplay()), PLAYER_WIDTH, PLAYER_HEIGHT};
  Rect customerRect = {customerXVal, customerYVal, CUSTOMER_WIDTH, CUSTOMER_HEIGHT};

  Sprites::drawOverwrite(logoXVal, logoYVal, SpaceCabSplash, 0);
  drawLevel();

  playerDisplay();
  customerDisplay();
  handleInput();
  
  if (arduboy.collide(playerRect, customerRect)){
    arduboy.initRandomSeed();
    sound.tone(NOTE_C5,50, NOTE_D4,50, NOTE_E3,50);
    state = GameState::PlayGame_InitGame;
  }
  
}
