#include "deadlock.h"

void create_deadlockA(void *params)
{
    SemaphoreHandle_t* sem = (SemaphoreHandle_t*)params;
    xSemaphoreTake(sem[0], portMAX_DELAY);
    {
        vTaskSuspend(NULL);
        xSemaphoreTake(sem[1], portMAX_DELAY);
        xSemaphoreGive(sem[1]);
    }
    xSemaphoreGive(sem[0]);
}

void create_deadlockB(void *params)
{
    SemaphoreHandle_t* sem = (SemaphoreHandle_t*)params;
    xSemaphoreTake(sem[1], portMAX_DELAY);
    {
        vTaskSuspend(NULL);
        xSemaphoreTake(sem[0], portMAX_DELAY);
        xSemaphoreGive(sem[0]);
    }
    xSemaphoreGive(sem[1]);
}

void orphaned_lock(void *params)
{
    SemaphoreHandle_t* sem = (SemaphoreHandle_t*)params;
    int counter = 0;
    while (1) {
        xSemaphoreTake(sem[0], portMAX_DELAY);
        counter++;
        if (counter % 2) {
            continue;
        }
        printf("Count %d\n", counter);
        xSemaphoreGive(sem[0]);
    }
}

void fixed_orphaned_lock(void *params)
{
    SemaphoreHandle_t* sem = (SemaphoreHandle_t*)params;
    int counter = 0;
    while (1) {
        xSemaphoreTake(sem[0], portMAX_DELAY);
        counter++;
        if (!(counter % 2)) {
            printf("Count %d\n", counter);
        }
        xSemaphoreGive(sem[0]);
    }
}
