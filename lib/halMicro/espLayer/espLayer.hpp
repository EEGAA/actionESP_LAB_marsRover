#pragma once
#include <Arduino.h>
#include "../../drivers/myTimer/myTimer.hpp"
#include "../../drivers/myServo/myServo.hpp"
#include "../../drivers/myLED/myLED.hpp"
#include "../../drivers/myNema/myNema.hpp"
#include "../../drivers/myRoboClaw/myRoboClaw.hpp"
#include "../../drivers/myMtrH/myMtrH.hpp"
#include "../../drivers/LED48/LED48.hpp"
#include "../../drivers/myLimit/myLimit.hpp"
extern SERVOgen servoDisp; // dispensación
extern SERVOgen servoCube; // cubeta
extern LEDgen myLed; // ilumia lab
extern EXCAgen exca; // gusano y broca
extern L298Ngen bomba; // limpieza
extern NEMAgen nemaEX; // excavación
extern NEMAgen nemaES; // espectrofotómetro
extern NEMAgen nemaBA; // bandeja
extern NEMAgen nemaAX; // auxiliar

extern LIMITgen limitEX; // excavación
extern LIMITgen limitES; // espectrofotómetro

extern NEOled neoLED; // es el led rgb integrado en la esp pin 48

void myESPinfo();
