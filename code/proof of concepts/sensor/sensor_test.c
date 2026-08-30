#include <stdint.h>

/* =========================================================
   SENSOR PROOF OF CONCEPT
   STM32F103C8T6 + 6x TCRT5000

   Doel:
   - 6 sensoren onafhankelijk uitlezen
   - analoge A0-uitgang gebruiken
   - ruwe ADC-waarden bewaren
   - geen calibratie
   - geen normalisatie
   - geen interpolatie

   Pinmapping:

   Sensor 1 -> PA0 -> ADC1_IN0
   Sensor 2 -> PA1 -> ADC1_IN1
   Sensor 3 -> PA4 -> ADC1_IN4
   Sensor 4 -> PA5 -> ADC1_IN5
   Sensor 5 -> PA6 -> ADC1_IN6
   Sensor 6 -> PA7 -> ADC1_IN7
   ========================================================= */


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
   GLOBAL VARIABLES

   Ruwe ADC-waarden van de zes sensoren.

   Deze kunnen tijdens debug rechtstreeks bekeken worden.
   ========================================================= */

volatile uint16_t sensor[6];


/* =========================================================
   ADC INITIALISATIE
   ========================================================= */

static void Sensors_Init(void)
{
    /* -----------------------------------------------------
       GPIOA en ADC1 clock inschakelen
       ----------------------------------------------------- */

    RCC_APB2ENR |= (1U << 2);   /* GPIOA */
    RCC_APB2ENR |= (1U << 9);   /* ADC1 */


    /* -----------------------------------------------------
       Sensorpinnen als analog input instellen

       MODE = 00
       CNF  = 00
       ----------------------------------------------------- */

    /* PA0 */
    GPIOA_CRL &= ~(0xFU << 0);

    /* PA1 */
    GPIOA_CRL &= ~(0xFU << 4);

    /* PA4 */
    GPIOA_CRL &= ~(0xFU << 16);

    /* PA5 */
    GPIOA_CRL &= ~(0xFU << 20);

    /* PA6 */
    GPIOA_CRL &= ~(0xFU << 24);

    /* PA7 */
    GPIOA_CRL &= ~(0xFU << 28);


    /* -----------------------------------------------------
       ADC clock

       ADCPRE = 10
       PCLK2 / 6
       ----------------------------------------------------- */

    RCC_CFGR &= ~(0x3U << 14);

    RCC_CFGR |= (0x2U << 14);


    /* -----------------------------------------------------
       Sampling time maximaal instellen.

       Langere sampling time geeft een stabiele meting.
       ----------------------------------------------------- */

    ADC1_SMPR2 |= (0x7U << 0);   /* ADC channel 0 */
    ADC1_SMPR2 |= (0x7U << 3);   /* ADC channel 1 */

    ADC1_SMPR2 |= (0x7U << 12);  /* ADC channel 4 */
    ADC1_SMPR2 |= (0x7U << 15);  /* ADC channel 5 */
    ADC1_SMPR2 |= (0x7U << 18);  /* ADC channel 6 */
    ADC1_SMPR2 |= (0x7U << 21);  /* ADC channel 7 */


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

    ADC1_CR2 |= (0x7U << 17);

    ADC1_CR2 |= (1U << 20);


    /* Kleine wachttijd na ADC enable */
    for (volatile uint32_t i = 0; i < 10000U; i++)
    {
    }


    /* -----------------------------------------------------
       ADC calibration reset
       ----------------------------------------------------- */

    ADC1_CR2 |= (1U << 3);

    while (ADC1_CR2 & (1U << 3))
    {
    }


    /* -----------------------------------------------------
       ADC calibreren
       ----------------------------------------------------- */

    ADC1_CR2 |= (1U << 2);

    while (ADC1_CR2 & (1U << 2))
    {
    }
}


/* =========================================================
   READ ONE ADC CHANNEL
   ========================================================= */

static uint16_t Sensors_ReadADC(uint8_t channel)
{
    /* Gewenst ADC-kanaal selecteren */
    ADC1_SQR3 = channel;


    /* Softwareconversie starten */
    ADC1_CR2 |= (1U << 22);


    /* Wachten op End Of Conversion */
    while (!(ADC1_SR & (1U << 1)))
    {
    }


    /* Ruwe 12-bit ADC-waarde teruggeven */
    return (uint16_t)ADC1_DR;
}


/* =========================================================
   READ ALL SIX SENSORS
   ========================================================= */

static void Sensors_ReadAll(void)
{
    /*
     * Iedere sensor wordt afzonderlijk uitgelezen.
     *
     * De waarden worden rechtstreeks opgeslagen.
     * Er wordt geen verdere verwerking uitgevoerd.
     */

    sensor[0] = Sensors_ReadADC(0);   /* S1 -> PA0 */

    sensor[1] = Sensors_ReadADC(1);   /* S2 -> PA1 */

    sensor[2] = Sensors_ReadADC(4);   /* S3 -> PA4 */

    sensor[3] = Sensors_ReadADC(5);   /* S4 -> PA5 */

    sensor[4] = Sensors_ReadADC(6);   /* S5 -> PA6 */

    sensor[5] = Sensors_ReadADC(7);   /* S6 -> PA7 */
}


/* =========================================================
   MAIN
   ========================================================= */

int main(void)
{
    /* ADC en sensoren initialiseren */
    Sensors_Init();


    while (1)
    {
        /*
         * Alle zes sensoren continu onafhankelijk uitlezen.
         *
         * De waarden sensor[0] t.e.m. sensor[5]
         * kunnen rechtstreeks in de debugger bekeken worden.
         */

        Sensors_ReadAll();
    }
}
