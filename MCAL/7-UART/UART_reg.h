/*********************************************************/
/*********************************************************/
/***********		Author: Mahmoud Hafez 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: UART 		**************/
/***********		Version: 1.00		 	**************/
/*********************************************************/
/*********************************************************/

/*Preprocessor file guard*/
#ifndef USART_REGISTER_H_
#define USART_REGISTER_H_


#define UBRRH *((volatile uint8*)0x40)		/*USART Baud Rate Register High*/
#define UBRRH_URSEL	7					/*Register Select*/

#define UBRRL *((volatile uint8*)0x29)		/*USART Baud Rate Register LOW*/

#define UDR *((volatile uint8*)0x2c)		/*USART Data Register
*/
#define UCSRA *((volatile uint8*)0x2b)		/*USART Control and Status Register A*/
#define UCSRA_RXC	7					/*Receive Complete Flag*/
#define UCSRA_TXC	6					/*Transmit Complete Flag*/
#define UCSRA_UDRE	5					/*USART Data Register Empty(The Transmit Data Register is ready)*/
#define UCSRA_FE	4					/*Frame Error (in the Receive Buffer)*/
#define UCSRA_DOR	3					/*Data Over Run*/
#define UCSRA_PE	2					/*Parity Error*/
#define UCSRA_U2X	1					/*USART Double Transmission Speed*/
#define UCSRA_MPCM	0					/*Multi Processor Communication Mode*/

#define UCSRB *((volatile uint8*)0x2a)		/*USART Control and Status Register B*/
#define UCSRB_RXCIE		7				/*RX Complete Interrupt Enable*/
#define UCSRB_TXCIE		6				/*TX Complete Interrupt Enable*/
#define UCSRB_UDRIE		5				/*USART Data Register Empty Interrupt Enable*/
#define UCSRB_RXEN		4				/*Receiver Enable*/
#define UCSRB_TXEN		3				/*Transmitter Enable*/
#define UCSRB_UCSZ2		2				/*USART Character Size BIT 2*/
#define UCSRB_RXB8		1				/*Receive Data Bit 8*/
#define UCSRB_TXB8		0				/*Transmit Data Bit 8*/



#define UCSRC *((volatile uint8*)0x40)		/*USART Control and Status Register C*/
#define UCSRC_URSEL		7				/*Register Select*/
#define UCSRC_UMSEL		6				/*USART Mode Select (Synchronous or Asynchronous)*/
#define UCSRC_UPM1		5				/*USART Parity Mode Bit 1*/
#define UCSRC_UPM0		4				/*USART Parity Mode Bit 0*/
#define UCSRC_USBS		3				/*Stop Bit Select*/
#define UCSRC_UCSZ1		2				/*USART Character Size BIT 1*/
#define UCSRC_UCSZ0		1				/*USART Character Size BIT 0*/
#define UCSRC_UCPOL		0				/*USART Clock Polarity*/




#endif
