#ifndef STEPPER_H
#define STEPPER_H

#include "stm32f1xx_hal.h"

// Cau truc luu giu che do chieu quay DIR
typedef enum
{
	FORWARD_MODE,
	REVERSE_MODE,
} stepper_dir_t;

// Cau truc luu giu thong tin 1 Stepper Motor
typedef struct
{
	TIM_HandleTypeDef *tim;
	uint16_t channel_1;
	uint16_t channel_2;
	uint16_t channel_3;
	uint16_t channel_4;
} stepper_motor_t;

// Declare prototype function
void stepper_init(stepper_motor_t *motor, TIM_HandleTypeDef *tim, uint16_t _channel1,\
									uint16_t channel2, uint16_t channel3, uint16_t channel4);

void stepper_wave_step_mode(stepper_motor_t *motor, stepper_dir_t mode,uint16_t time_delay);
void stepper_full_step_mode(stepper_motor_t *motor, stepper_dir_t mode, uint16_t time_delay);
void stepper_half_step_mode(stepper_motor_t *motor, stepper_dir_t mode, uint16_t time_delay);

#endif
