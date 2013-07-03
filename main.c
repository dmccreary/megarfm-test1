#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
//*****************************************************************************
// Hardware init
//*****************************************************************************
void pwmInit() {
	
	// Set PD3, PD5, PD6 to output
	DDRD|=(1<<DDD6)|(1<<DDD5)|(1<<DDD3);
	
	//
	// Timer 0
	// 
	
	// Timer 0A: ClearClear OC0A on Compare Match when up-counting.
	//           Set OC0A on Compare Match when down-counting.
	// Timer 0B: same
	TCCR0A|=(1<<COM0A1)|(1<<COM0B1);
	
	// Timer 0: Mode 1: PWM, Phase Correct
	TCCR0A|=(1<<WGM00);
	
	// // Timer 0: clkI/O/64 (From prescaler)
	// // That is 8MHz/64=125kHz, divided by 256 steps gives an overall frequency of 488 Hz.
	// TCCR0B|=(1<<CS01)|(1<<CS00);
	
	
	// Timer 0: clkI/O/8 (From prescaler)
	// That is 8MHz/8=1MHz, divided by 256 steps gives an overall frequency of 3906 Hz.
	// Should be more than fast enough for folks suffering from PWM visual issues.
	// OTOH it might actually cause problems because the LEDs may be to slow. The MOSFETs
	// should help.
	TCCR0B|=(1<<CS11);
	
	
	//
	// Timer 2
	// 
	
	// Timer 2B: Clear OC2B on Compare Match when up-counting.
	//           Set OC2B on Compare Match when down-counting.
	TCCR2A|=(1<<COM2B1);
	
	// Timer 2B: Mode 1: PWM, Phase Correct
	TCCR2A|=(1<<WGM20);
	
	// // clkT2S/64 (From prescaler) 
	// // That is 8MHz/64=125kHz, divided by 256 steps gives an overall frequency of 488 Hz.
	// TCCR2B|=(1<<CS22);
	
	// clkT2S/8 (From prescaler) 
	// That is 8MHz/8=1MHz, divided by 256 steps gives an overall frequency of 3906 Hz.
	// Should be more than fast enough for folks suffering from PWM visual issues.
	// OTOH it might actually cause problems because the LEDs may be to slow. The MOSFETs
	// should help.
	TCCR2B|=(1<<CS21);
}

//*****************************************************************************
// Initialization at 115.2k baud
//*****************************************************************************
void ioInit(void) {
	
	// Initialize UART0
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0); // Turn on the transmission and reception circuitry
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01); // Use 8-bit character sizes
	UCSR0A |= (1 << U2X0); // double speed
	UBRR0H = 0;
	UBRR0L = 8;	// 115200 - -3.5% error (seems OK with 'screen' despite high error)
	
	UCSR0B |= (1 << RXCIE0); // Enable the USART Receive Complete interrupt (USART_RXC)
}


//*****************************************************************************
// Interrup Service Routine Serial I/O
//*****************************************************************************
ISR(USART_RX_vect) {
	// read the register
	char rxByte=UDR0;
	// send the data back out
	UDR0=rxByte;
}


int main(void)
{
	pwmInit();
	ioInit();
	sei(); // enable global interrrupt flag
	OCR0A=1; // blue
	OCR0B=0; // green
	OCR2B=1; // red
    for(;;){
        //char i;
        //for(i = 0; i < 10; i++){
        //    _delay_ms(120);  /* max is 262.14 ms / F_CPU in MHz */
        //        }
//        PORTD ^= 1 << 5;    /* toggle the LED */
    }
    return 0;               /* never reached */
}

