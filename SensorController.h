#include "GPIOController.h"
#include "cmsis_os.h"

void setSensorDetectedFloor(int argument);
void setSensorDetectedCall(int argument);
void setSensorDetectedSend(int argument);
void triggerEmergencyStop(int argument);

int getSensorDetectedFloor(void);
int getSensorDetectedCall(void);
int getSensorDetectedSend(void);

void SensorControllerThread (void const *argument);             	// thread function
int Init_SensorControllerThread (void);														// thread function

void setSensorController_ExecBool(int argument);									// set bool (int)

void SensorController_Exec(void);																	// 
void SensorController_ExecIdle(void);															// 
