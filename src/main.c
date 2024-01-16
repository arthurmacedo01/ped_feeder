#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

TimerHandle_t xTimer = NULL;

void run_function(TimerHandle_t xTimer)
{
  printf("executando função após o timer expirar\n");
}

void app_main(void)
{
  xTimer = xTimerCreate("Temp_1", 1000 / portTICK_PERIOD_MS, pdTRUE, (void *)0, run_function);
  xTimerStart(xTimer, portMAX_DELAY);
}