#pragma once
//#include <micro_ros_platformio.h>
#include "../rosNode/rosNode.hpp"
#include "../../halMicro/halRTOS/sharedData/sharedData.hpp"
//el siguiente include sirve para manejar lo relacionado al modo Serial
#include "../../unitaryLayer/unitaryMode/unitaryMode.hpp"
class RosConnection{
private:
    enum State{
        WAITING_AGENT,//naranja
        AGENT_AVAILABLE,//rosa
        AGENT_CONNECTED,//verdeLima solo 1.5 s
        AGENT_DISCONNECTED,//rojo
        UNITARY_MODE,//azulCielo solo 1.5 s
    };
    State state = WAITING_AGENT;
    RosNode ros_node;
    Tempo timePING, timeCheckCon, lifeLED;
    bool bnd; // true == conectado 1er vez, false == conexion establecida

    UNITYgen appUM;
    //appUM tiene que ver con el manejo de los motores cuando se usa el modo Serial
public:
    RosConnection() : timePING(500, true), timeCheckCon(50, true), lifeLED(1500), bnd(true){}
    //timePING son los 500 ms de espera para reconectar, usados aqui WAITING_AGENT
    //intervalo entre intentos de reconeccion
    //da tiempo a destruir y construir las entidades de micro ros

    //timeCheckCon se usa en AGENT_CONNECTED y es el intervalo entre consultas de
    //desconeccion
    //para no saturar con tantas consultas improbables,

    // reintenta ping cada 500ms, verifica conexión activa cada 50ms.

    void init();
    void update();
};
