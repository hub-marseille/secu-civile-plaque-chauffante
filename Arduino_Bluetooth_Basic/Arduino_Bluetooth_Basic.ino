/*
    Bluetooh Basic: LED ON OFF - Avishkar
    Coder - Mayoogh Girish
    Website - http://bit.do/Avishkar
    Download the App :
    This program lets you to control a LED on pin 13 of arduino using a bluetooth module
*/

int sensorvalue = 0;
float temperature = 0;
int color = 0;
float temp_target = 10;
char data = 0;                //Variable for storing received data
String receive = "";

void setup()
{
  Serial.begin(9600);         //Sets the data rate in bits per second (baud) for serial data transmission
  pinMode(8, OUTPUT);
  pinMode(A0, INPUT);
}

void loop()
{
  sensorvalue = analogRead(A0);
  temperature = sensorvalue * (5.0 / 1024.0);
  temperature = (temperature - 0.5) * 100;
  if (temperature < temp_target)
  {
    digitalWrite(8, HIGH);
    Serial.println("On");
  }
  else
  {
    digitalWrite(8, LOW);
    Serial.println("Off");
  }
  //Serial.println(temperature);
  while (Serial.available() > 0)
  {
    data = Serial.read();
    if (data == '\n')
    {
      temp_target = receive.toFloat();
      receive = "";
      Serial.println(temperature);
      Serial.println(temp_target);
    }
    else
    {
      receive += data;
    }
  }
}
