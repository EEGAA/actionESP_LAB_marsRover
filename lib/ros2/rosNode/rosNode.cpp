#include "rosNode.hpp"

/*bool RosNode::createEntities(){
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

}*/
bool RosNode::createEntities(){
    allocator = rcl_get_default_allocator();

    Serial.println("[ROS] initSupport...");
    if(!initSupport()){ Serial.println("[ROS] FALLO: initSupport"); return false; }

    Serial.println("[ROS] initNode...");
    if(!initNode()){ Serial.println("[ROS] FALLO: initNode"); return false; }

    Serial.println("[ROS] initPublishers...");
    if(!initPublishers()){ Serial.println("[ROS] FALLO: initPublishers"); return false; }

    Serial.println("[ROS] initSubscribers...");
    if(!initSubscribers()){ Serial.println("[ROS] FALLO: initSubscribers"); return false; }

    Serial.println("[ROS] initExecutor...");
    if(!initExecutor()){ Serial.println("[ROS] FALLO: initExecutor"); return false; }

    Serial.println("[ROS] createEntities OK");
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
