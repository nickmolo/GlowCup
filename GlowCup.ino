

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN      6
#define N_LEDS 90

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);



void setup() {
  randomSeed(analogRead(0));
  strip.begin();
}

void loop() {
  twinkle(strip.Color(random(0,255), random(0,255), random(0,255)));
}


static void twinkle(uint32_t c){
  for(uint16_t i=0; i <strip.numPixels(); i++){
    if(random(0,10) >= 8){
      strip.setPixelColor(i,random(0,255), random(0,255), random(0,255));
    }else{
      strip.setPixelColor(i,0);
    }
    strip.show();
    //delay(25);
  }
}



