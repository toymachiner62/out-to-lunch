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
int arrayCounter = 0;

void setup() {
  pinMode(lunchPin, INPUT_PULLUP);
  lcd.begin(9600);  
  
  // set the size of the display if it isn't 16x2 (you only have to do this once)
  lcd.write(0xFE);
  lcd.write(0xD1);
  lcd.write(16);  // 16 columns
  lcd.write(2);   // 2 rows
  delay(10);       
}

void loop() {

  lunchButtonState = digitalRead(lunchPin);

  // If the button is pressed
  if(lunchButtonState == LOW) {
    //clearScreen();
    displayMessage();  // Reset the text on the screen
    setColor(arrayCounter);

    // Once we're at the end of our messages we need to loop them again
    if(arrayCounter > 3) {
      arrayCounter = 0;
    } else {
      arrayCounter++; // Increment the counter
    }
    delay(200);
  }
}

// Sets the message
void displayMessage() {
  // clear screen
  lcd.write(0xFE);
  lcd.write(0x58);
  delay(10);
  
  // go 'home'
  lcd.write(0xFE);
  lcd.write(0x48);
  delay(10);
}

// Sets the color of the screen
void setColor(int counter) {
  switch(counter) {
    case 0:
      blue();
      lcd.print("What's up Stud!!");
      break;
    case 1:
      red();
      lcd.print("Out to Lunch");
      break;
    case 2:
      purple();
      lcd.print("On a Call");
      break;
    case 3:
      orange();
      lcd.print("In a Meeting");
      break;
    case 4:
      green();
      lcd.print("Out of Office");
      break;
  }
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

// Set the display color to blue
void purple() {
  lcd.write(0xFE);
  lcd.write(0xD0);
  lcd.write(175);
  lcd.write(1); 
  lcd.write(175); 
  //lcd.write(1);
  delay(10);
}

// Set the display color to blue
void orange() {
  lcd.write(0xFE);
  lcd.write(0xD0);
  lcd.write(255);
  lcd.write(120); 
  lcd.write(1); 
  //lcd.write(1);
  delay(10);
}

// Set the display color to blue
void green() {
  lcd.write(0xFE);
  lcd.write(0xD0);
  lcd.write(255);
  lcd.write(200); 
  lcd.write((uint8_t)0); 
  //lcd.write(1);
  delay(10);
}
