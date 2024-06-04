volatile int stato = LOW;
unsigned long now = 0;
unsigned long durata = 0;
unsigned long array_durata[4] = {/*4sec*/2000, /*10sec*/4000, /*4sec*/8000, /*20sec*/2000};             //1 minuto(e 40 circa)
//unsigned long array_durata[5] = {/*10min*/600000, /*5min*/300000, /*30min*/1800000, /*1min*/60000, /*10min*/600000};  //1 ora
//unsigned long array_durata[5] = {60000, 120000, 30000, 120000, 60000};

boolean ris_1 = true;
boolean ris_2 = true;
boolean ris_3 = true;
boolean ris_4 = true;
boolean ris_5 = true;
boolean ris_6 = true;
boolean ris_7 = true;
boolean ris_8 = true;

boolean check_1 = true;
boolean check_2 = true;
boolean check_3 = true;
boolean check_4 = true;
boolean check_5 = true;
boolean check_6 = true;
boolean check_7 = true;
boolean check_8 = true;


void reset_var () {
  stato = LOW;
  
  ris_1 = true;
  ris_2 = true;
  ris_3 = true;
  ris_4 = true;
  ris_5 = true;
  ris_6 = true;
  ris_7 = true;
  ris_8 = true;

  check_1 = true;
  check_2 = true;
  check_3 = true;
  check_4 = true;
  check_5 = true;
  check_6 = true;
  check_7 = true;
  check_8 = true;
}


void reset_ris() {
  ris_1 = true;
  ris_2 = true;
  ris_3 = true;
  ris_4 = true;
  ris_5 = true;
  ris_6 = true;
  ris_7 = true;
  ris_8 = true;
}


/*
//-------------------------------------------------- funzioni per prova 1 relè
void check_while_0 () {
  if (digitalRead(0) == 1) {
    ris_1 = false;
  }
}

void check_durata_0 () {
  if (ris_1 == true) {
    Serial.println("Scheda_0: 0");
  } else {
    Serial.println("Scheda_0: 1");
    check_1 = false;
  }
}

void check_scheda_0 () {
  if (check_1 == true) {
    Serial.println("Scheda_0 --> OK");
  } else {
    Serial.println("Scheda_0 --> NO!!!");
  }
}
//--------------------------------------------------
*/

void check_while() {
  //1
  if (digitalRead(R1) == 1) {
    ris_1 = false;
  }
  //2
  if (digitalRead(R2) == 1) {
    ris_2 = false;
  }
  //3
  if (digitalRead(R3) == 1) {
    ris_3 = false;
  }
  //4
  if (digitalRead(R4) == 1) {
    ris_4 = false;
  }
  //5
  if (digitalRead(R5) == 1) {
    ris_5 = false;
  }
  //6
  if (digitalRead(R6) == 1) {
    ris_6 = false;
  }
  //7
  if (digitalRead(R7) == 1) {
    ris_7 = false;
  }
  //8
  if (digitalRead(R8) == 1) {
    ris_8 = false;
  }
}


void check_durata() {
  //1
  if (ris_1 == true) {
    Serial.println("Scheda 1: 0 (ok)");
  } else {
    Serial.println("Scheda 1: 1 (!)");
    check_1 = false;
  }
  //2
  if (ris_2 == true) {
    Serial.println("Scheda 2: 0 (ok)");
  } else {
    Serial.println("Scheda 2: 1 (!)");
    check_2 = false;
  }
  //3
  if (ris_3 == true) {
    Serial.println("Scheda 3: 0 (ok)");
  } else {
    Serial.println("Scheda 3: 1 (!)");
    check_3 = false;
  }
  //4
  if (ris_4 == true) {
    Serial.println("Scheda 4: 0 (ok)");
  } else {
    Serial.println("Scheda 4: 1 (!)");
    check_4 = false;
  }
  //5
  if (ris_5 == true) {
    Serial.println("Scheda 5: 0 (ok)");
  } else {
    Serial.println("Scheda 5: 1 (!)");
    check_5 = false;
  }
  //6
  if (ris_6 == true) {
    Serial.println("Scheda 6: 0 (ok)");
  } else {
    Serial.println("Scheda 6: 1 (!)");
    check_6 = false;
  }
  //7
  if (ris_7 == true) {
    Serial.println("Scheda 7: 0 (ok)");
  } else {
    Serial.println("Scheda 7: 1 (!)");
    check_7 = false;
  }
  //8
  if (ris_8 == true) {
    Serial.println("Scheda 8: 0 (ok)");
  } else {
    Serial.println("Scheda 8: 1 (!)");
    check_8 = false;
  }
}


void check_scheda() {
  //1
  if (check_1 == true) {
    Serial.println("Scheda 1  -->  OK");
  } else {
    Serial.println("Scheda 1  -->  NO!!!");
  }
  //2
  if (check_2 == true) {
    Serial.println("Scheda 2  -->  OK");
  } else {
    Serial.println("Scheda 2  -->  NO!!!");
  }
  //3
  if (check_3 == true) {
    Serial.println("Scheda 3  -->  OK");
  } else {
    Serial.println("Scheda 3  -->  NO!!!");
  }
  //4
  if (check_4 == true) {
    Serial.println("Scheda 4  -->  OK");
  } else {
    Serial.println("Scheda 4  -->  NO!!!");
  }
  //5
  if (check_5 == true) {
    Serial.println("Scheda 5  -->  OK");
  } else {
    Serial.println("Scheda 5  -->  NO!!!");
  }
  //6
  if (check_6 == true) {
    Serial.println("Scheda 6  -->  OK");
  } else {
    Serial.println("Scheda 6  -->  NO!!!");
  }
  //7
  if (check_7 == true) {
    Serial.println("Scheda 7  -->  OK");
  } else {
    Serial.println("Scheda 7  -->  NO!!!");
  }
  //8
  if (check_8 == true) {
    Serial.println("Scheda 8  -->  OK");
  } else {
    Serial.println("Scheda 8  -->  NO!!!");
  }
}


/*void risultati() {
  Serial.println("");
  Serial.print("Rele 1: ");
  Serial.println(digitalRead(R1));
  Serial.print("Rele 2: ");
  Serial.println(digitalRead(R2));
  Serial.print("Rele 3: ");
  Serial.println(digitalRead(R3));
  Serial.print("Rele 4: ");
  Serial.println(digitalRead(R4));
  Serial.print("Rele 5: ");
  Serial.println(digitalRead(R5));
  Serial.print("Rele 6: ");
  Serial.println(digitalRead(R6));
  Serial.print("Rele 7: ");
  Serial.println(digitalRead(R7));
  Serial.print("Rele 8: ");
  Serial.println(digitalRead(R8));
  Serial.println("");
}*/
