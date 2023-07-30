#include <FastLED.h>

#define DATA_PIN 3
#define SCALE 63
#define COLOR_ORDER RGB
#define LED_TYPE WS2811

CRGB leds[SCALE];

#define MAX_BRIGHTNESS          255

#define FRAMES_PER_SECOND 120

void setup() {
  delay(5000); //For setup.
  
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, SCALE).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(MAX_BRIGHTNESS);

  Serial.begin(57600);
}

typedef void (*SimplePatternList[])();

SimplePatternList gPatterns = { purpleglitter, orangeglitter, whiteglitter, purpleorangewhiteglitter, purpleorangeGlitter};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current

void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void purpleglitter()
{
  PurpleGlitter(50);
  fadeToBlackBy( leds, SCALE, 20);
}

void PurpleGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(SCALE) ] += CRGB(255,0,240);
  }
}

void orangeglitter()
{
  OrangeGlitter(75);
  fadeToBlackBy( leds, SCALE, 20);
}

void OrangeGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(SCALE) ] += CRGB(255,125,0);
  }
}

void whiteglitter()
{
  WhiteGlitter(75);
  fadeToBlackBy( leds, SCALE, 20);
}

void WhiteGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(SCALE) ] += CRGB(255,255,255);
  }
}

void purpleorangewhiteglitter()
{
  WhiteGlitter(25);
  OrangeGlitter(25);
  PurpleGlitter(25);
  fadeToBlackBy( leds, SCALE, 25);
}

void purpleorangeGlitter()
{
  OrangeGlitter(37);
  PurpleGlitter(37);
  fadeToBlackBy( leds, SCALE, 37);
}

/// Created by MrFunnyPenguin. Made using Modifed version of DemoReel100. Features glitter in Halloween colors, all in a seemless loop. Version 1.0. July 30 2023. 
