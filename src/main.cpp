#include "../lib/halMicro/halRTOS/appManager/appManager.hpp"
void setup() {
    AppManager::start();
}
void loop(){
    AppManager::idle();
}
