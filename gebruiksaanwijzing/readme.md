# Gebruiksaanwijzing

Deze gebruiksaanwijzing beschrijft het gebruik van het Plan-B-prototype van de snelle line-following robot.

## Voeding

De robot wordt gevoed door een 2S LiPo-batterij van 7,4 V nominaal.

De batterij wordt via de XT60-connector aangesloten op de robot. De hoofdvoeding wordt in- en uitgeschakeld met de tuimelschakelaar.

De voedingsspanningen worden met twee MP1584EN buckconverters geregeld:

- 5 V voor de STM32 en de motorvoeding via de TB6612FNG
- 3,3 V voor de overige 3,3 V-logica
- de TCRT5000-sensoren worden gevoed via de 3,3 V-uitgang van de STM32

Alle subsystemen hebben een gemeenschappelijke GND.

## Inschakelen

1. Plaats de robot op het parcours met de sensoren boven de zwarte lijn.
2. Controleer of de LiPo-batterij correct is aangesloten.
3. Zet de hoofdschakelaar aan.
4. De Power-on LED geeft aan dat de robot voeding krijgt.
5. De STM32 start het lijnvolgprogramma automatisch.
6. De robot begint de zwarte lijn te volgen.

## Lijnvolging

De robot gebruikt zes TCRT5000-reflectiesensoren om het parcours waar te nemen.

De analoge sensorwaarden worden ingelezen door de ADC van de STM32F103C8T6.

De software bepaalt aan de hand van de sensorwaarden de positie van de zwarte lijn. Met een proportionele regeling wordt vervolgens het snelheidsverschil tussen de linker- en rechtermotor bepaald.

Op rechte stukken rijdt de robot sneller. In bochten wordt de basissnelheid automatisch verlaagd.

## Kruispunten

De robot is geprogrammeerd om op een kruispunt rechtdoor te rijden.

Wanneer meerdere sensoren gelijktijdig een brede zwarte zone detecteren, schakelt de software tijdelijk over naar kruispuntmodus.

Tijdens deze modus worden beide motoren met dezelfde snelheid aangestuurd zodat de robot rechtdoor over het kruispunt rijdt.

Na het verlaten van het kruispunt schakelt de robot automatisch terug naar de normale lijnvolging.

## Instellingen

De belangrijkste instellingen van de huidige software zijn:

- rechte snelheid: 220
- bochtsnelheid: 150
- bochtdrempel: 120
- maximale motorsnelheid: 600
- proportionele correctiefactor: 0,75

Deze waarden zijn experimenteel afgestemd op het Plan-B-prototype.

## Uitschakelen

Na gebruik wordt de robot uitgeschakeld met de hoofdschakelaar.

Koppel de LiPo-batterij los wanneer de robot langere tijd niet gebruikt wordt.

## LiPo-batterij

Gebruik voor het opladen van de 2S LiPo-batterij uitsluitend een geschikte LiPo-balanslader.

De batterij heeft:

- nominale spanning: 7,4 V
- volledig geladen spanning: 8,4 V
- capaciteit: 1500 mAh

Beschadigde of opgezwollen LiPo-batterijen mogen niet gebruikt of opgeladen worden.

## Huidige beperkingen

De HM-10 Bluetoothmodule, EEPROM en externe START/STOP-functionaliteit zijn voorzien in het elektronische ontwerp, maar zijn niet geïntegreerd in de huidige finale lijnvolgsoftware.
