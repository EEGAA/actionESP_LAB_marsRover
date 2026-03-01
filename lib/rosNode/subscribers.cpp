#include <rosNode.hpp>
bool RosNode::initSubscribers(){
    if (rclc_subscription_init_default(
        &subscriber,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Bool),
                                       "led_command") != RCL_RET_OK)
        return false;
    return true;
}
void RosNode::finiSubscribers(){
    rcl_subscription_fini(&subscriber, &node);
}
