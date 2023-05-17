# Documentação do software do computador de bordo do foguete STAY

Esta documentação explica em detalhes o funcionamento do código que será utilizado no computador de bordo do foguete.

## Etapas de lançamento

As etapas de lançamento são as ações que o foguete realiza antes do lançamento, durante o voo e pouso. Essas etapas incluem verificações, autorizações, e coleta de dados. Os dados podem ser coletados apenas a partir da etapa **LAUNCH.**

1. `SETUP`: Inicialização do sistema de log, sensores e comunicação.
2. `AUTHORIZATION`: Aguarda a autorização do lançamento do foguete.
3. `COUNTDOWN`: Quando autorizado, uma contagem de 10 segundos será iniciada internamente, nesse período, o Controle Vetorial de Empuxo é ativado. A contagem **pode ser interrompida** pela comunicação com o comando `SLC` (Stop Launch Countdown).
4. `LAUNCH`: Inicialização do motor. A próxima etapa só é realizada quando for detectada um **aumento na aceleração** do foguete.
5. `MECO`: Desligamento do Motor Principal (Main Engine Cut Off).