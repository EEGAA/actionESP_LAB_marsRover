#pragma once
#include <Arduino.h>

class NEMAgen{
private:
    uint8_t dir, step, enable;
    uint32_t contStep, totalStep;
public:
    NEMAgen(uint8_t dir_, uint8_t step_, uint8_t enable_);
    void setEnable(bool bnd);
    void setDir(bool bnd);
    void setStep(bool bnd);
    uint32_t getContStep();
    void resetContStep();
    bool sumContStep();
    void setTotalStep(uint32_t x);
    uint32_t getTotalStep();
};
