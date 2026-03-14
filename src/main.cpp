#include "../lib/halMicro/halRTOS/appManager/appManager.hpp"

void setup() {
    AppManager::start();
}
void loop(){
    //manager.update();
    // vTaskDelay(pdMS_TO_TICKS(1000)); // loop vacío, todo corre en tasks
    AppManager::idle();
}
