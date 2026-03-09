#pragma once
//Esta clase es para hacer funcionar un puente h l298
#include "../myPWM/myPWM.hpp"
class L298Ngen{
private:
    uint8_t pinA, pinB;
    PWMgen myPWM;
public:
    L298Ngen(uint8_t, uint8_t, int);
    void stop();
    void moveR();
    void moveL();
    void PWMmas(int);
    void PWMmenos(int);
    int getPWM();
};
