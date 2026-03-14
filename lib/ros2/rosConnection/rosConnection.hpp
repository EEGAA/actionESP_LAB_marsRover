#pragma once
//#include <micro_ros_platformio.h>
#include "../rosNode/rosNode.hpp"
#include "../../halMicro/halRTOS/sharedData/sharedData.hpp"
class RosConnection{
private:
    enum State{
        WAITING_AGENT,
        AGENT_AVAILABLE,
        AGENT_CONNECTED,
        AGENT_DISCONNECTED
    };
    State state = WAITING_AGENT;
    RosNode ros_node;
public:
    void init();
    void update();
};
