#include <LiquidCrystal.h>

LiquidCrystal monEcran(12,11,7, 6, 5, 4);

int sensorvalue = 0;
float temperature = 0;
int color = 0;
float temp_target = 10;
char data = 0;                //Variable for storing received data
String receive = "";

void setup()
{
   monEcran.begin(16,2);
  monEcran.clear();
  monEcran.print("Actuelle | Cible");
  monEcran.setCursor(0,1);
  Serial.begin(9600);         //Sets the data rate in bits per second (baud) for serial data transmission
  pinMode(8, OUTPUT);
  pinMode(A0, INPUT);
}

void loop()
{
  sensorvalue = analogRead(A0);
  temperature = sensorvalue * (5.0 / 1024.0);
  temperature = (temperature - 0.5) * 100;
  monEcran.setCursor(0,1);
  monEcran.print(temperature, BIN);
  if (temperature < temp_target)
    digitalWrite(8, HIGH);
  else
    digitalWrite(8, LOW);
  //Serial.println(temperature);
  while (Serial.available() > 0)
  {
    data = Serial.read();
    if (data == '\n')
    {
      temp_target = receive.toFloat();
      receive = "";
      monEcran.setCursor(12,1);
      monEcran.print(temp_target);
    }
    else
    {
      receive += data;
    }
  }
}
