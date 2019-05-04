#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/ledc.h>
#include <driver/i2c.h>
#include <esp_log.h>
#include <esp_err.h>
#include <MPU6050.h>
#include <MPU6050_6Axis_MotionApps20.h>

#define PIN_SDA 18
#define PIN_CLK 19

