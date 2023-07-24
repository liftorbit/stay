# Documentação de hardware do foguete STAY

Esta documentação explica em detalhes o funcionamento e as conexões de sensores e servo motores do foguete. Os componentes utilizados são:

- ESP32 (38 pinos)
- BMP280 (barômetro)
- BMI180 (acelerômetro/giroscópio)
- HC-12 SI4463 (transmissão wireless)
- NEO6M (módulo GPS)
- Módulo cartão MicroSD
- Sensor infravermelho
- Booster DC-DC (MT3608)
- 02 Servos motores 9g
- Transceptor RF (HC12)

Atualmente, todos esses componentes resulta no valor de aproximadamente R$ 163 em sites estrangeiros.

Além de sensores e servos motores, o pino `G26` do ESP32 é reservado para realizar a **ignição do motor principal**. Já o pino `G25` irá alimentar um LED para indicação dos status do computador. Todos os componentes do projeto consomem, se usados ao máximo, 504.5 mA. Uma bateria de 9v com o dobro do necessário (1000mAh) é o suficiente para suprir todos os sistemas do foguete por mais ou menos 2 horas.

## Manual de conexão dos componentes

Para que o manual funcione corretamente, todos os componentes devem ser iguais aos listados na lista, evitando problemas de comunicação ou até danos ao componente.

### BMP280 (barômetro)

O barômetro realiza medições de pressão, altitude e temperatura. O protocolo de comunicação utilizado é o SPI.

- VCC **->** 3.3v
- SCL **->** G13
- SDA **->** G14
- CSB **->** G27
- SDO **->** G12

### BMI160 (acelerômetro/giroscópio)

O sensor BMI160 é uma unidade de medida inercial que fornece dados sobre orientação do foguete, usado principalmente para a manipulação do controle vetorial de empuxo. O protocolo de comunicação é I2C.

- VCC **->** 3.3v
- SCL **->** G22
- SDA **->** G21

### Módulo cartão MicroSD

O módulo adaptador para cartão MicroSD é necessário para salvar registros importantes do foguete. O módulo utiliza o protocolo SPI.

- VCC **->** 5v
- MISO **->** G19
- MOSI **->** G23
- SCK **->** G18
- CS **->** G5

### Servos motores 9g

Os servos motores são responsáveis por controlar o empuxo vetorial do foguete (TVC). Para isso, dois servos motores são utilizados.

- VCC **->** 5v (alimentação externa)
- GND **->** GND externo e GND ESP32
- Servo 01 (eixo X) **->** G2
- Servo 02 (eixo Y) **->** G32

### Sensor infravermelho

O sensor infravermelho é responsável por informar ao computador de bordo se o motor está ligado ou desligado.

- VCC **->** 5v
- D0 **->** G35

### GPS (neo-6m)

O módulo de GPS NEO6M fornece dados da localização do foguete após o desligamento do motor principal. O protocolo de comunicação utilizado é UART.

- VCC **->** 5v
- RX  **->** G15 ESP
- TX  **->** G04 ESP

### Módulo RF (HC12)

O módulo de Rádio Frequência HC12 transmite dados de telemetria do foguete durante o vôo, além de receber comandos para autorizações. O protocolo de comunicação utilizado é UART.

- VCC **->** 5v
- RX  **->** G17 ESP (UART 2 TX)
- TX  **->** G16 ESP (UART 2 RX)