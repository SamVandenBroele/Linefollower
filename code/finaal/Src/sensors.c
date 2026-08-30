#include "sensors.h"


/* =========================================================
   REGISTER DEFINITIONS
   ========================================================= */

/* RCC */
#define RCC_CFGR       (*(volatile uint32_t *)0x40021004)
#define RCC_APB2ENR    (*(volatile uint32_t *)0x40021018)

/* GPIOA */
#define GPIOA_CRL      (*(volatile uint32_t *)0x40010800)

/* ADC1 */
#define ADC1_SR        (*(volatile uint32_t *)0x40012400)
#define ADC1_CR2       (*(volatile uint32_t *)0x40012408)
#define ADC1_SMPR2     (*(volatile uint32_t *)0x40012410)
#define ADC1_SQR1      (*(volatile uint32_t *)0x4001242C)
#define ADC1_SQR3      (*(volatile uint32_t *)0x40012434)
#define ADC1_DR        (*(volatile uint32_t *)0x4001244C)


/* =========================================================
   GLOBAL SENSOR ARRAY
   ========================================================= */

volatile uint16_t sensor[SENSOR_COUNT];


/* =========================================================
   SENSOR INITIALISATION
   ========================================================= */

void Sensors_Init(void)
{
    /* GPIOA clock */
    RCC_APB2ENR |= (1U << 2);

    /* ADC1 clock */
    RCC_APB2ENR |= (1U << 9);


    /* -----------------------------------------------------
       GPIO als analog input
       MODE = 00
       CNF  = 00
       ----------------------------------------------------- */

    /* PA0 -> S0 */
    GPIOA_CRL &= ~(0xFU << 0);

    /* PA1 -> S1 */
    GPIOA_CRL &= ~(0xFU << 4);

    /* PA4 -> S2 */
    GPIOA_CRL &= ~(0xFU << 16);

    /* PA5 -> S3 */
    GPIOA_CRL &= ~(0xFU << 20);

    /* PA6 -> S4 */
    GPIOA_CRL &= ~(0xFU << 24);

    /* PA7 -> S5 */
    GPIOA_CRL &= ~(0xFU << 28);


    /* -----------------------------------------------------
       ADC clock
       ADCPRE = 10
       PCLK2 / 6
       ----------------------------------------------------- */

    RCC_CFGR &= ~(0x3U << 14);
    RCC_CFGR |=  (0x2U << 14);


    /* -----------------------------------------------------
       Sampling time
       ----------------------------------------------------- */

    ADC1_SMPR2 |= (0x7U << 0);   /* Channel 0 */
    ADC1_SMPR2 |= (0x7U << 3);   /* Channel 1 */
    ADC1_SMPR2 |= (0x7U << 12);  /* Channel 4 */
    ADC1_SMPR2 |= (0x7U << 15);  /* Channel 5 */
    ADC1_SMPR2 |= (0x7U << 18);  /* Channel 6 */
    ADC1_SMPR2 |= (0x7U << 21);  /* Channel 7 */


    /* Eén conversie per sequence */
    ADC1_SQR1 = 0;


    /* ADC inschakelen */
    ADC1_CR2 |= (1U << 0);


    /* -----------------------------------------------------
       Software trigger selecteren
       EXTSEL = 111 -> SWSTART
       EXTTRIG = 1
       ----------------------------------------------------- */

    ADC1_CR2 &= ~(0x7U << 17);
    ADC1_CR2 |=  (0x7U << 17);
    ADC1_CR2 |=  (1U << 20);


    /* Kleine wachttijd */
    for (volatile uint32_t i = 0; i < 10000U; i++)
    {
    }


    /* ADC calibration reset */
    ADC1_CR2 |= (1U << 3);

    while (ADC1_CR2 & (1U << 3))
    {
    }


    /* ADC calibreren */
    ADC1_CR2 |= (1U << 2);

    while (ADC1_CR2 & (1U << 2))
    {
    }
}


/* =========================================================
   READ ONE ADC CHANNEL
   ========================================================= */

uint16_t Sensors_ReadADC(uint8_t channel)
{
    /* Selecteer ADC-kanaal */
    ADC1_SQR3 = channel;


    /* Start softwareconversie */
    ADC1_CR2 |= (1U << 22);


    /* Wacht tot End Of Conversion */
    while (!(ADC1_SR & (1U << 1)))
    {
    }


    /* ADC-resultaat teruggeven */
    return (uint16_t)ADC1_DR;
}


/* =========================================================
   READ ALL SIX SENSORS

   Fysieke volgorde:

   LINKS                           RECHTS
   S0   S1   S2   S3   S4   S5
   ========================================================= */

void Sensors_ReadAll(void)
{
    sensor[0] = Sensors_ReadADC(0);  /* S0 -> PA0 */
    sensor[1] = Sensors_ReadADC(1);  /* S1 -> PA1 */
    sensor[2] = Sensors_ReadADC(4);  /* S2 -> PA4 */
    sensor[3] = Sensors_ReadADC(5);  /* S3 -> PA5 */
    sensor[4] = Sensors_ReadADC(6);  /* S4 -> PA6 */
    sensor[5] = Sensors_ReadADC(7);  /* S5 -> PA7 */
}


/* =========================================================
   CALCULATE LINE POSITION
   =========================================================

   Sensorposities:

   S0 = -390
   S1 = -240
   S2 =  -85
   S3 =  +70
   S4 = +240
   S5 = +400

   S5 wordt TIJDELIJK NIET meegenomen
   omdat deze op wit foutief een hoge ADC-waarde geeft.

   S2 + S3 vormen het gewenste midden.

   ========================================================= */

int16_t Sensors_GetLinePosition(void)
{
    static const int16_t position[SENSOR_COUNT] =
    {
        -390,
        -240,
         -85,
          70,
         240,
         400
    };


    static int16_t last_position = 0;

    int32_t weighted_sum = 0;
    uint32_t total_signal = 0;


    /* -----------------------------------------------------
       Alleen S0 t.e.m. S4 gebruiken

       i < 5 betekent:
       sensor[0]
       sensor[1]
       sensor[2]
       sensor[3]
       sensor[4]

       sensor[5] wordt genegeerd.
       ----------------------------------------------------- */

    for (uint8_t i = 0; i < 5; i++)
    {
        /*
         * Wit   = lage ADC-waarde
         * Zwart = hoge ADC-waarde
         */

        if (sensor[i] > LINE_THRESHOLD)
        {
            weighted_sum +=
                    (int32_t)sensor[i] *
                    (int32_t)position[i];

            total_signal += sensor[i];
        }
    }


    /* -----------------------------------------------------
       Geen zwarte lijn gevonden
       ----------------------------------------------------- */

    if (total_signal == 0U)
    {
        return last_position;
    }


    /* -----------------------------------------------------
       Gewogen gemiddelde berekenen
       ----------------------------------------------------- */

    last_position =
            (int16_t)(
                weighted_sum /
                (int32_t)total_signal
            );


    /* -----------------------------------------------------
       Correctie mechanisch midden

       S2 + S3 vormen gewenste middenpositie.
       ----------------------------------------------------- */

    last_position += 163;


    return last_position;
}

