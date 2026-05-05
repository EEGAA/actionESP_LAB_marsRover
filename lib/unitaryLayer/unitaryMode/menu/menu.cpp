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
    Serial.println("\n\tQue quieres saber?");

    Serial.println("a) Como mover la roboclaw?");
    Serial.println("b) Como mover la bomba?");
    Serial.println("c) Como mover los servos?");
    Serial.println("d) Como mover los nemas?");
    Serial.println("e) Para mostrar datos GENERALES");
    Serial.println("R) Para regresar a modo micro ROS");
    
    Serial.println("Opcion: ");
    while(!Serial.available() > 0){ delay(100); }
    op = Serial.read();
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
        Serial.println("Opcion NO reconicida tonto,\nIntentalo de nuevo perdedor jaja L"); 
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
    Serial.println("\n\tROBOCLAW m e n u :)");
    Serial.println(" F detiene ambos motores");
    Serial.println("\t- Motor Gusano -");
    Serial.println(" Q giro antihorario mtr1");
    Serial.println(" E giro horario mtr1");
    Serial.println("\t- Motor Broca -");
    Serial.println(" A giro antihorario mtr2");
    Serial.println(" D giro horario mtr2");
    Serial.println("\t- Modificar Velocidad de ambos MTR -");
    Serial.println(" R cambia entre mtr1 o mtr2 para ajustar sus velocidades");
    Serial.println("\t donde 0 = stop   ;   127 = maxVel");
    Serial.println(" W aumenta en uno la velocidad del mtrX");
    Serial.println(" S disminuye en uno la velocidad del mtrX");
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
    Serial.println("\n\tGENERAL d a t a :)");
}