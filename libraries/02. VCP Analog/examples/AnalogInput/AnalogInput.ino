
int sensorPin = 16;
int ledPin = 3;
int sensorValue = 0;  

void setup()
{

  pinMode(ledPin, OUTPUT);

}

void loop()
{

  for(;;)
  {
    sensorValue = analogRead(sensorPin);
    if(sensorValue<3000)
    {
      digitalWrite(ledPin, LOW);
    }
    else 
    {
      digitalWrite(ledPin, HIGH);  
    }
    
    delay(10);
  }

}