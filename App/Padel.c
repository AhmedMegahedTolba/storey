

#include "stdtypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "Padel.h"

#define F_CPU 16000000
#include <util/delay.h>



/*******************GVARS****************/

/********************** 7amoksha********************/
u8  Hamoksha[8] = {
	0b00100,
	0b01010,
	0b00100,
	0b01110,
	0b10101,
	0b00100,
	0b01010,
	0b01010
};


u8 flag_direction=1;
s8 ch_1=0,ch_2=0;

u8 score1=0;
u8 score2=0;
s8 i=1,j=0;
u8 end_padel_flag;

/***************************************/
void Padel_Init(void)
{
	DIO_Init();
	LCD_Init();
	LCD_CustomChar(1,Hamoksha);
	LCD_GoTo(3,0);
	LCD_WriteString("p1:0          p2:0");
}



void Padel_Runnable(void)
{
	if (score1==5 || score2==5)
	{
		if (score1==5)
		{
			end_padel_flag=1;
		}
		if(score2==5)
		{
			end_padel_flag=2;
			
		}
	}
	LCD_GoTo(ch_2,19);
	LCD_WriteChar(1);
	LCD_GoTo(ch_1,0);
	LCD_WriteChar(1);
	
	
	if (flag_direction)
	{
		if(!DIO_ReadPin(BALL1_DOWN))
		{
			_delay_ms(20);
			while(!DIO_ReadPin(BALL1_DOWN));
			j++;
			if(j==3)
			{
				j=2;
			}
		}
		if(!DIO_ReadPin(BALL1_UP))
		{
			
			_delay_ms(20);
			while(!DIO_ReadPin(BALL1_UP));
			j--;
			if(j==-1)
			{
				j=0;
			}
		}
		
		if(!DIO_ReadPin(HAMOKSHA2_DOWN))
		{
			_delay_ms(20);
			while(!DIO_ReadPin(HAMOKSHA2_DOWN));
			LCD_GoTo(ch_2,19);
			LCD_WriteChar(' ');
			ch_2++;
			
			if(ch_2==3)
			{
				ch_2=2;
			}
		}
		
		if(!DIO_ReadPin(HAMOKSHA2_UP))
		{
			_delay_ms(20);
			while(!DIO_ReadPin(HAMOKSHA2_UP));
			LCD_GoTo(ch_2,19);
			LCD_WriteChar(' ');
			ch_2--;
			if(ch_2==-1)
			{
				ch_2=0;
			}
		}
		
		LCD_GoTo(j,i);
		LCD_WriteChar('0');
		_delay_ms(300);
		LCD_GoTo(j,i);
		LCD_WriteChar(' ');
		i++;
		if (i==18)
		{
			if(j!=ch_2)
			{
				DIO_WritePin(PUZ,DIO_HIGH);
				_delay_ms(300);
				DIO_WritePin(PUZ,DIO_LOW);
				score1++;
				LCD_GoTo(3,3);
				LCD_WriteNum(score1);
			}
			flag_direction=0;
		}

	}
	else
	{
		
		if(!DIO_ReadPin(BALL2_DOWN))
		{
			_delay_ms(20);
			while(!DIO_ReadPin(BALL2_DOWN));
			j++;
			if(j==3)
			{
				j=2;
			}
		}
		if(!DIO_ReadPin(BALL2_UP))
		{
			_delay_ms(20);
			while(!DIO_ReadPin(BALL2_UP));
			j--;
			if(j==-1)
			{
				j=0;
			}
		}
		
		if(!DIO_ReadPin(HAMOKSHA1_DOWN))
		{
			_delay_ms(20);
			while(!DIO_ReadPin(HAMOKSHA1_DOWN));
			LCD_GoTo(ch_1,0);
			LCD_WriteChar(' ');
			ch_1++;
			if(ch_1==3)
			{
				ch_1=2;
			}
		}
		
		if(!DIO_ReadPin(HAMOKSHA1_UP))
		{
			_delay_ms(20);
			while(!DIO_ReadPin(HAMOKSHA1_UP));
			LCD_GoTo(ch_1,0);
			LCD_WriteChar(' ');
			ch_1--;
			if(ch_1==-1)
			{
				ch_1=0;
			}
		}
		
		LCD_GoTo(j,i);
		LCD_WriteChar('0');
		_delay_ms(300);
		LCD_GoTo(j,i);
		LCD_WriteChar(' ');
		i--;
		if (i==1)
		{
			if(j!=ch_1)
			{
				DIO_WritePin(PUZ,DIO_HIGH);
				_delay_ms(300);
				DIO_WritePin(PUZ,DIO_LOW);
				score2++;
				LCD_GoTo(3,17);
				LCD_WriteNum(score2);
			}
			flag_direction=1;
		}
	}
}