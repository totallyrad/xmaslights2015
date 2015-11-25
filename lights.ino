// xmas tree lights

#include "SPI.h"
#include "Adafruit_WS2801.h"

volatile int state = HIGH;   // inturrupt 

int switchPin = 7;              // switch is connected to pin 2
int val;                        // variable for reading the pin status
int buttonState;                // variable to hold the button state
int lightPattern = 0;          // lightPattern

int dataPin = 2;                // WS2801 data pin
int clockPin = 3;               // WS2801 clock pin
// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
Adafruit_WS2801 strip = Adafruit_WS2801(50, dataPin, clockPin);


void setup() {
  pinMode(switchPin, INPUT);    // Set the switch pin as input

  Serial.begin(9600);           // Set up serial communication at 9600bps
  buttonState = digitalRead(switchPin);   // read the initial state
    attachInterrupt(0, advance, LOW);   // interrupt 0 on PIN 2, run the "advance" loop when LOW
}


void loop(){
/*  val = digitalRead(switchPin);      // read input value and store it in val

  if (val != buttonState) {          // the button state has changed!
    if (val == LOW) {                // check if the button is pressed
      lightPattern++;               // increment the buttonPresses variable
      if (lightPattern > 4) lightPattern = 1;
      Serial.print("         BUTTON PRESS");
      delay(100);
*/

    }
    
  
  buttonState = val;                 // save the new state in a variable


switch (lightPattern) {
  case 1:
    pattern1();
      break;
  case 2:
    pattern2();
      break;
  case 3:
    pattern3();
      break;
  case 4:
    pattern4();
      break;
}

// patterns 

} void pattern1() {

// Code for LEDS 

/* Commented out for debugging
dither(Color(  0, 127,   0), 10); // Green
dither(Color(127,   0,   0), 20); // Red
dither(Color(  0,   0, 127), 10); // Blue
dither(Color(  0, 127, 127), 5); // Cyan
strip.show();   // write all the pixels out
*/

// debugging

Serial.print("Pattern1");
Serial.println();

} void pattern2() {

// Commented out for debugging  
rainbowCycle(1);
strip.show();   // write all the pixels out
// 
    Serial.print("Pattern2");
    Serial.println();
} void pattern3() {
  
//
colorChase(Color(  0, 127,   0), 2); // Green
colorChase(Color(  0, 127, 127), 2); // Cyan
colorChase(Color(  0,   0, 127), 2); // Blue
colorChase(Color(127,   0, 127), 2); // Violet
colorChase(Color(127, 127, 127), 2); // White
colorChase(Color(127,   0,   0), 2); // Red
colorChase(Color(127, 127,   0), 2); // Yellow
colorChase(Color(  0, 127,   0), 2); // Green
strip.show();   // write all the pixels out
//
  
    Serial.print("Pattern3");
    Serial.println();
}  void pattern4() {

// Commented out for debugging
rainbowCycle(2);
strip.show();   // write all the pixels out
//

    Serial.print("Pattern4");
    Serial.println();
}




////// HELPER FUNCTIONS BELOW

// Rainbow

void rainbow(uint8_t wait) {
  int i, j;

  for (j=0; j < 256; j++) {     // 3 cycles of all 256 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 255));
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// rainbowcycle
// Slightly different, this one makes the rainbow wheel equally distributed along the chain

void rainbowCycle(uint8_t wait) {
  int i, j;

  for (j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 256 / strip.numPixels()) + j) % 256) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// colorwipe
// fill the dots one after the other with said color good for testing purposes

void colorWipe(uint32_t c, uint8_t wait) {
  int i;

  for (i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

// colorChase
// Chase one dot down the full strip.

void colorChase(uint32_t c, uint8_t wait) {
  int i;

  // Start by turning all pixels off:
  for(i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);

  // Then display one pixel at a time:
  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c); // Set new pixel 'on'
    strip.show();              // Refresh LED states
    strip.setPixelColor(i, 0); // Erase pixel, but don't refresh!
    delay(wait);
  }

  strip.show(); // Refresh to turn off last pixel
}


// An "ordered dither" fills every pixel in a sequence that looks
// sparkly and almost random, but actually follows a specific order.

void dither(uint32_t c, uint8_t wait) {

  // Determine highest bit needed to represent pixel index
  int hiBit = 0;
  int n = strip.numPixels() - 1;
  for(int bit=1; bit < 0x8000; bit <<= 1) {
    if(n & bit) hiBit = bit;
  }

  int bit, reverse;
  for(int i=0; i<(hiBit << 1); i++) {
    // Reverse the bits in i to create ordered dither:
    reverse = 0;
    for(bit=1; bit <= hiBit; bit <<= 1) {
      reverse <<= 1;
      if(i & bit) reverse |= 1;
    }
    strip.setPixelColor(reverse, c);
    strip.show();
    delay(wait);
  }
  delay(250); // Hold image for 1/4 sec
}


/* Helper functions */

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
    return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170; 
    return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void advance()
{ 
lightPattern++;               // increment the buttonPresses variable
      if (lightPattern > 4) lightPattern = 1;
      Serial.print("         BUTTON PRESS");
}
