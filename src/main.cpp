#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "../lib/ros2/rosConnection/rosConnection.hpp"

#include "../lib/halMicro/halRTOS/sharedData/sharedData.hpp"
#include "../lib/halMicro/halRTOS/driversTask/driversTask.hpp"
// ── Definición de las colas globales ──
QueueHandle_t commandQueue;   // RosNode → DriversTask
QueueHandle_t statusQueue;    // DriversTask → RosNode

// ── Instancias ──
RosConnection rosManager;
DriversTask   driversManager;

// ──────────────────────────────────────────
//  TASK Core 0 — micro-ROS
// ──────────────────────────────────────────
void rosTask(void* pvParameters) {
    rosManager.init();
    for (;;) {
        rosManager.update();
        vTaskDelay(pdMS_TO_TICKS(1)); // yield mínimo, evita watchdog
    }
}

// ──────────────────────────────────────────
//  TASK Core 1 — Drivers (excavación/dispensación)
// ──────────────────────────────────────────
void driversTask(void* pvParameters) {
    driversManager.init();
    for (;;) {
        driversManager.update();
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}
//RosConnection manager;
void setup(){
   // manager.init();
   // myESPinfo();
    // Crear colas antes de lanzar tasks
    commandQueue = xQueueCreate(16, sizeof(RosCommand));
    statusQueue  = xQueueCreate(16, sizeof(DriverStatus));

    // Crear tasks pinadas a su core
    xTaskCreatePinnedToCore(
        rosTask,            // función
        "rosTask",          // nombre debug
        8192,               // stack (bytes) — micro-ROS necesita bastante
        nullptr,            // parámetros
        5,                  // prioridad (más alta = más urgente)
        nullptr,            // handle (no necesario ahora)
        0                   // Core 0
    );

    xTaskCreatePinnedToCore(
        driversTask,
        "driversTask",
        4096,
        nullptr,
        4,                  // prioridad ligeramente menor que ROS
        nullptr,
        1                   // Core 1
    );
}
void loop(){
    //manager.update();
    vTaskDelay(pdMS_TO_TICKS(1000)); // loop vacío, todo corre en tasks
}
