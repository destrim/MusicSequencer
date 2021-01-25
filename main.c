
#include "frdm_bsp.h"
#include "pmusic.h"
#include "buttons.h"
#include "tpm_pcm.h"
#include "pit.h"
#include "lcd1602.h"
#include "GUI.h"
//#include "tsi.h"

/* 
Connections

Matrix Keypad:
C4 -> PTA9
C3 -> PTA10
C2 -> PTA11
C1 -> PTA12
R1 -> PTA8
R2 -> PTA7
R3 -> PTA6
R4 -> PTA5

Speaker:
GND -> GND
+5V -> 3.3V
AUDIO_IN -> PTB7

Potentiometer:


LCD Display:
GND -> GND
VCC -> 5V
SDA -> PTB4
SCL -> PTB3
*/

int main (void) { 
	
	uint8_t	kal_error;
	
	musicInit();  // initialize music array
	
	buttonsInit();  // initialize buttons
	
	kal_error=ADC_Init();				// initialize and calibrate ADC
	if(kal_error)
	{
		while(1);									// calibration failed
	}
	
	LCD1602_Init();  // initialize lcd display
	LCD1602_Backlight(TRUE);  // turn on display backlight
	GUI_WelcomeSequence();  // display welcome sequence
	GUI_Menu();
	
	TPM0_Init();  // initialize TPM0 interrupts
	
  PIT_Init();  // initialize PIT interrupts
	
  while(1) {

		__WFI();															/* sleep & wait for interrupt */
		
	}
}
