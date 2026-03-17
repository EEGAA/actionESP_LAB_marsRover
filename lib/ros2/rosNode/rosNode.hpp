#pragma once

#include "../halMicro/espLayer/espLayer.hpp"

#include <micro_ros_platformio.h>

#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <std_msgs/msg/int32.h>
// #include <std_msgs/msg/int16.h>
#include <std_msgs/msg/u_int8.h>
#include <std_msgs/msg/bool.h>

class RosNode{
private:
    //Variables locales de ROS2 (micro ros agent)

    rcl_allocator_t allocator;
    rclc_support_t support;
    rcl_node_t node;

    rcl_publisher_t pubCounter;
    rcl_subscription_t subLED, subServo;
    rclc_executor_t executor;

    std_msgs__msg__Int32 counter_msg;
    std_msgs__msg__Bool led_msg;
    std_msgs__msg__UInt8 servoAng_msg;

    //este callback manipula el LED
    static void subLED_callback(const void * msgin);
    static void subServoAng_callback(const void * msgin);

public:
    //metodos relacionados con ROS
    void initSerial();//debe usarse en main.cpp setup
    bool createEntities();
    void destroyEntities();
    void spinROS();
    //******metodos sobre los topicos******
        //los siguientes metodos se manjean en rosSetup.cpp y se usan en createEntities() en rosNode.cpp
    bool initSupport();
    bool initNode();
    bool initExecutor();
        //los siguientes dos metodos se manejan en subscribers.cpp
        // son usados en createEntities y destroyEntities en rosNode.cpp
    bool initSubscribers();
    void finiSubscribers();
        //los siguientes dos metodos se manejan en publishers.cpp
        // son usados en createEntities y destroyEntities en rosNode.cpp
    bool initPublishers();
    void finiPublishers();

    void publishCounter();
};
//es buena idea poner callback en private  y publish en public
