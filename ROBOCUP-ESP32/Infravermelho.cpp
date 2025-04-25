#include "Infravermelho.h"
#include <Arduino.h> 

Infravermelho::Infravermelho(int pino_shutInput, uint8_t enderecoInput) {
  //=====PINO-PARA-DESLIGAR-SENSOR=====//
  pino_shut = pino_shutInput;
  //=====ENDERECO-QUE-O-SENSOR-DEVERA-TER=====//
  endereco = enderecoInput;
  //=====DEFINIR-FUNCAO-DO-PINO-DE-DESLIGAR=====//
  pinMode(pino_shut, OUTPUT);
}

void Infravermelho::ligar() {
  digitalWrite(pino_shut, HIGH);
}

void Infravermelho::desligar() {
  digitalWrite(pino_shut, LOW);
}

void Infravermelho::inicializar() {
  //=====ESPERAR-PARA-GARANTIR-VERACIDADE=====//
  delay(50);
  //=====INICIALIZAR-SENSOR=====//
  sensor.init(); 
  //=====DEFINIR-CONFIGURACOES-PADRAO=====//
  sensor.configureDefault();
  //=====DEFINIR-TIMEOUT=====//
  sensor.setTimeout(500);
  //=====MUDAR-O-ENDERECO-DO-SENSOR=====//
  sensor.setAddress(endereco);
  //=====DEFINIR-ESCALA-DO-SENSOR-COMO-2X-PARA-MAIOR-PROVEITO=====//
  sensor.setScaling(2);
}

uint16_t Infravermelho::ler_distancia() {
  return sensor.readRangeSingleMillimeters();
}