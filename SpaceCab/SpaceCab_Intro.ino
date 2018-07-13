#include "src/utils/Arduboy2Ext.h"

void vsBoot() {
  
  Sprites::drawOverwrite(29, 17, bootlogo, 0);

  switch (bootCounter) {

    case 0:
      
      if (!fadeOutEffect.isComplete()) {

        fadeOutEffect.draw(arduboy);
        fadeOutEffect.update();

      }

      if (fadeOutEffect.isComplete())   state = GameState::SplashScreen_Init;

      break;

    case 1:

      fadeOutEffect.reset(0, HEIGHT, 1);
      --bootCounter;
      break;

    default:
  
      --bootCounter;
      break;
      
  }

}

void titleScreen(Level &level, Player &player, Customer &customer) {

  if (gotoCounter != 0)   gotoCounter--;

  if (ouchCounter != 0) { 

    ouchCounter--;
    if (ouchCounter == 0) {
      gateToRender = (gateToRender == 0 ? 1 : 0);
      launchCustomer(level, customer, gateToRender, GO_TO_GATE);
    }

  }

  Sprites::drawOverwrite(0, 9, SpaceCabSplash, 0);
  drawLevel_Intro(level, gateToRender);

  playerDisplay(player);
  customerDisplay(level, player, customer);
  handleInput(player);


  checkCollisionWithCustomer(level, player, customer);
//  checkCollisionWithLevelElements(level, player);

  drawGoto(level, player, customer);
  drawOuch(level, customer);

  if (player.getY() >= 41 && player.getYDelta()> 0) {
    player.setLandingGearDown(true);
  } 

  // if (arduboy.collide(playerRect, customerRect)){
  //   arduboy.initRandomSeed();
  //   sound.tone(NOTE_C5,50, NOTE_D4,50, NOTE_E3,50);
  //   state = GameState::PlayGame_InitGame;
  // }
  
}
