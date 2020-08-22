#include <Adafruit_NeoPixel.h>
#define PIN 7
#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int hsv_color = random(0,360);
int rgb[3];

void setup() {
  Serial.begin(9600);
  pixels.begin();
}

void loop() {
ledanimation();
delay(3000);
}

void ledanimation(){

int hsv_new = hsv_color + 59;
if (hsv_new >= 360){
  hsv_new = hsv_new-360;  
}

while (hsv_color != hsv_new){

  for(int i=0; i<NUMPIXELS; i++) { 
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
    pixels.show();
  }
  hsv_color = hsv_color + 1;
  if (hsv_color >= 360) {
    hsv_color = 0; 
  }
  Serial.print(hsv_color);
Serial.print('\n');
Serial.print(hsv_new);
Serial.print('\n');
delay(500);
}
hsv_new = hsv_color;
}
