#include "driversTask.hpp"

// Timer local para reportar el contador de segundos
static uint32_t lastSecTick = 0;

void DriversTask::init() {
    // Inicializa hardware aquí (la mayoria de los constructores drivers ya lo hacen {igual hay metodos para cambiarlos aqui mismo si se necesita})
}

void DriversTask::update(){
    // ── 1. Consumir comandos de ROS ──
    RosCommand cmd;
    while(xQueueReceive(commandQueue, &cmd, 0) == pdTRUE){
        switch(cmd.type){
            case CmdType::LED_SET:
                myLed.setState(cmd.boolVal);
                break;
            case CmdType::SERVOdisp_MOVE:
                servoDisp.moveAng(cmd.uint8Val);
                break;
            case CmdType::SERVOcube_MOVE:
                servoCube.moveAng(cmd.uint8Val);
                break;
            // Añade: todos los demas motores
            case CmdType::RC_STOP:
                if(cmd.boolVal)
                    exca.stop();
                else
                    exca.stop();
                break;
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
