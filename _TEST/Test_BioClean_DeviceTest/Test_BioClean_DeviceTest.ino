#define BUTTON  10
#define PWM     13
#define RELE     7

unsigned long now = 0;
unsigned long durata = 0;
unsigned long array_durata[2] = {3000, 20000};

boolean risultato = true;
boolean check = true;

void check_durata () {
  if (risultato == true) {
    Serial.println("Scheda: (ok)");
  } else {
    Serial.println("Scheda: no!");
    check = false;
  }
}

void check_scheda () {
  if (check == true) {
    Serial.println("result OK");
  } else {
    Serial.println("result ERROR");
  }
}

//  *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON, INPUT);
  pinMode(PWM, OUTPUT);
  pinMode(RELE, INPUT_PULLUP);
}

void loop() {
     
  if (digitalRead(BUTTON) == HIGH) {
    delay(100);
    
    Serial.println("INIZIO TEST BioClean");
    Serial.println("");
    for (int i = 0; i < 2; i++) {
      durata = array_durata[i];
      now = millis();
      
      while ((millis() - now) <= durata) {
        for (int y = 0; y < 50 ; y++) {
          digitalWrite(PWM, HIGH);
          delay(50);
          if ((y == 20) || (y == 40)) {
            if (digitalRead(RELE) == 1) { risultato = false; }
          }
          digitalWrite(PWM, LOW);
          delay(50);
        }
      }
      delay(4000);
      digitalWrite(PWM, LOW);
      delay(4000);
      check_durata();
      risultato = true; //  reset risultato
      now = millis();
    }

    Serial.println("");
    check_scheda();
    //Serial.println("");
    Serial.println("______________________________");
    Serial.println("");
    risultato = true;
    check = true;
    delay(100);
  }
}
