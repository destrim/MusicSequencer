
#include "MKL05Z4.h"                    /* Device header */
#include "buttons.h"
#include "fsm.h"

/* Buttons connected to port B */
typedef enum{ BUT1 = 1, BUT2 = 2, BUT3 = 3 } ButtonType;

/*Number of IRQ generated by PORTC_PORTD interrupt*/
static const IRQn_Type myPORT_IRQn = PORTB_IRQn;

/*----------------------------------------------------------------------------
	Interrupt service routine
	Button will cause PORTC_PORTD interrupt 
 *----------------------------------------------------------------------------*/
void PORTB_IRQHandler(void) {

	if( PORTB->ISFR & (1 << BUT1) ){	/* Check in ISFR register if button BUT1 is pressed */
		but1_clicked();
    while((FPTB->PDIR&(1<<BUT1))==0);
		PORTB->PCR[BUT1] |= PORT_PCR_ISF_MASK;
  }
	
	if( PORTB->ISFR & (1 << BUT2) ){	/* Check in ISFR register if button BUT2 is pressed */
		but2_clicked();
    while((FPTB->PDIR&(1<<BUT2))==0);
		PORTB->PCR[BUT2] |= PORT_PCR_ISF_MASK;
	}
		
	if( PORTB->ISFR & (1 << BUT3) ){ /* Check in ISFR register if button BUT3 is pressed */
		but3_clicked();
    while((FPTB->PDIR&(1<<BUT3))==0);
		PORTB->PCR[BUT3] |= PORT_PCR_ISF_MASK;
  }
}

/*----------------------------------------------------------------------------
	Function initializes port C pin for switch 1 (SW1) handling
	and enables PORT_C_D interrupts
 *----------------------------------------------------------------------------*/
void buttonsInitialize(void){
	SIM->SCGC5 |=  SIM_SCGC5_PORTB_MASK; 				/* Enable clock for port B */
	
	PORTB->PCR[BUT1] |= PORT_PCR_MUX(1);      	/* Pin PTB0 is GPIO */
	PORTB->PCR[BUT2] |= PORT_PCR_MUX(1);      	/* Pin PTB1 is GPIO */
	PORTB->PCR[BUT3] |= PORT_PCR_MUX(1);      	/* Pin PTB2 is GPIO */
	
	/* Port control register for bit 3 of port C configuration. Activate pull up and interrupt */
	PORTB->PCR[BUT1] |=  PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; /* Button SW1 initialize */
	PORTB->PCR[BUT1] |=  PORT_PCR_IRQC(10);
	
	PORTB->PCR[BUT2] |=  PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; /* Button SW5 initialize */
	PORTB->PCR[BUT2] |=  PORT_PCR_IRQC(10);
	
	PORTB->PCR[BUT3] |=  PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; /* Button SW9 initialize */
	PORTB->PCR[BUT3] |=  PORT_PCR_IRQC(10);
	
		
	/* ARM's Nested Vector Interrupt Controller configuration */
	NVIC_ClearPendingIRQ(myPORT_IRQn);				/* Clear NVIC any pending interrupts on PORTC_B */
	NVIC_EnableIRQ(myPORT_IRQn);							/* Enable NVIC interrupts source for PORTC_B module */
	NVIC_SetPriority (myPORT_IRQn, 3);			/* Set PORT_B interrupt priority level  */ 

}



