#include <LiquidCrystal.h>

LiquidCrystal monEcran(12, 11, 7, 6, 5, 4);

String receive = "";
int i;
const int buzzer = 8;
float radiations = 0.1;
char data = 0;                //Variable for storing received data
bool lastState[2];

void setup() {
  monEcran.begin(16, 2);
  monEcran.clear();
  monEcran.print("Radiations :");
  pinMode(buzzer, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  Serial.begin(9600);
  lastState[0] = false;
  lastState[1] = false;
}

void loop() {
  while (Serial.available() > 0)
  {
    data = Serial.read();
    if (data == '\n')
    {
      radiations = receive.toFloat();
      if (radiations < 0.2)
        radiations = 0.2;
      receive = "";
    }
    else
    {
      receive += data;
    }
  }
  if (digitalRead(2) == LOW) //boutton appuyé
  {
    if (lastState[0] == false)
      Serial.println("0");
    lastState[0] = true;
  }
  else
    lastState[0] = false;
  if (digitalRead(3) == LOW) //boutton appuyé
  {
    if (lastState[1] == false)
      Serial.println("1");
    lastState[1] = true;
  }
  else
    lastState[1] = false;
  digitalWrite(10, HIGH);
  if (radiations >= 0.3)
    tone(buzzer, 1000);
  delay(100 / radiations);
  noTone(buzzer);
  digitalWrite(10, LOW);
  delay(40 / radiations);
  monEcran.setCursor(0, 1);
  monEcran.print(radiations);
  monEcran.print(" µSv/h");
}
