#include "PWM-MANAGER-3.h"

PWM_object::PWM_object()
{
}

PWM_object::PWM_object(char *name, ledc_init init, bool is_low_on)
{
    this->is_LOW_on = is_low_on;

    this->init(name, init);

    /*for (int i = 0; i < this->ledc_init_value.channels; i++)
    {
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, this->ledc_init_value.leds[i].channel, MAX_DUTY);
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, this->ledc_init_value.leds[i].channel);
    }*/
}

PWM_object::PWM_object(char *name, ledc_init init)
{
    this->init(name, init);
}

void PWM_object::init(char *name, ledc_init init)
{

    this->_name = name;
    this->ledc_init_value = init;

    //ledc_timer_config(&this->ledc_init_value.ledc_timer);

    for (int i = 0; i < this->ledc_init_value.channels; i++)
    {
        ledc_channel_config(&this->ledc_init_value.leds[i]);

    }

    //delay(1000);
    //ledc_fade_func_install(0);

    /*xTaskCreatePinnedToCore(
        PWM_object::loop, // Task function.
        name,             // String with name of task.
        10000,            // Stack size in bytes.
        this,             // Parameter passed as input of the task
        2,                // Priority of the task.
        &this->handle,
        1); // Task handle. */
}

void PWM_object::change_configuration(ledc_visual_configuration *conf,bool force_update)
{
    if (this->configuration != conf || force_update)
    {
        debug("Change configuration");
        this->repeated = 0;
        this->reverse = 0;
        this->configuration = conf;

        if (this->configuration->blink_millis == 0 && this->configuration->fade_millis != 0)
        {
            //this->configuration->blink_millis = 1;
            //this->configuration->repeat = 1;
        }

        //configASSERT(this->handle);

        if (this->handle == NULL)
        {
            xTaskCreatePinnedToCore(
                PWM_object::loop, // Task function.
                this->_name,      // String with name of task.
                10000,            // Stack size in bytes.
                this,             // Parameter passed as input of the task
                2,                // Priority of the task.
                &this->handle,
                0);
        }
        else
        {
            if (!this->_is_looping)
            {
                vTaskResume(this->handle);
            }
            else
            {
                vTaskDelete(this->handle);

                xTaskCreatePinnedToCore(
                    PWM_object::loop, // Task function.
                    this->_name,      // String with name of task.
                    10000,            // Stack size in bytes.
                    this,             // Parameter passed as input of the task
                    2,                // Priority of the task.
                    &this->handle,
                    0);
            }
        }
    }
}

void PWM_object::loop(void *argument)
{
    PWM_object *element = (PWM_object *)argument;

    while (1)
    {
        element->_is_looping = true;
        if (element->configuration == NULL)
        {
            debug("Suspended...");
            element->_is_looping = false;
            vTaskSuspend(NULL);
        }
        /*else if (element->configuration->blink_millis == 0)
        {
            debug("Blink 0");
            if (element->configuration->fade_millis == 0)
            {
                for (int i = 0; i < element->ledc_init_value.channels; i++)
                {
                    uint32_t value;
                    if (element->is_LOW_on)
                    {
                        value = MAX_DUTY - element->configuration->duty[i] * element->intensity;
                    }
                    else
                    {
                        value = element->configuration->duty[i] * element->intensity;
                    }

                    ledc_set_duty(LEDC_HIGH_SPEED_MODE, element->ledc_init_value.leds[i].channel, value);
                    ledc_update_duty(LEDC_HIGH_SPEED_MODE, element->ledc_init_value.leds[i].channel);
                }
            }
            debug("Going to be suspended...");
            //vTaskDelay(1);
            element->_is_looping = false;
            vTaskSuspend(NULL); //vTaskDelay(10000); //TODO da sospendere
        }*/
        else
        {
            debug("Blink %d", element->configuration->blink_millis);
            debug("Fade %d", element->configuration->fade_millis);

            if (element->configuration->fade_millis != 0)
            {
                int step = element->configuration->fade_millis / 25;
                debug("Fade singolo con %d step", step);

                float step_value[LEDC_CHANNELS];

                float value[LEDC_CHANNELS];

                for (int i = 0; i < element->ledc_init_value.channels; i++)
                {
                    value[i] = (float)ledc_get_duty(element->ledc_init_value.leds[i].speed_mode, element->ledc_init_value.leds[i].channel);

                    int to = element->configuration->duty[i] * element->_intensity;
                    if (element->reverse)
                    {
                        to = 0;
                    }

                    if (element->is_LOW_on)
                    {
                        to = MAX_DUTY - to;
                    }

                    step_value[i] = (float)(to - value[i]) / step;

                    debug("channel %d value %d to %d with step %f", element->ledc_init_value.leds[i].channel, (int)value[i], to, step_value[i]);
                }

                for (int c = 1; c <= step; c++)
                {

                    for (int i = 0; i < element->ledc_init_value.channels; i++)
                    {

                        value[i] += step_value[i];

                        //debug("value %d", (int)value[i]);
                        ESP_ERROR_CHECK(ledc_set_duty(element->ledc_init_value.leds[i].speed_mode, element->ledc_init_value.leds[i].channel, (int)value[i]));
                        ESP_ERROR_CHECK(ledc_update_duty(element->ledc_init_value.leds[i].speed_mode, element->ledc_init_value.leds[i].channel));
                    }
                    vTaskDelay(25);
                }

                debug("Fade singolo di %d ms", element->configuration->fade_millis);
            }

            for (int i = 0; i < element->ledc_init_value.channels; i++)
            {

                uint32_t value = element->configuration->duty[i] * element->_intensity;
                if (element->reverse)
                {
                    value = 0;
                }

                if (element->is_LOW_on)
                {
                    value = MAX_DUTY - value;
                }

                debug("channel %d to %d", element->ledc_init_value.leds[i].channel, value);
                ledc_set_duty(element->ledc_init_value.leds[i].speed_mode, element->ledc_init_value.leds[i].channel, value);
                ledc_update_duty(element->ledc_init_value.leds[i].speed_mode, element->ledc_init_value.leds[i].channel);

            }

            if (element->configuration->repeat != 0)
            {
                if (element->configuration->repeat != 1)
                {
                    element->reverse = !element->reverse;
                }
                element->repeated += 1;
                if (element->repeated >= element->configuration->repeat)
                {

                    if (element->configuration->blink_millis == 0)
                    {
                        debug("Repeted %d times. Suspended...", element->repeated);
                        element->_is_looping = false;
                        vTaskSuspend(NULL);
                    }
                    else
                    {
                        element->repeated = 0;
                        //element->reverse = !element->reverse;
                        vTaskDelay(element->configuration->blink_millis);
                    }
                }
                else
                {
                    //vTaskDelay(element->configuration->blink_millis);
                    //element->reverse = !element->reverse;
                    vTaskDelay(10);
                }
            }
            else
            {
                if (element->configuration->blink_millis == 0)
                {
                    debug("Repeted %d times. Suspended...", element->repeated);
                    element->_is_looping = false;
                    vTaskSuspend(NULL);
                }
                else
                {
                    element->reverse = !element->reverse;
                    vTaskDelay(element->configuration->blink_millis);
                }
            }
        }
    }
}

bool PWM_object::isOff()
{
    if (this->configuration != NULL)
    {
        for (int i = 0; i < this->ledc_init_value.channels; i++)
        {
            uint32_t duty = ledc_get_duty(this->ledc_init_value.leds[i].speed_mode, this->ledc_init_value.leds[i].channel);
            //debug("Configuration %d is %d", i, duty);//this->configuration->duty[i]);
            if (!this->is_LOW_on)
            {
                if (duty != 0)
                {
                    return false;
                }
            }
            else
            {
                if (duty != MAX_DUTY)
                {
                    return false;
                }
            }
        }
        return true;
    }
    return true;
}

void PWM_object::setIntensity(float value)
{
    if (value != this->_intensity)
    {
        this->_intensity = value;

        if (this->handle == NULL)
        {
            /*xTaskCreatePinnedToCore(
                PWM_object::loop, // Task function.
                this->_name,      // String with name of task.
                10000,            // Stack size in bytes.
                this,             // Parameter passed as input of the task
                2,                // Priority of the task.
                &this->handle,
                1);*/
        }
        else
        {
            if (!this->_is_looping)
            {
                vTaskResume(this->handle);
            }
            else
            {
                vTaskDelete(this->handle);

                xTaskCreatePinnedToCore(
                    PWM_object::loop, // Task function.
                    this->_name,      // String with name of task.
                    10000,            // Stack size in bytes.
                    this,             // Parameter passed as input of the task
                    2,                // Priority of the task.
                    &this->handle,
                    0);
            }
        }
    }
}