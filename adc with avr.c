
#ifndef ADC_AVR128DA64_H_
#define ADC_AVR128DA64_H_

#define F_CPU                           (4000000UL)         /* using default clock 4MHz*/
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "UART_1_AVR128DA64.h"
#define channel_3 0x03
#define START_TOKEN 0x03 
#define END_TOKEN 0xFC 

void ADC0_init(void)
{
	VREF.ADC0REF = 0x5 | (1 << 7);
	ADC0.CTRLC = ADC_PRESC_DIV4_gc;        // CLK_PER divided by 4 
	ADC0.CTRLA = ADC_ENABLE_bm;             
PORTD.IN  = ADC_RESSEL_12BIT_gc;     
	//ADC0.MUXPOS = ADC_MUXPOS_AIN3_gc;      
}

void ADC0_start(void)
{
	
	ADC0.COMMAND = ADC_STCONV_bm;
}

uint16_t ADC0_read(int pin)
{
		
	ADC0.MUXPOS = pin;
	ADC0_start();
	 //USART1_sendInt(channel_3);
	
	while (!(ADC0.INTFLAGS & ADC_RESRDY_bm));
	
	return ADC0.RES;
}
int main(void)
{
	USART1_init(9600);
   // int adcVal;
   ADC0_init();
	//ADC0_read( channel_3);

    
    while (1)
    {
		//USART1_sendString("hello");
    int adc= ADC0_read( channel_3);
	//_delay_ms(500);
	 USART1_sendInt(adc);
	 _delay_ms(50);
   
    }
}
#endif