//Made with ♥ by MakerSpace 2024-2026


#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); //I2c will vary from module to module. Use the I2c scanner to find the correct address of your I2c module.

const int x = A0;  //joystick :)
const int y = A1;  
const int jbutton = 5;  //joystick button
const int button = 2;    // regular button
const int hfs = 5;       // hall effect sensor at start (hf -> hall-effect, s-> start)
const int hfe = 6;      //hall effect sensor at end
const int threshold = 255;
const int servoxpin = 9;
const int servoypin = 10;  //threshold for hall effect
unsigned long time;  //variable to hold time of player
const int commin = 3;
const int commout = 4;

Servo sx; 
Servo sy;
const int xrest = 90;  //rest positions of servos
const int yrest = 90;
const int xupper = 170;
const int yupper = 170;
const int xlower = 10;
const int ylower = 10;

void marblereset();
void gamereset();
void gameover(bool outcome);
void communicate();

bool lost;

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
    attachInterrupt(digitalPinToInterrupt(commin), communicate, FALLING);
    bool in = digitalRead(commin);
    Serial.begin(9600);
    sx.attach(servoxpin);  //attach servos
    sy.attach(servoypin);
    lcd.init();     
    lcd.backlight();
    // check if marble is at start point, act appropriately
    if(analogRead(hfs) > threshold){
      gamereset();  //main menu
    }
    else{
      marblereset();  //bring marble to start, if not already
    }
}

void loop() {
    int xval = analogRead(x);
    int yval = analogRead(y);
    int bval = digitalRead(button);
    int hfeval = analogRead(hfe);
    //check if the other player has won the game.
    if (lost == true){
      gameover(false);
    }
    else if(hfeval > threshold){
      gameover(true);
    }
    time = millis();  
    //check if time is exactly 1,2,3.... seconds
    if(time%1000 == 0)  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Player 1 Time:");
    lcd.setCursor(0, 1);
    lcd.print(time/1000);
    }
    //dont waste any more precious cycles and move the maze...
    xval = map(xval, 0, 1023, xlower, xupper);
    sx.write(xval);
    yval = map(xval, 0, 1023, ylower, yupper);
    sy.write(yval);
    Serial.print("x = ");
    Serial.print(xval);
    Serial.print(" y = ");
    Serial.print(yval);
    Serial.print(" button = ");
    Serial.println(bval);
}

void gamereset(){
  sx.write(xrest);
  sy.write(yrest);
  lcd.clear();
  lcd.setCursor(0, 0);
  unsigned long initialtime = millis();
  bool flippy;
  while(true){
    time = millis()-initialtime;
    delay(1);
    if (time>2000){
      lcd.clear();
      lcd.setCursor(0,0);
      if (flippy){
        lcd.print("DuelMaze:Welcome!");
        lcd.setCursor(0,1);
        lcd.print("Ready to Roll?");
      }
      else{
    lcd.print("Press button to");
    lcd.setCursor(0, 1);
    lcd.print("Start Game.");
      }
      flippy = !flippy;
      initialtime = millis();
    }
    if(digitalRead(button)==LOW){
      return;
    }
  }
}

void gameover(bool outcome){

}


void marblereset(){
  //trial 'n' error bois
  //once shitty complicated code done,
  gamereset();
}

void communicate(){

}