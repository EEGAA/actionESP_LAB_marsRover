#pragma once
#include "../sharedData/sharedData.hpp"
#include "../driversTask/driversTask.hpp"
#include "../../../ros2/rosConnection/rosConnection.hpp"

class AppManager {
public:
    // Única función pública — el main solo llama esto
    static void start();
    static void idle();
private:
    // Creación de colas y lanzamiento de tasks
    static void createQueues();
    static void launchTasks();

    // Funciones de tarea (se pasan a xTaskCreatePinnedToCore)
    static void rosTask(void* pvParameters);
    static void driversTask(void* pvParameters);
};
