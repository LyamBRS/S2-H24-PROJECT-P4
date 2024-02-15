#include <Arduino.h>
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 34, en = 32, d4 = 30, d5 =28, d6 = 26, d7 = 24;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}

#include "BarGraph.h"

void setup() {
  Serial.begin(9600); // Démarre la communication série à 9600 bauds

  // Initialize your BarGraph with the appropriate pin numbers
  BarGraph myBarGraph(44, 38, 40, 36, 42, 37, 39, 41, 43, 45);

  for(int i = 0; i < 10, i++){
    // Test individual LED control
    Serial.println("Turning on the first LED...");
    myBarGraph.SetIndividualState(i, true); // Turn on the first LED
    delay(1000); // Wait for 1 second

    Serial.println("Turning off the first LED...");
    myBarGraph.SetIndividualState(i, false); // Turn off the first LED
    delay(1000); // Wait for 1 second
  }
 
  // Test turning all LEDs on and off
  Serial.println("Turning all LEDs on...");
  myBarGraph.TurnAllOn(); // Turn on all LEDs
  delay(1000); // Wait for 1 second

  Serial.println("Turning all LEDs off...");
  myBarGraph.TurnAllOff(); // Turn off all LEDs
  delay(1000); // Wait for 1 second

  Serial.println("Turning on the first LED...");
  myBarGraph.SetIndividualState(0, true); // Turn on the first LED
  delay(1000); // Wait for 1 second

  // Test flipping all LEDs
  Serial.println("Flipping all LEDs...");
  myBarGraph.FlipAll(); // Flip the state of all LEDs
  delay(1000); // Wait for 1 second

  Serial.println("Flipping all LEDs again...");
  myBarGraph.FlipAll(); // Flip the state of all LEDs again
  delay(1000); // Wait for 1 second

  Serial.println("Turning off the first LED...");
  myBarGraph.SetIndividualState(0, false); // Turn off the first LED
  delay(1000); // Wait for 1 second

  // Test updating the LEDs based on a bit pattern
  Serial.println("Setting a bit pattern and updating LEDs...");
  myBarGraph.SetBits(0b1010101010); // Set a bit pattern
  myBarGraph.Update(); // Update the LEDs based on the new bit pattern
}
