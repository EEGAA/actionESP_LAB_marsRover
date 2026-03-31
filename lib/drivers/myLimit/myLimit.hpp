#pragma once
#include <Arduino.h>

class LIMITgen{
private:
    uint8_t pin;
    bool state;
public:
    LIMITgen(uint8_t);
    bool readState();
    bool getState();
};
