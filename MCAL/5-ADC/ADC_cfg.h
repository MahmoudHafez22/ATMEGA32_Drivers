/*
 * ADC_cfg.h
 *
 *  Created on: Dec 13, 2022
 *      Author: Mahmoud Hafez
 */

#ifndef ADC_CFG_H_
#define ADC_CFG_H_

/**
 * @details configure the reference, options: 1- AREF_REF
 * 											  2- AVCC_REF
 * 											  3- INTERNAL_2560mV_REF
 */
#define ADC_u8REF_VOLT			AVCC_REF

/**
 * @details configure the required ADC resolutions, options are: 1- EIGHT_BITS
 * 																 2- TEN_BITS
 */
#define ADC_u8RESOLUTION        EIGHT_BITS


/**
 * @details configure the interrupt enable configuration, options are 1-ENABLE
 * 																	  2-DISABLE
 */
#define ADC_u8INTERRUPT_ENABLE          DISABLE

#define ADC_u8PRESCALER_VAL        DIVISION_BY_128


#define ADC_u32TIMOUT              50000u

#endif /* ADC_CFG_H_ */
