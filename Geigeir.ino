#include <LiquidCrystal.h>

LiquidCrystal monEcran(12,11,7,6,5,4);

char recu[20];
String reponse;
int i;
const int buzzer = 8;
float radiations = 10;

void setup(){
      monEcran.begin(16,2);
      monEcran.clear();
      monEcran.print("Radiations (Bq):");
      monEcran.setCursor(0,1);
      pinMode(buzzer, OUTPUT);
      pinMode(10, OUTPUT);
      Serial.begin(9600);
      }

void loop() {
      monEcran.setCursor(0,1);
      while ( Serial.available()>0 ) {
            monEcran.setCursor(0,1);
            recu[i] = Serial.read();
            reponse += recu[i];
            i++;
      }
      if (i > 0) {
            digitalWrite(10, HIGH);
            tone(buzzer, 1000);
            delay(1000);
            noTone(buzzer);
            digitalWrite(10, LOW);
        radiations = reponse.toFloat();
      } 
      i = 0;
            monEcran.setCursor(0,1);
            monEcran.print(radiations);
            Serial.println(radiations); 
            reponse = ""; 
}
