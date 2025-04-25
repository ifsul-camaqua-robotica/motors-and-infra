//=====VITOR-MAZIERO-OLIVEIRA=====//
//=====TAI2V=====//
//=====GITHUB-vitor-m-o=====//

//// GABRIELA ////
//// TAI4V /////

//=====CHAMAR-BIBLIOTECAS-UTILIZADAS=====//
//=====BIBLIOTECA-PARA-I2C=====//
#include <Wire.h>
//=====BIBLIOTECA-PARA-WIFI=====//
#include <WiFi.h>
//=====BIBLIOTECA-PARA-SENSORES-INFRAVERMELHOS=====//
#include <VL6180X.h>
//=====BIBLIOTECAS-PARA-TELA-OLED=====//
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Infravermelho.h"

//=====CLASSE-MOTORES=====//
class Motor {
  private:
    //=====PINO-DO-MOTOR=====//
    int pino_horario;
    int pino_antihorario;
    //=====PINO-DO-ENCODER=====//
    int encoder_a;
    int encoder_b;
    //=====VARIAVEL-PARA-CONTROLAR-PULSOS-DO-ENCODER=====//
    int encoder_pulsos;
    //=====VARIAVEL-DE-CONTROLE-PARA-ROTACAO-COMPLETA-DO-MOTOR=====//
    int rotacao_necessaria;

  public:
    Motor(int pino_horarioInput, int pino_antihorarioInput, int encoder_aInput, int encoder_bInput, int rotacao_necessariaInput) {
      //=====PINOS-DO-MOTOR=====//
      pino_horario = pino_horarioInput;
      pino_antihorario = pino_antihorarioInput;
      //=====PINOS-DO-ENCODER=====//
      encoder_a = encoder_aInput;
      encoder_b = encoder_bInput;
      //=====VARIAVEL-DE-CONTROLE-PARA-ROTACAO-COMPLETA=====//
      rotacao_necessaria = rotacao_necessariaInput;
      //=====DEFINIR-FUNCAO-DO-PINO-DO-MOTOR=====//
      pinMode(pino_horario, OUTPUT);
      pinMode(pino_antihorario, OUTPUT);
    }

    void mover_frente() {
      analogWrite(pino_horario, HIGH);
      analogWrite(pino_antihorario, LOW);
    }

    void mover_tras() {
      analogWrite(pino_horario, LOW);
      analogWrite(pino_antihorario, HIGH);
    }

    void parar_motor() {
      analogWrite(pino_horario, LOW);
      analogWrite(pino_antihorario, LOW);
    }

    int ler_encoder() {
      if (digitalRead(encoder_a) == digitalRead(encoder_b)) {
        encoder_pulsos++;  // Incrementa se girando em um sentido
      } else {
        encoder_pulsos--;  // Decrementa se girando no outro sentido
      }
      return encoder_pulsos;
    }
};

//=====PARAMETROS-UTILIZADOS-NA-TELA-OLED=====//
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//=====DEFINICAO-DOS-SENSORES-INFRAVERMELHOS=====//
VL6180X sensorDireita;     //SENSOR DIREITA
VL6180X sensorCentralDireita;    //SENSOR CENTRAL DIREITA
VL6180X sensorCentralEsquerda;   //SENSOR CENTRAL ESQUERDA
VL6180X sensorEsquerda;    //SENSOR ESQUERDA

//=====DEFINIR-O-PINO-XSHUT-DO-SENSOR-INFRAVERMELHO=====//
const int shutPinUm = 17;     //SENSOR DIREITA
const int shutPinDois = 2;    //SENSOR CENTRAL DIREITA
const int shutPinTres = 16;   //SENSOR CENTRAL ESQUERDA
const int shutPinQuatro = 4;  //SENSOR ESQUERDA

// Credenciais do Access Point
const char *ssid = "ROBOCUP";
const char *password = "graxaimbots";

// Criação do servidor
WiFiServer server(80);

//// PINOS DIREÇÕES MOTOR DIREITA ////
#define DIRECAO_HORARIO_DIREITA 12
#define DIRECAO_ANTIHORARIO_DIREITA 14

//// PINOS DEIREÇÕES MOTOR ESQUERDA ////
#define DIRECAO_HORAIO_ESQUERDA 27
#define DIRECAO_ANTIHORARIO_ESQUERDA 26

// Pinos do Encoder
#define ENCODER_A_ESQUERDA 36  // Pino de interrupção
#define ENCODER_B_ESQUERDA 39  // Pino comum

#define ENCODER_A_DIREITA 34  // Pino de interrupção
#define ENCODER_B_DIREITA 35  // Pino comum

//=====VARIAVEIS-PARA-MANIPULAR-ENCODER=====//
volatile long encoderPulses_Esquerda = 0, encoderPulses_Direita = 0;
int encoderEsquerda, encoderDireita;

//=====VARIAVEL-PARA-CONTROLAR-MILLIS=====//
int tempoAnterior;

//=====VARIAVEIS-PARA-CONTROLAR-ROTACOES-POR-SEGUNDO=====//
int RSE, RPE, RSD;

//=====VARIAVEIS-PARA-MANIPULAR-MOVIMENTO-DO-CARRO=====//
int velocidade = 80, rotacoes = 0, rotacaoAlvo = 2000;
String direcao;

void setup() {
  //=====INICIALIZAR-WIRE=====//
  Wire.begin();

}

void loop() {

}
