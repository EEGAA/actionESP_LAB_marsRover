#pragma once
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class NEOled{
private:
    Adafruit_NeoPixel pixels;
    static const int PIN_LED = 48;
    static const int NUM_LEDS = 1;
    int brillo;
public:
    NEOled();
    void begin();
    void LEDoff();
    void setBrillo(uint8_t);
    uint8_t getBrillo();
    void rojo();
    void verde();
    void azul();
    void blanco();
};
