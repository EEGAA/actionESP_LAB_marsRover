#include "myNema.hpp"

NEMAgen::NEMAgen(uint8_t dir_, uint8_t step_, uint8_t enable_){
    this->dir = dir_;
    this->step = step_;
    this->enable = enable_;
    pinMode(dir, OUTPUT);
    pinMode(step, OUTPUT);
    pinMode(enable, OUTPUT);
    resetContStep();
    setTotalStep(1);
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

void NEMAgen::writeDir(bool bnd){
    digitalWrite(dir, bnd);
}

void NEMAgen::writeStep(bool bnd){
    digitalWrite(step, bnd);
}
uint32_t NEMAgen::getContStep(){
    return contStep;
}
void NEMAgen::resetContStep(){
    this->contStep = 0;
}
bool NEMAgen::sumContStep(){
    if(contStep == totalStep)
        return false;
    else
        contStep++;
    return true;
}
void NEMAgen::setTotalStep(uint32_t x){
    this->totalStep = x;
}
uint32_t NEMAgen::getTotalStep(){
    return totalStep;
}
