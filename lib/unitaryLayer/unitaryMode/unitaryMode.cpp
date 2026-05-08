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
        case 'Z'://selecciona el servo de la dispensacion
            Serial.println("Entra a bule servo dispensacion");
            while(loopServo(true)){}
            Serial.println("Sale con exito del bucle dispensacion");
            break;
        case 'X'://seleciona al de la cubeta
            Serial.println("Entra a bule servo cubeta optica");
            while(loopServo(false)){}
            Serial.println("Sale con exito del bucle cubeta optica");
            break;
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


        //ESTO es para la bomba controlada con el puente H
        case '1':
            bomba.PWMmenos(5);
            Serial.println("PWM actual: "+String(bomba.getPWM()));
            break;
        case '2':
            bomba.moveL();
            Serial.println("Movienodo bomba en sentido antihorario");
            break;
        case '3':
            bomba.moveR();
            Serial.println("Moviendo bomba en sentido horario");
            break;
        case '4':
            bomba.PWMmas(5);
            Serial.println("PWM actual: "+String(bomba.getPWM()));
            break;
        case '5':
            bomba.stop();
            Serial.println("BOMBAA stop con exito :)");
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

bool UNITYgen::loopServo(bool bnd){
    char op;
    Serial.print("Opcion: ");
    while(!Serial.available() > 0){ delay(100); }
    op = Serial.read();

    switch(op){
        case '1':
            if(bnd)
                servoDisp.moveAng(20.0f);
            else
                servoCube.moveAng(20.0f);
            Serial.println("angulo actual 20°");
            break;
        case '2':
            if(bnd)
                servoDisp.moveAng(40.0f);
            else
                servoCube.moveAng(40.0f);
            Serial.println("angulo actual 40°");
            break;
        case '3':
            if(bnd)
                servoDisp.moveAng(60.0f);
            else
                servoCube.moveAng(60.0f);
            Serial.println("angulo actual 60°");
            break;
        case '4':
            if(bnd)
                servoDisp.moveAng(80.0f);
            else
                servoCube.moveAng(80.0f);
            Serial.println("angulo actual 80°");
            break;
        case '5':
            if(bnd)
                servoDisp.moveAng(100.0f);
            else
                servoCube.moveAng(100.0f);
            Serial.println("angulo actual 100°");
            break;
        case '6':
            if(bnd)
                servoDisp.moveAng(120.0f);
            else
                servoCube.moveAng(120.0f);
            Serial.println("angulo actual 120°");
            break;
        case '7':
            if(bnd)
                servoDisp.moveAng(140.0f);
            else
                servoCube.moveAng(140.0f);
            Serial.println("angulo actual 140°");
            break;
        case '8':
            if(bnd)
                servoDisp.moveAng(160.0f);
            else
                servoCube.moveAng(160.0f);
            Serial.println("angulo actual 160°");
            break;
        case '9':
            if(bnd)
                servoDisp.moveAng(180.0f);
            else
                servoCube.moveAng(180.0f);
            Serial.println("angulo actual 180°");
            break;
        case 'S':
            return false;
            break;
        default:
            Serial.println("Tecla no reconocida");
            Serial.println("'S' para salir de este bucle");
            break;
    }

    return true;
}
