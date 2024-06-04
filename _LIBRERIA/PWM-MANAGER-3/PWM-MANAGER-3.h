#ifndef PWM_MANAGER_H
#define PWM_MANAGER_H

#define LEDC_CHANNELS 8

#define MAX_DUTY (1 << LEDC_TIMER_10_BIT) 

//#define DEBUG_PWM

#ifdef DEBUG_PWM
#define debug(fmt, ...) printf("%s: " fmt "\n", "PWM_MANAGER", ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif

#include "arduino.h"
#include "driver/ledc.h"

typedef struct
{
  uint32_t duty[LEDC_CHANNELS];
  uint32_t fade_millis; //quanti ms ci mette a fare il fade
  uint32_t blink_millis; // quanti ms attende prima di cambiare direzione (se 0 non cambia direzione se anche repeat 0)
  uint32_t repeat; // quante volte deve cambiare direzione (0 infiniti se blink impostato)
} ledc_visual_configuration;

typedef struct
{
  uint8_t channels;
  ledc_channel_config_t leds[LEDC_CHANNELS];
  //ledc_timer_config_t ledc_timer;
} ledc_init;

class PWM_object
{
private:
  char* _name;
  ledc_init ledc_init_value;
  ledc_channel_config_t leds[LEDC_CHANNELS];
  ledc_timer_config_t ledc_timer;
  bool reverse = false;
  int repeated = 0;

  bool is_LOW_on = false; //acceso con 0

  float _intensity = 1;
  void init(char *name, ledc_init init);

  bool _is_looping=false;

public:
  ledc_visual_configuration *configuration = NULL;
  TaskHandle_t handle=NULL;
  PWM_object();
  PWM_object(char *name, ledc_init init);
  PWM_object(char *name, ledc_init init, bool is_low_on);
  static void loop(void *argument);
  void change_configuration(ledc_visual_configuration *conf,bool force_update=false);

  void setLowOn();

  bool isOff();

  void setIntensity(float value);
  float getIntensity() const
  {
    return this->_intensity;
  };

  uint32_t *duty() const
  {
    if (this->configuration != NULL)
    {
      return this->configuration->duty;
    }
    return new uint32_t[LEDC_CHANNELS];
  };

  int channels() const
  {
    return this->ledc_init_value.channels;
  };
};

#endif