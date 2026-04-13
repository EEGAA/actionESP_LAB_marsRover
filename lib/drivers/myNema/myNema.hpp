#pragma once
#include <Arduino.h>

class NEMAgen{
private:
    uint8_t dir, step, enable;
    uint32_t contStep, totalStep, timeSleep;
    bool stopNema, currentDir;
public:
    NEMAgen(uint8_t dir_, uint8_t step_, uint8_t enable_);
    void setEnable(bool bnd);
    void writeDir();
    void writeStep(bool bnd);
    uint32_t getContStep();
    void resetContStep();
    bool sumContStep();
    void setTotalStep(uint32_t x);
    uint32_t getTotalStep();
    //..........pasos, direccion, delay, micros o millis
    void moveMTR(uint32_t, bool, uint32_t, bool);
    //timeSleep son milisegundos
    void setTimeSleep(uint32_t);
    uint32_t getTimeSleep();

    void setStopNema(bool);
    bool getStopNema();

    void setCurrentDir(bool);
    bool getCurrentDir();
};
