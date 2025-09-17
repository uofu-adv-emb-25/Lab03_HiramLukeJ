#include "helpers.h" 

int print_count(SemaphoreHandle_t semaphore, TickType_t timeout, int * counter, const char thread_type[]){
    if (!xSemaphoreTake(semaphore, timeout))
        return 0;
    {
        *counter += 1;
        printf("hello world from %s! Count %d\n", thread_type, counter);
    }
    xSemaphoreGive(semaphore);
    return 1;
}