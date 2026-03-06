#include "myMtrH.hpp"
L298N::L298N(uint8_t a, uint8_t b, int c):
    myPWM(20000, 0, 10, c){
    this->pinA = a;
    this->pinB = b;
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
}
void L298N::stop(){
    myPWM.stopPWM();
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, LOW);
}
void L298N::moveR(){
    myPWM.startPWM();
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, LOW);
}
void L298N::moveL(){
    myPWM.startPWM();
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, HIGH);
}
void L298N::PWMmas(int x){
    int aux = myPWM.getPWM();
    myPWM.setPWM(aux + x);
}
void L298N::PWMmenos(int x){
    int aux = myPWM.getPWM();
    myPWM.setPWM(aux - x);
}
int L298N::getPWM(){
    return myPWM.getPWM();
}
