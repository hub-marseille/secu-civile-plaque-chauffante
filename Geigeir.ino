#include <LiquidCrystal.h>

LiquidCrystal monEcran(12,11,5,4,3,2);

char recu[20];
String reponse;
int i;
float radiations = 10;

void setup(){
      monEcran.begin(16,2);
      monEcran.clear();
      monEcran.print("Radiations (Bq):");
      monEcran.setCursor(0,1);
      pinMode(8, OUTPUT);
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
        radiations = reponse.toFloat();
      } 
      i = 0;
            monEcran.setCursor(0,1);
            monEcran.print(radiations);
            Serial.println(radiations); 
            tone(9, 1000); 
            digitalWrite(10, HIGH);
            delay(1000);
            digitalWrite(10, LOW);
            noTone(9);
            reponse = ""; 
}
