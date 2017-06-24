
#include "stm32f10x.h"
#include "AT24C02.h"


void main(){
// set clock 18 MHz for MCU
	PLL_SRC_Sel(2);
	PLL_MUL(2);
	Src_Sys_Clk(3);
	AHB_Div(4);
	APB1_APB2_Div(1, 1);

// set Clocks Peripherals MCU
	SetPeriphAPB1(APB1_I2C1);
	SetPeriphAPB2(APB2_IOPB);
	SetPeriphAPB2(APB2_AFIO);

// config pins for I2C 
	Init_PIN(PORTB, PIN6, Config_Out_50MHz, Alter_Out_OD); //configuration out pin for I2C1 SCL
	Init_PIN(PORTB, PIN7, Config_Out_50MHz, Alter_Out_OD); //Configuration out pin for I2C1 SDA


// initialize I2C1
	I2C_Cmd(I2C1, ENABLE);
	I2C1_Init.I2C_Ack = I2C_Ack_Enable;
	I2C1_Init.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C1_Init.I2C_ClockSpeed = 40000;
	I2C1_Init.I2C_DutyCycle = I2C_DutyCycle_16_9;
	I2C1_Init.I2C_Mode = I2C_Mode_I2C;
	I2C1_Init.I2C_OwnAddress1 = 0x00;
	I2C_Init(I2C1, &I2C1_Init);
	I2C_Cmd(I2C1, ENABLE);

	AT24C02_Write(I2C1, 0xA0, 10, 123); //0xA0=> address device; 10=> address byte;123 => write value in address byte;
 	
	// wait >= 10ms

	unsigned char value = AT24C02_Read(I2C1, 0xA0, 10); //0xA0=> address device; 10=> address byte;

	while(1);
	
};
