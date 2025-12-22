/*
 * eeprom.c
 *
 *  Created on: 2025. 12. 8.
 *      Author: parkjinsu
 */

#include "stm32f0xx_hal.h"
#include "stm32f0xx_hal_i2c.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>


#define SLAVE_AADR 0x53 << 1
#define I2C_BYTE 1
#define I2C_PAGE 4
uint8_t byte_data= 0x01;   //RX데이터 1바이트 버퍼
uint8_t page_data[4] = {0x01,0x01,0x01,0x01};

HAL_StatusTypeDef error = HAL_OK;

// 0x 00 01



// 접두사 + 기능 +  타겟

int WriteByte(I2C_HandleTypeDef *hi2c1,uint16_t MemAddress, uint8_t *pData, int size)
{


    if (HAL_I2C_Mem_Write(hi2c1,SLAVE_AADR, MemAddress, sizeof(MemAddress) ,pData,sizeof(*pData), HAL_MAX_DELAY) == HAL_OK)
    {
    	HAL_Delay(5);
        printf("Write Address: 0x%04x data: 0x%02x\r\n",MemAddress,*pData);
        return 0;
    }
    printf("Byte Write error\r\n");
    return -1;
}

int ReadByte(I2C_HandleTypeDef *hi2c1,uint16_t MemAddress, int size)
{



    if (HAL_I2C_Mem_Read(hi2c1,SLAVE_AADR, MemAddress, sizeof(MemAddress) ,&byte_data,sizeof(byte_data), HAL_MAX_DELAY) == HAL_OK)
    {
    	printf("Read Address: 0x%04x data: 0x%02x\r\n ",MemAddress,byte_data);
        return 0;
    }
    printf("Byte Read error\r\n");
    return -1;
}

int WritePage(I2C_HandleTypeDef *hi2c1,uint16_t MemAddress, uint8_t *pData,int size)
{
    if (HAL_I2C_Mem_Write(hi2c1,SLAVE_AADR, MemAddress, sizeof(MemAddress) ,pData,sizeof(*pData), HAL_MAX_DELAY) == HAL_OK)
    {
    	HAL_Delay(5);
        printf("Page Write Address: 0x%04x data: 0x%02x 0x%02x 0x%02x 0x%02x\r\n",MemAddress,*pData,*(pData+1),*(pData+2),*(pData+3));
        return 0;
    }
    printf("Page Write error\r\n");
    return -1;
}

int ReadPage(I2C_HandleTypeDef *hi2c1,uint16_t MemAddress,int size)
{


    if (HAL_I2C_Mem_Read(hi2c1,SLAVE_AADR, MemAddress, sizeof(MemAddress) ,page_data,sizeof(page_data), HAL_MAX_DELAY) == HAL_OK)
    {
    	printf("Read Address: 0x%04x Page Read data: 0x%02x 0x%02x 0x%02x 0x%02x \r\n",MemAddress,page_data[0],page_data[1],page_data[2],page_data[3]);
        return 0;
    }
    printf("Page Read error\r\n");
    return -1;
}

void Verify(I2C_HandleTypeDef *hi2c1,uint16_t MemAddress, uint16_t size)
{
	printf("****************************************\r\n");
	printf("Verify Start address: 0x%04x Size of Byte: 0x%02x\r\n",MemAddress,size);


	for(int i=0x0000; i<size; i++)
	{
		 printf("Read Address: 0x%04x ",MemAddress+i);
		 ReadByte(hi2c1,MemAddress+i,1);
	}

}
