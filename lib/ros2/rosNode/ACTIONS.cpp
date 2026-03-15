#include "rosNode.hpp"
#include "../../halMicro/halRTOS/sharedData/sharedData.hpp"
void RosNode::publishCounter(){
    counter_msg.data++;
    rcl_publish(&pubCounter, &counter_msg, NULL);
}

void RosNode::subLED_callback(const void * msgin){
    const std_msgs__msg__Bool * msg = (const std_msgs__msg__Bool *)msgin;
    //myLed.setState(msg->data);
    RosCommand cmd;
    cmd.type     = CmdType::LED_SET;
    cmd.boolVal  = msg->data;
    xQueueSendFromISR(commandQueue, &cmd, nullptr);
    // Usa xQueueSend si callbacks NO son ISR reales:
    // xQueueSend(commandQueue, &cmd, 0);
}

void RosNode::subServoDispAng_callback(const void * msgin){
    const std_msgs__msg__UInt8 * msg = (const std_msgs__msg__UInt8 *)msgin;
    //servoDisp.moveAng(msg->data);
    RosCommand cmd;
    cmd.type      = CmdType::SERVOdisp_MOVE;
    cmd.uint8Val  = msg->data;
    xQueueSend(commandQueue, &cmd, 0);
}

void RosNode::subServoCubeAng_callback(const void * msgin){
    const std_msgs__msg__UInt8 * msg = (const std_msgs__msg__UInt8 *)msgin;
    //servoDisp.moveAng(msg->data);
    RosCommand cmd;
    cmd.type      = CmdType::SERVOcube_MOVE;
    cmd.uint8Val  = msg->data;
    xQueueSend(commandQueue, &cmd, 0);
}
