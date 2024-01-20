#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "my_wifi.h"
#include "my_mqtt.h"

TaskHandle_t xTask = NULL;

void task_function(void *arg)
{
  while (1)
  {
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    printf("task function sendo executado!\n");
  }
}

void app_main(void)
{
  xTaskCreate(task_function, "Task", 2048, NULL, 0, &xTask);
  wifi_init_sta();
  mqtt_app_start(xTask);
}
