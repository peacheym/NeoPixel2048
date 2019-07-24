#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

// Color definitions
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

#define PIN 6

//Define values for each button pin.
#define RIGHT_BTN 12

#define DOWN_BTN 11

#define UP_BTN 10

#define LEFT_BTN 9

#define NUMPIXELS 16 // Popular NeoPixel ring size

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(4, 4, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

int xpos;
int ypos;

// Color values...
int r;
int g;
int b;

void randomColor(){
  r = random(151);
  g = random(151);
  b = random(151);
}

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

void setup() {

  Serial.begin(9600);

  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  matrix.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  pinMode(RIGHT_BTN,INPUT_PULLUP);
  pinMode(DOWN_BTN,INPUT_PULLUP);
  pinMode(UP_BTN,INPUT_PULLUP);
  pinMode(LEFT_BTN,INPUT_PULLUP);

  //Random pixel Color button
  pinMode(2,INPUT_PULLUP);

  //Setup inital values for pixel matrix.
  xpos = 0;
  ypos = 0;
  
  r = 150;
  g = 0;
  b = 0;
  
}

void loop() {

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
