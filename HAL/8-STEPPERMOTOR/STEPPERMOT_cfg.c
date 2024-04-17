/**************************************************************/
/**************************************************************/
/*********		Author: Mahmoud Hafez		*******************/
/*********		File: STEPPERMOT_prog.c		*******************/
/*********		Version: 1.00				*******************/
/**************************************************************/
/**************************************************************/

#include "std_types.h"

#include "DIO_interface.h"

#include "STEPPERMOT_interface.h"


Stepper_st_t Global_stStepper1 =
{
		.u8ControlePort      = DIO_u8PORTB,
		.u8ControlePinBlue   = DIO_u8PIN0,
		.u8ControlePinPink   = DIO_u8PIN1,
		.u8ControlePinYellow = DIO_u8PIN2,
		.u8ControlePinOrange = DIO_u8PIN3,
};

