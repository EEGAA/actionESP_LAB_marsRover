#include "espLayer.hpp"
NEOled neoLED;
//- - - -  pinTx, pinRx
EXCAgen exca(39, 40);
//- - - Hz|canalPWM|resolucion|pulsoMin|pulsoMax|pinServo
SERVOgen servoDisp(50, 0, 14, 550, 2450, 14);
SERVOgen servoCube(50, 1, 14, 550, 2450, 13);// el home es en 90 grados
//- - - - pinLED
LEDgen myLed(47);
//- - - - - INa, INb, pinPWM, canalPWM
L298Ngen bomba(10, 11, 9, 2);

//pines PCB nueva
//- - - - - dir, step, enable
NEMAgen nemaBA(42, 2, 1); //bien
NEMAgen nemaES(38, 37, 36); //bien
NEMAgen nemaEX(8, 18, 17); // bien
NEMAgen nemaAX(4, 5, 6); // 


//PCB viejita
// nemaA = {36, 37, 38}, nemaB = {42, 2, 1}; //nemaC{4, 5 ,6}
// NEMAgen nemaEX(36, 37, 38);
// NEMAgen nemaES(42, 2, 1);
// NEMAgen nemaBA(4, 5 ,6);
// NEMAgen nemaAX(18, 8, 17);


//Pines limit switch
LIMITgen limitEX(19);
LIMITgen limitES(20);

//esto es una clase que solo gestiona el estado de una bnadera o sea variable booleana
SIGNALgen bndSignal_UM;
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

//NOTAS generales
//NOTAS: definicion de pasos NEMA
// para mover el nema ex, el recorrido es de 3500 pasos -> true = sube; false = baja


//nemaES, direccion 1 va al home, con 0 va a cubeta
//pasos desde el home nemaES para llegar primera cubeta = 1800
//segunda cubeta 600 pasos despues de la pirmea
//o 2400 desde el home