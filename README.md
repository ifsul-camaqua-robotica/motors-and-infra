# ROBOCUP 2025
# CÓDIGO PARA MOTORES E INFRAVERMELHOS

# DESCRIÇÃO DO CÓDIGO:

- O código atualmente apenas consegue fazer o carro se movimentar, não houve tempo para testes da parte dos infravermelhos

# BIBLIOTECAS:

- Wire.h -> I2C
- VL6180X.h -> CONFIGURAÇÃO SENSORES INFRAVERMELHO

# PINAGEM:

# MOTOR DIREITO:

- ENABLE MOTOR DIREITA -> A0
- PWM MOTOR DIREITA -> 5
- DIRECAO HORARIO DIREITA -> 6
- DIRECAO ANTIHORARIO DIREITA -> 7
  
# MOTOR ESQUERDO:
  
- ENABLE MOTOR ESQUERDA -> A1
- PWM MOTOR ESQUERDA -> 8
- DIRECAO HORAIO ESQUERDA -> 9
- DIRECAO ANTIHORARIO ESQUERDA -> 10

# INFRAVERMELHOS:
  
- PINOS DE COMUNICAÇÃO INFRAVERMELHOS -> SDA E SCL

- PINO SHUT SENSOR UM -> 22 (SENSOR DA DIREITA)
- PINO SHUT SENSOR DOIS -> 23 (SENSOR CENTRAL DA DIREITA)
- PINO SHUT SENSOR TRES -> 24 (SENSOR CENTRAL DA ESQUERDA)
- PINO SHUT SENSOR QUATRO -> 25 (SENSOR DA ESQUERDA)

# INICIALIZAÇÃO SENSORES INFRAVERMELHO:

- Na inicialização dos sensores infravermelhos, para que, não possua conflito entre os sensores, pois todos são de mesmo endereço, utilizamos do ultimo pino que há em sua composição, o "SHUT"
- Ao utilizar o "SHUT" o sensor fica indisponível para acesso e já não envia ou recebe sinais do I2C, permitindo assim que ao um sensor estar desligado, fazer alterações no sensor que permanece ligado apenas
- E por isso, nós desligamos todos os sensores com o pino SHUT, menos um, e após isso trocamos o endereço via código do sensor que permanece ligado, e após isso repetimos o processo, ligando cada sensor gradativamente e trocando seus endereços
- Após a troca de endereço de cada sensor, também é necessário fazer a inicialização dele, definindo a inicialização, configuração e o tempo de delay entre respostas

# FUNÇÕES DA BIBLIOTECA "VL6180X.h"

# FUNÇÃO ".init()":

- Função para inicialização do sensor infravermelho

# FUNÇÃO ".configureDefault()":

- Função para definir configurações do sensor como padrão, não necessário mudar

# FUNÇÃO ".setTimeout(COLOCAR-AQUI-O-TEMPO-DE-RESPOSTA)":

- Função para definir o tempo de atraso entre cada resposta do sensor infravermelho, colocando o tempo em milisegundos dentro dos parenteses

# FUNÇÃO ".setAddress(COLOCAR-AQUI-ENDEREÇO)":

- Função para definir/trocar o endereço do sensor citado, com a função permitindo escolher o endereço e coloca-lo entre os parenteses

# FUNÇÃO ".setScaling(COLOCAR-AQUI-A-ESCALA)":

- Função para definir escala do sensor infravermelho, permitindo aumentar ou diminuir a escala e assim mudando o seu campo de visão com o valor da escala dentro dos parenteses

# FUNÇÃO ".readRangeSingleMillimeters()":

- Função para ler o valor recebido nos infravermelhos em milimetros

# FUNÇÔES CRIADAS NO CÓDIGO:

# FUNÇÃO "LerSensores(LIMITE-FRENTE, LIMITE-LADOS)":

INPUTS:
- Limite Frente -> Limite de distancia que o robo pode chegar de uma parede em sua frente
- Limite Lados -> Limite de distancia que o robo pode chegar de uma parede em suas laterais

PROCESSAMENTO:
- Ler valores dos sensores infravermelhos e comparar seus valores com os limites entregados nos argumentos da função

OUTPUTS:
- Valor string de acordo com o valor recebido nos sensores e verificação de qual ação é necessária para navegar o labirinto, seja ela "FRENTE", "ESQUERDA", "DIREITA" ou "ATRAS"

# LINGUAGEM:
<img src="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/icons/arduino/arduino-original.svg" width="115" height="115"/>

# AUTORES:

[<img loading="lazy" src="https://avatars.githubusercontent.com/u/165217446?v=4" width=115><br><sub>Gabriela Hoppe Garcia</sub>](https://github.com/GabrielaGarcia03)

[<img loading="lazy" src="https://avatars.githubusercontent.com/u/110566021?v=4" width=115><br><sub>Vítor Maziero Oliveira</sub>](https://github.com/vitor-m-o)

  
