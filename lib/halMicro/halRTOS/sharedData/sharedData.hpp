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
    NEMA_STOP,
};
//La siguiente estructura es para que los nema, pueda recibir, bien bien
// el mensaje custom
struct NemaMSGS{
    uint32_t pasos;
    bool     direccion;
};


struct RosCommand {
    CmdType type;
    union {
        bool    boolVal;
        uint8_t uint8Val;
        int16_t int16Val;
        uint32_t uint32Val;
        NemaMSGS nemaVal;
        //float   floatVal;
    };
};

// ── Tipos de estado que Drivers pueden reportar a ROS ──
enum class StatusType : uint8_t {
    COUNTER_TICK,   // señal para publicar counter
    // aqui tambien se tienen que modificar/agregar cosas
    SIGNAL_LIMIT_EX,
    SIGNAL_LIMIT_ES,
};

struct DriverStatus {
    StatusType type;
    int32_t    value;
    // bool       boolVal;
};

// ── Handles globales (definidos en main.cpp) ──
extern QueueHandle_t commandQueue;   // ROS  → Drivers
extern QueueHandle_t statusQueue;    // Drivers → ROS
extern TaskHandle_t servoTaskHandle;
//Semaforos motor nemaEX
extern SemaphoreHandle_t semNemaEX;   // Semáforo binario: dispara el movimiento de
extern SemaphoreHandle_t mutexNemaEX; // Mutex: protege acceso al objeto motor
//Semaforos nemaES
extern SemaphoreHandle_t semNemaES, mutexNemaES;
//nemaBA
extern SemaphoreHandle_t semNemaBA, mutexNemaBA;
//nemaAX
extern SemaphoreHandle_t semNemaAX, mutexNemaAX;

