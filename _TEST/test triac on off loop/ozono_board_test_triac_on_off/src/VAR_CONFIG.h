#ifndef VAR_CONFIG_H
#define VAR_CONFIG_H

#include "PIN_CONFIG.h"
#include "PWM-MANAGER-3.h"

extern unsigned long last_millis_change_aux;
extern unsigned long last_ok;
extern unsigned long now;

extern ledc_timer_config_t ledc_timer;

extern ledc_init led_struct;
extern PWM_object led;

extern int cont;

#endif