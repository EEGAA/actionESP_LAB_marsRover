#include "menu.hpp"

MENUgen::MENUgen(){
    //roboclaw, bomba, servos, nemas
    this->M[0] = 'r';
    this->M[1] = 'b';
    this->M[2] = 's';
    this->M[3] = 'n';
}

bool MENUgen::menuOption(){
    char op = 'z', opM = 'x';
    separacion(true);
    Serial.println("\tQue quieres saber?");

    Serial.println("a) Como mover la roboclaw?");
    Serial.println("b) Como mover la bomba?");
    Serial.println("c) Como mover los servos?");
    Serial.println("d) Como mover los nemas?");
    Serial.println("e) Para mostrar datos GENERALES");
    Serial.println("R) Para regresar a modo micro ROS");
    Serial.println("\nNOTA: el programa diferencia minusculas de mayusculas\n");
    Serial.println("Asegurate de ingresar el formato correcto... ;)");
    separacion(false);
    Serial.print("Opcion: ");
    while(!Serial.available() > 0){ delay(100); }
    op = Serial.read();
    Serial.print("\n");
    separacion(false);
    switch (op){
    case 'a':
        opM = 'r';
        break;
    case 'b':
        opM = 'b';
        break;
    case 'c':
        opM = 's';
        break;
    case 'd':
        opM = 'n';
        break;
    case 'R':
        ESP.restart();
        break;
    case 'e':
        generalDTA();
        break;
    
    default:
        Serial.println("Opcion NO reconicida tonto,\nIntentalo de nuevo pendejo jaja L"); 
        // menuOption();
        return true;
        break;
    }
        
    menuManager(opM);
    return false;
}

void MENUgen::menuManager(char currentTecla){
    if(M[0] == currentTecla){
        roboclaw_M();
        return;
    }
    if(M[1] == currentTecla){
        bomba_M();
        return;
    }
    if(M[2] == currentTecla){
        servos_M();
        return;
    }
    if(M[3] == currentTecla){
        nemas_M();
        return;
    }
}

void MENUgen::roboclaw_M(){
    separacion(true);
    Serial.println("\n\tROBOCLAW m e n u :)");
    Serial.println(" f - detiene ambos motores");
    Serial.println("\t- Motor Gusano -");
    Serial.println(" q - giro antihorario mtr1");
    Serial.println(" e - giro horario mtr1");
    Serial.println("\t- Motor Broca -");
    Serial.println(" a - giro antihorario mtr2");
    Serial.println(" d - giro horario mtr2");
    Serial.println("\t- Modificar Velocidad de ambos MTR -");
    Serial.println(" r - cambia entre mtr1 o mtr2 para ajustar sus velocidades");
    Serial.println("\t donde 0 = stop   ;   127 = maxVel");
    Serial.println(" w - aumenta en 5 la velocidad del mtrX");
    Serial.println(" s - disminuye en 5 la velocidad del mtrX");
    separacion(false);
}
void MENUgen::bomba_M(){
    Serial.println("\n\tBOMBA m e n u :)");
}
void MENUgen::servos_M(){
    Serial.println("\n\tSERVOS m e n u :)");
}
void MENUgen::nemas_M(){
    Serial.println("\n\tNEMAS m e n u :)");
}

void MENUgen::generalDTA(){
    separacion(true);
    Serial.println("\n\tGENERAL d a t a :)");
    Serial.println(" S - para detener TODO");
    Serial.println("\nTECLADO");
    Serial.println("designadas a ROBOCLAW:");
    Serial.println("QWER\tmoveMTR1true, +velMTRx, moveMTR1false, switchMTRx"); 
    Serial.println("ASDF\tmoveMTR2true, -velMTRx, moveMTR2false, stopMTR1y2");
    separacion(false);
}

void MENUgen::separacion(bool bnd){
    if(bnd)
        Serial.println("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
    else
        Serial.println("____________________________________________________");
}