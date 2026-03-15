#include "espLayer.hpp"
void myESPinfo(){
    //uint64_t chipid = ESP.getEfuseMac();
    Serial.println("\n************************************************");
    Serial.println("======Data sobre la ESP actual======");
    Serial.println("\nChip: " + String(ESP.getChipModel()));
    Serial.println("Cores: " + String(ESP.getChipCores()));
    Serial.println("CPU MHz: " + String(ESP.getCpuFreqMHz()));
    Serial.println("\nMemoria SRAM bytes");
    Serial.println("Heap libre: " + String(ESP.getFreeHeap()));
    Serial.println("Heap minimo: " + String(ESP.getMinFreeHeap()));
    Serial.println("Heap max asignable: " + String(ESP.getMaxAllocHeap()));
    Serial.println("Heap size: " + String(ESP.getHeapSize()));
    if(psramFound()){
        Serial.println("\nMemoria PSRAM bytes");
        Serial.println("PSRAM size: " + String(ESP.getPsramSize()));
        Serial.println("PSRAM libre: " + String(ESP.getFreePsram()));
        Serial.println("PSRAM max asignable: " + String(ESP.getMaxAllocPsram()));
    }else
        Serial.println("PSRAM: NO DISPONIBLE");
    Serial.println("\nMemoria Flash bytes");
    Serial.println("Flash freq Hz: " + String(ESP.getFlashChipSpeed()));
    Serial.println("Flash mode: " + String(ESP.getFlashChipMode()));
    Serial.println("Flash size: " + String(ESP.getFlashChipSize()));
    Serial.println("Firmware size: " + String(ESP.getSketchSize()));
    Serial.println("\nFree flash: " + String(ESP.getFreeSketchSpace()));
    Serial.println("\nID chip: " + String(ESP.getEfuseMac()));
    Serial.println("SDK: " + String(ESP.getSdkVersion()));
    Serial.println("************************************************");
    /*
     ESP.restart();
     Serial.println(ESP.getResetReason());
     Serial.println(ESP.getChipRevision());
     ESP.abort();
     */
}
