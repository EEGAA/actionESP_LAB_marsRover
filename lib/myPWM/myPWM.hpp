#pragma once
#include <Arduino.h>

class PWMgen{
private:
    int pwm, freq, chanel, resolution, pin, ADCmax;
public:
    PWMgen(int freq_, int chanel_, int resolution_, int pin_);
    int getPWM();
    void setPWM(int x);
    void stopPWM();
    void startPWM();
    int getADCmax();
};
