#pragma once
#include <Arduino.h>
#include "../../drivers/myTimer/myTimer.hpp"
#include "../../drivers/myServo/myServo.hpp"
#include "../../drivers/myLED/myLED.hpp"
#include "../../drivers/myNema/myNema.hpp"
#include "../../drivers/myRoboClaw/myRoboClaw.hpp"
extern SERVOgen servoDisp;
extern SERVOgen servoCube;
extern LEDgen myLed;
extern EXCAgen exca;

void myESPinfo();
