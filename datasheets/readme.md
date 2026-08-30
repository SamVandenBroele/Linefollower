# Datasheets

Deze map bevat de beschikbare datasheets en technische documentatie van de belangrijkste componenten die gebruikt worden in de Line Following Robot.

## Componenten

De volgende documentatie is opgenomen:

- STM32F103C8T6 microcontroller
- TB6612FNG dubbele motordriver
- TCRT5000 reflectieve optische sensor
- HM-10 Bluetoothmodule
- GA12-N20 6 V 300 rpm DC-reductiemotor
- 24LC256 I²C EEPROM

## TCRT5000-sensormodule

De TCRT5000-sensoren die in dit project gebruikt worden, zijn complete sensormodules met een TCRT5000 reflectieve optische sensor en bijkomende elektronica, waaronder een LM393-comparator.

Er was geen officiële datasheet beschikbaar voor de volledige gebruikte sensormodule.

Daarom is de datasheet van de TCRT5000-sensor zelf opgenomen als technische referentie.

In het uiteindelijke prototype wordt de analoge uitgang A0 van de sensormodule gebruikt.

## GA12-N20 6 V 300 rpm motor

Voor de exacte GA12-N20 6 V 300 rpm motor die in dit project gebruikt wordt, was geen officiële datasheet beschikbaar.

Het opgenomen GA12-N20-document wordt daarom gebruikt als algemene technische referentie voor deze motorfamilie en beschrijft niet noodzakelijk exact de gebruikte 300 rpm-variant.

## MP1584EN buckconverter

Voor de voedingsregeling worden twee instelbare MP1584EN DC-DC step-down buckconverters gebruikt.

De batterijspanning van de 2S LiPo wordt hiermee verlaagd naar:

- 3,3 V voor de 3,3 V-logica;
- 5 V voor de STM32 en de motorvoeding.

De gebruikte modules zijn gebaseerd op de MP1584EN en hebben een instelbare uitgangsspanning.

Er is momenteel geen aparte datasheet van de gebruikte MP1584EN-module opgenomen in deze map.
