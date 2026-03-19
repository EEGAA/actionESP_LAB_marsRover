#include "rosNode.hpp"
bool RosNode::initSubscribers(){
    if (rclc_subscription_init_default(
        &subLED,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Bool),
                                       "led_command") != RCL_RET_OK)
        return false;
    if (rclc_subscription_init_default(
        &subServoDisp,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, UInt8),
                                        "svDispAng") != RCL_RET_OK)
        return false;
    if (rclc_subscription_init_default(
        &subServoCube,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, UInt8),
                                        "svCubeAng") != RCL_RET_OK)
        return false;
    //RoboClaw
    if (rclc_subscription_init_default(
        &subRCStop,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, UInt8),
                                        "RCstop") != RCL_RET_OK)
        return false;
    if (rclc_subscription_init_default(
        &subRCvelMTR1,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, UInt8),
                                        "RCvelMtr1") != RCL_RET_OK)
        return false;
    if (rclc_subscription_init_default(
        &subRCvelMTR2,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, UInt8),
                                        "RCvelMtr2") != RCL_RET_OK)
        return false;
    if (rclc_subscription_init_default(
        &subRCmoveMTR1,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Bool),
                                        "RCmoveMtr1") != RCL_RET_OK)
        return false;
    if (rclc_subscription_init_default(
        &subRCmoveMTR2,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Bool),
                                        "RCmoveMtr2") != RCL_RET_OK)
        return false;

    //puente H
    if (rclc_subscription_init_default(
        &subH_moveMTR,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, UInt8),
                                        "HmtrMove") != RCL_RET_OK)
        return false;

    return true;
}

void RosNode::finiSubscribers(){
    rcl_subscription_fini(&subLED, &node);
    rcl_subscription_fini(&subServoDisp, &node);
    rcl_subscription_fini(&subServoCube, &node);
    rcl_subscription_fini(&subRCStop, &node);
    rcl_subscription_fini(&subRCvelMTR1, &node);
    rcl_subscription_fini(&subRCvelMTR2, &node);
    rcl_subscription_fini(&subRCmoveMTR1, &node);
    rcl_subscription_fini(&subRCmoveMTR2, &node);
    rcl_subscription_fini(&subH_moveMTR, &node);
}
