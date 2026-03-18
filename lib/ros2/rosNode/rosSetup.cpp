//Todo lo que se use aqui normalmente estaria en el setup del main.cpp
//pero aqui es parte del control modular y estos metodos se aplican en createEntities() de rosNode.cpp
#include "rosNode.hpp"
RosNode::RosNode(): timeConnected(2000), sleepReinit(1000){}
void RosNode::initSerial(){
    if(Serial.available() > 0){
        sleepReinit.initTempo();
        while(!sleepReinit.checkTempo()){}
        ESP.restart();
    }
    Serial.begin(115200);
    timeConnected.initTempo();
    while(!Serial && !timeConnected.checkTempo()){}
    if(!Serial)//es improbable entrar a este if, y si pasa, se reinicia la esp
        ESP.restart();

    sleepReinit.initTempo();
    while(!sleepReinit.checkTempo()){}//bloqueante solo por 1000 ms, espera a estabilizar Serial

    initTransport();
}

void RosNode::initTransport(){
    while(Serial.available())//recorre basura de la conexion anterior,
        Serial.read(); //lo lee para sacarlo del buffer
    set_microros_serial_transports(Serial);//con esto micro ros sabe que debe usar Serial
}

bool RosNode::initSupport(){
    if (rclc_support_init(&support, 0, NULL, &allocator) != RCL_RET_OK)
        return false;
    // if (rclc_support_init_with_options(&support, 0, NULL, &init_options, &allocator) != RCL_RET_OK)
    //     return false;
    return true;
}

bool RosNode::initNode(){
    if (rclc_node_init_default(&node, "esp32_node", "actionESP", &support) != RCL_RET_OK)
        return false;
    return true;
}

bool RosNode::initExecutor(){
    if (rclc_executor_init(&executor, &support.context, 8, &allocator) != RCL_RET_OK)
        return false;

    if (rclc_executor_add_subscription(
        &executor,
        &subLED,
        &led_msg,
        &RosNode::subLED_callback,
        ON_NEW_DATA) != RCL_RET_OK)
        return false;
    if (rclc_executor_add_subscription(
        &executor,
        &subServoDisp,
        &svDispAng_msg,
        &RosNode::subServoDispAng_callback,
        ON_NEW_DATA) != RCL_RET_OK)
        return false;
    if (rclc_executor_add_subscription(
        &executor,
        &subServoCube,
        &svCubeAng_msg,
        &RosNode::subServoCubeAng_callback,
        ON_NEW_DATA) != RCL_RET_OK)
        return false;
    //RoboClaw
    if (rclc_executor_add_subscription(
        &executor,
        &subRCStop,
        &rcStop_msg,
        &RosNode::subRCstop_callback,
        ON_NEW_DATA) != RCL_RET_OK)
        return false;
    if (rclc_executor_add_subscription(
        &executor,
        &subRCvelMTR1,
        &velMTR1_msg,
        &RosNode::subSetVelRCmtr1_callback,
        ON_NEW_DATA) != RCL_RET_OK)
        return false;
    if (rclc_executor_add_subscription(
        &executor,
        &subRCvelMTR2,
        &velMTR2_msg,
        &RosNode::subSetVelRCmtr2_callback,
        ON_NEW_DATA) != RCL_RET_OK)
        return false;
    if (rclc_executor_add_subscription(
        &executor,
        &subRCmoveMTR1,
        &moveRCmtr1_msg,
        &RosNode::subRCmoveMTR1_callback,
        ON_NEW_DATA) != RCL_RET_OK)
        return false;
    if (rclc_executor_add_subscription(
        &executor,
        &subRCmoveMTR2,
        &moveRCmtr2_msg,
        &RosNode::subRCmoveMTR2_callback,
        ON_NEW_DATA) != RCL_RET_OK)
        return false;
    return true;
}
