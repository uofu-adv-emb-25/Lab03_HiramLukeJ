#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>
#include <stdio.h>

int print_count(SemaphoreHandle_t semaphore, TickType_t timeout, int * counter, const char thread_type[]);