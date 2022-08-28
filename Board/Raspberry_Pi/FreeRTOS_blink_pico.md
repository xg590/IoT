### Dev Env  
* Pico (W): AArch32
* VM      : x86_64 and Ubuntu 20.04.3
```
sudo apt install build-essential cmake gcc-arm-none-eabi binutils-arm-none-eabi
```
### Blink
* [Original Post](https://learnembeddedsystems.co.uk/freertos-on-rp2040-boards-pi-pico-etc-using-vscode) by "Learn Embedded Systems" 
``` 
mkdir -p pico_dev/git_repos_archive 
git clone --recurse-submodules https://github.com/raspberrypi/pico-examples.git pico_dev/git_repos_archive/pico-examples
git clone --recurse-submodules https://github.com/FreeRTOS/FreeRTOS-Kernel.git  pico_dev/git_repos_archive/FreeRTOS-Kernel
git clone --recurse-submodules https://github.com/raspberrypi/pico-sdk.git      pico_dev/git_repos_archive/pico-sdk
```
* FreeRTOS Dir
```
mkdir -p pico_dev/root_dir_1st_project/freertos

cp -r pico_dev/git_repos_archive/FreeRTOS-Kernel pico_dev/root_dir_1st_project/freertos/FreeRTOS-Kernel

cat << EOF > pico_dev/root_dir_1st_project/freertos/CMakeLists.txt
set(PICO_SDK_FREERTOS_SOURCE FreeRTOS-Kernel) 
add_library(freertos
    \${PICO_SDK_FREERTOS_SOURCE}/event_groups.c
    \${PICO_SDK_FREERTOS_SOURCE}/list.c
    \${PICO_SDK_FREERTOS_SOURCE}/queue.c
    \${PICO_SDK_FREERTOS_SOURCE}/stream_buffer.c
    \${PICO_SDK_FREERTOS_SOURCE}/tasks.c
    \${PICO_SDK_FREERTOS_SOURCE}/timers.c
    \${PICO_SDK_FREERTOS_SOURCE}/portable/MemMang/heap_3.c
    \${PICO_SDK_FREERTOS_SOURCE}/portable/GCC/ARM_CM0/port.c
) 
target_include_directories(freertos PUBLIC
    .
    \${PICO_SDK_FREERTOS_SOURCE}/include
    \${PICO_SDK_FREERTOS_SOURCE}/portable/GCC/ARM_CM0
)
EOF

cat << EOF > pico_dev/root_dir_1st_project/freertos/FreeRTOSConfig.h
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H
/* Use Pico SDK ISR handlers */
#define vPortSVCHandler         isr_svcall
#define xPortPendSVHandler      isr_pendsv
#define xPortSysTickHandler     isr_systick
#define configUSE_PREEMPTION                    1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0
#define configUSE_TICKLESS_IDLE                 0
#define configCPU_CLOCK_HZ                      133000000
#define configTICK_RATE_HZ                      100
#define configMAX_PRIORITIES                    5
#define configMINIMAL_STACK_SIZE                128
#define configMAX_TASK_NAME_LEN                 16
#define configUSE_16_BIT_TICKS                  0
#define configIDLE_SHOULD_YIELD                 1
#define configUSE_TASK_NOTIFICATIONS            1
#define configTASK_NOTIFICATION_ARRAY_ENTRIES   3
#define configUSE_MUTEXES                       0
#define configUSE_RECURSIVE_MUTEXES             0
#define configUSE_COUNTING_SEMAPHORES           0
#define configQUEUE_REGISTRY_SIZE               10
#define configUSE_QUEUE_SETS                    0
#define configUSE_TIME_SLICING                  0
#define configUSE_NEWLIB_REENTRANT              0
#define configENABLE_BACKWARD_COMPATIBILITY     0
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS 5
#define configSTACK_DEPTH_TYPE                  uint16_t
#define configMESSAGE_BUFFER_LENGTH_TYPE        size_t
/* Memory allocation related definitions. */
#define configSUPPORT_STATIC_ALLOCATION         0
#define configSUPPORT_DYNAMIC_ALLOCATION        1
#define configAPPLICATION_ALLOCATED_HEAP        1
/* Hook function related definitions. */
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0
#define configCHECK_FOR_STACK_OVERFLOW          0
#define configUSE_MALLOC_FAILED_HOOK            0
#define configUSE_DAEMON_TASK_STARTUP_HOOK      0
/* Run time and task stats gathering related definitions. */
#define configGENERATE_RUN_TIME_STATS           0
#define configUSE_TRACE_FACILITY                0
#define configUSE_STATS_FORMATTING_FUNCTIONS    0
/* Co-routine related definitions. */
#define configUSE_CO_ROUTINES                   0
#define configMAX_CO_ROUTINE_PRIORITIES         1
/* Software timer related definitions. */
#define configUSE_TIMERS                        1
#define configTIMER_TASK_PRIORITY               3
#define configTIMER_QUEUE_LENGTH                10
#define configTIMER_TASK_STACK_DEPTH            configMINIMAL_STACK_SIZE
/* Define to trap errors during development. */
#define configASSERT( x )
/* Optional functions - most linkers will remove unused functions anyway. */
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_xResumeFromISR                  1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_xTaskGetSchedulerState          1
#define INCLUDE_xTaskGetCurrentTaskHandle       1
#define INCLUDE_uxTaskGetStackHighWaterMark     0
#define INCLUDE_xTaskGetIdleTaskHandle          0
#define INCLUDE_eTaskGetState                   0
#define INCLUDE_xEventGroupSetBitFromISR        1
#define INCLUDE_xTimerPendFunctionCall          0
#define INCLUDE_xTaskAbortDelay                 0
#define INCLUDE_xTaskGetHandle                  0
#define INCLUDE_xTaskResumeFromISR              1
/* A header file that defines trace macro can be included here. */
#endif /* FREERTOS_CONFIG_H */
EOF
```
#### Blink Pico
* Root Dir
```
mkdir pico_dev/root_dir_1st_project

cp    pico_dev/git_repos_archive/pico-examples/pico_sdk_import.cmake pico_dev/root_dir_1st_project/pico_sdk_import.cmake 

cat << EOF > pico_dev/root_dir_1st_project/CMakeLists.txt
cmake_minimum_required(VERSION 3.12)
set(PICO_SDK_PATH "${PWD}/pico_dev/git_repos_archive/pico-sdk/")
include(pico_sdk_import.cmake)
project(Pico-FreeRTOS)
pico_sdk_init()
add_subdirectory(freertos)
add_subdirectory(ProjectFiles)
EOF
```
* Program Dir
```
mkdir pico_dev/root_dir_1st_project/ProjectFiles 

cat << EOF > pico_dev/root_dir_1st_project/ProjectFiles/CMakeLists.txt
add_executable(blink
    main.c
) 
target_link_libraries(blink pico_stdlib freertos)
pico_add_extra_outputs(blink)
EOF

cat << EOF > pico_dev/root_dir_1st_project/ProjectFiles/main.c
#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"
void led_task()
{   
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
        gpio_put(LED_PIN, 1);
        vTaskDelay(100);
        gpio_put(LED_PIN, 0);
        vTaskDelay(100);
    }
}
int main()
{
    stdio_init_all();
    xTaskCreate(led_task, "LED_Task", 256, NULL, 1, NULL);
    vTaskStartScheduler();
    while(1){};
}
EOF
```
#### Blink Pico W 
* Root Dir
```
mkdir pico_dev/root_dir_1st_project

cp    pico_dev/git_repos_archive/pico-examples/pico_sdk_import.cmake pico_dev/root_dir_1st_project/pico_sdk_import.cmake 

cat << EOF > pico_dev/root_dir_1st_project/CMakeLists.txt
cmake_minimum_required(VERSION 3.12)
set(PICO_SDK_PATH "${PWD}/pico_dev/git_repos_archive/pico-sdk/")
set(PICO_BOARD "pico_w")
include(pico_sdk_import.cmake)
project(Pico-FreeRTOS)
pico_sdk_init()
add_subdirectory(freertos)
add_subdirectory(ProjectFiles)
EOF
```
* Program Dir 
```
mkdir pico_dev/root_dir_1st_project/ProjectFiles 

cat << EOF > pico_dev/root_dir_1st_project/ProjectFiles/CMakeLists.txt
add_executable(blink
    main.c
) 
target_link_libraries(blink pico_stdlib pico_cyw43_arch_none freertos)
pico_add_extra_outputs(blink)
EOF

cat << EOF > pico_dev/root_dir_1st_project/ProjectFiles/main.c
#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
void led_task()
{
    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        vTaskDelay(100);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        vTaskDelay(100);
    }
}
int main()
{
    stdio_init_all();
    xTaskCreate(led_task, "LED_Task", 256, NULL, 1, NULL);
    vTaskStartScheduler();
    while(1){};
}
EOF
```
### Build
``` 
cd pico_dev/root_dir_1st_project/
mkdir build ; cd build ; cmake .. ; make ; 
```
* Final uf2 @ pico_dev/root_dir_1st_project/build/ProjectFiles/blink.bin
