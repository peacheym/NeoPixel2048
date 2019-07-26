#ifndef FUNCTIONS
  #define FUNCTIONS

  //Function prototypes

  void up();
  void down();
  void left();
  void right();

  // HELPER FUNCTION TO RETURN RANDOM RGB VALUE
  void randomColor(){
    int r = random(151);
    int g = random(151);
    int b = random(151);
    //TODO: Return the associated HEX value.
  }

  // ---- RANDOM HELPER FUNCTIONS ----

  /*
  80% chance of new tile being a 2
  20% chance of new tile being a 4
  */  
  int newTileValue(){
    int chance = random(10);
    if(chance < 8){return 2;}
    else{return 4;}

  }
  
  /*
  Returns random point value between 0 and 3 to be used for placing new tiles.
  */
  int getRandomPoint(){
    return random(4);	
  }

  //---- END RANDOM HELPER FUNCTIONS ----



  unsigned char gameStatus() {
	bool moveable = false;
	unsigned char x, y;
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

#endif
