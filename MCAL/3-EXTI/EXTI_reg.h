
#ifndef EXTI_REG_H_
#define EXTI_REG_H_

#define GICR      			*((volatile uint8*)0x5B) 	/*@brief Global interrupt control register*/
#define GICR_INIT1  		7u					        /*@brief INT1 control bit*/
#define GICR_INIT0  		6u							/*@brief INT0 control bit*/
#define GICR_INIT2  		5u							/*@brief INT1 control bit*/

#define MCUCR            	*((volatile uint8*)0x55)	/*@brief MCU control register*/
#define MCUCR_ISC00			0u							/*@brief Interrupt sense control sense */
#define MCUCR_ISC01			1u							/*@brief Interrupt sense control sense */
#define MCUCR_ISC10			2u							/*@brief Interrupt sense control sense */
#define MCUCR_ISC11			3u							/*@brief Interrupt sense control sense */

#define MCUCSR            	*((volatile uint8*)0x54)
#define MCUCR_ISC2			6u
#endif /* EXTI_REG_H_ */
