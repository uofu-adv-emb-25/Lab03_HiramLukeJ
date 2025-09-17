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
}

void testSuccess() {

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
