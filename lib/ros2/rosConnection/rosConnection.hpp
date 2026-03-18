#pragma once
//#include <micro_ros_platformio.h>
#include "../rosNode/rosNode.hpp"
#include "../../halMicro/halRTOS/sharedData/sharedData.hpp"
class RosConnection{
private:
    enum State{
        WAITING_AGENT,
        AGENT_AVAILABLE,
        AGENT_CONNECTED,
        AGENT_DISCONNECTED
    };
    State state = WAITING_AGENT;
    RosNode ros_node;
    Tempo timeInter, timePing;
public:
    RosConnection() : timeInter(500, true), timePing(2000, true){}
    //timeInter son los 500 ms de espera para reconectar, usados aqui WAITING_AGENT
    //intervalo entre intentos de reconeccion
    //da tiempo a destruir y construir las entidades de micro ros

    //timePing se usa en AGENT_CONNECTED y es el intervalo entre consultas de
    //desconeccion
    //para no saturar con tantas consultas improbables,

    void init();
    void update();
};
