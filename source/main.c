/*Standard integer definition provided by the compiler*/
#include <stdint.h>
#include "MK64F12.h"
#define DELAY 650000

void delay (uint32_t delay);

int main(void){
	/*declaration and initialization of inputs */
	uint32_t input_SW2=0;
	uint32_t input_SW3=0;

	/*Activating the GPIOx clock gating*/
	SIM->SCGC5  = 0x00000400; //GPIOB
	SIM->SCGC5 |= 0x00002000; //GPIOE
	SIM->SCGC5 |= 0x00000200; //GPIOA
	SIM->SCGC5 |= 0x00000800; //GPIOC

	/*Pin control configuration of GPIOx PINx as GPIO*/
	PORTB->PCR[21]  = 0x00000100; //GPIOB PIN21 BLUE_LED
	PORTB->PCR[22] |= 0x00000100; //GPIOB PIN22 RED_LED
	PORTE->PCR[26]  = 0x00000100; //GPIOE PIN26 GREEN_LED
	PORTC->PCR[6]   = 0x00000100; //GPIOC PIN6  SW2
	PORTA->PCR[4]   = 0x00000100; //GPIOA PIN4	SW3

	/*Port Set configuration for LEDs start*/
	GPIOB->PSOR  = 0x00200000; //BLUE_LED off
	GPIOB->PSOR |= 0x00400000; //RED_LED off
	GPIOE->PSOR  = 0x04000000; //GREEN_LED off

	/*Configures GPIOx PINx as output*/
	GPIOB->PDDR  = 0x00200000; //GPIOB PIN21 BLUE_LED
	GPIOB->PDDR |= 0x00400000; //GPIOB PIN22 RED_LED
	GPIOE->PDDR  = 0x04000000; //GPIOE PIN26 GREEN_LED

	/*Configures GPIOx PINx as input*/
	GPIOC->PDDR  &= ~(0x00000040); //GPIOC PIN6  SW2
	GPIOA->PDDR  &= ~(0x00000010); //GPIOA PIN4	SW3


	while(1){

		input_SW2 = GPIOC->PDIR;
		input_SW2 &= 0x00000040;

		input_SW3 = GPIOA->PDIR;
		input_SW3 &= 0x00000010;

		if(0x00 == input_SW2){
			//yellow
			GPIOB->PCOR  = 0x00400000; //red on
			GPIOE->PCOR  = 0x04000000;	//green on
			delay(DELAY);
			//red
			GPIOE->PSOR  = 0x04000000; //green off
			delay(DELAY);
			//purple
			GPIOB->PCOR  = 0x00200000; //blue on
			delay(DELAY);
			//blue
			GPIOB->PSOR  = 0x00400000; //red off
			delay(DELAY);
			//green
			GPIOB->PSOR  = 0x00200000; //blue off
			GPIOE->PCOR  = 0x04000000;	//green on
			delay(DELAY);
		}else if (0x00 == input_SW3){
			//green
			GPIOE->PCOR  = 0x04000000;	//green on
			delay(DELAY);
			//blue
			GPIOE->PSOR  = 0x04000000; //green off
			GPIOB->PCOR  = 0x00200000; //blue on
			delay(DELAY);
			//purple
			GPIOB->PCOR  = 0x00400000; //red on
			delay(DELAY);
			//red
			GPIOB->PSOR  = 0x00200000; //blue off
			delay(DELAY);
			//yellow
			GPIOE->PCOR  = 0x04000000;	//green on
			delay(DELAY);
			GPIOB->PSOR  = 0x00400000; //red off
		}else{
			GPIOE->PSOR  = 0x04000000; //green off
			GPIOB->PSOR  = 0x00400000;//red off
			GPIOB->PSOR  = 0x00200000; //blue off
		}
	}
	return 0;
}

void delay(uint32_t delay){
	volatile uint32_t counter;
	for(counter=delay; counter>0; counter--){
		__asm("nop");
	}
}

