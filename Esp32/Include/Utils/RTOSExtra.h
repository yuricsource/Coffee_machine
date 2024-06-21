#pragma once

#include "freertos/FreeRTOS.h"

#define configWIFISVC_STACK_DEPTH (1024 * 3)
#define configCMDSVC_STACK_DEPTH (1024 * 3)
#define configCLIENT_STACK_DEPTH (1024 * 3)

#define configTOTAL_PROJECT_HEAP_SIZE_ALLOCATED (configCMDSVC_STACK_DEPTH          + \
                                                configCMDSVC_STACK_DEPTH           + \
                                                configCLIENT_STACK_DEPTH           + \
                                                )
