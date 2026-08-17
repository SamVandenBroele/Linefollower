# Bill of Materials

Deze Bill of Materials bevat de onderdelen voor het plan-B-prototype van de snelle line-following robot.

| Nr. | Component | Type / specificatie | Aangekocht | Gebruikt | Kostprijs verpakking | Kost in project | Opmerking |
|---:|---|---|---:|---:|---:|---:|---|
| 1 | Dubbele motordriver | TB6612FNG breakoutmodule | 1 | 1 | €4,61 | €4,61 | Stuurt beide DC-motoren aan |
| 2 | Dupont jumperdraden | 10 cm, diverse stekkertypes | 1 set | n.v.t. | €1,91 | €1,91 | Alleen voor Plan B |
| 3 | Infraroodreflectiesensor | TCRT5000-module met VCC, GND, D0 en A0 | 10 | 6 | €3,89 | €2,33 | A0 wordt gebruikt als analoog signaal; minimaal 6 sensoren vereist |
| 4 | Microcontrollerbord | STM32F103C8T6 development board | 1 | 1 | €4,69 | €4,69 | Centrale besturing |
| 5 | Bluetoothmodule | HM-10 BLE 4.0 | 1 | 1 | €3,14 | €3,14 | Voor draadloze instellingen, communicatie en debug |
| 6 | Printkroonsteen | KF301, 2-polig, steek 5,0 mm | 50 | ca. 4 | €0,88 | €0,07 | Voor motor- en voedingsaansluitingen |
| 7 | Aan-uitschakelaar | GOOBAY 10013, mini-tuimelschakelaar, ON-OFF, 3 A / 125 V | 2 | 1 | €1,22 | €0,61 | Bistabiele hoofdschakelaar voor de voeding |
| 8 | DC-DC-omvormer | Step-downmodule naar 5 V | 2 | 1 | €1,99 | €1,00 | Voor gereguleerde voeding van de besturing |
| 9 | Robotwiel | Rubber wiel, diameter 44 mm, geschikt voor N20-as | 2 | 2 | €0,52 | €0,52 | Aandrijfwielen |
| 10 | DC-reductiemotor | GA12-N20, 6 V, 300 rpm | 2 | 2 | €3,60 | €3,60 | Aandrijving van de robot |
| 11 | Batterijconnector | XT60 mannelijk en vrouwelijk | 2 sets | 1 set | €2,38 | €1,19 | Voor afneembare batterijverbinding |
| 12 | LiPo-batterij | 2S, 7,4 V, 1500 mAh, 45C | 1 | 1 | €7,91 | €7,91 | Volgeladen spanning is 8,4 V |
| 13 | Pinheaders | 2,54 mm male headers | 10 strips | n.v.t. | €0,68 | €0,68 | Voor modulaire aansluitingen |
| 14 | Kogelwiel | CY-19D metalen ball caster | 1 | 1 | €1,27 | €1,27 | Derde steunpunt |
| 15 | Prototypeprintplaat | Dubbelzijdig protoboard, 6 × 8 cm | 3 | 1 | €2,90 | €0,97 | Voor Plan-B-elektronica |
| 16 | Chassismateriaal | PVC-plaat, 4 mm, 100 × 200 mm | 1 | 1 | €4,13 | €4,13 | Basisplaat van de robot |
| 17 | EEPROM | 24LC256-I/P, 256 Kbit (32 KB), I²C, DIP-8 | 2 | 1 | €1,90 | €0,95 | Opslag van PID-instellingen, calibratie, maximumsnelheid enz. |
| 18 | I²C pull-upweerstand | Metaalfilmweerstand, 4,7 kΩ | 10 | 2 | €0,35 | €0,07 | Pull-ups voor SDA en SCL |
| 19 | Ontkoppelcondensator | Keramisch, 100 nF, KERKO 100N | 10 | 1 | €0,40 | €0,04 | Ontkoppeling bij EEPROM |
| 20 | Start/stop-drukknop | Momentary tactile pushbutton, 6 × 6 mm | - | 1 | - | €0,00 | Monostabiele START/STOP-schakelaar; reeds in bezit |
| 21 | Power-on LED | Losse LED, THT | - | 1 | - | €0,00 | Visuele indicatie dat de voeding ingeschakeld is; reeds in bezit |
| 22 | LED-serieweerstand | 1 kΩ, THT | - | 1 | - | €0,00 | Stroombegrenzing voor Power-on LED; reeds in bezit |

## Kostenoverzicht

| Omschrijving | Bedrag |
|---|---:|
| Totale aankoopprijs onderdelen | €48,37 |
| Geschatte kost van gebruikte onderdelen in één robot | ca. €40,49 |
