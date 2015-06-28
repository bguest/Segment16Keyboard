/*
  LiquidCrystal Library - Serial Input

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch displays text sent over the serial port
 (e.g. from the Serial Monitor) on an attached LCD.

 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 7
 * LCD D5 pin to digital pin 6
 * LCD D6 pin to digital pin 5
 * LCD D7 pin to digital pin 4
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://arduino.cc/en/Tutorial/LiquidCrystalSerial
 */

// include the library code:
#include <PS2Keyboard.h>

const int DataPin = 3;
const int IRQpin =  2;

PS2Keyboard keyboard;

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

uint8_t cursorX = 0;
uint8_t cursorY = 0;
char incomingByte;

#define SCREEN_WIDTH 20
#define SCREEN_HEIGHT 4

void setup() {
  delay(1000);
  keyboard.begin(DataPin, IRQpin);
  // set up the LCD's number of columns and rows:
  lcd.begin(SCREEN_WIDTH, SCREEN_HEIGHT);
  // initialize the serial communications:
  Serial.begin(9600);
}

void loop()
{

  // Read from keyboard and put to Serial1
  while (keyboard.available() > 0){
    if(keyboard.available() > 0){
      incomingByte = keyboard.read()
      Serial.write(incomingByte);
    }
  }

  while (Serial.available() > 0) {
    if(cursorX == 0 && cursorY == 0){
      lcd.clear();
    }
    // display each character to the LCD
    if(Serial.available() > 0){
      incomingByte = Serial.read();
    }
    if(incomingByte == 13){
      cursorX = 0;
      cursorY++;
    }else if(incomingByte == 127){
      cursorX--;
      lcd.setCursor(cursorX, cursorY);
      lcd.write(" ");
    }else{
      lcd.setCursor(cursorX, cursorY);
      lcd.write(incomingByte);
      cursorX++;
    }
    //Serial.print(incomingByte);

    if(cursorX >= SCREEN_WIDTH){
      cursorX = 0;
      cursorY++;
      cursorY = cursorY % SCREEN_HEIGHT;
    }
  }

}
