/*
 * Interfaces_Functions.h
 *
 *  Created on: Aug 14, 2013
 *      Author: Roosemberth Palacios
 */

#ifndef INTERFACES_FUNCTIONS_H_
#define INTERFACES_FUNCTIONS_H_

#include "Config_file.h"
#include "board.h"

void PIO_Set(AT91S_PIO *pin, u32_t pins){pin->PIO_SODR = pins;}
void PIO_Clear(AT91S_PIO *pin, u32_t pins){pin->PIO_CODR = pins;}
unsigned char PIO_Get(AT91S_PIO *pin, u32_t pins){
    u32_t reg;
    if (pin->PIO_OER == pins) {
    	reg = pin->PIO_ODSR;
    }
    	else {reg = pin->PIO_PDSR;}
    if ((reg & pin->mask) == 0) {return 0;}
    	else {return 1;}
}
unsigned char PIO_GetOutputDataStatus(AT91S_PIO *pin){
    if ((pin->PIO_ODSR & pin->mask) == 0) {return 0;}
    	else {return 1;}
}
unsigned int PIO_GetISR(AT91S_PIO *pin){
    return (pin->PIO_ISR);
}

#endif /* INTERFACES_FUNCTIONS_H_ */
