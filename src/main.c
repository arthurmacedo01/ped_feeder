#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

int shared_value = 0;
SemaphoreHandle_t myMutex = NULL;

void task1(void *args)
{
  while (1)
  {
    xSemaphoreTake(myMutex, portMAX_DELAY);
    shared_value++;
    xSemaphoreGive(myMutex);
    printf("task 1: valor: %d\n", shared_value);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void task2(void *args)
{
  while (1)
  {
    xSemaphoreTake(myMutex, portMAX_DELAY);
    shared_value *= 2;
    xSemaphoreGive(myMutex);
    printf("task 2: valor: %d\n", shared_value);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void task3(void *args)
{
  while (1)
  {
    xSemaphoreTake(myMutex, portMAX_DELAY);
    shared_value *= 3;
    xSemaphoreGive(myMutex);
    printf("task 3: valor: %d\n", shared_value);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void app_main(void)
{
  myMutex = xSemaphoreCreateMutex();
  xTaskCreate(task1, "task1", 2048, NULL, 0, NULL);
  xTaskCreate(task2, "task2", 2048, NULL, 0, NULL);
  xTaskCreate(task3, "task3", 2048, NULL, 0, NULL);
}