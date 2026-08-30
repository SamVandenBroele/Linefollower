#include <stdint.h>

#include "sensors.h"
#include "motors.h"


/* =========================================================
   STM32F103C8T6 - LINE FOLLOWER

   LIJNVOLGER MET ROBUUSTE KRUISPUNTDETECTIE

   - normale lijnvolging
   - vertragen in bochten
   - kruispunt detecteren
   - kruispuntmodus vasthouden
   - altijd rechtdoor over kruispunt
   ========================================================= */


/* =========================================================
   INSTELLINGEN
   ========================================================= */

#define STRAIGHT_SPEED          300
#define CURVE_SPEED             150
#define CURVE_THRESHOLD         120

#define MAX_MOTOR_SPEED         600

/*
 * Vanaf 3 zwarte sensoren vermoeden we een kruispunt.
 */
#define CROSS_SENSOR_COUNT      3

/*
 * Na het detecteren van een kruispunt moet de robot
 * gedurende een aantal meetcycli weer een gewone lijn
 * zien voordat de kruispuntmodus wordt verlaten.
 */
#define CROSS_CLEAR_COUNT       300


/* =========================================================
   GLOBAL VARIABLES
   ========================================================= */

volatile int16_t line_position = 0;
volatile int16_t correction = 0;

volatile int16_t base_speed = 0;

volatile int16_t motor_a_speed = 0;
volatile int16_t motor_b_speed = 0;

volatile uint8_t black_sensor_count = 0;

volatile uint8_t crossing_mode = 0;
volatile uint16_t crossing_clear_counter = 0;


/* =========================================================
   MAIN
   ========================================================= */

int main(void)
{
    /* Sensoren initialiseren */
    Sensors_Init();

    /* Motorsturing initialiseren */
    Motors_Init();

    /* TB6612 inschakelen */
    Motors_Enable();

    /* Eerst stilstaan */
    Motors_Stop();


    /* =====================================================
       MAIN LOOP
       ===================================================== */

    while (1)
    {
        /* -------------------------------------------------
           Sensoren uitlezen
           ------------------------------------------------- */

        Sensors_ReadAll();


        /* -------------------------------------------------
           Zwarte sensoren tellen

           S5 = sensor[5] blijft voorlopig genegeerd.

           We gebruiken:
           S0
           S1
           S2
           S3
           S4
           ------------------------------------------------- */

        black_sensor_count = 0;

        for (uint8_t i = 0; i < 5; i++)
        {
            if (sensor[i] > LINE_THRESHOLD)
            {
                black_sensor_count++;
            }
        }


        /* =================================================
           KRUISPUNT DETECTEREN
           ================================================= */

        if (crossing_mode == 0)
        {
            /*
             * Kruispunt herkennen.
             *
             * Drie of meer sensoren tegelijk zwart
             * betekent dat de zwarte zone veel breder
             * is dan een normale lijn.
             */
            if (black_sensor_count >= CROSS_SENSOR_COUNT)
            {
                crossing_mode = 1;
                crossing_clear_counter = 0;
            }
        }


        /* =================================================
           KRUISPUNTMODUS
           ================================================= */

        if (crossing_mode == 1)
        {
            /*
             * Tijdens het volledige kruispunt:
             *
             * GEEN lijncorrectie.
             *
             * Beide motoren exact dezelfde snelheid,
             * zodat de robot rechtdoor blijft rijden.
             */

            motor_a_speed = STRAIGHT_SPEED;
            motor_b_speed = STRAIGHT_SPEED;

            MotorA_SetSpeed(motor_a_speed);
            MotorB_SetSpeed(motor_b_speed);


            /* ---------------------------------------------
               Controleren of kruispunt voorbij is
               --------------------------------------------- */

            if (black_sensor_count <= 2)
            {
                /*
                 * We zien weer iets dat op een normale
                 * lijn lijkt.
                 *
                 * Niet onmiddellijk terugschakelen.
                 * Eerst een aantal opeenvolgende cycli
                 * wachten.
                 */

                crossing_clear_counter++;

                if (crossing_clear_counter >= CROSS_CLEAR_COUNT)
                {
                    crossing_mode = 0;
                    crossing_clear_counter = 0;
                }
            }
            else
            {
                /*
                 * Nog altijd brede zwarte zone.
                 */

                crossing_clear_counter = 0;
            }
        }


        /* =================================================
           NORMALE LIJNVOLGING
           ================================================= */

        else
        {
            /* Positie zwarte lijn berekenen */

            line_position = Sensors_GetLinePosition();


            /* ---------------------------------------------
               Snelheid bepalen
               --------------------------------------------- */

            if ((line_position > CURVE_THRESHOLD) ||
                (line_position < -CURVE_THRESHOLD))
            {
                base_speed = CURVE_SPEED;
            }
            else
            {
                base_speed = STRAIGHT_SPEED;
            }


            /* ---------------------------------------------
               P-regeling

               correctie = 50% van lijnpositie
               --------------------------------------------- */

            correction =
                    (int16_t)(((int32_t)line_position) / 2);


            /* ---------------------------------------------
               Motorsnelheden
               --------------------------------------------- */

            motor_a_speed = base_speed + correction;
            motor_b_speed = base_speed - correction;


            /* ---------------------------------------------
               Motor A begrenzen
               --------------------------------------------- */

            if (motor_a_speed > MAX_MOTOR_SPEED)
            {
                motor_a_speed = MAX_MOTOR_SPEED;
            }

            if (motor_a_speed < 0)
            {
                motor_a_speed = 0;
            }


            /* ---------------------------------------------
               Motor B begrenzen
               --------------------------------------------- */

            if (motor_b_speed > MAX_MOTOR_SPEED)
            {
                motor_b_speed = MAX_MOTOR_SPEED;
            }

            if (motor_b_speed < 0)
            {
                motor_b_speed = 0;
            }


            /* ---------------------------------------------
               Motoren aansturen
               --------------------------------------------- */

            MotorA_SetSpeed(motor_a_speed);
            MotorB_SetSpeed(motor_b_speed);
        }
    }
}
