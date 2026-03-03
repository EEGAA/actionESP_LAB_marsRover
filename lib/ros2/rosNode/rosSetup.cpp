//Todo lo que se use aqui normalmente estaria en el setup del main.cpp
//pero aqui es parte del control modular y estos metodos se aplican en createEntities() de rosNode.cpp
#include "rosNode.hpp"

void RosNode::initSerial(){
    Serial.begin(921600);
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
    if (rclc_executor_init(&executor, &support.context, 2, &allocator) != RCL_RET_OK)
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
        &subServo,
        &servoAng_msg,
        &RosNode::subServoAng_callback,
        ON_NEW_DATA) != RCL_RET_OK)
        return false;
    return true;
}
