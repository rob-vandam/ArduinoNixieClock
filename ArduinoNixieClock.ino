#include <Adafruit_NeoPixel.h>
#define PIN 7
#define NUMPIXELS 1
#include "RTClib.h"

RTC_DS3231 rtc;
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);
uint32_t hsv_color = 0;
unsigned long previousMillis = 0;
long AnimationDelay = 12000;  

void setup() {
  Serial.begin(9600);
  pixels.begin();
 if (! rtc.begin()) {
   Serial.println("Couldn't find RTC");
   Serial.flush();
   abort();
 }
   if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop() {
DateTime now = rtc.now();
unsigned long currentMillis = millis();
if (currentMillis - previousMillis >= AnimationDelay)
  {
  previousMillis = currentMillis;
  ledanimation();
  }
  Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
  //  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
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
