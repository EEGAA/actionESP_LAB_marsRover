#pragma once
#include <myPWM.hpp>

class Servo {
private:
    PWMgen thisPWM;
    int minPulso, maxPulso, periodo;
    int ADCmax;
public:
    Servo(int freq_, int chanel_, int resolution_, int minPulso_, int maxPulso_, int pin_);
    void moveAng(int angulo);   // 0 a 180 grados
    void sendPWM(float pulso_);
    int getADCmax();
};
