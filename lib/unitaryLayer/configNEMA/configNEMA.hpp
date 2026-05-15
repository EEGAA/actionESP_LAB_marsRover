#pragma once
//Esta clase solo ba a contener el registro de las caracteristicas actuales del nema
//solo va a guardar la cantidad de pasos que se tiene que mover, y a que velocidad hacerlo 

class INFO_NEMA{
private:
    int pasos;//ps la cantidad de pasos que va a dar cada pulsacion
    bool direccion;//esto realmente no es necesario pq son distintas teclas las que definen esto, pero weno, direccion del nema
    int retraso;//que tanto tiempo espera el nema entre pasos, no estoy seguro si esto sera en milisegundos o en microsegundos
public:
    INFO_NEMA();

    void setPasos(int);
    int getPasos();
    void setDireccion(bool);
    bool getDireccion();
    void setRetraso(int);
    int getRetraso();
    void pasosINTER(bool, int);//[ si bool = true -> aumenta, else disminuye ] -> +- int
    void tiempoINTER(bool, int);
};

class GENERAL_nemaDTA{
public:
    int nemaAux;
    //nemaAux solo puede tener 1 de 4 valores, 0,1,2 o 3, su valor corresponde con el nema a usar
    //el codigo por default decide usar el motor nema 0, o sea el nemaEx cavadora
    //se puede intercambiar el nema por otro usando la tecla "n"
    bool bndMode;
    //bndMode es una bandera que indentifica que cosa se quiere modificar, la canitidad en cuanto a que
    //cantidad de pasos, o cantidad de tiempo entre pasos, 
    //cuando es true = pasos, cuando es false = tiempo
    int intervalo;
    //intervalo lo que hcae es guardar en, la cantidad en la que disminuye o aumenta la cantidad 
    //de pasos y/o tiempo al momento de que el usuario los modifique.
    //esto con el motivo de evitar tener que cambiar de uno en uno cuando se necesite incrementar o
    //disminuir mucho y tambien para poder disminuir o aumentar de uno en uno cunado se necesite 
    GENERAL_nemaDTA();

    void interMENOS();
    void interMAS();
};