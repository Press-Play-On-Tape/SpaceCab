#pragma once

// --------------------------------------------------------------------------

#define _ARROWS_FP

// --------------------------------------------------------------------------

#define PLAYER_WIDTH 17
#define PLAYER_WIDTH_HALF PLAYER_WIDTH / 2
#define PLAYER_HEIGHT 8
#define PLAYER_HEIGHT_HALF PLAYER_HEIGHT / 2

#define CUSTOMER_WIDTH 7
#define CUSTOMER_WIDTH_HALF CUSTOMER_WIDTH / 2
#define CUSTOMER_HEIGHT 8

#define EMPTY 0
#define PLAT1 1
#define EDGE1 2
#define WATER 3
#define SIGN1 4
#define GATE1 5
#define METAL 6
#define SHADE 7
#define ROCKS 8
#define BRICK 9
#define GRASS 10
#define FUEL1 11
#define SAND1 12
#define SPIKU 13
#define SPIKD 14

#define TILE_COUNT 15
#define TILE_SIZE 8
#define NO_TILE 255

#define DOLLARS_COUNT_MULT 8
#define DOLLARS_COUNT_MAX (DOLLARS_COUNT_MULT * 5) - 1 

static const uint8_t MAX_NUMBER_OF_LEVELS         = 4;
static const uint8_t MAX_NUMBER_OF_SCORES         = 5;
static const uint8_t DO_NOT_EDIT_SLOT             = 255;
static const uint8_t GAME_TIME_MAX                = 10;
static const uint8_t FLASH_MAX                    = 40;
static const uint8_t ARROW_DO_NOT_SHOW            = 255;

static const uint16_t PLAYER_FUEL_MAX             = 200;
static const uint8_t PLAYER_NUMBER_OF_LIVES_MAX   = 3;
static const uint8_t PLAYER_RETRACT_LANDING_GEAR  = 20;

static const uint16_t FARE_X_FRAMES               = 15;
static const uint16_t FARE_COUNT                  = 10;
static const uint16_t FARE_MIN                    = 10;
static const uint16_t FARE_MAX                    = 20;

static const uint8_t CUSTOMER_NO_STARTING_POS     = 255;
static const uint8_t CUSTOMER_PICKUP_RANGE        = 16;

static const uint8_t GOTO_COUNTER_MAX             = 120;
static const uint8_t OUCH_COUNTER_MAX             = 120;

static const uint8_t FUEL_TILES_MAX               = 5;
static const uint8_t GATE_TILES_MAX               = 5;
static const uint8_t FUEL_MIN                     = 40;
static const uint8_t FUEL_MAX                     = 80;

enum class GameState : uint8_t {

  VSBoot,
  SplashScreen_Init,
  SplashScreen,
  PlayGame_InitGame,
  PlayGame_InitLevel,
  PlayGame,
  EndOfLevel,
  GameOver,
  SaveScore,
  HighScore

};

enum class PlayerStatus : uint16_t {

  Active,
  Inactive,
  OutOfFuel_End,
  OutOfFuel_Min,
  OutOfFuel_Blank_01,
  OutOfFuel_Blank_02,
  OutOfFuel_Blank_03,
  OutOfFuel_Blank_04,
  OutOfFuel_Blank_05,
  OutOfFuel_Blank_06,
  OutOfFuel_Blank_07,
  OutOfFuel_Blank_08,
  OutOfFuel_Blank_09,
  OutOfFuel_Blank_10,
  OutOfFuel_Blank_11,
  OutOfFuel_Blank_12,
  OutOfFuel_Blank_13,
  OutOfFuel_Blank_14,
  OutOfFuel_Blank_15,
  OutOfFuel_Blank_16,
  OutOfFuel_Blank_17,
  OutOfFuel_Blank_18,
  OutOfFuel_Blank_19,
  OutOfFuel_Blank_20,
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

enum class Direction : uint8_t {

  Up,
  UpRight,
  Right,
  DownRight,
  Down,
  DownLeft,
  Left,
  UpLeft

};

enum class CustomerStatus : uint8_t {

  Dead,
  Alive,
  BoardingCab

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

