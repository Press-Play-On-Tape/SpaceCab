#pragma once

#define PLAYER_WIDTH 17
#define PLAYER_WIDTH_HALF PLAYER_WIDTH / 2
#define PLAYER_HEIGHT 8
#define PLAYER_HEIGHT_HALF PLAYER_HEIGHT / 2

#define CUSTOMER_WIDTH 7
#define CUSTOMER_HEIGHT 8

#define PLAT1 0
#define EMPTY 1
#define EDGE1 2
#define WATER 3
#define SIGN1 4
#define GATE1 5
#define METAL 6
#define SHADE 7
#define ROOF2 8
#define BRICK 9
#define GRASS 10
#define ROCK1 11
#define ROCK2 12
#define ROCK3 13
#define ROCK4 14
#define ROCK5 15
#define ROCK6 16
#define ROCK7 17
#define FUEL1 18

#define TILE_COUNT 19
#define TILE_SIZE 8
#define NO_TILE 255

static const uint8_t MAX_NUMBER_OF_SCORES         = 5;
static const uint8_t DO_NOT_EDIT_SLOT             = 255;
static const uint8_t GAME_TIME_MAX                = 10;
static const uint8_t ARROW_FLASH                  = 40;

static const uint16_t PLAYER_FUEL_MAX             = 1000;
static const uint16_t FARE_X_FRAMES               = 15;
static const uint16_t FARE_COUNT                  = 10;


enum class GameState : uint8_t {

  VSBoot,
  SplashScreen_Init,
  SplashScreen,
  PlayGame_Init,
  PlayGame,
  EndOfLevel,
  GameOver,
  SaveScore,
  HighScore

};

enum class PlayerStatus : uint16_t {

  Active,
  OutOfFuel_End,
  OutOfFuel_Min,
  OutOfFuel_Img1_Start,
  OutOfFuel_Img1_1,
  OutOfFuel_Img1_2,
  OutOfFuel_Img1_3,
  OutOfFuel_Img1_4,
  OutOfFuel_Img1_5,
  OutOfFuel_Img1_End,
  OutOfFuel_Img2_Start,
  OutOfFuel_Img2_1,
  OutOfFuel_Img2_2,
  OutOfFuel_Img2_3,
  OutOfFuel_Img2_4,
  OutOfFuel_Img2_5,
  OutOfFuel_Img2_End,
  OutOfFuel_Img3_Start,
  OutOfFuel_Img3_1,
  OutOfFuel_Img3_2,
  OutOfFuel_Img3_3,
  OutOfFuel_Img3_4,
  OutOfFuel_Img3_5,
  OutOfFuel_Img3_End,
  OutOfFuel_Img4_Start,
  OutOfFuel_Img4_1,
  OutOfFuel_Img4_2,
  OutOfFuel_Img4_3,
  OutOfFuel_Img4_4,
  OutOfFuel_Img4_5,
  OutOfFuel_Img4_End,
  OutOfFuel_Max = OutOfFuel_Img4_End

};


inline PlayerStatus operator++( PlayerStatus & c ) {

  c = static_cast<PlayerStatus>( static_cast<uint16_t>(c) + 1 );
  return c;

}

inline PlayerStatus operator++( PlayerStatus & c, int ) {

  PlayerStatus result = c;
  ++c;
  return result;

}

inline PlayerStatus operator--( PlayerStatus & c ) {
 
  c = static_cast<PlayerStatus>( static_cast<uint16_t>(c) - 1 );
  return c;

}

inline PlayerStatus operator--( PlayerStatus & c, int ) {

  PlayerStatus result = c;
  --c;
  return result;

}