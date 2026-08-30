#ifndef MOTORS_H_
#define MOTORS_H_

#include <stdint.h>

/* =========================
   MOTOR FUNCTIES
   ========================= */

/* Initialiseer TB6612FNG en PWM */
void Motors_Init(void);

/* Motor A snelheid
   speed: -1000 ... +1000
   negatief = achteruit
   positief = vooruit
   0 = stop
*/
void MotorA_SetSpeed(int16_t speed);

/* Motor B snelheid */
void MotorB_SetSpeed(int16_t speed);

/* Stop beide motoren */
void Motors_Stop(void);

/* Zet TB6612 in standby */
void Motors_Standby(void);

/* Activeer TB6612 */
void Motors_Enable(void);

#endif /* MOTORS_H_ */

