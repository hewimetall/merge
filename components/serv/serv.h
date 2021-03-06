/*
 * head.h
 */

#ifndef MAIN_HEAD_H_
#define MAIN_HEAD_H_
#include <esp_event.h>
#include <esp_event_loop.h>
#include <esp_log.h>
#include <esp_system.h>
#include <esp_wifi.h>
#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "freertos/semphr.h"
#include <nvs_flash.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include </home/x/.eclipse/esp/esp-idf/components/lwip/lwip/src/include/lwip/sockets.h>
#include <errno.h>
#include "freertos/event_groups.h"
#include <driver/i2c.h>
#include <esp_err.h>

#define PIN_SDA 18
#define PIN_CLK 19

//////////////////////////////////////////////////////////////////////////////////////
///  Macro
//////////////////////////////////////////////////////////////////////////////////////
#define IF_ERR(X,MASS,ERR_MASS) if(X==ESP_OK) ESP_LOGE(TAG, #MASS);\
	 else  ESP_LOGE(TAG, #ERR_MASS)

//////////////////////////////////////////////////////////////////////////////////////
/// Macro
//////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////
/// WIFI  Block
//////////////////////////////////////////////////////////////////////////////////////
#define PORT_NUMBER 989

#define SSID  "ESP32_TESTAP"
#define PASS ""
#define TIP_WIFI_AUTH_OPEN WIFI_AUTH_OPEN
//  USED FOR IP STATIC
// The IP address that we want our device to have.
#define DEVICE_IP          "10.0.0.1"

// The Gateway address where we wish to send packets.
// This will commonly be our access point.
#define DEVICE_GW          "10.1.0.3"

// The netmask specification.
#define DEVICE_NETMASK     "255.0.0.0"

EventGroupHandle_t wifi_group;
#define BIT_0    ( 1 << 0 ) //event bit access_point_task Delete
#define BIT_1    ( 1 << 1 )//event bit Socket created

//////////////////////////////////////////////////////////////////////////////////////
///	END WIFI  Block
//////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////
///	UDP
//////////////////////////////////////////////////////////////////////////////////////

  struct data {
    char str[42];
    int  len ; //len str
    int16_t  key; //hz
};
  QueueHandle_t xQueue1; /// UDP date stream

  //////////////////////////////////////////////////////////////////////////////////////
  ///	 End UDP
  //////////////////////////////////////////////////////////////////////////////////////


#endif /* MAIN_HEAD_H_ */
