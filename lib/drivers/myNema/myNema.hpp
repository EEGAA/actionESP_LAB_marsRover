#pragma once
#include <Arduino.h>

class NEMAgen{
private:
    uint8_t dir, step, enable;
public:
    NEMAgen(uint8_t dir_, uint8_t step_, uint8_t enable_);
    void setEnable(bool bnd);
    void printDir(bool bnd);

};
