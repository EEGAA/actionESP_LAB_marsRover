#include "myRoboClaw.hpp"
EXCAVA::EXCAVA(uint8_t pinTx, uint8_t pinRx):
    roboclaw(&RBW_SERIAL, 10000){
    RBW_SERIAL.begin(RBW_BAUD, SERIAL_8N1, pinTx, pinRx);
    roboclaw.begin(RBW_BAUD);
    //roboclaw.SetConfig();
    colchon = 2;
    this->velG = constrain(124, 0, 70 - colchon);;
    this->velB = constrain(124, 0, 127 - colchon);;
}
void EXCAVA::setVel1(uint8_t vel_){
    this->velG = constrain(vel_, 0, 127 - colchon);
}
void EXCAVA::setVel2(uint8_t vel_){
    this->velB = constrain(vel_, 0, 127 - colchon);
}
uint8_t EXCAVA::getVel1(){return velG;}
uint8_t EXCAVA::getVel2(){return velB;}

void EXCAVA::stopMTR1(){
    roboclaw.ForwardM1(MTR1_ADDRESS, 0);
}
void EXCAVA::stopMTR2(){
    roboclaw.ForwardM2(MTR2_ADDRESS, 0);
}
void EXCAVA::stop(){
    stopMTR1();
    stopMTR2();
}
void EXCAVA::moveMTR1(bool aux){
    if(aux)
        roboclaw.ForwardM1(MTR1_ADDRESS, velG);
    else
        roboclaw.BackwardM1(MTR1_ADDRESS, velG);
}
void EXCAVA::moveMTR2(bool aux){
    if(aux)
        roboclaw.ForwardM2(MTR2_ADDRESS, velB);
    else
        roboclaw.BackwardM2(MTR2_ADDRESS, velB);
}
