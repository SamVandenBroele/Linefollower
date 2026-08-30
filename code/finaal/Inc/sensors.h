#ifndef SENSORS_H_
#define SENSORS_H_

#include <stdint.h>

/* =========================================================
   LINE SENSORS

   S1 -> PA0 -> ADC1_IN0
   S2 -> PA1 -> ADC1_IN1
   S3 -> PA4 -> ADC1_IN4
   S4 -> PA5 -> ADC1_IN5
   S5 -> PA6 -> ADC1_IN6
   S6 -> PA7 -> ADC1_IN7
   ========================================================= */

#define SENSOR_COUNT 6

/*
 * Voorlopige drempel tussen wit en zwart.
 *
 * In de definitieve montage meten we ongeveer:
 * wit  -> rond 200 - 300
 * zwart -> vanaf ongeveer 600 en hoger
 *
 * Daarom gebruiken we voorlopig 450.
 */
#define LINE_THRESHOLD 450


/* Ruwe ADC-waarden van de 6 sensoren */
extern volatile uint16_t sensor[SENSOR_COUNT];


/* Sensorhardware + ADC initialiseren */
void Sensors_Init(void);


/* Eén ADC-kanaal uitlezen */
uint16_t Sensors_ReadADC(uint8_t channel);


/* Alle zes sensoren uitlezen */
void Sensors_ReadAll(void);


/*
 * Positie van de zwarte lijn berekenen.
 *
 * negatief = lijn links
 * 0        = midden
 * positief = lijn rechts
 */
int16_t Sensors_GetLinePosition(void);


#endif /* SENSORS_H_ */

