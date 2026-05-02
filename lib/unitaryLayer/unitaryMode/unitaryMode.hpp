#pragma once
#include <Arduino.h>
#include "menu/menu.hpp"
class UNITYgen{
private:
    int teclaInt;
    char teclaChar;
    MENUgen myMenu;
public:
    void setTecla();
    char getTeclaC();
    int getTeclaI();

    void update(); //aqui se hace todo alv

    void showTeclas();

    void genSwitch();
};
