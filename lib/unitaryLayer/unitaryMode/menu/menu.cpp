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
    Serial.println(" 1 - disminuye PWM");
    Serial.println(" 2 - Mueve bomba antihorario");
    Serial.println(" 3 - Mueve bomba horario");
    Serial.println(" 4 - aumenta PWM");
    Serial.println(" 5 - DETIENE la bomba");
}
void MENUgen::servos_M(){
    Serial.println("\n\tSERVOS m e n u :)");
    Serial.println("Primero accede al control de uno solo motor SERVO");
    Serial.println(" Z - para seleccionar el servo dispensacion");
    Serial.println(" X - para seleccionar el servo cubeta optica");
    Serial.println("\nUna vez selecionado el motor veras un mensaje similar a:");
    Serial.println("Entra a bule servo ");
    Serial.println("\n\tLas siguientes teclas solo funcinan\n\tdentro del bucle del servo");
    Serial.println("\n S - para salir del bucle servo, y regresar al principal");
    Serial.println("\n teclas del 0 al 9 realizan:");
    Serial.println(" 0 -> 0°     1 -> 20°     2 -> 40°     3 -> 60°     4 -> 80°");
    Serial.println(" 5 -> 100°   6 -> 120°    7 -> 140°    8 -> 160°    9 -> 180°");
    //w para aumentar un grado, s para disminuirlo
    //d para aumentar 5 grados, a para disminuirlo
}
void MENUgen::nemas_M(){
    Serial.println("\n\t\tNEMAS m e n u :)");
    //primero se sellciona un nema, hay 4 nemas a escoger, ex, es, ba, y ax
    //se menciona como puedes modificar las caracteristicas del nema seleccionado
    //indica que tienes que hacer para poder mover el nema
    Serial.println("\nPRIMERO selecciona el nema que quieres controlar con \"n\"");
    Serial.println(" n - switch que seleciona el nema a controlar");
    Serial.println("NEMAS: EX->cavadora, ES->pectrometro, BA->ndeja y AX->auxiliar");
    Serial.println("\nPara ver el motor actual y sus caracteristicas, es con: ");
    Serial.println(" m - muestra el motor selecionado y sus atributos actuales");
    Serial.println("\n¿Como mover el NEMA?");
    Serial.println(" j - mover NEMA en sentido antihorario");
    Serial.println(" k - mover NEMA en sentido horario");

    Serial.println("\n¿Como modificar los atributos?");
    Serial.println("   puedes modificar la cantidad de pasos");
    Serial.println("   y tambien la cantidad de milisegundos entre pasos");
    Serial.println("     b - Decide si modificas pasos o tiempo");
    
    Serial.println("\n    ¿Como disminuir o aumentar el intervalo de cambio?");
    Serial.println("     c - disminuye en uno el intervalo del atributo selecionado");
    Serial.println("     v - aumenta en uno el intervalo del atributo selecionado");

    Serial.println("\n    ¿Como aplicar los cambios al motor NEMA?");
    Serial.println("     z - disminuye atributo seleccionado, un intervalo");
    Serial.println("     x - aumenta atributo seleccionado, un intervalo");
    /*
        B switchea que aumentar entre cantidad de pasos o timer entre pasos
        hay cierto intervalo entre cada vez que se aumenta o se disminuye
        (Esto quiero decir que el factor de cambio des de 2 posibles opiciones, pasos, o delay)

        Normalmente el intervalo es de 50

        C disminuye en 1 el intervalo 
        V aumenta en 1 el intervalo

        para aplicar una resta o una suma, del intervalo al posible factor de cambio:
        Z para restar al cambio
        X para sumar al cambio
    */
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
