#include "VAR_CONFIG.h"

//struct led
ledc_init led_struct = {
  .channels = 3,
  .leds = {
    {
      .gpio_num       = led_red,
      .speed_mode     = LEDC_LOW_SPEED_MODE,
      .channel        = LEDC_CHANNEL_0,
      .intr_type      = LEDC_INTR_DISABLE,
      .timer_sel      = LEDC_TIMER_1,
      .duty           = 0, // Set duty to 0%
      .hpoint         = 0
    },
    {
      .gpio_num       = led_green,
      .speed_mode     = LEDC_LOW_SPEED_MODE,
      .channel        = LEDC_CHANNEL_1,
      .intr_type      = LEDC_INTR_DISABLE,
      .timer_sel      = LEDC_TIMER_1,
      .duty           = 0, // Set duty to 0%
      .hpoint         = 0
    },
    {
      .gpio_num       = led_blue,
      .speed_mode     = LEDC_LOW_SPEED_MODE,
      .channel        = LEDC_CHANNEL_2,
      .intr_type      = LEDC_INTR_DISABLE,
      .timer_sel      = LEDC_TIMER_1,
      .duty           = 0, // Set duty to 0%
      .hpoint         = 0
    }
  }
};

//inizializzazione timer
ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .duty_resolution  = LEDC_TIMER_10_BIT,
        .timer_num        = LEDC_TIMER_1,
        .freq_hz          = 5000,  // Set output frequency at 5 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };

//oggetto pwm
PWM_object led = PWM_object((char*)"pwm_led_rgb", led_struct);

//millis per segnale sensore
unsigned long last_millis_change_aux = 0;
unsigned long last_ok = 0;
unsigned long now = 0;

int cont = 0;