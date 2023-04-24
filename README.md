# STAY Beginner

**STAY Beginner** é um foguete de propulsão com combustível sólido desenvolvido pela [Firlast](https://github.com/firlast) feito para dar o passo inicial no desenvolvimento de outros projetos. O STAY B conta com um computador de bordo responsável por coletar dados de diversos sensores e controlar o TVC (controle vetorial de empuxo).

## Missão

A missão do **STAY Beginner** é voar para testar o *Controle Vetorial de Empuxo* e coletar dados importantes durante o voo, utilizando diversos sensores localizados no foguete. Os dados coletados serão:

1. Aceleração máxima
2. Velocidade máxima
3. Altitude máxima
4. Temperatura máxima
5. Umidade máxima

Esses dados serão utilizados no desenvolvimento de **outros projetos**, melhorando a aerodinâmica e resistência durante o voo do foguete.

## Informações úteis

### Bibliotecas utilizadas

- [BMI160 Sensor](https://github.com/hanyazou/BMI160-Arduino)
- [Adafruit BusIO](https://github.com/adafruit/Adafruit_BusIO)
- [Adafruit BMP280](https://github.com/adafruit/Adafruit_BMP280_Library)
- [Adafruit Sensors](https://github.com/adafruit/Adafruit_Sensor)
- [SD card](https://github.com/espressif/arduino-esp32/tree/master/libraries/SD)
- [ServoESP32](https://github.com/RoboticsBrno/ServoESP32)

> Toda essas bibliotecas foram utilizadas para o módulo Espressif 32.

### Computador de bordo

- Endereço MAC do computador: `24:D7:EB:11:C8:76`
- Placa utilizada: ESP32

## Licença

```
GNU Affero General Public License
Copyright (c) 2023  Firlast
```

Este projeto utiliza a licença [GNU Affero General Public License](https://github.com/firlast/stay-b/blob/master/LICENSE), visite o link para obter mais informações.