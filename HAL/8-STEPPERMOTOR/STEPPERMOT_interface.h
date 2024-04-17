/**************************************************************/
/**************************************************************/
/*********		Author: Mahmoud Hafez		*******************/
/*********		File: STEPPERMOT_interface.h*******************/
/*********		Version: 1.00				*******************/
/**************************************************************/
/**************************************************************/

#ifndef STEPPERMOT_INTERFACE_H_
#define STEPPERMOT_INTERFACE_H_


typedef struct
{
	uint8 u8ControlePort;
	uint8 u8ControlePinBlue;
	uint8 u8ControlePinPink;
	uint8 u8ControlePinYellow;
	uint8 u8ControlePinOrange;
}Stepper_st_t;

typedef enum
{
	CCW,
	CW,
}Direction_en_t;

extern Stepper_st_t Global_stStepper1;
uint8 STEPPERMOT_u8Run(Stepper_st_t const *Copy_stMot, Direction_en_t Copy_enDirection, uint16 Copy_u8Angle);

#endif
