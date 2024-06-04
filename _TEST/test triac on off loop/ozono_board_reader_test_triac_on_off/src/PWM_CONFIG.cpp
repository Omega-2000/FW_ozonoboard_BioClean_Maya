#include "PWM_CONFIG.h"

ledc_visual_configuration green = {
  .duty = {0, 100, 0},
  .fade_millis = 1000,
  .blink_millis = 0,
  .repeat = 1
};

ledc_visual_configuration blue = {
  .duty = {0, 0, 100},
  .fade_millis = 1000,
  .blink_millis = 0,
  .repeat = 1
};

ledc_visual_configuration white = {
  .duty = {MAX_DUTY, MAX_DUTY, MAX_DUTY},
  .fade_millis = 1000,
  .blink_millis = 0,
  .repeat = 1
};
