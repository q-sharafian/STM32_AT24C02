
#include "stm32f10x_i2c.h"

#ifndef AT24C02_H_
#define AT24C02_H_

void AT24C02_Write(I2C_TypeDef* I2Cx, unsigned char AddressDevice, unsigned char AddressByte, unsigned char Value);
unsigned char AT24C02_Read(I2C_TypeDef* I2Cx, unsigned char AddressDevice, unsigned char AddressByte);

#endif /* AT24C02_H_ */
