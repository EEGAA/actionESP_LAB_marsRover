#include "driversTask.hpp"

// Timers locales para reportar el contador de segundos
static uint32_t lastSecTick = 0, lastTimeLimit = 0;

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
                //servoDisp.moveAng(cmd.uint8Val);
                servoDisp.setTargetAngle(cmd.uint8Val, 360.0f);
                if (servoTaskHandle)
                    xTaskNotify(servoTaskHandle, 0, eNoAction);
                break;
            case CmdType::SERVOcube_MOVE:
                //servoCube.moveAng(cmd.uint8Val);
                servoCube.setTargetAngle(cmd.uint8Val, 270.0f);
                if (servoTaskHandle)
                    xTaskNotify(servoTaskHandle, 0, eNoAction);
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
                    case 0: neoLED.LEDoff(); break;
                    //primarios
                    case 1: neoLED.rojo(); break;
                    case 2: neoLED.verde(); break;
                    case 3: neoLED.azul(); break;
                    //secundarios
                    case 4: neoLED.amarillo(); break;
                    case 5: neoLED.magenta(); break;
                    case 6: neoLED.cian(); break;
                    //terciarios
                    case 7: neoLED.naranja(); break;
                    case 8: neoLED.rosa(); break;
                    case 9: neoLED.verdeLima(); break;
                    case 10: neoLED.verdeMenta(); break;
                    case 11: neoLED.violeta(); break;
                    case 12: neoLED.azulCielo(); break;
                    //complementos
                    case 13: neoLED.grisOscuro(); break;
                    case 14: neoLED.grisMedio(); break;
                    case 15: neoLED.grisClaro(); break;
                    case 16: neoLED.rojoClaro(); break;
                    case 17: neoLED.rojoIntenso(); break;
                    case 18: neoLED.verdeClaro(); break;
                    case 19: neoLED.verdeIntenso(); break;
                    case 20: neoLED.azulClaro(); break;
                    case 21: neoLED.azulIntenso(); break;

                    case 100: neoLED.blanco(); break;
                    default:  neoLED.LEDoff(); break;
                }
                break;
            case CmdType::NEO_LED_brillo:
                neoLED.setBrillo(cmd.uint8Val);
                break;
            case CmdType::STOPall:
                exca.stop();
                bomba.stop();
                neoLED.LEDoff();
                myLed.LEDoff();
                nemaEX.setStopNema(true);
                nemaES.setStopNema(true);
                nemaBA.setStopNema(true);
                nemaAX.setStopNema(true);
                break;
            //NEMA
            case CmdType::NEMA_EX_MOVE:
                if(xSemaphoreTake(mutexNemaEX, pdMS_TO_TICKS(100)) == pdTRUE){
                    nemaEX.setCurrentDir(cmd.nemaVal.direccion);
                    nemaEX.setTotalStep(cmd.nemaVal.pasos);
                    xSemaphoreGive(mutexNemaEX);
                }
                //libera la tarea nemaEXTask
                xSemaphoreGive(semNemaEX);
                break;
            case CmdType::NEMA_ES_MOVE:
                if(xSemaphoreTake(mutexNemaES, pdMS_TO_TICKS(100)) == pdTRUE){
                    nemaES.setCurrentDir(cmd.nemaVal.direccion);
                    nemaES.setTotalStep(cmd.nemaVal.pasos);
                    xSemaphoreGive(mutexNemaES);
                }
                //libera la tarea nemaESTask
                xSemaphoreGive(semNemaES);
                break;
            case CmdType::NEMA_BA_MOVE:
                if(xSemaphoreTake(mutexNemaBA, pdMS_TO_TICKS(100)) == pdTRUE){
                    nemaBA.setCurrentDir(cmd.nemaVal.direccion);
                    nemaBA.setTotalStep(cmd.nemaVal.pasos);
                    xSemaphoreGive(mutexNemaBA);
                }
                //libera la tarea nemaBATask
                xSemaphoreGive(semNemaBA);
                break;
            case CmdType::NEMA_AX_MOVE:
                // nemaAX.moveMTR(cmd.uint32Val, cmd.boolVal, 1000, true);
                if(xSemaphoreTake(mutexNemaAX, pdMS_TO_TICKS(100)) == pdTRUE){
                    nemaAX.setCurrentDir(cmd.nemaVal.direccion);
                    nemaAX.setTotalStep(cmd.nemaVal.pasos);
                    xSemaphoreGive(mutexNemaAX);
                }
                //libera la tarea nemaAXTask
                xSemaphoreGive(semNemaAX);
                break;
            case CmdType::NEMA_STOP:
                switch(cmd.boolVal){
                    case 0:
                        nemaEX.setStopNema(true);
                        break;
                    case 1:
                        nemaES.setStopNema(true);
                        break;
                    case 2:
                        nemaBA.setStopNema(true);
                        break;
                    case 3:
                        nemaAX.setStopNema(true);
                        break;
                    default:
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
    //cuando se consulta el pub de los limits regresa cada 1/4 [s] su satate
    if(now - lastTimeLimit >= 250){
        lastTimeLimit = now;
        DriverStatus statusLex, statusLes;
        statusLex.type = StatusType::SIGNAL_LIMIT_EX;
        xQueueSend(statusQueue, &statusLex, 0);
        statusLes.type = StatusType::SIGNAL_LIMIT_ES;
        xQueueSend(statusQueue, &statusLes, 0);
    }
    // ── 3. Aquí va lógica de excavación/dispensación ──
    // excavationFSM.update();
    // dispenserFSM.update();
}
