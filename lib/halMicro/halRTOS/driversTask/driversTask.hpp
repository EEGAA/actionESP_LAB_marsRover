#pragma once
#include "../sharedData/sharedData.hpp"
// Incluye tus drivers según los uses:
// #include "../myLED/myLED.hpp"
// #include "../myServo/myServo.hpp"
// #include "../myMtrH/myMtrH.hpp"
// #include "../myNema/myNema.hpp"
// etc.
#include "../../espLayer/espLayer.hpp"

class DriversTask {
public:
    void init();    // inicializa hardware
    void update();  // consume commandQueue, ejecuta drivers, reporta statusQueue
};
