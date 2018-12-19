#include <avr/io.h> /* Register defs */
#include <util/delay.h> /* Delays library */
#include <stdio.h>

#define STEPPER_PIN_1 PB0
#define STEPPER_PIN_2 PB1
#define STEPPER_PIN_3 PB2
#define STEPPER_PIN_4 PB3



int degrees_to_steps(unsigned int degrees)
{
	uint16_t steps=0, n=0;

	n=degrees/360;
	degrees =degrees - (n*360);

	steps = (degrees*17)/3;

	return steps;
}


int Stepper(unsigned int dir, unsigned int steps)
{

	static uint16_t step_number = 0;

	while(steps>0)
	{

	if(dir==1){

	switch(step_number){

	case 0:
	  PORTB ^= 0b00001001;
	  break;

	case 1:
		PORTB ^= 0b00001100;
		break;
	case 2:
		PORTB ^= 0b00000110;
		break;
	case 3:
		PORTB ^= 0b00000011;
		break;
	}

	step_number++;

		if(step_number > 3)
			step_number = 0;
		_delay_ms(40);

	  }
	steps--;

	}

	return steps;
}



int main (void)
{
	DDRB |= ((1<<STEPPER_PIN_1)|(1<<STEPPER_PIN_2)|(1<<STEPPER_PIN_3)|(1<<STEPPER_PIN_4));
	DDRB &= ~((1<<PB4)|(1<<PB5));
	DDRD &= ~((1<<PD7)|(1<<PD6));

	PORTB = 0b00110001;
	PORTD = 0b11000000;

	uint16_t re=0, re1=0, re2=0, re3=0;
	unsigned int steps=0, degrees=0;

	while(1)
	{

			if (!(PIND & (1<<PD7)))
				re=1;

			else if (re==1)
			{
				re=0;
				degrees +=100;
			}


			if (!(PIND & (1<<PD6)))
			{
				re1=1;
			}

			else if (re1==1)
			{
				re1=0;
				steps=degrees_to_steps(degrees);
				steps=Stepper(1, steps);
				degrees=0;
			}

			if (!(PINB & (1<<PB4)))
				re2=1;

			else if (re2==1)
			{
				re2=0;
				degrees +=10;
			}

			if (!(PINB & (1<<PB5)))
				re3=1;

			else if (re3==1)
			{
				re3=0;
				degrees +=1;
			}



	}


}




