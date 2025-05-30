//=====VITOR-MAZIERO-OLIVEIRA=====//
//=====TAI2V=====//
//=====GITHUB-vitor-m-o=====//

//=====CHAMAR-BIBLIOTECAS-UTILIZADAS=====//
#include <Wire.h>
#include <VL6180X.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//=====PARAMETROS-UTILIZADOS-NA-TELA-OLED=====//
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//=====DEFINICAO-DOS-SENSORES-INFRAVERMELHOS=====//
VL6180X sensorum;      //SENSOR DIREITA
VL6180X sensordois;    //SENSOR CENTRAL DIREITA
VL6180X sensortres;    //SENSOR CENTRAL ESQUERDA
VL6180X sensorquatro;  //SENSOR ESQUERDA

//=====DEFINIR-O-PINO-XSHUT-DO-SENSOR-INFRAVERMELHO=====//
const int shutPinUm = 17;     //SENSOR DIREITA
const int shutPinDois = 2;    //SENSOR CENTRAL DIREITA
const int shutPinTres = 16;   //SENSOR CENTRAL ESQUERDA
const int shutPinQuatro = 4;  //SENSOR ESQUERDA

#include <WiFi.h>

// Credenciais do Access Point
const char *ssid = "ROBOCUP";
const char *password = "graxaimbots";

// Criação do servidor
WiFiServer server(80);

//// GABRIELA ////
//// TAI4V /////

//// PARTE DO CODIGO ESCRITO PELA GABRIELA ////

//// PWM MOTORES ////
//#define PWM_MOTOR_DIREITA A2
//#define PWM_MOTOR_ESQUERDA A3

//// PINOS DIREÇÕES MOTOR DIREITA ////
#define DIRECAO_HORARIO_DIREITA 12
#define DIRECAO_ANTIHORARIO_DIREITA 14

//// PINOS DEIREÇÕES MOTOR ESQUERDA ////
#define DIRECAO_HORAIO_ESQUERDA 27
#define DIRECAO_ANTIHORARIO_ESQUERDA 26

//// PARTE DO CODIGO ESCRITO PELA GABRIELA ////

// Pinos do Encoder
#define ENCODER_A_ESQUERDA 36  // Pino de interrupção
#define ENCODER_B_ESQUERDA 39  // Pino comum

#define ENCODER_A_DIREITA 34  // Pino de interrupção
#define ENCODER_B_DIREITA 35  // Pino comum

volatile long encoderPulses_Esquerda = 0;  // Contagem dos pulsos do encoder
volatile long encoderPulses_Direita = 0;
int targetPulses = 1100;  // Quantidade de pulsos alvo (exemplo)

int tempoAnterior;

int RSE, RPE, RSD;

int encoderAnterior_Esquerda = 0, encoderAnterior_Direita = 0;

int velocidade = 80;

int rotacoes = 0;
int rotacaoGraus = 1700;

bool movimento;

int encoderEsquerda;
int encoderDireita;

int rotacao = 4000;

String direcao;

void setup() {
  pinMode(ENCODER_A_ESQUERDA, INPUT_PULLUP);
  pinMode(ENCODER_B_ESQUERDA, INPUT_PULLUP);

  pinMode(ENCODER_A_DIREITA, INPUT_PULLUP);
  pinMode(ENCODER_B_DIREITA, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENCODER_A_ESQUERDA), encoderISR_ESQUERDA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_A_DIREITA), encoderISR_DIREITA, CHANGE);

  //// PARTE DO CODIGO ESCRITO PELA GABRIELA ////

  pinMode(DIRECAO_HORARIO_DIREITA, OUTPUT);
  pinMode(DIRECAO_ANTIHORARIO_DIREITA, OUTPUT);

  pinMode(DIRECAO_HORAIO_ESQUERDA, OUTPUT);
  pinMode(DIRECAO_ANTIHORARIO_ESQUERDA, OUTPUT);

  //// PARTE DO CODIGO ESCRITO PELA GABRIELA ////

  //=====INICIALIZAR-SERIAL=====//
  Serial.begin(115200);

  //=====INICIALIZAR-WIRE=====//
  Wire.begin();

  // Iniciar o Access Point
  WiFi.softAP(ssid, password);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  server.begin();

  millis();

  //=====INICIALIZAÇÃO-DOS-SENSORES-INFRAVERMELHO=====//

  //=====DEFINIR-O-MODO-DE-PINO-DOS-SHUTS=====//
  pinMode(shutPinUm, OUTPUT);
  pinMode(shutPinDois, OUTPUT);
  pinMode(shutPinTres, OUTPUT);

  //=====ENVIAR-SINAL-PARA-OS-PINOS-SHUT-ASSIM-DESLIGANDO-OS-SENSORES=====//
  digitalWrite(shutPinUm, LOW);
  digitalWrite(shutPinDois, LOW);
  digitalWrite(shutPinTres, LOW);
  //=====ESPERAR-PARA-GARANTIR-VERACIDADE-DO-PINO=====//
  delay(50);

  //=====AGORA-QUE-HA-APENAS-UM-SENSOR-DE-MESMO-ENDERECO-CONECTADO-E-LIGADO-INICIALIZAR-O-PRIMEIRO-SENSOR=====//

  sensorquatro.init();  //SENSOR ESQUERDA

  //=====DEFINIR-CONFIGURACOES-PADRAO=====//
  sensorquatro.configureDefault();
  //=====DEFINIR-TIMEOUT=====//
  sensorquatro.setTimeout(500);
  //=====MUDAR-O-ENDERECO-DO-SENSOR-PARA-0X30-ASSIM-ACABANDO-COM-O-CONFLITO-DE-ENDERECOS=====//
  sensorquatro.setAddress(0x30);

  //=====AGORA-QUE-HA-APENAS-ENDERECOS-ORIGINAIS-CONECTADOS-LIGAR-O-TERCEIRO-SENSOR-NOVAMENTE=====//

  digitalWrite(shutPinTres, HIGH);  //SENSOR CENTRAL ESQUERDA

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

  digitalWrite(shutPinDois, HIGH);  //SENSOR CENTRAL DIREITA

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

  //=====AGORA-QUE-HA-APENAS-ENDERECOS-ORIGINAIS-CONECTADOS-LIGAR-O-PRIMEIRO-SENSOR-NOVAMENTE=====//

  digitalWrite(shutPinUm, HIGH);  //SENSOR DIREITA

  //=====ESPERAR-PARA-POSSUIR-VERACIDADE-DO-PINO=====//
  delay(50);

  //=====INICIALIZAR-O-TERCEIRO-SENSOR=====//
  sensorum.init();
  //=====DEFINIR-CONFIGURACOES-PADRAO=====//
  sensorum.configureDefault();
  //=====DEFINIR-TIMEOUT=====//
  sensorum.setTimeout(500);
  //=====NAO-E-NECESSARIO-MUDAR-O-ENDERECO-DO-PRIMEIRO-SENSOR-POIS-HA-APENAS-UM-COM-O-ENDERECO-0X29=====//

  //=====FUNÇÕES-QUE-TALVEZ-PRECISEMOS-PARA-OS-SENSORES=====//

  //sensor.writeReg(VL6180X::SYSRANGE__PART_TO_PART_RANGE_OFFSET, 5);  // Define um offset de 5 mm

  sensorum.setScaling(2);      // Escala 2x para maior alcance
  sensordois.setScaling(2);    // Escala 2x para maior alcance
  sensortres.setScaling(2);    // Escala 2x para maior alcance
  sensorquatro.setScaling(2);  // Escala 2x para maior alcance

  //=====EXIBIR-MENSAGEM-NA-TELA-OLED=====//

  //=====INICIALIZAR-DISPLAY-(APENAS-UMA-UNICA-VEZ-NO-CODIGO)=====//
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  //=====LIMPAR-DISPLAY=====//
  display.clearDisplay();

  //=====DEFINIR-TAMANHO-DO-TEXTO=====//
  display.setTextSize(1);

  //=====DEFINIR-COR-DO-TEXTO=====//
  display.setTextColor(SSD1306_WHITE);

  //=====DEFINIR-CURSOR=====//
  display.setCursor(0, 0);

  //=====ESCREVER-TEXTO=====//
  display.println("IFSUL campus Camaqua");

  //=====COLOCAR-A-INFORMAÇÃO-NA-TELA-DO-DISPLAY=====//
  display.display();

  //=====ESPERAR-2-SEGUNDOS=====//
  delay(2000);

  display.clearDisplay();
}

void loop() {
  //=====LER-VALOR-DA-DISTANCIA-DOS-INFRAVERMELHOS=====//
  //=====O-LIMITE-DOS-SENSORES-INFRAVERMELHOS-E-DE-20CM=====//
  int dist1 = sensorquatro.readRangeSingleMillimeters();
  int dist2 = sensordois.readRangeSingleMillimeters();
  int dist3 = sensortres.readRangeSingleMillimeters();
  int dist4 = sensorum.readRangeSingleMillimeters();

  /*
  //=====IMPRIMIR-O-VALOR-DA-DISTANCIA-DOS-SENSORES-NO-SERIAL-MONITOR=====//
  Serial.print("Distancia Sensor 1: ");
  Serial.println(dist1);
  Serial.print("Distancia Sensor 2: ");
  Serial.println(dist2);
  Serial.print("Distancia Sensor 3: ");
  Serial.println(dist3);
  Serial.print("Distancia Sensor 4: ");
  Serial.println(dist4);
  Serial.print("Direção - ");
  Serial.println(direcao);
  */

  //=====FILTRAR-VALORES-DOS-SENSORES-INFRA-PARA-OBTER-A-DIREÇÃO-QUE-O-CARRO-DEVE-IR=====//
  direcao = LerSensores();

  if (millis() - tempoAnterior >= 1000) {
    RSE = encoderPulses_Esquerda - encoderAnterior_Esquerda;
    if (RSE < 0) {
      RSE = RSE * -1;
    }

    RSD = encoderPulses_Direita - encoderAnterior_Direita;
    if (RSD < 0) {
      RSD = RSD * -1;
    }

    encoderAnterior_Esquerda = encoderPulses_Esquerda;
    encoderAnterior_Direita = encoderPulses_Direita;
    tempoAnterior = millis();
  }

  DesenharTela(dist1, dist2, dist3, dist4, direcao, velocidade, RSE, RSD);

  MoverCarro(velocidade, direcao);

  WiFiClient client = server.available();
  if (client) 
  {
    PararCarro();


    WiFiClient client = server.available();
    if (client) {
      Serial.println("Cliente conectado");
      String request = client.readStringUntil('\r');
      client.flush();

      // Rota AJAX que envia apenas os dados em JSON
      if (request.indexOf("GET /dados") >= 0) {
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: application/json");
        client.println("Access-Control-Allow-Origin: *");
        client.println();
        client.print("{");
        client.print("\"dist1\":" + String(dist1) + ",");
        client.print("\"dist2\":" + String(dist2) + ",");
        client.print("\"dist3\":" + String(dist3) + ",");
        client.print("\"dist4\":" + String(dist4) + ",");
        client.print("\"direcao\":\"" + String(direcao) + "\",");
        client.print("\"velocidade\":" + String(velocidade) + ",");
        client.print("\"encoderPulses_Esquerda\":" + String(encoderPulses_Esquerda) + ",");
        client.print("\"encoderPulses_Direita\":" + String(encoderPulses_Direita) + ",");
        client.print("\"RSE\":" + String(RSE) + ",");
        client.print("\"RSD\":" + String(RSD));
        client.println("}");
      }
      // Página principal com AJAX
      else {
        String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <meta charset="UTF-8">
      <title>CARRO ROBOCUP</title>
      <script>
        function atualizarDados() {
          fetch('/dados')
            .then(response => response.json())
            .then(data => {
              document.getElementById("dist1").innerText = data.dist1;
              document.getElementById("dist2").innerText = data.dist2;
              document.getElementById("dist3").innerText = data.dist3;
              document.getElementById("dist4").innerText = data.dist4;
              document.getElementById("direcao").innerText = data.direcao;
              document.getElementById("velocidade").innerText = data.velocidade;
              document.getElementById("encoderE").innerText = data.encoderPulses_Esquerda;
              document.getElementById("encoderD").innerText = data.encoderPulses_Direita;
              document.getElementById("RSE").innerText = data.RSE;
              document.getElementById("RSD").innerText = data.RSD;
            });
        }

        setInterval(atualizarDados, 100); // Atualiza a cada 100 ms
      </script>
    </head>
    <body>
      <h1>Sensor Infravermelho Esquerda: <span id="dist1">--</span></h1>
      <h1>Sensor Central Esquerda: <span id="dist2">--</span></h1>
      <h1>Sensor Central Direita: <span id="dist3">--</span></h1>
      <h1>Sensor Direita: <span id="dist4">--</span></h1>
      <h1>Direção: <span id="direcao">--</span></h1>
      <h1>Velocidade: <span id="velocidade">--</span></h1>
      <h1>Encoder Esquerda: <span id="encoderE">--</span></h1>
      <h1>Encoder Direita: <span id="encoderD">--</span></h1>
      <h1>Rotações por Segundo Esquerda: <span id="RSE">--</span></h1>
      <h1>Rotações por Segundo Direita: <span id="RSD">--</span></h1>
    </body>
    </html>
    )rawliteral";

        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println();
        client.println(html);
      }

      client.stop();
      Serial.println("Cliente desconectado");
    }
  }
}

void DesenharTela(int sensorEsquerdo, int sensorCentralEsquerdo, int sensorCentralDireito, int sensorDireito, String direcao, int velocidade, int rotacoesSegundoEsquerda, int rotacoesSegundoDireita)
{
  //=====IMPRIMIR-O-VALOR-DA-DISTANCIA-DOS-SENSORES-NA-TELA-OLED=====//
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("E - ");
  display.setCursor(25, 0);
  display.println(sensorEsquerdo);

  display.setCursor(0, 10);
  display.println("CE- ");
  display.setCursor(25, 10);
  display.println(sensorCentralEsquerdo);

  display.setCursor(0, 20);
  display.println("CD- ");
  display.setCursor(25, 20);
  display.println(sensorCentralDireito);

  display.setCursor(0, 30);
  display.println("D - ");
  display.setCursor(25, 30);
  display.println(sensorDireito);

  display.setCursor(0, 40);
  display.println("DR - ");
  display.setCursor(25, 40);
  display.println(direcao);

  display.setCursor(0, 50);
  display.println("VEL - ");
  display.setCursor(35, 50);
  display.println(velocidade);

  display.setCursor(50, 0);
  display.println("ENE - ");
  display.setCursor(85, 0);
  display.println(encoderPulses_Esquerda);

  display.setCursor(50, 10);
  display.println("END - ");
  display.setCursor(85, 10);
  display.println(encoderPulses_Direita);

  //ROTAÇÕES POR SEGUNDO
  display.setCursor(50, 20);
  display.println("RSE - ");
  display.setCursor(85, 20);
  display.println(rotacoesSegundoEsquerda);

  //ROTAÇÕES POR SEGUNDO
  display.setCursor(50, 30);
  display.println("RSD - ");
  display.setCursor(85, 30);
  display.println(rotacoesSegundoDireita);

  //====MOSTRAR-INFORMAÇÂO-NO-DISPLAY=====//
  display.display();
  display.clearDisplay();
}
// Interrupção para contar os pulsos
void encoderISR_ESQUERDA() {
  if (digitalRead(ENCODER_A_ESQUERDA) == digitalRead(ENCODER_B_ESQUERDA)) {
    encoderPulses_Esquerda++;  // Incrementa se girando em um sentido
  } else {
    encoderPulses_Esquerda--;  // Decrementa se girando no outro sentido
  }
}

void encoderISR_DIREITA() {
  if (digitalRead(ENCODER_A_DIREITA) == digitalRead(ENCODER_B_DIREITA)) {
    encoderPulses_Direita++;  // Incrementa se girando em um sentido
  } else {
    encoderPulses_Direita--;  // Decrementa se girando no outro sentido
  }
}

//=====FUNÇÃO-PARA-LER-SENSORES-INFRAVERMELHOS-E-ENTREGAR-STRING=====//
String LerSensores() {
  int limiteFrente = 150;
  int limiteLados = 120;

  //=====VARIAVEIS-UTILIZADAS-PARA-LER-SENSORES=====//
  int sensorUm = sensorquatro.readRangeSingleMillimeters();  //SENSOR ESQUERDA
  int sensorDois = sensordois.readRangeSingleMillimeters();  //SENSOR CENTRAL ESQUERDA
  int sensorTres = sensortres.readRangeSingleMillimeters();  //SENSOR CENTRAL DIREITA
  int sensorQuatro = sensorum.readRangeSingleMillimeters();  //SENSOR DIREITA

  //=====VERIFICAÇÃO-PARA-ENTREGAR-VALOR-CORRESPONDENTE-A-AÇÃO=====//
  if ((sensorDois <= limiteFrente) && (sensorTres <= limiteFrente)) {
    if (sensorUm > limiteLados) {
      return "ESQUERDA";
    } else if (sensorQuatro > limiteLados) {
      return "DIREITA";
    } else {
      return "TRAS";
    }
  } else {
    return "FRENTE";
  }
}


void MoverCarro(int vel, String dir) {
  int contador;

  Serial.print("ENCODER ESQUERDA:  ");
  Serial.println(encoderPulses_Esquerda);
  Serial.print("ENCODER DIREITA:  ");
  Serial.println(encoderPulses_Direita);

  Serial.println(dir);
  if (dir == "FRENTE") {
    rotacoes = encoderEsquerda;
    while (encoderEsquerda - rotacoes <= rotacao) {
      encoderEsquerda = encoderPulses_Esquerda;
      if (encoderEsquerda < 0)
      {
        encoderEsquerda = encoderEsquerda * -1;
      }
      analogWrite(DIRECAO_HORAIO_ESQUERDA, vel);
      analogWrite(DIRECAO_ANTIHORARIO_ESQUERDA, LOW);
      analogWrite(DIRECAO_HORARIO_DIREITA, vel);
      analogWrite(DIRECAO_ANTIHORARIO_DIREITA, LOW);
    }
    PararCarro();
    rotacoes = encoderEsquerda;
  } 
  else if (dir == "ESQUERDA") {
    rotacoes = encoderDireita;
    while (encoderDireita - rotacoes <= rotacao) {
      encoderDireita = encoderPulses_Direita;
      if (encoderDireita < 0)
      {
        encoderDireita = encoderDireita * -1;
      }
      analogWrite(DIRECAO_HORAIO_ESQUERDA, LOW);
      analogWrite(DIRECAO_ANTIHORARIO_ESQUERDA, vel);
      analogWrite(DIRECAO_HORARIO_DIREITA, vel);
      analogWrite(DIRECAO_ANTIHORARIO_DIREITA, LOW);
    } 
    PararCarro();
    rotacoes = encoderDireita;

  } else if (dir == "DIREITA") {
    rotacoes = encoderEsquerda;
    while (encoderEsquerda - rotacoes <= 5700) {
      encoderEsquerda = encoderPulses_Esquerda;
      if (encoderEsquerda < 0)
      {
        encoderEsquerda = encoderEsquerda * -1;
      }
      analogWrite(DIRECAO_HORAIO_ESQUERDA, vel);
      analogWrite(DIRECAO_ANTIHORARIO_ESQUERDA, LOW);
      analogWrite(DIRECAO_HORARIO_DIREITA, LOW);
      analogWrite(DIRECAO_ANTIHORARIO_DIREITA, vel);
    } 
    PararCarro();
    rotacoes = encoderEsquerda;
  } 
  else if (dir == "TRAS") {
    analogWrite(DIRECAO_HORAIO_ESQUERDA, LOW);
    analogWrite(DIRECAO_ANTIHORARIO_ESQUERDA, vel);
    analogWrite(DIRECAO_HORARIO_DIREITA, LOW);
    analogWrite(DIRECAO_ANTIHORARIO_DIREITA, vel);
  } else if (dir == "PARE") {
    PararCarro();
  }
}

void PararCarro() {
  while (millis() - tempoAnterior <= 1000) {
    analogWrite(DIRECAO_HORAIO_ESQUERDA, LOW);
    analogWrite(DIRECAO_ANTIHORARIO_ESQUERDA, LOW);
    analogWrite(DIRECAO_HORARIO_DIREITA, LOW);
    analogWrite(DIRECAO_ANTIHORARIO_DIREITA, LOW);

    direcao = LerSensores();
  }
  tempoAnterior = millis();
  movimento = true;
}
