# NeoPixel 2048
My implementation of the popular game **2048** built using a 4x4 NeoPixel Matrix and powered by an Arduino micro-controller. This version of the game relies on RGB LEDs to display the state of each cell instead of the numeric value like the original game.

The rules of my implementation of **2048** remain the same as the original game. A player will use a D-pad to control which direction to slide all of the tiles on the game board.  When two tiles of the same value are slided together, they combine into a tile with the sum of the two original tiles.  Since this game will be implemented with color instead of numbers, there is a simple mapping of all the powers of 2 to a unique color.

The beauty of the NeoPixel (WS2812) is that you can fully control the entirety of the matrix with only one PWM pin on Arduino. This means that I can potentially use an extremely small form factor board such as ATTiny85 to build this project.  This will allow for the game to be completely contained in a handheld form factor, allowing it to live as a standalone game 'console'.

---

Products used in this project include:

* [Arduino UnoR3](https://store.arduino.cc/usa/arduino-uno-rev3)
* [4x4 WS2812 Matrix](https://www.universal-solder.ca/product/rgb-led-4x4-matrix-with-16-x-ws2812-neopixel-compatible/)
* [Momentary Push Buttons](https://www.adafruit.com/product/367)

Libraries used in this project include:
* [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
* [Adafruit_NeoMatrix](https://github.com/adafruit/Adafruit_NeoMatrix)
* [Adafruit_GFX](https://github.com/adafruit/Adafruit-GFX-Library)
