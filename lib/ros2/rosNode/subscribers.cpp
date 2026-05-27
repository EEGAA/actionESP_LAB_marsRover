#include "rosNode.hpp"
bool RosNode::initSubscribers(){
    if (rclc_subscription_init_default(
        &subLED,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Bool),
                                       "ledCommand") != RCL_RET_OK)
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
                                        "rcStop") != RCL_RET_OK)
        return false;
    if (rclc_subscription_init_default(
        &subRCvelMTR1,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, UInt8),
                                        "rcVelMtr1") != RCL_RET_OK)
        return false;
    if (rclc_subscription_init_default(
        &subRCvelMTR2,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, UInt8),
                                        "rcVelMtr2") != RCL_RET_OK)
        return false;
    if (rclc_subscription_init_default(
        &subRCmoveMTR1,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Bool),
                                        "rcMoveMtr1") != RCL_RET_OK)
        return false;
    if (rclc_subscription_init_default(
        &subRCmoveMTR2,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Bool),
                                        "rcMoveMtr2") != RCL_RET_OK)
        return false;

    //puente H
    if (rclc_subscription_init_default(
        &subH_moveMTR,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, UInt8),
                                        "hmMove") != RCL_RET_OK)
        return false;
    if (rclc_subscription_init_default(
        &subH_setPWM,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int16),
                                        "hmSpwm10B") != RCL_RET_OK)
        return false;

    //Neo led
    if (rclc_subscription_init_default(
        &subNeo_basic,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, UInt8),
                                        "neoLED_21c") != RCL_RET_OK)
        return false;
    if (rclc_subscription_init_default(
        &subNeo_brillo,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, UInt8),
                                        "neoLED_brillo") != RCL_RET_OK)
        return false;

    if (rclc_subscription_init_default(
        &subSTOP,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Bool),
                                        "STOP") != RCL_RET_OK)
        return false;

    //Nemas
    if (rclc_subscription_init_default(
        &subNemaEX_move,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(lab_interfaces, msg, NemaCMD),
                                        "nemaEX") != RCL_RET_OK)
        return false;
    if (rclc_subscription_init_default(
        &subNemaES_move,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(lab_interfaces, msg, NemaCMD),
                                        "nemaES") != RCL_RET_OK)
        return false;
    if (rclc_subscription_init_default(
        &subNemaBA_move,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(lab_interfaces, msg, NemaCMD),
                                        "nemaBA") != RCL_RET_OK)
        return false;
    if (rclc_subscription_init_default(
        &subNemaAX_move,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(lab_interfaces, msg, NemaCMD),
                                        "nemaAX") != RCL_RET_OK)
        return false;
    if (rclc_subscription_init_default(
        &subNemaStop,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, UInt8),
                                        "nemaStop") != RCL_RET_OK)
        return false;

    if (rclc_subscription_init_default(
        &subUnitaryMode,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Bool),
                                        "unitaryMode") != RCL_RET_OK)
        return false;

    if (rclc_subscription_init_default(
        &subExcavando,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Bool),
                                        "EXCAVANDO") != RCL_RET_OK)
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
    rcl_subscription_fini(&subH_setPWM, &node);
    rcl_subscription_fini(&subNeo_basic, &node);
    rcl_subscription_fini(&subNeo_brillo, &node);
    rcl_subscription_fini(&subSTOP, &node);
    rcl_subscription_fini(&subNemaEX_move, &node);
    rcl_subscription_fini(&subNemaES_move, &node);
    rcl_subscription_fini(&subNemaBA_move, &node);
    rcl_subscription_fini(&subNemaAX_move, &node);
    rcl_subscription_fini(&subNemaStop, &node);
    rcl_subscription_fini(&subUnitaryMode, &node);
    rcl_subscription_fini(&subExcavando, &node);
}
