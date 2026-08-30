# Sensoren proof of concept

## Testresultaten

De zes TCRT5000-lijnsensoren werden afzonderlijk uitgelezen via de 12-bit ADC van de STM32F103C8T6. Hiervoor wordt de analoge uitgang (A0) van iedere sensormodule gebruikt.

### Meting op witte ondergrond

Bij een witte ondergrond geven de sensoren een relatief lage ADC-waarde. De onderstaande screenshot toont de ruwe ADC-waarden van de zes sensoren.

![Sensoren op witte ondergrond](sensor_wit.png)

### Meting op zwarte ondergrond

Bij een zwarte ondergrond stijgt de gemeten ADC-waarde duidelijk. Hierdoor kan de software onderscheid maken tussen de witte ondergrond en de zwarte lijn.

![Sensoren op zwarte ondergrond](sensor_zwart.png)

### Conclusie

De test toont aan dat alle zes TCRT5000-sensoren onafhankelijk via de ADC kunnen worden uitgelezen en dat er een duidelijk verschil meetbaar is tussen wit en zwart. De getoonde waarden zijn ruwe ADC-waarden; voor deze proof of concept wordt geen normalisatie of interpolatie toegepast.
