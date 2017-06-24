
#include "AT24C02.h"
#include "stm32f10x_i2c.h"

void AT24C02_Write(I2C_TypeDef* I2Cx, unsigned char AddressDevice, unsigned char AddressByte, unsigned char Value)
{
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
	I2C_AcknowledgeConfig(I2Cx, ENABLE);

	I2C_GenerateSTART(I2Cx, ENABLE);
	while( !I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB) ); // wait Generate Start

	I2C_Send7bitAddress(I2Cx, AddressDevice, I2C_Direction_Transmitter);
	while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) ); // wait send Address

	I2C_SendData(I2Cx, AddressByte);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); // wait send Address Byte

	I2C_SendData(I2Cx, Value);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); // wait Send Value for Byte

	I2C_GenerateSTOP(I2Cx, ENABLE);
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF)); // wait Generate Stop
};

unsigned char AT24C02_Read(I2C_TypeDef* I2Cx, unsigned char AddressDevice, unsigned char AddressByte)
{
	unsigned char ReceiveData = 0;

	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
	I2C_GenerateSTART(I2Cx, ENABLE);
	while( !I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB) ); // wait Generate Start

	I2C_Send7bitAddress(I2Cx, AddressDevice, I2C_Direction_Transmitter);
	while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) ); // wait send Address Device

	I2C_SendData(I2Cx, AddressByte);
	while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED) ); // wait send Address Byte

	I2C_GenerateSTART(I2Cx, ENABLE);
	while( !I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB) ); // wait Generate Start

	I2C_Send7bitAddress(I2Cx, AddressDevice, I2C_Direction_Receiver);
	while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) ); // wait Send Address Device As Receiver

	while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) ); // wait Receive a Byte
	ReceiveData = I2C_ReceiveData(I2Cx);

	I2C_NACKPositionConfig(I2Cx, I2C_NACKPosition_Current); // send not acknowledge
	I2C_AcknowledgeConfig(I2Cx, DISABLE);// disable acknowledge

	I2C_GenerateSTOP(I2Cx, ENABLE);
	while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF)); // wait Generate Stop Condition

	I2C_AcknowledgeConfig(I2Cx, DISABLE);// disable acknowledge

	return ReceiveData;
};
