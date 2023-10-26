#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "Seg_interface.h"
#include "LCD_Interface.h"
#include "KEYBAD_Interface.h"
#include "EX_Interrupt.h"
#include "ADC_Interface.h"
#include "Sensors_Interface.h"
#include "ADC_Service.h"


#define F_CPU 16000000
#include <util/delay.h>


int main(void)
{
	story_Init();
	
    while (1) 
    {
		story_Runnable();
		
   
  }

	}