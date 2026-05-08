#include "rosNode.hpp"
// uint32_t RosNode::generate_client_key(){
//     uint64_t mac = ESP.getEfuseMac();
//     return (uint32_t)(mac ^ millis());//llave unica
// }
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
    // y demas cosas que necesite inicializar
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
