#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 13

const float TIME_IN_MS_PER_LED = 1000;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  strip.begin();

  // The overall brightness of ALL the LEDs can be adjusted using setBrightness(). 
  // This takes a single argument, a number in the range 0 (off) to 255 (max brightness). 
  // For example, to set a strip to 1/4 brightness: strip.setBrightness(64);
  strip.setBrightness(90);
  strip.show(); // Initialize all pixels to 'off'
}
void loop() {
  // First set all to BLANK
  oneColor(strip.Color(0, 0, 0));
  delay(TIME_IN_MS_PER_LED);

  // 1 GREEN
  count(strip.Color(0, 255, 0));

  // 2 LIGHTER GREEN 
  count(strip.Color(40, 180, 0));

  // 3 LIGHT-GREEN
  count(strip.Color(20, 90, 0));
  
  // 4 YELLOW-GREEN
  count(strip.Color(100, 255, 0));
  
  // 5 LIGHT-YELLOW
  count(strip.Color(255, 210, 0));
  
  // 6 ORANGE
  count(strip.Color(230, 80, 0));
  
  // 7 RED
  count(strip.Color(255, 0, 0));

  // STROBO
  theaterChaseRainbow(50);
  oneColor(strip.Color(0, 0, 0));
  delay(10000000);
}

// Fill the dots one after the other with a color
void oneColor(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
}
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    delay(wait);
    strip.show();
  }
}

// Fill the dots one after the other with a color
void count(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(TIME_IN_MS_PER_LED);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
      delay(wait);
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, strip.Color(255, 0, 0));    //turn every third pixel on
      }
      strip.show();
      delay(wait);
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
