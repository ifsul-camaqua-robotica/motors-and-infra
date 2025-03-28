//=====VITOR-MAZIERO-OLIVEIRA=====//
//=====TAI2V=====//
//=====GITHUB-vitor-m-o=====//

//=====CHAMAR-BIBLIOTECAS-UTILIZADAS=====//
#include <Wire.h>
#include <VL6180X.h>

//=====DEFINICAO-DOS-SENSORES-INFRAVERMELHOS=====//
VL6180X sensorum;
VL6180X sensordois;
VL6180X sensortres;
VL6180X sensorquatro;

//=====DEFINIR-O-PINO-XSHUT-DO-SENSOR-INFRAVERMELHO=====//
const int shutPinUm = 22;  
const int shutPinDois = 23;  
const int shutPinTres = 24;  
const int shutPinQuatro = 25;  

//// GABRIELA ////
//// TAI4V /////

//// PARTE DO CODIGO ESCRITO PELA GABRIELA ////

//// PWM MOTORES ////
#define PWM_MOTOR_DIREITA 5
#define PWM_MOTOR_ESQUERDA 8

//// ENABLE MOTORES ////
#define ENABLE_MOTOR_DIREITA A0
#define ENABLE_MOTOR_ESQUERDA A1

//// PINOS DIREÇÕES MOTOR DIREITA //// 
#define DIRECAO_HORARIO_DIREITA 6
#define DIRECAO_ANTIHORARIO_DIREITA 7

//// PINOS DEIREÇÕES MOTOR ESQUERDA ////
#define DIRECAO_HORAIO_ESQUERDA 9
#define DIRECAO_ANTIHORARIO_ESQUERDA 10

//// PARTE DO CODIGO ESCRITO PELA GABRIELA ////

void setup() {

  //// PARTE DO CODIGO ESCRITO PELA GABRIELA ////

  pinMode(PWM_MOTOR_DIREITA, OUTPUT);
  pinMode(PWM_MOTOR_ESQUERDA, OUTPUT);

  pinMode(ENABLE_MOTOR_DIREITA, OUTPUT);
  pinMode(ENABLE_MOTOR_ESQUERDA, OUTPUT);

  pinMode(DIRECAO_HORARIO_DIREITA, OUTPUT);
  pinMode(DIRECAO_ANTIHORARIO_DIREITA, OUTPUT);

  pinMode(DIRECAO_HORAIO_ESQUERDA, OUTPUT);
  pinMode(DIRECAO_ANTIHORARIO_ESQUERDA, OUTPUT);
  
  //// PARTE DO CODIGO ESCRITO PELA GABRIELA ////

  //=====INICIALIZAÇÃO-DOS-SENSORES-INFRAVERMELHO=====//

  //=====INICIALIZAR-SERIAL=====//
  Serial.begin(9600);

  //=====INICIALIZAR-WIRE=====//
  Wire.begin();

  //=====DEFINIR-O-MODO-DE-PINO-DO-XSHUT=====//
  pinMode(shutPinUm, OUTPUT);
  //=====ENVIAR-SINAL-PARA-O-PINO-XSHUT-ASSIM-DESLIGANDO-O-SENSOR-ATE-QUE-ELE-NAO-RECEBA-MAIS-SINAL-NESTA-PORTA=====//
  digitalWrite(shutPinUm, LOW);
  //=====ESPERAR-PARA-GARANTIR-VERACIDADE-DO-PINO=====//
  delay(50);

  //=====DEFINIR-O-MODO-DE-PINO-DO-XSHUT=====//
  pinMode(shutPinDois, OUTPUT);
  //=====ENVIAR-SINAL-PARA-O-PINO-XSHUT-ASSIM-DESLIGANDO-O-SENSOR-ATE-QUE-ELE-NAO-RECEBA-MAIS-SINAL-NESTA-PORTA=====//
  digitalWrite(shutPinDois, LOW);
  //=====ESPERAR-PARA-GARANTIR-VERACIDADE-DO-PINO=====//
  delay(50);

  //=====DEFINIR-O-MODO-DE-PINO-DO-XSHUT=====//
  pinMode(shutPinTres, OUTPUT);
  //=====ENVIAR-SINAL-PARA-O-PINO-XSHUT-ASSIM-DESLIGANDO-O-SENSOR-ATE-QUE-ELE-NAO-RECEBA-MAIS-SINAL-NESTA-PORTA=====//
  digitalWrite(shutPinTres, LOW);
  //=====ESPERAR-PARA-GARANTIR-VERACIDADE-DO-PINO=====//
  delay(50);

  //=====AGORA-QUE-HA-APENAS-UM-SENSOR-DE-MESMO-ENDERECO-CONECTADO-E-LIGADO-INICIALIZAR-O-PRIMEIRO-SENSOR=====//
  sensorquatro.init();
  //=====DEFINIR-CONFIGURACOES-PADRAO=====//
  sensorquatro.configureDefault();
  //=====DEFINIR-TIMEOUT=====//
  sensorquatro.setTimeout(500);
  //=====MUDAR-O-ENDERECO-DO-SENSOR-PARA-0X30-ASSIM-ACABANDO-COM-O-CONFLITO-DE-ENDERECOS=====//
  sensorquatro.setAddress(0x30);

  //=====AGORA-QUE-HA-APENAS-ENDERECOS-ORIGINAIS-CONECTADOS-LIGAR-O-SEGUNDO-SENSOR-NOVAMENTE=====//
  digitalWrite(shutPinTres, HIGH);
  //=====ESPERAR-PARA-POSSUIR-VERACIDADE-DO-PINO=====//
  delay(50);

  //=====INICIALIZAR-O-SEGUNDO-SENSOR=====//
  sensortres.init();
  //=====DEFINIR-CONFIGURACOES-PADRAO=====//
  sensortres.configureDefault();
  //=====DEFINIR-TIMEOUT=====//
  sensortres.setTimeout(500);
  //=====MUDAR-O-ENDERECO-DO-SENSOR-PARA-0X31-ASSIM-ACABANDO-COM-O-CONFLITO-DE-ENDERECOS=====//
  sensortres.setAddress(0x31);

  //=====AGORA-QUE-HA-APENAS-ENDERECOS-ORIGINAIS-CONECTADOS-LIGAR-O-SEGUNDO-SENSOR-NOVAMENTE=====//
  digitalWrite(shutPinDois, HIGH);
  //=====ESPERAR-PARA-POSSUIR-VERACIDADE-DO-PINO=====//
  delay(50);

  //=====INICIALIZAR-O-SEGUNDO-SENSOR=====//
  sensordois.init();
  //=====DEFINIR-CONFIGURACOES-PADRAO=====//
  sensordois.configureDefault();
  //=====DEFINIR-TIMEOUT=====//
  sensordois.setTimeout(500);
  //=====MUDAR-O-ENDERECO-DO-SENSOR-PARA-0X32-ASSIM-ACABANDO-COM-O-CONFLITO-DE-ENDERECOS=====//
  sensordois.setAddress(0x32);

  //=====INICIALIZAR-O-SEGUNDO-SENSOR=====//
  sensorum.init();
  //=====DEFINIR-CONFIGURACOES-PADRAO=====//
  sensorum.configureDefault();
  //=====DEFINIR-TIMEOUT=====//
  sensorum.setTimeout(500);
  //=====NAO-E-NECESSARIO-MUDAR-O-ENDERECO-DO-PRIMEIRO-SENSOR-POIS-HA-APENAS-UM-COM-O-ENDERECO-0X29=====//
}

void loop() {

  //// PARTE DO CODIGO ESCRITO PELA GABRIELA ////

  digitalWrite(ENABLE_MOTOR_DIREITA, HIGH);
  digitalWrite(ENABLE_MOTOR_ESQUERDA, HIGH);

  digitalWrite(DIRECAO_HORARIO_DIREITA, HIGH);
  digitalWrite(DIRECAO_ANTIHORARIO_DIREITA, LOW);
  analogWrite(PWM_MOTOR_DIREITA, 150);

  digitalWrite(DIRECAO_HORAIO_ESQUERDA, LOW);
  digitalWrite(DIRECAO_ANTIHORARIO_ESQUERDA, HIGH);
  analogWrite(PWM_MOTOR_ESQUERDA, 150);

  delay(2000);

  digitalWrite(DIRECAO_HORARIO_DIREITA, LOW);
  digitalWrite(DIRECAO_ANTIHORARIO_DIREITA, LOW);
  analogWrite(PWM_MOTOR_DIREITA, 0);

  digitalWrite(DIRECAO_HORAIO_ESQUERDA, LOW);
  digitalWrite(DIRECAO_ANTIHORARIO_ESQUERDA, LOW);
  analogWrite(PWM_MOTOR_ESQUERDA, 0);

  delay(3000);

  //// PARTE DO CODIGO ESCRITO PELA GABRIELA ////
  
}

//=====FUNÇÃO-PARA-LER-SENSORES-INFRAVERMELHOS-E-ENTREGAR-STRING=====//
void LerSensores(unsigned int limiteFrente, unsigned int limiteLados)
{
  //=====VARIAVEIS-UTILIZADAS-PARA-LER-SENSORES=====//
  int sensorUm = sensorum.readRangeSingleMillimeters(); //SENSOR DIREITA
  int sensorDois = sensordois.readRangeSingleMillimeters(); //SENSOR CENTRAL DIREITA
  int sensorTres = sensortres.readRangeSingleMillimeters(); //SENSOR CENTRAL ESQUERDA
  int sensorQuatro = sensorquatro.readRangeSingleMillimeters(); //SENSOR ESQUERDA

  if ( (sensorDois <= limiteFrente) && (sensorTres <= limiteFrente) )
  {
    if ( sensorUm > limiteLados)
    {
      return "DIREITA";
    }
    else if (sensorQuatro > limiteLados)
    {
      return "ESQUERDA";
    }
    else
    {
      return "ATRAS";
    }
  }
  else
  {
    return "FRENTE";
  }
}