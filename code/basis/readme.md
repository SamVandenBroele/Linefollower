# Basisprogramma

Deze map was voorzien voor het basisprogramma waarin verschillende algemene functies van de robot samen geïntegreerd konden worden.

Het oorspronkelijke project voorzag onder andere:

- instelbare parameters via seriële communicatie;
- opslag van parameters in EEPROM;
- START/STOP via een externe interrupt;
- draadloze communicatie.

Deze functies zijn niet volledig samengebracht in één afzonderlijk basisprogramma.

Voor het uiteindelijke Plan-B-prototype werd de ontwikkeling voornamelijk gericht op de essentiële functies voor een werkende line-following robot:

- uitlezen van zes analoge TCRT5000-lijnsensoren;
- aansturen van twee DC-motoren via de TB6612FNG;
- PWM-snelheidsregeling;
- berekenen van de lijnpositie;
- corrigeren van de rijrichting;
- detecteren en rechtdoor rijden op kruispunten.

De daadwerkelijk gebruikte software van het uiteindelijke prototype is terug te vinden in:

`code/finaal`

Afzonderlijke werkende tests van de lijnsensoren en H-brug zijn terug te vinden onder:

`code/proof of concepts`
