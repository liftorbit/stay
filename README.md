<h1 align="center">STAY</h1>
<p align="center">Um foguete de propulsão a combustível sólido.<br><i>Passo inicial para foguetes da <a href="https://github.com/liftorbit">Liftorbit</a></i></p>

<p align="center" style="margin-bottom: 15px">
    <img alt="STAY em desenvolvimento" src="https://img.shields.io/static/v1?label=status&message=desenvolvimento&color=green">
    <a href="https://github.com/jaedsonpys/cookiedb/blob/master/LICENSE" style="margin-right: 5px; margin-left: 5px">
    <img alt="Licença GNU AGPL do STAY" src="https://img.shields.io/static/v1?label=licen%C3%A7a&message=GNU%20AGPL&color=red">
    </a>
    <img alt="Previsão de lançamento para 2023" src="https://img.shields.io/static/v1?label=previs%C3%A3o%20de%20lan%C3%A7amento&message=2023&color=red">
</p>

**STAY** é um foguete de propulsão com combustível sólido desenvolvido pela [Liftorbit](https://github.com/liftorbit), criado para dar o passo inicial no desenvolvimento de outros projetos. O foguete utiliza um computador de bordo responsável por coletar dados de diversos sensores e controlar empuxo vetorial.

A missão do **STAY** é voar para testar o *Controle Vetorial de Empuxo* e coletar dados importantes durante o voo, utilizando diversos sensores localizados no foguete. Esses dados serão utilizados no desenvolvimento de **outros projetos**, melhorando a aerodinâmica e resistência durante o voo do foguete.

## Detalhes técnicos

O foguete STAY possui alguns detalhes técnicos relevantes sobre hardware e software. Outras informações sobre desempenho do foguete serão adicionadas após o primeiro lançamento.

- Utilização de ESP32 como computador de bordo
- Possui três sensores:
  - Barômetro
  - Acelerômetro/Giroscópio
  - Sensor de chamas (para detectar de ignição)
- Telemetria em tempo real
- Localização do foguete durante o vôo
- Possui controle vetorial de empuxo (TVC)

Saiba mais sobre os detalhes técnicos do STAY acessando a [documentação do software](https://github.com/liftorbit/stay-rocket/blob/master/docs/software.md) ou a [documentação do hardware](https://github.com/liftorbit/stay-rocket/blob/master/docs/hardware.md).

## Licença

```
GNU Affero General Public License
Copyright (c) 2023  Liftorbit
```

Este projeto utiliza a licença **GNU Affero General Public License**, visite o [arquivo LICENSE](https://github.com/liftorbit/stay-rocket/blob/master/LICENSE) para obter mais informações sobre como você deve utilizar o código-fonte do projeto.