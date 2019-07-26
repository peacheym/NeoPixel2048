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

  pinMode(RIGHT_BTN,INPUT_PULLUP);
  pinMode(DOWN_BTN,INPUT_PULLUP);
  pinMode(UP_BTN,INPUT_PULLUP);
  pinMode(LEFT_BTN,INPUT_PULLUP);

  //Random pixel Color button
  pinMode(2,INPUT_PULLUP);

  //Setup inital values for pixel matrix.
  xpos = 0;
  ypos = 0;
  
}

//This function will continously loop
void loop() {
  //If the game is not over yet
  if(gameStatus != 2){
    if(digitalRead(RIGHT_BTN) == LOW){
      right();
      delay(300);
    }

    if(digitalRead(DOWN_BTN) == LOW){
      down();	
      delay(300);
    }
  
    if(digitalRead(UP_BTN) == LOW){
      up();
      delay(300);
    }
  
    if(digitalRead(LEFT_BTN) == LOW){
      left();
      delay(300);
    }

    if(digitalRead(2) == LOW){
      randomColor();
      delay(500);
    }
  
    matrix.clear(); // Set all pixel colors to 'off'
  
    matrix.drawPixel(xpos,ypos,CYAN);

    matrix.show();
  }
}

//These functions will be called when a button is pressed
void up(){
  if(ypos > 0){ypos--;}
}

void down(){
  if(ypos < 3){ypos++;}
}

void left(){
  if(xpos%4 !=0 ){xpos--;}
}

void right(){
  if((xpos+1)%4 != 0){xpos++;}
}
