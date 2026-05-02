#include "unitaryMode.hpp"


void UNITYgen::update(){
    setTecla();
//     switch(teclaChar){
//
//     }
    Serial.println(teclaChar);
}


void UNITYgen::setTecla(){
    this->teclaInt = Serial.read();
    this->teclaChar = (char)teclaInt;
}
char UNITYgen::getTeclaC(){
    return teclaChar;
}
int UNITYgen::getTeclaI(){
    return teclaInt;
}
