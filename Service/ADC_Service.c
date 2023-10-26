#include "stdtypes.h"
#include "Utils.h"
#include "ADC_Interface.h"
#include "Sensors_Interface.h"

u32 arr_chain[3]={0};
static volatile u8 i=0;
void chain_func(void)
{
	
	static flag=0;
	if (flag==0)
	{
		arr_chain[i++]=ADC_Read_asynch();
		flag=1;
		ADC_voidStartConversion(CH_1);
		
	}
	else if (flag==1)
	{
		arr_chain[i]=ADC_Read_asynch();
		flag=0;
		i=0;
		ADC_voidStartConversion(CH_0);
	}
	/*
	else if (flag==2)
	{
		arr_chain[i]=ADC_Read_asynch();
		flag=0;
		i=0;
		ADC_voidStartConversion(CH_0);
	}
	*/
	
}
void ADC_Chain(void)
{
	ADC_SetCallBack(chain_func);
	ADC_voidStartConversion(CH_0);
	
	
}
