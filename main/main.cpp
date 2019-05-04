#include "freertos/FreeRTOS.h"
#include "sdkconfig.h"
#include "freertos/task.h"
#include </home/x/eclipse-workspace/TEST_T/components/serv/serv.h>
extern "C"
    {
    void app_main(void);
    void vTask_test_Queue( void * pvParameters );
    void socket_server(void *pvParameters);
    void access_point_task(void *ignore);
    }
extern void task_initI2C(void*);
extern void task_display(void*);

void app_main(void)
    {
    printf("Star my program\n");

    nvs_flash_init();
    tcpip_adapter_init();
// Create a queue capable of containing 10 uint32_t values.
    xQueue1 = xQueueCreate(1, sizeof(struct data));
    wifi_group = xEventGroupCreate();

    /* Configure and run Access Point */
    xTaskCreatePinnedToCore(access_point_task, /* pvTaskCode */
    "udp_server", /* pcName */
    4096, /* usStackDepth */
    NULL, /* pvParameters */
    1, /* uxPriority */
    NULL, /* pxCreatedTask */
    0); /* xCoreID */
    vTaskDelay(500 / portTICK_PERIOD_MS);

    /* socket_server is responsible for creating and maintaining incoming connections */
    xTaskCreatePinnedToCore(socket_server, /* pvTaskCode */
    "socket_server", /* pcName */
    4096, /* usStackDepth */
    NULL, /* pvParameters */
    3, /* uxPriority */
    NULL, /* pxCreatedTask */
    0); /* xCoreID */

    xEventGroupWaitBits(wifi_group, /* The event group being tested. */
    BIT_1, /* The bits within the event group to wait for. */
    pdTRUE, /* BIT_0 & BIT_4 should be cleared before returning. */
    pdFALSE, /* Don't wait for both bits, either bit will do. */
    portMAX_DELAY);/* Wait a maximum of 100ms for either bit to be set. */

    xTaskCreatePinnedToCore(&task_initI2C, "mpu_task", 2048, NULL, 1, NULL, 1);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    xTaskCreatePinnedToCore(&task_display, "disp_task", 6800, NULL, 5, NULL, 1);
    }
