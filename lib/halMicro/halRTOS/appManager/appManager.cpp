#include "appManager.hpp"
//#include "esp_task_wdt.h"
// ── Definición real de las colas (aquí vive la memoria) ──
QueueHandle_t commandQueue = nullptr;
QueueHandle_t statusQueue  = nullptr;
TaskHandle_t servoTaskHandle = nullptr;
SemaphoreHandle_t semNemaEX = nullptr;
SemaphoreHandle_t mutexNemaEX = nullptr;
SemaphoreHandle_t semNemaES = nullptr;
SemaphoreHandle_t mutexNemaES = nullptr;
SemaphoreHandle_t semNemaBA = nullptr;
SemaphoreHandle_t mutexNemaBA = nullptr;
SemaphoreHandle_t semNemaAX = nullptr;
SemaphoreHandle_t mutexNemaAX = nullptr;
TaskHandle_t excavandoTaskHandle = nullptr;
SemaphoreHandle_t mutexEXCA = nullptr;
// ── Instancias privadas al translation unit ──
static RosConnection rosManager;
static DriversTask   driversManager;

void AppManager::start(){
    neoLED.begin();
    createQueues();
    createSemaphores();
    launchTasks();
}

void AppManager::createQueues(){
    commandQueue = xQueueCreate(16, sizeof(RosCommand));
    statusQueue  = xQueueCreate(16, sizeof(DriverStatus));
}

void AppManager::createSemaphores(){
    semNemaEX = xSemaphoreCreateBinary();
    mutexNemaEX = xSemaphoreCreateMutex();
    //nemaES
    semNemaES = xSemaphoreCreateBinary();
    mutexNemaES = xSemaphoreCreateMutex();
    //nemaBA
    semNemaBA = xSemaphoreCreateBinary();
    mutexNemaBA = xSemaphoreCreateMutex();
    //nemaAX
    semNemaAX = xSemaphoreCreateBinary();
    mutexNemaAX = xSemaphoreCreateMutex();
    //semaforo para la excavadora
    mutexEXCA = xSemaphoreCreateMutex();
}

void AppManager::launchTasks(){
    xTaskCreatePinnedToCore(rosTask,     "rosTask",     32768, nullptr, 7, nullptr, 0);
    xTaskCreatePinnedToCore(driversTask, "driversTask", 4096, nullptr, 6, nullptr, 1);
    xTaskCreatePinnedToCore(servoTask,  "servoTask",  2048,  nullptr, 3, &servoTaskHandle,  1);
    xTaskCreatePinnedToCore(nemaEXTask, "nemaEXTask", 2048, nullptr, 4, nullptr, 1);
    xTaskCreatePinnedToCore(nemaESTask, "nemaESTask", 2048, nullptr, 4, nullptr, 1);
    xTaskCreatePinnedToCore(nemaBATask, "nemaBATask", 2048, nullptr, 4, nullptr, 1);
    xTaskCreatePinnedToCore(nemaAXTask, "nemaAXTask", 2048, nullptr, 4, nullptr, 1);
    xTaskCreatePinnedToCore(excavandoTask, "excavandoTask", 4096, nullptr, 5, &excavandoTaskHandle, 1);
    xTaskCreatePinnedToCore(stopRC_MTR1, "stopRC_MTR1", 2048, nullptr, 5, nullptr, 1);
}

void AppManager::rosTask(void* pvParameters){
    //esp_task_wdt_delete(NULL);
    rosManager.init();
    while(true){
        rosManager.update();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void AppManager::driversTask(void* pvParameters){
    driversManager.init();
    while(true){
        driversManager.update();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

// La tarea: duerme con Task Notification, corre hasta que ambos servos lleguen,
// luego vuelve a dormir. Si llega una nueva notificación mientras corre,
// simplemente continúa sin reiniciarse.
void AppManager::servoTask(void* pvParameters){
    while(true){
        // Bloquea indefinidamente hasta que driversTask notifique
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // Corre el update hasta que ambos servos lleguen al objetivo
        while(!servoDisp.isAtTarget() || !servoCube.isAtTarget()){
            servoDisp.update(false);//velocidad constante
            servoCube.update(true);//empieza rapido termina lento
            vTaskDelay(pdMS_TO_TICKS(10));  // 10 ms = dt razonable para el cálculo
        }
    }
}
//tarea excavando ando
void AppManager::excavandoTask(void* pvParameters){
    while(true){
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // ── Arrancar los dos motores UNA sola vez ──
        if(xSemaphoreTake(mutexEXCA, pdMS_TO_TICKS(100)) == pdTRUE){
            exca.setVel1(70);
            exca.setVel2(125);
            exca.moveMTR1(true);
            exca.moveMTR2(true);
            xSemaphoreGive(mutexEXCA);
        }

        // ── 5 ciclos de limit switch ──
        for(uint8_t ciclo = 0; ciclo < 10; ciclo++){

            // Espera a que el limitEX se presione (pasa de true -> false)
            while(limitEX.readState())
                vTaskDelay(pdMS_TO_TICKS(10));

            if(ciclo < 9){
                // Ciclos 1-4: retrocede MTR1 durante 2 segundos, luego avanza de nuevo
                if(xSemaphoreTake(mutexEXCA, pdMS_TO_TICKS(100)) == pdTRUE){
                    exca.setVel1(125);
                    exca.moveMTR1(false);
                    xSemaphoreGive(mutexEXCA);
                }
                vTaskDelay(pdMS_TO_TICKS(250));

                if(xSemaphoreTake(mutexEXCA, pdMS_TO_TICKS(100)) == pdTRUE){
                    exca.setVel1(50);
                    exca.moveMTR1(true);
                    xSemaphoreGive(mutexEXCA);
                }

            } else {
                // Ciclo 5 (último): para MTR1, MTR2 sigue 5 segundos
                if(xSemaphoreTake(mutexEXCA, pdMS_TO_TICKS(100)) == pdTRUE){
                    exca.stopMTR1();
                    xSemaphoreGive(mutexEXCA);
                }
                vTaskDelay(pdMS_TO_TICKS(60000));

                // Para ambos, luego MTR1 en reversa durante 3 segundos
                if(xSemaphoreTake(mutexEXCA, pdMS_TO_TICKS(100)) == pdTRUE){
                    exca.stop();
                    xSemaphoreGive(mutexEXCA);
                }
                vTaskDelay(pdMS_TO_TICKS(100)); // pequeña pausa antes de reversa

                if(xSemaphoreTake(mutexEXCA, pdMS_TO_TICKS(100)) == pdTRUE){
                    exca.setVel1(70);
                    exca.moveMTR1(false);
                    xSemaphoreGive(mutexEXCA);
                }
                // vTaskDelay(pdMS_TO_TICKS(5500));
                // Espera a que el limitES se presione (pasa de true -> false)
                while(limitES.readState())
                    vTaskDelay(pdMS_TO_TICKS(10));

                if(xSemaphoreTake(mutexEXCA, pdMS_TO_TICKS(100)) == pdTRUE){
                    exca.stop();
                    xSemaphoreGive(mutexEXCA);
                }
            }
        }
        // Tarea termina su ciclo -> vuelve a ulTaskNotifyTake y duerme
    }
}
//Esta tarea se encarga de monitoriar si el gusano se mueve, y de detenerlo cuando llegue al limit correspondiente
void AppManager::stopRC_MTR1(void* pvParameters){
    while(true){
        if(exca.mtr1Move){//cuando se esta moviendo, 
            if(exca.mtr1Direccion){//gusano va para abajo
                if(!limitEX.readState())//limitEX, lo detiene al presionarlo
                    exca.stopMTR1();
            }else{//gusano va para arriba
                if(!limitES.readState())//en esta dirrecion lo detiene limitES
                    exca.stopMTR1();
            }

        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
//NEMA Task
void AppManager::nemaEXTask(void* pvParameters){
    while(true){
        // BLOQUEADO aquí hasta que driversTask haga xSemaphoreGive()
        // No consume CPU mientras espera (FreeRTOS la pone en estado BLOCKED)
        // portMAX_DELAY = espera indefinidamente
        xSemaphoreTake(semNemaEX, portMAX_DELAY);

        if(xSemaphoreTake(mutexNemaEX, pdMS_TO_TICKS(100)) == pdTRUE){
            nemaEX.resetContStep();
            nemaEX.setEnable(true);
            xSemaphoreGive(mutexNemaEX);
        }

        uint32_t timeSleep = nemaEX.getTimeSleep();

        bool sigueMoviendo = true;
        while(sigueMoviendo){

            if(nemaEX.getStopNema()){
                nemaEX.setEnable(false);
                break;
            }

            if(xSemaphoreTake(mutexNemaEX, pdMS_TO_TICKS(25)) == pdTRUE){
                nemaEX.writeStep(true);
                xSemaphoreGive(mutexNemaEX);
            }
            vTaskDelay(pdMS_TO_TICKS(timeSleep));

            if(xSemaphoreTake(mutexNemaEX, pdMS_TO_TICKS(25)) == pdTRUE){
                nemaEX.writeStep(false);
                sigueMoviendo = nemaEX.sumContStep();
                xSemaphoreGive(mutexNemaEX);
            }
            vTaskDelay(pdMS_TO_TICKS(timeSleep));

            //En caso de que se detecte el limit, se para en seco el nema
            //sigueMoviendo = limitEX.readState();
            //ya no es necesario frenarel nema con este limit
            //ahora este limit sera para freanr el gusano
            //y hacer imposibe que caiga del modulo
        }
        // Movimiento completado -> deshabilitar motor
        if(xSemaphoreTake(mutexNemaEX, pdMS_TO_TICKS(100)) == pdTRUE){
            nemaEX.setEnable(false);
            xSemaphoreGive(mutexNemaEX);
        }
    }
}

void AppManager::nemaESTask(void* pvParameters){
    while(true){
        xSemaphoreTake(semNemaES, portMAX_DELAY);

        if(xSemaphoreTake(mutexNemaES, pdMS_TO_TICKS(100)) == pdTRUE){
            nemaES.resetContStep();
            nemaES.setEnable(true);
            xSemaphoreGive(mutexNemaES);
        }

        uint32_t timeSleep = nemaES.getTimeSleep();

        bool sigueMoviendo = true;
        while(sigueMoviendo){

            if(nemaES.getStopNema()){
                nemaES.setEnable(false);
                break;
            }

            if(xSemaphoreTake(mutexNemaES, pdMS_TO_TICKS(25)) == pdTRUE){
                nemaES.writeStep(true);
                xSemaphoreGive(mutexNemaES);
            }
            vTaskDelay(pdMS_TO_TICKS(timeSleep));

            if(xSemaphoreTake(mutexNemaES, pdMS_TO_TICKS(25)) == pdTRUE){
                nemaES.writeStep(false);
                sigueMoviendo = nemaES.sumContStep();
                xSemaphoreGive(mutexNemaES);
            }
            vTaskDelay(pdMS_TO_TICKS(timeSleep));

            //En caso de que se detecte el limit, se para en seco el nema
            sigueMoviendo = limitES.readState();
        }
        // Movimiento completado -> deshabilitar motor
        if(xSemaphoreTake(mutexNemaES, pdMS_TO_TICKS(100)) == pdTRUE){
            nemaES.setEnable(false);
            xSemaphoreGive(mutexNemaES);
        }
    }
}

void AppManager::nemaBATask(void* pvParameters){
    while(true){
        xSemaphoreTake(semNemaBA, portMAX_DELAY);

        if(xSemaphoreTake(mutexNemaBA, pdMS_TO_TICKS(100)) == pdTRUE){
            nemaBA.resetContStep();
            nemaBA.setEnable(true);
            xSemaphoreGive(mutexNemaBA);
        }

        uint32_t timeSleep = nemaBA.getTimeSleep();

        bool sigueMoviendo = true;
        while(sigueMoviendo){

            if(nemaBA.getStopNema()){
                nemaBA.setEnable(false);
                break;
            }

            if(xSemaphoreTake(mutexNemaBA, pdMS_TO_TICKS(25)) == pdTRUE){
                nemaBA.writeStep(true);
                xSemaphoreGive(mutexNemaBA);
            }
            vTaskDelay(pdMS_TO_TICKS(timeSleep));

            if(xSemaphoreTake(mutexNemaBA, pdMS_TO_TICKS(25)) == pdTRUE){
                nemaBA.writeStep(false);
                sigueMoviendo = nemaBA.sumContStep();
                xSemaphoreGive(mutexNemaBA);
            }
            vTaskDelay(pdMS_TO_TICKS(timeSleep));
        }
        // Movimiento completado -> deshabilitar motor
        if(xSemaphoreTake(mutexNemaBA, pdMS_TO_TICKS(100)) == pdTRUE){
            nemaBA.setEnable(false);
            xSemaphoreGive(mutexNemaBA);
        }
    }
}

void AppManager::nemaAXTask(void* pvParameters){
    while(true){
        xSemaphoreTake(semNemaAX, portMAX_DELAY);

        if(xSemaphoreTake(mutexNemaAX, pdMS_TO_TICKS(100)) == pdTRUE){
            nemaAX.resetContStep();
            nemaAX.setEnable(true);
            xSemaphoreGive(mutexNemaAX);
        }

        uint32_t timeSleep = nemaAX.getTimeSleep();

        bool sigueMoviendo = true;
        while(sigueMoviendo){

            if(nemaAX.getStopNema()){
                nemaAX.setEnable(false);
                break;
            }

            if(xSemaphoreTake(mutexNemaAX, pdMS_TO_TICKS(25)) == pdTRUE){
                nemaAX.writeStep(true);
                xSemaphoreGive(mutexNemaAX);
            }
            vTaskDelay(pdMS_TO_TICKS(timeSleep));

            if(xSemaphoreTake(mutexNemaAX, pdMS_TO_TICKS(25)) == pdTRUE){
                nemaAX.writeStep(false);
                sigueMoviendo = nemaAX.sumContStep();
                xSemaphoreGive(mutexNemaAX);
            }
            vTaskDelay(pdMS_TO_TICKS(timeSleep));
        }
        // Movimiento completado -> deshabilitar motor
        if(xSemaphoreTake(mutexNemaAX, pdMS_TO_TICKS(100)) == pdTRUE){
            nemaAX.setEnable(false);
            xSemaphoreGive(mutexNemaAX);
        }
    }
}

void AppManager::idle(){
    vTaskDelay(portMAX_DELAY);
}
