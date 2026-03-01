//Todo lo que se use aqui normalmente estaria en el setup del main.cpp
//pero aqui es parte del control modular y estos metodos se aplican en createEntities() de rosNode.cpp
#include <rosNode.hpp>

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
    if (rclc_executor_init(&executor, &support.context, 1, &allocator) != RCL_RET_OK)
        return false;

    if (rclc_executor_add_subscription(
        &executor,
        &subscriber,
        &led_msg,
        &RosNode::subscription_callback,
        ON_NEW_DATA) != RCL_RET_OK)
        return false;
    return true;
}
