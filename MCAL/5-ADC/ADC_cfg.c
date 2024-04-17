/*
 * ADC_cfg.c
 *
 *  Created on: Jan 3, 2023
 *      Author: Mahmoud Hafez
 */

#include "std_types.h"

#include "CLCD_interface.h"

#include "ADC_interface.h"

uint8 Local_u8DigitalResult;
uint8 Local_u8DigitalResult1;
uint16 Local_u16Temperature;
uint16 Local_u16Res[2];
uint8 u8ChannelArr[] = {ADC_SINGLE_ENDED_CH0, ADC_SINGLE_ENDED_CH7};
static void App(void);

ADC_Chain_t Global_stChainConversion =
{
	.pau8Channel 		   = u8ChannelArr          ,
	.u8ChainSize 		   = 2                     ,
	.pau16ResultArr		   = Local_u16Res          ,
	.ADC_pvNotificationFun = App                   ,
};

void App(void)
{
		CLCD_voidGoToXY(0, 0);
		CLCD_voidSendNumber(Global_stChainConversion.pau16ResultArr[0]);
		CLCD_voidGoToXY(0, 1);
		CLCD_voidSendNumber(Global_stChainConversion.pau16ResultArr[1]);
}
