#pragma once
#include <Arduino.h>

class MENUgen{
private:
    //roboclaw, bomba, servos, nemas
    char M[4];

    void roboclaw_M();
    void bomba_M();
    void servos_M();
    void nemas_M();
    void generalDTA();
public:
    MENUgen();
    bool menuOption();
    void menuManager(char currentTecla);    
};