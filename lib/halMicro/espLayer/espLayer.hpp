#pragma once
#include <Arduino.h>
#include "../../drivers/myTimer/myTimer.hpp"
#include "../../drivers/myServo/myServo.hpp"
#include "../../drivers/myLED/myLED.hpp"
extern Servo servoDisp;//recuerda usar stopPWM ya que se mueva el servo,
extern LEDgen myLed;
