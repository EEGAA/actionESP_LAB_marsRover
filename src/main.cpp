//en la rama devNewStruct hare una mejor organizacion de rosNode.hpp para escalar el proyecto facilmente
#include <rosConnection.hpp>
RosConnection manager;
void setup(){
    manager.init();
}
void loop(){
    manager.update();
}
