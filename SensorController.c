#include "SensorController.h"

extern void setEmergencyStop(int argument);
extern int getEmergencyStop(void);
extern void set10SecondBool(int argument);
extern int get10SecondBool(void);

extern int addToServiceStack(int argument);

#ifdef _RTE_
#include "RTE_Components.h"             // Component selection
#endif

int SensorController_ExecBool = NULL;
int sensorDetectedFloor = 0;
int sensorDetectedCall = 0;
int sensorDetectedSend = 0;

osThreadId tid_SensorControllerThread;                           			// thread id
osThreadDef (SensorControllerThread, osPriorityHigh, 1, 512);   	// thread object

int Init_SensorControllerThread () {
  tid_SensorControllerThread = osThreadCreate (osThread(SensorControllerThread), NULL);
  if (!tid_SensorControllerThread) return(-1);
  
  return(0);
}

void setSensorController_ExecBool(int argument){
	SensorController_ExecBool = argument;
}

void SensorController_Exec() {
	//Floor sensors
	if(GPIOReadPin(GPIOA, GPIO_PIN_0))
		setSensorDetectedFloor(0);
	if(GPIOReadPin(GPIOF, GPIO_PIN_10))
		setSensorDetectedFloor(1);
	if(GPIOReadPin(GPIOF, GPIO_PIN_9))
		setSensorDetectedFloor(2);
	if(GPIOReadPin(GPIOF, GPIO_PIN_8))
		setSensorDetectedFloor(3);
	
	//Floor calls
	if(GPIOReadPin(GPIOF, GPIO_PIN_7))
		setSensorDetectedCall(0);
	if(GPIOReadPin(GPIOF, GPIO_PIN_6))
		setSensorDetectedCall(1);
	if(GPIOReadPin(GPIOG, GPIO_PIN_6))
		setSensorDetectedCall(2);
	if(GPIOReadPin(GPIOB, GPIO_PIN_4))
		setSensorDetectedCall(3);
	
	//Floor sends
	if(GPIOReadPin(GPIOG, GPIO_PIN_7))
		setSensorDetectedSend(0);
	if(GPIOReadPin(GPIOI, GPIO_PIN_0))
		setSensorDetectedSend(1);
	if(GPIOReadPin(GPIOH, GPIO_PIN_6))
		setSensorDetectedSend(2);
	if(GPIOReadPin(GPIOI, GPIO_PIN_3))
		setSensorDetectedSend(3);
	
	//Emergency stop
	if(GPIOReadPin(GPIOI, GPIO_PIN_2))
		triggerEmergencyStop(1);
	
}

void SensorController_ExecIdle() {
  osDelay(1);
}

void SensorControllerThread (void const *argument) {
	while (1) {
    if(SensorController_ExecBool)
			SensorController_Exec();          
		
    SensorController_ExecIdle();             /* Nothing left to do for the moment ... Idle processing */
  }
}


void setSensorDetectedFloor(int argument){
	sensorDetectedFloor = argument;
}

void setSensorDetectedCall(int argument){
	sensorDetectedCall = argument;
	addToServiceStack(sensorDetectedCall);
}

void setSensorDetectedSend(int argument){
	sensorDetectedSend = argument;
	addToServiceStack(sensorDetectedSend);
}

void triggerEmergencyStop(int argument){
	setEmergencyStop(argument);
}


int getSensorDetectedFloor(){
	return sensorDetectedFloor;
}

int getSensorDetectedCall(){
	return sensorDetectedCall;
}

int getSensorDetectedSend(){
	return sensorDetectedSend;
}
