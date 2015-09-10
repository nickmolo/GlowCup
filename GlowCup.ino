int state = 0;
int prevstate = 0;
int switchpin = 4; 

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN      6
#define N_LEDS 90

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

#define PIN 6
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(10, 9, PIN,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(218,165,32), matrix.Color(153, 0, 153), matrix.Color(0, 0, 255) };

    
int len = 10;
char message[20] = "boiler up!";
int x    = matrix.width();
int pass = 0;



void setup() {
  randomSeed(analogRead(0));
  state =0;
  prevstate =0; 
}

void loop() {

  if(digitalRead(switchpin) ==  LOW){
    
    state = 0;

    if(prevstate == 0 ){
      strip.begin();
      prevstate=state;
    }
    
    twinkle(strip.Color(random(0,255), random(0,255), random(0,255)));
    
  }else{
    state = 1;

    if(prevstate == 1){
      matrix.begin();
      matrix.setTextWrap(false);
      matrix.setBrightness(40);
      matrix.setTextColor(colors[0]);
      prevstate = state;
    }

    matrix.fillScreen(0);
    matrix.setCursor(x, 0);
    matrix.print(message);
    if(--x < len * -6) {
      x = matrix.width();
      if(++pass >= 3) pass = 0;
      matrix.setTextColor(colors[pass]);
    }
    
    matrix.show();
    delay(100);
  }
}

static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip.show();
      delay(25);
  }
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



