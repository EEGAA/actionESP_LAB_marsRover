#include <myTimer.hpp>

Tempo::Tempo(unsigned long intervalo, bool autoReinicio){
    this->intervalo_ = intervalo;
    this->autoReinicio_ = autoReinicio;
    this->usarMicros_ = false;//pq de cajon usa millis
    initTempo();
}

void Tempo::initTempo(){
    tempoBase_ = getCurrentTime();
}
void Tempo::resetTempo(){
    initTempo();
}

void Tempo::setInter(unsigned long nuevoIntervalo){
    intervalo_ = nuevoIntervalo;
}

void Tempo::useMicro(bool usar){
    usarMicros_ = usar;
    initTempo();
}

unsigned long Tempo::getCurrentTime(){
    return usarMicros_ ? micros() : millis();
}

bool Tempo::checkTimer(){
    unsigned long ahora = getCurrentTime();
    bool expirado = (ahora - tempoBase_) >= intervalo_;

    if(expirado && autoReinicio_)
        tempoBase_ += intervalo_;

    return expirado;
}

unsigned long Tempo::tempoDiff(){
    unsigned long transcurrido = getCurrentTime() - tempoBase_;
    if(transcurrido >= intervalo_)
        return 0;
    return intervalo_ - transcurrido;
}
