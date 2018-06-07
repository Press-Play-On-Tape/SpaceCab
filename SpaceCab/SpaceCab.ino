#include <Arduboy2.h>
#include <ArduboyTones.h>
 
Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);
Sprites sprite;


// Lets Load images in PROGMEM -------------------------------------------------

const unsigned char PROGMEM SpaceTaxi[] =
{
// width, height,
17, 8,

//facing right frame0
0x00, 0x70, 0x18, 0x6e, 0x1e, 0x5e, 0x12, 0x72, 0x76, 0x7c, 0x18, 0x6a, 0x1e, 0x5a, 0x10, 0x60, 0x00, 

//facing left frame1
0x00, 0x60, 0x10, 0x5a, 0x1e, 0x6a, 0x18, 0x7c, 0x76, 0x72, 0x12, 0x5e, 0x1e, 0x6e, 0x18, 0x70, 0x00, 
};

const unsigned char PROGMEM SpaceTaxiMask[] =
{

//facing right frame0
0x70, 0xf8, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xfa, 0xf0, 0x60,  

//facing left frame1
0x60, 0xf0, 0xfa, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf8, 0x70,
};

const unsigned char PROGMEM Customer[] =
{
// width, height,
7, 8,

//frame0
0x00, 0x08, 0x64, 0x1e, 0x64, 0x02, 0x00, 

//frame1
0x00, 0x08, 0x64, 0x1e, 0x64, 0x04, 0x00, 
};

const unsigned char PROGMEM CustomerMask[] =
{

//frame0
0x08, 0x7c, 0xfe, 0x7f, 0xfe, 0x67, 0x02, 

//frame1
0x08, 0x7c, 0xfe, 0x7f, 0xfe, 0x6e, 0x04, 
};

//------------------------------------------------------------------------------

// Global Variables now --------------------------------------------------------

uint8_t playerx = 58;
uint8_t playery = 32;
uint8_t playerFrame = 0;

uint8_t customerx = 73;
uint8_t customery = 47;
uint8_t customerFrame = 0;

//------------------------------------------------------------------------------

// Functions -------------------------------------------------------------------

void playerDisplay()
{
  Sprites::drawExternalMask(playerx, playery, SpaceTaxi, SpaceTaxiMask, playerFrame, playerFrame);
  if(arduboy.everyXFrames(3))
  {
    ++playery;
  }
  if(playery>47)
  {
    playery = 47;
  }
}

void customerDisplay()
{
  Sprites::drawExternalMask(customerx, customery, Customer, CustomerMask, customerFrame, customerFrame);
  if(arduboy.everyXFrames(15))
  {
  ++customerFrame;
  customerFrame %=2;
  }
}

void handleInput()
{
  if(arduboy.pressed(LEFT_BUTTON) && playerx > 0)
  {
    --playerx;
    playerFrame = 1;
  }
  if(arduboy.pressed(RIGHT_BUTTON) && playerx < 111)
  {
    ++playerx;
    playerFrame = 0;
  }
  if(arduboy.pressed(A_BUTTON) && playery > 0)
  {
    --playery;
  }
}

void drawHUD()
{
  arduboy.drawLine(0, 53, 128, 53, WHITE);
  arduboy.fillRect(0, 55, 128, 64, WHITE);
  arduboy.fillRect(1, 56, 40, 64, BLACK);
  arduboy.setCursor(2, 57);
  arduboy.print(F("$:"));
}

void drawPad1()
{
  arduboy.drawLine(10, 28, 39, 28, WHITE);
  arduboy.fillRect(10, 30, 30, 9, WHITE);
  arduboy.setCursor(22, 31);
  arduboy.print(F("1"));
}

void customerPosition()
{
  customerx = random(0,121);
  customery = random(0,47);
}

void checkCollision()
{
  Rect playerRect = {playerx, playery, 17, 8};
  Rect customerRect = {customerx, customery, 7, 8};
  Rect pad1Rect = {10, 30, 30, 9};
  if (arduboy.collide(playerRect, pad1Rect))
  {
    playery = playery - 1;
  }
  if (arduboy.collide(playerRect, customerRect))
  {
    customerPosition();
    sound.tone(NOTE_E6, 50, NOTE_E3, 50, NOTE_E2, 50);
  }
}


//------------------------------------------------------------------------------

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(60);

  // initialize things here

}

void loop() {
  if (!(arduboy.nextFrame()))
    return;

  arduboy.clear();

  // Here we go!
  drawHUD();
  drawPad1();
  playerDisplay();
  customerDisplay();
  checkCollision();
  handleInput();

  arduboy.display();
}

