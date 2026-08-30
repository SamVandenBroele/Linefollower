# Sensoren proof of concept

## Testresultaten

De zes TCRT5000-lijnsensoren werden afzonderlijk uitgelezen via de 12-bit ADC van de STM32F103C8T6. Hiervoor wordt de analoge uitgang (A0) van iedere sensormodule gebruikt.

### Meting op witte ondergrond

Bij een witte ondergrond werden ADC-waarden tussen ongeveer 200 en 336 gemeten.

### Meting op zwarte ondergrond

Bij een zwarte ondergrond werden ADC-waarden tussen ongeveer 1700 en 3769 gemeten.

### Conclusie

De test toont aan dat alle zes TCRT5000-sensoren onafhankelijk via de ADC kunnen worden uitgelezen. Er is een duidelijk verschil tussen de gemeten waarden op een witte en een zwarte ondergrond.

De STM32F103C8T6 beschikt over een 12-bit ADC met een bereik van 0 tot 4095. De gemeten waarden benutten een groot deel van dit bereik, met waarden tot 3769 op de zwarte ondergrond.

Voor deze proof of concept worden de ruwe ADC-waarden rechtstreeks weergegeven. Er wordt geen normalisatie of interpolatie toegepast.
