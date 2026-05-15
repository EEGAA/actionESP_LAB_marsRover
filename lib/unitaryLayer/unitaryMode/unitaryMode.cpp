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
    Serial.println(" ");
    Serial.print(teclaChar);
    Serial.println(" "+String(teclaInt));
}

void UNITYgen::genSwitch(){
    uint8_t aux;
    switch(teclaChar){
        //casos GENERALES
        case 'Z'://selecciona el servo de la dispensacion
            myMenu.separacion(false);
            Serial.println("Entra a bule servo dispensacion");
            while(loopServo(true)){}
            Serial.println("Sale con exito del bucle dispensacion");
            myMenu.separacion(true);
            myMenu.separacion(false);
            break;
        case 'X'://seleciona al de la cubeta
            myMenu.separacion(false);
            Serial.println("Entra a bule servo cubeta optica");
            while(loopServo(false)){}
            Serial.println("Sale con exito del bucle cubeta optica");
            myMenu.separacion(true);
            myMenu.separacion(false);
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
            Serial.println("\n\nTODO DETENIDO awevo :)\n\n");
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


        //estos case corresponden al manejo de la logica del control de los motores nema
        case 'n':
            controlNEMA();
            switch(myNEMAdta.nemaAux){
                case 0:
                    Serial.println("NEMA EX-cavadora seleccionado");
                    break;
                case 1:
                    Serial.println("NEMA ES-pectrometro seleccionado");
                    break;
                case 2:
                    Serial.println("NEMA BA-ndeja seleccionado");
                    break;
                case 3:
                    Serial.println("NEMA AX-auxiliar seleccionado");
                    break;
            }
            break;
        case 'm':
            switch(myNEMAdta.nemaAux){
                case 0:
                    Serial.println("NEMA EX-cavadora CARACTERISTICAS");
                    break;
                case 1:
                    Serial.println("NEMA ES-pectrometro CARACTERISTICAS");
                    break;
                case 2:
                    Serial.println("NEMA BA-ndeja CARACTERISTICAS");
                    break;
                case 3:
                    Serial.println("NEMA AX-auxiliar CARACTERISTICAS");
                    break;
            }
            break;
        case 'b':
            myNEMAdta.bndMode = !myNEMAdta.bndMode;
            if(myNEMAdta.bndMode){
                Serial.println("Modifica PASOS");
            }else{
                Serial.println("Modifica TIEMPO");
            }
            break;
        case 'c':
            myNEMAdta.interMENOS();
            Serial.println("Intervalo actual "+String(myNEMAdta.intervalo));
            break;
        case 'v':
            myNEMAdta.interMAS();
            Serial.println("Intervalo actual "+String(myNEMAdta.intervalo));
            break;
        case 'z':
            if(myNEMAdta.bndMode){//modifica pasos
                switch(myNEMAdta.nemaAux){
                    case 0:
                        infoEX.pasosINTER(false, myNEMAdta.intervalo);
                        break;
                    case 1:
                        infoES.pasosINTER(false, myNEMAdta.intervalo);
                        break;
                    case 2:
                        infoBA.pasosINTER(false, myNEMAdta.intervalo);
                        break;
                    case 3:
                        infoAX.pasosINTER(false, myNEMAdta.intervalo);
                        break;
                }
            }else{//modifica tiempo
                switch(myNEMAdta.nemaAux){
                    case 0:
                        infoEX.tiempoINTER(false, myNEMAdta.intervalo);
                        break;
                    case 1:
                        infoES.tiempoINTER(false, myNEMAdta.intervalo);
                        break;
                    case 2:
                        infoBA.tiempoINTER(false, myNEMAdta.intervalo);
                        break;
                    case 3:
                        infoAX.tiempoINTER(false, myNEMAdta.intervalo);
                        break;
                }
            }
            break;
        case 'x':
            if(myNEMAdta.bndMode){
                switch(myNEMAdta.nemaAux){
                    case 0:
                        infoEX.pasosINTER(true, myNEMAdta.intervalo);
                        break;
                    case 1:
                        infoES.pasosINTER(true, myNEMAdta.intervalo);
                        break;
                    case 2:
                        infoBA.pasosINTER(true, myNEMAdta.intervalo);
                        break;
                    case 3:
                        infoAX.pasosINTER(true, myNEMAdta.intervalo);
                        break;
                }
            }else{
                switch(myNEMAdta.nemaAux){
                    case 0:
                        infoEX.tiempoINTER(true, myNEMAdta.intervalo);
                        break;
                    case 1:
                        infoES.tiempoINTER(true, myNEMAdta.intervalo);
                        break;
                    case 2:
                        infoBA.tiempoINTER(true, myNEMAdta.intervalo);
                        break;
                    case 3:
                        infoAX.tiempoINTER(true, myNEMAdta.intervalo);
                        break;
                }
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

bool UNITYgen::loopServo(bool bnd){
    char op;
    Serial.print("Opcion: ");
    while(!Serial.available() > 0){ delay(100); }
    op = Serial.read();

    switch(op){
        case '0':
            if(bnd)
                servoDisp.moveAng(0.0f);
            else
                servoCube.moveAng(0.0f);
            Serial.println("angulo actual 0°");
            break;
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
//los siguientes metodos corresponen al control de los motroes nema
void UNITYgen::controlNEMA(){
    myNEMAdta.nemaAux++;
    if(myNEMAdta.nemaAux > 3)
        myNEMAdta.nemaAux = 0;
}
