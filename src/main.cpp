#include "../lib/ros2/rosConnection/rosConnection.hpp"
RosConnection manager;
void setup(){
    manager.init();
    myESPinfo();
}
void loop(){
    manager.update();
}
