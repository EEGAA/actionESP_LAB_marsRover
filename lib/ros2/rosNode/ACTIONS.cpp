#include "rosNode.hpp"

void RosNode::publishCounter(){
    counter_msg.data++;
    rcl_publish(&pubCounter, &counter_msg, NULL);
}

void RosNode::subLED_callback(const void * msgin){
    const std_msgs__msg__Bool * msg = (const std_msgs__msg__Bool *)msgin;
    //aqui el led debe tomar el estado de msg
    //pero no se si implementarlo aqui o con /hal
    myLed.setState(msg->data);
}

void RosNode::subServoAng_callback(const void * msgin){
    const std_msgs__msg__UInt8 * msg = (const std_msgs__msg__UInt8 *)msgin;
    servoDisp.moveAng(msg->data);
}
