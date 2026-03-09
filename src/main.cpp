#include "../lib/ros2/rosConnection/rosConnection.hpp"
RosConnection manager;
void setup(){
    myESPinfo();
    manager.init();
}
void loop(){
    manager.update();
}
