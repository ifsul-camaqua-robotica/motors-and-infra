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
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//=====DEFINICAO-DOS-SENSORES-INFRAVERMELHOS=====//
VL6180X sensorum; //SENSOR DIREITA
VL6180X sensordois; //SENSOR CENTRAL DIREITA
VL6180X sensortres; //SENSOR CENTRAL ESQUERDA
VL6180X sensorquatro; //SENSOR ESQUERDA

//=====DEFINIR-O-PINO-XSHUT-DO-SENSOR-INFRAVERMELHO=====//
const int shutPinUm = 22; //SENSOR DIREITA
const int shutPinDois = 23; //SENSOR CENTRAL DIREITA
const int shutPinTres = 24; //SENSOR CENTRAL ESQUERDA
const int shutPinQuatro = 25; //SENSOR ESQUERDA

//// GABRIELA ////
//// TAI4V /////

//// PARTE DO CODIGO ESCRITO PELA GABRIELA ////

//// PWM MOTORES ////
#define PWM_MOTOR_DIREITA A2
#define PWM_MOTOR_ESQUERDA A3

//// PINOS DIREÇÕES MOTOR DIREITA //// 
#define DIRECAO_HORARIO_DIREITA 10
#define DIRECAO_ANTIHORARIO_DIREITA 11

//// PINOS DEIREÇÕES MOTOR ESQUERDA ////
#define DIRECAO_HORAIO_ESQUERDA 12
#define DIRECAO_ANTIHORARIO_ESQUERDA 13

//// PARTE DO CODIGO ESCRITO PELA GABRIELA ////

void setup() 
{

  //// PARTE DO CODIGO ESCRITO PELA GABRIELA ////

  pinMode(PWM_MOTOR_DIREITA, OUTPUT);
  pinMode(PWM_MOTOR_ESQUERDA, OUTPUT);

  pinMode(DIRECAO_HORARIO_DIREITA, OUTPUT);
  pinMode(DIRECAO_ANTIHORARIO_DIREITA, OUTPUT);

  pinMode(DIRECAO_HORAIO_ESQUERDA, OUTPUT);
  pinMode(DIRECAO_ANTIHORARIO_ESQUERDA, OUTPUT);

  digitalWrite(PWM_MOTOR_ESQUERDA, HIGH);
  digitalWrite(PWM_MOTOR_DIREITA, HIGH);
  
  //// PARTE DO CODIGO ESCRITO PELA GABRIELA ////

  //=====INICIALIZAR-SERIAL=====//
  Serial.begin(9600);

  //=====INICIALIZAR-WIRE=====//
  Wire.begin();

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

  sensorquatro.init(); //SENSOR ESQUERDA

  //=====DEFINIR-CONFIGURACOES-PADRAO=====//
  sensorquatro.configureDefault();
  //=====DEFINIR-TIMEOUT=====//
  sensorquatro.setTimeout(500);
  //=====MUDAR-O-ENDERECO-DO-SENSOR-PARA-0X30-ASSIM-ACABANDO-COM-O-CONFLITO-DE-ENDERECOS=====//
  sensorquatro.setAddress(0x30);

  //=====AGORA-QUE-HA-APENAS-ENDERECOS-ORIGINAIS-CONECTADOS-LIGAR-O-TERCEIRO-SENSOR-NOVAMENTE=====//

  digitalWrite(shutPinTres, HIGH); //SENSOR CENTRAL ESQUERDA

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

  digitalWrite(shutPinDois, HIGH); //SENSOR CENTRAL DIREITA

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

  sensorum.setScaling(2);  // Escala 2x para maior alcance 
  sensordois.setScaling(2);  // Escala 2x para maior alcance 
  sensortres.setScaling(2);  // Escala 2x para maior alcance 
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

void loop() 
{
  //=====LER-VALOR-DA-DISTANCIA-DOS-INFRAVERMELHOS=====//
  //=====O-LIMITE-DOS-SENSORES-INFRAVERMELHOS-E-DE-20CM=====//
  int dist1 = sensorquatro.readRangeSingleMillimeters();
  int dist2 = sensordois.readRangeSingleMillimeters();
  int dist3 = sensortres.readRangeSingleMillimeters();
  int dist4 = sensorum.readRangeSingleMillimeters();

  //=====IMPRIMIR-O-VALOR-DA-DISTANCIA-DOS-SENSORES-NO-SERIAL-MONITOR=====//
  Serial.print("Distancia Sensor 1: ");
  Serial.println(dist1);
  Serial.print("Distancia Sensor 2: ");
  Serial.println(dist2);
  Serial.print("Distancia Sensor 3: ");
  Serial.println(dist3);
  Serial.print("Distancia Sensor 4: ");
  Serial.println(dist4);

  String direcao = LerSensores();
  Serial.print("Direção - ");
  Serial.println(direcao);

  //=====IMPRIMIR-O-VALOR-DA-DISTANCIA-DOS-SENSORES-NA-TELA-OLED=====//
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Esquerdo - ");
  display.setCursor(110, 0);
  display.println(dist1);

  display.setCursor(0, 10);
  display.println("Central Esquerdo - ");
  display.setCursor(110, 10);
  display.println(dist2);

  display.setCursor(0, 20);
  display.println("Central Direito - ");
  display.setCursor(110, 20);
  display.println(dist3);

  display.setCursor(0, 30);
  display.println("Direito - ");
  display.setCursor(110, 30);
  display.println(dist4);

  display.setCursor(0, 40);
  display.println("Direcao - ");
  display.setCursor(70, 40);
  display.println(direcao);

  display.display();
  display.clearDisplay();
}

//=====FUNÇÃO-PARA-LER-SENSORES-INFRAVERMELHOS-E-ENTREGAR-STRING=====//
String LerSensores()
{
  int limiteFrente = 60;
  int limiteLados = 60;

  //=====VARIAVEIS-UTILIZADAS-PARA-LER-SENSORES=====//
  int sensorUm = sensorquatro.readRangeSingleMillimeters(); //SENSOR ESQUERDA
  int sensorDois = sensordois.readRangeSingleMillimeters(); //SENSOR CENTRAL ESQUERDA
  int sensorTres = sensortres.readRangeSingleMillimeters(); //SENSOR CENTRAL DIREITA
  int sensorQuatro = sensorum.readRangeSingleMillimeters(); //SENSOR DIREITA

  //=====VERIFICAÇÃO-PARA-ENTREGAR-VALOR-CORRESPONDENTE-A-AÇÃO=====//
  if ( (sensorDois <= limiteFrente) && (sensorTres <= limiteFrente) )
  {
    if ( sensorUm > limiteLados)
    {
      return "ESQUERDA";
    }
    else if (sensorQuatro > limiteLados)
    {
      return "DIREITA";
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
