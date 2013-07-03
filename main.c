#include <avr/io.h>
#include <util/delay.h>

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



int main(void)
{
	pwmInit();
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

