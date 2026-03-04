#pragma once
#include <Arduino.h>
#include <RoboClaw.h>

// #define pinTx 39
// #define pinRx 40

#define RBW_SERIAL Serial2 //roboclaw_serial
#define RBW_BAUD 38400 //roboclaw_baudios

#define MTR1_ADDRESS 0x80  //Gusano
#define MTR2_ADDRESS 0x80 //Broca

class EXCAVA{
private:
    RoboClaw roboclaw;
    ////////MTR1///MTR2
    uint8_t velG, velB;
    int colchon;
public:
    EXCAVA(uint8_t pinTx, uint8_t pinRx);
    void setVel1(uint8_t vel_);
    void setVel2(uint8_t vel_);
    uint8_t getVel1();
    uint8_t getVel2();
    void stop();
    void stopMTR1();
    void stopMTR2();
    void moveMTR1(bool aux);
    void moveMTR2(bool aux);
};
