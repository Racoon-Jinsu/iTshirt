/*
 * eeprom.h
 *
 *  Created on: 2025. 12. 8.
 *      Author: parkjinsu
 */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_


#include "stm32f0xx_hal.h"
#include "stm32f0xx_hal_i2c.h"
int WriteByte(I2C_HandleTypeDef *hi2c1,uint16_t MemAddress,uint8_t *pData,int size);
int ReadByte(I2C_HandleTypeDef *hi2c1,uint16_t MemAddress,int size);
int WritePage(I2C_HandleTypeDef *hi2c1,uint16_t MemAddress,uint8_t *pData,int size);
int ReadPage(I2C_HandleTypeDef *hi2c1,uint16_t MemAddress,int size);
void Verify(I2C_HandleTypeDef *hi2c1,uint16_t MemAddress, uint16_t size);


#endif /* INC_EEPROM_H_ */
