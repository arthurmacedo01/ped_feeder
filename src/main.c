#include <stdio.h>
#include "iot_servo.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "wifi.c"
#include "ntp.c"
#include "led.c"
#include "mqtt_example.c"
#include "feed.h"

void app_main()
{
  configure_led();
  connect_to_wifi();
  ntp();
  led_blink(1);
  mqtt_example();
  led_blink(1);

  servo_config_t servo_cfg = {
      .max_angle = 180,
      .min_width_us = 500,
      .max_width_us = 2600,
      .freq = 50,
      .timer_number = LEDC_TIMER_0,
      .channels = {
          .servo_pin = {
              5},
          .ch = {
              LEDC_CHANNEL_0,
          },
      },
      .channel_number = 1,
  };
  iot_servo_init(LEDC_LOW_SPEED_MODE, &servo_cfg);
  led_blink(2);
  iot_servo_write_angle(LEDC_LOW_SPEED_MODE, 0, 0);
  led_blink(3);

  time_t now = 0;
  int is_feeded = 0;
  int is_sync = 0;
  struct tm *timeinfo = localtime(&now);

  while (true)
  {
    time(&now);
    timeinfo = localtime(&now);

    print_time(now, "Tempo agora");
    printf("is_feeded: %d. is_sync: %d\n", is_feeded, is_sync);

    if (sntp_get_sync_status() == SNTP_SYNC_STATUS_COMPLETED)
    {
      is_sync = 1;
      turn_on_off(1);
    }

    if ((timeinfo->tm_hour == 7 || timeinfo->tm_hour == 12 || timeinfo->tm_hour == 17 || timeinfo->tm_hour == 21) && is_sync)
    {

      if (!is_feeded)
      {
        feed_now(700);
        is_feeded = 1;
      }
    }
    else
    {
      is_feeded = 0;
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  // deinit servo
  iot_servo_deinit(LEDC_LOW_SPEED_MODE);
}