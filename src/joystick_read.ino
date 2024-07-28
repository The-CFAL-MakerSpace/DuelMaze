//Made with ♥ by MakerSpace 2024-2026

#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2); //I2c will vary from module to module. Use the I2c scanner to find the correct address of your I2c module.

const int x = A0;  //joystick :)
const int y = A1;  
const int jbutton = 3;  //joystick button
const int button = 4;    // regular button
const int hfs = 5;       // hall effect sensor at start (hf -> hall-effect, s-> start)
const int hfe = 6;      //hall effect sensor at end
const int threshold = 255; //threshold for hall effect
unsigned long time;  //variable to hold time of player
const int commin = 12;
const int commout = 13;

Servo sx; 
Servo sy;
const int xrest = 90;  //rest positions of servos
const int yrest = 90;
const int xupper = 170;
const int yupper = 170;
const int xlower = 10;
const int ylower = 10;

//this i a porject depicting thedeath of the 
void setup() {
  // put your setup code here, to run once:
    pinMode(x, INPUT);  //set PinModes
    pinMode(y, INPUT);
    pinMode(button, INPUT_PULLUP);
    pinMode(jbutton, INPUT_PULLUP);
    pinMode(hfe, INPUT);
    pinMode(hfs, INPUT);
    pinMode(commin, INPUT_PULLUP);
    pinMode(commout, OUTPUT);
    int in = digitalRead(commin);
    Serial.begin(9600);
    sx.attach(9);  //attach servos
    sy.attach(8);
    lcd.init();     
    lcd.backlight();
    if (in ==   HIGH){

    }
    // check if marble is at start point, act appropriately
    if(analogRead(hfs) > threshold){
      gameover();  //main menu
    }
    else{
      marblereset();  //bring marble to start, if not already
    }
}

void loop() {
  // put your main code here, to run repeatedly:
    time = millis();  
    //check if time is exactly 1,2,3.... seconds
    if(time%1000 == 0)  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Player 1 Time:");
    lcd.setCursor(0, 1);
    lcd.print(time/1000)
    }
    int xval = analogRead(x);
    int yval = analogRead(y);
    int bval = digitalRead(button);
    int hfeval = analogRead(hfe);
    if(hfeval> threshold){
      while true
      unsigned long initaltime = millis();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("G")
      lcd.print("")
    }
    int xval = map(xval, 0, 1023, xlower, xupper);
    sx.write(xval);d
    int yval = map(xval, 0, 1023, ylower, yupper);
    sy.write(yval);
    Serial.print("x = ");
    Serial.print(xval);
    Serial.print(" y = ");
    Serial.print(yval);
    Serial.print(" button = ");
    Serial.println(bval);
    

}

void gameover{
  sx.write(xrest);
  sy.write(yrest);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press button to");
  lcd.setCursor(0, 1);
  lcd.print("Start Game.");
  while(true){
    if(digitalRead(button)==LOW){
      gamestart();
    }
  }
}

void marblereset(){
  //trial 'n' error bois
  //once shitty complicated code done,
  gameover();
}

void 
