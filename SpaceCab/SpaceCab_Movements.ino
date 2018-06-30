#include <Arduboy2.h>


// ----------------------------------------------------------------------------------------------------------
//  Can the player move left ?
// ----------------------------------------------------------------------------------------------------------

bool canMoveLeft() {

  const uint8_t * levelMap = levelMaps[level.getLevelNumber()];
  uint16_t playerXPosition = player.getXDisplay() - level.getXOffsetDisplay();
  uint16_t playerYPosition = player.getYDisplay() - level.getYOffsetDisplay();
 

  // We are not yet at the left hand edge of tile so movement is possible ..

  if (playerXPosition % TILE_SIZE != 0) return true;
	

  // Retrieve the tile from the level defintion for x, y1 ..

  uint8_t tileX = (playerXPosition / 8) - 1;
  uint8_t tileY1 = (playerYPosition / 8);
  uint8_t tile1 = pgm_read_byte(&levelMap[(tileY1 * level.getWidthInTiles()) + tileX]);

  if (isTileSolid(tile1)) return false;


  // Are we are actually straddling two tiles vertically?  If so test the second tile ..

  if (playerYPosition % TILE_SIZE != 0) {

    uint8_t tileY2 = (playerYPosition / 8) + 1;
    uint8_t tile2 = pgm_read_byte(&levelMap[(tileY2 * level.getWidthInTiles()) + tileX]);

    if (isTileSolid(tile2)) return false;

  }

  return true;

}


// ----------------------------------------------------------------------------------------------------------
//  Can the player move right ?
// ----------------------------------------------------------------------------------------------------------

bool canMoveRight() {

  const uint8_t * levelMap = levelMaps[level.getLevelNumber()];
  uint16_t playerXPosition = player.getXDisplay() - level.getXOffsetDisplay() + PLAYER_WIDTH;
  uint16_t playerYPosition = player.getYDisplay() - level.getYOffsetDisplay();


  // We are not yet at the right hand edge of tile so movement is possible..

  if (playerXPosition % TILE_SIZE != TILE_SIZE - 1) return true;


  // Retrieve the tile from the level defintion for x, y1 ..
  
  uint8_t tileX = (playerXPosition / 8) + 1;
  uint8_t tileY1 = (playerYPosition / 8);
  uint8_t tile1 = pgm_read_byte(&levelMap[(tileY1 * level.getWidthInTiles()) + tileX]);

  if (isTileSolid(tile1)) return false;


  // Are we are actually straddling two tiles vertically?  If so test the second tile ..

  if (playerYPosition % TILE_SIZE != 0) {

    uint8_t tileY2 = (playerYPosition / 8) + 1;
    uint8_t tile2 = pgm_read_byte(&levelMap[(tileY2 * level.getWidthInTiles()) + tileX]);

    if (isTileSolid(tile2)) return false;

  }

  return true;
  
}


// ----------------------------------------------------------------------------------------------------------
//  Can the player move up ?
// ----------------------------------------------------------------------------------------------------------

bool canMoveUp() {

  const uint8_t * levelMap = levelMaps[level.getLevelNumber()];
  uint16_t playerXPosition = player.getXDisplay() - level.getXOffsetDisplay();
  uint16_t playerYPosition = player.getYDisplay() - level.getYOffsetDisplay();


  // We are not yet at the top edge of tile so movement is possible ..

  if (playerYPosition % TILE_SIZE != 0) return true;


  // The player is 17 pixels wide so always straddles 3 tiles .. 

  uint8_t tileY = (playerYPosition / 8) - 1;
  uint8_t tileX1 = (playerXPosition / 8);
  uint8_t tileX2 = (playerXPosition / 8) + 1;
  uint8_t tileX3 = (playerXPosition / 8) + 2;


  // Retrieve the the three tiles and test them in order ..

  uint8_t tile1 = pgm_read_byte(&levelMap[(tileY * level.getWidthInTiles()) + tileX1]);
  if (isTileSolid(tile1)) return false;
	
  uint8_t tile2 = pgm_read_byte(&levelMap[(tileY * level.getWidthInTiles()) + tileX2]);
  if (isTileSolid(tile2)) return false;
	
  uint8_t tile3 = pgm_read_byte(&levelMap[(tileY * level.getWidthInTiles()) + tileX3]);
  if (isTileSolid(tile3)) return false;

  return true;

}



// ----------------------------------------------------------------------------------------------------------
//  Can the player move down ?
// ----------------------------------------------------------------------------------------------------------

bool canMoveDown() {

  const uint8_t * levelMap = levelMaps[level.getLevelNumber()];
  uint16_t playerXPosition = player.getXDisplay() - level.getXOffsetDisplay();
  uint16_t playerYPosition = player.getYDisplay() - level.getYOffsetDisplay() + PLAYER_HEIGHT;


  // We are not yet at the bottom edge of tile so movement is possible ,,

  if (playerYPosition % TILE_SIZE != 0) return true;


  // The player is 17 pixels wide so always straddles 3 tiles .. 

  uint8_t tileY = (playerYPosition / 8);
  uint8_t tileX1 = (playerXPosition / 8);
  uint8_t tileX2 = (playerXPosition / 8) + 1;
  uint8_t tileX3 = (playerXPosition / 8) + 2;


  // Retrieve the the three tiles and test them in order ..

  uint8_t tile1 = pgm_read_byte(&levelMap[(tileY * level.getWidthInTiles()) + tileX1]);
  if (isTileSolid(tile1)) return false;
	
  uint8_t tile2 = pgm_read_byte(&levelMap[(tileY * level.getWidthInTiles()) + tileX2]);
  if (isTileSolid(tile2)) return false;
	
  uint8_t tile3 = pgm_read_byte(&levelMap[(tileY * level.getWidthInTiles()) + tileX3]);
  if (isTileSolid(tile3)) return false;

  return true;

}


void moveCab() {

  SQ15x16 playerYDeltaVal = player.getYDeltaVal();
  SQ15x16 playerXDeltaVal = player.getXDeltaVal();


  // --  Moving up --------------------------------------------------------------------------------------------

  if (player.yDelta < 0) { 

    if (canMoveUp()) {

      if (level.yOffset < 0) {

        if (player.y < PLAYER_Y_CENTRE) {
          if (level.yOffset < playerYDeltaVal) {
            level.yOffset = level.yOffset - playerYDeltaVal;
          }
          else {
            level.yOffset = 0;
          }
        }
        else if (player.y == PLAYER_Y_CENTRE) {
          if (level.yOffset < PLAYER_Y_CENTRE && (level.getWidthInTiles() != 16 || level.getHeightInTiles() != 8)) {
            level.yOffset = level.yOffset - playerYDeltaVal;
          }
          else {
            player.y = player.y + playerYDeltaVal - level.yOffset;
            level.yOffset = 0;
          }
        }
        else if (player.y > PLAYER_Y_CENTRE) {
          if (player.y + playerYDeltaVal > PLAYER_Y_CENTRE) {
            player.y = player.y + playerYDeltaVal;
          }
          else {
            level.yOffset = level.yOffset + PLAYER_Y_CENTRE - player.y - playerYDeltaVal;
            player.y = PLAYER_Y_CENTRE;
          }
        }

      }
      else {

        if (player.y > -playerYDeltaVal) {
          player.y = player.y + playerYDeltaVal;
        }
        else {
          player.y = 0;
        }

      }

    }
    
  }


  // --  Moving down --------------------------------------------------------------------------------------------

  if (player.yDelta > 0) { 
    
    if (canMoveDown()) {
      if (player.y < PLAYER_Y_CENTRE) {                         
        if (player.y + playerYDeltaVal < PLAYER_Y_CENTRE) {
          player.y = player.y + playerYDeltaVal;
        }
        else {
          level.yOffset = PLAYER_Y_CENTRE - player.y - playerYDeltaVal;
          player.y = PLAYER_Y_CENTRE;
        }
      }
      else if (player.y == PLAYER_Y_CENTRE) {                            
        if (level.yOffset - playerYDeltaVal > -level.getHeight() + HEIGHT && (level.getWidthInTiles() != 16 || level.getHeightInTiles() != 8)) {
          level.yOffset = level.yOffset - playerYDeltaVal;
        }
        else {
          player.y = player.y + ((level.getHeight() - HEIGHT) + level.yOffset) + playerYDeltaVal;
          level.yOffset = -level.getHeight() + HEIGHT;
        }
      }
      else if (player.y > PLAYER_Y_CENTRE) {
        // Player is below the half way line ..     
        // If the player can still move downwards on the screen then do it.      
        if (player.y + playerYDeltaVal + PLAYER_HEIGHT < HEIGHT) {
          player.y = player.y + playerYDeltaVal;
        }
        else {
          // Otherwise, cap the Y value at the maximum height ..
          player.y = HEIGHT - PLAYER_HEIGHT;
        }

      }

    }

  }


  // --  Moving left --------------------------------------------------------------------------------------------

  if (player.xDelta < 0) { 

    if (canMoveLeft()) {

      if (level.xOffset < 0) {

        if (player.x < PLAYER_X_CENTRE) {
          if (level.xOffset < playerXDeltaVal) {
            level.xOffset = level.xOffset - playerXDeltaVal;
          }
          else {
            level.xOffset = 0;
          }
        }
        else if (player.x == PLAYER_X_CENTRE) {
          if (level.xOffset < playerXDeltaVal && (level.getWidthInTiles() != 16 || level.getHeightInTiles() != 8)) {
            level.xOffset = level.xOffset - playerXDeltaVal;
          }
          else {
            player.x = player.x + playerXDeltaVal - level.xOffset;
            level.xOffset = 0;
          }
        }
        else if (player.x > PLAYER_X_CENTRE) {
          if (player.x + playerXDeltaVal > PLAYER_X_CENTRE) {
            player.x = player.x + playerXDeltaVal;
          }
          else {
            level.xOffset = level.xOffset + PLAYER_X_CENTRE - player.x - playerXDeltaVal;
            player.x = PLAYER_X_CENTRE;
          }
        }

      }
      else {

        if (player.x > -playerXDeltaVal) {
          player.x = player.x + playerXDeltaVal;
        }
        else {
          player.x = 0;
        }

      }

    }
    
  }


  // --  Moving Right -------------------------------------------------------------------------------------------

  if (player.xDelta > 0) {

    if (canMoveRight()) {

      if (player.x < PLAYER_X_CENTRE) {
        if (player.x + playerXDeltaVal < PLAYER_X_CENTRE) {
          player.x = player.x + playerXDeltaVal;
        }
        else {
          level.xOffset = PLAYER_X_CENTRE - player.x - playerXDeltaVal;
          player.x = PLAYER_X_CENTRE;
        }
      }
      else if (player.x == PLAYER_X_CENTRE) {                            
        if (level.xOffset - playerXDeltaVal > -level.getWidth() + WIDTH && (level.getWidthInTiles() != 16 || level.getHeightInTiles() != 8)) {
          level.xOffset = level.xOffset - playerXDeltaVal;
        }
        else {
          player.x = player.x + ((level.getWidth() - WIDTH) + level.xOffset) + playerXDeltaVal;
          level.xOffset = -level.getWidth() + WIDTH;
        }
      }
      else if (player.x > PLAYER_X_CENTRE) {

        if (player.x + playerXDeltaVal + PLAYER_WIDTH < WIDTH) {
          player.x = player.x + playerXDeltaVal;
        }
        else {
          player.x = WIDTH - PLAYER_WIDTH;
        }

      }

    }

  }

}