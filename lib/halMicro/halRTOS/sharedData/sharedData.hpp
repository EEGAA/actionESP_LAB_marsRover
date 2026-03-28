#pragma once
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>

// ── Tipos de comando que ROS puede enviar a los drivers ──
enum class CmdType : uint8_t {
    LED_SET,        // bool
    SERVOdisp_MOVE,     // uint8 ángulo
    SERVOcube_MOVE,
    // aqui va el resto de lo que desarrolle despues
    //RoboClaw
    RC_STOP, //bool = true = stop ambos motores; cuando es false no hace nada
    RC_VELMTR1,//dan velociadad 0 a 127 a los motores gusano y broca
    RC_VELMTR2,
    RC_MoveMTR1,
    RC_MoveMTR2,
    H_mtrMOVE,
    H_mtrSetPWM,
    NEO_LED_basic,
    NEO_LED_brillo,
    STOPall,
    NEMA_EX_MOVE,
    NEMA_ES_MOVE,
    NEMA_BA_MOVE,
    NEMA_AX_MOVE,
};

struct RosCommand {
    CmdType type;
    union {
        bool    boolVal;
        uint8_t uint8Val;
        int16_t int16Val;
        uint32_t uint32Val;
        //float   floatVal;
    };
};

// ── Tipos de estado que Drivers pueden reportar a ROS ──
enum class StatusType : uint8_t {
    COUNTER_TICK,   // señal para publicar counter
    // aqui tambien se tienen que modificar/agregar cosas
};

struct DriverStatus {
    StatusType type;
    int32_t    value;
};

// ── Handles globales (definidos en main.cpp) ──
extern QueueHandle_t commandQueue;   // ROS  → Drivers
extern QueueHandle_t statusQueue;    // Drivers → ROS
