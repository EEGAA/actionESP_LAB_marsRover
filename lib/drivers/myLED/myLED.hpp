#pragma once
//El motivo de este .h es crear una clase que pueda encender un led usando digitalWrite
//y ademas tener un metodo que permita si se quiere usar pwm
//por ahora solo estara el digitalWrite
#include <Arduino.h>

class LEDgen{
private:
    uint8_t pin;
    bool state;
public:
    LEDgen(uint8_t pin_);
    void setState(bool bnd);
    void LEDon();
    void LEDoff();
    void switchState();
    void writeLED();
    bool getState();
};
