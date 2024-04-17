/**************************************************************/
/**************************************************************/
/*********		Author: Mahmoud Hafez		*******************/
/*********		File: MOT_prog.c			*******************/
/*********		Version: 1.00				*******************/
/**************************************************************/
/**************************************************************/

#include "std_types.h"
#include "util/delay.h"

#include "DIO_interface.h"

#include "STEPPERMOT_interface.h"
#include "STEPPERMOT_private.h"

#define FULL_ROTATION_ANGLE 360ul
#define FULL_ROTATION_STEPS 2048ul

static void voidActivateBlue(uint8 const Copy_u8Port)
{
	DIO_u8SetPinValue(Copy_u8Port, DIO_u8PIN3, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(Copy_u8Port, DIO_u8PIN2, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(Copy_u8Port, DIO_u8PIN1, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(Copy_u8Port, DIO_u8PIN0, DIO_u8PIN_LOW);
	_delay_ms(2);
}
static void voidActivatePink(uint8 const Copy_u8Port)
{
	DIO_u8SetPinValue(Copy_u8Port, DIO_u8PIN3, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(Copy_u8Port, DIO_u8PIN2, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(Copy_u8Port, DIO_u8PIN0, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(Copy_u8Port, DIO_u8PIN1, DIO_u8PIN_LOW);
	_delay_ms(2);
}
static void voidActivateYellow(uint8 const Copy_u8Port)
{
	DIO_u8SetPinValue(Copy_u8Port, DIO_u8PIN3, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(Copy_u8Port, DIO_u8PIN1, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(Copy_u8Port, DIO_u8PIN0, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(Copy_u8Port, DIO_u8PIN2, DIO_u8PIN_LOW);
	_delay_ms(2);
}
static void voidActivateOrange(uint8 const Copy_u8Port)
{
	DIO_u8SetPinValue(Copy_u8Port, DIO_u8PIN0, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(Copy_u8Port, DIO_u8PIN1, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(Copy_u8Port, DIO_u8PIN2, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(Copy_u8Port, DIO_u8PIN3, DIO_u8PIN_LOW);
	_delay_ms(2);
}


uint8 STEPPERMOT_u8Run(Stepper_st_t const *Copy_stMot, Direction_en_t Copy_enDirection, uint16 Copy_u8Angle)
{
	uint8 Local_u8ErrorState = OK;
	uint16 Local_u8Counter;
	uint16 Local_u16MotorSteps;
	if(Copy_stMot== NULL)
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	else
	{
		Local_u16MotorSteps = (uint16) (((uint32)Copy_u8Angle * FULL_ROTATION_STEPS) / FULL_ROTATION_ANGLE);
		switch(Copy_enDirection)
		{
		case CCW:
			for (Local_u8Counter = Local_u16MotorSteps; Local_u8Counter > 0; Local_u8Counter--)
			{
				if ((Local_u8Counter %4) == 0)
				{
					voidActivateBlue(Copy_stMot->u8ControlePort);
				}
				else if ((Local_u8Counter %4) == 1)
				{
					voidActivatePink(Copy_stMot->u8ControlePort);
				}
				else if ((Local_u8Counter %4) == 2)
				{
					voidActivateYellow(Copy_stMot->u8ControlePort);
				}
				else if ((Local_u8Counter %4) == 3)
				{
					voidActivateOrange(Copy_stMot->u8ControlePort);
				}
			}
			break;
		case CW:
			for (Local_u8Counter = Local_u16MotorSteps; Local_u8Counter > 0; Local_u8Counter--)
			{
				if ((Local_u8Counter %4) == 3)
				{
					voidActivateBlue(Copy_stMot->u8ControlePort);
				}
				else if ((Local_u8Counter %4) == 2)
				{
					voidActivatePink(Copy_stMot->u8ControlePort);
				}
				else if ((Local_u8Counter %4) == 1)
				{
					voidActivateYellow(Copy_stMot->u8ControlePort);
				}
				else if ((Local_u8Counter %4) == 0)
				{
					voidActivateOrange(Copy_stMot->u8ControlePort);
				}
			}
			break;
		default:
			break;
		}
	}
	return Local_u8ErrorState;
}
