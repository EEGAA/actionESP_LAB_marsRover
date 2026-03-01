#include <rosConnection.hpp>

void RosConnection::init(){
    ros_node.initSerial();
}

void RosConnection::update()
{
    switch (state) {

        case WAITING_AGENT:
            if (rmw_uros_ping_agent(100, 1) == RMW_RET_OK) {
                state = AGENT_AVAILABLE;
            }
            break;

        case AGENT_AVAILABLE:
            if (ros_node.createEntities()) {
                state = AGENT_CONNECTED;
            } else {
                state = WAITING_AGENT;
            }
            break;

        case AGENT_CONNECTED:
            if (rmw_uros_ping_agent(100, 1) != RMW_RET_OK) {
                state = AGENT_DISCONNECTED;
            } else {
                ros_node.publishCounter();
                ros_node.spinROS();
                delay(500);
            }
            break;

        case AGENT_DISCONNECTED:
            ros_node.destroyEntities();
            state = WAITING_AGENT;
            break;
    }
}
