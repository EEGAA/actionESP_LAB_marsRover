#include "configNEMA.hpp"
INFO_NEMA::INFO_NEMA(){
    pasos = 1;
    direccion = true;
}
void INFO_NEMA::setPasos(int x){
    this->pasos = x;
}
int INFO_NEMA::getPasos(){
    return pasos;
}
void INFO_NEMA::setDireccion(bool x){
    this->direccion = x;
}
bool INFO_NEMA::getDireccion(){
    return direccion;
}
void INFO_NEMA::setRetraso(int x){
    this->retraso = x;
}
int INFO_NEMA::getRetraso(){
    return retraso;
}

void INFO_NEMA::pasosINTER(bool bnd, int x){
    if(bnd)
        pasos += x;
    else{
        if((pasos - x) < 1)
            pasos = x;
        else
            pasos -= x;
    }
}
void INFO_NEMA::tiempoINTER(bool bnd, int x){
    if(bnd)
        retraso += x;
    else{
       if((retraso - x) < 1)
            retraso = x;
        else
            retraso -= x; 
    }
}


//lo que va de aqui pa abajo tiene que ver con GENERAL_nemaDTA
GENERAL_nemaDTA::GENERAL_nemaDTA(){
    nemaAux = 0;//por default inicia en nema EX, 
    bndMode = true; //true = pasos y false = timer
    intervalo = 50;//por defecto comienza modificando de 50 en 50
}
void GENERAL_nemaDTA::interMENOS(){
    if(intervalo != 1)
        intervalo--;
}
void GENERAL_nemaDTA::interMAS(){
    intervalo++;
}
