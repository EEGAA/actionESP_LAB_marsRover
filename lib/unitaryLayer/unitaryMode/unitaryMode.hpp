#pragma once
#include <Arduino.h>
class UNITYgen{
private:
    int teclaInt;
    char teclaChar;
public:
    void setTecla();
    char getTeclaC();
    int getTeclaI();

    void update(); //aqui se hace todo alv
};
