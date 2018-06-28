#include <Arduboy2.h>

void vsBoot()
{
  // Vsoft logo display
    arduboy.drawBitmap(0, 0, bootlogo, 128, 64, WHITE);
    if (fadeOut())
    {
      resetFade();
      resetFadeIn();
      state = GameState::SplashScreen_Init;
    }
}

void titleScreen()
{
  Rect playerRect = {player.getXDisplay(), player.getYDisplay(), 17, 8};
  Rect customerRect = {97, 48, 7, 8};
  arduboy.drawBitmap(0, 0, SpaceCabSplash, 128, 64, WHITE);
  Sprites::drawExternalMask(97, 48, Customer_Img, Customer_Img_Mask, customer.frame, customer.frame);
  if (arduboy.everyXFrames(15))
  {
    customer.incFrame();
  }
  Sprites::drawExternalMask(player.getXDisplay(), player.getYDisplay(), SpaceTaxi, SpaceTaxiMask, player.frame, player.frame);

  if (arduboy.everyXFrames(4)) {

    if (arduboy.pressed(LEFT_BUTTON)) {
      player.decXDelta();
      player.frame = 1;
    }
    if (arduboy.pressed(RIGHT_BUTTON)) {
      player.incXDelta();
      player.frame = 0;
    }
    if (arduboy.pressed(A_BUTTON)) {
      if (player.frame == 0) {
        Sprites::drawExternalMask(player.getXDisplay(), player.getYDisplay() + 8, thrusterRight, thrusterRightMask, thrusterFrame, thrusterFrame);
      }
      if (player.frame == 1) {
        Sprites::drawExternalMask(player.getXDisplay(), player.getYDisplay() + 8, thrusterLeft, thrusterLeftMask, thrusterFrame, thrusterFrame);
      }
      if (arduboy.everyXFrames(5)) {
        ++thrusterFrame;
        thrusterFrame %=2;
      }
      player.decYDelta();
      sound.tone(NOTE_C1, 50, NOTE_C2, 50, NOTE_C1, 50);
    }

    if (arduboy.everyXFrames(8)) {

      if (arduboy.notPressed(A_BUTTON)){
        player.incYDelta();
      }
      if (arduboy.notPressed(LEFT_BUTTON) && arduboy.notPressed(RIGHT_BUTTON)){
        if (player.xDelta > 0) {
          player.decXDelta();
        }
        if (player.xDelta < 0) {
          player.incXDelta();
        }
      }

    }
  }

  if (arduboy.collide(playerRect, customerRect))
  {
    arduboy.initRandomSeed();
    sound.tone(NOTE_C5,50, NOTE_D4,50, NOTE_E3,50);
    state = GameState::PlayGame_Init;
  }
}


