#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.


SoftwareSerial chipSerial(7, 8); // RX, TX  
// Connect HM10      Arduino Uno
//     Pin 1/TXD          Pin 7
//     Pin 2/RXD          Pin 8

void setup() {  
  Serial.begin(9600);
  // If the baudrate of the HM-10 module has been updated,
  // you may need to change 9600 by another value
  // Once you have found the correct baudrate,
  // you can update it using AT+BAUDx command 
  // e.g. AT+BAUD0 for 9600 bauds
  chipSerial.begin(9600);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

// To send data via serial, use chipSerial.print(c);
// Refer to https://www.arduino.cc/en/Tutorial/ReadASCIIString

void loop() {  
  char c;
  if (Serial.available()) {
    c = Serial.read();

    if(c == 'r') {
      Serial.print("It's Red!\n\n");
      colorWipe(strip.Color(255, 0, 0), 50); // Red
    }
    if(c == 'g') {
      Serial.print("It's Green!\n\n");
      colorWipe(strip.Color(0, 255, 0), 50); // Green
    }
    if(c == 'b') {
      Serial.print("It's Blue!\n\n");
      colorWipe(strip.Color(0, 0, 255), 50); // Blue
    }
    chipSerial.print(c);
  }
//  if (chipSerial.available()) {
//    c = chipSerial.read();
//    Serial.print(c);    
//  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}


