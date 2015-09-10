

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN      6
#define N_LEDS 90

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);



void setup() {
  randomSeed(analogRead(0));
  strip.begin();
  strip.setBrightness(64);
}

void loop() {
  twinkle(strip.Color(random(0,255), random(0,255), random(0,255)));
}


static void twinkle(uint32_t c){
  for(uint16_t i=0; i <strip.numPixels(); i++){
    if(random(0,10) >= 6){
      strip.setPixelColor(i,random(0,255), random(0,255), random(0,255));
    }else{
      strip.setPixelColor(i,0);
    }
    strip.show();
    //delay(25);
  }
}

void setLedColorHSV(int h, double s, double v) {
  //this is the algorithm to convert from RGB to HSV
  double r=0; 
  double g=0; 
  double b=0;

  double hf=h/60.0;

  int i=(int)floor(h/60.0);
  double f = h/60.0 - i;
  double pv = v * (1 - s);
  double qv = v * (1 - s*f);
  double tv = v * (1 - s * (1 - f));

  switch (i)
  {
  case 0: //rojo dominante
    r = v;
    g = tv;
    b = pv;
    break;
  case 1: //verde
    r = qv;
    g = v;
    b = pv;
    break;
  case 2: 
    r = pv;
    g = v;
    b = tv;
    break;
  case 3: //azul
    r = pv;
    g = qv;
    b = v;
    break;
  case 4:
    r = tv;
    g = pv;
    b = v;
    break;
  case 5: //rojo
    r = v;
    g = pv;
    b = qv;
    break;
  }

  //set each component to a integer value between 0 and 255
  int red=constrain((int)255*r,0,255);
  int green=constrain((int)255*g,0,255);
  int blue=constrain((int)255*b,0,255);

 // setLedColor(red,green,blue);
}


