/*
 * Params.c
 *
 *  Created on: Oct 12, 2019
 *      Author: 16138
 */

#include "Params.h"
#include <stm32f1xx.h>
#include "UserCode/user_define.h"

params_t params = {
		.pid_whe0 = {
				.KP = 10,
				.KI = 0,
				.KD = 0,

				.minIpart = -1000,
				.maxIPart = 1000,
				.minDpart = -1000,
				.maxDPart = 1000,
				.minOut = -1000,
				.maxOut = 1000,

				.preIPart = 0,
				.preError = 0,
				.isFistCompute = true
		},

		.pid_whe1 = {
				.KP = 10,
				.KI = 0,
				.KD = 0,

				.minIpart = -1000,
				.maxIPart = 1000,
				.minDpart = -1000,
				.maxDPart = 1000,
				.minOut = -1000,
				.maxOut = 1000,

				.preIPart = 0,
				.preError = 0,
				.isFistCompute = true
		},

		.pid_sta = {
				.KP = 10,
				.KI = 0,
				.KD = 0,

				.minIpart = -1000,
				.maxIPart = 1000,
				.minDpart = -1000,
				.maxDPart = 1000,
				.minOut = -1000,
				.maxOut = 1000,

				.preIPart = 0,
				.preError = 0,
				.isFistCompute = true
		},

		.pid_rob = {
				.KP = 10,
				.KI = 0,
				.KD = 0,

				.minIpart = -1000,
				.maxIPart = 1000,
				.minDpart = -1000,
				.maxDPart = 1000,
				.minOut = -1000,
				.maxOut = 1000,

				.preIPart = 0,
				.preError = 0,
				.isFistCompute = true
		},

		.angle_ajusted = 0,
		.believe_in_gyro = 0.99,

		.gx_offset = 1,
		.gy_offset = 2,
		.gz_offset = 3
};

static uint32_t address = PARAMS_PAGE_ADDRESS;

static void write(uint32_t* ptr){
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, *ptr);
	address+=4;
}

static void read(uint32_t* ptr){
	*ptr = *((__IO uint32_t*)address);
	address+=4;
}

void params_save(){
	HAL_FLASH_Unlock();

	FLASH_EraseInitTypeDef EraseInitStruct;
	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = PARAMS_PAGE_ADDRESS;
	EraseInitStruct.NbPages     = 1;

	uint32_t PageError = 0;
	HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);

	address = PARAMS_PAGE_ADDRESS;

	uint32_t saved = HAVE_SAVED_DATA;
	write(&saved);

	// wheels pid
	write((uint32_t*)(&params.pid_whe0.KP));
	write((uint32_t*)(&params.pid_whe0.KI));
	write((uint32_t*)(&params.pid_whe0.KD));

	write((uint32_t*)(&params.pid_whe1.KP));
	write((uint32_t*)(&params.pid_whe1.KI));
	write((uint32_t*)(&params.pid_whe1.KD));

	// stability pid
	write((uint32_t*)(&params.pid_sta.KP));
	write((uint32_t*)(&params.pid_sta.KI));
	write((uint32_t*)(&params.pid_sta.KD));

	// robot pid
	write((uint32_t*)(&params.pid_rob.KP));
	write((uint32_t*)(&params.pid_rob.KI));
	write((uint32_t*)(&params.pid_rob.KD));

	// IMU
	write((uint32_t*)(&params.angle_ajusted));
	write((uint32_t*)(&params.believe_in_gyro));
	write((uint32_t*)(&params.gx_offset));
	write((uint32_t*)(&params.gy_offset));
	write((uint32_t*)(&params.gz_offset));
	HAL_FLASH_Lock();
}

bool params_load(){
	address = PARAMS_PAGE_ADDRESS;

	if((*(__IO uint32_t*) address) != HAVE_SAVED_DATA) return false;
	address+=4;

	// wheels pid
	read((uint32_t*)(&params.pid_whe0.KP));
	read((uint32_t*)(&params.pid_whe0.KI));
	read((uint32_t*)(&params.pid_whe0.KD));

	read((uint32_t*)(&params.pid_whe1.KP));
	read((uint32_t*)(&params.pid_whe1.KI));
	read((uint32_t*)(&params.pid_whe1.KD));

	// stability pid
	read((uint32_t*)(&params.pid_sta.KP));
	read((uint32_t*)(&params.pid_sta.KI));
	read((uint32_t*)(&params.pid_sta.KD));

	// robot pid
	read((uint32_t*)(&params.pid_rob.KP));
	read((uint32_t*)(&params.pid_rob.KI));
	read((uint32_t*)(&params.pid_rob.KD));

	// IMU
	read((uint32_t*)(&params.angle_ajusted));
	read((uint32_t*)(&params.believe_in_gyro));
	read((uint32_t*)(&params.gx_offset));
	read((uint32_t*)(&params.gy_offset));
	read((uint32_t*)(&params.gz_offset));

	return true;
}
