#include "myServo.hpp"

SERVOgen::SERVOgen(int freq_, int chanel_, int resolution_, int minPulso_, int maxPulso_, int pin_):
    thisPWM(freq_, chanel_, resolution_, pin_){
    this->minPulso = minPulso_;
    this->maxPulso = maxPulso_;
    this->periodo  = (int)(1e6 / freq_);  // periodo en microsegundos
    ADCmax = thisPWM.getADCmax();
}

// Mueve el servo a un angulo entre 0 y 180
void SERVOgen::moveAng(int angulo){
    if (angulo < 0 || angulo > 180) return;
    // Interpola el pulso en us segun el angulo
    float pulso = minPulso + (maxPulso - minPulso) * (angulo / 180.0f);
    // Convierte el pulso a duty cycle en counts ADC
    sendPWM(pulso);
}

void SERVOgen::sendPWM(float pulso_){
    int pwm_ = (int)((pulso_ / periodo) * ADCmax + 0.5f);
    thisPWM.setPWM(pwm_);
}

int SERVOgen::getADCmax(){
    return ADCmax;
}

void SERVOgen::stopPWM(){
    thisPWM.stopPWM();
}
