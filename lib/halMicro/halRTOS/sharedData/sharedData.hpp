#pragma once
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>

// ── Tipos de comando que ROS puede enviar a los drivers ──
enum class CmdType : uint8_t {
    LED_SET,        // bool
    SERVO_MOVE,     // uint8 ángulo
    // añade aquí: MOTOR_SET, STEPPER_MOVE, etc.
};

struct RosCommand {
    CmdType type;
    union {
        bool    boolVal;
        uint8_t uint8Val;
        int32_t int32Val;
        float   floatVal;
    };
};

// ── Tipos de estado que Drivers pueden reportar a ROS ──
enum class StatusType : uint8_t {
    COUNTER_TICK,   // señal para publicar counter
    // añade: EXCAVATION_DONE, DISPENSE_DONE, ERROR, etc.
};

struct DriverStatus {
    StatusType type;
    int32_t    value;
};

// ── Handles globales (definidos en main.cpp) ──
extern QueueHandle_t commandQueue;   // ROS  → Drivers
extern QueueHandle_t statusQueue;    // Drivers → ROS
