#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include "sdkconfig.h"

TaskHandle_t task1handler = NULL;
TaskHandle_t task2handler = NULL;

static const char *TAG = "codeRed";

/*
Learning........
xTaskCreate
vTaskSuspend
vTaskResume
vTaskDelete */

int count1 = 0;
int count2 = 0;


void task1(void* pvParameter)
{
    for (;;)
    {
        count1++;
        ESP_LOGI(TAG, "Task1 running : %d", count1);
        if (count1 == 20)
        {
            vTaskSuspend(NULL);                        
        }
        vTaskDelay(500 / portTICK_PERIOD_MS);

        
    };
}

void task2(void *pvParameter)
{
    for (;;)
    {
        count2++;
        ESP_LOGI(TAG, "Task2 running : %d", count2);
         if (count2 == 40)
        {
            vTaskResume(task1handler);
            vTaskSuspend(NULL);
      //      vTaskDelete(NULL); 
        }
        vTaskDelay(500 / portTICK_PERIOD_MS);

       
    };
}
void app_main()
{
    xTaskCreate(task1,"Task 1",4096,NULL,7,&task1handler);
    xTaskCreatePinnedToCore(task2,"Task 2",4096,NULL,7,&task2handler,1);

    for(;;)
    {
        ESP_LOGI(TAG,"MAIN TASK RUNNING");
        if(count1>=60)
        {
            vTaskSuspend(task1handler);
            vTaskResume(task2handler);
        }
        vTaskDelay(6000/portTICK_PERIOD_MS);
    };

}
