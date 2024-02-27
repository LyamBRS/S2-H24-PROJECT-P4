#include <Arduino.h>
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//const int rs = 34, en = 32, d4 = 30, d5 =28, d6 = 26, d7 = 24;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


#include "Application.h"
#include "BarGraph.h"

Application application();

 // Initialize your BarGraph with the appropriate pin numbers
BarGraph myBarGraph(44, 38, 40, 36, 42, 45, 43, 41, 39, 37);

void testBarGraph() {
  Serial.println("LOOP");

  for(int i = 0; i < 1024; i++)
  {
    Serial.println(i);
    myBarGraph.SetBits(i);
    myBarGraph.Update();
    delay(10); // Wait for 1 second
  }
  delay(1000);
  Serial.println("FlipAll");
  myBarGraph.FlipAll();
  myBarGraph.Update();
  delay(1000);
  Serial.println("FlipAll");
  myBarGraph.FlipAll();
  myBarGraph.Update();
  delay(1000);
  Serial.println("SetBits");
  myBarGraph.SetBits(0b0101010101010101);
  myBarGraph.Update();
  delay(1000);
  Serial.println("SetBits");
  myBarGraph.SetBits(0b1010101010101010);
  myBarGraph.Update();
  delay(1000);
  Serial.println("SetIndividualState");
  myBarGraph.SetIndividualState(0,true);
  myBarGraph.SetIndividualState(1,true);
  myBarGraph.SetIndividualState(2,true);
  myBarGraph.SetIndividualState(3,true);
  myBarGraph.SetIndividualState(4,true);
  myBarGraph.SetIndividualState(5,false);
  myBarGraph.SetIndividualState(6,false);
  myBarGraph.SetIndividualState(7,false);
  myBarGraph.SetIndividualState(8,false);
  myBarGraph.SetIndividualState(9,false);
  myBarGraph.Update();
  delay(1000);
  Serial.println("FlipAll");
  myBarGraph.FlipAll();
  myBarGraph.Update();
  delay(1000);
  Serial.println("TurnAllOn");
  myBarGraph.TurnAllOn();
  myBarGraph.Update();
  delay(1000);
  Serial.println("TurnAllOff");
  myBarGraph.TurnAllOff();
  myBarGraph.Update();  
}



void setup() {
  // set up the LCD's number of columns and rows:
  //lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");
  Serial.begin(115200); // Démarre la communication série à 9600 bauds
  Serial.println("HERE");
  testBarGraph();
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
  //Serial.println("LOOP");
}

