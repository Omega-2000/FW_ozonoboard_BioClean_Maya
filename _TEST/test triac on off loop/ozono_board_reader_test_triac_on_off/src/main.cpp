#include <Arduino.h>
#include "PWM-MANAGER-3.h"
#include "driver/ledc.h"
#include "PIN_CONFIG.h"
#include "PWM_CONFIG.h"
#include "VAR_CONFIG.h"
#include "spiff.h"

String all = "";

void setup() {
  Serial.begin(115200);

  if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
    Serial.println("SPIFFS Mount Failed");
    return;
  }

  File file = SPIFFS.open("/log.txt", FILE_READ);
  while (file.available()) {
    all = file.readStringUntil('\n');
    Serial.println("File:");
    Serial.println(all);
  }
}

void loop() {
}
