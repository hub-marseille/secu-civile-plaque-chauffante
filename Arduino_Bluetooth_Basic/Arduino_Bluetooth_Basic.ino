
int sensorvalue1 = 0;
int sensorvalue2 = 0;
float temperature1 = 0;
float temperature2 = 0;
int color = 0;
float temp_target = 20;
char data = 0;                //Variable for storing received data
String receive = "";

void setup()
{
  Serial.begin(9600);         //Sets the data rate in bits per second (baud) for serial data transmission
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void loop()
{
  sensorvalue1 = analogRead(A0);
  temperature1 = sensorvalue1 * (5.0 / 1024.0);
  temperature1 = (temperature1 - 0.5) * 100;
  if (temperature1 < temp_target)
    digitalWrite(8, HIGH);
  else
    digitalWrite(8, LOW);  
  sensorvalue2 = analogRead(A1);
  temperature2 = sensorvalue2 * 5.0 / 1024.0;
  temperature2 = temperature2 * 100;
  if (temperature2 < temp_target)
    digitalWrite(9, HIGH);
  else
    digitalWrite(9, LOW);
  while (Serial.available() > 0)
  {
    data = Serial.read();
    if (data == '\n')
    {
      temp_target = receive.toFloat();
      receive = "";
    }
    else
    {
      receive += data;
    }
  }
}
