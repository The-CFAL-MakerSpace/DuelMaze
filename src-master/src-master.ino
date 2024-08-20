//Made with ♥ by MakerSpace 2024-2026

#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); //I2c will vary from module to module. Use the I2c scanner to find the correct address of your I2c module.
// LCD Goes to A4 and A5

const int x = A0;  //joystick :)
const int y = A1;  
const int jbutton = 5;  //joystick button
const int button = 6;    // regular button
const int hfs = 5;       // hall effect sensor at start (hf -> hall-effect, s-> start)
const int hfe = 6;      //hall effect sensor at end
const int threshold = 255; //threshold for hall effect
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

unsigned long startTime;  // variable to hold start time of player
unsigned long elapsedTime;  // variable to hold elapsed time

// READ THIS: im gonna change the timing system later, this is rudimentary

bool gameStarted = false;
 
void gamestart() {
    gameStarted = true;
    startTime = millis();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Player 1 Time:");
}

void gameover(bool winner = false) {
    gameStarted = false;
    sx.write(xrest);
    sy.write(yrest);
    lcd.clear();
    if (winner) {
        lcd.setCursor(0, 0);
        lcd.print("You Win!");
        digitalWrite(commout, HIGH);  // signal the other board that player 1 won
    } else {
        lcd.setCursor(0, 0);
        lcd.print("You Lose!");
    }
    delay(3000);  // wait for 3 seconds
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Press button to");
    lcd.setCursor(0, 1);
    lcd.print("Start Game.");
}

void marblereset(){
  //trial 'n' error bois
  //once shitty complicated code done,
  gameover();
}




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
    sy.attach(10);
    lcd.init();     
    lcd.backlight();

    if(analogRead(hfs) > threshold){
      gameover();  //main menu
    }
    else{
      marblereset();  //bring marble to start, if not already
    }
}

void loop() {
if (!gameStarted) {
        if (digitalRead(jbutton) == LOW) {
            gamestart();
        }
    } else {
        elapsedTime = millis() - startTime;
        updateDisplay();
        
        int xval = analogRead(x);
        int yval = analogRead(y);
        
        int xvalMapped = map(xval, 0, 1023, xlower, xupper);
        int yvalMapped = map(yval, 0, 1023, ylower, yupper);
        
        sx.write(xvalMapped);
        sy.write(yvalMapped);
        
        Serial.print("x = ");
        Serial.print(xvalMapped);
        Serial.print(" y = ");
        Serial.print(yvalMapped);
        
        if (analogRead(hfe) > threshold) {
            gameover(true);
        }
    }
}

void updateDisplay() {
    if (elapsedTime % 1000 == 0) {  // update every second [THIS IS WHAT WE NEED TO CHANGE LATER]
        lcd.setCursor(0, 1);
        lcd.print(elapsedTime / 1000);
    }
}



