# Just some rough code to test during the session:


```

    // Check if the marble has started
    if (hfsval == HIGH) {  // Start sensor detects the marble
        // Start tracking time from when marble leaves the start
        time = millis();
    }

    // Check if the other player has won
    if (lost == true) {
        gameover(false);  // You lose if the other player wins
    }
    // Check if the current player has won
    else if (hfeval == HIGH) {  // End sensor detects the marble
        gameover(true);  // Current player wins
    }

    // Show player time on the LCD every second
    unsigned long elapsed = millis() - time;
    if (elapsed % 1000 == 0) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Player 1 Time:");
        lcd.setCursor(0, 1);
        lcd.print(elapsed / 1000);  // Display time in seconds
    }

    // Control maze movement with joystick
    xval = map(xval, 0, 1023, xlower, xupper);
    sx.write(xval);
    yval = map(yval, 0, 1023, ylower, yupper);
    sy.write(yval);

    Serial.print("x = ");
    Serial.print(xval);
    Serial.print(" y = ");
    Serial.print(yval);
    Serial.print(" button = ");
    Serial.println(bval);
}
```

## COM Func:
```
void communicate() {
    lost = true;  // Other player has won
}
```

## GMOVR:
```
void gameover(bool outcome) {
    lcd.clear();
    if (outcome == true) {
        lcd.setCursor(0, 0);
        lcd.print("You Win!");
        digitalWrite(commout, LOW);  // Notify the other player that they lost
    } else {
        lcd.setCursor(0, 0);
        lcd.print("You Lose.");
    }
    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    lcd.print((millis() - time) / 1000);  // Display final time
    while (true);  // Freeze the game, wait for reset
}
```