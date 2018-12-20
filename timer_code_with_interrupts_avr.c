#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER1_COMPA_vect)  // Interrupt Vector in mode "Compare match A" for Timer 1
	{
		PORTB ^=(1<<PB0);
	}


int main ()
{
	sei();  //Enable global interrupt flag


	DDRB = 0b00000001;

	TCCR1B |= ((1<<CS12)|(1<<WGM12)); //prescale 256 and Wave Generation Mode 12 (Clear Timer on Compare)
	TIMSK1 |= (1<<OCIE1A); // Time Interrupt Mask (Requests interrupt when TCNT1 = OCR1A)

	OCR1A = 62500;  // Value which will allow the interrupt to begin (16M/256= 62500)


	while (1)
	{
		//Its just to blink a Led at an 1 second rating so we don't code in this endless loop
	}


}
