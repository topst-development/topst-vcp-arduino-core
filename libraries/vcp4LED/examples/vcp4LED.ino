/*
*  TOPST VCP : 4 LED Control
*/

int ledPin[] = {3, 5, 7, 8};
int buttonPin[] = {10};

// the setup function runs once when you press reset or power the board
void setup() {
  // LED Mode and Init 
  for(int i=0; i<4; i++)
  {
    pinMode(ledPin[i], OUTPUT);
    digitalWrite(ledPin[i], HIGH);
  }

  pinMode(buttonPin[0], INPUT);

}
  
// the loop function runs over and over again forever
void loop() {

  int button = digitalRead(buttonPin[0]);
  if(button==HIGH)
  {
    for(int i=0; i<4; i++)
    {
      digitalWrite(ledPin[i], LOW);
    }
  }
  else
  {
    for(int i=3; i>=0; i--)
    {
      digitalWrite(ledPin[i], HIGH);
    }
  }
  
  // for(int i=0; i<4; i++)
  // {
  //   digitalWrite(ledPin[i], LOW);
  //   delay(500);
  // }

  // for(int i=3; i>=0; i--)
  // {
  //   digitalWrite(ledPin[i], HIGH);
  //   delay(500);
  // }

}
