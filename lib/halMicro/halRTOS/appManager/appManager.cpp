#include "appManager.hpp"
//#include "esp_task_wdt.h"
// ── Definición real de las colas (aquí vive la memoria) ──
QueueHandle_t commandQueue = nullptr;
QueueHandle_t statusQueue  = nullptr;
TaskHandle_t servoTaskHandle = nullptr;
SemaphoreHandle_t semNemaEX = nullptr;
SemaphoreHandle_t mutexNemaEX = nullptr;
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
}

void AppManager::launchTasks(){
    xTaskCreatePinnedToCore(rosTask,     "rosTask",     32768, nullptr, 7, nullptr, 0);
    xTaskCreatePinnedToCore(driversTask, "driversTask", 4096, nullptr, 6, nullptr, 1);
    xTaskCreatePinnedToCore(servoTask,  "servoTask",  2048,  nullptr, 3, &servoTaskHandle,  1);
    xTaskCreatePinnedToCore(nemaEXTask, "nemaEXTask", 2048, nullptr, 4, nullptr, 1);
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
        }
        // Movimiento completado -> deshabilitar motor
        if(xSemaphoreTake(mutexNemaEX, pdMS_TO_TICKS(100)) == pdTRUE){
            nemaEX.setEnable(false);
            xSemaphoreGive(mutexNemaEX);
        }
    }
}


void AppManager::idle(){
    vTaskDelay(portMAX_DELAY);
}
