#include <stdio.h>
#include <ctype.h>

int main()
{

	char unit;
	float temp;

	printf("Is the temperature in (F) or (C): ");
	scanf("%c", &unit);
	unit = toupper(unit);

	switch (unit)
	{
	case 'F':
		
		printf("Enter the temperature in Fahrenheit: ");
		scanf("%f", &temp);

		temp = (temp - 32) * 5/9;

		printf("The temp in Celsius is: %.1f", temp);

		break;

	case 'C':

		printf("Enter the temperature in Celsius: ");
		scanf("%f", &temp);

		temp = (temp * 9 / 5) + 32;

		printf("The temp in Fahrenheit is: %.1f", temp);

		break;
	
	default:
		printf("%c Is not a valid unit.");
		break;
	}

	return 0;
}