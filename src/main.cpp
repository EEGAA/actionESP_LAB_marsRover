//esta modificacion no tiene chiste nadamas quiero hacer un comit en mi rama dev
#include <rosConnection.hpp>
RosConnection manager;
void setup(){
    manager.init();
}
void loop(){
    manager.update();
}
