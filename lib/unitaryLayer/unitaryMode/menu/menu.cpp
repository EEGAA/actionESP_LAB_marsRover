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
    Serial.println("Que quieres saber?");

    Serial.println("a) Como mover la roboclaw?");
    Serial.println("b) Como mover la bomba?");
    Serial.println("c) Como mover los servos?");
    Serial.println("d) Como mover los nemas?");
    
    Serial.println("Opcion: ");
    while(Serial.available() < 0){ delay(100); }
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
    
    default:
        Serial.println("Opcion NO reconicida tonto,\nIntentalo de nuevo perdedor jaja L"); 
        // menuOption();
        return false;
        break;
    }
        
    menuManager(opM);
    return true;
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
    Serial.println("\n\tROBOCLAW m e n u\t:)");
}
void MENUgen::bomba_M(){
    Serial.println("\n\tBOMBA m e n u\t:)");
}
void MENUgen::servos_M(){
    Serial.println("\n\tSERVOS m e n u\t:)");
}
void MENUgen::nemas_M(){
    Serial.println("\n\tNEMAS m e n u\t:)");
}