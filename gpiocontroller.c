#include "GPIOController.h"

#ifdef _RTE_
#include "RTE_Components.h"             // Component selection
#endif

int GPIOController_ExecBool;
int GPIOController_DirectionBool;
int GPIOController_MotorControlBool;

void GPIOControllerThread (void const *argument);             	// thread function
osThreadId tid_GPIOControllerThread;                           			// thread id
osThreadDef (GPIOControllerThread, osPriorityIdle, 1, 512);   	// thread object

int Init_GPIOControllerThread (void) {

  tid_GPIOControllerThread = osThreadCreate (osThread(GPIOControllerThread), NULL);
  if (!tid_GPIOControllerThread) return(-1);

  return(0);
}

void setGPIOController_ExecBool(int argument){
	GPIOController_ExecBool = argument;
}

void setGPIOController_DirectionBool(int argument){
	GPIOController_DirectionBool = argument;
}

void setGPIOController_MotorControlBool(int argument){
	GPIOController_MotorControlBool = argument;
}

void setGPIOController_SevenSegmentMSB(int argument){
	if(argument == 0){
		GPIOWritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
	}else{
		GPIOWritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
	}
}

void setGPIOController_SevenSegmentLSB(int argument){
	if(argument == 0){
		GPIOWritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
	}else{
		GPIOWritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
	}
}

void GPIOController_Exec(void) {
	//direction control	
	if(GPIOController_DirectionBool == 0){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	}
	else{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
	}
	
	//motor speed control
	TIM12->CCR2 = GPIOController_MotorControlBool;
}

void GPIOController_ExecIdle(void) {
  osDelay(1);
}

void GPIOControllerThread (void const *argument) {

	while (1) {
    if(GPIOController_ExecBool)
			GPIOController_Exec();

		GPIOController_ExecIdle();             /* Nothing left to do for the moment ... Idle processing */
  }
}

void GPIOWritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState){
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, PinState);
}

int GPIOReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_RESET){
		return 0;
	}
	
	return 1;
}

int getGPIOController_MotorControlBool(){
	return GPIOController_MotorControlBool;
}
