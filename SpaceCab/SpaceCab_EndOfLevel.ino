uint8_t starX1 = WIDTH / 2;
uint8_t starY1 = HEIGHT / 2;
uint8_t starX2 = WIDTH / 2;
uint8_t starY2 = HEIGHT / 2;
uint8_t starX3 = WIDTH / 2;
uint8_t starY3 = HEIGHT / 2;
uint8_t starX4 = WIDTH / 2;
uint8_t starY4 = HEIGHT / 2;
uint8_t starX5 = WIDTH / 2;
uint8_t starY5 = HEIGHT / 2;
uint8_t starX6 = WIDTH / 2;
uint8_t starY6 = HEIGHT / 2;
uint8_t starX7 = WIDTH / 2;
uint8_t starY7 = HEIGHT / 2;
uint8_t starX8 = WIDTH / 2;
uint8_t starY8 = HEIGHT / 2;

void starsBackground()
{
  arduboy.drawPixel(starX1,starY1,WHITE);
  --starX1;
  --starY1;
  
  arduboy.drawPixel(starX2,starY2,WHITE);
  ++starX2;
  ++starY2;
  
  arduboy.drawPixel(starX3,starY3,WHITE);
  --starX3;
  ++starY3;
  
  arduboy.drawPixel(starX4,starY4,WHITE);
  ++starX4;
  --starY4;
  
  arduboy.drawPixel(starX5,starY5,WHITE);
  --starX5;
  
  arduboy.drawPixel(starX6,starY6,WHITE);
  ++starX6;
  
  arduboy.drawPixel(starX7,starY7,WHITE);
  ++starY7;
  
  arduboy.drawPixel(starX8,starY8,WHITE);
  --starY8;
  
  if (starX1 == 0)
  {
    starX1 = WIDTH / 2;
    starY1 = HEIGHT / 2;
  };
  
  if (starX5 == 0)
  {
    starX5 = WIDTH / 2;
    starY5 = HEIGHT / 2;
  };
  
  if (starX6 == 128)
  {
    starX6 = WIDTH / 2;
    starY6 = HEIGHT / 2;
  };
  
  if (starY7 == 64)
  {
    starX7 = WIDTH / 2;
    starY7 = HEIGHT / 2;
  };
  
  if (starY8 == 0)
  {
    starX8 = WIDTH / 2;
    starY8 = HEIGHT / 2;
  };
  
  if (starX2 == 128)
  {
    starX2 = WIDTH / 2;
    starY2 = HEIGHT / 2;
  };
  
  if (starX3 == 0)
  {
    starX3 = WIDTH / 2;
    starY3 = HEIGHT / 2;
  };
  
  if (starX4 == 128)
  {
    starX4 = WIDTH / 2;
    starY4 = HEIGHT / 2;
  };

}
