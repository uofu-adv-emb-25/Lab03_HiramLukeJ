#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"
#include "helpers.h"
#include "deadlock.h"

void setUp(void) {}

void tearDown(void) {}

#define SIDE_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define SIDE_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

void testTimeout() {
    SemaphoreHandle_t semaphore = xSemaphoreCreateCounting(1, 1);
    TEST_ASSERT_TRUE_MESSAGE(xSemaphoreTake(semaphore, portMAX_DELAY), "Failed to take Semaphore");
    
    int count = 0;
    int status = print_count(semaphore, 0, &count, "timeout");

    TEST_ASSERT_FALSE_MESSAGE(status, "Returned 1");
    TEST_ASSERT_EQUAL_MESSAGE(0, count, "Count incremented");
}

void testSuccess() {
    SemaphoreHandle_t semaphore = xSemaphoreCreateCounting(1, 1);    
    int count = 0;
    int status = print_count(semaphore, 0, &count, "success");

    TEST_ASSERT_TRUE_MESSAGE(status, "Returned 0");
    TEST_ASSERT_EQUAL_MESSAGE(1, count, "Count didn't increment");
}

void testDeadlock() {
    TaskHandle_t handle1, handle2;
    SemaphoreHandle_t semA = xSemaphoreCreateCounting(1, 1);
    SemaphoreHandle_t semB = xSemaphoreCreateCounting(1, 1);
    SemaphoreHandle_t params[2] = {semA, semB};
    
    xTaskCreate(create_deadlockA, "create_deadlockA",
                SIDE_TASK_STACK_SIZE, params, SIDE_TASK_PRIORITY, &handle1);
    xTaskCreate(create_deadlockB, "create_deadlockB",
                SIDE_TASK_STACK_SIZE, params, SIDE_TASK_PRIORITY, &handle2);

    sleep_ms(100);
    vTaskResume(handle1);
    vTaskResume(handle2);
    sleep_ms(100);
    TEST_ASSERT_EQUAL_MESSAGE(eBlocked, eTaskGetState(handle1), "Task 1 wasn't blocked");
    TEST_ASSERT_EQUAL_MESSAGE(eBlocked, eTaskGetState(handle2), "Task 2 wasn't blocked");
    
    vTaskDelete(handle1);
    vTaskDelete(handle2);
}

void testOrphanedLock() 
{
    
}

void testRunner() {
    sleep_ms(10000);
    while (1) {
        printf("Start tests\n");
        UNITY_BEGIN();
        RUN_TEST(testTimeout);
        RUN_TEST(testSuccess);
        RUN_TEST(testDeadlock);
        sleep_ms(5000);
        UNITY_END();
    }
}

int main (void)
{
    stdio_init_all();
    const char *rtos_name;
    rtos_name = "Test";
    TaskHandle_t task;
    xTaskCreate(testRunner, "TestRunner",
                SIDE_TASK_STACK_SIZE, NULL, SIDE_TASK_PRIORITY, &task);
    vTaskStartScheduler();
    return 0;
}
