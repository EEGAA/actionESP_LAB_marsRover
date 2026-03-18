#include "rosConnection.hpp"
void RosConnection::init(){
    ros_node.initSerial();
    myESPinfo();//este mensaje solo se muestra en el puerto serial
}

void RosConnection::update(){
    switch(state){
        case WAITING_AGENT:
            if(timeInter.checkTempo())
                if(rmw_uros_ping_agent(100, 1) == RMW_RET_OK){
                    state = AGENT_AVAILABLE;
                }
            break;

        case AGENT_AVAILABLE:
            if(ros_node.createEntities()){
                state = AGENT_CONNECTED;
            }else{
                // ros_node.destroyEntities();//esta linea
                // //asegura iniciar AGENT_AVAILABLE sin entidades creadas
                // delay(500); // es bloqueante pero aqui vale la pena
                // //da tiempo a que todo se destruya correctamente
                //
                // //una vez sin entidades se busca intentar recuperar Serial
                // ros_node.initSerial();//para poder detener el nodo con ctrl+c,
                // //y al reclamarlo recuperar Serial sin tener que reiniciar la esp
                state = WAITING_AGENT;
            }
            break;

        case AGENT_CONNECTED:
            if(timePing.checkTempo()){
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

        case AGENT_DISCONNECTED:
            ros_node.destroyEntities();
            delay(500); // es bloqueante pero aqui vale la pena
            //da tiempo a que todo se destruya correctamente

            //una vez sin entidades se busca intentar recuperar Serial
            ros_node.initSerial();//para poder detener el nodo con ctrl+c,
            //y al reclamarlo recuperar Serial sin tener que reiniciar la esp
            state = WAITING_AGENT;
            break;
    }
}
