# ROBOCUP 2025
# CÓDIGO PARA MOTORES E INFRAVERMELHOS

# DESCRIÇÃO DO CÓDIGO:
- 

# BIBLIOTECAS:

- Wire.h -> I2C
- VL6180X.h -> SENSORES INFRAVERMELHO

# PINAGEM:

# MOTOR DIREITO:

- ENABLE MOTOR DIREITA -> 
- PWM MOTOR DIREITA -> 
- DIRECAO HORARIO DIREITA -> 
- DIRECAO ANTIHORARIO DIREITA -> 
  
# MOTOR ESQUERDO:
  
- ENABLE MOTOR ESQUERDA -> 
- PWM MOTOR ESQUERDA -> 
- DIRECAO HORAIO ESQUERDA -> 
- DIRECAO ANTIHORARIO ESQUERDA -> 

# INFRAVERMELHOS:
  
- PINOS DE COMUNICAÇÃO INFRAVERMELHOS -> 

- PINO SHUT SENSOR UM ->  (SENSOR DA DIREITA)
- PINO SHUT SENSOR DOIS ->  (SENSOR CENTRAL DA DIREITA)
- PINO SHUT SENSOR TRES ->  (SENSOR CENTRAL DA ESQUERDA)
- PINO SHUT SENSOR QUATRO ->  (SENSOR DA ESQUERDA)

# INICIALIZAÇÃO SENSORES INFRAVERMELHO:

- Na inicialização dos sensores infravermelhos, para que, não possua conflito entre os sensores, pois todos são de mesmo endereço, utilizamos do ultimo pino que há em sua composição, o "SHUT"
- Ao utilizar o "SHUT" o sensor fica indisponível para acesso e já não envia ou recebe sinais do I2C, permitindo assim que ao um sensor estar desligado, fazer alterações no sensor que permanece ligado apenas
- E por isso, nós desligamos todos os sensores com o pino SHUT, menos um, e após isso trocamos o endereço via código do sensor que permanece ligado, e após isso repetimos o processo, ligando cada sensor gradativamente e trocando seus endereços
- Após a troca de endereço de cada sensor, também é necessário fazer a inicialização dele, definindo a inicialização, configuração e o tempo de delay entre respostas

# CLASSES:


# LINGUAGEM:
<img src="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/icons/arduino/arduino-original.svg" width="115" height="115"/>

# AUTORES:

[<img loading="lazy" src="https://avatars.githubusercontent.com/u/165217446?v=4" width=115><br><sub>Gabriela Hoppe Garcia</sub>](https://github.com/GabrielaGarcia03)

[<img loading="lazy" src="https://avatars.githubusercontent.com/u/110566021?v=4" width=115><br><sub>Vítor Maziero Oliveira</sub>](https://github.com/vitor-m-o)

  
