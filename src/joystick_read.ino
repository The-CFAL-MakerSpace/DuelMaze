#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2); //I2c will vary from module to module. Use the I2c scanner to find the correct address of your I2c module.

const int x = A0;
const int y = A1;
const int button = 3;

    Servo s1;
//this i a porject depicting thedeath of the 
void setup() {
  // put your setup code here, to run once:
    pinMode(x, INPUT);
    pinMode(y, INPUT);
    pinMode(button, INPUT_PULLUP);
    Serial.begin(9600);
    s1.attach(9);
    lcd.init();
    lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
    lcd.setCursor(0, 0);
    lcd.print("Player 1 Time:");
    lcd.setCursor(0, 1);
    // lcd.print(millis() / 1000);
    int xval = analogRead(x);
    int yval = analogRead(y);
    int bval = digitalRead(button);

    int sval = map(xval, 0, 1023, 10, 170);
    s1.write(sval);

    Serial.print("x = ");
    Serial.print(xval);
    Serial.print(" y = ");
    Serial.print(yval);
    Serial.print(" button = ");
    Serial.println(bval);
    delay(100);
}
