# Finale code

Deze map bevat de finale software van het Plan-B-prototype van de snelle line-following robot.

De software is geschreven voor de STM32F103C8T6 en verzorgt de uitlezing van de lijnsensoren, de aansturing van beide motoren en de detectie van kruispunten.

## Bestandsstructuur

### Inc

- `sensors.h` – definities en functies voor de lijnsensoren
- `motors.h` – definities en functies voor de motorsturing
- `bluetooth.h` – functies voorzien voor de HM-10 Bluetoothmodule
- `eeprom.h` – functies voorzien voor de 24LC256 EEPROM

### Src

- `main.c` – hoofdprogramma en lijnvolgalgoritme
- `sensors.c` – ADC-uitlezing en berekening van de lijnpositie
- `motors.c` – aansturing van de TB6612FNG en beide motoren
- `bluetooth.c` – functies voor Bluetoothcommunicatie
- `eeprom.c` – functies voor EEPROM-communicatie

## Lijnvolging

De robot gebruikt zes TCRT5000-reflectiesensoren.

Alle zes sensoren worden analoog uitgelezen door de ADC van de STM32.

In de huidige finale lijnregeling worden de eerste vijf sensoren gebruikt voor:

- het berekenen van de lijnpositie;
- het detecteren van een kruispunt.

De zesde sensor wordt wel uitgelezen, maar niet meegenomen in de huidige regeling omdat deze in de gemonteerde opstelling een foutief hoge meetwaarde op wit gaf.

De positie van de zwarte lijn wordt bepaald aan de hand van een gewogen gemiddelde van de sensorwaarden.

Op basis van deze lijnpositie wordt een proportionele correctie berekend:

`correctie = 0,50 × lijnpositie`

De motorsnelheden worden vervolgens bepaald als:

`motor A = basissnelheid + correctie`

`motor B = basissnelheid - correctie`

Hierdoor wordt de robot terug naar het midden van de zwarte lijn gestuurd.

## Snelheidsregeling

De huidige instellingen zijn:

- snelheid op een recht stuk: `220`
- snelheid in een bocht: `120`
- grenswaarde voor bochtdetectie: `120`
- maximale motorsnelheid in software: `600`
- proportionele correctiefactor: `0,50`

Wanneer de absolute waarde van de lijnpositie groter wordt dan `120`, wordt de lagere bochtsnelheid gebruikt.

Hierdoor rijdt de robot sneller op rechte stukken en trager wanneer een grotere stuurcorrectie nodig is.

## Kruispuntdetectie

Een brede zwarte zone wordt als kruispunt beschouwd wanneer minimaal drie van de gebruikte lijnsensoren tegelijk zwart detecteren.

Wanneer een kruispunt wordt gedetecteerd:

1. wordt de normale lijncorrectie tijdelijk uitgeschakeld;
2. krijgen beide motoren dezelfde snelheid;
3. rijdt de robot rechtdoor over het kruispunt;
4. blijft de kruispuntmodus actief tot opnieuw gedurende meerdere meetcycli een normale lijn wordt waargenomen.

De gebruikte instellingen zijn:

- minimaal aantal zwarte sensoren: `3`
- aantal cycli voor het verlaten van de kruispuntmodus: `300`

## Motorsturing

De twee GA12-N20 DC-motoren worden aangestuurd met een TB6612FNG dubbele H-brug.

De snelheid wordt geregeld met PWM.

De gebruikte aansluitingen zijn:

### Motor A

- PWMA → PA8
- AIN1 → PB13
- AIN2 → PB12

### Motor B

- PWMB → PB3
- BIN1 → PB15
- BIN2 → PA9

### TB6612FNG

- STBY → PB14
- VCC → 3,3 V
- VM → 5 V
- GND → gemeenschappelijke GND

## Sensoren

De gebruikte analoge ingangen zijn:

- S0 → PA0
- S1 → PA1
- S2 → PA4
- S3 → PA5
- S4 → PA6
- S5 → PA7

De zes sensoren worden gevoed via de 3,3 V-uitgang van de STM32.

## Huidige uitvoering

De huidige finale software bevat de werkende functies die nodig zijn voor het Plan-B-prototype:

- analoog uitlezen van zes lijnsensoren;
- bepalen van de lijnpositie;
- proportionele lijncorrectie;
- afzonderlijke PWM-aansturing van beide motoren;
- vertragen in bochten;
- detecteren van kruispunten;
- rechtdoor rijden over kruispunten.

De parameters werden experimenteel afgesteld op het uiteindelijke prototype.

Met de huidige instellingen volgt de robot de lijn stabiel en kan hij een kruispunt rechtdoor nemen.

De HM-10 Bluetoothmodule en 24LC256 EEPROM zijn voorzien in het elektronische ontwerp, maar worden niet actief gebruikt door de huidige finale lijnvolgsoftware.
