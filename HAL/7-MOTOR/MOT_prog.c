/**************************************************************/
/**************************************************************/
/*********		Author: Mahmoud Hafez		*******************/
/*********		File: MOT_prog.c			*******************/
/*********		Version: 1.00				*******************/
/**************************************************************/
/**************************************************************/

#include "std_types.h"
#include "MOT_interface.h"
#include "DIO_interface.h"



uint8 MOT_u8Init(Mot_st_t *Copy_stMot)
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_stMot== NULL)
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	else
	{
		DIO_u8SetPinDirection(Copy_stMot->u8ControlePort1, Copy_stMot->u8ControlePin1, DIO_u8PIN_OUTPUT);
		DIO_u8SetPinDirection(Copy_stMot->u8ControlePort2, Copy_stMot->u8ControlePin2, DIO_u8PIN_OUTPUT);
	}
	return Local_u8ErrorState;
}
uint8 MOT_u8RotateCW(Mot_st_t const *Copy_stMot)
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_stMot== NULL)
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	else
	{
		DIO_u8SetPinValue(Copy_stMot->u8ControlePort1, Copy_stMot->u8ControlePin1, DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_stMot->u8ControlePort2, Copy_stMot->u8ControlePin2, DIO_u8PIN_HIGH);
	}
	return Local_u8ErrorState;
}
uint8 MOT_u8RotateCCW(Mot_st_t const *Copy_stMot)
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_stMot == NULL)
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	else
	{
		DIO_u8SetPinValue(Copy_stMot->u8ControlePort2, Copy_stMot->u8ControlePin2, DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_stMot->u8ControlePort1, Copy_stMot->u8ControlePin1, DIO_u8PIN_HIGH);
	}
	return Local_u8ErrorState;
}
uint8 MOT_u8Stop(Mot_st_t const *Copy_stMot)
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_stMot== NULL)
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	else
	{
		DIO_u8SetPinValue(Copy_stMot->u8ControlePort2, Copy_stMot->u8ControlePin2, DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_stMot->u8ControlePort1, Copy_stMot->u8ControlePin1, DIO_u8PIN_HIGH);
	}
	return Local_u8ErrorState;
}

