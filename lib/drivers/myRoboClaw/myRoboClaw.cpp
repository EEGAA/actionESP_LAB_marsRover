#include "myRoboClaw.hpp"
EXCAgen::EXCAgen(uint8_t pinTx, uint8_t pinRx):
    roboclaw(&RBW_SERIAL, 10000){
    RBW_SERIAL.begin(RBW_BAUD, SERIAL_8N1, pinTx, pinRx);
    roboclaw.begin(RBW_BAUD);
    //roboclaw.SetConfig();
    colchon = 2;
    setVel1(70);
    setVel2(127);
    mtr1Move = false;
}
void EXCAgen::setVel1(uint8_t vel_){
    this->velG = constrain(vel_, 0, 127 - colchon);
}
void EXCAgen::setVel2(uint8_t vel_){
    this->velB = constrain(vel_, 0, 127 - colchon);
}
uint8_t EXCAgen::getVel1(){return velG;}
uint8_t EXCAgen::getVel2(){return velB;}

void EXCAgen::stopMTR1(){
    roboclaw.ForwardM1(MTR1_ADDRESS, 0);
    mtr1Move = false;
}
void EXCAgen::stopMTR2(){
    roboclaw.ForwardM2(MTR2_ADDRESS, 0);
}
void EXCAgen::stop(){
    stopMTR1();
    stopMTR2();
}
void EXCAgen::moveMTR1(bool aux){
    if(aux)
        roboclaw.ForwardM1(MTR1_ADDRESS, velG);
    else
        roboclaw.BackwardM1(MTR1_ADDRESS, velG);
    mtr1Direccion = aux;
    mtr1Move = true;
}
void EXCAgen::moveMTR2(bool aux){
    if(aux)
        roboclaw.ForwardM2(MTR2_ADDRESS, velB);
    else
        roboclaw.BackwardM2(MTR2_ADDRESS, velB);
}
