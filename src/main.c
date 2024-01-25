#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "my_wifi.h"
#include "my_mqtt.h"
#include "cJSON.h"
#include "my_servo.h"
#include "my_softap.h"

#include "my_scan.c"
#include "my_server.h"

TaskHandle_t xTask = NULL;
TaskHandle_t xTaskServer = NULL;
QueueHandle_t xQueueMQTT = NULL;
QueueHandle_t xQueueMQTTOut = NULL;

void task_function(void *arg)
{
  char *data = NULL;
  while (1)
  {
    xQueueReceive(xQueueMQTT, &data, portMAX_DELAY);
    cJSON *data_JSON = cJSON_Parse(data);

    int intensity = 0;
    intensity = atoi(cJSON_GetObjectItem(data_JSON, "intensity")->valuestring);
    printf("dentro da task: o valor de itensity é %d\n", intensity);
    rotate_servo(intensity);
    char *msg = "OK";
    xQueueSendToBack(xQueueMQTTOut, (void *)&(msg), portMAX_DELAY);
  }
}
void task_mqtt(void *arg)
{
  mqtt_app_start(xQueueMQTT);
  char *data = NULL;
  while (1)
  {
    xQueueReceive(xQueueMQTTOut, &data, portMAX_DELAY);
    printf("dentro da task mqtt: %s\n", data);
    send_mqtt(data);
  }
}

void task_server(void *arg)
{
  while (1)
  {
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    softap_init();
    server_init();
  }
}

void app_main(void)
{
  xQueueMQTT = xQueueCreate(3, 40 * sizeof(char));
  xQueueMQTTOut = xQueueCreate(3, 40 * sizeof(char));
  xTaskCreate(task_function, "Task", 2048, NULL, 0, &xTask);
  xTaskCreate(task_server, "TaskServer", 3072, NULL, 0, &xTaskServer);
  wifi_init_sta(xTaskServer);
  xTaskCreate(task_mqtt, "TaskMQTT", 3072, NULL, 0, NULL);
}