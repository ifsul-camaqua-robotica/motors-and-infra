#ifndef INFRAVERMELHO_H
#define INFRAVERMELHO_H

#include <VL6180X.h>

class Infravermelho {
  private:
    //=====PINO-PARA-DESLIGAR-SENSOR=====//
    int pino_shut;
    //=====ENDERECO-QUE-O-SENSOR-DEVERA-TER=====//
    uint8_t endereco;
    //=====INICIALIZAR-OBJETO-PARA-CONTROLAR-SENSOR-INFRAVERMELHO=====//
    VL6180X sensor;

  public:
    Infravermelho(int pino_shutInput, uint8_t enderecoInput;
    void ligar();
    void desligar();
    void inicializar();
    uint16_t ler_distancia();
};

#endif
