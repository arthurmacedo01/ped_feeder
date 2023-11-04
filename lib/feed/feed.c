#include "feed.h"

#define TAG_FEED "FEED"

void feed_now(int duration)
{
  ESP_LOGI(TAG_FEED, "Alimentando... duration: %d", duration);
  iot_servo_write_angle(LEDC_LOW_SPEED_MODE, 0, (float)180);
  vTaskDelay(duration / portTICK_PERIOD_MS);
  iot_servo_write_angle(LEDC_LOW_SPEED_MODE, 0, (float)0);
  ESP_LOGI(TAG_FEED, "ok");
}