#include "myMtrH.hpp"
L298Ngen::L298Ngen(uint8_t a, uint8_t b, int c):
    thisPWM(20000, 0, 10, c){
    this->pinA = a;
    this->pinB = b;
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
}
void L298Ngen::stop(){
    thisPWM.stopPWM();
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, LOW);
}
void L298Ngen::moveR(){
    thisPWM.startPWM();
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, LOW);
}
void L298Ngen::moveL(){
    thisPWM.startPWM();
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, HIGH);
}
void L298Ngen::PWMmas(int x){
    int aux = thisPWM.getPWM();
    thisPWM.setPWM(aux + x);
}
void L298Ngen::PWMmenos(int x){
    int aux = thisPWM.getPWM();
    thisPWM.setPWM(aux - x);
}
int L298Ngen::getPWM(){
    return thisPWM.getPWM();
}
