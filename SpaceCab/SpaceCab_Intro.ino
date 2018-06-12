void vsBoot()
{
  // Vsoft logo display
    arduboy.drawBitmap(0, 0, bootlogo, 128, 64, WHITE);
    if(fadeOut())
    {
      resetFade();
      resetFadeIn();
      state = 1;
    }
}

void titleScreen()
{
  Rect playerRect = {player.getXDisplay(), player.getYDisplay(), 17, 8};
  Rect customerRect = {97, 48, 7, 8};
  arduboy.drawBitmap(0, 0, SpaceCabSplash, 128, 64, WHITE);
  Sprites::drawExternalMask(97, 48, Customer, CustomerMask, customerFrame, customerFrame);
  if(arduboy.everyXFrames(15))
  {
  ++customerFrame;
  customerFrame %=2;
  }
  Sprites::drawExternalMask(player.getXDisplay(), player.getYDisplay(), SpaceTaxi, SpaceTaxiMask, playerFrame, playerFrame);

  if (arduboy.everyXFrames(4)) {

    if(arduboy.pressed(LEFT_BUTTON))// && playerx > 0)
    {
      decXDelta();
      playerFrame = 1;
    }
    if(arduboy.pressed(RIGHT_BUTTON))// && playerx < 111)
    {
      incXDelta();
      playerFrame = 0;
    }
    if(arduboy.pressed(A_BUTTON))// && playery > 0)
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
      decYDelta();
      sound.tone(NOTE_C1, 50, NOTE_C2, 50, NOTE_C1, 50);
    }

    if (arduboy.everyXFrames(8)) {

      if (arduboy.notPressed(A_BUTTON)){
        incYDelta();
      }
      if (arduboy.notPressed(LEFT_BUTTON) && arduboy.notPressed(RIGHT_BUTTON)){
        if (player.xDelta > 0) {
          decXDelta();
        }
        if (player.xDelta < 0) {
          incXDelta();
        }
      }

    }
  }

  if (arduboy.collide(playerRect, customerRect))
  {
    arduboy.initRandomSeed();
    sound.tone(NOTE_C5,50, NOTE_D4,50, NOTE_E3,50);
    state = 2;
  }
}


