# Gebruiksaanwijzing

Deze gebruiksaanwijzing beschrijft het gebruik van het Plan-B-prototype van de snelle line-following robot.

## Voeding

De robot wordt gevoed door een 2S LiPo-batterij van 7,4 V nominaal.

De batterij wordt via de XT60-connector aangesloten op de robot. De hoofdvoeding wordt in- en uitgeschakeld met de tuimelschakelaar.

De voedingsspanningen worden met twee MP1584EN buckconverters geregeld:

- 5 V voor de STM32 en de motorvoeding via de TB6612FNG
- 3,3 V voor de overige 3,3 V-logica
- de TCRT5000-sensoren worden gevoed via de 3,3 V-uitgang van de STM32

Alle subsystemen gebruiken een gemeenschappelijke GND.

## Inschakelen

1. Plaats de robot op het parcours met de sensoren boven de zwarte lijn.
2. Controleer of de LiPo-batterij correct is aangesloten.
3. Zet de hoofdschakelaar aan.
4. De STM32 start het lijnvolgprogramma automatisch.
5. De robot begint de zwarte lijn te volgen.

## Lijnvolging

De robot beschikt over zes TCRT5000-reflectiesensoren.

De analoge uitgangen van de sensoren worden uitgelezen via de ADC van de STM32F103C8T6.

De software bepaalt aan de hand van de sensorwaarden de positie van de zwarte lijn. Met een proportionele regeling wordt vervolgens het snelheidsverschil tussen de linker- en rechtermotor bepaald.

Op rechte stukken wordt een hogere basissnelheid gebruikt. Wanneer een grotere afwijking van de lijn wordt gemeten, wordt de basissnelheid verlaagd zodat de robot stabieler door bochten kan rijden.

In de huidige software worden vijf van de zes uitgelezen sensoren gebruikt voor de berekening van de lijnpositie. De zesde sensor wordt voorlopig niet meegenomen omdat deze in de huidige opstelling op een witte ondergrond foutief hoge ADC-waarden kan geven.

## Kruispunten

De robot is geprogrammeerd om op een kruispunt rechtdoor te rijden.

Wanneer minstens drie van de gebruikte sensoren gelijktijdig zwart detecteren, wordt dit beschouwd als een brede zwarte zone en wordt de kruispuntmodus geactiveerd.

Tijdens deze modus:

- wordt de normale lijncorrectie tijdelijk uitgeschakeld;
- worden beide motoren met dezelfde snelheid aangestuurd;
- rijdt de robot rechtdoor over het kruispunt.

Wanneer gedurende meerdere opeenvolgende meetcycli opnieuw een normale lijn wordt waargenomen, schakelt de robot automatisch terug naar de normale lijnvolging.

## Motorsturing

De robot gebruikt twee GA12-N20 DC-motoren.

Beide motoren worden onafhankelijk aangestuurd via een TB6612FNG dubbele H-brug.

De snelheid van de motoren wordt geregeld met PWM. Door het snelheidsverschil tussen de linker- en rechtermotor aan te passen kan de robot naar links of rechts corrigeren.

## Instellingen

De belangrijkste instellingen van de huidige finale software zijn:

- rechte snelheid: `220`
- bochtsnelheid: `150`
- bochtdrempel: `120`
- maximale motorsnelheid: `600`
- proportionele correctiefactor: `0,75`
- kruispuntdetectie: minimaal `3` zwarte sensoren

Deze waarden zijn experimenteel afgestemd op het Plan-B-prototype en het gebruikte testparcours.

## Uitschakelen

Na gebruik wordt de robot uitgeschakeld met de hoofdschakelaar.

Wanneer de robot langere tijd niet gebruikt wordt, wordt de LiPo-batterij losgekoppeld van de robot.

## LiPo-batterij

Voor het opladen van de 2S LiPo-batterij moet een geschikte LiPo-balanslader gebruikt worden.

De gebruikte batterij heeft:

- nominale spanning: 7,4 V
- volledig geladen spanning: 8,4 V
- capaciteit: 1500 mAh
- ontlaadfactor: 45C

Een beschadigde of opgezwollen LiPo-batterij mag niet gebruikt of opgeladen worden.

## Huidige beperkingen

De HM-10 Bluetoothmodule, EEPROM en externe START/STOP-functionaliteit zijn voorzien in het elektronische ontwerp, maar zijn niet geïntegreerd in de huidige finale lijnvolgsoftware.

Er wordt in het huidige Plan-B-prototype geen Power-on LED gebruikt.
