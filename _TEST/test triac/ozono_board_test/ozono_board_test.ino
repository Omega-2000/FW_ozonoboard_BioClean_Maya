#include "PIN_CONFIG.h"
#include "VAR_CONFIG.h"


void setup() {
  Serial.begin(9600);
  pinMode(OUT, OUTPUT);
  pinMode(R1, INPUT_PULLUP);
  pinMode(R2, INPUT_PULLUP);
  pinMode(R3, INPUT_PULLUP);
  pinMode(R4, INPUT_PULLUP);
  pinMode(R5, INPUT_PULLUP);
  pinMode(R6, INPUT_PULLUP);
  pinMode(R7, INPUT_PULLUP);
  pinMode(R8, INPUT_PULLUP);
  pinMode(BUTTON, INPUT);
}


void loop() {
  if(digitalRead(BUTTON) == HIGH){
    stato = HIGH;
  } else {
    stato = LOW; 
  }
     
  if (stato == HIGH) {
    delay(3000);
    now = millis();
    Serial.println("INIZIO TEST ozono board");
    Serial.println("");
    for (int i = 0; i < 4; i++) {
      durata = array_durata[i];
      Serial.print("__________pwm_");
      Serial.print(i+1);
      Serial.print(" (");
      if (durata < 60000) {
        Serial.print(durata/1000);
        Serial.print("secondi");
      } else {
        Serial.print(durata/60000);
        Serial.print("minuti");
      }
      Serial.println(")");
      delay(1000);
      
      while ((millis() - now) <= durata) {
          for (int y = 0; y < 50 ; y++) {
            digitalWrite(OUT, HIGH);
            delay(50);
            if ((y == 20) || (y == 40)) {
              check_while();  
            }
            digitalWrite(OUT, LOW);
            delay(50);
          }
      }
      delay(4000);
      digitalWrite(OUT, LOW);
      delay(4000);
      check_durata();
      reset_ris();
      now = millis();
    }

    Serial.println("__________risultati");
    check_scheda();
    Serial.println("");
    Serial.println("TEST COMPLETATO");
    Serial.println("");
    Serial.println("______________________________");
    Serial.println("");
    reset_var();
    delay(3000);
  }
}
