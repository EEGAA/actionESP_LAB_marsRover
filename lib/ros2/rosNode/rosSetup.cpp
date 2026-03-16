//Todo lo que se use aqui normalmente estaria en el setup del main.cpp
//pero aqui es parte del control modular y estos metodos se aplican en createEntities() de rosNode.cpp
#include "rosNode.hpp"
Tempo timeConnected(500);//es para darle 500ms en caso de no poder inicializar Serial antes
void RosNode::initSerial(){
    Serial.begin(921600);
    timeConnected.initTempo();
    while(!Serial && !timeConnected.checkTempo()){}
    if(!Serial)//es improbable entrar a este if, y si pasa, se reinicia la esp
        ESP.restart();
    myESPinfo();//este mensaje solo se muestra en el puerto serial
    set_microros_serial_transports(Serial);
}

bool RosNode::initSupport(){
    if (rclc_support_init(&support, 0, NULL, &allocator) != RCL_RET_OK)
        return false;
    return true;
}

bool RosNode::initNode(){
    if (rclc_node_init_default(&node, "esp32_node", "actionESP", &support) != RCL_RET_OK)
        return false;
    return true;
}

bool RosNode::initExecutor(){
    if (rclc_executor_init(&executor, &support.context, 6, &allocator) != RCL_RET_OK)
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
    return true;
}
