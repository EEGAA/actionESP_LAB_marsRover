#pragma once
#include <Arduino.h>
#include "menu/menu.hpp"
//dirversLayer, ahi es donde se reunen todas las objetos de los drivers
#include "../../halMicro/espLayer/espLayer.hpp"
class UNITYgen{
private:
    int teclaInt;
    char teclaChar;
    bool omiteDefault;
    MENUgen myMenu;

    bool bndRBCLW;//bandera que indica si se decide sobre 1 o 2 mtr de roboclaw
    //bndRBCLW = true = gusano
    //bndRBCLW = false = broca
    uint8_t interVclw;
    //interVclw es el intervalo en el cambio de velocidad, 
    //para este caso sera de 5 en 5
public:
    UNITYgen();
    void setTecla();
    char getTeclaC();
    int getTeclaI();

    void update(); //aqui se hace todo alv

    void showTeclas();

    void genSwitch();

    bool loopServo(bool);
};
