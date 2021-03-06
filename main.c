 /**
  ******************************************************************************
  * @file    Templates/Src/main.c
  * @author  MCD Application Team
  * @version V1.0.3
  * @date    22-April-2016
  * @brief   STM32F7xx HAL API Template project (with modifications from ARM)
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/*
 * This file contains modifications by ARM to provide it as User Code Template
 * within the STM32 Device Family Pack.
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32746g_discovery_sdram.h"  // Keil.STM32F746G-Discovery::Board Support:Drivers:SDRAM
#include "stm32f7xx_hal_tim.h"
#include "stm32f7xx_hal_tim_ex.h"
#include "GUI.h"
#include "Board_LED.h"                  // ::Board Support:LED
#include "GPIOController.h"							// GPIO Controller include - 3441 - 21/3/2017
#include "SensorController.h"						// Sensor Controller include - 3441 - 11/4/2017
#include "ElevatorController.h"					// Elevator Controller include - 3441 - 21/3/2017

extern int Init_GUIThread(void);
extern int Init_GPIOControllerThread(void);
extern int Init_ElevatorControllerThread(void);

GPIO_InitTypeDef GPIO_InitStruct;



#ifdef _RTE_
#include "RTE_Components.h"             // Component selection
#endif
#ifdef RTE_CMSIS_RTOS                   // when RTE component CMSIS RTOS is used
#include "cmsis_os.h"                   // CMSIS RTOS header file
#endif

#ifdef RTE_CMSIS_RTOS_RTX
extern uint32_t os_time;

uint32_t HAL_GetTick(void) {
  return os_time;
}
#endif

/** @addtogroup STM32F7xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);
static void MPU_Config(void);
static void CPU_CACHE_Enable(void);

/* Private functions ---------------------------------------------------------*/
/*
void SysTick_Handler(void)
{
    HAL_IncTick();
    HAL_SYSTICK_IRQHandler();
}*/

static TIM_HandleTypeDef TIM12_Handle;
static TIM_OC_InitTypeDef TIM12_OCConfig;
static TIM_ClockConfigTypeDef TIM12_ClockSourceConfig;

void InitializeTimer()
{
		/* Internal clock is set to 216MHz. This makes the tim12 clock 108MHZ. */
		uint32_t internalFrequency = 108000000;
		uint32_t desiredFrequency = 1000;
		uint32_t  prescaler = 9;

		uint32_t timerPeriod = ((internalFrequency / (prescaler + 1)) / desiredFrequency) - 1;
		/* 	This timerPeriod value cannot be higher than 65535 (16bit timer of timer12).
				If it is then the prescaler needs to be greater than 0

				timer_tick_frequency = internalFrequency / (prescaler + 1)
				timerPeriod = timer_tick_frequency / desiredFrequency - 1

				3441 - 29/3/2017
		*/

		TIM12_Handle.Instance = TIM12;
    TIM12_Handle.Init.Prescaler = prescaler;
    TIM12_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    TIM12_Handle.Init.Period = timerPeriod;
    TIM12_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    TIM12_Handle.Init.RepetitionCounter = 0;

		HAL_TIM_PWM_MspInit(&TIM12_Handle);

		__HAL_RCC_TIM12_CLK_ENABLE();

		__HAL_RCC_GPIOB_CLK_ENABLE();

		GPIO_InitStruct.Pin					=	GPIO_PIN_15;
		GPIO_InitStruct.Mode				= GPIO_MODE_AF_PP;
		//GPIO_InitStruct.Pull				=	GPIO_PULLDOWN;
		GPIO_InitStruct.Speed				= GPIO_SPEED_HIGH;
		GPIO_InitStruct.Alternate 	= GPIO_AF9_TIM12;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		TIM12_ClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
		HAL_TIM_ConfigClockSource(&TIM12_Handle, &TIM12_ClockSourceConfig);

		HAL_TIM_PWM_Init(&TIM12_Handle);

		TIM12_OCConfig.OCMode = TIM_OCMODE_PWM2;
		TIM12_OCConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
		int dutyPercentage = 50;
		TIM12_OCConfig.Pulse = ((timerPeriod + 1) / (100 / dutyPercentage)) - 1;

		HAL_TIM_PWM_ConfigChannel(&TIM12_Handle, &TIM12_OCConfig, TIM_CHANNEL_2);

		HAL_TIM_PWM_Start(&TIM12_Handle, TIM_CHANNEL_2);

}


/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* This project template calls firstly two functions in order to configure MPU feature
     and to enable the CPU Cache, respectively MPU_Config() and CPU_CACHE_Enable().
     These functions are provided as template implementation that User may integrate
     in his application, to enhance the performance in case of use of AXI interface
     with several masters. */

  /* Configure the MPU attributes as Write Through */
  MPU_Config();

  /* Enable the CPU Cache */
  CPU_CACHE_Enable();

#ifdef RTE_CMSIS_RTOS                   // when using CMSIS RTOS
  osKernelInitialize();                 // initialize CMSIS-RTOS
#endif

  /* STM32F7xx HAL library initialization:
       - Configure the Flash ART accelerator on ITCM interface
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  HAL_Init();
	BSP_SDRAM_Init();
  /* Configure the System clock to have a frequency of 216 MHz */
  SystemClock_Config();
	LED_Initialize();


	#ifdef RTE_CMSIS_RTOS                   // when using CMSIS RTOS
		// create 'thread' functions that start executing,
		// example: tid_name = osThreadCreate (osThread(name), NULL);
		Init_GPIOControllerThread();
		Init_SensorControllerThread();
		Init_GUIThread();
		Init_ElevatorControllerThread();
		
		osKernelStart();                      // start thread execution
	#endif


	//GPIO Clock Enables & Configs
	#include "IOSetup.h"
	
	//Timer 12 PWM initalization
	InitializeTimer();
	
		
  /* Infinite loop */
  while (1)
  {
		/*
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
		osDelay(500);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
		osDelay(1000);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
		osDelay(500);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
		osDelay(1000);

		HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, GPIO_PIN_SET);
		osDelay(500);
		HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, GPIO_PIN_RESET);
		osDelay(1000);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
		osDelay(500);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
		osDelay(1000);
		*/

		

		/*	To change the duty cycle of the pwm output */
		/*
		for(uint32_t i = 0; i < 10800; i=i+4){
			TIM12->CCR2 = i;
			osDelay(1);
		}
		*/
		
		/*
		
		
		if(0 == 1){
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
		}
		*/

		osDelay(1);
  }
}





/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 216000000
  *            HCLK(Hz)                       = 216000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 432
  *            PLL_P                          = 2
  *            PLL_Q                          = 9
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 7
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /* activate the OverDrive to reach the 216 Mhz Frequency */
  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while(1)
  {
  }
}

/**
  * @brief  Configure the MPU attributes as Write Through for SRAM1/2.
  * @note   The Base Address is 0x20010000 since this memory interface is the AXI.
  *         The Region Size is 256KB, it is related to SRAM1 and SRAM2  memory size.
  * @param  None
  * @retval None
  */
static void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct;

  /* Disable the MPU */
  HAL_MPU_Disable();

  /* Configure the MPU attributes as WT for SRAM */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x20010000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_256KB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Enable the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

/**
  * @brief  CPU L1-Cache enable.
  * @param  None
  * @retval None
  */
static void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
