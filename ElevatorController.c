#include "ElevatorController.h"

#ifdef _RTE_
#include "RTE_Components.h"             // Component selection
#endif

int emergencyStopEnabled = 0;
int timer10SecondBool = 0;
int busyBool = 0;
int timedFloor = 0;
int currentFloor = 0;
int desiredFloor = 0;
Stack serviceStack;

int ElevatorController_ExecBool = 1;

static TIM_HandleTypeDef TIM13_Handle;

osThreadId tid_ElevatorControllerThread;                           			// thread id
osThreadDef (ElevatorControllerThread, osPriorityIdle, 1, 512);   	// thread object

int Init_ElevatorControllerThread () {
  tid_ElevatorControllerThread = osThreadCreate (osThread(ElevatorControllerThread), NULL);
  if (!tid_ElevatorControllerThread) return(-1);
  
	//init serviceStack
	stackInit(&serviceStack);
	
	initialize10SecondTimer();
		
  return(0);
}

void setElevatorController_ExecBool(int argument){
	ElevatorController_ExecBool = argument;
}

void ElevatorController_Exec(int argument) {
	setGPIOController_ExecBool(1);
	setSensorController_ExecBool(1);
		
	//set sensor detected floor to currentFloor. comment out next line for debug simulation testing
	currentFloor = getSensorDetectedFloor();
	sevenSegmentOutput(currentFloor);
	
	if(currentFloor == desiredFloor){
		//set motor to stop
		setGPIOController_MotorControlBool(10800);
		
		if(timedFloor != currentFloor){
			start10SecondTimer();
		}
		
		if(get10SecondBool() == 0){			//timer has finished
			timedFloor = currentFloor;
			
			desiredFloor = stackPop(&serviceStack);
			if(desiredFloor == 0xFFFFFFFF){
				desiredFloor = currentFloor;
			}
		}else{
			
		}
		
	}
	
	if(currentFloor > desiredFloor){
		//set motor direction
		setGPIOController_DirectionBool(0);
		//set motor to on
		setGPIOController_MotorControlBool(0);
		//set busy bool
		setBusyBool(1);
	}
	
	if(currentFloor < desiredFloor){
		//set motor direction
		setGPIOController_DirectionBool(1);
		//set motor to on
		setGPIOController_MotorControlBool(0);
		//set busy bool
		setBusyBool(1);
	}
		
	//10 second timer catch
	if(TIM13->CNT >= 0x5555){
		set10SecondBool(0);
		timedFloor = currentFloor;
		HAL_TIM_Base_Stop(&TIM13_Handle);
		HAL_TIM_Base_Init(&TIM13_Handle);
	}else{
		//do nothing
	}
}

void ElevatorController_ExecIdle(void) {
  osDelay(1);
}

void ElevatorControllerThread (void const *argument) {	
	while (1) {
		ElevatorController_Exec(ElevatorController_ExecBool);
				
		ElevatorController_ExecIdle();
	}
}

void sevenSegmentOutput(int argument){
	//switch case implementation
	switch(argument){
		case 0:
			setGPIOController_SevenSegmentMSB(0);
			setGPIOController_SevenSegmentLSB(0);
			break;
		case 1:
			setGPIOController_SevenSegmentMSB(0);
			setGPIOController_SevenSegmentLSB(1);
			break;
		case 2:
			setGPIOController_SevenSegmentMSB(1);
			setGPIOController_SevenSegmentLSB(0);
			break;
		case 3:
			setGPIOController_SevenSegmentMSB(1);
			setGPIOController_SevenSegmentLSB(1);
			break;
	}	
	
	//if statements implementation
	
}

void initialize10SecondTimer()
{
	static TIM_ClockConfigTypeDef TIM13_ClockSourceConfig;

	/* Internal clock is set to 216MHz. This makes the TIM13 clock 108MHZ. */
	//uint32_t internalFrequency = 108000000;
	uint32_t prescaler = 50000;

	uint32_t timerPeriod = 43199;

	TIM13_Handle.Instance = TIM13;
	TIM13_Handle.Init.Prescaler = prescaler;
	TIM13_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	TIM13_Handle.Init.Period = timerPeriod;
	TIM13_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	//TIM13_Handle.Init.RepetitionCounter = 0;

	HAL_TIM_Base_MspInit(&TIM13_Handle);

	__HAL_RCC_TIM13_CLK_ENABLE();

	TIM13_ClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	HAL_TIM_ConfigClockSource(&TIM13_Handle, &TIM13_ClockSourceConfig);

	HAL_TIM_Base_Init(&TIM13_Handle);

}

void start10SecondTimer(){
	HAL_TIM_Base_Start(&TIM13_Handle);
	set10SecondBool(1);
}

int addToServiceStack(int floorLevel){
	//if the top of the stack does not contain the current floor or the floor level to be added
	
	if(stackTop(&serviceStack) != floorLevel){
	//if(stackTop(&serviceStack) != floorLevel && desiredFloor != floorLevel){
		return stackPush(&serviceStack, floorLevel);
	}
	
	return -1;
}

int getEmergencyStop(){
	return emergencyStopEnabled;
}

void setEmergencyStop(int enabled){
	if(emergencyStopEnabled != enabled){
		emergencyStopEnabled = enabled;
	}
}

int getBusyBool(){
	return busyBool;
}

void setBusyBool(int enabled){
	busyBool = enabled;
}

void set10SecondBool(int enabled){
	timer10SecondBool = enabled;
}

int get10SecondBool(){
	return timer10SecondBool;
}

int getCurrentFloor(){
	return currentFloor;
}

int setCurrentFloor(int floor){
	currentFloor = floor;
	
	return getCurrentFloor();
}
