#include "myNema.hpp"

NEMAgen::NEMAgen(uint8_t dir_, uint8_t step_, uint8_t enable_){
    this->dir = dir_;
    this->step = step_;
    this->enable = enable_;
    pinMode(dir, OUTPUT);
    pinMode(step, OUTPUT);
    pinMode(enable, OUTPUT);
    setEnable(false);
}

void NEMAgen::setEnable(bool bnd){
    if(bnd)
        digitalWrite(enable, LOW);
    else{
        digitalWrite(enable, HIGH);
        digitalWrite(dir, LOW);
        digitalWrite(step, LOW);
    }
}

void NEMAgen::printDir(bool bnd){
    digitalWrite(dir, bnd);
}
