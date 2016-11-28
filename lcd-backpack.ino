#include "Arduino.h"

#if defined(ARDUINO_ARCH_SAMD) || defined(__SAM3X8E__)
  // use pin 18 with Due, pin 1 with Zero or M0 Pro 
  #define lcd Serial1 
#else
  #include <SoftwareSerial.h>
  // Create a software serial port!
  SoftwareSerial lcd = SoftwareSerial(0,2);
#endif

// for ESP8266 use this SoftwareSerial library: https://github.com/plerup/espsoftwareserial

const int lunchPin = 3;  // The GPIO number of the out to lunch button.
int lunchButtonState = LOW; // Variable for reading the lunch button status
boolean buttonPressed = false;
String clearMessage = String("What's up STUD!!");

void setup() {
  pinMode(lunchPin, INPUT_PULLUP);
  //digitalWrite(lunchPin, HIGH);       // turn on pullup resistors
  lcd.begin(9600);  
  
  // set the size of the display if it isn't 16x2 (you only have to do this once)
  lcd.write(0xFE);
  lcd.write(0xD1);
  lcd.write(16);  // 16 columns
  lcd.write(2);   // 2 rows
  delay(10);       
  // we suggest putting delays after each command to make sure the data 
  // is sent and the LCD is updated.
  
  clearScreen();  // Set the initial message
  delay(1000);
}

void loop() {

  lunchButtonState = digitalRead(lunchPin);
  
  // if button was pressed
  if(buttonPressed == false && lunchButtonState == LOW) {
    displayLunchMessage();
    buttonPressed = true;
    delay(200);
  } else if(buttonPressed == true && lunchButtonState == LOW) {
    clearScreen();
    buttonPressed = false;
    delay(200);
  }
}

// Sets the out to lunch message
void displayLunchMessage() {
 // clear screen
  lcd.write(0xFE);
  lcd.write(0x58);
  delay(10);
  
 // go 'home'
  lcd.write(0xFE);
  lcd.write(0x48);
  delay(10);
  
  lcd.print("Out to Lunch");
  red();
}

// Sets the screen back to the original message
void clearScreen() {
  // clear screen
  lcd.write(0xFE);
  lcd.write(0x58);
  delay(10);
  
  // go 'home'
  lcd.write(0xFE);
  lcd.write(0x48);
  delay(10);
  
  lcd.print(clearMessage);
  blue();
}

// Set the display color to red
void red() {
  lcd.write(0xFE);
  lcd.write(0xD0);
  lcd.write(255); 
  lcd.write((uint8_t)0);
  lcd.write(1);
  delay(10);
}

// Set the display color to blue
void blue() {
  lcd.write(0xFE);
  lcd.write(0xD0);
  lcd.write((uint8_t)0);
  lcd.write(255); 
  lcd.write(255); 
  //lcd.write(1);
  delay(10);
}
