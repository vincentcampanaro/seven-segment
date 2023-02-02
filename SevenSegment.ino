// Define the segments
const byte a = 0;
const byte b = 1;
const byte c = 2;
const byte d = 3;
const byte e = 4;
const byte f = 5;
const byte g = 6;
const byte dp = 7;

#define LED_green CRGB::Green
#define LED_red CRGB::Red

#include <FastLED.h>
#include <SoftwareSerial.h>

CRGB leds[112];
// Create a multidimensional array to store the state of each segment
bool segments[10][7] = {
  // a  b  c  d  e  f  g
  { 1, 1, 1, 1, 1, 1, 0 }, // 0
  { 0, 0, 1, 1, 0, 0, 0 }, // 1
  { 0, 1, 1, 0, 1, 1, 1 }, // 2
  { 0, 1, 1, 1, 1, 0, 1}, // 3
  { 1, 0, 1, 1, 0, 0, 1 }, // 4
  { 1, 1, 0, 1, 1, 0, 1}, // 5
  { 1, 1, 0, 1, 1, 1, 1}, // 6
  { 0, 1, 1, 1, 0, 0, 0}, // 7
  { 1, 1, 1, 1, 1, 1, 1 }, // 8
  { 1, 1, 1, 1, 1, 0, 1 }  // 9
};
/*bool segments[2][56] = {
  // a  b  c  d  e  f  g
  { 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1 }, // 0
  { 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1 }  // 1
};*/

void setDigit(int strip,int digit) {
  // clear all the segments
  for (byte j = 0 + 56 *(strip-1); j < 56 * 2;j++){
    leds[j] = CRGB::Black;
  }
 
  // light up the appropriate segments
  for (byte i = 0; i < 8; i++) {
    if (segments[digit][i]) { // if this LED is not lit
      for (byte j = (i * 8) * strip ; j < ((i*8)+8) * strip; j++){ // lights up all the appropriate LEDs
        leds[j] = CRGB::Red;
      }
    }
  }

 
  // update the LEDs
  FastLED.show();
}
void setup(){
  // set up the serial
  Serial.begin(9600);
  // set up the NeoPixel LEDs
  FastLED.addLeds<NEOPIXEL, 2>(leds,112);
}
void loop(){
  /*if(Serial.available()){
    int num_input = Serial.parseInt(); // stores the latest number entered into the serial
    int tens = num_input/10; // stores the digit in the tens place
    int ones = num_input % 10; // stores the digit in the ones place
    setDigit(2,ones); // sets the second strip LEDs to the digit in the ones place
    setDigit(1,tens); // sets the first strip LEDs to the digit in the tens place
  }*/
  for (int i = 0; i <= 9; i++) { // test loop that counts from zero to nine on the first strip
    //for (int j = 1; j <= 9; j++) {
      setDigit(1, i); // set the first strip to i
      for (int j = 0; j <= 9; i++) { // test loop that counts from zero to nine on the first strip
        setDigit(2, j); // set the first strip to j
      }
      delay(1000); // wait one second before switching to the next number
    }
}