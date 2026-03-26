#include "LED48.hpp"
const int NEOled::PIN_LED;
const int NEOled::NUM_LEDS;
NEOled::NEOled():
    pixels(NUM_LEDS, PIN_LED, NEO_GRB + NEO_KHZ800){}

void NEOled::begin(){
    pixels.begin();           // Inicializar el LED
    delay(20);
    setBrillo(50); // ajustar brillo (0-255)
    delay(10);
    LEDoff();
}

void NEOled::LEDoff(){
    pixels.clear();           // Apagar todos los LEDs
    pixels.show();            // Enviar datos
}

void NEOled::setBrillo(uint8_t x){
    this->brillo = x;
    pixels.setBrightness(brillo);
}

uint8_t NEOled::getBrillo(){
    return brillo;
}

void NEOled::rojo(){
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.show();
}

void NEOled::verde(){
    pixels.setPixelColor(0, pixels.Color(0, 255, 0));
    pixels.show();
}

void NEOled::azul(){
    pixels.setPixelColor(0, pixels.Color(0, 0, 255));
    pixels.show();
}

void NEOled::blanco(){
    pixels.setPixelColor(0, pixels.Color(255, 255, 255));
    pixels.show();
}
