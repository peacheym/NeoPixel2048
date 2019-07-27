#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>

#include "definitions.h"
#include "functions.h"


//Instansiate a matrix object to power the 4x4 NeoPixel Matrix
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(4, 4, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

//These values are used for testing a single pixel on the matrix.  Will likely be removed for full version of the game.
int xpos;
int ypos;


//The main game board where all values will be stored.
int board[4][4];



void setup() {

  Serial.begin(9600);

  matrix.begin(); // INITIALIZE NeoPixel Matrix
  matrix.setBrightness(10);

  pinMode(RIGHT_BTN,INPUT_PULLUP);
  pinMode(DOWN_BTN,INPUT_PULLUP);
  pinMode(UP_BTN,INPUT_PULLUP);
  pinMode(LEFT_BTN,INPUT_PULLUP);

  //Random pixel Color button
  pinMode(2,INPUT_PULLUP);

  //Setup inital values for pixel matrix.
  xpos = 0;
  ypos = 0;

  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      board[i][j] = 0;
    }
  }

  //First two tiles on the board.
  placeNewTile();
  placeNewTile();

  
}

//This function will continously loop
void loop() {
  //If the game is not over yet
  if(gameStatus != 2){
    if(digitalRead(RIGHT_BTN) == LOW){
      if(right()){placeNewTile();}
      delay(300);
    }

    if(digitalRead(DOWN_BTN) == LOW){
      if(down()){placeNewTile();}
      delay(300);
    }
  
    if(digitalRead(UP_BTN) == LOW){
      if(up()){placeNewTile();}
      delay(300);
    }
  
    if(digitalRead(LEFT_BTN) == LOW){
      if(left()){placeNewTile();}
      delay(300);
    }

    showBoard();
  }
}

//These functions will be called when a button is pressed


int gameStatus() {
  bool moveable = false;
  int x, y;
  for ( y = 0; y <= 3; y++ ) {
    for ( x = 0; x <= 3; x++ ) {
      if ( board[x][y] == 0 ) { // vacant tile
        return 0; // board not full
      }
      // let's check if the player can move further
      if ( x <= 2 ) {
        if ( board[x][y] == board[x+1][y] )
          moveable = true;
      }
      if ( y <= 2 ) {
        if ( board[x][y] == board[x][y+1] )
          moveable = true;
      }
    }
  }
  // board full
  if ( moveable ) return 1; // board is 100% full, but still moveable at this point
  else return 2; // No more moves able to be made, game over!
}

void showBoard(){
  matrix.clear();
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      matrix.drawPixel(i,j,getTileColor(board[i][j]));
    }
  }
  matrix.show();
}

void placeNewTile() {
  if ( gameStatus() == 0 ) { // board not full
    int x, y, i;
    //30 'random' attempts at a new tile.
    for ( i = 1; i <= 30; i++ ) {
      x = getRandomPoint();
      y = getRandomPoint();
      if ( !board[x][y] ) {
         board[x][y] = newTileValue();
         return;
      }
    }
    //else find any empty spot.
    for ( y = 0; y <= 3; y++ ) {
      for ( x = 0; x <= 3; x++ ) {
        if ( !board[x][y] ) {
           board[x][y] = newTileValue();
           return;
        }
      }
    }
  }
}

int moveOnce( int x, int y, bool h, bool v, bool hv, bool vv, bool noMerge ) {
  int tx = x, ty = y;
  
  if ( h ) {
    if ( hv ) tx += 1;
    else tx -= 1;
  }
  
  if (v) {
    if (vv){ ty += 1;}
    else{ty -= 1;}
  }
  
  if(!isValidPosition(x,y) || !isValidPosition(tx,ty)){ // illegal tile
    return 0;
  }
  
  else if ( board[x][y] == 0 ){return 0;} // empty tile
  else if ( board[tx][ty] == 0 ) { // the target tile is empty
    board[tx][ty] = board[x][y];
    board[x][y] = 0;
    return 1; // done!
  } 
  else if (!noMerge && board[tx][ty] == board[x][y]) { // the target tile can be merged
    board[tx][ty] = 2 * board[tx][ty];
    board[x][y] = 0;
    return 2; //done!
  }
  return 0;
}

#define moveVerticallyOnce( x, y, d, noMerge ) moveOnce( x, y, false, true, false, d, noMerge )
#define moveHorizontallyOnce( x, y, d, noMerge ) moveOnce( x, y, true, false, d, false, noMerge )

bool up() {
  int x, y, ly, lyMargin, result = 0;
  bool moved = false;
  bool noMerge = false;
  for ( x = 0; x <= 3; x++ ) {
    // now we are at a new col
    lyMargin = 0; // reset the margin
    for ( y = 1; y <= 3; y++ ) {
      // now we are at a new row
      noMerge = false; // reset the noMerge flag
      for ( ly = y; ly > lyMargin; ly-- ) {
        result = moveVerticallyOnce( x, ly, false, noMerge );
        if ( result )
          moved = true;
        if ( result == 2 ) {
          noMerge = true;
          lyMargin = ly;
        }
        if ( result == 0 ) break; // move complete
      }
    }
  }
  return moved;
}

bool left() {
  int x, y, lx, lxMargin, result = 0;
  bool moved = false;
  bool noMerge = false;
  for ( y = 0; y <= 3; y++ ) {
    lxMargin = 0;
    for ( x = 1; x <= 3; x++ ) {
      noMerge = false;
      for ( lx = x; lx > lxMargin; lx-- ) {
        result = moveHorizontallyOnce( lx, y, false, noMerge );
        if ( result )
          moved = true;
        if ( result == 2 ) {
          noMerge = true;
          lxMargin = lx;
        }
        if ( result == 0 ) break; // move complete
      }
    }
  }
  return moved;
}

bool down() {
  int x, y, ly, lyMargin, result = 0;
  bool moved = false;
  bool noMerge = false;
  for ( x = 0; x <= 3; x++ ) {
    lyMargin = 3;
    for ( y = 2; y >= 0; y-- ) {
      noMerge = false;
      for ( ly = y; ly < lyMargin; ly++ ) {
        result = moveVerticallyOnce( x, ly, true, noMerge );
        if ( result )
          moved = true;
        if ( result == 2 ) {
          noMerge = true;
          lyMargin = ly;
        }
        if ( result == 0 ) break;
      }
      if ( y == 0 ) break; // fix the mind-bogging infinite loop
    }
  }
  return moved;
}

bool right() {
  int x, y, lx, lxMargin, result = 0;
  bool moved = false;
  bool noMerge = false;
  for ( y = 0; y <= 3; y++ ) {
    lxMargin = 3;
    for ( x = 2; x >= 0; x-- ) {
      noMerge = false;
      for ( lx = x; lx < lxMargin; lx++ ) {
        result = moveHorizontallyOnce( lx, y, true, noMerge );
        if ( result )
          moved = true;
        if ( result == 2 ) {
          noMerge = true;
          lxMargin = lx;
        }
        if ( result == 0 ) break; // move complete
      }
      if ( x == 0 ) break;
    }
  }
  return moved;
}


