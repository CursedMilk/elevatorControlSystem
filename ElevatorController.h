#include "Stack.h"
#include "GPIOController.h"
#include "SensorController.h"
#include "cmsis_os.h"

int addToServiceStack(int floorLevel);
int getEmergencyStop(void);
void setEmergencyStop(int enabled);
int getBusyBool(void);
void setBusyBool(int enabled);
int get10SecondBool(void);
void set10SecondBool(int enabled);

void start10SecondTimer(void);

int getCurrentFloor(void);
int setCurrentFloor(int floorLevel);

void sevenSegmentOutput(int argument);

void initialize10SecondTimer(void);

void ElevatorControllerThread (void const *argument);             	// thread function
int Init_ElevatorControllerThread (void);														// thread function

void setElevatorController_ExecBool(int argument);									// set bool (int)
void setElevatorController_DirectionBool(int argument);							// set bool (int)

void ElevatorController_Exec(int argument);													// 
void ElevatorController_Direction(int argument);										// 
void ElevatorController_ExecIdle(void);															// 
