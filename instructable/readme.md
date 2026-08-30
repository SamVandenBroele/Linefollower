# Instructable

Dit stappenplan beschrijft hoe het Plan-B-prototype van de snelle line-following robot kan worden opgebouwd.

Voor de gebruikte componenten wordt verwezen naar de Bill of Materials. Het elektronische schema en de mechanische tekeningen zijn terug te vinden in de map `technische tekeningen`.

## Stap 1 – Verzamel de componenten

Verzamel de componenten uit de Bill of Materials.

De belangrijkste onderdelen zijn:

- STM32F103C8T6 development board
- TB6612FNG dubbele H-brug
- 6 × TCRT5000-reflectiesensor
- 2 × GA12-N20 6 V 300 rpm DC-motor
- 2 × robotwiel van 44 mm
- 2S LiPo-batterij van 7,4 V
- XT60-connector
- 2 × MP1584EN buckconverter
- tuimelschakelaar
- prototypeprintplaat
- PVC-chassis
- Dupont jumperdraden
- HM-10 Bluetoothmodule
- 24LC256 EEPROM
- LEGO-gezichtje als glijsteun

Het LEGO-gezichtje was reeds thuis beschikbaar en wordt gebruikt als derde steunpunt van de robot. Het glijdt tijdens het rijden over het parcours.

## Stap 2 – Bouw het chassis

Maak het chassis uit een PVC-plaat van 4 mm dik.

Monteer vervolgens:

1. beide GA12-N20 motoren;
2. beide aandrijfwielen;
3. het LEGO-gezichtje als glijsteun en derde steunpunt;
4. de sensoropstelling aan de voorzijde;
5. de elektronische componenten op het chassis.

Gebruik de mechanische tekeningen in de repository als referentie voor de afmetingen en plaatsing van de onderdelen.

## Stap 3 – Monteer de lijnsensoren

Monteer zes TCRT5000-sensoren naast elkaar aan de voorzijde van de robot.

De sensoren moeten naar de ondergrond gericht zijn en voldoende dicht boven het parcours geplaatst worden om een duidelijk verschil tussen zwart en wit te meten.

Van iedere TCRT5000-module wordt de analoge uitgang `A0` gebruikt.

De digitale uitgang `D0` wordt niet gebruikt.

## Stap 4 – Bouw de voeding

Sluit de 2S LiPo-batterij via de XT60-connector en de tuimelschakelaar aan op de voedingsverdeling.

Gebruik twee MP1584EN buckconverters.

Stel vóór het aansluiten van de elektronica de uitgangsspanningen met een multimeter af:

- buckconverter 1: 3,3 V
- buckconverter 2: 5 V

De 3,3 V-buckconverter voedt de 3,3 V-logica.

De 5 V-buckconverter voedt de STM32 en de motorvoeding van de TB6612FNG.

De zes TCRT5000-sensoren worden gevoed via de 3,3 V-uitgang van de STM32.

Alle onderdelen moeten een gemeenschappelijke GND hebben.

## Stap 5 – Sluit de STM32 en sensoren aan

Verbind de analoge uitgangen van de zes TCRT5000-sensoren met de STM32:

- sensor S0 → PA0
- sensor S1 → PA1
- sensor S2 → PA4
- sensor S3 → PA5
- sensor S4 → PA6
- sensor S5 → PA7

Verbind de voedingsaansluitingen van de sensoren met de 3,3 V-uitgang van de STM32 en met GND.

## Stap 6 – Sluit de TB6612FNG aan

Sluit de TB6612FNG aan op de STM32.

De gebruikte stuursignalen zijn:

- PWMA → PA8
- AIN1 → PB13
- AIN2 → PB12
- STBY → PB14
- PWMB → PB3
- BIN1 → PB15
- BIN2 → PA9

Sluit:

- VCC aan op 3,3 V van de 3,3 V-buckconverter;
- VM aan op 5 V van de 5 V-buckconverter;
- GND aan op de gemeenschappelijke massa.

Sluit vervolgens beide GA12-N20 motoren aan op de motoruitgangen van de TB6612FNG.

## Stap 7 – Controleer de bedrading

Controleer vóór het inschakelen:

- polariteit van de LiPo-batterij;
- uitgangsspanning van beide buckconverters;
- gemeenschappelijke GND;
- aansluiting van de STM32;
- aansluiting van de TB6612FNG;
- aansluiting van de zes lijnsensoren;
- aansluiting van beide motoren.

Gebruik hiervoor ook het elektronische schema in de repository.

## Stap 8 – Programmeer de STM32

Open het project in STM32CubeIDE.

De finale broncode staat in:

`code/finaal`

De belangrijkste bestanden zijn:

- `main.c`
- `sensors.c`
- `motors.c`
- `sensors.h`
- `motors.h`

Compileer het programma en programmeer de STM32F103C8T6 via SWD met een ST-LINK-programmer.

Voor het programmeren worden gebruikt:

- PA13 → SWDIO
- PA14 → SWCLK
- GND → GND

## Stap 9 – Test de sensoren

Plaats de sensoren eerst boven een witte en daarna boven een zwarte ondergrond.

Controleer of alle zes sensoren een duidelijk verschil in ADC-waarde geven.

De uitgevoerde sensortest is terug te vinden bij:

`code/proof of concepts/sensor`

## Stap 10 – Test de motoren

Controleer afzonderlijk of beide motoren:

- vooruit kunnen draaien;
- afzonderlijk kunnen worden aangestuurd;
- regelbaar zijn in snelheid via PWM.

De uitgevoerde motortest is terug te vinden bij:

`code/proof of concepts/hbridge`

## Stap 11 – Test de lijnvolger

Plaats de robot met de sensoren boven de zwarte lijn.

Schakel de robot in met de tuimelschakelaar.

De STM32 start het programma automatisch en de robot begint de zwarte lijn te volgen.

De software:

- bepaalt de positie van de zwarte lijn;
- corrigeert de snelheid van beide motoren;
- verlaagt de snelheid in bochten;
- detecteert brede zwarte zones als kruispunt;
- probeert op een kruispunt rechtdoor te rijden.

## Stap 12 – Uitschakelen

Schakel de robot na gebruik uit met de tuimelschakelaar.

Koppel de LiPo-batterij los wanneer de robot langere tijd niet gebruikt wordt.

## Opmerking

Het huidige Plan-B-prototype heeft geen afzonderlijke START/STOP-drukknop en geen Power-on LED.

Als derde steunpunt wordt een LEGO-gezichtje gebruikt dat reeds thuis beschikbaar was. Dit onderdeel dient als eenvoudige glijsteun onder het chassis.

De HM-10 Bluetoothmodule en 24LC256 EEPROM zijn voorzien in het elektronische ontwerp, maar zijn niet geïntegreerd in de huidige finale lijnvolgsoftware.
