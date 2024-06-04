#include <Arduino.h>
#include "PWM-MANAGER-3.h"
#include "driver/ledc.h"
#include "PIN_CONFIG.h"
#include "PWM_CONFIG.h"
#include "VAR_CONFIG.h"


void IRAM_ATTR aux_isr() {
  now = millis();

  if (now - last_millis_change_aux > 4 && now - last_millis_change_aux < 100) {
    last_ok = now;
  }
  
  last_millis_change_aux = now;
}


void setup() {
  Serial.begin(115200);

  pinMode(sensore, INPUT);
  pinMode(ozono, OUTPUT);
  
  ledc_timer_config(&ledc_timer);

  led.change_configuration(&green); //led verde
  digitalWrite(ozono, LOW); //ozono off

  attachInterrupt(sensore, aux_isr, CHANGE); //RISING o CHANGE

  //  Serial.println("setup");
}


void loop() { 
  if ((last_ok != 0) && (millis() - last_ok < 100)) {
    led.change_configuration(&blue); //led blu
    digitalWrite(ozono, HIGH); //ozono on
  } else {
    led.change_configuration(&green); //led verde
    digitalWrite(ozono, LOW); //ozono off
  }

}
