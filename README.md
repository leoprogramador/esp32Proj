![image](https://github.com/user-attachments/assets/75ce6bbd-a8fe-4f2e-b90a-0f47021564ec)

## 1. Introdução

O presente relatório descreve o desenvolvimento do Dispositivo Educativo Interativo para Higienização das Mãos, um projeto prático realizado no âmbito da unidade curricular de Project Factory.

O objetivo principal do projeto é criar um dispositivo interativo capaz de guiar e incentivar a correta higienização das mãos, através de feedback sensorial, visual e sonoro. 

O protótipo desenvolvido o Projeto do Pato foi concebido para ser autónomo e portátil, eliminando a dependência de dispositivos externos como smartphones.

O sistema utiliza um sensor de distância ultrassónico (HC-SR04) para detetar a aproximação do utilizador, desencadeando uma sequência de interação guiada. 

O feedback é fornecido através de um ecrã LCD, que apresenta informação visual, e de um módulo de áudio DFPlayer Mini com buzzer, que emite instruções sonoras. 

O utilizador pode ainda ajustar o volume através de um potenciómetro. 

Toda a lógica é coordenada pelo microcontrolador ESP32, alimentado por bateria para garantir portabilidade.

## 2. Funcionalidades 
O sistema desenvolvido apresenta um conjunto de funcionalidades que permitem uma interação intuitiva entre o utilizador e o dispositivo, promovendo o correto processo de higienização das mãos.

As principais funcionalidades implementadas são:

● Deteção de Proximidade:
O sistema utiliza um sensor ultrassónico (HC-SR04) para detetar a aproximação da mão do utilizador. Esta deteção funciona como evento de ativação, iniciando automaticamente o ciclo de interação sem necessidade de contacto físico.

● Interação Automática:
Após a deteção do utilizador, o sistema inicia uma sequência de instruções guiadas, orientando o utilizador ao longo das diferentes etapas do processo de higienização.

● Feedback Visual:
Através de um display LCD, o sistema apresenta informações relevantes, como estados do sistema, instruções ou mensagens de apoio ao utilizador.

● Feedback Sonoro:
O módulo DFPlayer Mini, em conjunto com o speaker, permite a reprodução de instruções áudio, tornando a interação mais clara e acessível.

● Controlo de Volume:
O utilizador pode ajustar o volume do sistema através de um potenciómetro, permitindo adaptar o dispositivo a diferentes ambientes.

● Funcionamento Autónomo:
O dispositivo opera de forma independente, sendo alimentado por bateria, o que garante portabilidade e flexibilidade de utilização.

## 3. Arquitetura 

3.1 Arquitetura de Hardware

O sistema desenvolvido é centrado no microcontrolador ESP32, responsável pela coordenação de todos os componentes do dispositivo.

A arquitetura segue um modelo de aquisição de dados, processamento e atuação, permitindo uma resposta em tempo real à interação do utilizador.

O sensor ultrassónico HC-SR04 constitui o principal elemento de entrada do sistema, sendo responsável pela deteção da proximidade do utilizador.

Este sensor opera através da emissão de ondas ultrassónicas e medição do tempo de retorno do eco, permitindo calcular a distância ao objeto detetado.

Os dados provenientes do sensor são processados pelo ESP32, que executa a lógica de controlo e decide as ações a realizar com base na distância medida. 
Quando é detetada a presença de um utilizador dentro de um determinado intervalo, o sistema inicia automaticamente a sequência de interação.

A interface de saída é composta por dois subsistemas principais: visual e sonoro. 

A componente visual é assegurada por um display LCD, responsável pela apresentação de mensagens, instruções e estados do sistema. 

A componente sonora é implementada através do módulo DFPlayer Mini, que permite a reprodução de ficheiros de áudio, complementado por um SPEAKER para emissão de alertas simples.

Adicionalmente, o sistema inclui um potenciómetro que funciona como interface de entrada do utilizador, permitindo o ajuste dinâmico do volume do áudio. 

Este componente é lido pelo ESP32 através de uma entrada analógica, sendo o valor utilizado para controlar o nível de saída sonora.

A alimentação do sistema é garantida por uma bateria, permitindo o funcionamento autónomo e portátil do dispositivo. 

Esta abordagem elimina a necessidade de ligação contínua à rede elétrica, aumentando a flexibilidade de utilização.

## 3.2 Arquitetura de Software

O software do sistema foi desenvolvido em linguagem C++ no ambiente Arduino, adotando uma estrutura baseada em ciclos de execução contínua (loop), típica de sistemas embebidos.

A lógica de funcionamento assenta na leitura periódica dos sensores e na tomada de decisão com base em condições pré-definidas. 

Quando o sensor ultrassónico deteta a presença de um utilizador, o sistema transita para um estado ativo, iniciando a sequência de instruções visuais e sonoras.

O controlo do sistema é realizado de forma sequencial, garantindo que as diferentes etapas da interação ocorrem de forma ordenada.

A leitura do potenciómetro é efetuada continuamente, permitindo ajustar o volume em tempo real sem interromper o funcionamento do sistema.
 
