#include "appManager.hpp"
//#include "esp_task_wdt.h"
// ── Definición real de las colas (aquí vive la memoria) ──
QueueHandle_t commandQueue = nullptr;
QueueHandle_t statusQueue  = nullptr;
TaskHandle_t servoTaskHandle = nullptr;
// ── Instancias privadas al translation unit ──
static RosConnection rosManager;
static DriversTask   driversManager;

void AppManager::start(){
    neoLED.begin();
    createQueues();
    launchTasks();
}

void AppManager::createQueues(){
    commandQueue = xQueueCreate(16, sizeof(RosCommand));
    statusQueue  = xQueueCreate(16, sizeof(DriverStatus));
}

void AppManager::launchTasks(){
    xTaskCreatePinnedToCore(rosTask,     "rosTask",     32768, nullptr, 5, nullptr, 0);
    xTaskCreatePinnedToCore(driversTask, "driversTask", 4096, nullptr, 4, nullptr, 1);
    xTaskCreatePinnedToCore(servoTask,  "servoTask",  2048,  nullptr, 3, &servoTaskHandle,  1);
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
void AppManager::servoTask(void* pvParameters) {
    while (true) {
        // Bloquea indefinidamente hasta que driversTask notifique
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // Corre el update hasta que ambos servos lleguen al objetivo
        while (!servoDisp.isAtTarget() || !servoCube.isAtTarget()) {
            servoDisp.update();
            servoCube.update();
            vTaskDelay(pdMS_TO_TICKS(10));  // 10 ms = dt razonable para el cálculo
        }
    }
}




void AppManager::idle(){
    vTaskDelay(portMAX_DELAY);
}
