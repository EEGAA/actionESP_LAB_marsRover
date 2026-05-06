#include "unitaryMode.hpp"


UNITYgen::UNITYgen(){
    omiteDefault = true;
    bndRBCLW = true;
    interVclw = 5;
}

void UNITYgen::update(){
    setTecla();
    showTeclas();
    if(teclaChar == 'R')//este if es bien importante pq gracias a el regresamos a modo ros2
         ESP.restart();

    if(teclaInt == 9){//si pucha tab muestra un menu
        while(myMenu.menuOption()){}
        omiteDefault = false;
    }
    genSwitch();
}


void UNITYgen::setTecla(){
    this->teclaInt = Serial.read();
    this->teclaChar = (char)teclaInt;
}
char UNITYgen::getTeclaC(){
    return teclaChar;
}
int UNITYgen::getTeclaI(){
    return teclaInt;
}

void UNITYgen::showTeclas(){
    Serial.print(teclaChar);
    Serial.println(" "+String(teclaInt));
}

void UNITYgen::genSwitch(){
    uint8_t aux;
    switch(teclaChar){
        //casos GENERALES
        case 'S'://detiene todo alv como vez asi nomas en caliente
            Serial.println("PAREN TODO!!!");
            exca.stop();
            bomba.stop();
            neoLED.LEDoff();
            myLed.LEDoff();
            nemaEX.setStopNema(true);
            nemaES.setStopNema(true);
            nemaBA.setStopNema(true);
            nemaAX.setStopNema(true);
            Serial.println("TODO DETENIDO awevo");
            break;
        /// estos case son para mover los motores de la roboclaw
        case 'q'://antihorario
            exca.moveMTR1(true);
            Serial.println("moveMTR1 en true");
            break;
        case 'e'://horario
            exca.moveMTR1(false);
            Serial.println("moveMTR1 en false");
            break;
        case 'a'://antihorario
            exca.moveMTR2(true);
            Serial.println("moveMTR2 en true");
            break;
        case 'd'://horario
            exca.moveMTR2(false);
            Serial.println("moveMTR2 en false");
            break;
        case 'f':// f de freno para ambos motores de la excaRoboclaw
            exca.stop();
            Serial.println("Ambos motores claw STOP!!!");
            break;
        case 'r'://cambia entre modificar la velocidad del gusano o de la broca
            bndRBCLW = !bndRBCLW;
            if(bndRBCLW)
                Serial.println("Cambia a gusano");
            else
                Serial.println("Cambia a broca");
            break;
        case 'w'://aumenta la velocidad de un motor controlado por roboclaw, depende de la seleccion de 'r'
            if(bndRBCLW){
                aux = exca.getVel1();
                exca.setVel1(aux + interVclw);
                Serial.println("Veloidad gusano = "+String(exca.getVel1()));
            }else{
                aux = exca.getVel2();
                exca.setVel2(aux + interVclw);
                Serial.println("Veloidad broca = "+String(exca.getVel2()));
            }
            break;
        case 's'://disminuye la velociad de el motor seleccionado por 's'
            if(bndRBCLW){
                aux = exca.getVel1();
                exca.setVel1(aux - interVclw);
                Serial.println("Veloidad gusano = "+String(exca.getVel1()));
            }else{
                aux = exca.getVel2();
                exca.setVel2(aux - interVclw);
                Serial.println("Veloidad broca = "+String(exca.getVel2()));
            }
            break;

        default:
            if(omiteDefault)
                Serial.println("Tecla NO reconocida :( ...");
            else
                omiteDefault = true;
            // Serial.println("Intenta con alguna de las siguientes opciones");
            //aki se supone que debo de imprimir un menu relatando lo que hace cada tecla pero xd pa luego sera otro dia
            break;
    }
}
