#include <Adafruit_NeoPixel.h>
#define PIN 7
#define NUMPIXELS 1
#include "RTClib.h"

RTC_DS3231 rtc;
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);
uint32_t hsv_color = 0;
unsigned long previousMillis = 0;
long AnimationDelay = 12000;
int m2;  
//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;
int timearray[4];
byte PinHour = 2;
byte PinMinute = 3;
bool timechanged = 0;
bool hourchanged = 0;
bool minutechanged = 0;
const unsigned long debounceTime = 50;  // milliseconds
unsigned long switchPressTime;
DateTime now;

void setup() {
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(PinHour, INPUT);
  pinMode(PinMinute, INPUT);
  anticathodepoisoning();
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
 DateTime now = rtc.now();
 m2 = now.minute();
 attachInterrupt(digitalPinToInterrupt(PinHour), changehour, RISING);
 attachInterrupt(digitalPinToInterrupt(PinMinute), changeminute, RISING);
}

void loop() {
unsigned long currentMillis = millis();
if ((currentMillis - previousMillis >= AnimationDelay) && (timechanged != 1) && (hourchanged != 1) && (minutechanged != 1))
  {
  previousMillis = currentMillis;
  ledanimation();
  }
  
now = rtc.now();
int h1 = now.hour();
int m1 = now.minute();

if (hourchanged == 1){
//   hourchanged = 0;
   rtc.adjust(DateTime(now.year(),now.month(),now.day(),(now.hour()+1)%24,now.minute(),now.second()));
//   now = rtc.now();
//   Serial.print("H");
//   Serial.print(now.hour());
//   Serial.print(now.minute());
//   Serial.print('\n');
//   displaytime();
 }
 if (minutechanged == 1){
//     minutechanged = 0;
     rtc.adjust(DateTime(now.year(),now.month(),now.day(),now.hour(),(now.minute()+1)%60,now.second()));
     displaytime();
 }

if ((m1!=m2) || (timechanged == 1)||(hourchanged==1)||(minutechanged==1)){ 
    //int newtimearray[]={(h1/10)%10,h1%10,(m1/10)%10,m1%10};
    now = rtc.now();
    h1 = now.hour();
    m1 =now.minute();
    int newtimearray[]={(h1/10)%10,h1%10,(m1/10)%10,m1%10};
    memcpy(timearray,newtimearray,sizeof(timearray));
    displaytime();
    m2 = m1;
    timechanged = 0;
    hourchanged= 0;
    minutechanged = 0;
  }
}

void changehour(){
  if (millis () - switchPressTime >= debounceTime)
       {
       switchPressTime = millis ();  
       hourchanged = 1;
       timechanged = 1;
       }
}

void changeminute(){
  if (millis () - switchPressTime >= debounceTime)
       {
       switchPressTime = millis ();  
       minutechanged = 1;
       timechanged = 1;
       }
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
delay(20);
}
hsv_new = hsv_color;
}

void displaytime(){
  //Serial.print('tijd');
  for (int i=0;i< sizeof(timearray)/sizeof(int);i++){
    //Serial.print('time: ');
    Serial.print(timearray[i]);
  }
  Serial.print('\n');
    byte digit1 = timearray[0];
    byte digit2 = timearray[1] << 4;
    byte digit3 = timearray[2];
    byte digit4 = timearray[3] <<4;
    byte numberToDisplay = digit1 ^ digit2;
    byte numberToDisplay1 = digit3 ^ digit4;
    //byte sum = numberToDisplay + numberToDisplay1;
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay1);  
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
 // }
}

void anticathodepoisoning() {
 for (byte i=0;i<10;i++){
    byte digit1 = i;
    byte digit2 = i << 4;
    byte digit3 = i;
    byte digit4 = i <<4;
    byte numberToDisplay = digit1 ^ digit2;
    byte numberToDisplay1 = digit3 ^ digit4;
    //byte sum = numberToDisplay + numberToDisplay1;
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay1);  
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
   delay(1000);
 }
}
