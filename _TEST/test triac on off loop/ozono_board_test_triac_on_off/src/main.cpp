#include <Arduino.h>
#include "PWM-MANAGER-3.h"
#include "driver/ledc.h"
#include "PIN_CONFIG.h"
#include "PWM_CONFIG.h"
#include "VAR_CONFIG.h"
#include "spiff.h"


void setup() {
  Serial.begin(115200);

  pinMode(sensore, INPUT);
  pinMode(ozono, OUTPUT);
  
  ledc_timer_config(&ledc_timer);

  led.change_configuration(&green); //led verde
  digitalWrite(ozono, LOW); //ozono off

  //SPIFFS
  if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
    Serial.println("SPIFFS Mount Failed");
    return;
  }

  listDir(SPIFFS, "/", 0);
  if(!SPIFFS.exists("/log.txt")) {
    writeFile(SPIFFS, "/log.txt", "log\n");
  }

  readFile(SPIFFS, "/log.txt");  
  //deleteFile(SPIFFS, "/log.txt");   //se serve eliminare il file
}

void loop() { 
  digitalWrite(ozono, HIGH); //ozono on
  //delay(10000);
  cont = cont + 1;
  char c[16];
  char capo[2] = "\n";
  const char *acapo = capo;
  itoa(cont, c, 10);
  appendFile(SPIFFS, "/log.txt", c);
  appendFile(SPIFFS, "/log.txt", acapo);
  delay(3600000); //1 ora
  digitalWrite(ozono, LOW); //ozono off
  delay(60000); //1 minuto

}