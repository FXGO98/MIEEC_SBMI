#include <avr/io.h>

int main ()
{
	DDRB = 0b00000111;
	DDRD = 0b00000111;
	PORTB = 0b00000000;
	PORTD = 0b00000000;

	TCCR1B |= (1<<CS12); //prescale 256
	int LedNumber[2];

	while (1)
	{
		if (TCNT1 > 20833)  // 16M/256=62500 counts per second      62500/3 ~ 20833  (3 toggles in 1 second)
		{
			TCNT1 = 0;
			PORTB = 1<<LedNumber[0];
			LedNumber[0]++;
			if (LedNumber[0] > 2)
			{
				LedNumber[0] = 0;
				PORTD = 1<<LedNumber[1];
				LedNumber[1]++;
				if (LedNumber[1]>2) LedNumber[1] = 0;
			}
		}
	}
}
