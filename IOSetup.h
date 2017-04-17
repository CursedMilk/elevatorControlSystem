/*
	UNALLOCATED				C6		Serial6 TX	
							C7		Serial6 RX
							B9		D14
							B8		D15
							
	//OUTPUTS
	MOTORDIRECTIONPIN		B14		D12
	MOTORSTARTPIN			B15		D11
	MOTORBUSYPIN			I1		D13
	SEVENSEGMENTMSBPIN		A15		D9
	SEVENSEGMENTLSBPIN		A8		D10
	
	//INPUTS
	SENSORFLOOR3PIN				F8		A3
	SENSORFLOOR2PIN				F9		A2
	SENSORFLOOR1PIN				F10		A1
	SENSORFLOOR0PIN				A0		A0
	CALLFLOOR3PIN				B4		D3
	CALLFLOOR2PIN				G6		D2
	CALLFLOOR1PIN				F6		A5
	CALLFLOOR0PIN				F7		A4
	CAGESEND3PIN				I3		D7
	CAGESEND2PIN				H6		D6
	CAGESEND1PIN				I0		D5
	CAGESEND0PIN				G7		D4
	EMERGENCYSTOPPIN			I2		D8
*/

/* Clock enables */
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();
}

/* outputs */
{
	//MOTOR DIRECTION
	GPIO_InitStruct.Pin				=	GPIO_PIN_14;
	GPIO_InitStruct.Mode			= GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull			=	GPIO_PULLDOWN;
	GPIO_InitStruct.Speed			= GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	//MOTOR START
	//Configured in main() to set up to timer 12

	//SEVEN SEGMENT MSB
	GPIO_InitStruct.Pin				=	GPIO_PIN_15;
	GPIO_InitStruct.Mode			= GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull			=	GPIO_PULLDOWN;
	GPIO_InitStruct.Speed			= GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	//SEVEN SEGMENT LSB
	GPIO_InitStruct.Pin				=	GPIO_PIN_8;
	GPIO_InitStruct.Mode			= GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull			=	GPIO_PULLDOWN;
	GPIO_InitStruct.Speed			= GPIO_SPEED_LOW;
HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/* inputs */
{
	//MOTOR BUSY
	GPIO_InitStruct.Pin				=	GPIO_PIN_1;
	GPIO_InitStruct.Mode			= GPIO_MODE_INPUT;
	//GPIO_InitStruct.Pull			=	GPIO_PULLDOWN;
	GPIO_InitStruct.Speed			= GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

	//SENSOR FLOOR 3
	GPIO_InitStruct.Pin				=	GPIO_PIN_8;
	GPIO_InitStruct.Mode			= GPIO_MODE_INPUT;
	//GPIO_InitStruct.Pull			=	GPIO_PULLDOWN;
	GPIO_InitStruct.Speed			= GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	//SENSOR FLOOR 2
	GPIO_InitStruct.Pin				=	GPIO_PIN_9;
	GPIO_InitStruct.Mode			= GPIO_MODE_INPUT;
	//GPIO_InitStruct.Pull			=	GPIO_PULLDOWN;
	GPIO_InitStruct.Speed			= GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	//SENSOR FLOOR 1
	GPIO_InitStruct.Pin				=	GPIO_PIN_10;
	GPIO_InitStruct.Mode			= GPIO_MODE_INPUT;
	//GPIO_InitStruct.Pull			=	GPIO_PULLDOWN;
	GPIO_InitStruct.Speed			= GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	//SENSOR FLOOR 0
	GPIO_InitStruct.Pin				=	GPIO_PIN_0;
	GPIO_InitStruct.Mode			= GPIO_MODE_INPUT;
	//GPIO_InitStruct.Pull			=	GPIO_PULLDOWN;
	GPIO_InitStruct.Speed			= GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	//CALL FLOOR 3
	GPIO_InitStruct.Pin				=	GPIO_PIN_4;
	GPIO_InitStruct.Mode			= GPIO_MODE_INPUT;
	//GPIO_InitStruct.Pull			=	GPIO_PULLDOWN;
	GPIO_InitStruct.Speed			= GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	//CALL FLOOR 2
	GPIO_InitStruct.Pin				=	GPIO_PIN_6;
	GPIO_InitStruct.Mode			= GPIO_MODE_INPUT;
	//GPIO_InitStruct.Pull			=	GPIO_PULLDOWN;
	GPIO_InitStruct.Speed			= GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	//CALL FLOOR 1
	GPIO_InitStruct.Pin				=	GPIO_PIN_6;
	GPIO_InitStruct.Mode			= GPIO_MODE_INPUT;
	//GPIO_InitStruct.Pull			=	GPIO_PULLDOWN;
	GPIO_InitStruct.Speed			= GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	//CALL FLOOR 0
	GPIO_InitStruct.Pin				=	GPIO_PIN_7;
	GPIO_InitStruct.Mode			= GPIO_MODE_INPUT;
	//GPIO_InitStruct.Pull			=	GPIO_PULLDOWN;
	GPIO_InitStruct.Speed			= GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	//SEND FLOOR 3
	GPIO_InitStruct.Pin				=	GPIO_PIN_3;
	GPIO_InitStruct.Mode			= GPIO_MODE_INPUT;
	//GPIO_InitStruct.Pull			=	GPIO_PULLDOWN;
	GPIO_InitStruct.Speed			= GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

	//SEND FLOOR 2
	GPIO_InitStruct.Pin				=	GPIO_PIN_6;
	GPIO_InitStruct.Mode			= GPIO_MODE_INPUT;
	//GPIO_InitStruct.Pull			=	GPIO_PULLDOWN;
	GPIO_InitStruct.Speed			= GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

	//SEND FLOOR 1
	GPIO_InitStruct.Pin				=	GPIO_PIN_0;
	GPIO_InitStruct.Mode			= GPIO_MODE_INPUT;
	//GPIO_InitStruct.Pull			=	GPIO_PULLDOWN;
	GPIO_InitStruct.Speed			= GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

	//SEND FLOOR 0
	GPIO_InitStruct.Pin				=	GPIO_PIN_7;
	GPIO_InitStruct.Mode			= GPIO_MODE_INPUT;
	//GPIO_InitStruct.Pull			=	GPIO_PULLDOWN;
	GPIO_InitStruct.Speed			= GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	//EMERGENCY STOP
	GPIO_InitStruct.Pin				=	GPIO_PIN_2;
	GPIO_InitStruct.Mode			= GPIO_MODE_INPUT;
	//GPIO_InitStruct.Pull			=	GPIO_PULLDOWN;
	GPIO_InitStruct.Speed			= GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
}
