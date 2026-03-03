//en la rama devNewStruct hare una mejor organizacion de rosNode.hpp para escalar el proyecto facilmente
#include "../lib/ros2/rosConnection/rosConnection.hpp"
RosConnection manager;
void setup(){
    manager.init();
}
void loop(){
    manager.update();
}
