//Todo lo que se use aqui normalmente estaria en el setup del main.cpp
//pero aqui es parte del control modular y estos metodos se aplican en createEntities() de rosNode.cpp
#include "rosNode.hpp"
RosNode::RosNode(): timeConnected(2000), sleepTime(250){}

void RosNode::initSerial(){
    if(!Serial){
        timeConnected.initTempo();
        Serial.begin(SerialSpeed);
        while(!Serial && !timeConnected.checkTempo()){}
    }
    if(!Serial)//es improbable entrar a este if, y si pasa, se reinicia la esp
        ESP.restart();

    sleepTime.initTempo();
    while(!sleepTime.checkTempo()){}//bloqueante solo por 250 ms, espera a estabilizar Serial

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

    return true;
}

bool RosNode::initNode(){
    if (rclc_node_init_default(&node, "esp32_node", "labActESP", &support) != RCL_RET_OK)
        return false;

    return true;
}

bool RosNode::initExecutor(){
    if (rclc_executor_init(&executor, &support.context, 20, &allocator) != RCL_RET_OK)
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
    if (rclc_executor_add_subscription(
        &executor,
        &subH_moveMTR,
        &subH_moveMTR_msg,
        &RosNode::subH_moveMTR_callback,
        ON_NEW_DATA) != RCL_RET_OK)
        return false;
    if (rclc_executor_add_subscription(
        &executor,
        &subH_setPWM,
        &subH_setPWM_msg,
        &RosNode::subH_setPWM_callback,
        ON_NEW_DATA) != RCL_RET_OK)
        return false;
    if (rclc_executor_add_subscription(
        &executor,
        &subNeo_basic,
        &subNeo_basic_msg,
        &RosNode::subNeo_basic_callback,
        ON_NEW_DATA) != RCL_RET_OK)
        return false;
    if (rclc_executor_add_subscription(
        &executor,
        &subNeo_brillo,
        &subNeo_brillo_msg,
        &RosNode::subNeo_brillo_callback,
        ON_NEW_DATA) != RCL_RET_OK)
        return false;
    if (rclc_executor_add_subscription(
        &executor,
        &subSTOP,
        &subSTOP_msg,
        &RosNode::subSTOP_callback,
        ON_NEW_DATA) != RCL_RET_OK)
        return false;
    // NEMA
    if (rclc_executor_add_subscription(
        &executor,
        &subNemaEX_move,
        &subNemaEX_move_msg,
        &RosNode::subNemaEX_move_callback,
        ON_NEW_DATA) != RCL_RET_OK)
        return false;
   if (rclc_executor_add_subscription(
        &executor,
        &subNemaES_move,
        &subNemaES_move_msg,
        &RosNode::subNemaES_move_callback,
        ON_NEW_DATA) != RCL_RET_OK)
        return false;
   if (rclc_executor_add_subscription(
        &executor,
        &subNemaBA_move,
        &subNemaBA_move_msg,
        &RosNode::subNemaBA_move_callback,
        ON_NEW_DATA) != RCL_RET_OK)
        return false;
   if (rclc_executor_add_subscription(
        &executor,
        &subNemaAX_move,
        &subNemaAX_move_msg,
        &RosNode::subNemaAX_move_callback,
        ON_NEW_DATA) != RCL_RET_OK)
        return false;
   if (rclc_executor_add_subscription(
        &executor,
        &subNemaStop,
        &subNemaStop_msg,
        &RosNode::subNemaStop_callback,
        ON_NEW_DATA) != RCL_RET_OK)
        return false;
   //subUnitaryMode
   if (rclc_executor_add_subscription(
        &executor,
        &subUnitaryMode,
        &subUnitaryMode_msg,
        &RosNode::subUnitaryMode_callback,
        ON_NEW_DATA) != RCL_RET_OK)
        return false;
    if (rclc_executor_add_subscription(
        &executor,
        &subExcavando,
        &subExcavando_msg,
        &RosNode::subExcavando_callback,
        ON_NEW_DATA) != RCL_RET_OK)
        return false;
    return true;
}
