/*
 * ADC_interface.h
 *
 *  Created on: Dec 13, 2022
 *      Author: Mahmoud Hafez
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#define ADC_SINGLE_ENDED_CH0              0u
#define ADC_SINGLE_ENDED_CH1              1u
#define ADC_SINGLE_ENDED_CH2              2u
#define ADC_SINGLE_ENDED_CH3              3u
#define ADC_SINGLE_ENDED_CH4              4u
#define ADC_SINGLE_ENDED_CH5              5u
#define ADC_SINGLE_ENDED_CH6              6u
#define ADC_SINGLE_ENDED_CH7              7u

typedef struct
{
	uint8 u8ChainSize;
	uint8 *pau8Channel;
	uint16 *pau16ResultArr;
	pfVoidFuncPtr ADC_pvNotificationFun;
}ADC_Chain_t;


/*static sint32 s32Remapping(sint32 Copy_s32InputRangeMin, sint32 Copy_s32InputRangeMax, sint32 Copy_s32OutputRangeMin,
							sint32 Copy_s32OutputRangeMax, sint32 Copy_s32InputValue);*/

extern ADC_Chain_t Global_stChainConversion;
void ADC_voidInit(void);

uint8 ADC_u16StartConversionSynch(uint8 Copy_u8Channel, uint16* Copy_pu16Result);
uint8 ADC_u8StartSingleConversionAsynch(uint8 Copy_u8Channel, uint16* Copy_pu16Result, pfVoidFuncPtr Copy_pvNotificationFun);
uint8 ADC_u8StartChainConversionAsynch(ADC_Chain_t *Copy_pstAdcChain);

#endif /* ADC_INTERFACE_H_ */
