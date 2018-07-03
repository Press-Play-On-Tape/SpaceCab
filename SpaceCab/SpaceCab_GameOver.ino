#include <Arduboy2.h>

void gameoverScreen() {

  uint8_t digits[5];
  scrollingBackground(true);
  arduboy.fillRect(0, 16, 128, 31, BLACK);
  arduboy.drawLine(0, 17, 128, 17, WHITE);
  arduboy.drawLine(0, 45, 128, 45, WHITE);

  font4x6.setCursor(37, 22);
  font4x6.print(F("GAME OVER"));

  font4x6.setCursor(31, 34);
  font4x6.print(F("SCORE:"));
  extractDigits(digits, player.currentScore);
  for(uint8_t i = 5; i > 0; --i)
  font4x6.print(digits[i - 1]);
  
  if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) {
    state = GameState::SaveScore;
  }
  
}
