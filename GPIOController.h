/* Includes ------------------------------------------------------------------*/
#include "stm32746g_discovery_sdram.h"  // Keil.STM32F746G-Discovery::Board Support:Drivers:SDRAM
#include "stm32f7xx_hal_tim.h"
#include "stm32f7xx_hal_tim_ex.h"
#include "stm32f7xx_hal_gpio.h"
#include "cmsis_os.h"

void GPIOWritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
int GPIOReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

void setGPIOController_ExecBool(int argument);
void setGPIOController_DirectionBool(int argument);
void setGPIOController_MotorControlBool(int argument);

void setGPIOController_SevenSegmentMSB(int argument);
void setGPIOController_SevenSegmentLSB(int argument);

int getGPIOController_MotorControlBool(void);			//for debugging
