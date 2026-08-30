# Mechanisch ontwerp

Deze map bevat het mechanische ontwerp van het Plan-B-prototype van de snelle line-following robot.

## Chassis

Het chassis is vervaardigd uit een PVC-plaat.

Belangrijkste afmetingen:

- Materiaal: PVC
- Dikte: 4 mm
- Breedte: 100 mm
- Lengte: 147 mm
- Uitsparingen voor de wielen: 20 × 47 mm
- Opening voor de sensoren: 90 × 5 mm
- Voorste rand: 5 mm
- Achterste rand: 5 mm

## Aandrijving

De robot wordt aangedreven door twee GA12-N20 DC-reductiemotoren van 6 V en 300 rpm.

Op beide motoren is een rubberen wiel met een diameter van 44 mm gemonteerd.

## Lijnsensoren

Aan de voorzijde van het chassis zijn zes TCRT5000-reflectiesensoren naast elkaar geplaatst.

De sensoren zijn naar de ondergrond gericht en worden gebruikt om de zwarte lijn op de witte ondergrond te detecteren.

## Elektronica

Op het chassis zijn onder andere de volgende onderdelen geplaatst:

- STM32F103C8T6 development board
- TB6612FNG dubbele H-brug
- twee MP1584EN buckconverters
- 2S LiPo-batterij
- HM-10 Bluetoothmodule
- 24LC256 EEPROM
- prototypeprintplaat
- zes TCRT5000-lijnsensoren

## Derde steunpunt

Als derde steunpunt onder het chassis wordt een LEGO-gezichtje gebruikt dat reeds thuis beschikbaar was.

Het LEGO-onderdeel vormt een eenvoudige glijsteun en glijdt tijdens het rijden over het parcours.

## Mechanische tekening

Het bestand `Mechanical_Design.png` toont de afmetingen van het chassis en de voorziene plaatsing van de belangrijkste onderdelen.

De uiteindelijke fysieke plaatsing van kleine elektronische componenten kan licht afwijken van de schematische voorstelling.
