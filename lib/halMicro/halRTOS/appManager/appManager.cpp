#include "appManager.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../sharedData/sharedData.hpp"
#include "../driversTask/driversTask.hpp"
#include "../../../ros2/rosConnection/rosConnection.hpp"

// ── Definición real de las colas (aquí vive la memoria) ──
QueueHandle_t commandQueue = nullptr;
QueueHandle_t statusQueue  = nullptr;

// ── Instancias privadas al translation unit ──
static RosConnection rosManager;
static DriversTask   driversManager;

void AppManager::start(){
    createQueues();
    launchTasks();
}

void AppManager::createQueues(){
    commandQueue = xQueueCreate(16, sizeof(RosCommand));
    statusQueue  = xQueueCreate(16, sizeof(DriverStatus));
}

void AppManager::launchTasks(){
    xTaskCreatePinnedToCore(rosTask,     "rosTask",     8192, nullptr, 5, nullptr, 0);
    xTaskCreatePinnedToCore(driversTask, "driversTask", 4096, nullptr, 4, nullptr, 1);
}

void AppManager::rosTask(void* pvParameters){
    rosManager.init();
    while(true){
        rosManager.update();
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

void AppManager::driversTask(void* pvParameters){
    driversManager.init();
    while(true){
        driversManager.update();
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

void AppManager::idle(){
    vTaskDelay(portMAX_DELAY);
}
