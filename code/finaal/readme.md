# Finale code

Deze map bevat de finale software van het Plan-B-prototype van de snelle line-following robot.

De software is ontwikkeld voor een STM32F103C8T6 en stuurt de lijnsensoren en beide DC-motoren rechtstreeks aan.

## Bestandsstructuur

### Inc

De map `Inc` bevat de headerbestanden:

- `sensors.h` – declaraties voor het uitlezen van de lijnsensoren
- `motors.h` – declaraties voor de aansturing van de motoren
- `eeprom.h` – declaraties voor de 24LC256 EEPROM
- `bluetooth.h` – declaraties voor de HM-10 Bluetoothmodule

### Src

De map `Src` bevat de bronbestanden:

- `main.c` – hoofdprogramma en lijnvolgalgoritme
- `sensors.c` – initialisatie en uitlezing van de TCRT5000-lijnsensoren
- `motors.c` – PWM- en richtingssturing van beide DC-motoren via de TB6612FNG
- `eeprom.c` – functies voor communicatie met de 24LC256 EEPROM
- `bluetooth.c` – functies voor communicatie met de HM-10 Bluetoothmodule

## Werking van het lijnvolgalgoritme

Bij iedere cyclus worden de lijnsensoren uitgelezen.

Op basis van de sensorwaarden wordt de positie van de zwarte lijn bepaald. Deze lijnpositie wordt gebruikt als foutsignaal voor de motorsturing.

De correctie wordt berekend met een proportionele regeling:

`correctie = 0,75 × lijnpositie`

De motorsnelheden worden vervolgens bepaald als:

`motor A = basissnelheid + correctie`

`motor B = basissnelheid - correctie`

Hierdoor stuurt de robot automatisch terug naar de zwarte lijn.

## Snelheidsregeling

Op rechte stukken wordt een hogere basissnelheid gebruikt.

Wanneer de absolute lijnpositie groter wordt dan de ingestelde bochtdrempel, wordt de basissnelheid verlaagd zodat de robot stabieler door bochten kan rijden.

De gebruikte waarden in de finale code zijn:

- rechte snelheid: `220`
- bochtsnelheid: `150`
- bochtdrempel: `120`
- maximale motorsnelheid: `600`

## Kruispuntdetectie

De robot is geprogrammeerd om op een kruispunt rechtdoor te rijden.

Wanneer minstens drie sensoren gelijktijdig zwart detecteren, wordt dit beschouwd als een brede zwarte zone en wordt de kruispuntmodus geactiveerd.

Tijdens deze modus:

- wordt de normale lijncorrectie tijdelijk uitgeschakeld;
- krijgen beide motoren dezelfde snelheid;
- rijdt de robot rechtdoor over het kruispunt.

De kruispuntmodus wordt pas verlaten nadat gedurende meerdere opeenvolgende meetcycli opnieuw een normale lijn wordt waargenomen.

## Sensoren

Voor de lijnvolging worden zes TCRT5000-reflectiesensoren analoog uitgelezen via de ADC van de STM32F103C8T6.

In de huidige kruispuntdetectie worden de eerste vijf sensorwaarden gebruikt. De zesde sensor wordt daar voorlopig niet meegenomen.

## Motorsturing

Beide GA12-N20 DC-motoren worden aangestuurd via een TB6612FNG dubbele H-brug.

De snelheid wordt geregeld met PWM.

De software kan beide motoren afzonderlijk aansturen, waardoor de robot kan corrigeren naar links of rechts.

## Opmerking

De waarden voor snelheid, bochtdetectie en kruispuntdetectie zijn experimenteel afgestemd op het Plan-B-prototype en het gebruikte testparcours.
