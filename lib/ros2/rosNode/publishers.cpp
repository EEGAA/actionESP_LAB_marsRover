#include "rosNode.hpp"
bool RosNode::initPublishers(){
    if (rclc_publisher_init_default(
        &pubCounter,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
                                    "counter") != RCL_RET_OK)
        return false;
    return true;
}
void RosNode::finiPublishers(){
    rcl_publisher_fini(&pubCounter, &node);
}
