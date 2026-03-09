#include "myMtrH.hpp"
L298Ngen::L298Ngen(uint8_t a, uint8_t b, int c):
    myPWM(20000, 0, 10, c){
    this->pinA = a;
    this->pinB = b;
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
}
void L298Ngen::stop(){
    myPWM.stopPWM();
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, LOW);
}
void L298Ngen::moveR(){
    myPWM.startPWM();
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, LOW);
}
void L298Ngen::moveL(){
    myPWM.startPWM();
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, HIGH);
}
void L298Ngen::PWMmas(int x){
    int aux = myPWM.getPWM();
    myPWM.setPWM(aux + x);
}
void L298Ngen::PWMmenos(int x){
    int aux = myPWM.getPWM();
    myPWM.setPWM(aux - x);
}
int L298Ngen::getPWM(){
    return myPWM.getPWM();
}
