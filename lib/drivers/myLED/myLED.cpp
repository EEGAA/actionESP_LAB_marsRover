#include "myLED.hpp"

LEDgen::LEDgen(uint8_t pin_): pin(pin_) {
    pinMode(pin, OUTPUT);
    LEDoff();
}
void LEDgen::setState(bool bnd){
    this->state = bnd;
    writeLED();
}
void LEDgen::LEDon(){
    setState(true);
}
void LEDgen::LEDoff(){
    setState(false);
}
void LEDgen::switchState(){
    setState(!state);
}
void LEDgen::writeLED(){
    digitalWrite(pin, state);
}
bool LEDgen::getState(){
    return state;
}
