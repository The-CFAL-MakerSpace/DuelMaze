// Made with ♥ by MakerSpace 2024-2026

#include <Arduino.h>
#include <avr/wdt.h>
#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

volatile bool flag;
int count;
LiquidCrystal_I2C lcd1(0x26, 16, 2); // I2c will vary from module to module. Use the I2c scanner to find the correct address of your I2c module.
LiquidCrystal_I2C lcd2(0x27, 16, 2);
const int x = A0; // joystick :)
const int y = A1;
const int button = 2;      // regular button         
const int hfe = 6;        // hall effect sensor at end
const int threshold = 255; // threshold for hall effect
unsigned long time;        // variable to hold time of player
unsigned long initialtime;
const int commin = 3;
const int commout = 13;
volatile bool commflag = false;
bool oppready;
bool selfready;

Servo sx;
Servo sy;
const int xrest = 102; // rest positions of servos
const int yrest = 75;
 int xupper;
 int yupper;
 int xlower;
int ylower;
int xval;
int yval;

// void gameover();
// void gamereset();
// void gameMenu();
// void marblereset();
// void commrec();
// void pulse();
// void communicate();
void gamereset()
{
  sx.write(xrest);
  sy.write(yrest);
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print("Made By");
  lcd1.setCursor(0, 1);
  lcd1.print("MakerSpace CFAL.");
  lcd2.clear();
  lcd2.setCursor(0, 0);
  lcd2.print("Press button to");
  lcd2.setCursor(0, 1);
  lcd2.print("Start Game.");
  // while (true)
  // {
  //   if (digitalRead(button) == LOW)
  //   {
  //     lcd2.clear();
  //     lcd2.setCursor(0, 0);
  //     lcd2.print("Press button to");
  //     lcd2.setCursor(0, 1);
  //     lcd2.print("Forfeit Game.");
  //     lcd1.clear();
  //     lcd1.setCursor(0, 0);
  //     lcd1.print("Player 1 Time:");
  //     initialtime = millis();
  //     return;
  //   }
  // }
  selfready = false;
  oppready = false;
  commflag = false;
  count = 0;
  delay(1000);
}


ISR(WDT_vect)
{
  flag = true;
  wdt_enable(WDTO_1S);
  MCUSR &= ~(1 << WDRF);
  WDTCSR |= (1 << WDCE);
  WDTCSR &= ~(1 << WDE);
  WDTCSR |= (1 << WDIE);
  wdt_reset();
}

void commrec(){
  commflag = true;
}

void pulse(){
  digitalWrite(commout, HIGH);
  delay(10);
  digitalWrite(commout, LOW);
}

void gameOver(bool win, bool forfeit){

 
  if(forfeit && !win){
    pulse();
    delay(10);
    pulse();
  }
  
  if(win){
    pulse();
    lcd1.clear();
    lcd1.setCursor(0,0);
    lcd1.print("You Won!");
    lcd1.setCursor(0,1);
    lcd1.print("Your Time: ");
    lcd1.setCursor(11, 1);
    String countstring = String(count);
    lcd1.print(countstring);
      }
    else{
          lcd1.clear();
    lcd1.setCursor(0,0);
    lcd1.print("You Lost!");
    lcd1.setCursor(0,1);
    lcd1.print("Your Time: ");
    lcd1.setCursor(11, 1);
    String countstring = String(count);
    lcd1.print(countstring);
    }
    lcd2.clear();
    lcd2.setCursor(0, 0);
    lcd2.print("Press Button To");
    lcd2.setCursor(0,1);
    lcd2.print("Reset Game.");
    while (digitalRead(button)){
    }
    gamereset();
    gameMenu();
}

void gameMenu(){
   bool done = false;

  while (!done){
    sx.write(xrest);
    sy.write(yrest);
    if (!digitalRead(button) && !selfready){
      selfready = true;
      pulse();
      lcd1.clear();
      lcd1.setCursor(0,0);
      lcd1.print("You are now");
      lcd1.setCursor(0,1);
      lcd1.print("Ready to Play!");
      lcd2.clear();
      lcd2.setCursor(0,0);
      lcd2.print("Waiting for");
      lcd2.setCursor(0,1);
      lcd2.print("Opponent!");
    }
    if(commflag && !oppready){
      commflag = false;
      oppready = true;
          lcd1.clear();
      lcd1.setCursor(0,0);
      lcd1.print("Your Opponent");
      lcd1.setCursor(0,1);
      lcd1.print("Is now Ready!");
  lcd2.clear();
  lcd2.setCursor(0, 0);
  lcd2.print("Press button to");
  lcd2.setCursor(0, 1);
  lcd2.print("Start Game.");
    }
    if (selfready && oppready){
      lcd2.clear();
      lcd2.setCursor(0, 0);
      lcd2.print("Press button to");
      lcd2.setCursor(0, 1);
      lcd2.print("Forfeit Game.");
      lcd1.clear();
      lcd1.setCursor(0, 0);
      lcd1.print("Player 1 Time:");
      initialtime = millis();
      delay(1000);
      commflag = false;
      done = true;
    }
}
}

void setup()
{
  // put your setup code here, to run once:
  wdt_disable();
  EEPROM.begin();
  xupper = xrest-40;
  xlower = xrest+40;
  yupper = yrest+40;
  ylower = yrest-40;
  pinMode(x, INPUT); // set PinModes
  pinMode(y, INPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(hfe, INPUT_PULLUP);
  pinMode(commin, INPUT);
  pinMode(commout, OUTPUT);
  digitalWrite(commout, LOW);
  attachInterrupt(digitalPinToInterrupt(commin), commrec, RISING);
  int in = digitalRead(commin);
  Serial.begin(9600);
  sx.attach(10); // attach servos
  sy.attach(9);
  lcd1.init();
  lcd1.backlight();
  lcd2.init();
  lcd2.backlight();
  gamereset();
  gameMenu();


  if (in == HIGH)
  {
  }
  wdt_enable(WDTO_1S);
  MCUSR &= ~(1 << WDRF);
  WDTCSR |= (1 << WDCE);
  WDTCSR &= ~(1 << WDE);
  WDTCSR |= (1 << WDIE);
}

void loop()
{
  // put your main code here, to run repeatedly:
  Serial.println(flag);
  // check if time is exactly 1,2,3.... seconds
  if (flag == true)
  {

    lcd1.setCursor(0, 1);
    lcd1.print(count);
    count++;
    flag = false;
  }
  if(commflag){
    commflag = false;
    delay(100);
    if(commflag){
      gameOver(true, false);
    }
    else{
      gameOver(false, false);
    }

  }
  if(!digitalRead(hfe)){
    gameOver(true, false);
  }
  if(!digitalRead(button)){
    gameOver(false,true);
  }
 
  
  xval = analogRead(x);
  yval = analogRead(y);
  int bval = digitalRead(button);
  int hfeval = digitalRead(hfe);
  // if (hfeval > threshold)
  // {
  //   while (true)
  //   {
  //     unsigned long initaltime = millis();
  //     lcd1.clear();
  //     lcd1.setCursor(0, 0);
  //     lcd1.print("G");
  //     lcd1.print("");
  //   }
  // }
  int servoxval = map(xval, 0, 1023, xlower, xupper);
  sx.write(servoxval);
  int servoyval = map(yval, 0, 1023, ylower, yupper);
  sy.write(servoyval);
  Serial.print("x = ");
  Serial.print(servoxval);
  Serial.print(" y = ");
  Serial.print(servoyval);
  Serial.print(" button = ");
  Serial.println(bval);
}

