#pragma once
#include <Arduino.h>
#include "../../drivers/myTimer/myTimer.hpp"
#include "../../drivers/myServo/myServo.hpp"
#include "../../drivers/myLED/myLED.hpp"
#include "../../drivers/myNema/myNema.hpp"
#include "../../drivers/myRoboClaw/myRoboClaw.hpp"
extern Servo servoDisp;//recuerda usar stopPWM ya que se mueva el servo,
extern LEDgen myLed;
extern EXCAVA exca;
