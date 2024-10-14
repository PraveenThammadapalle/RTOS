/*
 * main.c
 *
 *  Created on: 2024 Oct 14 11:20:07
 *  Author: Admin
 */




#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */
TaskHandle_t xHandle_1,xHandle_2;

static void sensortask_1(void *pvparameters);
static void sensortask_2(void *pvparameters);

void DAVE_Initialsisation(void);

int main(void)
{

	DAVE_Initialsisation();

	BaseType_t status;

	status = xTaskCreate(sensortask_1,"sensortask_1",1024,NULL,5,&xHandle_1);

	configASSERT(status == pdPASS);

	status = xTaskCreate(sensortask_2,"sensortask_2",1024,NULL,5,&xHandle_2);

	configASSERT(status == pdPASS);

	   vTaskStartScheduler();
}

static  void sensortask_1(void *pvparameters)
{
	uint8_t Send_Data[] = "Task-1 from Infineon\r\n";
	while(1)
	{

		UART_Transmit(&UART_0, Send_Data, sizeof(Send_Data)-1);
            taskYIELD();
	}
}

static  void sensortask_2(void *pvparameters)
{
	uint8_t Send_Data[] = "Task-2 from Infineon\r\n";
	while(1)
	{

		UART_Transmit(&UART_0, Send_Data, sizeof(Send_Data)-1);
		taskYIELD();
	}
}

void DAVE_Initialsisation(void){

DAVE_STATUS_t status;

status = DAVE_Init();           /* Initialization of DAVE APPs  */

if (status != DAVE_STATUS_SUCCESS)
{
  /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
  XMC_DEBUG("DAVE APPs initialization failed\n");

  while(1U)
  {

  }
}

}



