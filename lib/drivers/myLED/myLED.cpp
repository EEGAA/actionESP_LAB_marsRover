#include "myLED.hpp"

LEDgen::LEDgen(uint8_t pin_): pin(pin_) {
    pinMode(pin, OUTPUT);
    LEDof();
}
void LEDgen::setState(bool bnd){
    this->state = bnd;
    writeLED();
}
void LEDgen::LEDon(){
    setState(true);
    writeLED();
}
void LEDgen::LEDof(){
    setState(false);
    writeLED();
}
void LEDgen::switchState(){
    setState(!state);
    writeLED();
}
void LEDgen::writeLED(){
    digitalWrite(pin, state);
}
bool LEDgen::getState(){
    return state;
}
