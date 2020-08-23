#include <Adafruit_NeoPixel.h>
#define PIN 7
#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);
uint32_t hsv_color = 0;
int rgb[3];

void setup() {
  Serial.begin(9600);
  pixels.begin();
}

void loop() {
//ledanimation();
pixels.fill(pixels.ColorHSV(65536));
pixels.show();
delay(3000);
}

void ledanimation(){

uint32_t hsv_new = hsv_color + 10900;
if (hsv_new >= 65500){
  hsv_new = hsv_new-65500;  
}

while (hsv_color != hsv_new){

uint32_t kleur = pixels.ColorHSV(hsv_color);

  for(int i=0; i<NUMPIXELS; i++) { 
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, kleur);
    pixels.show();
  }
  hsv_color = hsv_color + 100;
  if (hsv_color >= 65500) {
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
