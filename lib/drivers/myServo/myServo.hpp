#pragma once
#include "../myPWM/myPWM.hpp"

class SERVOgen {
private:
    PWMgen thisPWM;
    int minPulso, maxPulso, periodo;
    int ADCmax;

    //los siguientes atributos sirven para poder manipular la velocidad de giro del servo
    //objetivo es lograr cambios lentos con codigo no  bloqueante
    float currentAngle;   // estado interno real
    float targetAngle;    // objetivo
    float speed;          // grados por segundo
    unsigned long lastUpdate;

public:
    SERVOgen(int freq_, int chanel_, int resolution_, int minPulso_, int maxPulso_, int pin_);
    void moveAng(float angulo_);   // 0 a 180 grados
    void sendPWM(float pulso_);
    void stopPWM();
    int getADCmax();

    // void setCurrentAngle();
    void setTargetAngle(float angulo_, float speed_);
    // void setSpeed;

    void update(bool);
    //update(false) -> el servo se mueve siempre a la misma velocidad
    //update(true) -> empieza rapido, termina suave, lo mas rapido que empezara
    //equivale a la velocidad constante de update(false)

    float getCurrentAngle();
    // float getTargetAngle();
    // float getSpeed;
    bool isAtTarget();

};
//Este es un ejemplo en como se puede usar el objeto Servo
// (freq, canal, resolucion, minPulso_us, maxPulso_us, pin)
//Servo myServo(50, 0, 14, 500, 2400, 18);  // resolución de 10 o 14, recomendadas, con otras el servo tiene problemas






/*
 Para controlar la velocidad del servo me base en esta ecuacion:

 NuevoAngulo = AnguloActual +- w * dt

 donde +- es mas-menos
 w = omega, o sea velocidad angular, grados/segundo
 dt = diferencial de tiempo, es decir, tiempo entre actualizaciones

 */
