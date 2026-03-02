#include <myPWM.hpp>
PWMgen::PWMgen(int freq_, int chanel_, int resolution_, int pin_){
    this->freq = freq_;
    this->chanel = chanel_;
    this->resolution = resolution_;
    this->pin = pin_;
    this->pwm = 0;
    pinMode(pin, OUTPUT);
    ledcSetup(chanel, freq, resolution);
    ledcAttachPin(pin, chanel);
    stopPWM();
    ADCmax = (1 << resolution) - 1;
}
int PWMgen::getPWM(){
    return pwm;
}
void PWMgen::setPWM(int x){
    if (x >= 0 && x <= ADCmax){
        this->pwm = x;
        startPWM();
    }else return;
}
void PWMgen::stopPWM(){
    ledcWrite(chanel, 0);
}
void PWMgen::startPWM(){
    ledcWrite(chanel, pwm);
}
void PWMgen::getADCmax(){
    return ADCmax;
}
