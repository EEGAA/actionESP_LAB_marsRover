#include "unitaryMode.hpp"


void UNITYgen::update(){
    setTecla();
    showTeclas();
    if(teclaChar == 'R')//este if es bien importante pq gracias a el regresamos a modo ros2
         ESP.restart();
    genSwitch();
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

void UNITYgen::genSwitch(){
    if(teclaInt == 9)
        myMenu.menuOption();
    switch(teclaChar){
        
        default:
            Serial.println("Tecla NO reconocida :( ...");
            // Serial.println("Intenta con alguna de las siguientes opciones");
            //aki se supone que debo de imprimir un menu relatando lo que hace cada tecla pero xd pa luego sera otro dia
            break;
    }
}
