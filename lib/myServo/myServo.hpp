#pragma once
#include <myPWM.hpp>

class Servo {
private:
    PWMgen thisPWM;
    int minPulso, maxPulso, periodo;
    int ADCmax;
public:
    Servo(int freq_, int chanel_, int resolution_, int minPulso_, int maxPulso_, int pin_);
    void moveAng(int angulo);   // 0 a 180 grados
    void sendPWM(float pulso_);
    void stopPWM();
    int getADCmax();
};
//Este es un ejemplo en como se puede usar el objeto Servo
// (freq, canal, resolucion, minPulso_us, maxPulso_us, pin)
//Servo myServo(50, 0, 14, 500, 2400, 18);  // resolución de 10 o 14, no funciona con otras
