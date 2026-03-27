#pragma once
//#include <micro_ros_platformio.h>
#include "../rosNode/rosNode.hpp"
#include "../../halMicro/halRTOS/sharedData/sharedData.hpp"
class RosConnection{
private:
    enum State{
        WAITING_AGENT,//naranja
        AGENT_AVAILABLE,//rosa
        AGENT_CONNECTED,//verdeLima
        AGENT_DISCONNECTED//rojo
    };
    State state = WAITING_AGENT;
    RosNode ros_node;
    Tempo timePING, timeCheckCon, lifeLED;
    bool bnd; // true == conectado 1er vez, false == conexion establecida
public:
    RosConnection() : timePING(500, true), timeCheckCon(1000, true), lifeLED(1500), bnd(true){}
    //timePING son los 500 ms de espera para reconectar, usados aqui WAITING_AGENT
    //intervalo entre intentos de reconeccion
    //da tiempo a destruir y construir las entidades de micro ros

    //timeCheckCon se usa en AGENT_CONNECTED y es el intervalo entre consultas de
    //desconeccion
    //para no saturar con tantas consultas improbables,

    // reintenta ping cada 500ms, verifica conexión activa cada 1s.

    void init();
    void update();
};
