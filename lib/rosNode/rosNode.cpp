#include <rosNode.hpp>

void RosNode::initSerial(){
    Serial.begin(921600);
    set_microros_serial_transports(Serial);
}

bool RosNode::createEntities(){
    allocator = rcl_get_default_allocator();
    //support
    if(!initSupport()) return false;
    //node
    if(!initNode()) return false;
    //publishers
    if(!initPublishers()) return false;
    //subscribers
    if(!initSubscribers()) return false;
    //executor
    if(!initExecutor()) return false;

    counter_msg.data = 0;

    return true;

}

void RosNode::destroyEntities(){
    rclc_executor_fini(&executor);


    finiPublishers();
    finiSubscribers();


    rcl_node_fini(&node);
    rclc_support_fini(&support);
}

void RosNode::spinROS(){
    rclc_executor_spin_some(&executor, RCL_MS_TO_NS(10));
}

void RosNode::publishCounter(){
    counter_msg.data++;
    rcl_publish(&publisher, &counter_msg, NULL);
}

void RosNode::subscription_callback(const void * msgin){
    const std_msgs__msg__Bool * msg = (const std_msgs__msg__Bool *)msgin;
    //aqui el led debe tomar el estado de msg
    //pero no se si implementarlo aqui o con /hal
    const int pinLED = 14;
    pinMode(pinLED, OUTPUT);
    digitalWrite(pinLED, msg->data);
}
