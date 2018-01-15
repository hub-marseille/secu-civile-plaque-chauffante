/* 
 *  Bluetooh Basic: LED ON OFF - Avishkar
 *  Coder - Mayoogh Girish
 *  Website - http://bit.do/Avishkar
 *  Download the App : 
 *  This program lets you to control a LED on pin 13 of arduino using a bluetooth module
 */

int sensorvalue = 0;
float temperature = 0;
int color = 0;
int temp_target = 25;
int data = 0;                //Variable for storing received data
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
    digitalWrite(8, HIGH);
  else
    digitalWrite(8, LOW);

 while (Serial.available() > 0) {
  if (color != 'R' || receive.length() == 3)
  {
    color = Serial.read();
    receive = "";

  }
  else if (color == 'R') {
    data = Serial.read();
    receive = receive + char(data);
    if (receive.length() == 3)
    {
      temp_target = map(receive.toInt(), 0, 256, 20, 60);
      Serial.println("value:          " + receive);
        Serial.print(temperature);
  Serial.print(" ");
  Serial.print(color);
  Serial.print(" ");
  Serial.println(temp_target);
    }
  }
  else
    Serial.read();
 }
}       
