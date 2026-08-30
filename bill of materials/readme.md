# Bill of Materials

Deze Bill of Materials bevat de onderdelen die gebruikt worden voor het Plan-B-prototype van de snelle line-following robot.

| Nr. | Component | Type / specificatie | Aangekocht | Gebruikt | Kostprijs verpakking | Kost in project | Opmerking |
|---:|---|---|---:|---:|---:|---:|---|
| 1 | Dubbele motordriver | TB6612FNG breakoutmodule | 1 | 1 | €4,61 | €4,61 | Stuurt beide GA12-N20 DC-motoren aan |
| 2 | Dupont jumperdraden | 10 cm, diverse stekkertypes | 1 set | n.v.t. | €1,91 | €1,91 | Gebruikt voor het Plan-B-prototype |
| 3 | Infraroodreflectiesensor | TCRT5000-module met VCC, GND, D0 en A0 | 10 | 6 | €3,89 | €2,33 | Zes sensoren gemonteerd; analoge uitgang A0 wordt gebruikt |
| 4 | Microcontrollerbord | STM32F103C8T6 development board | 1 | 1 | €4,69 | €4,69 | Centrale besturing van de robot |
| 5 | Bluetoothmodule | HM-10 BLE 4.0 | 1 | 1 | €3,14 | €3,14 | Fysiek voorzien; draadloze communicatie is niet geïntegreerd in de huidige finale software |
| 6 | Printkroonsteen | KF301, 2-polig, steek 5,0 mm | 50 | ca. 4 | €0,88 | €0,07 | Voor motor- en voedingsaansluitingen |
| 7 | Aan-uitschakelaar | GOOBAY 10013, mini-tuimelschakelaar, ON-OFF, 3 A / 125 V | 2 | 1 | €1,22 | €0,61 | Bistabiele hoofdschakelaar voor het in- en uitschakelen van de batterijvoeding |
| 8 | DC-DC buckconverter | DollaTek MP1584EN, instelbaar, 4,5–28 V ingang, 0,8–20 V uitgang, max. 3 A | 5 | 2 | €4,99 | €2,00 | Eén ingesteld op 3,3 V voor de logica en één ingesteld op 5 V voor STM32 en motorvoeding |
| 9 | Robotwiel | Rubber wiel, diameter 44 mm, geschikt voor N20-as | 2 | 2 | €0,52 | €0,52 | Aandrijfwielen |
| 10 | DC-reductiemotor | GA12-N20, 6 V, 300 rpm | 2 | 2 | €3,60 | €3,60 | Aandrijving van de robot |
| 11 | Batterijconnector | XT60 mannelijk en vrouwelijk | 2 sets | 1 set | €2,38 | €1,19 | Afneembare verbinding tussen LiPo en robot |
| 12 | LiPo-batterij | 2S, 7,4 V, 1500 mAh, 45C | 1 | 1 | €7,91 | €7,91 | Nominaal 7,4 V; maximaal 8,4 V volledig geladen |
| 13 | Pinheaders | 2,54 mm male headers | 10 strips | n.v.t. | €0,68 | €0,68 | Voor modulaire elektrische aansluitingen |
| 14 | Kogelwiel | CY-19D metalen ball caster | 1 | 1 | €1,27 | €1,27 | Derde steunpunt van het chassis |
| 15 | Prototypeprintplaat | Dubbelzijdig protoboard, 6 × 8 cm | 3 | 1 | €2,90 | €0,97 | Printplaat voor de Plan-B-elektronica |
| 16 | Chassismateriaal | PVC-plaat, 4 mm, 100 × 200 mm | 1 | 1 | €4,13 | €4,13 | Basisplaat van de robot |
| 17 | EEPROM | 24LC256-I/P, 256 Kbit (32 KB), I²C, DIP-8 | 2 | 1 | €1,90 | €0,95 | Fysiek voorzien; niet geïntegreerd in de huidige finale lijnvolgsoftware |
| 18 | I²C pull-upweerstand | Metaalfilmweerstand, 4,7 kΩ | 10 | 2 | €0,35 | €0,07 | Pull-upweerstanden voor SDA en SCL van de I²C-bus |
| 19 | Ontkoppelcondensator | Keramisch, 100 nF, KERKO 100N | 10 | 1 | €0,40 | €0,04 | Voedingsontkoppeling bij de EEPROM |
| 20 | Start/stop-drukknop | Momentary tactile pushbutton, 6 × 6 mm | - | 0 | - | €0,00 | Voorzien in het elektrisch ontwerp, maar niet gemonteerd op het uiteindelijke Plan-B-prototype |
| 21 | Power-on LED | Losse LED, THT | - | 0 | - | €0,00 | Voorzien in het elektrisch ontwerp, maar niet gemonteerd op het uiteindelijke Plan-B-prototype |
| 22 | LED-serieweerstand | 1 kΩ, THT | - | 0 | - | €0,00 | Voorzien voor de Power-on LED, maar niet gebruikt op het uiteindelijke Plan-B-prototype |

## Voedingsverdeling

De robot wordt gevoed door een 2S LiPo-batterij van 7,4 V nominaal en maximaal 8,4 V bij volledige lading.

De voedingsverdeling is als volgt:

- LiPo-batterij → hoofdschakelaar → beide buckconverters
- Buckconverter 1 → **3,3 V**
  - TB6612FNG VCC
  - 24LC256 EEPROM
  - HM-10 Bluetoothmodule
  - I²C pull-upweerstanden
- Buckconverter 2 → **5 V**
  - STM32F103C8T6 development board
  - TB6612FNG VM / motorvoeding
- STM32 3,3 V-uitgang → zes TCRT5000-lijnsensoren
- TB6612FNG → beide GA12-N20 DC-motoren
- Alle subsystemen gebruiken een gemeenschappelijke GND

## Bediening

Het huidige Plan-B-prototype beschikt uitsluitend over een bistabiele tuimelschakelaar voor het in- en uitschakelen van de robot.

Een afzonderlijke START/STOP-drukknop en Power-on LED zijn niet gemonteerd op het uiteindelijke prototype.

## Kostenoverzicht

| Omschrijving | Bedrag |
|---|---:|
| Totale aankoopprijs onderdelen | €51,37 |
| Geschatte kost van gebruikte onderdelen in één robot | ca. €41,49 |
