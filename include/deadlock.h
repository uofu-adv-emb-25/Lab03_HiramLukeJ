#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>
#include <stdio.h>

void create_deadlockA(__unused void *params);
void create_deadlockB(__unused void *params);


void orphaned_lock(__unused void *params);
void fixed_orphaned_lock(void *params);