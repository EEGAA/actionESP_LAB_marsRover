#pragma once
#include <Arduino.h>
#include <RoboClaw.h>

#define pinTx 39
#define pinRx 40


#define RBW_SERIAL Serial2 //roboclaw_serial
#define RBW_BAUD 38400 //roboclaw_baudios

RoboClaw roboclaw(&RBW_SERIAL, 10000);

#define MTR1_ADDRESS 0x80  //Gusano
#define MTR2_ADDRESS 0x80 //Broca

void excavadoraSetup(){
    RBW_SERIAL.begin(RBW_BAUD, SERIAL_8N1, pinTx, pinRx);
    roboclaw.begin(RBW_BAUD);
    //roboclaw.SetConfig();
}


class EXCAVA{
private:
    int colchon = 2;
    ////////MTR1///MTR2
    uint8_t velG, velB;
public:
    EXCAVA(){
        this->velG = constrain(124, 0, 70 - colchon);;
        this->velB = constrain(124, 0, 127 - colchon);;
        excavadoraSetup();
    }
    void setVel1(uint8_t vel_){this->velG = constrain(vel_, 0, 127 - colchon);}
    void setVel2(uint8_t vel_){this->velB = constrain(vel_, 0, 127 - colchon);}
    uint8_t getVel1(){return velG;}
    uint8_t getVel2(){return velB;}

    void stop(){
        roboclaw.ForwardM1(MTR1_ADDRESS, 0);
        roboclaw.ForwardM2(MTR2_ADDRESS, 0);
    }
    void moveMTR1(bool aux){
        if(aux)
            roboclaw.ForwardM1(MTR1_ADDRESS, velG);
        else
            roboclaw.BackwardM1(MTR1_ADDRESS, velG);
    }
    void moveMTR2(bool aux){
        if(aux)
            roboclaw.ForwardM2(MTR2_ADDRESS, velB);
        else
            roboclaw.BackwardM2(MTR2_ADDRESS, velB);
    }
};
