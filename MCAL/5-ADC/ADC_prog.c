/*
 * ADC_prog.c
 *
 *  Created on: Dec 13, 2022
 *      Author: Mahmoud Hafez
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "defines.h"

#include "ADC_private.h"
#include "ADC_cfg.h"
#include "ADC_reg.h"
#include "ADC_interface.h"


static uint16* ADC_pu16ConversionResult = NULL;
/*Notification fun body example: read the output result after conversion*/
static pfVoidFuncPtr ADC_pvNotificationFun = NULL;
static uint8 ADC_u8BusyFlag = IDLE;
static uint8 ADC_u8ChainConversionType;

static ADC_Chain_t *ADC_pstChain = NULL;
static uint8 ADC_u8ChainCounter = 0;

void ADC_voidInit(void)
{
#if ADC_u8REF_VOLT == AREF_REF
	CLR_BIT(ADMUX, ADMUX_REFS0);
	CLR_BIT(ADMUX, ADMUX_REFS1);
#elif ADC_u8REF_VOLT == AVCC_REF
	SET_BIT(ADMUX, ADMUX_REFS0);
	CLR_BIT(ADMUX, ADMUX_REFS1);
#elif ADC_u8REF_VOLT == AREF_REF
	CLR_BIT(ADMUX, ADMUX_REFS0);
	CLR_BIT(ADMUX, ADMUX_REFS1);
#else
#error Wrong ADC_u8REF_VOLT configuration
#endif

#if ADC_u8RESOLUTION == EIGHT_BITS
	SET_BIT(ADMUX, ADMUX_ADLAR);
#elif ADC_u8RESOLUTION == TEN_BITS
	CLR_BIT(ADMUX, ADMUX_ADLAR);
#else
#error Wrong ADC_u8RESOLUTION configuration
#endif


#if ADC_u8INTERRUPT_ENABLE == DISABLE
	CLR_BIT(ADCSRA, ADCSRA_ADIE);
#elif ADC_u8INIT_ENABLE == ENABLE
	SET_BIT(ADCSRA, ADCSRA_ADIE);
#else
#error Wrong ADC_u8INIT_ENABLE configuration option
#endif


	/*configure prescaler bits*/
	ADCSRA &= PRESCALER_MASK;
	ADCSRA |= ADC_u8PRESCALER_VAL;

	/*ADC Enable*/
	SET_BIT(ADCSRA, ADCSRA_ADEN);
}


uint8 ADC_u16StartConversionSynch(uint8 Copy_u8Channel, uint16 * Copy_pu16Result)
{
	uint8 Local_u8ErrorState = OK;
	if (Copy_pu16Result != NULL)
	{
		if (ADC_u8BusyFlag == IDLE)
		{
			/*ADC is now busy*/
			ADC_u8BusyFlag = BUSY;
			uint32 Local_u32TimeoutCounter = 0;

			/*configure analog channel */
			ADMUX &= CHANNEL_MASK;
			ADMUX |= Copy_u8Channel;

			/*Start the conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*wait until the conversion is complete or the timeout is passed*/
			while((GET_BIT(ADCSRA, ADCSRA_ADIF) == 0) && (Local_u32TimeoutCounter < ADC_u32TIMOUT))
			{
				Local_u32TimeoutCounter++;
			}
			if (Local_u32TimeoutCounter >= ADC_u32TIMOUT)
			{
				/*Loop is broken because flag isn't raised until timeout is passed*/
				Local_u8ErrorState = TIMEOUT_ERR;
			}
			else
			{
				/*Loop is broken because flag is raised before the timeout is passed*/
				/*clear the conversion complete flag*/
				SET_BIT(ADCSRA, ADCSRA_ADIF);

#if ADC_u8RESOLUTION == EIGHT_BITS
				*Copy_pu16Result =  ADCH;
#elif ADC_u8RESOLUTION == TEN_BITS
				*Copy_pu16Result =  ADC;
#endif
				/*ADC is now IDLE*/
				ADC_u8BusyFlag = IDLE;
			}
		}
		else
		{
			/*ADC was busy, assign the error state*/
			Local_u8ErrorState = BUSY_STATE_ERR;
		}
	}
	else
	{

		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}


uint8 ADC_u8StartSingleConversionAsynch(uint8 Copy_u8Channel, uint16* Copy_pu16Result, pfVoidFuncPtr Copy_pvNotificationFun)
{
	uint8 Local_u8ErrorState = OK;

	if((Copy_pu16Result != NULL) && (Copy_pvNotificationFun != NULL))
	{
		if (ADC_u8BusyFlag == IDLE)
		{
			ADC_u8ChainConversionType = 0;
			ADC_u8BusyFlag = BUSY;

			/*Initialize the result pointer globally*/
			ADC_pu16ConversionResult = Copy_pu16Result;

			/*Initialize the result notification function globally*/
			ADC_pvNotificationFun = Copy_pvNotificationFun;

			/*configure analog channel */
			ADMUX &= CHANNEL_MASK;
			ADMUX |= Copy_u8Channel;

			/*Start the conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*Enable the ADC conversion complete  interrupt*/
			SET_BIT(ADCSRA, ADCSRA_ADIE);
		}
		else
		{
			Local_u8ErrorState = BUSY_STATE_ERR;
		}

	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

uint8 ADC_u8StartChainConversionAsynch(ADC_Chain_t *Copy_pstAdcChain)
{
	uint8 Local_u8ErrorState = OK;
	if (   Copy_pstAdcChain != NULL && Copy_pstAdcChain->ADC_pvNotificationFun != NULL && Copy_pstAdcChain->pau16ResultArr != NULL
			&& Copy_pstAdcChain->pau8Channel != NULL)
	{
		ADC_u8ChainConversionType = 1;
		if (ADC_u8BusyFlag == IDLE)
		{
			ADC_u8BusyFlag = BUSY;

			/*Initialize the global data*/
			ADC_pstChain = Copy_pstAdcChain;

			/*configure analog channel */
			ADMUX &= CHANNEL_MASK;
			ADMUX |= ADC_pstChain->pau8Channel[ADC_u8ChainCounter];

			/*Start the conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*Enable the ADC conversion complete  interrupt*/
			SET_BIT(ADCSRA, ADCSRA_ADIE);
		}
		else
		{
			Local_u8ErrorState = BUSY_STATE_ERR;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}


/**
 * @brief ADC chain conversion complete ISR
 */
void __vector_16 (void)  __attribute__((signal));
void __vector_16 (void)
{
	if (ADC_u8ChainConversionType == CHAIN_CONVERSION)
	{
		if(ADC_pstChain != NULL)
		{
#if ADC_u8RESOLUTION == EIGHT_BITS
			ADC_pstChain->pau16ResultArr[ADC_u8ChainCounter] =  ADCH;
#elif ADC_u8RESOLUTION == TEN_BITS
			ADC_pstChain->pau16ResultArr[ADC_u8ChainCounter] =  ADC;
#endif
			ADC_u8ChainCounter++;
			if(ADC_u8ChainCounter < ADC_pstChain->u8ChainSize)
			{
				/*configure analog channel */
				ADMUX &= CHANNEL_MASK;
				ADMUX |= ADC_pstChain->pau8Channel[ADC_u8ChainCounter];
				/*Start the conversion*/
				SET_BIT(ADCSRA, ADCSRA_ADSC);
			}
			else
			{
				/*ADC is now IDLE*/
				ADC_u8BusyFlag = IDLE;
				/*Disable the ADC conversion complete interrupt*/
				CLR_BIT(ADCSRA, ADCSRA_ADIE);

				ADC_u8ChainCounter = 0;
				/*Invoke the app notification fun*/
				if (ADC_pstChain->ADC_pvNotificationFun != NULL)
				{
					ADC_pstChain->ADC_pvNotificationFun();
				}
				else
				{
					/*Notification function pointer is NULL*/
				}
			}
		}
		else
		{
			/*Conversion result pointer is NULL*/
		}
	}
	else
	{
		/*Single conversion*/
		if(ADC_pu16ConversionResult != NULL)
		{

#if ADC_u8RESOLUTION == EIGHT_BITS
			*ADC_pu16ConversionResult =  ADCH;
#elif ADC_u8RESOLUTION == TEN_BITS
			*ADC_pu16ConversionResult =  ADC;
#endif
			/*Disable the ADC conversion complete interrupt*/
			CLR_BIT(ADCSRA, ADCSRA_ADIE);

			/*ADC is now IDLE*/
			ADC_u8BusyFlag = IDLE;

			/*Invoke the app notification fun*/
			if (ADC_pvNotificationFun != NULL)
			{
				ADC_pvNotificationFun();
			}
			else
			{
				/*Notification function pointer is NULL*/
			}
		}
		else
		{
			/*Conversion result pointer is NULL*/
		}
	}
}
