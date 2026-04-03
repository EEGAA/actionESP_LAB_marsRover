#include "myServo.hpp"

SERVOgen::SERVOgen(int freq_, int chanel_, int resolution_, int minPulso_, int maxPulso_, int pin_):
    thisPWM(freq_, chanel_, resolution_, pin_){
    this->minPulso = minPulso_;
    this->maxPulso = maxPulso_;
    this->periodo  = (int)(1e6 / freq_);  // periodo en microsegundos
    ADCmax = thisPWM.getADCmax();
    stopPWM();

    this->currentAngle = 0;
    this->targetAngle = 0;
    this->speed = 0;

    this->lastUpdate = millis();
}

// Mueve el servo a un angulo entre 0 y 180
void SERVOgen::moveAng(float angulo_){
    if (angulo_ < 0 || angulo_ > 180) return;
    this->currentAngle = angulo_;
    // Interpola el pulso en us segun el angulo
    float pulso = minPulso + (maxPulso - minPulso) * (angulo_ / 180.0f);
    // Convierte el pulso a duty cycle en counts ADC
    sendPWM(pulso);
}

void SERVOgen::sendPWM(float pulso_){
    int pwm_ = (int)((pulso_ / periodo) * ADCmax + 0.5f);
    thisPWM.setPWM(pwm_);
}

int SERVOgen::getADCmax(){
    return ADCmax;
}

void SERVOgen::stopPWM(){
    thisPWM.stopPWM();
}

//angulo_ es el angulo objetivo, al cual se movera el servo
//speed_ es un numero entero mayor a 1, indica cuandos grados por segndo se movera el servo
//eso significa que numeros chiquitos equivalen a movimiento lento
//numeros grandes a movimiento rapido,

//es importante dejar claro el hecho de que nunca se movera mas rapido que llamar directamente a moveAng
//y que lo mas lento que se podra mover es 1 grado por segundo
void SERVOgen::setTargetAngle(float angulo_, float speed_){
    if (angulo_ < 0 || angulo_ > 180 || speed_ < 1) return;

    this->targetAngle = angulo_;
    this->speed = speed_;
    this->lastUpdate = millis();
}
//update es quien se encarga de que esto no sea bloqueante, ya que se llama cada ciclo, lo ideal es que este
//dentro de una tarea de freertos
void SERVOgen::update(bool bnd){
    unsigned long now = millis();
    float dt = (now - lastUpdate) / 1000.0f; //en segundos
    lastUpdate = now;

    if (dt <= 0) return;

    float error_ = targetAngle - currentAngle;

    if(abs(error_) < 0.1f)
        currentAngle = targetAngle;
    else{
        float step_;
        if(!bnd)
            step_ = speed * dt;
        else
            step_ = speed * dt * (abs(error_) / 180.0f);

        if(abs(step_) > abs(error_))
            currentAngle = targetAngle;
        else
            currentAngle += (error_ > 0 ? step_ : -step_);
    }

    moveAng(currentAngle);
}

float SERVOgen::getCurrentAngle(){
    return this->currentAngle;
}

bool SERVOgen::isAtTarget(){
    return (abs(targetAngle - currentAngle) < 0.1f);
}
