#include "rosConnection.hpp"
void RosConnection::init(){
    neoLED.azul();
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

            if(timeCheckCon.checkTempo()){//verifica cada 1.5 segundos si sigue conectado
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
                if(status.type == StatusType::SIGNAL_LIMIT_EX){
                    ros_node.pubLimitEX_callback();
                }
                if(status.type == StatusType::SIGNAL_LIMIT_ES){
                    ros_node.pubLimitES_callback();
                }
            }
            //cambia a modo unitary mode, Serial mode, solo cuando es true bndSignal_UM
            if(bndSignal_UM.getSignalBND())
                state = UNITARY_MODE;
            break;

        case AGENT_DISCONNECTED: neoLED.rojo();
            ros_node.destroyEntities();
            vTaskDelay(pdMS_TO_TICKS(500));
            neoLED.azul();
            //una vez sin entidades se busca intentar recuperar Serial
            ros_node.initSerial();//para poder detener el nodo con ctrl+c,
            //y al reclamarlo recuperar Serial sin tener que reiniciar la esp
            state = WAITING_AGENT;
            break;
        case UNITARY_MODE:
            if(bndSignal_UM.getSignalBND()){
                neoLED.grisMedio();
                ros_node.destroyEntities();
                vTaskDelay(pdMS_TO_TICKS(500));
                bndSignal_UM.setSignalBND(false);
                neoLED.azulCielo();
                if(!Serial){
                    Serial.begin(SerialSpeed);
                    vTaskDelay(pdMS_TO_TICKS(250));
                }
                lifeLED.initTempo();
                bnd = true;
            }
            if(bnd)
                if(lifeLED.checkTempo()){
                    neoLED.LEDoff();
                    bnd = false;
                }

            //esto es cada respuesta al teclado
            if(Serial.available() > 0)
                appUM.update();


            break;
    }
}
