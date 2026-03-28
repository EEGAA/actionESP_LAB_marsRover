#include "espLayer.hpp"
NEOled neoLED;
//- - - -  pinTx, pinRx
EXCAgen exca(39, 40);
//- - - Hz|canalPWM|resolucion|pulsoMin|pulsoMax|pinServo
SERVOgen servoDisp(50, 0, 14, 550, 2450, 14);
SERVOgen servoCube(50, 1, 14, 550, 2450, 13);
//- - - - pinLED
LEDgen myLed(47);
//- - - - - INa, INb, pinPWM, canalPWM
L298Ngen bomba(10, 11, 9, 2);
//- - - - - dir, step, enable
// NEMAgen nemaEX(4, 5, 6);
// NEMAgen nemaES(7, 8, 9);
// NEMAgen nemaBA(10, 11, 12);
// NEMAgen nemaAX(15, 16, 17);

//pines PCB
NEMAgen nemaEX(2, 42, 1);
NEMAgen nemaES(37, 38, 36);
NEMAgen nemaBA(5, 4, 6);
NEMAgen nemaAX(18, 8, 17);
/*
NO usar estos pines

26 al 32  (flash)
33 al 37  (psram en muchos módulos)
0
3
45
46

Pines recomendados
lado izquierdo
de este lado se conectan los 3 nema
4 5 6 7 8 9 10 11 12 13 14 (gpio)
cada nema usa 3 pines por lo que de este lado sobran 2 pines

lado derecho
15 16 17 18 21 (gpio)
38 39 40 41 42 (gpio)
47 48 (solo entrada)
pin 39 y 40 apartados para roboclaw
*/
