#include "definitions.h"

#ifndef FUNCTIONS
  #define FUNCTIONS

  //Function prototypes

  bool up();
  bool down();
  bool left();
  bool right();

  int gameStatus();

  void showBoard();

  void placeNewTile();

  int moveOnce(int, int, bool, bool, bool, bool, bool);

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

  int getTileColor(int tileValue){
    //This function simply maps the predefined colors to each power of 2.
    switch(tileValue){
      case    2: return WHITE;
      case    4: return YELLOW;
      case    8: return GREEN;
      case   16: return MAGENTA;
      case   32: return RED;
      case   64: return BLUE;
      case  128: return BLUE;
      case  256: return 0xFFFF;
      case  512: return 0xFFFF;
      case 1024: return 0xFFFF;
      case 2048: return 0xFFFF;
      default: return 0;
    }
  }

  bool isValidPosition(int xpos, int ypos){
    return xpos<4 && ypos<4 && xpos>=0 && ypos>=0;
  }



#endif

