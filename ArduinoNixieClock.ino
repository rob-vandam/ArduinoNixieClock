#include <Adafruit_NeoPixel.h>
#define PIN 7
#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);
uint32_t hsv_color = 0;
unsigned long previousMillis = 0;
long AnimationDelay = 12000;  

void setup() {
  Serial.begin(9600);
  pixels.begin();
}

void loop() {
unsigned long currentMillis = millis();
if (currentMillis - previousMillis >= AnimationDelay)
  {
  previousMillis = currentMillis;
  ledanimation();
  }
//delay(3000);
}

void ledanimation(){

uint32_t hsv_new = hsv_color + 10900;
if (hsv_new >= 65500){
  hsv_new = hsv_new-65500;  
}

while (hsv_color != hsv_new){
pixels.fill(pixels.ColorHSV(hsv_color));
pixels.show();
hsv_color = hsv_color + 100;
  if (hsv_color >= 65500) {
    hsv_color = 0; 
  }
//Serial.print(hsv_color);
//Serial.print('\n');
//Serial.print(hsv_new);
//Serial.print('\n');
delay(20);
}
hsv_new = hsv_color;
}
