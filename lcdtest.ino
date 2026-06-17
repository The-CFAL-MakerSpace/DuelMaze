#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 (or 0x3F) for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x26, 16, 2);

void setup() {
  lcd.init();                      // initialize the lcd 
  lcd.backlight();                 // turn on the backlight
  lcd.setCursor(0, 0);             // move to column 0, row 0
  lcd.print("Hello, World!");      // print a message
  lcd.setCursor(0, 1);             // move to column 0, row 1
  lcd.print("I2C LCD Working!");   // print a second message
}

void loop() {
}
