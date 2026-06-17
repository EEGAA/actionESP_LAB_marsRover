#include "LED48.hpp"
const int NEOled::PIN_LED;
const int NEOled::NUM_LEDS;
NEOled::NEOled():
    pixels(NUM_LEDS, PIN_LED, NEO_GRB + NEO_KHZ800){}

void NEOled::begin(){
    pixels.begin();           // Inicializar el LED
    delay(20);
    setBrillo(5); // ajustar brillo (0-255)
    // delay(10);
    LEDoff();
}

void NEOled::LEDoff(){
    pixels.clear();           // Apagar todos los LEDs
    pixels.show();            // Enviar datos
}

void NEOled::setBrillo(uint8_t x){
    this->brillo = constrain(x, 0, 255);
    pixels.setBrightness(brillo);
    pixels.show();
}

uint8_t NEOled::getBrillo(){
    return brillo;
}

void NEOled::blanco(){
    pixels.setPixelColor(0, pixels.Color(255, 255, 255));
    pixels.show();
}
//primarios
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
//secundarios
void NEOled::amarillo(){
    pixels.setPixelColor(0, pixels.Color(255, 255, 0));
    pixels.show();
}

void NEOled::magenta(){
    pixels.setPixelColor(0, pixels.Color(255, 0, 255));
    pixels.show();
}

void NEOled::cian(){
    pixels.setPixelColor(0, pixels.Color(0, 255, 255));
    pixels.show();
}
//terciarios
void NEOled::naranja(){
    pixels.setPixelColor(0, pixels.Color(255, 128, 0));
    pixels.show();
}
void NEOled::rosa(){
    pixels.setPixelColor(0, pixels.Color(255, 0, 128));
    pixels.show();
}
void NEOled::verdeLima(){
    pixels.setPixelColor(0, pixels.Color(128, 255, 0));
    pixels.show();
}
void NEOled::verdeMenta(){
    pixels.setPixelColor(0, pixels.Color(0, 255, 128));
    pixels.show();
}
void NEOled::violeta(){
    pixels.setPixelColor(0, pixels.Color(128, 0, 255));
    pixels.show();
}
void NEOled::azulCielo(){
    pixels.setPixelColor(0, pixels.Color(0, 128, 255));
    pixels.show();
}
//complementos
void NEOled::grisOscuro(){
    pixels.setPixelColor(0, pixels.Color(32, 32, 32));
    pixels.show();
}
void NEOled::grisMedio(){
    pixels.setPixelColor(0, pixels.Color(128, 128, 128));
    pixels.show();
}
void NEOled::grisClaro(){
    pixels.setPixelColor(0, pixels.Color(192, 192, 192));
    pixels.show();
}
void NEOled::rojoClaro(){
    pixels.setPixelColor(0, pixels.Color(255, 64, 64));
    pixels.show();
}
void NEOled::rojoIntenso(){
    pixels.setPixelColor(0, pixels.Color(255, 32, 32));
    pixels.show();
}
void NEOled::verdeClaro(){
    pixels.setPixelColor(0, pixels.Color(64, 255, 64));
    pixels.show();
}
void NEOled::verdeIntenso(){
    pixels.setPixelColor(0, pixels.Color(32, 255, 32));
    pixels.show();
}
void NEOled::azulClaro(){
    pixels.setPixelColor(0, pixels.Color(64, 64, 255));
    pixels.show();
}
void NEOled::azulIntenso(){
    pixels.setPixelColor(0, pixels.Color(32, 32, 255));
    pixels.show();
}
