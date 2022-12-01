# Contador de pulsos com conectividade LoRaWAN


## Introdução 

Este é o repositório de um projeto de um contador de pulsos com conectividade LoRaWAN, usando como principais items de hardware um ESP32-C3 e módulo LoRaWAN SMW SX1262M0.

Este projeto foi desenvolvido para a [placa DevKit ESP32-C3 LoRaWAN](https://devkit-lorawan.douglaszuqueto.com/), cuja imagem pode ser vista abaixo:

![Foto do DevKit](https://1494345701-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2Fk4vm1BAonZb0lJir85Kt%2Fuploads%2FZND8R36Ykkojp0VLa4FY%2FIMG_20221023_140025349_HDR.jpg?alt=media&token=62299eeb-f435-40e6-be26-8786e45f4079 "Foto do DevKit")


## O que este projeto faz?

Este projeto é capaz de:

* Contabilizar até duas entradas pulsadas (borda de descida), localizadas nos GPIOs 3 e 4.
* Enviar periodicamente (a título de exemplo, a cda 15 segundos, tempo este definido em TEMPO_MIN_ENTRE_ENVIOS_LORAWAN_MS) a contabilização dos pulsos. O payload LoRaWAN tem 8 bytes, sendo 4 bytes para cada contador.
* O limite de pulsos contabilizados por entrada é de 4.294.967.296 (valor de 32-bits).
* A cada certo número de envios (definido por NUM_ENVIOS_PARA_GRAVAR_CONTADORES_NVS), é feito o salvamento dos valores dos contadores na partição NVS do ESP32. Desse modo, se o módulo perder a alimentação (após feito um salvamento), o número de pulsos contados será resgatado.
* Neste projeto, utiliza-se o LoRaWAN classe A, modo ABP e sem confirmação de envio.


## Motivação do projeto

Muitos instrumentos de medição de consumo de água, consumo de gás e até mesmo consumo de energia possuem uma saída pulsada, onde cada pulso gerado significa um certo consumo registrado (exemplo: em um hidrômetro deste tipo, há modelos que geram 1 pulso / litro de água consumido). Normalmente, estes pulsos são gerados por reed-switches, sendo portanto um contato seco.

O projeto é capaz de ler tais pulsos (inclusive, fazendo debounce de ambas entradas pulsadas) e enviar, por LoRaWAN, os contadores. Desta forma, no "receptor" de tais dados (plataforma IoT, por exemplo), é possível estabelecer a relação de pulsos / consumo do medidor ao qual o projeto está conectado e calcular, na plataforma iot / nuvem, o consumo total.

Exemplos de equipamentos com saidas pulsadas nos quais este projeto pode ser usado:

* [Saga - hidrômetro Multijato MS](https://www.sagamedicao.com.br/residencialms/)
* [Saga - hidrômetro Unijato US](https://www.sagamedicao.com.br/residencialus/)
* [DAEFLEX - Medidor de gás G0.6](https://daeflex.com.br/produto/medidor-de-gas-g0-6/?gclid=Cj0KCQiA-JacBhC0ARIsAIxybyPE-6tCbLkEUKSEnKOd4kyAlN_isvCH-yrvSlyzxwK6cnFUEfrJ57saAoFHEALw_wcB)


## Como usar o projeto?

Este projeto foi feito utilizando-se o ESP-IDF 4.4, a partir da extensão do ESP-IDF para o VSCode. Portanto, basta instalar a extensão com a versão 4.4 do ESP-IDF para ser capaz de compilar, gravar e modificar este projeto.

Veja como instalar a extensão no seu Visual Studio Code [neste link](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/vscode-setup.html).