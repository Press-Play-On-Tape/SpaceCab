#include <Arduboy2.h>

void vsBoot() {
  // Vsoft logo display
  Sprites::drawOverwrite(46, 14, bootlogo, 0);

  if (!fadeOutEffect.isComplete()) {

    fadeOutEffect.draw(arduboy);
    fadeOutEffect.update();

  }

  if (fadeOutEffect.isComplete()) state = GameState::SplashScreen_Init;

}

void titleScreen()
{
  int16_t customerXVal = customer.x + level.xOffset.getInteger();
  int16_t customerYVal = customer.y + level.yOffset.getInteger();
  int16_t logoXVal = 0 + level.xOffset.getInteger();
  int16_t logoYVal = 6 + level.yOffset.getInteger();  
  
  Rect playerRect = {static_cast<int16_t>(player.getXDisplay()), static_cast<int16_t>(player.getYDisplay()), PLAYER_WIDTH, PLAYER_HEIGHT};
  Rect customerRect = {customerXVal, customerYVal, CUSTOMER_WIDTH, CUSTOMER_HEIGHT};
  handleInput();
  drawLevel();
  Sprites::drawExternalMask(logoXVal, logoYVal, SpaceCabSplash, SpaceCabSplashMask, 0, 0);
  
  playerDisplay();
  customerDisplay();
  
  if (arduboy.collide(playerRect, customerRect))
  {
    arduboy.initRandomSeed();
    sound.tone(NOTE_C5,50, NOTE_D4,50, NOTE_E3,50);
    state = GameState::PlayGame_Init;
  }
}
