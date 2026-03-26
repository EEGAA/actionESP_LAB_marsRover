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
                switch(cmd.uint8Val){
                    case 0:
                        exca.stop();
                        break;
                    case 1:
                        exca.stopMTR1();
                        break;
                    case 2:
                        exca.stopMTR2();
                        break;
                    default:
                        exca.stop();
                }
                break;
            case CmdType::RC_VELMTR1:
                exca.setVel1(cmd.uint8Val);
                break;
            case CmdType::RC_VELMTR2:
                exca.setVel2(cmd.uint8Val);
                break;
            case CmdType::RC_MoveMTR1:
                exca.moveMTR1(cmd.boolVal);
                break;
            case CmdType::RC_MoveMTR2:
                exca.moveMTR2(cmd.boolVal);
                break;

            //puenteH
            case CmdType::H_mtrMOVE:
                switch(cmd.uint8Val){
                    case 0:
                        bomba.stop();
                        break;
                    case 1:
                        bomba.moveR();
                        break;
                    case 2:
                        bomba.moveL();
                        break;
                    default:
                        bomba.stop();
                }
                break;
            case CmdType::H_mtrSetPWM:
                      bomba.setPWM(cmd.int16Val);
                break;
            //neo led
            case CmdType::NEO_LED_basic:
                switch(cmd.uint8Val){
                    case 0:
                        neoLED.LEDoff();
                        break;

                    case 1:
                        neoLED.rojo();
                        break;
                    case 2:
                        neoLED.verde();
                        break;
                    case 3:
                        neoLED.azul();
                        break;
                    case 4:
                        neoLED.blanco();
                        break;
                    default:
                        neoLED.LEDoff();
                        break;
                }
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
