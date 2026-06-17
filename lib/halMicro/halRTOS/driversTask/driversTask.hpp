#pragma once
#include "../sharedData/sharedData.hpp"
#include "../../espLayer/espLayer.hpp"

class DriversTask {
private:
    // Tempo timeAfloja, timeSube, timeEXCAVANDO;
public:
    // DriversTask(): timeAfloja(1, true), timeSube(1, true), timeEXCAVANDO(1){}
    void init();    // inicializa hardware
    void update();  // consume commandQueue, ejecuta drivers, reporta statusQueue
    // void EXCAVANDOgen();
};
