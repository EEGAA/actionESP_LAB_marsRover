#pragma once
#include <Arduino.h>
//con millis puedo contar 70 dias, con micros 70 min
class Tempo{
private:
    unsigned long intervalo_;//es el tiempo de espera
    unsigned long tempoBase_;//la variable que guarda la referencia
    //este resta sera la referencia
    //(ahora - tempoBase_) >= intervalo_
    bool autoReinicio_;//por si se necesita hacer repeticiones del timer o no
    bool usarMicros_;//para poder camiar a micro si es necesario
    //usarMicro ? micros() : millis()
public:
    // Constructor: intervalo en milisegundos, autoReinicio = true para tareas periódicas
    Tempo(unsigned long intervalo, bool autoReinicio = false);

    //inicia o reinicia, hacen lo mismo, (establece el tiempo base)
    void initTempo();
    void resetTempo();//alias de initTempo()

    bool checkTimer();//devuelve true si el intervalo ha transcurrido

    void setInter(unsigned long nuevoIntervalo);//util para cambiar el tiempo de espera del objeto Tempo

    unsigned long tempoDiff();//tempoDiff regresa el tiempo que falta para expirar

    void useMicro(bool usar);//para decidir si usamos millis o micros

    unsigned long getCurrentTime();

};
