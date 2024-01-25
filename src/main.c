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
#include "mdns.h"
#include "my_ntp.h"
#include "my_mdns.h"

TaskHandle_t xTask = NULL;
TaskHandle_t xTaskMQTT = NULL;
TaskHandle_t xTaskServer = NULL;
QueueHandle_t xQueueMQTTIn = NULL;
QueueHandle_t xQueueMQTTOut = NULL;

void task_function(void *arg)
{
  char *data = NULL;
  while (1)
  {
    xQueueReceive(xQueueMQTTIn, &data, portMAX_DELAY);
    cJSON *data_JSON = cJSON_Parse(data);
    time_t now = 0;
    time(&now);
    localtime(&now);
    print_time(now, "Time inside task");
    int intensity = 0;
    intensity = atoi(cJSON_GetObjectItem(data_JSON, "intensity")->valuestring);
    rotate_servo(intensity);
    char *msg = "OK";
    xQueueSendToBack(xQueueMQTTOut, (void *)&(msg), portMAX_DELAY);
  }
}
void task_mqtt(void *arg)
{
  ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
  mqtt_app_start(xQueueMQTTIn);
  char *data = NULL;
  while (1)
  {
    xQueueReceive(xQueueMQTTOut, &data, portMAX_DELAY);
    send_mqtt(data);
  }
}

void task_client(void *arg)
{
  wifi_init_sta(xTaskServer, xTaskMQTT);
  vTaskDelete(NULL);
}

void task_server(void *arg)
{
  ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
  ESP_ERROR_CHECK(nvs_flash_init());
  ESP_ERROR_CHECK(esp_netif_init());
  ESP_ERROR_CHECK(esp_event_loop_create_default());
  initialise_mdns();
  wifi_init_softap();
  server_init();
  ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
  vTaskDelete(NULL);
}

void app_main(void)
{
  xQueueMQTTIn = xQueueCreate(3, 40 * sizeof(char));
  xQueueMQTTOut = xQueueCreate(3, 40 * sizeof(char));
  xTaskCreate(task_function, "Task", 2048, NULL, 0, &xTask);
  xTaskCreate(task_client, "TaskClient", 3072, NULL, 0, NULL);
  xTaskCreate(task_mqtt, "TaskMQTT", 3072, NULL, 0, &xTaskMQTT);
  xTaskCreate(task_server, "TaskServer", 3072, NULL, 0, &xTaskServer);

  // ntp_init();
}