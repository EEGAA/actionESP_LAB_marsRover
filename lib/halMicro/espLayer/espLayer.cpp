#include "espLayer.hpp"

EXCAgen exca(39, 40);
SERVOgen servoDisp(50, 0, 14, 550, 2450, 14);
SERVOgen servoCube(50, 1, 14, 550, 2450, 13);
LEDgen myLed(47);
L298Ngen bomba(15, 16, 17);

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
