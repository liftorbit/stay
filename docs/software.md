# Documentação do software do computador de bordo do foguete STAY

Esta documentação explica em detalhes o funcionamento do código que será utilizado no computador de bordo do foguete.

## Etapas de lançamento

As etapas de lançamento são as ações que o foguete realiza antes do lançamento, durante o voo e pouso. Essas etapas incluem verificações, autorizações, e coleta de dados. Os dados podem ser coletados apenas a partir da etapa **LAUNCH.**

1. `SETUP`: Inicialização do sistema de log, sensores e comunicação.
2. `AUTHORIZATION`: Aguarda a autorização do lançamento do foguete.
3. `COUNTDOWN`: Quando autorizado, uma contagem de 10 segundos será iniciada internamente, nesse período, o Controle Vetorial de Empuxo é ativado. A contagem **pode ser interrompida** pela comunicação com o comando `SLC` (Stop Launch Countdown).
4. `LAUNCH`: Inicialização do motor, controle vetorial de empuxo e telemetria.
5. `MECO`: Desligamento do Motor Principal (Main Engine Cut Off).

### Etapa `LAUNCH`

Todas as etapas são simples até a decolagem, onde é requerido um bom gerenciamento de tempo e de ordem na coleta de dados e controle do foguete. Nesta etapa, 03 coisas devem acontecer:

- Telemetria de dados
  - Localização via GPS (começa a ser enviado após o desligamento do motor principal)
  - Status do motor
  - Aceleração
  - Altitude
  - Pressão
- Registro de ações realizadas pelo foguete (logging)
- Manipular o controle vetorial de empuxo enquanto o motor está ligado

A telemetria de dados e a manipulação do controle vetorial de empuxo devem ocorrer ao mesmo tempo, permitindo que os dois sistemas funcionem sem interrupções. Para isso, a seguinte ordem de ações deve ser executada:

1. Após a ignição do motor, uma thread é criada para enviar dados 10 vezes por segundos de telemetria do foguete e a thread principal é utilizada para manipular o controle vetorial de empuxo.
2. Após o desligamento do motor principal, o controle vetorial de empuxo é desligado e a telemetria passa a trabalhar na thread principal enviando dados (incluindo localização) 2 vezes por segundo.