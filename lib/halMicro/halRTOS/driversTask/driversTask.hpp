#pragma once
#include "../sharedData/sharedData.hpp"
#include "../../espLayer/espLayer.hpp"

class DriversTask {
public:
    void init();    // inicializa hardware
    void update();  // consume commandQueue, ejecuta drivers, reporta statusQueue
};
