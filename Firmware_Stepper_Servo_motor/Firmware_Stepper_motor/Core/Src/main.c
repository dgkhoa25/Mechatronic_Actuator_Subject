/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stepper_motor.h"
#include "Button.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum
{
	init,
	stop,
	start
} system_state_t;

typedef enum
{
	init_,
	wave_step,
	full_step,
	half_step
} stepper_motor_sys_t;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

// Khai bao doi tuong STEPPER MOTOR
stepper_motor_t stepper_1;

// Khai bao toc do mac dinh
uint16_t speed = 4;

// Khai bao cac nut nhan cho che do Polling
Button_Typdef nut3, nut4;

// Khai tao trang thai mac dinh cua toan he thong: init, stop, start
system_state_t sys_state = init;

// Khai bao trang thai cua 3 che do: Wave, Full, Half
stepper_motor_sys_t stepper_state;

// Khoi tao bien giu chieu quay cua Stepper Motor
uint8_t dir = 0;

// Khoi tao bien giu chieu cua toc do 
uint8_t speed_sign = 1;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// ----------- Xu li nut nhan bang P.P Interrupt cho cac che do ------------- //
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	
	switch (GPIO_Pin)
	{
		case GPIO_PIN_3:
		{
			sys_state = stop;
			break;
		}
		case GPIO_PIN_4:
		{
			if (sys_state == stop)
			{
				sys_state = start;
			}
			break;
		}
		case GPIO_PIN_7:
		{
			if (sys_state == stop)
			{
				stepper_state = wave_step;
			}
			break;
		}
		case GPIO_PIN_8:
		{
			if (sys_state == stop)
			{
				stepper_state = full_step;
			}
			break;
		}
		case GPIO_PIN_9:
		{
			if (sys_state == stop)
			{
				stepper_state = half_step;
			}
			break;
		}
	}
}

// ----------------------------------------------------------------- //

// ------------Xu li phim nhan bang P.P polling -------------------- //
void	btn_pressing_callback(Button_Typdef *ButtonX)
{
	if (ButtonX == &nut3)
	{
		if (sys_state == stop)
		{
			dir =!dir;
		}
	}
	if (ButtonX == &nut4)
	{
		if (sys_state == stop)
		{
			speed_sign = !speed_sign;
			if (speed_sign)
			{
				speed = 4;
			}
			else
			{
				speed = 1;
			}
		}
	}
}
// ----------------------------------------------------------------- //

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
	
	// Khoi tao STEPPER MOTOR
	stepper_init(&stepper_1, &htim2, TIM_CHANNEL_1, TIM_CHANNEL_2, TIM_CHANNEL_3, TIM_CHANNEL_4);
	// Khoi tao nut nhan DIR, SPEED
	button_init(&nut3, GPIOB, GPIO_PIN_5);
	button_init(&nut4, GPIOB, GPIO_PIN_6);
	// Khoi tao trang thai mac dinh
	sys_state = stop;
	stepper_state = init_;
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
		// Thuc thi cac che do tuong ung Wave, Full, Half
		if (sys_state == start && stepper_state == wave_step)
		{
			stepper_wave_step_mode(&stepper_1, (stepper_dir_t)dir, speed); // 3
		}
		else if (sys_state == start && stepper_state == full_step)
		{
			stepper_full_step_mode(&stepper_1, (stepper_dir_t)dir, speed);	// 1
		}
		else if (sys_state == start && stepper_state == half_step)
		{
			stepper_half_step_mode(&stepper_1, (stepper_dir_t)dir, 8 + speed);
		}
		
		// Polling nut nhan DIR, SPEED
		button_handle(&nut3);
		button_handle(&nut4);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
