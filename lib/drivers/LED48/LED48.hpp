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
    //todos los colores
    void blanco();
    //colores primarios
    void rojo();
    void verde();
    void azul();
    //colores secundarios
    void amarillo();
    void magenta();
    void cian();
    //colores terciarios
    void naranja();
    void rosa();
    void verdeLima();
    void verdeMenta();
    void violeta();
    void azulCielo();
    //complementos
    void grisOscuro();
    void grisMedio();
    void grisClaro();
    void rojoClaro();
    void rojoIntenso();
    void verdeClaro();
    void verdeIntenso();
    void azulClaro();
    void azulIntenso();
};
