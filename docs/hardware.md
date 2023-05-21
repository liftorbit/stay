# Documentação de hardware do foguete STAY

Esta documentação explica em detalhes o funcionamento e as conexões de sensores e servo motores do foguete. Os componentes utilizados são:

- ESP32 (38 pinos)
- BMP280 (barômetro)
- BMI180 (acelerômetro/giroscópio)
- HC-12 SI4463 (transmissão wireless)
- Módulo cartão MicroSD
- Sensor infravermelho
- Booster DC-DC (MT3608)
- 02 Servos motores 9g

Atualmente, todos esses componentes resulta no valor de aproximadamente R$ 163 em sites estrangeiros.

Além de sensores e servos motores, o pino `G26` do ESP32 é reservado para realizar a **ignição do motor principal**. Já o pino `G25` irá alimentar um LED para indicação dos status do computador.

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