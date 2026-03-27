#include "rosConnection.hpp"
void RosConnection::init(){
    ros_node.initSerial();
    myESPinfo();//este mensaje solo se muestra en el puerto serial
}

void RosConnection::update(){
    switch(state){
        case WAITING_AGENT: neoLED.naranja();
            if(timePING.checkTempo())//verifica cada 1/2 segundo si puede conectarse
                if(rmw_uros_ping_agent(100, 1) == RMW_RET_OK){
                    state = AGENT_AVAILABLE;
                }
            break;

        case AGENT_AVAILABLE: neoLED.rosa();
            if(ros_node.createEntities()){
                state = AGENT_CONNECTED;
                bnd = true;
                lifeLED.initTempo();
                neoLED.verdeLima();
            }else{
                state = AGENT_DISCONNECTED;
            }
            break;

        case AGENT_CONNECTED:
            if(bnd)
                if(lifeLED.checkTempo()){
                    neoLED.LEDoff();
                    bnd = false;
                }

            if(timeCheckCon.checkTempo()){//verifica cada 2 segundos si sigue conectado
                if(rmw_uros_ping_agent(100, 1) != RMW_RET_OK){
                    state = AGENT_DISCONNECTED;
                    break;
                }
            }

            ros_node.spinROS();

            // Consumir statusQueue — drivers nos piden publicar algo
            DriverStatus status;
            while(xQueueReceive(statusQueue, &status, 0) == pdTRUE){
                if(status.type == StatusType::COUNTER_TICK){
                    ros_node.publishCounter();
                }
            }
            break;

        case AGENT_DISCONNECTED: neoLED.rojo();
            ros_node.destroyEntities();
            neoLED.azul();
            //una vez sin entidades se busca intentar recuperar Serial
            ros_node.initSerial();//para poder detener el nodo con ctrl+c,
            //y al reclamarlo recuperar Serial sin tener que reiniciar la esp
            state = WAITING_AGENT;
            break;
    }
}
