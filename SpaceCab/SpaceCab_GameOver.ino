void gameoverScreen()
{
  uint8_t digits[5];
  scrollingBackground();
  arduboy.fillRect(0, 16, 128, 31, BLACK);
  arduboy.drawLine(0, 17, 128, 17, WHITE);
  arduboy.drawLine(0, 45, 128, 45, WHITE);
  arduboy.drawLine(0, 48, 128, 48, BLACK);
  arduboy.drawLine(0, 50, 128, 50, BLACK);

  arduboy.setCursor(37, 22);
  arduboy.print(F("GAME OVER"));

  arduboy.setCursor(31, 34);
  arduboy.print(F("SCORE:"));
  extractDigits(digits, currentScore);
  for(uint8_t i = 5; i > 0; --i)
  arduboy.print(digits[i - 1]);
  
  if (arduboy.justPressed(B_BUTTON))
  {
    state = 1;
  }
}
