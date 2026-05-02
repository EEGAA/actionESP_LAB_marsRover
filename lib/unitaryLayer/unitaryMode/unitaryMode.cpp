#include "unitaryMode.hpp"


void UNITYgen::update(){
    setTecla();
//     switch(teclaChar){
//
//     }
    showTeclas();
    if(teclaChar == 'R')//este if es bien importante pq gracias a el regresamos a modo ros2
         ESP.restart();
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

void UNITYgen::showTeclas(){
    Serial.print(teclaChar);
    Serial.println(" "+String(teclaInt));
}
