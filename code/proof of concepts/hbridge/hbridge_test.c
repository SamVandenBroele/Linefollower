#include <stdint.h>

/* =========================================================
   H-BRIDGE PROOF OF CONCEPT
   STM32F103C8T6 + TB6612FNG

   Doel:
   - aantonen dat beide motoren onafhankelijk werken
   - draairichting kunnen wijzigen
   - snelheid regelen met PWM

   Pinmapping:
   Motor A:
   PWMA -> PA8
   AIN1 -> PB13
   AIN2 -> PB12

   Motor B:
   PWMB -> PB3
   BIN1 -> PB15
   BIN2 -> PA9

   STBY -> PB14
   ========================================================= */


/* =========================================================
   REGISTER DEFINITIES
   ========================================================= */

#define RCC_APB2ENR   (*(volatile uint32_t *)0x40021018)
#define RCC_APB1ENR   (*(volatile uint32_t *)0x4002101C)

#define AFIO_MAPR     (*(volatile uint32_t *)0x40010004)

#define GPIOA_CRL     (*(volatile uint32_t *)0x40010800)
#define GPIOA_CRH     (*(volatile uint32_t *)0x40010804)
#define GPIOA_BSRR    (*(volatile uint32_t *)0x40010810)
#define GPIOA_BRR     (*(volatile uint32_t *)0x40010814)

#define GPIOB_CRL     (*(volatile uint32_t *)0x40010C00)
#define GPIOB_CRH     (*(volatile uint32_t *)0x40010C04)
#define GPIOB_BSRR    (*(volatile uint32_t *)0x40010C10)
#define GPIOB_BRR     (*(volatile uint32_t *)0x40010C14)

#define TIM1_CR1      (*(volatile uint32_t *)0x40012C00)
#define TIM1_CCMR1    (*(volatile uint32_t *)0x40012C18)
#define TIM1_CCER     (*(volatile uint32_t *)0x40012C20)
#define TIM1_PSC      (*(volatile uint32_t *)0x40012C28)
#define TIM1_ARR      (*(volatile uint32_t *)0x40012C2C)
#define TIM1_CCR1     (*(volatile uint32_t *)0x40012C34)
#define TIM1_BDTR     (*(volatile uint32_t *)0x40012C44)

#define TIM2_CR1      (*(volatile uint32_t *)0x40000000)
#define TIM2_CCMR1    (*(volatile uint32_t *)0x40000018)
#define TIM2_CCER     (*(volatile uint32_t *)0x40000020)
#define TIM2_PSC      (*(volatile uint32_t *)0x40000028)
#define TIM2_ARR      (*(volatile uint32_t *)0x4000002C)
#define TIM2_CCR2     (*(volatile uint32_t *)0x40000038)


/* =========================================================
   DELAY
   ========================================================= */

static void delay(volatile uint32_t count)
{
    while (count--)
    {
        __asm volatile ("nop");
    }
}


/* =========================================================
   MOTOR INITIALISATIE
   ========================================================= */

static void Motors_Init(void)
{
    /* GPIOA, GPIOB, AFIO en TIM1 clock */
    RCC_APB2ENR |= (1U << 0);
    RCC_APB2ENR |= (1U << 2);
    RCC_APB2ENR |= (1U << 3);
    RCC_APB2ENR |= (1U << 11);

    /* TIM2 clock */
    RCC_APB1ENR |= (1U << 0);

    /*
     * JTAG uitschakelen, SWD behouden.
     * Nodig omdat PB3 anders door JTAG gebruikt wordt.
     */
    AFIO_MAPR &= ~(7U << 24);
    AFIO_MAPR |=  (2U << 24);

    /*
     * TIM2 partial remap:
     * TIM2_CH2 -> PB3
     */
    AFIO_MAPR &= ~(3U << 8);
    AFIO_MAPR |=  (1U << 8);


    /* -----------------------------------------------------
       PA8 = TIM1_CH1 = PWMA
       Alternate function push-pull
       ----------------------------------------------------- */

    GPIOA_CRH &= ~(0xFU << 0);
    GPIOA_CRH |=  (0xBU << 0);


    /* -----------------------------------------------------
       PA9 = BIN2
       General purpose push-pull output
       ----------------------------------------------------- */

    GPIOA_CRH &= ~(0xFU << 4);
    GPIOA_CRH |=  (0x3U << 4);


    /* -----------------------------------------------------
       PB3 = TIM2_CH2 = PWMB
       Alternate function push-pull
       ----------------------------------------------------- */

    GPIOB_CRL &= ~(0xFU << 12);
    GPIOB_CRL |=  (0xBU << 12);


    /* -----------------------------------------------------
       PB12 = AIN2
       PB13 = AIN1
       PB14 = STBY
       PB15 = BIN1
       ----------------------------------------------------- */

    GPIOB_CRH &= ~(0xFFFFU << 16);

    GPIOB_CRH |= (0x3U << 16);   /* PB12 */
    GPIOB_CRH |= (0x3U << 20);   /* PB13 */
    GPIOB_CRH |= (0x3U << 24);   /* PB14 */
    GPIOB_CRH |= (0x3U << 28);   /* PB15 */


    /* -----------------------------------------------------
       TIM1 PWM - Motor A
       ----------------------------------------------------- */

    TIM1_PSC = 0;
    TIM1_ARR = 999;

    TIM1_CCMR1 &= ~(0xFFU);
    TIM1_CCMR1 |= (6U << 4);
    TIM1_CCMR1 |= (1U << 3);

    TIM1_CCER |= (1U << 0);

    /* Main output enable */
    TIM1_BDTR |= (1U << 15);

    TIM1_CCR1 = 0;

    TIM1_CR1 |= (1U << 7);
    TIM1_CR1 |= (1U << 0);


    /* -----------------------------------------------------
       TIM2 PWM - Motor B
       ----------------------------------------------------- */

    TIM2_PSC = 0;
    TIM2_ARR = 999;

    TIM2_CCMR1 &= ~(0xFFU << 8);
    TIM2_CCMR1 |= (6U << 12);
    TIM2_CCMR1 |= (1U << 11);

    TIM2_CCER |= (1U << 4);

    TIM2_CCR2 = 0;

    TIM2_CR1 |= (1U << 7);
    TIM2_CR1 |= (1U << 0);


    /* TB6612 uit standby halen */
    GPIOB_BSRR = (1U << 14);
}


/* =========================================================
   MOTOR A
   ========================================================= */

static void MotorA_SetSpeed(int16_t speed)
{
    if (speed > 1000)
        speed = 1000;

    if (speed < -1000)
        speed = -1000;


    if (speed > 0)
    {
        /* Vooruit */

        GPIOB_BRR  = (1U << 13);
        GPIOB_BSRR = (1U << 12);

        TIM1_CCR1 = (uint16_t)speed;
    }

    else if (speed < 0)
    {
        /* Achteruit */

        GPIOB_BSRR = (1U << 13);
        GPIOB_BRR  = (1U << 12);

        TIM1_CCR1 = (uint16_t)(-speed);
    }

    else
    {
        /* Stop */

        GPIOB_BRR = (1U << 13);
        GPIOB_BRR = (1U << 12);

        TIM1_CCR1 = 0;
    }
}


/* =========================================================
   MOTOR B
   ========================================================= */

static void MotorB_SetSpeed(int16_t speed)
{
    if (speed > 1000)
        speed = 1000;

    if (speed < -1000)
        speed = -1000;


    if (speed > 0)
    {
        /* Vooruit */

        GPIOB_BRR  = (1U << 15);
        GPIOA_BSRR = (1U << 9);

        TIM2_CCR2 = (uint16_t)speed;
    }

    else if (speed < 0)
    {
        /* Achteruit */

        GPIOB_BSRR = (1U << 15);
        GPIOA_BRR  = (1U << 9);

        TIM2_CCR2 = (uint16_t)(-speed);
    }

    else
    {
        /* Stop */

        GPIOB_BRR = (1U << 15);
        GPIOA_BRR = (1U << 9);

        TIM2_CCR2 = 0;
    }
}


/* =========================================================
   MAIN - PROOF OF CONCEPT
   ========================================================= */

int main(void)
{
    Motors_Init();

    while (1)
    {
        /*
         * TEST 1
         * Beide motoren vooruit op lage snelheid
         */

        MotorA_SetSpeed(300);
        MotorB_SetSpeed(300);

        delay(4000000);


        /*
         * STOP
         */

        MotorA_SetSpeed(0);
        MotorB_SetSpeed(0);

        delay(2000000);


        /*
         * TEST 2
         * Beide motoren achteruit
         */

        MotorA_SetSpeed(-300);
        MotorB_SetSpeed(-300);

        delay(4000000);


        /*
         * STOP
         */

        MotorA_SetSpeed(0);
        MotorB_SetSpeed(0);

        delay(2000000);


        /*
         * TEST 3
         * Motor A afzonderlijk
         */

        MotorA_SetSpeed(400);
        MotorB_SetSpeed(0);

        delay(3000000);


        /*
         * TEST 4
         * Motor B afzonderlijk
         */

        MotorA_SetSpeed(0);
        MotorB_SetSpeed(400);

        delay(3000000);


        /*
         * TEST 5
         * Verschillende snelheden
         */

        MotorA_SetSpeed(500);
        MotorB_SetSpeed(250);

        delay(4000000);


        /*
         * STOP
         */

        MotorA_SetSpeed(0);
        MotorB_SetSpeed(0);

        delay(3000000);
    }
}
