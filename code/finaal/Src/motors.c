#include <stdint.h>
#include "motors.h"

/* =========================================================
   REGISTER DEFINITIONS
   ========================================================= */

/* RCC */
#define RCC_APB2ENR    (*(volatile uint32_t *)0x40021018)
#define RCC_APB1ENR    (*(volatile uint32_t *)0x4002101C)

/* AFIO */
#define AFIO_MAPR      (*(volatile uint32_t *)0x40010004)

/* GPIOA */
#define GPIOA_CRH      (*(volatile uint32_t *)0x40010804)
#define GPIOA_BSRR     (*(volatile uint32_t *)0x40010810)
#define GPIOA_BRR      (*(volatile uint32_t *)0x40010814)

/* GPIOB */
#define GPIOB_CRL      (*(volatile uint32_t *)0x40010C00)
#define GPIOB_CRH      (*(volatile uint32_t *)0x40010C04)
#define GPIOB_BSRR     (*(volatile uint32_t *)0x40010C10)
#define GPIOB_BRR      (*(volatile uint32_t *)0x40010C14)

/* TIM1 */
#define TIM1_CR1       (*(volatile uint32_t *)0x40012C00)
#define TIM1_EGR       (*(volatile uint32_t *)0x40012C14)
#define TIM1_CCMR1     (*(volatile uint32_t *)0x40012C18)
#define TIM1_CCER      (*(volatile uint32_t *)0x40012C20)
#define TIM1_PSC       (*(volatile uint32_t *)0x40012C28)
#define TIM1_ARR       (*(volatile uint32_t *)0x40012C2C)
#define TIM1_CCR1      (*(volatile uint32_t *)0x40012C34)
#define TIM1_BDTR      (*(volatile uint32_t *)0x40012C44)

/* TIM2 */
#define TIM2_CR1       (*(volatile uint32_t *)0x40000000)
#define TIM2_EGR       (*(volatile uint32_t *)0x40000014)
#define TIM2_CCMR1     (*(volatile uint32_t *)0x40000018)
#define TIM2_CCER      (*(volatile uint32_t *)0x40000020)
#define TIM2_PSC       (*(volatile uint32_t *)0x40000028)
#define TIM2_ARR       (*(volatile uint32_t *)0x4000002C)
#define TIM2_CCR2      (*(volatile uint32_t *)0x40000038)


/* =========================================================
   MOTOR INITIALISATIE
   ========================================================= */

void Motors_Init(void)
{
    /* Klokken inschakelen */
    RCC_APB2ENR |= (1U << 0);     /* AFIO */
    RCC_APB2ENR |= (1U << 2);     /* GPIOA */
    RCC_APB2ENR |= (1U << 3);     /* GPIOB */
    RCC_APB2ENR |= (1U << 11);    /* TIM1 */

    RCC_APB1ENR |= (1U << 0);     /* TIM2 */


    /* JTAG uitschakelen, SWD behouden */
    AFIO_MAPR &= ~(0x7U << 24);
    AFIO_MAPR |=  (0x2U << 24);


    /*
     * TIM2 partial remap
     * TIM2_CH2 -> PB3
     */
    AFIO_MAPR &= ~(0x3U << 8);
    AFIO_MAPR |=  (0x1U << 8);


    /* -----------------------------------------------------
       TB6612 direction pins
       ----------------------------------------------------- */

    /*
     * PB12 = AIN2
     * PB13 = AIN1
     * PB14 = STBY
     * PB15 = BIN1
     *
     * Output push-pull 2 MHz
     */
    GPIOB_CRH &= ~(0xFFFFU << 16);

    GPIOB_CRH |= (0x2U << 16);
    GPIOB_CRH |= (0x2U << 20);
    GPIOB_CRH |= (0x2U << 24);
    GPIOB_CRH |= (0x2U << 28);


    /* PA9 = BIN2 */
    GPIOA_CRH &= ~(0xFU << 4);
    GPIOA_CRH |=  (0x2U << 4);


    /* -----------------------------------------------------
       PWM pins
       ----------------------------------------------------- */

    /* PA8 -> TIM1_CH1 */
    GPIOA_CRH &= ~(0xFU << 0);
    GPIOA_CRH |=  (0xAU << 0);


    /* PB3 -> TIM2_CH2 */
    GPIOB_CRL &= ~(0xFU << 12);
    GPIOB_CRL |=  (0xAU << 12);


    /* -----------------------------------------------------
       TIM1 PWM - MOTOR A
       ----------------------------------------------------- */

    TIM1_PSC = 7;
    TIM1_ARR = 999;

    /* PWM mode 1 */
    TIM1_CCMR1 &= ~(0x7U << 4);
    TIM1_CCMR1 |=  (0x6U << 4);

    /* Preload */
    TIM1_CCMR1 |= (1U << 3);

    /* Channel 1 enable */
    TIM1_CCER |= (1U << 0);

    /* Main Output Enable */
    TIM1_BDTR |= (1U << 15);

    /* Update */
    TIM1_EGR |= (1U << 0);

    /* Start timer */
    TIM1_CR1 |= (1U << 0);


    /* -----------------------------------------------------
       TIM2 PWM - MOTOR B
       ----------------------------------------------------- */

    TIM2_PSC = 7;
    TIM2_ARR = 999;

    /* PWM mode 1 CH2 */
    TIM2_CCMR1 &= ~(0x7U << 12);
    TIM2_CCMR1 |=  (0x6U << 12);

    /* Preload */
    TIM2_CCMR1 |= (1U << 11);

    /* Channel 2 enable */
    TIM2_CCER |= (1U << 4);

    /* Update */
    TIM2_EGR |= (1U << 0);

    /* Start timer */
    TIM2_CR1 |= (1U << 0);


    /* Motor driver activeren */
    Motors_Enable();

    /* Veilig starten met motoren stil */
    Motors_Stop();
}


/* =========================================================
   MOTOR A
   Positieve snelheid = VOORUIT
   ========================================================= */

void MotorA_SetSpeed(int16_t speed)
{
    if (speed > 1000)
        speed = 1000;

    if (speed < -1000)
        speed = -1000;


    if (speed > 0)
    {
        /* vooruit */
        GPIOB_BRR  = (1U << 13);
        GPIOB_BSRR = (1U << 12);

        TIM1_CCR1 = (uint16_t)speed;
    }

    else if (speed < 0)
    {
        /* achteruit */
        GPIOB_BSRR = (1U << 13);
        GPIOB_BRR  = (1U << 12);

        TIM1_CCR1 = (uint16_t)(-speed);
    }

    else
    {
        /* stop / coast */
        GPIOB_BRR = (1U << 13);
        GPIOB_BRR = (1U << 12);

        TIM1_CCR1 = 0;
    }
}


/* =========================================================
   MOTOR B
   Positieve snelheid = VOORUIT
   ========================================================= */

void MotorB_SetSpeed(int16_t speed)
{
    if (speed > 1000)
        speed = 1000;

    if (speed < -1000)
        speed = -1000;


    if (speed > 0)
    {
        /* vooruit */
        GPIOB_BRR  = (1U << 15);
        GPIOA_BSRR = (1U << 9);

        TIM2_CCR2 = (uint16_t)speed;
    }

    else if (speed < 0)
    {
        /* achteruit */
        GPIOB_BSRR = (1U << 15);
        GPIOA_BRR  = (1U << 9);

        TIM2_CCR2 = (uint16_t)(-speed);
    }

    else
    {
        /* stop / coast */
        GPIOB_BRR = (1U << 15);
        GPIOA_BRR = (1U << 9);

        TIM2_CCR2 = 0;
    }
}


/* =========================================================
   STOP
   ========================================================= */

void Motors_Stop(void)
{
    MotorA_SetSpeed(0);
    MotorB_SetSpeed(0);
}


/* =========================================================
   STANDBY
   ========================================================= */

void Motors_Standby(void)
{
    /* STBY LOW */
    GPIOB_BRR = (1U << 14);
}


/* =========================================================
   ENABLE
   ========================================================= */

void Motors_Enable(void)
{
    /* STBY HIGH */
    GPIOB_BSRR = (1U << 14);
}

