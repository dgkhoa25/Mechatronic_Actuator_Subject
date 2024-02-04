#include "stepper_motor.h"

// Timer 1 to create Delay uS
extern TIM_HandleTypeDef htim1;

// Create Delay with micro second (uS)
static void delay_us(uint16_t time_delay_us)
{
	HAL_TIM_Base_Stop(&htim1);
	htim1.Instance->CNT = 0;
	HAL_TIM_Base_Start(&htim1);
	while (htim1.Instance->CNT < time_delay_us)
	{
		
	}
}

/* ----------------------- STEPPER MOTOR IN WAVE STEP MODE ----------------------------- */
void stepper_wave_step_mode(stepper_motor_t *motor, stepper_dir_t dir,uint16_t time_delay)
{
// WAVE STEP
	switch (dir)
	{
		case FORWARD_MODE:	// Quay cung chieu kim dong ho
		{
			for (int i = 0; i < 4; i++)
			{
				switch(i)
				{
					case 0:
					{
						motor->tim->Instance->CCR1 = 999;	// A+
						motor->tim->Instance->CCR2 = 0;		// A-
						motor->tim->Instance->CCR3 = 0;		// B+
						motor->tim->Instance->CCR4 = 0;		// B-
						break;
					}
					case 1:
					{
						motor->tim->Instance->CCR1 = 0;
						motor->tim->Instance->CCR2 = 0;
						motor->tim->Instance->CCR3 = 999;
						motor->tim->Instance->CCR4 = 0;
						break;
					}
					case 2:
					{
						motor->tim->Instance->CCR1 = 0;
						motor->tim->Instance->CCR2 = 999;
						motor->tim->Instance->CCR3 = 0;
						motor->tim->Instance->CCR4 = 0;
						break;
					}
					case 3:
					{
						motor->tim->Instance->CCR1 = 0;
						motor->tim->Instance->CCR2 = 0;
						motor->tim->Instance->CCR3 = 0;
						motor->tim->Instance->CCR4 = 999;
						break;
					}
				}
			HAL_Delay(time_delay); // 1 [Tan so chuyen cuon(coil)]
			}		
			break;
		}
		case REVERSE_MODE:	// Quay nguoc chieu kim dong ho
		{
			for (int i = 0; i < 4; i++)
			{
				switch(i)
				{
					case 0:
					{
						motor->tim->Instance->CCR1 = 0;
						motor->tim->Instance->CCR2 = 0;
						motor->tim->Instance->CCR3 = 0;
						motor->tim->Instance->CCR4 = 999;
						break;
					}
					case 1:
					{
						motor->tim->Instance->CCR1 = 0;
						motor->tim->Instance->CCR2 = 999;
						motor->tim->Instance->CCR3 = 0;
						motor->tim->Instance->CCR4 = 0;
						break;
					}
					case 2:
					{
						motor->tim->Instance->CCR1 = 0;
						motor->tim->Instance->CCR2 = 0;
						motor->tim->Instance->CCR3 = 999;
						motor->tim->Instance->CCR4 = 0;
						break;
					}
					case 3:
					{
						motor->tim->Instance->CCR1 = 999;
						motor->tim->Instance->CCR2 = 0;
						motor->tim->Instance->CCR3 = 0;
						motor->tim->Instance->CCR4 = 0;
						break;
					}
				}
			HAL_Delay(time_delay); // 1
			}		
			break;
		}
	}
}
/* ------------------------------------------------------------------------------------- */

/* ----------------------- STEPPER MOTOR IN FULL STEP MODE ----------------------------- */
void stepper_full_step_mode(stepper_motor_t *motor, stepper_dir_t dir, uint16_t time_delay)
{
// FULL STEP
	switch (dir)
	{
		case FORWARD_MODE:
		{
			for (int i  = 0; i < 4; i++)
			{
				switch (i)
				{
					case 0:
					{
						motor->tim->Instance->CCR1 = 999;			// A+
						motor->tim->Instance->CCR2 = 0;				// A-
						motor->tim->Instance->CCR3 = 999;			// B+
						motor->tim->Instance->CCR4 = 0;				// B-
						break;
					}
					case 1:
					{
						motor->tim->Instance->CCR1 = 0;	
						motor->tim->Instance->CCR2 = 999;
						motor->tim->Instance->CCR3 = 999;
						motor->tim->Instance->CCR4 = 0;
						break;
					}
					case 2:
					{
						motor->tim->Instance->CCR1 = 0;
						motor->tim->Instance->CCR2 = 999;
						motor->tim->Instance->CCR3 = 0;
						motor->tim->Instance->CCR4 = 999;
						break;
					}
					case 3:
					{
						motor->tim->Instance->CCR1 = 999;
						motor->tim->Instance->CCR2 = 0;
						motor->tim->Instance->CCR3 = 0;
						motor->tim->Instance->CCR4 = 999;
						break;
					}
				}
				HAL_Delay(time_delay); // 3
			}
			break;
		}
		case REVERSE_MODE:
		{
			for (int i  = 0; i < 4; i++)
			{
				switch (i)
				{
					case 0:
					{
						motor->tim->Instance->CCR1 = 0;			// A+
						motor->tim->Instance->CCR2 = 999;		// A-
						motor->tim->Instance->CCR3 = 0;			// B+
						motor->tim->Instance->CCR4 = 999;		// B-
						break;
					}
					case 1:
					{
						motor->tim->Instance->CCR1 = 0;	
						motor->tim->Instance->CCR2 = 999;
						motor->tim->Instance->CCR3 = 999;
						motor->tim->Instance->CCR4 = 0;
						break;
					}
					case 2:
					{
						motor->tim->Instance->CCR1 = 999;
						motor->tim->Instance->CCR2 = 0;
						motor->tim->Instance->CCR3 = 999;
						motor->tim->Instance->CCR4 = 0;
						break;
					}
					case 3:
					{
						motor->tim->Instance->CCR1 = 999;
						motor->tim->Instance->CCR2 = 0;
						motor->tim->Instance->CCR3 = 0;
						motor->tim->Instance->CCR4 = 999;
						break;
					}
				}
				HAL_Delay(time_delay); // 3
			}
			break;
		}
	}	
}
/* ------------------------------------------------------------------------------------- */

/* ----------------------- STEPPER MOTOR IN HALF STEP MODE ----------------------------- */
void stepper_half_step_mode(stepper_motor_t *motor, stepper_dir_t dir, uint16_t time_delay)
{
// HALF STEP
	switch (dir)
	{
		case FORWARD_MODE:
		{
			for (int i = 0; i < 8; i++)
			{
				switch (i)
				{
					case 0:
					{
						motor->tim->Instance->CCR1 = 999;		// A+
						motor->tim->Instance->CCR2 = 0;			// A-
						motor->tim->Instance->CCR3 = 0;			// B+
						motor->tim->Instance->CCR4 = 0;			// B-
						break;
					}
					case 1:
					{
						motor->tim->Instance->CCR1 = 999;
						motor->tim->Instance->CCR2 = 0;
						motor->tim->Instance->CCR3 = 999;
						motor->tim->Instance->CCR4 = 0;
						break;
					}
					case 2:
					{
						motor->tim->Instance->CCR1 = 0;
						motor->tim->Instance->CCR2 = 0;
						motor->tim->Instance->CCR3 = 999;
						motor->tim->Instance->CCR4 = 0;
						break;
					}
					case 3:
					{
						motor->tim->Instance->CCR1 = 0;
						motor->tim->Instance->CCR2 = 999;
						motor->tim->Instance->CCR3 = 999;
						motor->tim->Instance->CCR4 = 0;
						break;
					}
					case 4:
					{
						motor->tim->Instance->CCR1 = 0;
						motor->tim->Instance->CCR2 = 999;
						motor->tim->Instance->CCR3 = 0;
						motor->tim->Instance->CCR4 = 0;
						break;
					}
					case 5:
					{
						motor->tim->Instance->CCR1 = 0;
						motor->tim->Instance->CCR2 = 999;
						motor->tim->Instance->CCR3 = 0;
						motor->tim->Instance->CCR4 = 999;
						break;
					}
					case 6:
					{
						motor->tim->Instance->CCR1 = 0;
						motor->tim->Instance->CCR2 = 0;
						motor->tim->Instance->CCR3 = 0;
						motor->tim->Instance->CCR4 = 999;
						break;
					}
					case 7:
					{
						motor->tim->Instance->CCR1 = 999;
						motor->tim->Instance->CCR2 = 0;
						motor->tim->Instance->CCR3 = 0;
						motor->tim->Instance->CCR4 = 999;
						break;
					}
				}
		//		HAL_Delay(time_delay);
				delay_us(time_delay*100);
			}
			break;
		}
		case REVERSE_MODE:
		{
			for (int i = 0; i < 8; i++)
			{
				switch (i)
				{
					case 0:
					{
						motor->tim->Instance->CCR1 = 0;
						motor->tim->Instance->CCR2 = 0;
						motor->tim->Instance->CCR3 = 0;
						motor->tim->Instance->CCR4 = 999;
						break;
					}
					case 1:
					{
						motor->tim->Instance->CCR1 = 0;
						motor->tim->Instance->CCR2 = 999;
						motor->tim->Instance->CCR3 = 0;
						motor->tim->Instance->CCR4 = 999;
						break;
					}
					case 2:
					{
						motor->tim->Instance->CCR1 = 0;
						motor->tim->Instance->CCR2 = 999;
						motor->tim->Instance->CCR3 = 0;
						motor->tim->Instance->CCR4 = 0;
						break;
					}
					case 3:
					{
						motor->tim->Instance->CCR1 = 0;
						motor->tim->Instance->CCR2 = 999;
						motor->tim->Instance->CCR3 = 999;
						motor->tim->Instance->CCR4 = 0;
						break;
					}
					case 4:
					{
						motor->tim->Instance->CCR1 = 0;
						motor->tim->Instance->CCR2 = 0;
						motor->tim->Instance->CCR3 = 999;
						motor->tim->Instance->CCR4 = 0;
						break;
					}
					case 5:
					{
						motor->tim->Instance->CCR1 = 999;
						motor->tim->Instance->CCR2 = 0;
						motor->tim->Instance->CCR3 = 999;
						motor->tim->Instance->CCR4 = 0;
						break;
					}
					case 6:
					{
						motor->tim->Instance->CCR1 = 999;
						motor->tim->Instance->CCR2 = 0;
						motor->tim->Instance->CCR3 = 0;
						motor->tim->Instance->CCR4 = 0;
						break;
					}
					case 7:
					{
						motor->tim->Instance->CCR1 = 999;
						motor->tim->Instance->CCR2 = 0;
						motor->tim->Instance->CCR3 = 0;
						motor->tim->Instance->CCR4 = 999;
						break;
					}
				}
		//		HAL_Delay(time_delay);
				delay_us(time_delay*100);
			}
			break;
		}
	}
}
/* --------------------------------------------------------------------------------- */

/* ----------------------- STEPPER MOTOR INITITIALIZED ----------------------------- */
void stepper_init(stepper_motor_t *motor, TIM_HandleTypeDef *_tim, uint16_t _channel1,\
									uint16_t _channel2, uint16_t _channel3, uint16_t _channel4)
{
	motor->tim = _tim;
	motor->channel_1 = _channel1;
	motor->channel_2 = _channel2;
	motor->channel_3 = _channel3;
	motor->channel_4 = _channel4;
	HAL_TIM_PWM_Start(motor->tim, motor->channel_1);
	HAL_TIM_PWM_Start(motor->tim, motor->channel_2);
	HAL_TIM_PWM_Start(motor->tim, motor->channel_3);
	HAL_TIM_PWM_Start(motor->tim, motor->channel_4);
}
/* -------------------------------------------------------------------------------- */

