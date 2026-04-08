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
    setTimeSleep(20);
}

void NEMAgen::setEnable(bool bnd){
    if(bnd)
        digitalWrite(enable, LOW);
    else{
        digitalWrite(enable, HIGH);
        digitalWrite(dir, LOW);
        digitalWrite(step, LOW);
    }
    setStopNema(!bnd);
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

//..........pasos, direccion, delay, micros o millis
void NEMAgen::moveMTR(uint32_t pasos_, bool dir_, uint32_t time_, bool timeType_){
    setEnable(true);
    writeDir(dir_);

    for(int i = 0; i < pasos_; i++){
        writeStep(1);
        if(timeType_)
            delayMicroseconds(time_);
        else
            delay(time_);
        writeStep(0);
        if(timeType_)
            delayMicroseconds(time_);
        else
            delay(time_);
    }

    setEnable(false);
}

void NEMAgen::setTimeSleep(uint32_t ms){
    if(ms < 1) ms = 1;
    this->timeSleep = ms;
}

uint32_t NEMAgen::getTimeSleep(){
    return timeSleep;
}

void NEMAgen::setStopNema(bool bnd){
    this->stopNema = bnd;
}

bool NEMAgen::getStopNema(){
    return stopNema;
}
