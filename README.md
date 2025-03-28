# ROBOCUP 2025
# CÓDIGO PARA MOTORES E INFRAVERMELHOS

# DESCRIÇÃO DO CÓDIGO:

- O código atualmente apenas consegue fazer o carro se movimentar, não houve tempo para testes da parte dos infravermelhos

# FUNÇÃO "LerSensores":

INPUTS:
- Limite Frente -> Limite de distancia que o robo pode chegar de uma parede em sua frente
- Limite Lados -> Limite de distancia que o robo pode chegar de uma parede em suas laterais

PROCESSAMENTO:
- Ler valores dos sensores infravermelhos e comparar seus valores com os limites entregados nos argumentos da função

OUTPUTS:
- Valor string de acordo com a função necessária, seja ela "FRENTE", "ESQUERDA", "DIREITA" ou "ATRAS"

# INICIALIZAÇÂO SENSORES INFRAVERMELHO:

- está no código e teoricamente funcionando, irei explicar escrito aqui em breve.
  
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

# LINGUAGEM:
<img src="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/icons/arduino/arduino-original.svg" width="115" height="115"/>

# AUTORES:

[<img loading="lazy" src="https://avatars.githubusercontent.com/u/???v=4" width=115><br><sub>Gabriela Hoppe Garcia</sub>](https://github.com/gabriela???)

[<img loading="lazy" src="https://avatars.githubusercontent.com/u/110566021?v=4" width=115><br><sub>Vítor Maziero Oliveira</sub>](https://github.com/vitor-m-o)

  
