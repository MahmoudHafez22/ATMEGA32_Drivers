/*********************************************************/
/*********************************************************/
/***********		Author: Mahmoud Hafez 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: UART 		**************/
/***********		Version: 1.00		 	**************/
/*********************************************************/
/*********************************************************/

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_




void UART_voidInit(void);

void UART_voidSendData(uint8 Copy_u8Data);
uint8 UART_voidReceiveData(void);



#endif /* UART_INTERFACE_H_ */
