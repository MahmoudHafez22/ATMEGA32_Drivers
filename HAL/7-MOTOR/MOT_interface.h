/**************************************************************/
/**************************************************************/
/*********		Author: Mahmoud Hafez		*******************/
/*********		File: MOT_interface.h		*******************/
/*********		Version: 1.00				*******************/
/**************************************************************/
/**************************************************************/

#ifndef MOT_INTERFACE_H_
#define MOT_INTERFACE_H_



typedef struct
{
	uint8 u8ControlePort1;
	uint8 u8ControlePin1;
	uint8 u8ControlePort2;
	uint8 u8ControlePin2;
}Mot_st_t;

uint8 MOT_u8Init(Mot_st_t *Copy_stMot);
uint8 MOT_u8RotateCW(Mot_st_t const *Copy_stMot);
uint8 MOT_u8RotateCCW(Mot_st_t const *Copy_stMot);
uint8 MOT_u8Stop(Mot_st_t const*Copy_stMot);

#endif
