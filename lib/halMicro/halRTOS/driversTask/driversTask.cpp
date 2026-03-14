#include "driversTask.hpp"

// aqui se usa todo lo de espLayer.hpp (ya esta declarado en driversTask.hpp)
// extern LEDgen   myLed;
// extern SERVOgen servoDisp;
// extern MyMtrH  motorExc;  etc.

// Timer local para reportar el contador de segundos
static uint32_t lastSecTick = 0;

void DriversTask::init() {
    // Inicializa hardware aquí (la mayoria de los constructores drivers ya lo hacen {igual hay metodos para cambiarlos aqui mismo si se necesita})
    // myLed.init();
    // servoDisp.init();
}

void DriversTask::update(){
    // ── 1. Consumir comandos de ROS ──
    RosCommand cmd;
    while(xQueueReceive(commandQueue, &cmd, 0) == pdTRUE){
        switch(cmd.type){
            case CmdType::LED_SET:
                myLed.setState(cmd.boolVal);
                break;
            case CmdType::SERVO_MOVE:
                servoDisp.moveAng(cmd.uint8Val);
                break;
            // Añade: todos los demas motores
        }
    }

    // ── 2. Lógica periódica de drivers (ejemplo: tick del counter) ──
    uint32_t now = xTaskGetTickCount() * portTICK_PERIOD_MS;
    if(now - lastSecTick >= 1000){
        lastSecTick = now;
        DriverStatus status;
        status.type  = StatusType::COUNTER_TICK;
        status.value = 0;
        xQueueSend(statusQueue, &status, 0);
    }

    // ── 3. Aquí va lógica de excavación/dispensación ──
    // excavationFSM.update();
    // dispenserFSM.update();
}
