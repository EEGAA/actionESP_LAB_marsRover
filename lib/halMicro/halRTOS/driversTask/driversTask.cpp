#include "driversTask.hpp"

// Referencias a tus objetos de driver globales
// (los mismos que ya usas en ACTIONS.cpp)
extern LEDgen   myLed;
extern SERVOgen servoDisp;
// extern MyMtrH  motorExc;  etc.

// Timer local para reportar el contador de segundos
static uint32_t lastSecTick = 0;

void DriversTask::init() {
    // Inicializa hardware aquí si tus constructores no lo hacen
    // myLed.init();
    // servoDisp.init();
}

void DriversTask::update() {
    // ── 1. Consumir comandos de ROS ──
    RosCommand cmd;
    while (xQueueReceive(commandQueue, &cmd, 0) == pdTRUE) {
        switch (cmd.type) {
            case CmdType::LED_SET:
                myLed.setState(cmd.boolVal);
                break;
            case CmdType::SERVO_MOVE:
                servoDisp.moveAng(cmd.uint8Val);
                break;
            // Añade: MOTOR_SET, STEPPER_MOVE, etc.
        }
    }

    // ── 2. Lógica periódica de drivers (ejemplo: tick del counter) ──
    uint32_t now = xTaskGetTickCount() * portTICK_PERIOD_MS;
    if (now - lastSecTick >= 1000) {
        lastSecTick = now;
        DriverStatus status;
        status.type  = StatusType::COUNTER_TICK;
        status.value = 0;
        xQueueSend(statusQueue, &status, 0);
    }

    // ── 3. Aquí va tu lógica de excavación/dispensación ──
    // excavationFSM.update();
    // dispenserFSM.update();
}
