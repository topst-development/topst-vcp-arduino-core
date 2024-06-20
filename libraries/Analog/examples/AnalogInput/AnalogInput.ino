#include <LiquidCrystal_I2C.h>

int sensorPin = 16;
int sensorValue = 0;  

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{

  pinMode(3, OUTPUT);

  LiquidCrystal_I2C lcd(0x27,16,2);

  lcd.init(); 
  lcd.backlight(); // initialize the lcd 

  lcd.setCursor(2, 0);
  delay(10);
  lcd.print("* TOPST VCP *");
  
  lcd.setCursor(4, 1);
  delay(10);
  lcd.print("ADC Test!");

  for(;;)
  {
    sensorValue = analogRead(sensorPin);
    if(sensorValue<3000)
    {
      digitalWrite(3, LOW);
    }
    else 
    {
      digitalWrite(3, HIGH);  
    }
    
    delay(10);
  }
}

void loop()
{

}


// int sensorPin = 4;
// int sensorValue = 0; 

// void setup() {
//   // put your setup code here, to run once:

// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   sensorValue = analogRead(sensorPin);
// }
