#pragma once
#include <Arduino.h>
#include "menu/menu.hpp"
//dirversLayer, ahi es donde se reunen todas las objetos de los drivers
#include "../../halMicro/espLayer/espLayer.hpp"
//la siguiente biblioteca contiene un calse, la utilidad de esta es poder administar los
//atributos actuales del nema que se dese controlar, el objetivo es tener una clase
//de la cual pueda sacar 4 objetos, 1 por cada nema
#include "../configNEMA/configNEMA.hpp"
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

    //los nema pueden modificar sus caracteristicas en tiempo de ejecucion, 
    //los siguientes metodos sirven para poder modificar sus atributos 
    INFO_NEMA infoEX, infoES, infoBA, infoAX;
    //excavadora, espectrometro, bandeja, auxiliar
    //    0,            1,          2,       3
    GENERAL_nemaDTA myNEMAdta;
public:
    UNITYgen();
    void setTecla();
    char getTeclaC();
    int getTeclaI();

    void update(); //aqui se hace todo alv

    void showTeclas();

    void genSwitch();

    bool loopServo(bool);//esta funcion segmenta en un ciclo a parte lo referente a mover los servos

    void controlNEMA();//esta funcion lo unico que hace es determinar en funcion de la tecla n
    //cual es el nema actual que se desea manipular, es decir le da un estado a nemaAux, dicho estado
    //solo puede ser uno de cuatro opciones 0,1,2,3
};
