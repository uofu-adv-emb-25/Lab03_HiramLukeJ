#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"
#include "helpers.h"

void setUp(void) {}

void tearDown(void) {}

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

int main (void)
{
    stdio_init_all();
    while (1) {
        printf("Start tests\n");
        UNITY_BEGIN();
        RUN_TEST(testTimeout);
        RUN_TEST(testSuccess);
        sleep_ms(5000);
        UNITY_END();
    }
}
