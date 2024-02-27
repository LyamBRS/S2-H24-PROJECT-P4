#include "LCD.h"
const int 
rs = 52, // register select
en = 50, // Enable
d4 = 53, //data pins
d5 = 51,
d6 = 49,
d7 = 47;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void LCD::lcdInit(){
  lcd.begin(16, 2);
}

void LCD::print(int cursorRow, int cursorLine, char* display){
  lcd.setCursor(cursorRow, cursorLine);
  lcd.print(display);
}

bool LCD::SetNewLocalMessage(String newMessage)
{
  print(0,1,newMessage);
  return true;
}

bool LCD::SetNewPCMessage(String newMessage)
{
  print(0,0,newMessage);
  return true;
}
