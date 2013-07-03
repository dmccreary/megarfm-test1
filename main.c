#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD = 1 << 5;           /* make the LED pin an output */
    for(;;){
        char i;
        for(i = 0; i < 10; i++){
            _delay_ms(120);  /* max is 262.14 ms / F_CPU in MHz */
        }
        PORTD ^= 1 << 5;    /* toggle the LED */
    }
    return 0;               /* never reached */
}
