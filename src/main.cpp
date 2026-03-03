#include "../lib/ros2/rosConnection/rosConnection.hpp"
RosConnection manager;
void setup(){
    manager.init();
}
void loop(){
    manager.update();
}
