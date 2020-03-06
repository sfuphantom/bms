/*
 * sys_main.h
 *
 *  Created on: Feb 17, 2020
 *      Author: Mahmoud Ahmed
 */

#ifndef INCLUDE_SYS_MAIN_H_
#define INCLUDE_SYS_MAIN_H_

#define SIZE_OF_SLAVES_MSG  55
#define SIZE_OF_MULTI_SLAVES_MSG SIZE_OF_SLAVES_MSG*(TOTALBOARDS+1)

enum States{
        STATE_HANDLING = 0,
        RUNNING,
        SENSOR_READ,
        CAN_COMM,
        CHARGING,
        ERROR_HANDLING,
} STATE;

void my_sciInit(void);
void my_rtiInit(void);
void BMS_init(void);
void BMS_Read_Single(uint8_t device);
void BMS_Read_All(void);
void setBMSTimerPeriod(uint32 timems);
void Thermistor_Read(void);
int GetTimeout(void);

typedef struct CAN_MSG{

} CAN_MSG;

#endif /* INCLUDE_SYS_MAIN_H_ */
