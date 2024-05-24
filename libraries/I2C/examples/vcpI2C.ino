#include <SWire.h>
#include <LiquidCrystal_I2C.h>

uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
  
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  LiquidCrystal_I2C lcd(0x27,16,2);

  lcd.init(); 
  lcd.backlight();
  // delay(100);
  // lcd.noBacklight();
  // delay(100);                     // initialize the lcd 
  lcd.setCursor(0, 0);
  lcd.cursor();
  //lcd.blink();
  delay(1000);
  // delay(1000);
  lcd.createChar(0, heart);
  // lcd.home();
}

void loop()
{  

}



// #include "SWire.h"
// #include "LiquidCrystal_I2C.h"

// void setup() {
//   // put your setup code here, to run once:
//   SWire.begin();
//   SWire.beginTransmission(0x27);
//   // SWire.write(0x01);
//   // SWire.write(0xC6);
//   // SWire.write(0x10);
// }

// void loop() {
//   // put your main code here, to run repeatedly:


// }





