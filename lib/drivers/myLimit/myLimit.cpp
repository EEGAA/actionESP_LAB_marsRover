#include "myLimit.hpp"

LIMITgen::LIMITgen(uint8_t X): pin(X) {
    pinMode(pin, INPUT);
}

bool LIMITgen::readState(){
    this->state = digitalRead(pin);
    return state;
}

bool LIMITgen::getState(){
    return state;
}

