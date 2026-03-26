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
    //xQueueSendFromISR(commandQueue, &cmd, nullptr);
    // Usa xQueueSend si callbacks NO son ISR reales:
    xQueueSend(commandQueue, &cmd, 0);
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
//RoboClaw
void RosNode::subRCstop_callback(const void * msgin){
    const std_msgs__msg__UInt8 * msg = (const std_msgs__msg__UInt8 *)msgin;
    RosCommand cmd;
    cmd.type      = CmdType::RC_STOP;
    cmd.uint8Val   = msg->data;
    xQueueSend(commandQueue, &cmd, 0);
}

void RosNode::subSetVelRCmtr1_callback(const void * msgin){
    const std_msgs__msg__UInt8 * msg = (const std_msgs__msg__UInt8 *)msgin;
    RosCommand cmd;
    cmd.type      = CmdType::RC_VELMTR1;
    cmd.uint8Val   = msg->data;
    xQueueSend(commandQueue, &cmd, 0);
}
void RosNode::subSetVelRCmtr2_callback(const void * msgin){
    const std_msgs__msg__UInt8 * msg = (const std_msgs__msg__UInt8 *)msgin;
    RosCommand cmd;
    cmd.type      = CmdType::RC_VELMTR2;
    cmd.uint8Val   = msg->data;
    xQueueSend(commandQueue, &cmd, 0);
}

void RosNode::subRCmoveMTR1_callback(const void * msgin){
    const std_msgs__msg__Bool * msg = (const std_msgs__msg__Bool *)msgin;
    RosCommand cmd;
    cmd.type      = CmdType::RC_MoveMTR1;
    cmd.boolVal   = msg->data;
    xQueueSend(commandQueue, &cmd, 0);
}
void RosNode::subRCmoveMTR2_callback(const void * msgin){
    const std_msgs__msg__Bool * msg = (const std_msgs__msg__Bool *)msgin;
    RosCommand cmd;
    cmd.type      = CmdType::RC_MoveMTR2;
    cmd.boolVal   = msg->data;
    xQueueSend(commandQueue, &cmd, 0);
}
//puente H
void RosNode::subH_moveMTR_callback(const void * msgin){
    const std_msgs__msg__UInt8 * msg = (const std_msgs__msg__UInt8 *)msgin;
    RosCommand cmd;
    cmd.type      = CmdType::H_mtrMOVE;
    cmd.uint8Val   = msg->data;
    xQueueSend(commandQueue, &cmd, 0);
}

void RosNode::subH_setPWM_callback(const void * msgin){
    const std_msgs__msg__Int16 * msg = (const std_msgs__msg__Int16 *)msgin;
    RosCommand cmd;
    cmd.type      = CmdType::H_mtrSetPWM;
    cmd.int16Val   = msg->data;
    xQueueSend(commandQueue, &cmd, 0);
}

//NEO Led
void RosNode::subNeo_basic_callback(const void * msgin){
    const std_msgs__msg__UInt8 * msg = (const std_msgs__msg__UInt8 *)msgin;
    RosCommand cmd;
    cmd.type      = CmdType::NEO_LED_basic;
    cmd.uint8Val   = msg->data;
    xQueueSend(commandQueue, &cmd, 0);
}

void RosNode::subNeo_brillo_callback(const void * msgin){
    const std_msgs__msg__UInt8 * msg = (const std_msgs__msg__UInt8 *)msgin;
    RosCommand cmd;
    cmd.type      = CmdType::NEO_LED_brillo;
    cmd.uint8Val   = msg->data;
    xQueueSend(commandQueue, &cmd, 0);
}
