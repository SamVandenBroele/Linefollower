# H-Bridge proof of concept

# H-Bridge proof of concept

Deze proof of concept toont aan dat de TB6612FNG dubbele H-brug correct kan worden aangestuurd door de STM32F103C8T6.

## Doel

Het doel van deze test is controleren of:

- beide GA12-N20 DC-motoren kunnen worden aangestuurd;
- beide motoren onafhankelijk kunnen draaien;
- de draairichting softwarematig kan worden gewijzigd;
- de motorsnelheid met PWM kan worden geregeld;
- de STBY-functie van de TB6612FNG correct werkt.

## Gebruikte componenten

- STM32F103C8T6 development board
- TB6612FNG dubbele H-brug
- 2 × GA12-N20 6 V DC-motor, 300 rpm
- 5 V buck converter
- 3,3 V buck converter
- 2S 7,4 V LiPo-batterij

## Aansluitingen

### Motor A

- PWMA → PA8
- AIN1 → PB13
- AIN2 → PB12
- AO1/AO2 → linker motor

### Motor B

- PWMB → PB3
- BIN1 → PB15
- BIN2 → PA9
- BO1/BO2 → rechter motor

### H-brug

- STBY → PB14
- VCC → 3,3 V
- VM → 5 V
- GND → gemeenschappelijke GND

## Werking

De STM32 genereert PWM-signalen voor PWMA en PWMB. Hiermee wordt de gemiddelde spanning over de motoren en dus hun snelheid geregeld.

AIN1/AIN2 en BIN1/BIN2 bepalen de draairichting van respectievelijk motor A en motor B.

Via de STBY-ingang kan de volledige motordriver worden geactiveerd of in standby worden geplaatst.

De software gebruikt een snelheidswaarde van -1000 tot +1000:

- positieve waarde → vooruit;
- negatieve waarde → achteruit;
- 0 → motor gestopt.

## Testresultaat

De proof of concept werd succesvol uitgevoerd.

- Beide motoren draaien.
- Beide motoren kunnen onafhankelijk worden aangestuurd.
- De draairichting kan softwarematig worden gewijzigd.
- De snelheid kan met PWM worden geregeld.
- Beide motoren kunnen gelijktijdig worden aangestuurd.
- De TB6612FNG werkt correct in combinatie met de STM32F103C8T6.

Deze H-brugsturing wordt verder gebruikt in de finale line-following robot.
